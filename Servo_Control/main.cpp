/*
    ChibiOS - Copyright (C) 2006..2016 Nicolas Reinecke
    Licensed under the Apache License, Version 2.0 (the "License");
    you may not use this file except in compliance with the License.
    You may obtain a copy of the License at
        http://www.apache.org/licenses/LICENSE-2.0
    Unless required by applicable law or agreed to in writing, software
    distributed under the License is distributed on an "AS IS" BASIS,
    WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
    See the License for the specific language governing permissions and
    limitations under the License.
*/
// clang-format off
#include "ch.hpp"
#include "hal.h"
#include "string.h"
#include "usbcfg.h"
#include "ros.h"
#include "Libraries/ros_lib/sensor_msgs/Joy.h"
#include "Libraries/ros_lib/std_msgs/Int32.h"
// clang-format on

// PWM channel config
/*
 * Define the PWM driver config
 */
static PWMConfig pwmCFG = {1000000, /* 10kHz PWM clock frequency */
                           20000, /* PWM period = ticks / PWM clock frequency = 50HZ */
                           NULL, /* No callback */
                           /*
                            * Enable all channels
                            */
                           {{PWM_OUTPUT_ACTIVE_HIGH, NULL},
                            {PWM_OUTPUT_DISABLED, NULL},
                            {PWM_OUTPUT_DISABLED, NULL},
                            {PWM_OUTPUT_DISABLED, NULL}},
                           0,
                           0};

const uint32_t BLINK_THREAD_SIZE = 256;
const uint32_t SERVO_ROS_THREAD_SIZE = 512;

class RosServoControlThread : public chibios_rt::BaseStaticThread<SERVO_ROS_THREAD_SIZE>
{
  protected:
    void main(void) override
    {
        setName("RosServoControlThread");
        mRosNodeHandle.advertise(mPwmCalculatedValuePublisher);
        mRosNodeHandle.subscribe(mJoySubscriber);
        mRosNodeHandle.initNode();
        pwmEnableChannel(&PWMD4, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD4, 500));
        while(TRUE)
        {
            mRosNodeHandle.spinOnce();
            pwmEnableChannel(&PWMD4, 0, PWM_PERCENTAGE_TO_WIDTH(&PWMD4, mPwmCalculatedValue.data));
            chThdSleepMilliseconds(10);
        }
    }

  public:
    RosServoControlThread(void)
        : BaseStaticThread<SERVO_ROS_THREAD_SIZE>()
        , mJoySubscriber("joy", &RosServoControlThread::joyCallback, this)
        , mPwmCalculatedValue()
        , mPwmCalculatedValuePublisher("pwm_calculated", &mPwmCalculatedValue)
    {
    }

  private:
    // Constants
    static constexpr int32_t POS_OUTPUT_START = 750;
    static constexpr int32_t POS_OUTPUT_END = 500;
    static constexpr int32_t NEG_OUTPUT_START = 751;
    static constexpr int32_t NEG_OUTPUT_END = 1000;
    /**
     * @brief mRosNodeHandle The ros nodehandle that will be used to communicate with ros.
     */
    ros::NodeHandle mRosNodeHandle;
    /**
     * @brief mDs4StatusSubscriber Subscriber to handle ds4 messages.
     */
    ros::Subscriber<sensor_msgs::Joy, RosServoControlThread> mJoySubscriber;
    /**
     * @brief mPwmCalculatedValue The calculated PWM value after mapping the range.
     */
    std_msgs::Int32 mPwmCalculatedValue;
    /**
     * @brief mPwmCalculatedValuePublisher The publisher to publish the caluclated value.
     */
    ros::Publisher mPwmCalculatedValuePublisher;
    /**
     * @brief ds4StatusCallback The callback for the DS4 message.
     * @param statusMessage The status message originating from the playstation controller.
     */
    void joyCallback(const sensor_msgs::Joy& joyMessage)
    {
        // Extract the values and calculate the output PWM value by mapping the range.
        // Our steering angle will be on axes[0]
        // The maximum angle of the steering is 1.0 and the minimum value will be -1.0
        if(joyMessage.axes[0] >= 0)
        {
            float slope = 1.0 * ((POS_OUTPUT_START - POS_OUTPUT_END) / 1.0);
            float output = POS_OUTPUT_START - slope * (joyMessage.axes[0] - 0.0);
            mPwmCalculatedValue.data = static_cast<int32_t>(output);
        }
        else if(joyMessage.axes[0] < 0)
        {
            float slope = 1.0 * ((NEG_OUTPUT_END - NEG_OUTPUT_START) / -1.0);
            float output = NEG_OUTPUT_START + slope * (joyMessage.axes[0] - 0.0);
            mPwmCalculatedValue.data = static_cast<int32_t>(output);
        }
        // Publish the message
        mPwmCalculatedValuePublisher.publish(&mPwmCalculatedValue);
    }
};

class BlinkerThread : public chibios_rt::BaseStaticThread<BLINK_THREAD_SIZE>
{
  protected:
    void main(void) override
    {
        setName("BlinkerThreadC++");
        while(true)
        {
            palToggleLine(LINE_LED6);
            chThdSleepMilliseconds(1000);
        }
    }

  public:
    BlinkerThread(void)
        : BaseStaticThread<BLINK_THREAD_SIZE>()
    {
    }
};

/*
 * Application entry point.
 */
int main(void)
{
    /*
     * System initializations.
     * - HAL initialization, this also initializes the configured device drivers
     *   and performs the board-specific initializations.
     * - Kernel initialization, the main() function becomes a thread and the
     *   RTOS is active.
     */
    halInit();
    chibios_rt::System::init();

    // Initialize Serial-USB driver
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    // Initialize the pwm channel
    // Use the PB6 pin of STM32F4 Discovery board.
    palSetPadMode(GPIOB, 6, PAL_MODE_ALTERNATE(2));
    pwmStart(&PWMD4, &pwmCFG);

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1500);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    ///
    /// Start thread
    ///
    BlinkerThread blinkerThread;
    blinkerThread.start(NORMALPRIO + 1);

    RosServoControlThread rosServoThread;
    rosServoThread.start(NORMALPRIO + 1);

    while(1)
    {
        chThdSleepMilliseconds(500);
    }
}
