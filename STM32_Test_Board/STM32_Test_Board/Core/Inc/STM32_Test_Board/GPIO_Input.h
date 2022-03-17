/*
 * GPIO_Input.h
 *
 *  Created on: 16 de mar de 2022
 *      Author: Roniere
 */

#ifndef INC_STM32_TEST_BOARD_GPIO_INPUT_H_
#define INC_STM32_TEST_BOARD_GPIO_INPUT_H_

///////////////////////////////////////////////////////////////
// DEFINES
///////////////////////////////////////////////////////////////
#define TECLADO_NUMERO_DE_MEDIAS_DO_DEBOUNCE                2	  // ms -> Default -> 5
#define TECLADO_DELAY_ENTRE_CADA_SAMPLE                     2    // ms -> Default -> 5
#define TECLADO_THRESHOLD_DEBOUNCE_SUCESSO                  0.75f // percentage of correctness needed, both for pressure and for release
#define TECLADO_DELAY_ENTRE_CADA_PROCESSAMENTO_DE_TECLA   100     // ms -> Default -> 100
#define TECLADO_TEMPO_ESPERA_TOQUE_BOTAO                30000     // ms -> Time value to wait pressing any button


///////////////////////////////////////////////////////////////
// VARIABLES
///////////////////////////////////////////////////////////////
typedef enum e_Botao_Estado
{
	E_Botao_Inicio,

	E_Botao_Aguardando_Primeiro_Pressionamento,
	E_Botao_Realizando_Debounce_Pressionamento,

	E_Botao_Aguardando_Primeiro_Despressionamento,
	E_Botao_Realizando_Debounce_Despressionamento
}e_Botao_Estado;

typedef enum e_Botao_Tipo_De_Pull
{
	Botao_Pull_Nao_Inicializada,
	Botao_Pull_Up,
	Botao_Pull_Down
}e_Botao_Tipo_De_Pull;

typedef enum e_Botao_Comportamento
{
	Botao_Nao_Pressionado,
	Botao_Segurado,
	Botao_Liberado, // Quando o usuário segurar um botão, ao "liberá-lo", este será o novo estado desta tecla
	Botao_Clicado,
}e_Botao_Comportamento;

typedef struct s_Button
{
	GPIO_TypeDef *portX;
	uint16_t pinX;
	e_Botao_Estado Estado;
	e_Botao_Tipo_De_Pull Tipo_De_Pull;

	_Bool Leitura_Pressionado;	      // This is only to serve in state machine - it isn't the "final" value of pressing
	_Bool Aguardando_Realizar_Funcao;

	e_Botao_Comportamento Comportamento;

	uint16_t Contador_De_Amostras;
	float Media_De_Debounce;
	_Bool Deve_Ignorar_Comportamento_Clicado;
}s_Button;

typedef struct s_Botao_Timers
{
	uint32_t Generico;
	uint32_t Timer_Segurar_Botoes;
}s_Botao_Timers;

typedef struct s_GPIO_Input
{
	s_Button Button_One;
	s_Button Button_Two;

	s_Botao_Timers Timers;

	_Bool Realizando_Debounce_De_Alguma_Tecla;
	_Bool Locked;

	uint8_t Mensagem_Codificada;
	uint16_t Contador_Backlight;
}s_GPIO_Input;

void GPIO_Input_Execution(void);

#endif /* INC_STM32_TEST_BOARD_GPIO_INPUT_H_ */
