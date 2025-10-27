***********Projeto MTE-100 ************

Este documento tem por fim descrever o funcionamento o firmware e das função incluídas a ele. 

Os arquivos incluídos no projeto são os seguintes:

- mte100.c/.h
- mqtt.c/.h
- led.c/h

**** FUNÇõES ****

--- met100.c/.h ---

mte100_init()               -> Inicializa os estados das máquinas de estado da aplicação e o LED. Inicializa se necessário as variáveis do protocolo CAN. 

mte100_idle_()              -> Não realiza nenhuma rotina aguardanddo a recepção dos dados via protocolo CAN e a transmissão do protocolo JSON via tópico MQTT.

mte100_main()               -> Rotina em que toda aplicação é realizada, recebendo os dados via CAN e transmitindo via MQTT. Também manipula dos LEDs.

mte100_error_handler()      -> Em caso de erro/falha, essa função manipula o LED para pisca a cada 100 ms.

--- mqtt.c/h ---

mqtt_init()			        -> Define o IP do broker e realiza a conexão do cliente ao tópico MQTT.

mqtt_set_broker()           -> Configura o IP do broker.

mqtt_transmission()         -> Realiza a transmissão dos dados via tópico MQTT.

mqtt_publish_data()         -> Responsável por montar o JSON e enviá-lo ao broker MQTT.

mqtt_connection_cb()        -> Chama automaticamente quando o cliente MQTT tanta se conhectar ao broker.

mqtt_create_json_protocol() -> Cria a string de acordo com o protocol JSON.

--- led.c/h ---

led_init()                  -> Inicializa o LED em nível lógico baixo e configura a flag de toggle LED para nível lógico baixo

led_rx_data_can()           -> Realiza o toggle do LED indicando o recepção dos dados via protocolo CAN.

led_tx_transmit_data_mqtt() -> Realiza o toggle do LED indicando o transmissão dos dados via tópico MQTT.

led_handle()                -> Manipula o LED de acordo com o seu estado.

**** DESCRIÇÃO DO FUNCIONAMENTO ****