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

const uint32_t THREAD_SIZE = 128;

/**
 * @brief chp Stream for printing variables on USB
 */
BaseSequentialStream* chp = (BaseSequentialStream*)(&SDU1);

static size_t get_thd_free_stk(void* wsp, size_t size)
{
    size_t n = 0;
    uint8_t* startp = (uint8_t*)wsp;
    uint8_t* endp = (uint8_t*)wsp + size;
    while(*startp++ == CH_DBG_STACK_FILL_VALUE)
    {
        ++n;
        if(startp == endp)
            break;
    }
    return n;
}

/*
 * This is a periodic thread that does absolutely nothing except flashing
 * a LED.
 */
static THD_WORKING_AREA(waThread1, 256);
static THD_FUNCTION(Thread1, arg)
{
    (void)arg;
    stkalign_t* wa_thread_ptr = waThread1;
    chRegSetThreadName("BlinkerThread");
    float x = 0;
    size_t threadSize = 1111;
    while(true)
    {
        palToggleLine(LINE_LED3);
        if(wa_thread_ptr != NULL)
        {
            threadSize = get_thd_free_stk(wa_thread_ptr, 256);
        }
        chprintf(chp, "Thread size C Style : %d\n", threadSize);
        x += 1;

        chThdSleepMilliseconds(1000);
    }
}

class BlinkerThread : public chibios_rt::BaseStaticThread<THREAD_SIZE>
{
  protected:
    void main(void) override
    {
        setName("BlinkerThreadC++");
        stkalign_t* threadWorkingArea;
        size_t threadSize = 1111;
        threadWorkingArea = chThdGetWorkingAreaX(getSelfX().getInner());
        float x = 0;
        while(true)
        {
            palToggleLine(LINE_LED6);
            if(threadWorkingArea != NULL)
            {
                threadSize = get_thd_free_stk(threadWorkingArea, THREAD_SIZE);
            }
            chprintf(chp, "Thread size : %d\n", threadSize);
            x += 1;

            chThdSleepMilliseconds(1000);
        }
    }

  public:
    BlinkerThread(void)
        : BaseStaticThread<THREAD_SIZE>()
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

    ///
    /// Start thread
    ///
    BlinkerThread blinkerThread;
    blinkerThread.start(NORMALPRIO + 1);

    /*
     * Creates the example thread.
     */
    // chThdCreateStatic(waThread1, sizeof(waThread1), NORMALPRIO, Thread1, NULL);

    while(1)
    {
        chThdSleepMilliseconds(500);
    }
}
