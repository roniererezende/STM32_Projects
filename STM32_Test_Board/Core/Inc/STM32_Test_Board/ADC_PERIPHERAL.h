/*
 * ADC_PERIPHERAL.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Roniere Rezende
 */

#ifndef INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_
#define INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_

//#include "stm32g0xx_hal_adc.h"


#define NUMBER_MONITORING_CHANNEL    1
#define NUMBER_SAMPLES 		       100
#define TIMER_UPDATE_ADC_VALUE    1000

typedef struct s_ADC
{
	bool Update;
	uint16_t Counter_Update;
	uint32_t Sampled_Value;
	uint32_t Buffer_Samples[NUMBER_SAMPLES];
	uint8_t Counter_Samples;
	uint8_t Counter_Buffer;
	uint64_t Somatory_Samples;

	float Samples_Average;
	float Voltage;
	uint8_t Temperature;
}s_ADC;

typedef struct s_ADC_Peripheral
{
	s_ADC LM35;
	s_ADC  Potenciometer;

	uint16_t ADC_Samples[2];
	uint8_t Counter_Buffer;

}s_ADC_Peripheral;

void ADC_Peripheral_Init(void);
void ADC_Peripheral_LM35_Get_Sample_Temperature(void);
void ADC_Peripheral_Select_Sample_LM35(void);
void ADC_Peripheral_Select_Sample_Potenciometer(void);

#endif /* INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_ */
