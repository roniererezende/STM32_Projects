/*
 * mqtt.h
 *
 *  Created on: Oct 23, 2025
 *      Author: Roniere_Rezende
 */

#ifndef INC_MQTT_H_
#define INC_MQTT_H_

/* DEFINES */
// Configurações MQTT
#define MQTT_BROKER_IP   "broker.hivemq.com"
#define MQTT_BROKER_PORT 1883
#define CLIENT_ID        "stm32f767_demo01"
#define MQTT_TOPIC       "telemetria/plataforma/" CLIENT_ID "/dados"

/* STRUCTURES */
typedef struct
{
	bool    transmit;
	uint8_t payload[256];
}mqtt_s;

/* FUNCTION PROTOTYPE */
void mqtt_init(void);
void mqtt_set_broker(void);
void mqtt_transmission(void);

void mqtt_publish_data(void);
void mqtt_connection_cb(mqtt_client_t *client, void *arg, mqtt_connection_status_t status);
void mqtt_create_json_protocol(void);


#endif /* INC_MQTT_H_ */
