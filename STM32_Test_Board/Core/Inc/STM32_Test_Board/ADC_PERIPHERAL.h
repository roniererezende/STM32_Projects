/*
 * ADC_PERIPHERAL.h
 *
 *  Created on: Mar 30, 2022
 *      Author: Roniere Rezende
 */

#ifndef INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_
#define INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_

#define NUMBER_MONITORING_CHANNEL      1
#define NUMBER_SAMPLES 		         100
#define TIMER_UPDATE_TEMPERATURE    1000
#define TIMER_UPDATE_POTENCIOMETER   100

typedef struct s_ADC
{
	uint32_t Sampled_Value;
	uint32_t Buffer_Samples[NUMBER_SAMPLES];
	uint8_t Counter_Samples;
	uint8_t Counter_Buffer;
	uint64_t Somatory_Samples;

	float Samples_Average;
	float Voltage;
}s_ADC;

typedef struct s_ADC_Peripheral
{
	s_ADC LM35;
	s_ADC  Potenciometer;

	bool Update;

	uint8_t Temperature;

	uint16_t ADC_Samples[2];
	uint8_t Counter_Buffer;
	uint16_t Counter_Update;

}s_ADC_Peripheral;

void ADC_Peripheral_Init(void);
void ADC_Peripheral_Get_Samples(void);
void ADC_Peripheral_Select_Sample_LM35(void);
void ADC_Peripheral_Select_Sample_Potenciometer(void);

#endif /* INC_STM32_TEST_BOARD_ADC_PERIPHERAL_H_ */
