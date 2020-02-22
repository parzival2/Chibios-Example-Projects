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
 * This program drives the on board PINs using the General Purpose Timer driver
 * in ChibiOS. This comment gives a detailed explanation of what is going on in
 * the program.
 *
 * Explanation
 * -----------
 * Step1:
 * ------
 * Initialize GPT to drive the pin. The aim is to drive the pin with 0.1 second
 * interval. So Initialize the driver config with 10Khz timer clock. The
 * timer has to be run continuously with 1000tick time to run at 0.1 second.
 */
#include "ch.h"
#include "hal.h"

/*
 * GPT4 callback.
 */
static void gpt4cb(GPTDriver *gptp) {

  (void)gptp;
  palTogglePad(GPIOA, GPIOA_PIN1);
}

/*
 * GPT4 configuration.
 */
static const GPTConfig gpt4cfg = {
  10000,    /* 10kHz timer clock.*/
  gpt4cb,   /* Timer callback.*/
  0,
  0
};

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

  /*
   * Initializes the GPT drivers 4 and 3.
   */
  gptStart(&GPTD4, &gpt4cfg);
  gptPolledDelay(&GPTD4, 10); /* Small delay.*/

  /*
   * Set pad mode
   */
  palSetPadMode(GPIOA, GPIOA_PIN1, PAL_MODE_OUTPUT_PUSHPULL);

  /*
   * Normal main() thread activity, it changes the GPT4 period every
   * five seconds.
   */
  while (true) {
    palSetPad(GPIOD, GPIOD_LED4);
    /*
     * Run at 0.1 second interval. The callback will be called every 0.1secs.
     * The time can be calculated from the timer of the clock defined in the
     * driver config(gpt4cfg). The frequency of the timer is 10000 and the
     * callback will be called at (tick_count/10000)secs.
     */
    gptStartContinuous(&GPTD4, 1000);
    chThdSleepMilliseconds(5000);
    gptStopTimer(&GPTD4);
    palClearPad(GPIOD, GPIOD_LED4);
    gptStartContinuous(&GPTD4, 500);
    chThdSleepMilliseconds(5000);
    gptStopTimer(&GPTD4);
  }
}
