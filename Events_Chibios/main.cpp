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
#include "chprintf.h"
// clang-format on

///
/// Define an EventSource
///
event_source_t ledEventSource;

///
/// Define event flags
///
#define LED3 (eventflags_t)0
#define LED4 (eventflags_t)1
#define LED5 (eventflags_t)2
#define LED6 (eventflags_t)6
/**
 * @brief chp Stream for printing variables on USB
 */
BaseSequentialStream* chp = (BaseSequentialStream*)(&SDU1);

class BlinkerThread : public chibios_rt::BaseStaticThread<512>
{
  protected:
    void main(void) override
    {
        setName("BlinkerThread");

        // Define an event listener
        event_listener_t ledEventListener;
        // Register for the event
        chEvtRegisterMask(&ledEventSource, &ledEventListener, EVENT_MASK(0));
        eventflags_t flags;
        while(true)
        {
            chEvtWaitAny(EVENT_MASK(0));
            flags = chEvtGetAndClearFlags(&ledEventListener);
            if(flags == LED3)
            {
                palToggleLine(LINE_LED3);
            }
            else if(flags == LED4)
            {
                palToggleLine(LINE_LED4);
            }
            else if(flags == LED5)
            {
                palToggleLine(LINE_LED5);
            }
            else if(flags == LED6)
            {
                palToggleLine(LINE_LED6);
            }
        }
    }

  public:
    BlinkerThread(void)
        : BaseStaticThread<512>()
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
    chEvtObjectInit(&ledEventSource);
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

    ///
    /// Start thread
    ///
    BlinkerThread blinkerThread;
    blinkerThread.start(NORMALPRIO + 1);
    while(1)
    {
        chEvtBroadcastFlags(&ledEventSource, LED3);
        chThdSleepMilliseconds(50);
        chEvtBroadcastFlags(&ledEventSource, LED4);
        chThdSleepMilliseconds(50);
        chEvtBroadcastFlags(&ledEventSource, LED5);
        chThdSleepMilliseconds(50);
        chEvtBroadcastFlags(&ledEventSource, LED6);
        chThdSleepMilliseconds(50);
    }
}
