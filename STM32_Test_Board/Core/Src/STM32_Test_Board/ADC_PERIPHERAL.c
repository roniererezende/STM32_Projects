/*
 * ADC_PERIPHERAL.c
 *
 *  Created on: Mar 30, 2022
 *      Author: Roniere Rezende
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void ADC_PERIPHERAL_Init(void)
{
	HAL_ADC_Start_DMA(&hadc1, STM32_Test_Board.ADC_Peripheral.Buffer_ADC_Channels_Monitoring, NUMBER_MONITORING_CHANNELS);

	HAL_ADC_Start(&hadc1);

}

