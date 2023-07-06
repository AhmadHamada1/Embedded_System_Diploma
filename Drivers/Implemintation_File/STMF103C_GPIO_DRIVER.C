/*
 * STMF103C_GPIO_DRIVER.C
 *
 *  Created on: Dec 27, 2022
 *      Author: madaa
 */

#include "STMF103C6_GPIO_DRIVER.h"

uint16_t Get_CRLH_position(uint16_t PinNumber){

	switch(PinNumber)
	{
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3  : return 12;
	break;
	case GPIO_PIN_4  : return 16;
	break;
	case GPIO_PIN_5  : return 20;
	break;
	case GPIO_PIN_6  : return 24;
	break;
	case GPIO_PIN_7  : return 28;
	break;
	//position for pins from 8>>>15 in CRH register
	case GPIO_PIN_8  : return 0;
	break;
	case GPIO_PIN_9  : return 4;
	break;
	case GPIO_PIN_10 : return 8;
	break;
	case GPIO_PIN_11 : return 12;
	break;
	case GPIO_PIN_12 : return 16;
	break;
	case GPIO_PIN_13 : return 20;
	break;
	case GPIO_PIN_14 : return 24;
	break;
	case GPIO_PIN_15 : return 28;
	break;
	}

}





/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Reads value of specified PIN.
 * @param [in] 	-GPIOx where x can be (A...E depending on device used) to select GPIO peripheral.
 * @param [in] 	-PIN number : set PIN number according @ref GPIO_PINS_define
 * @retval	 	-input PIN value (two values according @ref GPIO_PIN_stat)
 * Note			-none
 */

void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx,GPIO_PinConfig_t* pinConfig)
{
	volatile uint32_t* configregister = NULL ;
	uint8_t PIN_CONFIG = 0;

	configregister=(pinConfig->GPIO_PinNumber<GPIO_PIN_8>)? (&GPIOx->CRL) : (&GPIOx->CRH);

	//clear CNF0[1:0] MODE0[1:0]
	(*configregister)&=~ (0xF << Get_CRLH_position(pinConfig->GPIO_PinNumber));

	//if pin is output
	if ((pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP) || (pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) || (pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP) || (pinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD))
	{
		//		00: General purpose output push-pull
		//		01: General purpose output Open-drain
		//		10: Alternate function output Push-pull
		//		11: Alternate function output Open-drain
		PIN_CONFIG = ( ((pinConfig->GPIO_MODE - 4) << 2) | ((pinConfig->GPIO_OUTPUT_SPEED) & 0x0F));

	}
	//if pin is input
	else //MODE[1:0]=00:input mode (reset state)
	{
		if ( (pinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO ) || (pinConfig->GPIO_MODE == GPIO_MODE_ANALOG ) )
		{
			pin_config = ( ((pinConfig->GPIO_MODE) <<2) | (0x0 & 0x0F));
		}else if( pinConfig->GPIO_MODE == GPIO_MODE_INPUT_AF)
		{
			pin_config = ( ((GPIO_MODE_INPUT_FLO) <<2) | (0x0 & 0x0F));
		}
		else //pu pd input
		{
			pin_config = ( ((GPIO_MODE_INPUT_PU) <<2) | (0x0 & 0x0F));

			//Table 20. Port bit configuration table
			if(pinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU) //PU
			{
				///set PxODR register to 1 if its input  pull up mode
				GPIOx->ODR |= pinConfig->GPIO_PinNumber;

			}
			else //PD
			{
				//set PxODR register to 0 if its input  pull up mode
				GPIOx->ODR &=~ (pinConfig->GPIO_PinNumber);
			}
		}

	}

	(*configregister) |= ((PIN_CONFIG) <<Get_CRLH_position(pinConfig->GPIO_PinNumber) );

}

/**================================================================
 * @Fn			-MCAL_GPIO_DeInitPin
 * @brief 		-Reset ALL pins
 * @param [in] 	-GPIOx where x can be (A...E depending on device used) to select GPIO peripheral.
 * @retval	 	-none
 * Note			-none
 */
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	// using reset controller
	if(GPIOx==GPIOA){
		RCC->APB2RSTR |= (1<<2);
		RCC->APB2RSTR &= ~(1<<2);
	} else if(GPIOx==GPIOB)
	{
		RCC->APB2RSTR |= (1<<3);
		RCC->APB2RSTR &= ~(1<<3);
	}
	else if(GPIOx == GPIOC)
		{
			RCC->APB2RSTR |= (1<<4);
			RCC->APB2RSTR &= ~(1<<4);

		}
		else if(GPIOx == GPIOD)
		{
			RCC->APB2RSTR |= (1<<5);
			RCC->APB2RSTR &= ~(1<<5);

		}
		else
		{
			RCC->APB2RSTR |= (1<<6);
			RCC->APB2RSTR &= ~(1<<6);

		}

}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPin
 * @brief 		-Read specific pin
 * @param [in] 	-GPIOx where x can be (A...E depending on device used) to select GPIO peripheral.
 * @param [in] 	-PinNumber: set pin Number according @ref GPIO_PINS_define
 * @retval	 	-theinput pin value (two values based on @ref GPIO_PIN_state
 * Note			-none
 */
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
	uint8_t bitstatus;
	if(((GPIOx->IDR)& PinNumber) != (uint32_t)GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_set ;
	}else
	{
		bitstatus = GPIO_PIN_reset ;
	}
return  bitstatus ;

}

/**================================================================
 * @Fn			-MCAL_GPIO_ReadPort
 * @brief 		-Read the input port
 * @param [in] 	-GPIOx where x can be (A...E depending on device used) to select GPIO peripheral.
 * @retval	 	-the input port value
 * Note			-none
 */

uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	unit16_t port_value ;
	port_value = (unit16_t)(GPIOx->IDR);
	return port_value;

}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePin
 * @brief 		-Write value on specified PIN.
 * @param [in] 	-GPIOx where x can be (A...E depending on device used) to select GPIO peripheral.
 * @param [in] 	-PIN number : set PIN number according @ref GPIO_PINS_define
 * @param [in]	-value : PIN value
 * @retval	 	-none
 * Note			-none
 */
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx,uint16_t PinNumber,uint8_t value)
{
	if(value != (uint32_t)GPIO_PIN_RESET)
		{
//		GPIOx->ODR |= PinNumber;
//		OR
		GPIOx->BSRR=PinNumber;
		//		Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		//		These bits are write-only and can be accessed in Word mode only.
		//		0: No action on the corresponding ODRx bit
		//		1: Set the corresponding ODRx bit
		}else
		{
			//			Bits 15:0 BRy: Port x Reset bit y (y= 0 .. 15)
			//			These bits are write-only and can be accessed in Word mode only.
			//			0: No action on the corresponding ODRx bit
			//			1: Reset the corresponding ODRx bit
			GPIOx->BRR=PinNumber;		}

}

/**================================================================
 * @Fn			-MCAL_GPIO_WritePort
 * @brief 		-write value to GPIOx.
 * @param [in] 	-GPIOx where x can be (A...E depending on device used) to select GPIO peripheral.
 * @param [in]	-value : PORT value
 * @retval	 	-none
 * Note			-none
 */
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx,uint16_t value)
{
	GPIOx->ODR = (uint32_t) value;

}

/**================================================================
 * @Fn			-MCAL_GPIO_TogglePin
 * @brief 		-toggle specific PIN.
 * @param [in] 	-GPIOx where x can be (A...E depending on device used) to select GPIO peripheral.
 * @param [in] 	-PIN number : set PIN number according @ref GPIO_PINS_define
 * @retval	 	-none
 * Note			-none
 */
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{

	GPIOx->ODR ^= PinNumber;
}


/**================================================================
 * @Fn			-MCAL_GPIO_LockPin
 * @brief 		-toggle specific PIN.
 * @param [in] 	-GPIOx where x can be (A...E depending on device used) to select GPIO peripheral.
 * @param [in] 	-PIN number : set PIN number according @ref GPIO_PINS_define
 * @retval	 	-enabled if PIN config is locked or error if PIN not locked (enabled or error defined according @ref GPIO_RETURN_LOCK )
 * Note			-none
 */
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx,uint16_t PinNumber)
{
volatile uint32_t tmp;
tmp = (1<<16);
//set lcky
tmp |= PinNumber;
//write 1
GPIOx->LCKR |= tmp;
//write0
GPIOx->LCKR = PinNumber;
//write1
GPIOx->LCKR |= tmp;
//read 0
tmp = (GPIOx->LCKR);
//read1 (this read is optional but confirms that the lock is active)
if((uint32_t)(GPIOx->LCKR & 1<<16)){
		return	GPIO_RETURN_LOCK_ENABLED;
	}
	else{
		return	GPIO_RETURN_LOCK_ERROR;
	}
}


