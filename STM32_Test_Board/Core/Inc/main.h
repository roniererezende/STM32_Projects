/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32g0xx_hal.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */

/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);

/* USER CODE BEGIN EFP */

/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
#define POT_INPUT_Pin GPIO_PIN_0
#define POT_INPUT_GPIO_Port GPIOA
#define LM35_INPUT_Pin GPIO_PIN_1
#define LM35_INPUT_GPIO_Port GPIOA
#define BUTTON_FIVE_Pin GPIO_PIN_5
#define BUTTON_FIVE_GPIO_Port GPIOC
#define BUTTON_FIVE_EXTI_IRQn EXTI4_15_IRQn
#define BUTTON_ONE_Pin GPIO_PIN_0
#define BUTTON_ONE_GPIO_Port GPIOB
#define BUTTON_TWO_Pin GPIO_PIN_1
#define BUTTON_TWO_GPIO_Port GPIOB
#define BUTTON_THREE_Pin GPIO_PIN_2
#define BUTTON_THREE_GPIO_Port GPIOB
#define BUTTON_FOUR_Pin GPIO_PIN_10
#define BUTTON_FOUR_GPIO_Port GPIOB
#define LED_LIGHT_Pin GPIO_PIN_12
#define LED_LIGHT_GPIO_Port GPIOB
#define LED_YELLOW_Pin GPIO_PIN_13
#define LED_YELLOW_GPIO_Port GPIOB
#define LED_BLUE_A_Pin GPIO_PIN_14
#define LED_BLUE_A_GPIO_Port GPIOB
#define LED_BLUE_B_Pin GPIO_PIN_15
#define LED_BLUE_B_GPIO_Port GPIOB
#define LED_RED_A_Pin GPIO_PIN_8
#define LED_RED_A_GPIO_Port GPIOA
#define LED_RED_B_Pin GPIO_PIN_9
#define LED_RED_B_GPIO_Port GPIOA
#define LED_GREEN_Pin GPIO_PIN_6
#define LED_GREEN_GPIO_Port GPIOC
#define TEST_TIMER_7_Pin GPIO_PIN_8
#define TEST_TIMER_7_GPIO_Port GPIOC
#define DISP_D4_Pin GPIO_PIN_0
#define DISP_D4_GPIO_Port GPIOD
#define DISP_D5_Pin GPIO_PIN_1
#define DISP_D5_GPIO_Port GPIOD
#define DISP_D6_Pin GPIO_PIN_2
#define DISP_D6_GPIO_Port GPIOD
#define DISP_D7_Pin GPIO_PIN_3
#define DISP_D7_GPIO_Port GPIOD
#define DISP_RS_Pin GPIO_PIN_4
#define DISP_RS_GPIO_Port GPIOD
#define DISP_EN_Pin GPIO_PIN_5
#define DISP_EN_GPIO_Port GPIOD
/* USER CODE BEGIN Private defines */

/* USER CODE END Private defines */

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
