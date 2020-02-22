#include "ch.hpp"
#include "hal.h"
#include "usbcfg.h"
#include "chprintf.h"

class BlinkerThread : public chibios_rt::BaseStaticThread<128>
{
protected:
    void main(void) override
    {
        setName("BlinkerThread");
        while(true)
        {
            palToggleLine(LINE_LED3);
            sleep(TIME_MS2I(1000));
        }
    }
public:
    BlinkerThread(void) : BaseStaticThread<128>()
    {

    }
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

    BlinkerThread blinkerThread;
    blinkerThread.start(NORMALPRIO+1);

    /*
   * Normal main() thread activity, in this demo it does nothing.
   */
    while (true) {
        chibios_rt::BaseThread::sleep(TIME_MS2I(500));
    }
    return 0;
}
