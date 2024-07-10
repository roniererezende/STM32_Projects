#include "stm32f411xe.h"
#include <stdbool.h>
#include <stdint.h>

void DelaySys_ms(uint32_t Time);

int main(void)
{
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN; 	  // Enable PORTB clock
	GPIOA->MODER |= GPIO_MODER_MODER5_0; 	  // Set PB0 as output
	GPIOA->OTYPER &= ~GPIO_OTYPER_OT_0;  	  // Set push-pull
	GPIOA->OSPEEDR |= GPIO_OSPEEDER_OSPEEDR0; // Set high speed

	while(true)
	{
		DelaySys_ms(100);

		GPIOA->BSRR |= GPIO_BSRR_BS5; // High level in PORTA_5

		DelaySys_ms(100);

		GPIOA->BSRR |= GPIO_BSRR_BR5; // Low level in PORTA_5
	}
}

void DelaySys_ms(uint32_t Time)
{
	SysTick->LOAD  = Time * 1000;
	SysTick->VAL   = 0;
	SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

	while(!(SysTick->CTRL & SysTick_CTRL_COUNTFLAG_Msk));
	SysTick->CTRL = 0;
}
