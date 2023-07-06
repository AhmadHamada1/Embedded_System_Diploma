/*
 * STMF103C_GPIO_DRIVER.h
 *
 *  Created on: Dec 27, 2022
 *      Author: madaa
 */

#ifndef INC_STMF103C6_GPIO_DRIVER_H_
#define INC_STMF103C6_GPIO_DRIVER_H_



//-----------------------------
//Includes
//----------------------------
#include "STMF103X6.h"


//-----------------------------
//User type definitions (structures)
//-----------------------------
typedef struct{
	volatile uint16_t GPIO_PinNumber ; //Specifies the pin number to be configured
	//this parameter can be value of @ref GPIO_PINS_define

	volatile uint8_t GPIO_MODE    ;  //Specifies the configuration for the selected pin
	//this parameter can be value of @ref GPIO_MODE_define

	volatile uint8_t GPIO_OUTPUT_SPEED;		 //Specifies the speed for the selected pin
	//this parameter can be value of @ref GPIO_SPEED_define

}GPIO_PinConfig_t;

//@ref GPIO_PIN_state
#define GPIO_PIN_set 		1
#define GPIO_PIN_reset 		0


//@ref GPIO_RETURN_LOCK
#define GPIO_RETURN_LOCK_ENABLED   		1
#define GPIO_RETURN_LOCK_ERROR 			0
//-----------------------------
//Macros Configuration References
//-----------------------------
//@ref GPIO_PINS_define
#define GPIO_PIN_0			((uint16_t) 0x0001)  // PIN0 selected
#define GPIO_PIN_1			((uint16_t) 0x0002)  // PIN1 selected
#define GPIO_PIN_2			((uint16_t) 0x0004)  // PIN2 selected
#define GPIO_PIN_3			((uint16_t) 0x0008)  // PIN3 selected
#define GPIO_PIN_4			((uint16_t) 0x0010)  // PIN4 selected
#define GPIO_PIN_5			((uint16_t) 0x0020)  // PIN5 selected
#define GPIO_PIN_6			((uint16_t) 0x0040)  // PIN6 selected
#define GPIO_PIN_7			((uint16_t) 0x0080)  // PIN7 selected
#define GPIO_PIN_8			((uint16_t) 0x0100)  // PIN8 selected
#define GPIO_PIN_9			((uint16_t) 0x0200)  // PIN9 selected
#define GPIO_PIN_10			((uint16_t) 0x0400)  // PIN10 selected
#define GPIO_PIN_11			((uint16_t) 0x0800)  // PIN11 selected
#define GPIO_PIN_12			((uint16_t) 0x1000)  // PIN12 selected
#define GPIO_PIN_13			((uint16_t) 0x2000)  // PIN13 selected
#define GPIO_PIN_14			((uint16_t) 0x4000)  // PIN14 selected
#define GPIO_PIN_15			((uint16_t) 0x8000)  // PIN15 selected
#define GPIO_PIN_ALL		((uint16_t) 0xFFFF)  // ALL pins selected

#define GPIO_PIN_MASK		(0x0000FFFFu)  // pin mask



//@ref GPIO_MODE_define

//0: Analog mode
//1: Floating input (reset state)
//2: Input with pull-up
//3: Input with pull-down
//4: General purpose output push-pull
//5: General purpose output Open-drain
//6: Alternate function output Push-pull
//7: Alternate function output Open-drain
//8: Alternate function input

#define GPIO_MODE_ANALOG      		( 0x00000000u) 		// Analog mode
#define GPIO_MODE_INPUT_FLO     	( 0x00000001u)		// Floating mode
#define GPIO_MODE_INPUT_PU	      	( 0x00000002u)		// Input with pull up mode
#define GPIO_MODE_INPUT_PD	      	( 0x00000003u)		// Input with pull down mode
#define GPIO_MODE_OUTPUT_PP      	( 0x00000004u)		// Output Push-Pull mode
#define GPIO_MODE_OUTPUT_OD      	( 0x00000005u)		// Output Open-Drain mode
#define GPIO_MODE_OUTPUT_AF_PP      ( 0x00000006u)		// Alternate function output Push-pull
#define GPIO_MODE_OUTPUT_AF_OD      ( 0x00000007u)		// Alternate function output Open-Drain
#define GPIO_MODE_INPUT_AF      	( 0x00000008u)		// Alternate function input


//@ref GPIO_SPEED_define

//1: Output mode, max speed 10 MHz.
//1: Output mode, max speed 2 MHz.
//3: Output mode, max speed 50 MHz.
#define GPIO_SPEED_10M				(0x00000001u)  		// Output mode, max speed 10 MHz
#define GPIO_SPEED_2M				(0x00000002u)  		// Output mode, max speed 2 MHz.
#define GPIO_SPEED_50M				(0x00000003u)  		// Output mode, max speed 50 MHz



/*@ref Module_REF_NAME_define
 */
/*
 * ===============================================
 * APIs Supported by "MCAL GPIO DRIVER"
 * ===============================================
 */
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t* pinConfig);
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx);

uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber);
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx);

void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx,uint16_t PinNumber,uint8_t value);
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx,uint16_t value);

void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint16_t PinNumber);

uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber);





#endif /* INC_STMF103C6_GPIO_DRIVER_H_ */
