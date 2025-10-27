/*
 * interrupcao.c
 *
 *  Created on: Oct 23, 2025
 *      Author: Roniere_Rezende
 */
#include <mte100.h>

//uint16_t count_millissecond_tim1 = 0;
//uint16_t count_millissecond_tim3 = 0;
//uint16_t count_second_tim3 = 0;
//uint16_t count_minute_tim3 = 0;

// Função de Callback da Interrupção
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
//	static uint8_t packet_num = 0;
//	static uint8_t led_counter = 0;
//	// Verifica se a interrupção é do TIM1
//	if (htim->Instance == TIM1)
//	{
//		count_millissecond_tim1++;
//
//		if(mte100.led.state ==  led_receive_data_can)
//		{
//			if(count_millissecond_tim1 % 100 == 0)
//			{
//				mte100.led.toggle = true;
//				led_counter++;
//
//			}
//
//			if(led_counter > 1)
//			{
//				mte100.led.state = led_idle;
//				led_counter = 0;
//			}
//		}
//
//		// A cada 2 segundos é habilitado o estado "run" para que se seja realizado a transmissão dos dados via CAN
//		if (count_millissecond_tim1 > 1999)
//		{
//			can_simulation_transmition(packet_num);
//
//			mte100.state = mte100_reception_can;
//			count_millissecond_tim1 = 0;
//
//			if(packet_num)
//			{
//				packet_num = 0;
//			}
//
//		}
//	}
//
//	// Verifica se a interrupção é do TIM1
//	/* Utilizado para controlar o tempo de transmissão do pacote MQTT a cada 5 minutos */
//	if (htim->Instance == TIM3)
//	{
//		count_millissecond_tim3++;
//
//		if(mte100.led.state ==  led_transmit_data_mqtt)
//		{
//			if(count_millissecond_tim3 % 100 == 0)
//			{
//				mte100.led.toggle = true;
//				led_counter++;
//
//			}
//
//			if(led_counter > 3)
//			{
//				mte100.led.state = led_idle;
//				led_counter = 0;
//			}
//		}
//
//		if(count_millissecond_tim3 > 999)
//		{
//			count_second_tim3++;
//			count_millissecond_tim3 = 0;
//
//			if(count_second_tim3 > 59)
//			{
//				count_minute_tim3++;
//
//				if(count_minute_tim3 > 5)
//				{
//					mte100.mqtt.transmit = true;
//					mte100.led.state = led_transmit_data_mqtt;
//				}
//			}
//		}
//	}
}
