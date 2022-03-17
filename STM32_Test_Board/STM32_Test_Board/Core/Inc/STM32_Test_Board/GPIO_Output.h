/*
 * GPIO_Output.h
 *
 *  Created on: 16 de mar de 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_GPIO_OUTPUT_H_
#define INC_STM32_TEST_BOARD_GPIO_OUTPUT_H_

#define LED_RED_HIGH_STATE	    HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_SET)
#define LED_RE_LOW_STATE		HAL_GPIO_WritePin(LED_RED_GPIO_Port, LED_RED_Pin, GPIO_PIN_RESET)
#define LED_RED_TOGGLE_STATE    HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin)

#define LED_LIGHT_HIGH_STATE	HAL_GPIO_WritePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin, GPIO_PIN_SET)
#define LED_LIGHT_LOW_STATE		HAL_GPIO_WritePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin, GPIO_PIN_RESET)
#define LED_LIGHT_TOGGLE_STATE  HAL_GPIO_TogglePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin)


typedef struct s_GPIO_Output
{

}s_GPIO_Output;

void GPIO_Output_Execution(void);



#endif /* INC_STM32_TEST_BOARD_GPIO_OUTPUT_H_ */
