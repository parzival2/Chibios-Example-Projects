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

#include "ch.h"
#include "hal.h"

/**
 * A Small project that would blink the on-board LED from a thread.
 */

/* Thread definition */
static THD_WORKING_AREA(ld4ledblink, 128);
static THD_FUNCTION(ld4LedThread, arg){
	(void)arg;
	/* Set thread name */
	chRegSetThreadName("ld4LedThread");
	/* Thread should not return, so begin a while loop */
	while(TRUE)
	{
		palTogglePad(GPIOD, GPIOD_LED4);
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
  chSysInit();

  /* Create thread */
  chThdCreateStatic(ld4ledblink, sizeof(ld4ledblink), NORMALPRIO+1, ld4LedThread, NULL);

  /*
   * Normal main() thread activity, it changes the GPT4 period every
   * five seconds.
   */
  while (true) {
	  chThdSleepMilliseconds(500);
  }
}
