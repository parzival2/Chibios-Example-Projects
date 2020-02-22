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

/**
 * Program that prints "Hello" when a serial terminal is opened. Make sure that
 * the baudrate is 115200.
 */

#include "ch.h"
#include "hal.h"
#include "chprintf.h"

// Serial driver config
static SerialConfig sd2Config = {
		115200, 					/* Baudrate */
		0,
		USART_CR2_STOP1_BITS,
		0
};
/*
 * Application entry point.
 */
int main(void) {
  /*
   * System initialisations.
   * - HAL initialisation, this also initialises the configured device drivers
   *   and performs the board-specific initialisations.
   * - Kernel initialisation, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  // Set the GPIOA_PIN2(PA2) pin on STM32F4 board as TX.
  // The alternate function table of GPIO's can be seen at
  // https://github.com/parzival2/STM32F4-Evaluation-Board-Free-IO-Pinouts
  palSetPadMode(GPIOA, 2, PAL_MODE_ALTERNATE(7));
  // Likewise set the GPIO_PIN3(PA3) pin on STM32F4 boards as RX
  palSetPadMode(GPIOA, 3, PAL_MODE_ALTERNATE(7));
  // This is needed to start the driver. It takes the struct SerialConfig as input.
  sdStart(&SD2, &sd2Config);


  /*
   * Normal main() thread activity, it changes the GPT4 period every
   * five seconds.
   */
  while (true) {
	  chprintf((BaseSequentialStream*)&SD2, "Hello\r\n");
	  palTogglePad(GPIOD, GPIOD_LED4);
	  chThdSleepMilliseconds(1000);
  }
}
