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
#define GPIO_INPUT_DEBOUNCE_AVERAGE_NUMBER              2	  // ms -> Default -> 5
#define GPIO_INPUT_DELAY_AMONG_EACH_SAMPLE              2     // ms -> Default -> 5
#define GPIO_SUCCESS_DEBOUNCE_THRESHOLD                0.75f // percentage of correctness needed, both for pressure and for release
#define GPIO_INPUT_DELAY_AMONG_EACH_PROCESSING_KEY   100     // ms -> Default -> 100
#define GPIO_INPUT_TIME_WAIT_TOUCH_BUTTON          30000     // ms -> Time value to wait pressing any button




///////////////////////////////////////////////////////////////
// VARIABLES
///////////////////////////////////////////////////////////////
typedef enum e_Botao_Estado
{
	E_Button_Start,

	E_Button_Waiting_First_Pressing,
	E_Button_Performing_Debounce_Pressing,

	E_Button_Waiting_First_Releasing,
	E_Button_Performing_Debounce_Releasing
}e_Botao_Estado;

typedef enum e_Botao_Tipo_De_Pull
{
	Button_Pull_No_Initialized,
	Button_Pull_Up,
	Button_Pull_Down
}e_Botao_Tipo_De_Pull;

typedef enum e_Botao_Comportamento
{
	Button_No_Pressed,
	Button_Held,
	Button_Released, // Quando o usuário segurar um botão, ao "liberá-lo", este será o novo estado desta tecla
	Button_Clicked,
}e_Botao_Comportamento;

typedef struct s_Button
{
	GPIO_TypeDef *portX;
	uint16_t pinX;
	e_Botao_Estado State;
	e_Botao_Tipo_De_Pull Pull_Type;

	_Bool Reading_Pressed;	      // This is only to serve in state machine - it isn't the "final" value of pressing
	_Bool Waiting_Perform_Function;

	e_Botao_Comportamento Behavior;

	uint16_t Samples_Counter;
	float Debounce_Average;
	_Bool Should_Ignore_Behavior_Clicked;
}s_Button;

typedef struct s_Botao_Timers
{
	uint32_t Generic;
	uint32_t Timer_Hold_Buttons;
}s_Botao_Timers;

typedef struct s_GPIO_Input
{
	s_Button Button_One;
	s_Button Button_Two;
	s_Button Button_Three;
	s_Button Button_Four;
	s_Button Button_Five;

	s_Botao_Timers Timers;

	_Bool Performing_Debounce_Any_Key;
	_Bool Locked;

	uint8_t Coded_Message;
	uint16_t Counter_Backlight;
}s_GPIO_Input;

void GPIO_Input_Init(void);
void GPIO_Input_Reading_Button(s_Button *Button);
void GPIO_Input_Process(void);
void GPIO_Input_Process_Button(s_Button *Button);
_Bool GPIO_Input_Any_Button_Is_Waiting_perform_Function(void);
void GPIO_Input_Process_Button_One(void);
void GPIO_Input_Process_Button_Two(void);
void GPIO_Input_Process_Button_Three(void);
void GPIO_Input_Process_Button_Four(void);
//void GPIO_Input_Process_Button_Five(void);

void GPIO_Input_Processing_Keyboard(void);

#endif /* INC_STM32_TEST_BOARD_GPIO_INPUT_H_ */
