/*
 * encoder.c
 *
 *  Created on: May 4, 2019
 *      Author: kalyansreenivas
 */
#include "ch.h"
#include "hal.h"
#include "encoder.h"

void initEncoder(void)
{
	palSetPadMode(GPIOB, GPIOB_GPIO_A, PAL_MODE_ALTERNATE(2));
	palSetPadMode(GPIOB, GPIOB_GPIO_B, PAL_MODE_ALTERNATE(2));

	    rccEnableTIM3(FALSE); // enable timer 3 clock
	    rccResetTIM3();
	    STM32_TIM3->CR2 = 0;
	    STM32_TIM3->PSC = 0; // Prescaler value.
	    STM32_TIM3->SR = 0; // Clear pending IRQs.
	    STM32_TIM3->DIER = 0; // DMA-related DIER bits.
	    STM32_TIM3->SMCR = STM32_TIM_SMCR_SMS(3); // count on both edges
	    STM32_TIM3->CCMR1 = STM32_TIM_CCMR1_CC1S(1); // CC1 channel is input, IC1 is mapped on TI1
	    STM32_TIM3->CCMR1 |= STM32_TIM_CCMR1_CC2S(1); // CC2 channel is input, IC2 is mapped on TI2
	    STM32_TIM3->CCER = 0;
	    STM32_TIM3->ARR = 0xFFFF;
	    STM32_TIM3->CR1 = 1; // start
}
