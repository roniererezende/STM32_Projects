/*
 * mqtt.c
 *
 *  Created on: Oct 23, 2025
 *      Author: Roniere_Rezende
 */

/* INCLUDES */
#include <mte100.h>

/* VARIABLES */
mqtt_client_t *client;
ip_addr_t     mqtt_server_ip;

/* FUNCTIONS */
void mqtt_init(void)
{

}

void mqtt_publish_data(void)
{
	mqtt_create_json_protocol();

	err_t result = mqtt_publish(client, MQTT_TOPIC, mte100.mqtt.payload, strlen((char *)mte100.mqtt.payload), 0, 0, NULL, NULL);

	if(result == ERR_OK)
	{
		printf("MQTT Published: %s\n", mte100.mqtt.payload);
	}
	else
	{
		printf("MQTT Published error (%d)\n", result);
	}
}

void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status)
{
	if(status == MQTT_CONNECT_ACCEPTED)
	{
		printf("Connect to the broker MQTT!\n");
	}
	else
	{
		printf("MQTT connection failure. Code: %d\n", status);
	}
}


void mqtt_create_json_protocol(void)
{
    char motor_ligado[6]   = {};
    char cesto_nivelado[6] = {};
    char sobrecarga[6]     = {};

    float altura  = mte100.data.altura / 1000;
    uint16_t peso = mte100.data.peso;
    float tensao = (float)mte100.data.tensao;
    uint32_t horimetro = mte100.data.horimetro;


    // Motor ligado
    if(payload_id_can_0x100[4] == true)
    {
         strcpy(motor_ligado,"true");
    }
    else
    {
        strcpy(motor_ligado,"false");
    }

    // Cesto Nivelado
    if(payload_id_can_0x100[4] == true)
    {
         strcpy(cesto_nivelado,"true");
    }
    else
    {
        strcpy(cesto_nivelado,"false");
    }

    // Sobrecarga
    if(payload_id_can_0x100[4] == true)
    {
         strcpy(sobrecarga,"true");
    }
    else
    {
        strcpy(sobrecarga,"false");
    }


    sprintf((char *)mte100.mqtt.payload,
        "{"
        "\"altura_m\":%.1f,"
        "\"peso_kg\":%u,"
        "\"tensao_v\":%.1f,"
        "\"horimetro_h\":%lu,"
        "\"motor_ligado\":%s,"
        "\"cesto_nivelado\":%s,"
        "\"sobrecarga\":%s"
        "}",
        altura, peso, tensao, horimetro, motor_ligado, cesto_nivelado, sobrecarga);
}

void mqtt_transmission(void)
{
	MX_LWIP_Process();

	if(mte100.mqtt.transmit == true)
	{
		mqtt_publish_data();
		mte100.mqtt.transmit = false;
	}
}
