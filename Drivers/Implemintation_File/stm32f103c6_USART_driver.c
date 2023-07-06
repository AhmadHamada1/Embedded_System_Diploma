/*
 * stm32f103c6_USART_driver.c
 *
 *  Created on: 4 FEB, 2023
 *      Author: Ahmed ELgazzar
 */
#include"stm32f103c6_USART_driver.h"

/*
 * ======================================================================
 *                   global variable
 *======================================================================
 */

UART_config* global_UART_config = NULL;

/*
 * ======================================================================
 *                  	APIS implemintation
 *======================================================================
 */

/**================================================================
 * @Fn               -MCAL_UART_init
 * @brief            -Initialize UART (Asynchronous Only)
 *param[in]          -UARTx :where x can be 1,2,3 depending on device used
 *param[in]          -UART config :all the uart configuration
 * @retval           -none
 * Note              -support for now ASynch mode and clock 8 HZ
 */
void MCAL_UART_init(UART_t* UARTx,UART_config* UART_cfg)
{
	global_UART_config = UART_cfg;
	uint32_t BRR,PCLK;

	//enable the clock for given USART Peripheral

	if(UARTx == UART1)
	{
		UART1_CLK_EN();
	}
	else if (UARTx == UART2)
	{
		UART2_CLK_EN();
	}
	else if (UARTx == UART3)
	{
		UART3_CLK_EN();
	}

	//config parameters

	//enable UART Module
	UARTx->CR1 |= (1<<13) ; //Bit 13 UE: USART enable

	//enable Mode TX RX
	UARTx->CR1 |= UART_cfg->UART_Mode ;///Bit 3 TE: Transmitter enable | Bit 2 RE: Receiver enable

	// enable Payload width
	UARTx->CR1 |= UART_cfg->Payload_Lentgh ;///Bit 12 M: Word length This bit

	//Configure parity bits
	UARTx->CR1 |= UART_cfg->parity ;//Bit 10 PCE: Parity control enable & Bit 9 PS: Parity selection

	//configure stop bits
	UARTx->CR2 |= UART_cfg->StopBit; //(Bits 13:12 STOP: STOP bits)

	//flow control
	UARTx->CR3 |= UART_cfg->HWFlowcontrol ;////Bit 9 CTSE: CTS enable | Bit 8 RTSE: RTS enable

	//Configure baud rate
	//PCLK2 For USART1
	//PCLK1 for USART2 ,3

	if(UARTx == UART1)
	{
		PCLK = MCAL_RCC_GetPCLK2();
	}
	else//USARTx == USART 2,3
	{
		PCLK = MCAL_RCC_GetPCLK1();
	}
	BRR = UART_BRR_Register(PCLK,UART_cfg->BaudRate);
	UARTx->BRR = BRR;

	//Enable UART (if Enabled)

	if(UART_cfg->IRQ_Enable != UART_IRQ_Enable_NONE)
	{
		UARTx->CR1 |= UART_cfg->IRQ_Enable;

		if(UARTx == UART1)
		{
			NVIC_UART1_IRQ37_Enable;
		}
		else if(UARTx == UART2)
		{
			NVIC_UART2_IRQ38_Enable;
		}
		else if(UARTx == UART3)
		{
			NVIC_UART3_IRQ39_Enable;
		}
	}
}

/**================================================================
 * @Fn               -MCAL_UART_Deinit
 * @brief            -DeInitialize UART (Asynchronous Only)
 *param[in]          -UARTx :where x can be 1,2,3 depending on device used
 * @retval           -none
 * Note              -Reset the model by RCC
 */
void MCAL_UART_Deinit(UART_t* UARTx)
{
	//Reset RCC Clock

	if(UARTx == UART1)
	{
		UART1_CLK_RESET();
	}
	else if(UARTx == UART2)
	{
		UART2_CLK_RESET();
	}
	else if(UARTx == UART3)
	{
		UART3_CLK_RESET();
	}

	//Reset NVIC

	if(UARTx == UART1)
	{
		NVIC_UART1_IRQ37_Disable;
	}
	else if(UARTx == UART2)
	{
		NVIC_UART2_IRQ38_Disable;
	}
	else if(UARTx == UART3)
	{
		NVIC_UART3_IRQ39_Disable;
	}

}

/**================================================================
 * @Fn               - MCAL_UART_set_GPIO_pen
 * @brief            -set the Gpio pins
 *param[in]          -USARTx :where x can be 1,2,3 depending on device used
 * @retval           -none
 * Note              -should enable the corresponding ALT &GPIO in RCC CLOCK AND called after MCAL_UART_init()
 */
void MCAL_UART_set_GPIO_pin(UART_t* UARTx)
{
	Pin_config_t pincfg;

	if(UARTx == UART1)
	{
		//from alternative pin table for LQF and see recommended gpio pins configuration table
		//PA9 TX
		//PA10 RX
		//PA11 CTS
		//PA12 RTS

		//PA9 TX
		pincfg.GPIO_PinNumber = GPIO_PIN9 ;
		pincfg.GPIO_MODE = GPIO_MODE_AF_PP;
		pincfg.GPIO_OUTPUT_speed = GPIO_SPEED_10M;
		MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		//PA10 RX
		pincfg.GPIO_PinNumber = GPIO_PIN10 ;
		pincfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		//PA11 CTS
		if(global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS || global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS_RTS)
		{
			pincfg.GPIO_PinNumber = GPIO_PIN11 ;
			pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		}

		//PA12 RTS
		if(global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_RTS || global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS_RTS)
		{
			pincfg.GPIO_PinNumber = GPIO_PIN12 ;
			pincfg.GPIO_MODE = GPIO_MODE_AF_PP;
			pincfg.GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		}

	}

	else if(UARTx == UART2)
	{
		//from alternative pin table for LQF and see recommended gpio pins configuration table
		//PA2 TX
		//PA3 RX
		//PA0 CTS
		//PA1 RTS

		//PA2 TX
		pincfg.GPIO_PinNumber = GPIO_PIN2 ;
		pincfg.GPIO_MODE = GPIO_MODE_AF_PP;
		pincfg.GPIO_OUTPUT_speed = GPIO_SPEED_10M;
		MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		//PA3 RX
		pincfg.GPIO_PinNumber = GPIO_PIN3 ;
		pincfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		//PA0 CTS
		if(global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS || global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS_RTS)
		{
			pincfg.GPIO_PinNumber = GPIO_PIN0 ;
			pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		}

		//PA1 RTS
		if(global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_RTS || global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS_RTS)
		{
			pincfg.GPIO_PinNumber = GPIO_PIN1 ;
			pincfg.GPIO_MODE = GPIO_MODE_AF_PP;
			pincfg.GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		}
	}

	else if(UARTx == UART3)
	{
		//from alternative pin table for LQF and see recommended gpio pins configuration table
		//PB10 TX
		//PB11 RX
		//PB13 CTS
		//PA14 RTS

		//PB10 TX
		pincfg.GPIO_PinNumber = GPIO_PIN10 ;
		pincfg.GPIO_MODE = GPIO_MODE_AF_PP;
		pincfg.GPIO_OUTPUT_speed = GPIO_SPEED_10M;
		MCAL_GPIO_INIT(GPIOB, &pincfg) ;

		//PB11 RX
		pincfg.GPIO_PinNumber = GPIO_PIN11 ;
		pincfg.GPIO_MODE = GPIO_MODE_AF_INPUT;
		MCAL_GPIO_INIT(GPIOB, &pincfg) ;

		//PB13 CTS
		if(global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS || global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS_RTS)
		{
			pincfg.GPIO_PinNumber = GPIO_PIN13 ;
			pincfg.GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			MCAL_GPIO_INIT(GPIOB, &pincfg) ;

		}

		//PA14 RTS
		if(global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_RTS || global_UART_config->HWFlowcontrol == UART_HWFlowcontrol_CTS_RTS)
		{
			pincfg.GPIO_PinNumber = GPIO_PIN14 ;
			pincfg.GPIO_MODE = GPIO_MODE_AF_PP;
			pincfg.GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, &pincfg) ;

		}
	}
}

/**================================================================
 * @Fn               - MCAL_UART_SendData
 * @brief            -send buffer on UART
 *param[in]          -USARTx :where x can be 1,2,3 depending on device used
 *param[in]          -PTXBuffer: the buffer that will be transmitted
 *param[in]          -PollingEn enable or disable the polling
 * @retval           -none
 * Note              -should initialize UART firist
 */
void MCAL_UART_send_data(UART_t* UARTx, uint32_t* PTXBuffer, polling_state_t PollingMechanism)
{
	//if we using polling mechanism
	if(PollingMechanism == pollingEn)
	{
		while( !(UARTx->SR & (1<<7) ) ); //Bit 7 TXE: Transmit data register empty
	}

	//check the data length
	//	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
	//	the value written in the MSB (bit 7 or bit 8 depending on the data length)
	if(global_UART_config->Payload_Lentgh == UART_PayloadLentgh_9bit)
	{
		UARTx->DR = ( (*PTXBuffer) & (uint16_t)0x01FF);
	}
	else if(global_UART_config->Payload_Lentgh == UART_PayloadLentgh_8bit)
	{
		UARTx->DR = ( (*PTXBuffer) & (uint16_t)0x0FF );
	}
}

/**================================================================
 * @Fn               - MCAL_UART_Recieve_data
 * @brief            -Recieve buffer on UART
 *param[in]          -USARTx :where x can be 1,2,3 depending on device used
 *param[in]          -PRXBuffer: the buffer that will be Recieved
 *param[in]          -PollingEn enable or disable the polling
 * @retval           -none
 * Note              -none
 */
void MCAL_UART_Recieve_data(UART_t* UARTx, uint32_t* PRXBuffer, polling_state_t PollingMechanism)
{
	//if we using polling mechanism
	if(PollingMechanism == pollingEn)
	{
		while( !(UARTx->SR & (1<<5) ) );  //Bit 5 RXNE: Read data register not empty
	}

	//check the data length
	if(global_UART_config->Payload_Lentgh == UART_PayloadLentgh_9bit)
	{
		if(global_UART_config->parity == UART_parity_NONE) //if not used pairty then all buffer is data
		{
			*((uint16_t*)PRXBuffer) = UARTx->DR;
		}
		else
		{
			*((uint16_t*)PRXBuffer) = ( UARTx->DR & 0x0FF); //if we used pairty then 8 bit only is data and 9 bit is pairty
		}
	}
	else if(global_UART_config->Payload_Lentgh == UART_PayloadLentgh_8bit)
	{
		if(global_UART_config->parity == UART_parity_NONE) //if not used pairty then all buffer is data
		{
			*((uint16_t*)PRXBuffer) = UARTx->DR;
		}
		else
		{
			*((uint16_t*)PRXBuffer) = ( UARTx->DR & 0x07F); //if we used pairty then 7 bit only is data and 8 bit is pairty
		}
	}
}


/**================================================================
 * @Fn               - MCAL_UART_wait_TC
 * @brief            -waiting the transsmit to ceomplete
 *param[in]          -USARTx :where x can be 1,2,3 depending on device used
 * @retval           -none
 * Note              -none
 */
void MCAL_UART_wait_TC(UART_t* UARTx)
{
	while( !(UARTx->SR & (1<<6) ) ); //Bit 6 TC: Transmission complete
}


//ISR
void USART1_IRQHandler(void)//ISR USART1
{
	global_UART_config->P_IRQ_Callback();
}

void USART2_IRQHandler(void)//ISR USART1
{
	global_UART_config->P_IRQ_Callback();
}

void USART3_IRQHandler(void)//ISR USART1
{
	global_UART_config->P_IRQ_Callback();
}



/*
 * ======================================================================
 *                   End of USART  driver.c
 *======================================================================
 */






