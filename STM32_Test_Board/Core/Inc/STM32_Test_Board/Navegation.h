/*
 * Navegation.h
 *
 *  Created on: Apr 5, 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_NAVEGATION_H_
#define INC_STM32_TEST_BOARD_NAVEGATION_H_

typedef struct s_Navegation
{
	e_Screen Current_Screen;
	_Bool Should_Mount_Screen;

}s_Navegation;

void Navegation_Processing(void);

#endif /* INC_STM32_TEST_BOARD_NAVEGATION_H_ */
