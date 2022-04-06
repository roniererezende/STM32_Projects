/*
 * Screen.h
 *
 *  Created on: Apr 5, 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_SCREEN_H_
#define INC_STM32_TEST_BOARD_SCREEN_H_

typedef enum e_Screen
{
	Screen_Temperature   = 0,
	Screen_Potenciometer = 1
}e_Screen;

void Screen_Mount_Temperature(void);
void Screen_Mount_Potenciometer(void);

#endif /* INC_STM32_TEST_BOARD_SCREEN_H_ */
