/*
 * STM32_Test_Board.h
 *
 *  Created on: Mar 14, 2022
 *      Author: Roniere Rezende
 */

#ifndef INC_STM32_TEST_BOARD_STM32_TEST_BOARD_H_
#define INC_STM32_TEST_BOARD_STM32_TEST_BOARD_H_

/* INCLUDES */
#include <stdint.h>
#include <stdbool.h>

#include "main.h"
#include "GPIO_Output.h"
#include "GPIO_Input.h"

/* STM32 Test Board State Machine */
typedef enum E_STM32_Test_Board_States
{
	E_Initialization = 0,
	E_Execution      = 1
}E_STM32_Test_Board_States;

/* Main Project Structure */
typedef struct s_STM32_Test_Board
{
	E_STM32_Test_Board_States States;
	s_GPIO_Output GPIO_Output;
	s_GPIO_Input  GPIO_Input;
}s_STM32_Test_Board;

extern s_STM32_Test_Board STM32_Test_Board;

/* FUNCTION PROTOTYPE */
void STM32_Test_Board_Main(void);

#endif /* INC_STM32_TEST_BOARD_STM32_TEST_BOARD_H_ */
