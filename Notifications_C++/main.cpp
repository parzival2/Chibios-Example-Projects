#include "ch.hpp"
#include "hal.h"
#include "usbcfg.h"
#include "chprintf.h"

BaseSequentialStream *chp = (BaseSequentialStream *)(&SDU1);


class LEDData
{
public:
    uint8_t pin;
    bool set;
    LEDData():pin(0),set(false)
    {}
};

chibios_rt::Mailbox<LEDData*, 10> ledDataMailBox;

static THD_WORKING_AREA(notifier1Area, 128);
static THD_FUNCTION(notifier1Thread, arg)
{
    (void) arg;
    chRegSetThreadName("notifier1Thread");
    LEDData *data;
    while(TRUE)
    {
        ledDataMailBox.fetch(&data, TIME_INFINITE);
        if(data->set)
        {
            palSetPad(GPIOD, data->pin);
        }
        else
        {
            palClearPad(GPIOD, data->pin);
        }
        chThdSleepMilliseconds(50);
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

    /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
    usbDisconnectBus(serusbcfg.usbp);
    chThdSleepMilliseconds(1500);
    usbStart(serusbcfg.usbp, &usbcfg);
    usbConnectBus(serusbcfg.usbp);

    chThdCreateStatic(notifier1Area, sizeof(notifier1Area), NORMALPRIO+1,
                      notifier1Thread, NULL);
    //chThdCreateStatic(notifier2Area, sizeof(notifier2Area), NORMALPRIO+1,
    //                  notifier2Thread, NULL);

    /*
   * Normal main() thread activity, in this demo it does nothing.
   */
    LEDData data;
    LEDData* d = &data;
    while (true) {
        d->pin = LINE_LED3;
        d->set = true;
        msg_t result = ledDataMailBox.post(d, TIME_IMMEDIATE);
        if(result == MSG_OK)
        {
            chprintf(chp, "MSG_OK\n");
        }
        else if (result == MSG_RESET)
        {
            chprintf(chp, "MSG_RESET\n");
        }
        else if(result == MSG_TIMEOUT)
        {
            chprintf(chp, "MSG_TIMEOUT\n");
        }
        chThdSleepMilliseconds(50);
        d->pin = LINE_LED3;
        d->set = false;
        result = ledDataMailBox.post(d, TIME_IMMEDIATE);
        if(result == MSG_OK)
        {
            chprintf(chp, "MSG_OK\n");
        }
        else if (result == MSG_RESET)
        {
            chprintf(chp, "MSG_RESET\n");
        }
        else if(result == MSG_TIMEOUT)
        {
            chprintf(chp, "MSG_TIMEOUT\n");
        }
        chThdSleepMilliseconds(50);
    }
    return 0;
}
