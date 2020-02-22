/*
    ChibiOS - Copyright (C) 2006..2018 Giovanni Di Sirio

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

/*
 * This example tries to drive the on-board LEDs using the PWM output.
 */
#include "ch.hpp"
#include "hal.h"
#include "usbcfg.h"
#include "mpu9250.hpp"
#include "chprintf.h"
// User includes
#include "datapackets/acceldata.hpp"
#include "datapackets/gyrodata.hpp"
// Ros includes
#include "roslib/ros.h"
#include "roslib/sensor_msgs/Imu.h"


#define CHPRINTF_USE_FLOAT TRUE
#define SPI_BaudRatePrescaler_2 ((uint16_t)0x0000)   //  42 MHz      21 MHZ
#define SPI_BaudRatePrescaler_4 ((uint16_t)0x0008)   //  21 MHz      10.5 MHz
#define SPI_BaudRatePrescaler_8 ((uint16_t)0x0010)   //  10.5 MHz    5.25 MHz
#define SPI_BaudRatePrescaler_16 ((uint16_t)0x0018)  //  5.25 MHz    2.626 MHz
#define SPI_BaudRatePrescaler_32 ((uint16_t)0x0020)  //  2.626 MHz   1.3125 MHz
#define SPI_BaudRatePrescaler_64 ((uint16_t)0x0028)  //  1.3125 MHz  656.25 KHz
#define SPI_BaudRatePrescaler_128 \
  ((uint16_t)0x0030)  //  656.25 KHz  328.125 KHz
#define SPI_BaudRatePrescaler_256 ((uint16_t)0x0038)  //  328.125 KHz 164.06 KHz

/*
 * Create ROS node-handle
 */
ros::NodeHandle rosNodeHandle;

/*
 * Create publisher
 *
 * The topics that we are going to advertise are
 * 1) imu
 *
 * The publisher will be imu_publisher
 */
// Form IMU message
sensor_msgs::Imu imuMessage;
ros::Publisher imuPublisher("imu", &imuMessage);


/* Thread definition */
/*
 * Thread to just blink LED
 */
static THD_WORKING_AREA(ld4ledblink, 128);
static THD_FUNCTION(ld4LedThread, arg) {
  (void)arg;
  /* Set thread name */
  chRegSetThreadName("ld4LedThread");
  /* Thread should not return, so begin a while loop */
  while (TRUE) {
    palTogglePad(GPIOD, GPIOD_LED4);
    chThdSleepMilliseconds(100);
  }
}

/* Thread definition */
/*
 * This thread will publish imu message at 50Hz.
 */
static THD_WORKING_AREA(spithread, 256);
static THD_FUNCTION(spithdfunction, arg) {
  MPU9250 *mpu = (MPU9250 *)arg;
  chRegSetThreadName("spithread");
  while (TRUE) {
	// Check for callbacks by calling spinOnce
	rosNodeHandle.spinOnce();
    // Print accelerometer data on screen
    AccelData accelData;
    mpu->getAccelData(accelData);
    // Gyro data
    GyroData gyroData;
    mpu->getGyroData(gyroData);

    // Angular velocity
    imuMessage.angular_velocity.x = gyroData.getAngularVelX() * 0.0174533;
    imuMessage.angular_velocity.y = gyroData.getAngularVelY() * 0.0174533;
    imuMessage.angular_velocity.z = gyroData.getAngularVelZ() * 0.0174533;
    // Acceleration
    imuMessage.linear_acceleration.x = accelData.getAccelX();
    imuMessage.linear_acceleration.y = accelData.getAccelY();
    imuMessage.linear_acceleration.z = accelData.getAccelZ();
    imuMessage.header.stamp = rosNodeHandle.now();
    // Publish the message
    imuPublisher.publish(&imuMessage);
    chThdSleepMilliseconds(20);
  }
}

/*
 * Application entry point.
 */
int main(void) {
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

  /*
   * Initialize ros node
   */
  rosNodeHandle.initNode();

  /*
   * Advertise topics
   */
  rosNodeHandle.advertise(imuPublisher);

  /*
   * SPI Config definition
   */
  SPIConfig spiConfig = {false, NULL, GPIOB, 12, SPI_BaudRatePrescaler_8, 0};

  /*
     * SPI1 I/O pins setup.
     */
  palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5) |
                               PAL_STM32_OSPEED_HIGHEST); /* New SCK.     */
  palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5) |
                               PAL_STM32_OSPEED_HIGHEST); /* New MISO.    */
  palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5) |
                               PAL_STM32_OSPEED_HIGHEST); /* New MOSI.    */
  palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL |
                               PAL_STM32_OSPEED_HIGHEST); /* New CS.      */
  palSetPad(GPIOB, 12);

  // Initialize the MPU9250 class
  MPU9250 mpu9250(&SPID2, &spiConfig);

  // Create a thread for LED and SPI
  chThdCreateStatic(ld4ledblink, sizeof(ld4ledblink), NORMALPRIO + 1,
                    ld4LedThread, NULL);
  chThdCreateStatic(spithread, sizeof(spithread), NORMALPRIO + 1,
                    spithdfunction, &mpu9250);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {
    chThdSleepMicroseconds(1000);
  }
  return 0;
}
