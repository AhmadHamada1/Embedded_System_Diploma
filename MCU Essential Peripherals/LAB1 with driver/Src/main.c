/**
 ******************************************************************************
 * @file           : main.c
 * @author         : Auto-generated by STM32CubeIDE
 * @brief          : Main program body
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; Copyright (c) 2022 STMicroelectronics.
 * All rights reserved.</center></h2>
 *
 * This software component is licensed by ST under BSD 3-Clause license,
 * the "License"; You may not use this file except in compliance with the
 * License. You may obtain a copy of the License at:
 *                        opensource.org/licenses/BSD-3-Clause
 *
 ******************************************************************************
 */

#if !defined(__SOFT_FP__) && defined(__ARM_FP)
#warning "FPU is not initialized, but the project is compiling for an FPU. Please initialize the FPU before use."
#endif

#include "STMF103X6.h"
#include "STMF103C6_GPIO_DRIVER.h"

void clock_init(){

	//enable clock for GPIOA
	RCC_GPIOA_CLK_EN();

	//enable clock for GPIOB
	RCC_GPIOB_CLK_EN();
}

void GPIO_init(){
	GPIO_PinConfig_t pincfg;

	//configure PORT A pin 1 as floating input
	pincfg.GPIO_PinNumber = GPIO_PIN_1;
	pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &pincfg);

	//configure PORTB pin 1 as output push pull 10MHz
	pincfg.GPIO_PinNumber = GPIO_PIN_1;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pincfg);

	//configure PORTA pin 13 as floating input
	pincfg.GPIO_PinNumber = GPIO_PIN_13;
	pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
	MCAL_GPIO_Init(GPIOA, &pincfg);

	//configure PORTB pin 1 as output push pull 10MHz
	pincfg.GPIO_PinNumber = GPIO_PIN_13;
	pincfg.GPIO_MODE = GPIO_MODE_OUTPUT_PP;
	pincfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
	MCAL_GPIO_Init(GPIOB, &pincfg);
}

void delay(uint32_t time){
	uint32_t i,j;
	for(i=0;i<=time;i++){
		for(j=0;j<=255;j++);
	}

}


int main(void)
{
	clock_init();

	GPIO_init();

	while(1)
	{
		//check if the button is pressed
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0)
		{
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_1);
			while( MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_1) == 0); //single pressing
		}
		if(MCAL_GPIO_ReadPin(GPIOA, GPIO_PIN_13) == 1)
		{ //multi pressing
			MCAL_GPIO_TogglePin(GPIOB, GPIO_PIN_13);

		}
		delay(1);

	}

}
