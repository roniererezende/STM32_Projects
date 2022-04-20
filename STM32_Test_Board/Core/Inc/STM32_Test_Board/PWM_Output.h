/*
 * PWM_Output.h
 *
 *  Created on: Apr 19, 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_PWM_OUTPUT_H_
#define INC_STM32_TEST_BOARD_PWM_OUTPUT_H_

typedef struct s_PWM_Output
{
	uint16_t Value;
	uint16_t Printed_Value;
	_Bool Update;
}s_PWM_output;

void PWM_Output_Init(void);


#endif /* INC_STM32_TEST_BOARD_PWM_OUTPUT_H_ */
