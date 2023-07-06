/*
 * stm32f103c6_gpio_driver.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Ahmed ELgazzar
 */
#include"stm32f103c6_EXTI_driver.h"

/*
 * ======================================================================
 *                                          Generic variables
 *======================================================================
 */
void(* GP_IRQ_Callback[15])(void) ;

/*
 * ======================================================================
 *                                          Generic Macros
 *======================================================================
 */

#define AFIO_GPIO_EXTI_Mapping(x)        (  (x==GPIOA)?0:\
											(x==GPIOB)?1:\
											(x==GPIOC)?2:\
											(x==GPIOD)?3:0    )

/*
 * ======================================================================
 *                                          Generic Functions
 *======================================================================
 */

void Enable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Enable ;
		break ;
	case 1:
		NVIC_IRQ7_EXTI1_Enable ;
		break ;
	case 2:
		NVIC_IRQ8_EXTI2_Enable ;
		break ;
	case 3:
		NVIC_IRQ9_EXTI3_Enable ;
		break ;
	case 4:
		NVIC_IRQ10_EXTI4_Enable ;
		break ;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Enable ;
		break ;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Enable ;
		break ;
	}
}


void Disable_NVIC (uint16_t IRQ)
{
	switch(IRQ)
	{
	case 0:
		NVIC_IRQ6_EXTI0_Disable ;
		break ;
	case 1:
		NVIC_IRQ7_EXTI1_Disable ;
		break ;
	case 2:
		NVIC_IRQ8_EXTI2_Disable ;
		break ;
	case 3:
		NVIC_IRQ9_EXTI3_Disable ;
		break ;
	case 4:
		NVIC_IRQ10_EXTI4_Disable ;
		break ;
	case 5:
	case 6:
	case 7:
	case 8:
	case 9:
		NVIC_IRQ23_EXTI5_9_Disable ;
		break ;
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15:
		NVIC_IRQ40_EXTI10_15_Disable ;
		break ;
	}
}


void Update_EXTI(EXTI_Pinconfig_t* EXTI_Config)
{
	//1- configure GPIO to be AF input >> Floating input
	Pin_config_t pinCfg;
	pinCfg.GPIO_PinNumber = EXTI_Config->EXTI_PIN.GPIO_Pin;
	pinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLOAT ;
	MCAL_GPIO_INIT(EXTI_Config->EXTI_PIN.GPIO_Port , &pinCfg);

	//========================================================
	//2-update AFIO to route between EXTI line with port A,B,C,D
	uint8_t AFIO_EXTICR_index = EXTI_Config->EXTI_PIN.EXT_InputLineNumber / 4 ;
	uint8_t AFIO_EXTICR_position = (EXTI_Config->EXTI_PIN.EXT_InputLineNumber % 4) * 4  ;
	//clear the four bit
	AFIO->EXTICR[AFIO_EXTICR_index] &= (0xF <<AFIO_EXTICR_position);
	AFIO->EXTICR[AFIO_EXTICR_index] |= ((AFIO_GPIO_EXTI_Mapping(EXTI_Config->EXTI_PIN.GPIO_Port) & 0xF) << AFIO_EXTICR_position );

	//=================================================================
	//3- update Rising and Falling edge
	//clear the corresponding bit
	EXTI->RTSR &= ~ (1<< EXTI_Config->EXTI_PIN.EXT_InputLineNumber) ;
	EXTI->FTSR &= ~ (1<< EXTI_Config->EXTI_PIN.EXT_InputLineNumber) ;

	if(EXTI_Config->Trigger_Case == EXTI_Trigger_RISING)
	{
		EXTI->RTSR |= (1<< EXTI_Config->EXTI_PIN.EXT_InputLineNumber) ;

	}else if (EXTI_Config->Trigger_Case == EXTI_Trigger_FALLING)
	{
		EXTI->FTSR |=  (1<< EXTI_Config->EXTI_PIN.EXT_InputLineNumber) ;
	}
	else if (EXTI_Config->Trigger_Case == EXTI_Trigger_RisingAndFalling)
	{
		EXTI->RTSR |=  (1<< EXTI_Config->EXTI_PIN.EXT_InputLineNumber) ;
		EXTI->FTSR |=  (1<< EXTI_Config->EXTI_PIN.EXT_InputLineNumber) ;
	}
	//==========================================================================
	//4-update IRQ Handling Callback
	GP_IRQ_Callback[EXTI_Config->EXTI_PIN.EXT_InputLineNumber] = EXTI_Config->P_IRQ_Callback ;


	//=======================================================================
	//5-Enable/Disable IRQ EXTI &NVIC
	if(EXTI_Config->IRQ_EN == EXTI_IRQ_Enable)
	{
		EXTI->IMR |= (1<<EXTI_Config->EXTI_PIN.EXT_InputLineNumber);
		Enable_NVIC(EXTI_Config->EXTI_PIN.EXT_InputLineNumber);
	}
	else
	{
		EXTI->IMR &= ~(1<<EXTI_Config->EXTI_PIN.EXT_InputLineNumber);
		Disable_NVIC(EXTI_Config->EXTI_PIN.EXT_InputLineNumber);
	}
}


/*
 * ====================================================================================================
 *                          APIs Functions Definations
 * ====================================================================================================
 */


/**================================================================
 * @Fn               -MCAL_EXTI_GPIO_DeINIT
 * @brief            -Reset EXTI Registers and NVIC Corresponding IRQ Mask
 * @retval           -none
 * Note              -none
 */
void MCAL_EXTI_DeINIT(void)
{

	EXTI->IMR = 0x00000000 ;
	EXTI->EMR = 0x00000000 ;
	EXTI->RTSR = 0x00000000 ;
	EXTI->FTSR = 0x00000000 ;
	EXTI->SWIER  = 0x00000000 ;
	EXTI->PR = 0xFFFFFFFF ; //rc-w1
	//Disable EXTI IRQ from NVIC
	NVIC_IRQ6_EXTI0_Disable ;
	NVIC_IRQ7_EXTI1_Disable ;
	NVIC_IRQ8_EXTI2_Disable ;
	NVIC_IRQ9_EXTI3_Disable ;
	NVIC_IRQ10_EXTI4_Disable ;
	NVIC_IRQ23_EXTI5_9_Disable ;
	NVIC_IRQ40_EXTI10_15_Disable ;
}


/**================================================================
 * @Fn               -MCAL_EXTI_GPIO_INIT
 * @brief            -Initialize EXTI from specific GPIO PIN and specify MASK/trigger condition and IRQ Callback
 *param[in]           -EXTI config set by @ref EXTI_define ,@ref EXTI_Trigger_define and @ref EXTI_IRQ_define
 * @retval           -none
 * Note              -it is Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO
 */

void MCAL_EXTI_INIT(EXTI_Pinconfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);
}


/**================================================================
 * @Fn               -MCAL_EXTI_GPIO_Update
 * @brief            -Initialize EXTI from specific GPIO PIN and specify MASK/trigger condition and IRQ Callback
 *param[in]           -EXTI config set by @ref EXTI_define ,@ref EXTI_Trigger_define and @ref EXTI_IRQ_define
 * @retval           -none
 * Note              -it is Mandatory to Enable RCC Clock for AFIO and the corresponding GPIO
 */

void MCAL_EXTI_Update(EXTI_Pinconfig_t* EXTI_Config)
{
	Update_EXTI(EXTI_Config);

}


////**==========================================================================
////**==========================================================================
////**=====================     ISR FUNCTIONS      =============================
////**==========================================================================
////**==========================================================================

void EXTI0_IRQHandler(void)
{
	//Clear pending register by writing 1
	EXTI->PR |= 1<< 0 ;
	//Call IRQ Callback
	GP_IRQ_Callback[0]();
}


void EXTI1_IRQHandler(void)
{
	//Clear pending register by writing 1
	EXTI->PR |= 1<< 1 ;
	//Call IRQ Callback
	GP_IRQ_Callback[1]();
}


void EXTI2_IRQHandler(void)
{
	//Clear pending register by writing 1
	EXTI->PR |= 1<< 2 ;
	//Call IRQ Callback
	GP_IRQ_Callback[2]();
}


void EXTI3_IRQHandler(void)
{
	//Clear pending register by writing 1
	EXTI->PR |= 1<< 3 ;
	//Call IRQ Callback
	GP_IRQ_Callback[3]();
}


void EXTI4_IRQHandler(void)
{
	//Clear pending register by writing 1
	EXTI->PR |= 1<< 4 ;
	//Call IRQ Callback
	GP_IRQ_Callback[4]();
}


void EXTI9_5_IRQHandler(void)
{
	if(EXTI->PR & 1<<5) { EXTI->PR |= 1<< 5 ; GP_IRQ_Callback[5](); }
	if(EXTI->PR & 1<<6) { EXTI->PR |= 1<< 6 ; GP_IRQ_Callback[6](); }
	if(EXTI->PR & 1<<7) { EXTI->PR |= 1<< 7 ; GP_IRQ_Callback[7](); }
	if(EXTI->PR & 1<<8) { EXTI->PR |= 1<< 8 ; GP_IRQ_Callback[8](); }
	if(EXTI->PR & 1<<9) { EXTI->PR |= 1<< 9 ; GP_IRQ_Callback[9](); }
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI->PR & 1<<10) { EXTI->PR |= 1<< 10 ; GP_IRQ_Callback[10](); }
	if(EXTI->PR & 1<<11) { EXTI->PR |= 1<< 11 ; GP_IRQ_Callback[11](); }
	if(EXTI->PR & 1<<12) { EXTI->PR |= 1<< 12 ; GP_IRQ_Callback[12](); }
	if(EXTI->PR & 1<<13) { EXTI->PR |= 1<< 13 ; GP_IRQ_Callback[13](); }
	if(EXTI->PR & 1<<14) { EXTI->PR |= 1<< 12 ; GP_IRQ_Callback[14](); }
	if(EXTI->PR & 1<<15) { EXTI->PR |= 1<< 13 ; GP_IRQ_Callback[15](); }
}

/*
 * ======================================================================
 *                   End of EXTI  driver.c
 *======================================================================
 */






