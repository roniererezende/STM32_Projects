/*
 * ADC_PERIPHERAL.c
 *
 *  Created on: Mar 30, 2022
 *      Author: Roniere Rezende
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

extern ADC_ChannelConfTypeDef sConfig;

void ADC_Peripheral_Init(void)
{
	STM32_Test_Board.ADC_Peripheral.LM35.Counter_Update = TIMER_UPDATE_ADC_VALUE;
	STM32_Test_Board.ADC_Peripheral.LM35.Update = true;

	HAL_ADCEx_Calibration_Start(&hadc1);
	//HAL_ADC_Start(&hadc1);


	//HAL_ADC_Start_DMA(&hadc1, &STM32_Test_Board.ADC_Peripheral.LM35.Sampled_Value, NUMBER_MONITORING_CHANNEL);

	//HAL_ADC_Start(&hadc1);
}

void ADC_Peripheral_LM35_Get_Sample_Temperature(void)
{
	if((STM32_Test_Board.ADC_Peripheral.LM35.Counter_Samples < NUMBER_SAMPLES) && (STM32_Test_Board.ADC_Peripheral.LM35.Counter_Samples < NUMBER_SAMPLES))
	{
		ADC_Peripheral_Select_Sample_LM35();
		STM32_Test_Board.ADC_Peripheral.LM35.Buffer_Samples[STM32_Test_Board.ADC_Peripheral.LM35.Counter_Samples] = STM32_Test_Board.ADC_Peripheral.LM35.Sampled_Value = HAL_ADC_GetValue(&hadc1);
		STM32_Test_Board.ADC_Peripheral.LM35.Counter_Samples++;
		HAL_ADC_Stop(&hadc1);

		ADC_Peripheral_Select_Sample_Potenciometer();
		STM32_Test_Board.ADC_Peripheral.Potenciometer.Buffer_Samples[STM32_Test_Board.ADC_Peripheral.Potenciometer.Counter_Samples] = STM32_Test_Board.ADC_Peripheral.Potenciometer.Sampled_Value = HAL_ADC_GetValue(&hadc1);
		STM32_Test_Board.ADC_Peripheral.Potenciometer.Counter_Samples++;
		HAL_ADC_Stop(&hadc1);
	}
	else
	{
		STM32_Test_Board.ADC_Peripheral.LM35.Counter_Samples = 0;
		STM32_Test_Board.ADC_Peripheral.Potenciometer.Counter_Samples = 0;
	}

	for(STM32_Test_Board.ADC_Peripheral.Counter_Buffer = 0; STM32_Test_Board.ADC_Peripheral.Counter_Buffer < NUMBER_SAMPLES; STM32_Test_Board.ADC_Peripheral.Counter_Buffer++ )
	{
		STM32_Test_Board.ADC_Peripheral.LM35.Somatory_Samples += STM32_Test_Board.ADC_Peripheral.LM35.Buffer_Samples[STM32_Test_Board.ADC_Peripheral.Counter_Buffer];
		STM32_Test_Board.ADC_Peripheral.Potenciometer.Somatory_Samples += STM32_Test_Board.ADC_Peripheral.Potenciometer.Buffer_Samples[STM32_Test_Board.ADC_Peripheral.Counter_Buffer];
	}

	STM32_Test_Board.ADC_Peripheral.LM35.Samples_Average = STM32_Test_Board.ADC_Peripheral.LM35.Somatory_Samples / NUMBER_SAMPLES;
	STM32_Test_Board.ADC_Peripheral.LM35.Somatory_Samples = 0;

	STM32_Test_Board.ADC_Peripheral.Potenciometer.Samples_Average = STM32_Test_Board.ADC_Peripheral.Potenciometer.Somatory_Samples / NUMBER_SAMPLES;
	STM32_Test_Board.ADC_Peripheral.Potenciometer.Somatory_Samples = 0;

	STM32_Test_Board.ADC_Peripheral.LM35.Voltage = (STM32_Test_Board.ADC_Peripheral.LM35.Samples_Average * 3.3) / 4095.0;
	STM32_Test_Board.ADC_Peripheral.Potenciometer.Voltage = (STM32_Test_Board.ADC_Peripheral.Potenciometer.Samples_Average * 3.3) / 4095.0;

	STM32_Test_Board.ADC_Peripheral.LM35.Temperature = (uint8_t)(STM32_Test_Board.ADC_Peripheral.LM35.Voltage * 100);
}

void ADC_Peripheral_Select_Sample_LM35(void)
{
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)**/
	ADC_ChannelConfTypeDef sConfig = {0};

	HAL_ADC_Start(&hadc1);
	HAL_ADC_PollForConversion(&hadc1, 10);

	sConfig.Channel = ADC_CHANNEL_0;
	sConfig.Rank = ADC_REGULAR_RANK_1;
	sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
	  Error_Handler();
	}
}

void ADC_Peripheral_Select_Sample_Potenciometer(void)
{
	/** Configure the global features of the ADC (Clock, Resolution, Data Alignment and number of conversion)**/
	ADC_ChannelConfTypeDef sConfig = {0};

	sConfig.Channel = ADC_CHANNEL_1;
	sConfig.Rank = ADC_REGULAR_RANK_2;
	sConfig.SamplingTime = ADC_SAMPLINGTIME_COMMON_1;
	if (HAL_ADC_ConfigChannel(&hadc1, &sConfig) != HAL_OK)
	{
		Error_Handler();
	}
}

