/*
 * Screen.h
 *
 *  Created on: Apr 5, 2022
 *      Author: Roniere
 */


#ifndef INC_STM32_TEST_BOARD_SCREEN_H_
#define INC_STM32_TEST_BOARD_SCREEN_H_

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

#define SCREEN_MAXIMUM_BYTE_NUMBER 20


typedef struct s_Screen
{
	uint8_t Index_Buffer_Screen;
	uint8_t Buffer[SCREEN_MAXIMUM_BYTE_NUMBER];
	uint8_t Previous_Buffer[SCREEN_MAXIMUM_BYTE_NUMBER];

}s_Screen;

void Screen_Mount_Temperature(void);
void Screen_Mount_Potenciometer(void);
void Screen_Mount_Serial_Data(void);
void Screen_Mount_PWM(void);

#endif /* INC_STM32_TEST_BOARD_SCREEN_H_ */
