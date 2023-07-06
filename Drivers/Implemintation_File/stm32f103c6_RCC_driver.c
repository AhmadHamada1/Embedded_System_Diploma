/*
 * stm32f103c6_RCC_driver.c
 *
 *  Created on: FEB 4, 2023
 *      Author: Ahmed ELgazzar
 */
#include"stm32f103c6_RCC_driver.h"


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
 ==============global variables=============
 *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/


/*
 * Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
   Set and cleared by software to control the division factor of the APB High speed clock (PCLK2).
   0xx: HCLK not divided
   100: HCLK divided by 2
   101: HCLK divided by 4
   110: HCLK divided by 8
   111: HCLK divided by 16
 */
const uint8_t APBpres_table[] = {0,0,0,0,1,2,3,4};// shift right 1 == "/ 2^num"

/*
 *Bits 7:4 HPRE[3:0]: AHB prescaler
  Set and cleared by software to control AHB clock division factor.
  0xxx: SYSCLK not divided
  1000: SYSCLK divided by 2
  1001: SYSCLK divided by 4
  1010: SYSCLK divided by 8
  1011: SYSCLK divided by 16
  1100: SYSCLK divided by 64
  1101: SYSCLK divided by 128
  1110: SYSCLK divided by 256
  1111: SYSCLK divided by 512
 */
const uint8_t AHBpres_table[] = {0,0,0,0,0,0,0,0,1,2,3,4,5,6,7,8,9};// shift right 1 == "/ 2^num"


/**================================================================
 * @Fn				-MCAL_RCC_GetSysCLK
 * @brief 			-it is function to get the value of system clock to pass it to MCAL_RCC_GetHCLK...
 * @parameter[in]	- NONE
 * @return			-value of system clock..
 * Note				-None
 */
uint32_t MCAL_RCC_GetSysCLK(void)
{
	/*
	 * Bits 3:2 SWS[1:0]: System clock switch status
	   Set and cleared by hardware to indicate which clock source is used as system clock.
	   00: HSI oscillator used as system clock
	   01: HSE oscillator used as system clock
	   10: PLL used as system clock
       11:    Not applicable
	 */
	switch((RCC->CFGR >> 2) & 0b11)
	{
	case 0:
		return HSI_RC_CLK;
		break;
	case 1: // to do it you need to calculate ( HSI user should specify it)
		return HSE_CLK;
		break;
	case 2:// to do it you need to calculate ( PLLCLK & PLLMUL & PLL SOURCE MUX)
		return 16000000;
		break;
	}

	return 0;
}

/**================================================================
 * @Fn				-MCAL_RCC_GetHCLK
 * @brief 			-it is function to get the value of H clock to MCAL_RCC_GetPCLK1 or MCAL_RCC_GetPCLK2...
 * @parameter[in]	- NONE
 * @return			-value of H clock..
 * Note				-None
 */
uint32_t MCAL_RCC_GetHCLK(void)
{
	return (MCAL_RCC_GetHCLK() >> APBpres_table[ ((RCC->CFGR >> 4) & 0x0F) ] );
}

/**================================================================
 * @Fn				-MCAL_RCC_GetPCLK1
 * @brief 			-it is function to get the value of P clock1 to use it in BaudRate in USART 2,3...
 * @parameter[in]	- NONE
 * @return			-value of P clock1 clock..
 * Note				-None
 */
uint32_t MCAL_RCC_GetPCLK1(void)
{

	// Bits 10:8 PPRE1[2:0]: APB Low-speed prescaler (APB1)
	return (MCAL_RCC_GetHCLK() >> APBpres_table[ ((RCC->CFGR >> 8) & 0b111) ] );
}

/**================================================================
 * @Fn				-MCAL_RCC_GetPCLK2
 * @brief 			-it is function to get the value of P clock2 to use it in BaudRate in USART1...
 * @parameter[in]	- NONE
 * @return			-value of P clock2 clock..
 * Note				-None
 */
uint32_t MCAL_RCC_GetPCLK2(void)
{
	// Bits 13:11 PPRE2[2:0]: APB high-speed prescaler (APB2)
	return (MCAL_RCC_GetHCLK() >> APBpres_table[ ((RCC->CFGR >> 11) & 0b111) ] );
}


/*
 * ======================================================================
 *                   End of RCC  driver.c
 *======================================================================
 */
