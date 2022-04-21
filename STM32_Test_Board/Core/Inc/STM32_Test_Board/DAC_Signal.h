/*
 * DAC_Signal.h
 *
 *  Created on: 20 de abr de 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_DAC_SIGNAL_H_
#define INC_STM32_TEST_BOARD_DAC_SIGNAL_H_

#define    PI 								    3.14159265f
#define    SINE_SAMPLE_AMOUNT   			   50
#define    CENTER_AMPLITUDE_SINUSOID_BITS	 2046

#define    SINE_TIMER_PRESCALER_FREQUENCY 1000000

typedef enum e_Frequency_Option
{
	e_1_KHz = 0,
	e_4_KHz = 1
}e_Frequency_Option;

typedef struct s_DAC_Signal
{
	e_Frequency_Option Selected_Frequency;

	_Bool Update;
	uint32_t Sine[SINE_SAMPLE_AMOUNT];
	uint16_t Frequency;

}s_DAC_Signal;

void DAC_Signal_Init(void);
void DAC_Signal_Sine_Calc(void);
void DAC_Signal_Start(void);
void DAC_Signal_Generation(void);


#endif /* INC_STM32_TEST_BOARD_DAC_SIGNAL_H_ */
