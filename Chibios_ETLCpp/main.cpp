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
#include "chprintf.h"
#include "usbcfg.h"
#include "etl/vector.h"
// clang-format on

const uint32_t BLINK_THREAD_SIZE = 256;

class MessageData
{
  public:
    uint8_t number;
    MessageData()
        : number(0)
    {
    }
};

chibios_rt::Mailbox<MessageData*, 5> messageMailBox;
// Vector to hold the data
etl::vector<MessageData, 5> messageVector;

/**
 * @brief chp Stream for printing variables on USB
 */
BaseSequentialStream* chp = (BaseSequentialStream*)(&SDU1);

class BlinkerThread : public chibios_rt::BaseStaticThread<BLINK_THREAD_SIZE>
{
  protected:
    void main(void) override
    {
        setName("BlinkerThreadC++");
        while(true)
        {
            palToggleLine(LINE_LED6);

            for(size_t i = 0; i < messageVector.size(); i++)
            {
                MessageData* data;
                messageMailBox.fetch(&data, TIME_INFINITE);
                chprintf(chp, "Vector element %d : %d\n", i, data->number);
            }
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

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1500);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    // Fill the vector
    for(size_t i = 0; i < 5; i++)
    {
        MessageData messageData;
        messageData.number = 10 + i;
        messageVector.push_back(messageData);
    }

    ///
    /// Start thread
    ///
    BlinkerThread blinkerThread;
    blinkerThread.start(NORMALPRIO + 1);

    while(1)
    {
        MessageData messageData;
        for(size_t i = 0; i < 5; i++)
        {
            messageData.number = 10 + i;
            MessageData* dataPtr = &messageData;
            msg_t result = messageMailBox.post(dataPtr, TIME_IMMEDIATE);
        }
        chThdSleepMilliseconds(500);
    }
}
