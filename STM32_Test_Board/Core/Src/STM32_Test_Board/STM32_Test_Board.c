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
		case E_Initialization:
			// Initializes all peripheral here
			STM32_Test_Board.States = E_Execution;
		break;

		case E_Execution:
			// Performs all routines here
		break;
	}
}
