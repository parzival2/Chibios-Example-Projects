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

static const ADCConfig adcConfig{};

// Number of channels for ADC
#define ADC_NUM_CHANNELS 1
#define ADC_NUM_BUFFER_DEPTH 8

// The buffer to store the collected samples.
static adcsample_t adcSamples[ADC_NUM_CHANNELS * ADC_NUM_BUFFER_DEPTH];

// ADC conversion group
static const ADCConversionGroup adcGrpConfig = {
    FALSE, // Whether we want to use Circular buffer on samples
    ADC_NUM_CHANNELS, // Number of channels that we will be sampling
    NULL, // Callback function
    NULL, // Error callback function
    0, // CR1
    ADC_CR2_SWSTART, // CR2
    ADC_SMPR1_SMP_AN15(
        ADC_SAMPLE_3), // This comes from the STM32 data sheet. The PC5 pin has the AN15
    0, // SMPR2
    0, // HTR
    0, // LTR
    ADC_SQR1_NUM_CH(ADC_NUM_CHANNELS), // SQR1: Conversion group sequence 13-16 + sequence length
    0, // SQR2: Conversion group sequence 7-12
    ADC_SQR3_SQ1_N(ADC_CHANNEL_IN15) // SQR3: Conversion group sequence 1-6
};

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
        while(true)
        {
            palToggleLine(LINE_LED3);

            chThdSleepMilliseconds(200);
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
    halInit();
    chibios_rt::System::init();

    // Initialize Serial-USB driver
    sduObjectInit(&SDU1);
    sduStart(&SDU1, &serusbcfg);

    // We will be using PC1 as the analog input
    // Set the alternative mode
    palSetPadMode(GPIOC, GPIOC_PIN5, PAL_MODE_INPUT_ANALOG);

    // Start ADC driver
    adcStart(&ADCD1, NULL);
    adcSTM32EnableTSVREFE();

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
    // uint32_t sum = 0;
    while(1)
    {
        // Get the ADC values
        adcConvert(&ADCD1, &adcGrpConfig, adcSamples, ADC_NUM_BUFFER_DEPTH);
        for(int i = 0; i < ADC_NUM_BUFFER_DEPTH; i++)
        {
            chprintf(chp, "%d\n", adcSamples[i]);
        }

        chprintf(chp, "=============\n");
        chThdSleepMilliseconds(500);
    }
}
