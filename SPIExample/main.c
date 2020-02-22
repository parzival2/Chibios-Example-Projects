#include "ch.h"
#include "hal.h"
#include "usbcfg.h"
#include "chprintf.h"

#define MPU9250_ADDRESS  0x68
#define WHO_AM_I_RESP    0x73
#define WHO_AM_I         0x75
#define READ_FLAG   0x80
#define READHEX 0x00

#define SPI_BaudRatePrescaler_2         ((uint16_t)0x0000) //  42 MHz      21 MHZ
#define SPI_BaudRatePrescaler_4         ((uint16_t)0x0008) //  21 MHz      10.5 MHz
#define SPI_BaudRatePrescaler_8         ((uint16_t)0x0010) //  10.5 MHz    5.25 MHz
#define SPI_BaudRatePrescaler_16        ((uint16_t)0x0018) //  5.25 MHz    2.626 MHz
#define SPI_BaudRatePrescaler_32        ((uint16_t)0x0020) //  2.626 MHz   1.3125 MHz
#define SPI_BaudRatePrescaler_64        ((uint16_t)0x0028) //  1.3125 MHz  656.25 KHz
#define SPI_BaudRatePrescaler_128       ((uint16_t)0x0030) //  656.25 KHz  328.125 KHz
#define SPI_BaudRatePrescaler_256       ((uint16_t)0x0038) //  328.125 KHz 164.06 KHz

/*
 * SPI TX and RX buffers.
 */
static uint8_t txbuf[2];
static uint8_t rxbuf[2];

void spiCallback(void)
{
	palTogglePad(GPIOD, GPIOD_LED3);
}

static const SPIConfig spiConfig = {
		false,
		NULL,
		GPIOB,
		12,
		SPI_BaudRatePrescaler_8,
		0
};

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
		chThdSleepMilliseconds(100);
	}
}

/* Thread definition */
static THD_WORKING_AREA(spithread, 128);
static THD_FUNCTION(spithdfunction, arg){
	(void)arg;
	/* Set thread name */
	chRegSetThreadName("spithread");
	BaseSequentialStream *chp = (BaseSequentialStream*)(&SDU1);
	/* Thread should not return, so begin a while loop */
	while(TRUE)
	{
		spiAcquireBus(&SPID2);
		spiStart(&SPID2, &spiConfig);
		spiSelect(&SPID2);
		spiExchange(&SPID2, 2, &txbuf, &rxbuf);
		//spiSend(&SPID2, 2, &txbuf);
		//spiStartReceive(&SPID2, 1, &rxbuf);
		chprintf(chp, "Sending data over SPI %x\n", txbuf[0]);
		chprintf(chp, "Second byte : %x\n", txbuf[1]);
		//  spiSend(&SPID2, 1, &txbuf);
		//spiReceive(&SPID2, 1, &rxbuf);
		chprintf(chp, "Received data over SPI %x\n", rxbuf[1]);
		spiUnselect(&SPID2);
		spiReleaseBus(&SPID2);
		chThdSleepMilliseconds(10);
	}
}

/*
 * Application entry point.
 */
int main(void) {
	unsigned int i;

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

  /*
     * Activates the USB driver and then the USB bus pull-up on D+.
     * Note, a delay is inserted in order to not have to disconnect the cable
     * after a reset.
     */
  usbDisconnectBus(serusbcfg.usbp);
  chThdSleepMilliseconds(1500);
  usbStart(serusbcfg.usbp, &usbcfg);
  usbConnectBus(serusbcfg.usbp);

  /*
   * SPI1 I/O pins setup.
   */
  palSetPadMode(GPIOB, 13, PAL_MODE_ALTERNATE(5) |
                             PAL_STM32_OSPEED_HIGHEST);       /* New SCK.     */
  palSetPadMode(GPIOB, 14, PAL_MODE_ALTERNATE(5) |
                             PAL_STM32_OSPEED_HIGHEST);       /* New MISO.    */
  palSetPadMode(GPIOB, 15, PAL_MODE_ALTERNATE(5) |
                             PAL_STM32_OSPEED_HIGHEST);       /* New MOSI.    */
  palSetPadMode(GPIOB, 12, PAL_MODE_OUTPUT_PUSHPULL |
                             PAL_STM32_OSPEED_HIGHEST);       /* New CS.      */
  palSetPad(GPIOB, 12);

  /*
     * Prepare transmit pattern.
     */
    //for (i = 0; i < sizeof(txbuf); i++)
    //  txbuf[i] = (uint8_t)i;
  txbuf[0] = WHO_AM_I | READ_FLAG;
  txbuf[1] = READHEX;

  chThdCreateStatic(ld4ledblink, sizeof(ld4ledblink),
		  NORMALPRIO+1, ld4LedThread, NULL);
  chThdCreateStatic(spithread, sizeof(spithread),
  		  NORMALPRIO+1, spithdfunction, NULL);

  /*
   * Normal main() thread activity, in this demo it does nothing.
   */
  while (true) {
    chThdSleepMilliseconds(500);
  }
  return 0;
}
