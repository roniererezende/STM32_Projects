***********Projeto MTE-100 ************

Este documento tem por fim descrever o funcionamento o firmware e das função incluídas a ele. 

Os arquivos incluídos no projeto são os seguintes:

- mte100.c/.h - Rotinas da aplicações do projeto
- mqtt.c/.h   - Rotinas do tópido MQTT
- can.c/.h    - Rotinas referentes ao protocolo CAN. Esta rotina foi criada automaticamente pelo STM32CubeIDE, porém foram adicionadas essas funções ao arquivo.
- led.c/h     - Rotinas de manipulação do led


***************************************************************************************************

**** FUNÇõES ****

--- met100.c/.h ---

mte100_init()                -> Inicializa os estados das máquinas de estado da aplicação e o LED. Inicializa se necessário as variáveis do protocolo CAN. 

mte100_idle_()               -> Não realiza nenhuma rotina aguardanddo a recepção dos dados via protocolo CAN e a transmissão do protocolo JSON via tópico MQTT.

mte100_main()                -> Rotina em que toda aplicação é realizada, recebendo os dados via CAN e transmitindo via MQTT. Também manipula dos LEDs.

mte100_error_handler()       -> Em caso de erro/falha, essa função manipula o LED para pisca a cada 100 ms.


--- mqtt.c/h ---

mqtt_init()			         -> Define o IP do broker e realiza a conexão do cliente ao tópico MQTT.

mqtt_set_broker()            -> Configura o IP do broker.

mqtt_transmission()          -> Realiza a transmissão dos dados via tópico MQTT.

mqtt_publish_data()          -> Responsável por montar o JSON e enviá-lo ao broker MQTT.

mqtt_connection_cb()         -> Chama automaticamente quando o cliente MQTT tanta se conhectar ao broker.

mqtt_create_json_protocol()  -> Cria a string de acordo com o protocol JSON.


--- can.c/h ---

can_init()                   -> Inicializa os parâmetros e variáveis referentes ao protocolo CAN quando houver.

can_reception()              -> Recebe e processa os dados recebidos via protocolo CAN.

can_simulation_transmition() -> Simula a recepção do protocolo CAN selecionando 4 pacotes diferentes disponíveis.

--- led.c/h ---

led_init()                   -> Inicializa o LED em nível lógico baixo e configura a flag de toggle LED para nível lógico baixo.

led_idle_()                  -> Mantém o LED apagado enquanto aguarda o recebimento dos dados da CAN ou transmissão via MQTT.

led_rx_data_can()            -> Realiza o toggle do LED indicando o recepção dos dados via protocolo CAN.

led_tx_transmit_data_mqtt()  -> Realiza o toggle do LED indicando o transmissão dos dados via tópico MQTT.

led_handle()                 -> Manipula o LED de acordo com o seu estado.


***************************************************************************************************

**** DESCRIÇÃO DO FUNCIONAMENTO ****

O firmware do projeto é dividido em 6 estados e são os seguintes:

- Inicialização dos periféricos internos
- Inicialização dos periféricos externos
- Configuração do broker
- Idle
- Recepção CAN
- Transmissão JSON

&&&&& Descrição dos estados &&&&& 

- Inicialização dos periféricos internos

Inicializa todos os periféricos internos com as rotinas geradas pelo próprio do STM32CubeIDE.

- Inicialização dos periféricos externos

Inicializa todos os periféricos externos, como o LAN8742 e o TCAN1042.

- Configuração do broker

Configura o IP do broker e o cliente MQTT.

- Idle

Não realiza nenhuma função, apenas é um estado que se mantém inerte até a recepção dos dados via 
protocolo CAN ou transmissão dos dados via tópico MQTT sejam liberados pelo contador.

- Recepção CAN

A recepção do protocolo CAN é liberada a cada 2s. Como não é possível realizar o teste prático, 
é simulado o recebimento dos dados acessando um buffer que tem disponível 4 pacotes diferentes 
que estão contidos na função "can_simulation_transmition" que é declarada dentro do arquivo can.c. 

- Transmissão JSON

A transmissão do tópico MQTT é liberada a casa 5 minutos.

O controle do tempo é realizado pelo clock do sistema, SysTick. O SysTick possui um interrupção 
a cada 1 ms e chamado pela função SysTick_Handler() que está no arquivo stm32f7xx_it.c na linha 188.


***************************************************************************************************

**** LED STATUS ****

- Recepção dos dados do protocolo can: o LED dá 1 piscada de 100 ms a cada recebimento dos dados.

- Transmissão dos dados via tópico MQTT: O LED dá 2 piscadas de 100 ms a cada transmissão dos dados.

- Indicação de erro: o LED fica piscando a cada 100 ms ininterruptamente.


***************************************************************************************************
**** OBSERVAÇÕES ****
- Por boas práticas de programação, dentro do arquivo main.c não realizadas implementações. É somente 
deixada as implementações realizadas pela própria IDE.

- A aplicação toda é realizada dentro do loop infinito com a chamada na função mte100_main().

- Não foi utilizado o FreeRTOS, porque é uma tecnologia que ainda não domino e não achei prudente tentar fazer por dele e haver algum erro.
  Por barematel, tenho mais segurança em desenvolver o código no momento.
  Porém venho estudando o FreeRTOS, para realizar as implementações multitasks e utilizar as suas demais características.
  
- A configuração dos periférios internos do microcontrolador foram realizadas via configurador do STM32CubeIDE.