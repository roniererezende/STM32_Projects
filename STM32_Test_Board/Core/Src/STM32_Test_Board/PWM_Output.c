/*
 * PWM_Output.c
 *
 *  Created on: Apr 19, 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

void PWM_Output_Init(void)
{
	HAL_TIM_PWM_Start(&htim14, TIM_CHANNEL_1); // Starts PWM configured in TIM_14

	STM32_Test_Board.PWM_Output.Value = 50;
	STM32_Test_Board.PWM_Output.Printed_Value = (STM32_Test_Board.PWM_Output.Value * 100  / 1000);
	TIM14->CCR1 = STM32_Test_Board.PWM_Output.Value;
}
