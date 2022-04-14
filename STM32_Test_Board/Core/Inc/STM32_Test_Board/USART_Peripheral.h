/*
 * USART_Peripheral.h
 *
 *  Created on: Apr 6, 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_USART_PERIPHERAL_H_
#define INC_STM32_TEST_BOARD_USART_PERIPHERAL_H_

/* Defines */

#define USART_MAXIMUM_NUMBER_BITS_DATA_TRANSMIT	 50
#define USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE	 20
#define USART_TIME_TRANSMIT            5000

/* USART Structure*/
typedef struct s_USART_Peripheral
{
	_Bool Transmit_Enable;
	uint16_t Time_Transmit;

	uint8_t Received_Data_Buffer_Main[USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE];
	//uint8_t Received_Data_Buffer[USART_MAXIMUM_NUMBER_BITS_DATA_RECEIVE];
	uint8_t Index_Received_Data;
}s_USART_Peripheral;

/* Function Prototype */

void USART_Peripheral_Transmit_Data(uint8_t *Transmit_Data);
void USART_Peripheral_Receive_Data(void);
void USART_Peripheral_Transmit_Receive(void);



#endif /* INC_STM32_TEST_BOARD_USART_PERIPHERAL_H_ */
