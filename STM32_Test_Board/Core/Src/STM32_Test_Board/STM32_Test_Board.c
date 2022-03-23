/*
 * STM32_Test_Board.c
 *
 *  Created on: Mar 14, 2022
 *      Author: Roniere Rezende
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

/* Structure Declaration */
s_STM32_Test_Board STM32_Test_Board;

/* Main Project Routine */
void STM32_Test_Board_Main(void)
{
	switch (STM32_Test_Board.States)
	{
		// Initializes all peripheral here
		case E_Initialization:
			HAL_TIM_Base_Start_IT(&htim3); // Starts timer for General Functions
			STM32_Test_Board.States = E_Execution;
		break;

		// Performs all routines here
		case E_Execution:
			GPIO_Input_Process();
		break;
	}
}
