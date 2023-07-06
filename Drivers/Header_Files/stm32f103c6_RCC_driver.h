/*
 * stm32f103c6_RCC_driver.h
 *
 *  Created on: 4 Feb 2023
 *      Author: Dell
 */

#ifndef INC_STM32F103C6_RCC_DRIVER_H_
#define INC_STM32F103C6_RCC_DRIVER_H_

#include "stm32f103c6.h"
#include "Stm32F103c6_gpio_driver.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
===================global Macros=======================
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
#define HSE_CLK       (uint32_t)16000000
#define HSI_RC_CLK    (uint32_t)8000000


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
===================APIS=======================
*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
uint32_t MCAL_RCC_GetSysCLK(void);

uint32_t MCAL_RCC_GetHCLK(void);

uint32_t MCAL_RCC_GetPCLK1(void);

uint32_t MCAL_RCC_GetPCLK2(void);

#endif /* INC_STM32F103C6_RCC_DRIVER_H_ */
