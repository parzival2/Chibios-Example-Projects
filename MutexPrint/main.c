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
#include "ch.h"
#include "hal.h"
#include "chprintf.h"
#include "usbcfg.h"

static mutex_t mtx;


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

/* Thread definition - First printing thread*/
static THD_WORKING_AREA(printfunction1, 128);
static THD_FUNCTION(threadprint1, arg) {
  (void)arg;
  /* Set thread name */
  chRegSetThreadName("threadprint1");

  BaseSequentialStream *chp = (BaseSequentialStream *)(&SDU1);
  /* Thread should not return, so begin a while loop */
  while (TRUE) {
    chMtxLock(&mtx);
    chprintf(chp, "Printing from thread1\n");
    chMtxUnlock(&mtx);
    chThdSleepMicroseconds(10);
  }
}

/* Thread definition - First printing thread*/
static THD_WORKING_AREA(printfunction2, 128);
static THD_FUNCTION(threadprint2, arg) {
  (void)arg;
  /* Set thread name */
  chRegSetThreadName("threadprint2");
  BaseSequentialStream *chp = (BaseSequentialStream *)(&SDU1);
  /* Thread should not return, so begin a while loop */
  while (TRUE) {
    chMtxLock(&mtx);
    chprintf(chp, "Printing from thread2\n");
    chMtxUnlock(&mtx);
    chThdSleepMicroseconds(10);
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
  chSysInit();

  // Initialize Serial-USB driver
  sduObjectInit(&SDU1);
  sduStart(&SDU1, &serusbcfg);
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

  // Initialize mutex
  chMtxObjectInit(&mtx);

  // Create a thread for LED and SPI
  chThdCreateStatic(ld4ledblink, sizeof(ld4ledblink), NORMALPRIO + 1,
                      ld4LedThread, NULL);
  chThdCreateStatic(printfunction1, sizeof(printfunction1), NORMALPRIO + 1,
                      threadprint1, NULL);
  chThdCreateStatic(printfunction2, sizeof(printfunction2), NORMALPRIO + 1,
                        threadprint2, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {
    chThdSleepMicroseconds(1000);
  }
  return 0;
}
