/*
 * DAC_Signal.c
 *
 *  Created on: 20 de abr de 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void DAC_Signal_Init(void)
{
	 DAC_Signal_Sine_Calc();
	 STM32_Test_Board.DAC_Signal.Frequency = 1000;
}

void DAC_Signal_Sine_Calc(void)
{

	for(uint8_t Sine_Signal_Index = 0; Sine_Signal_Index < SINE_SAMPLE_AMOUNT; Sine_Signal_Index++)
	{
		STM32_Test_Board.DAC_Signal.Sine[Sine_Signal_Index] = 0.5*((sin(Sine_Signal_Index * 2 * PI/SINE_SAMPLE_AMOUNT ) + 1)*(CENTER_AMPLITUDE_SINUSOID_BITS));
	}
}

void DAC_Signal_Wave_Generation_Timer(void)
{
	__HAL_TIM_SET_PRESCALER(&htim15,(48-1));
	__HAL_TIM_SET_AUTORELOAD(&htim15,(unsigned char)(((SINE_TIMER_PRESCALER_FREQUENCY/STM32_Test_Board.DAC_Signal.Frequency)/SINE_SAMPLE_AMOUNT) - 1));
	__HAL_TIM_SET_COUNTER(&htim15,0);
	TIM2 ->EGR = TIM_EGR_UG;
}

void DAC_Signal_Start(void)
{
	HAL_TIM_Base_Start(&htim15);
	HAL_DAC_Start_DMA(&hdac1,DAC_CHANNEL_1, (uint32_t*)STM32_Test_Board.DAC_Signal.Sine, SINE_SAMPLE_AMOUNT, DAC_ALIGN_12B_R);
}

void DAC_Signal_Generation(void)
{
	DAC_Signal_Wave_Generation_Timer();
	DAC_Signal_Start();
}

