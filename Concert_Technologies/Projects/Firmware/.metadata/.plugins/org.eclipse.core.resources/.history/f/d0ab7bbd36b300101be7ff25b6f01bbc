/*
 * bsp.c
 *
 *  Created on: Oct 23, 2025
 *      Author: Roniere_Rezende
 */

/* INCLUDES */
#include <mte100.h>

/* VARIABLES */
mte100_s mte100;


/* FUNCTION DECLARATION */
void mte100_init(void)
{

	//Inicializa o protocolo CAN
	can_init();

	mte100.led.state  = led_initialization;


	// Inicializa a variável que habilita a transmissão com "false"
	mte100.mqtt.transmit = false;
}


void mte100_idle_(void)
{

}

void mte100_main(void)
{
	switch (mte100.state)
	{
		case mte100_initialization:
			mte100_init();
			mte100.state = mte100_set_broker_IP;
		break;

		case mte100_set_broker_IP:
			mqtt_init();
			mte100.state = mte100_idle;
		break;

		case mte100_idle:
			mte100_idle_();
		break;

		case mte100_reception_can:
			can_reception();
			mte100.state = mte100_idle;
		break;

		case mte100_transmission_json:
			mqtt_transmission();
			mte100.state = mte100_idle;
		break;
	}

	led_handle();
}

void mte100_error_handler(void)
{
	while(true)
	{
		LED_STATUS_TOGGLE();
		HAL_Delay(100);
	}
}
