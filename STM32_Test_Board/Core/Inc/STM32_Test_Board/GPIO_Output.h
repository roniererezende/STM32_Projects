/*
 * GPIO_Output.h
 *
 *  Created on: 16 de mar de 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_GPIO_OUTPUT_H_
#define INC_STM32_TEST_BOARD_GPIO_OUTPUT_H_

#define LED_LIGHT_HIGH_STATE	HAL_GPIO_WritePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin, GPIO_PIN_SET)
#define LED_LIGHT_LOW_STATE		HAL_GPIO_WritePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin, GPIO_PIN_RESET)
#define LED_LIGHT_TOGGLE_STATE  HAL_GPIO_TogglePin(LED_LIGHT_GPIO_Port, LED_LIGHT_Pin)

#define LED_YELLOW_HIGH_STATE	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_SET)
#define LED_YELLOW_LOW_STATE	HAL_GPIO_WritePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin, GPIO_PIN_RESET)
#define LED_YELLOW_TOGGLE_STATE HAL_GPIO_TogglePin(LED_YELLOW_GPIO_Port, LED_YELLOW_Pin)


#define LED_BLUE_A_HIGH_STATE	HAL_GPIO_WritePin(LED_BLUE_A_GPIO_Port, LED_BLUE_A_Pin, GPIO_PIN_SET)
#define LED_BLUE_A_LOW_STATE	HAL_GPIO_WritePin(LED_BLUE_A_GPIO_Port, LED_BLUE_A_Pin, GPIO_PIN_RESET)
#define LED_BLUE_A_TOGGLE_STATE HAL_GPIO_TogglePin(LED_BLUE_A_GPIO_Port, LED_BLUE_A_Pin)

#define LED_BLUE_B_HIGH_STATE	HAL_GPIO_WritePin(LED_BLUE_B_GPIO_Port, LED_BLUE_B_Pin, GPIO_PIN_SET)
#define LED_BLUE_B_LOW_STATE	HAL_GPIO_WritePin(LED_BLUE_B_GPIO_Port, LED_BLUE_B_Pin, GPIO_PIN_RESET)
#define LED_BLUE_B_TOGGLE_STATE HAL_GPIO_TogglePin(LED_BLUE_B_GPIO_Port, LED_BLUE_B_Pin)

#define LED_RED_A_HIGH_STATE	HAL_GPIO_WritePin(LED_RED_A_GPIO_Port, LED_RED_A_Pin, GPIO_PIN_SET)
#define LED_RED_A_LOW_STATE		HAL_GPIO_WritePin(LED_RED_A_GPIO_Port, LED_RED_A_Pin, GPIO_PIN_RESET)
#define LED_RED_A_TOGGLE_STATE  HAL_GPIO_TogglePin(LED_RED_A_GPIO_Port, LED_RED_A_Pin)

#define LED_RED_B_HIGH_STATE	HAL_GPIO_WritePin(LED_RED_B_GPIO_Port, LED_RED_B_Pin, GPIO_PIN_SET)
#define LED_RED_B_LOW_STATE		HAL_GPIO_WritePin(LED_RED_B_GPIO_Port, LED_RED_B_Pin, GPIO_PIN_RESET)
#define LED_RED_B_TOGGLE_STATE  HAL_GPIO_TogglePin(LED_RED_B_GPIO_Port, LED_RED_B_Pin)

#define LED_GREEN_HIGH_STATE	HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_SET)
#define LED_GREEN_LOW_STATE		HAL_GPIO_WritePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin, GPIO_PIN_RESET)
#define LED_GREEN_TOGGLE_STATE  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin)


typedef struct s_GPIO_Output
{

}s_GPIO_Output;

void GPIO_Output_Execution(void);



#endif /* INC_STM32_TEST_BOARD_GPIO_OUTPUT_H_ */
