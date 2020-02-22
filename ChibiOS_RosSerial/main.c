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
/*
 * Define the PWM driver config
 */
static PWMConfig pwmCFG =
{
   100000,                   /* 10kHz PWM clock frequency */
   1000,                   /* PWM period = ticks / PWM clock frequency */
   NULL,                    /* No callback */
   /*
    * Enable all channels
    */
   {
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL},
    {PWM_OUTPUT_ACTIVE_HIGH, NULL}
   },
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

  uint16_t dir = 0;
  uint16_t width = 0;

  /*
   * Route the PWM output to the on-board LEDs. To do this, we have to configure
   * on board LEDs to alternate function. The alternate function table can be
   * seen on DM00037051(Data sheet - page No - 65). Since the on board LEDs are
   * connected to PD12 - PD15 we have to look for PD12 - PD16 alternate function.
   *
   * As can be seen in the table, by setting the second Alternate Function
   * indicated by AF2, we can connect timers to these pins.
   *
   * Timer4 can be connected to all these pins according to data sheet.
   *
   * To use Timer4, it has to be switched on by changing it to TRUE in mcuconf
   */
  palSetPadMode(GPIOD, GPIOD_LED3, PAL_MODE_ALTERNATE(2));
  palSetPadMode(GPIOD, GPIOD_LED4, PAL_MODE_ALTERNATE(2));
  palSetPadMode(GPIOD, GPIOD_LED5, PAL_MODE_ALTERNATE(2));
  palSetPadMode(GPIOD, GPIOD_LED6, PAL_MODE_ALTERNATE(2));

  /*
   * Start timer 4 with the above.
   */
  pwmStart(&PWMD4, &pwmCFG);



  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {

      if (dir == 0)
      {
        width = (width + 1);
      }
      else
      {
        width = (width - 1);
      }

      if (width >= 1000)
      {
        dir = 1;
      }
      else if (width == 0)
      {
        dir = 0;
      }
    /*
       * Enable channel 0 with 10% duty cycle
       */
      pwmEnableChannel(&PWMD4, 3, width);
      chThdSleepMicroseconds(1000);
  }
  return 0;
}
