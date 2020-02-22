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
 * A Small project that would change the frequency of the blink whenever the user button has
 * been pressed.
 *
 * To do this, we need to route the PWM output to the on-board LED and when ever the
 * button has been pressed, we need to change the frequency to within a limit.
 */

/* Define event for button pressed event */
static event_source_t buttonPressedEvent;
static uint16_t MAX_VALUE = 10000;
static uint16_t MIN_VALUE = 500;
static uint16_t periodValue = 500;

/* PWM Cconfig */
static PWMConfig pwmCFG = {
		10000,					/* Clock frequncy */
		10000,					/* Period of the PWM driver */
		NULL,					/* No callback */
								/* Switchon channels */
		{
				{PWM_OUTPUT_ACTIVE_HIGH, NULL},
				{PWM_OUTPUT_DISABLED, NULL},
				{PWM_OUTPUT_DISABLED, NULL},
				{PWM_OUTPUT_DISABLED, NULL}
		},
		0,
		0
};

/* Callback for the button.
 * This function will be called when the button has been pressed. Inside it
 * we emit the event we have created.
 */
static void buttonCallBack(void* arg){
	(void)arg;



	/* Lock from ISR */
	chSysLockFromISR();

	/* Change the ontime of the LED */
	pwmEnableChannelI(&PWMD4, 0, periodValue);

	/* Ensure that the button has been pressed */
	if(palReadPad(GPIOA, GPIOA_BUTTON) == PAL_HIGH)
	{
		/* Broadcast the event */
		chEvtBroadcastI(&buttonPressedEvent);
	}
	chSysUnlockFromISR();

	/* Increase the PWM period every time until a Max value is reached */
	if(periodValue < MAX_VALUE && periodValue >= MIN_VALUE)
	{
		/* Increase 100 every time */
		periodValue = periodValue + 100;
	}
	else
	{
		/* Set it to initial value */
		periodValue = MIN_VALUE;
	}
}
/*
 * Application entry point.
 */
int main(void) {

  /* Define event listener */
  event_listener_t eventListenerButton;

  /*
   * System initializations.
   * - HAL initialization, this also initializes the configured device drivers
   *   and performs the board-specific initializations.
   * - Kernel initialization, the main() function becomes a thread and the
   *   RTOS is active.
   */
  halInit();
  chSysInit();

  /* Set alternative function for the LD4-LED */
  palSetPadMode(GPIOD, GPIOD_LED4, PAL_MODE_ALTERNATE(2));

  /* Initialize events */
  chEvtObjectInit(&buttonPressedEvent);

  /* Register events */
  chEvtRegister(&buttonPressedEvent, &eventListenerButton, 0);

  /* Start PWM driver */
  pwmStart(&PWMD4, &pwmCFG);

  /* Enable PWM output */
  /* The frequency of blinking with be 1 and the ontime will be 0.1 seconds */
  pwmEnableChannel(&PWMD4, 0, 500);

  /* Enable event handling on the button */
  /* Enable listening only on the rising edge i.e. when the button is pressed */
  palEnablePadEvent(GPIOA, GPIOA_BUTTON, PAL_EVENT_MODE_RISING_EDGE);

  /* Set the callback for the button. This function will be called when the button
   * will be pressed.
   */
  palSetPadCallback(GPIOA, GPIOA_BUTTON, &buttonCallBack, NULL);

  /*
   * Normal main() thread activity, it changes the GPT4 period every
   * five seconds.
   */
  while (true) {
	  /* Access the events here */
	  eventmask_t events;

	  /* Wait for one event
	   * EVENT_MASK takes event number as the argument.
	   * The event will be created along with the event number
	   * chEvtRegister(&buttonPressedEvent, &eventListenerButton, 0);
	   * In the above line 0 is the event number.
	   */
	  events = chEvtWaitOne(EVENT_MASK(0));

	  if(events & EVENT_MASK(0))
	  {
		  /* If the event has been dispatched, toggle LD5 LED */
		  palTogglePad(GPIOD, GPIOD_LED5);
	  }
  }
}
