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
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <STM32_Test_Board/ADC_Peripheral.h>

#include "main.h"
#include "stm32g071xx.h"
#include "adc.h"
#include "stm32g0xx_hal_adc.h"
//#include "dma.h"
#include "tim.h"
#include "gpio.h"
#include "stm32g0xx_it.h"

#include "GPIO_Output.h"
#include "GPIO_Input.h"
#include "Display_16x2.h"
#include "Delay.h"
#include "Screen.h"
#include "Navegation.h"

/* STM32 Test Board State Machine */
typedef enum E_STM32_Test_Board_States
{
	E_Initialization = 0,
	E_Execution      = 1
}E_STM32_Test_Board_States;

typedef enum e_STM32_Test_Board_Show_Data
{
	e_Temperature   = 0,
	e_Potenciometer = 1
}e_STM32_Test_Board_Show_Data;

/* Main Project Structure */
typedef struct s_STM32_Test_Board
{
	E_STM32_Test_Board_States States;
	e_STM32_Test_Board_Show_Data Show_Data;

	s_GPIO_Output GPIO_Output;
	s_GPIO_Input  GPIO_Input;
	s_ADC_Peripheral ADC_Peripheral;
	s_Display_16x2 Display_16x2;
	s_Navegation Navegation;

	uint16_t Timer_Generico;
}s_STM32_Test_Board;

extern s_STM32_Test_Board STM32_Test_Board;

/* FUNCTION PROTOTYPE */
void STM32_Test_Board_Main(void);
void STM32_Test_Board_Initialization(void);
void STM32_Test_Board_Execution(void);
void STM32_Test_Board_Update_Data(void);

#endif /* INC_STM32_TEST_BOARD_STM32_TEST_BOARD_H_ */
