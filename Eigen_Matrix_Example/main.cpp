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
#define EIGEN_NO_MALLOC
#include "ch.hpp"
#include "hal.h"
#include "Eigen/Dense"
#include "chprintf.h"
#include "usbcfg.h"

/* Thread definition */
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

/*
 * A Thread that will do a matrix multiplication and print the result on serial
 */
static THD_WORKING_AREA(eigenMatrixMul, 256);
static THD_FUNCTION(eigenThread, arg){
	(void)arg;
	/*
	 * Set thread name
	 */
	chRegSetThreadName("eigenThread");

	/*
	 * Thread should not exit, begin a while loop
	 */
	while(TRUE)
	{
		// Create a random 3x3 matrix
		Eigen::Matrix3d mat = Eigen::Matrix3d::Random(3,3);
		// Multiply the matrix with a vector.
		Eigen::Vector3d vec(1., 2., 3.);
		// The resultant will be a 3x1 vector.
		Eigen::Vector3d result = mat * vec;
		// Base sequential stream to print on Serial USB
		BaseSequentialStream *chp = (BaseSequentialStream *)(&SDU1);
		chprintf(chp,"Values : %.3f, %.3f, %.3f \n", result(0), result(1), result(2));
		chThdSleepMilliseconds(1000);
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


  // Create a thread for LED blinking
  chThdCreateStatic(ld4ledblink, sizeof(ld4ledblink), NORMALPRIO + 1,
                      ld4LedThread, NULL);
  chThdCreateStatic(eigenMatrixMul, sizeof(eigenMatrixMul), NORMALPRIO + 1,
  		  eigenThread, NULL);
  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {
      chThdSleepMicroseconds(1000);
  }
  return 0;
}
