/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
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
/* Includes ------------------------------------------------------------------*/


/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include "../Inc/STM32_Test_Board/STM32_Test_Board.h"

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/

/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
void SystemClock_Config(void);
/* USER CODE BEGIN PFP */

/* USER CODE END PFP */

/* Private user code ---------------------------------------------------------*/
/* USER CODE BEGIN 0 */

void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim->Instance == TIM3) // Timer for General Functions
	{
		if(STM32_Test_Board.Timer_Generico > 0) STM32_Test_Board.Timer_Generico --;
		if(STM32_Test_Board.GPIO_Input.Timers.Generic > 0) STM32_Test_Board.GPIO_Input.Timers.Generic--;
		if(STM32_Test_Board.GPIO_Input.Timers.Timer_Hold_Buttons > 0) STM32_Test_Board.GPIO_Input.Timers.Timer_Hold_Buttons--;
		if(STM32_Test_Board.ADC_Peripheral.Counter_Update > 0) STM32_Test_Board.ADC_Peripheral.Counter_Update--;
		else
		{
			STM32_Test_Board.ADC_Peripheral.Update = true;
			LED_RED_B_TOGGLE_STATE;
		}
		if(STM32_Test_Board.USART_Peripheral.Time_Transmit > 0) STM32_Test_Board.USART_Peripheral.Time_Transmit--;
		else
		{
			STM32_Test_Board.USART_Peripheral.Transmit_Enable = true;
		}
	}

	if(htim->Instance == TIM6) // Timer for General Functions
	{
		LED_GREEN_TOGGLE_STATE;
	}
}

void HAL_GPIO_EXTI_Falling_Callback(uint16_t GPIO_Pin)
{
	if(GPIO_Pin == GPIO_PIN_10)
	{
		LED_RED_A_TOGGLE_STATE;

		if(STM32_Test_Board.Show_Data == e_DAC_Signal)
		{
			STM32_Test_Board.DAC_Signal.Frequency = 4000;
			STM32_Test_Board.DAC_Signal.Update = true;
		}
	}
}

//void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
//{
//	HAL_UART_Receive_IT(&huart2, (uint8_t*)STM32_Test_Board.USART_Peripheral.Received_Data_Buffer_Main, USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE);
//	strcpy((char *)STM32_Test_Board.USART_Peripheral.Received_Data_Buffer, (char *)STM32_Test_Board.USART_Peripheral.Received_Data_Buffer_Main);
//	memset(STM32_Test_Board.USART_Peripheral.Received_Data_Buffer_Main,'\0', USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE);
//}

void HAL_UARTEx_RxEventCallback(UART_HandleTypeDef *huart, uint16_t Size)
{
	if(huart->Instance == USART2)
	{
		memcpy(STM32_Test_Board.USART_Peripheral.Received_Data_Buffer_Main, STM32_Test_Board.Screen.Buffer, USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE);

		HAL_UARTEx_ReceiveToIdle_DMA(&huart2, STM32_Test_Board.Screen.Buffer, USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE);

		__HAL_DMA_DISABLE_IT(&hdma_usart2_rx, DMA_IT_HT);

		STM32_Test_Board.USART_Peripheral.Clear = true;
	}
}

/* USER CODE END 0 */

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void)
{
  /* USER CODE BEGIN 1 */

  /* USER CODE END 1 */

  /* MCU Configuration--------------------------------------------------------*/

  /* Reset of all peripherals, Initializes the Flash interface and the Systick. */
  HAL_Init();

  /* USER CODE BEGIN Init */

  /* USER CODE END Init */

  /* Configure the system clock */
  SystemClock_Config();

  /* USER CODE BEGIN SysInit */

  /* USER CODE END SysInit */

  /* Initialize all configured peripherals */
  MX_GPIO_Init();
  MX_TIM3_Init();
  MX_TIM6_Init();
  MX_TIM7_Init();
  MX_DMA_Init();
  MX_USART2_UART_Init();
  MX_ADC1_Init();
  MX_TIM14_Init();
  MX_DAC1_Init();
  MX_TIM15_Init();
  /* USER CODE BEGIN 2 */

  //ADC_Peripheral_Init();


  /* USER CODE END 2 */

  /* Infinite loop */
  /* USER CODE BEGIN WHILE */
  while (true)
  {
    /* USER CODE END WHILE */

    /* USER CODE BEGIN 3 */
	  STM32_Test_Board_Main();

  }
  /* USER CODE END 3 */
}

/**
  * @brief System Clock Configuration
  * @retval None
  */
void SystemClock_Config(void)
{
  RCC_OscInitTypeDef RCC_OscInitStruct = {0};
  RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};

  /** Configure the main internal regulator output voltage
  */
  HAL_PWREx_ControlVoltageScaling(PWR_REGULATOR_VOLTAGE_SCALE1);
  /** Initializes the RCC Oscillators according to the specified parameters
  * in the RCC_OscInitTypeDef structure.
  */
  RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSI;
  RCC_OscInitStruct.HSIState = RCC_HSI_ON;
  RCC_OscInitStruct.HSIDiv = RCC_HSI_DIV1;
  RCC_OscInitStruct.HSICalibrationValue = RCC_HSICALIBRATION_DEFAULT;
  RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
  RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSI;
  RCC_OscInitStruct.PLL.PLLM = RCC_PLLM_DIV1;
  RCC_OscInitStruct.PLL.PLLN = 9;
  RCC_OscInitStruct.PLL.PLLP = RCC_PLLP_DIV2;
  RCC_OscInitStruct.PLL.PLLQ = RCC_PLLQ_DIV2;
  RCC_OscInitStruct.PLL.PLLR = RCC_PLLR_DIV3;
  if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
  {
    Error_Handler();
  }
  /** Initializes the CPU, AHB and APB buses clocks
  */
  RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK|RCC_CLOCKTYPE_SYSCLK
                              |RCC_CLOCKTYPE_PCLK1;
  RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
  RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV1;
  RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV1;

  if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_1) != HAL_OK)
  {
    Error_Handler();
  }
}

/* USER CODE BEGIN 4 */

/* USER CODE END 4 */

/**
  * @brief  This function is executed in case of error occurrence.
  * @retval None
  */
void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */

