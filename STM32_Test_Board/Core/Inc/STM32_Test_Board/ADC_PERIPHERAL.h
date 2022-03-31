/*
 * ADC_PERIPHERAL.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Roniere Rezende
 */

#ifndef INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_
#define INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_

#define NUMBER_MONITORING_CHANNELS	2

typedef struct s_LM35
{
	uint16_t Sampled_Value;
}s_LM35;

typedef struct s_Potenciometer
{
	uint16_t Sampled_Value;
}s_Potenciometer;

typedef struct s_ADC_Peripheral
{
	s_LM35 LM35;
	s_Potenciometer  Potenciometer;

	uint32_t Buffer_ADC_Channels_Monitoring[NUMBER_MONITORING_CHANNELS];
}s_ADC_Peripheral;

void ADC_PERIPHERAL_Init(void);

#endif /* INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_ */
