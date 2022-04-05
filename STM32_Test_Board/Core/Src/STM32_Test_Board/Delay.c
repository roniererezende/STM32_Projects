/*
 * Delay.c
 *
 *  Created on: Apr 2, 2022
 *      Author: Roniere
 */

#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

/*
 * Function:  Delay_us(
 * Parameters:
 * Note:
 *
 */
void Delay_us(uint16_t Time_us)
{
	htim7.Instance->CNT = 0;
    while (htim7.Instance->CNT < Time_us);
}

/*
 * Function:
 * Parameters:
 * Note:
 *
 */
void Delay_ms(uint16_t Time_ms)
{
    while(Time_ms > 0)
    {
    	htim7.Instance->CNT = 0;
		Time_ms--;
		while (htim7.Instance->CNT < 1000);
    }
}
