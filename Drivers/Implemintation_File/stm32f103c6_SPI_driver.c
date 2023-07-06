/*
 * stm32f103c6_gpio_driver.c
 *
 *  Created on: Dec 5, 2022
 *      Author: Ahmed ELgazzar
 */
#include"stm32f103c6_SPI_driver.h"

/*
 * ======================================================================
 *                                          Generic variables
 *======================================================================
 */
SPI_config_t* Global_SPI_config[2] = {NULL,NULL};

/*
 * ======================================================================
 *                                          Generic Macros
 *======================================================================
 */

//Global SPI config array index
#define SPI1_INDEX   0
#define SPI2_INDEX   1

//status registers
#define SPI_SR_TXE     (0x2) //SR register = 0b00000010
#define SPI_SR_RXNE    (0x1) //SR register = 0b00000001



/*
 * ======================================================================
 *                                          Generic Functions
 *======================================================================
 */


/*
 * ====================================================================================================
 *                          APIs Functions Definations
 * ====================================================================================================
 */

/**================================================================
 * @Fn               -MCAL_SPI_INIT
 * @brief            -set SPI Registers and configure parameters
 * param[in]         -SPIx :where x can be 1,2 depending on device used
 * param[in]         -SPI_config :all the SPI configuration
 * @retval           -none
 * Note              -none
 */
void MCAL_SPI_INIT(SPI_t* SPIx, SPI_config_t* SPI_config)
{
	//Alternative temp registers
	uint16_t temp_CR1 = 0;
	uint16_t temp_CR2 = 0;

	//Enable the choosen SPI 1 or 2
	if(SPIx == SPI1)
	{
		Global_SPI_config[SPI1_INDEX] = SPI_config;
		SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		Global_SPI_config[SPI2_INDEX] = SPI_config;
		SPI2_CLK_EN();
	}

	//Enable SPI SPE CR1 : Bit 6.
	temp_CR1 |= (1<<6);

	//Set Device mode
	temp_CR1 |= SPI_config->Device_Mode;

	//Set communication Mode
	temp_CR1 |= SPI_config->communication_Mode;

	//Set Frame format
	temp_CR1 |= SPI_config->Frame_format;

	//Set Data Size
	temp_CR1 |= SPI_config->DataSize;

	//Set CLK polarity
	temp_CR2 |= SPI_config->CLK_Polarity;

	//Set CLK phase
	temp_CR2 |= SPI_config->CLK_Phase;

	//Set CLK polarity
	temp_CR2 |= SPI_config->CLK_Polarity;

	//Set NSS configuration
	if(SPI_config->NSS == NSS_HW_MASTER_SSO_ENABLE)//Write on CR2
	{
		temp_CR2 |= SPI_config->NSS;
	}
	else if(SPI_config->NSS == NSS_HW_MASTER_SSO_DISABLE)//Write on CR2
	{
		temp_CR2 |= SPI_config->NSS;
	}
	else//Write on CR1
	{
		temp_CR1 |= SPI_config->NSS;
	}

	//Set BaudRate prescaler
	temp_CR1 |= SPI_config->BaudRate_Prescaler;

	//Enable the interrupt
	if(SPI_config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		temp_CR2 |= SPI_config->IRQ_Enable;
		if(SPIx == SPI1)
		{
			NVIC_SPI1_IRQ35_Enable;
		}
		else if(SPIx == SPI2)
		{
			NVIC_SPI2_IRQ36_Enable;
		}
	}
	SPIx->CR1 = temp_CR1;
	SPIx->CR2 = temp_CR2;

}

/**================================================================
 * @Fn               -MCAL_SPI_DEINIT
 * @brief            -Reset SPI Registers and configure parameters
 * param[in]         -SPIx :where x can be 1,2 depending on device used
 * @retval           -none
 * Note              -none
 */
void MCAL_SPI_DEINIT(SPI_t* SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_SPI1_IRQ35_Disable;
		SPI1_CLK_RESET();
	}
	else if(SPIx == SPI2)
	{
		NVIC_SPI2_IRQ36_Disable;
		SPI2_CLK_RESET();
	}
}

/**================================================================
 * @Fn               -MCAL_SPI_GPIO_SetPins
 * @brief            -set SPI GPIO pins
 * param[in]         -SPIx :where x can be 1,2 depending on device used
 * @retval           -none
 * Note              -none
 */
void MCAL_SPI_GPIO_SetPins(SPI_t *SPIx)
{
	Pin_config_t* SPI_Pincfg;
	if (SPIx == SPI1)
	{
		// PA4 : SPI1_NSS
		// PA5 : SPI1_SCK
		// PA6 : SPI1_MISO
		// PA7 : SPI1_MOSI
		if (Global_SPI_config[SPI1_INDEX]->Device_Mode == SPI_DEVICE_MODE_MASTER)
		{
			// PA4 : SPI1_NSS
			switch (Global_SPI_config[SPI1_INDEX]->NSS)
			{
			case NSS_HW_MASTER_SSO_DISABLE:
				// Hardware master / slave NSS output disabled (input floating).
				SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
				SPI_Pincfg->GPIO_PinNumber = GPIO_PIN4;
				MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);
				break;

			case NSS_HW_MASTER_SSO_ENABLE:
				// Hardware master / slave NSS output enabled Alternative function push-pull
				SPI_Pincfg->GPIO_MODE = GPIO_MODE_AF_PP;
				SPI_Pincfg->GPIO_PinNumber = GPIO_PIN4;
				SPI_Pincfg->GPIO_OUTPUT_speed = GPIO_SPEED_10M;
				MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);
				break;
			}

			// PA5 : SPI1_SCK
			// Master Alternative function push-pull
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_AF_PP;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN5;
			SPI_Pincfg->GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);

			// PA6 : SPI1_MISO
			// full duplex / master input floating
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN6;
			MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);

			// PA7 : SPI1_MOSI
			// full duplex / master alternative function push-pull
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_AF_PP;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN7;
			SPI_Pincfg->GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);
		}
		else if (Global_SPI_config[SPI1_INDEX]->Device_Mode == SPI_DEVICE_MODE_SLAVE)
		{
			// PA4 : SPI1_NSS
			if (Global_SPI_config[SPI1_INDEX]->NSS == NSS_HW_SLAVE)
			{
				// Hardware master / slave Input floating
				SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
				SPI_Pincfg->GPIO_PinNumber = GPIO_PIN4;
				MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);
			}

			// PA5 : SPI1_SCK
			// Slave input floating
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN5;
			MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);

			// PA6 : SPI1_MISO
			// full duplex / master input floating
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN6;
			MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);

			// PA7 : SPI1_MOSI
			// full duplex / master alternative function push-pull
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_AF_PP;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN7;
			SPI_Pincfg->GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOA, SPI_Pincfg);
		}
	}
	else if (SPIx == SPI2)
	{
		// PB12 : SPI2_NSS
		// PB13 : SPI2_SCK
		// PB14 : SPI2_MISO
		// PB15 : SPI2_MOSI
		if (Global_SPI_config[SPI2_INDEX]->Device_Mode == SPI_DEVICE_MODE_MASTER)
		{
			// PB12 : SPI2_NSS
			switch (Global_SPI_config[SPI2_INDEX]->NSS)
			{
			case NSS_HW_MASTER_SSO_DISABLE:
				// Hardware master / slave NSS output disabled (input floating).
				SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
				SPI_Pincfg->GPIO_PinNumber = GPIO_PIN12;
				MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);
				break;

			case NSS_HW_MASTER_SSO_ENABLE:
				// Hardware master / slave NSS output enabled Alternative function push-pull
				SPI_Pincfg->GPIO_MODE = GPIO_MODE_AF_PP;
				SPI_Pincfg->GPIO_PinNumber = GPIO_PIN12;
				SPI_Pincfg->GPIO_OUTPUT_speed = GPIO_SPEED_10M;
				MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);
				break;
			}

			// PB13 : SPI2_SCK
			// Master Alternative function push-pull
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_AF_PP;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN13;
			SPI_Pincfg->GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);

			// PB14 : SPI2_MISO
			// full duplex / master input floating
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN14;
			MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);

			// PB15 : SPI2_MOSI
			// full duplex / master alternative function push-pull
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_AF_PP;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN15;
			SPI_Pincfg->GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);
		}
		else if (Global_SPI_config[SPI2_INDEX]->Device_Mode == SPI_DEVICE_MODE_SLAVE)
		{
			// PB12 : SPI2_NSS
			if (Global_SPI_config[SPI2_INDEX]->NSS == NSS_HW_SLAVE)
			{
				// Hardware master / slave Input floating
				SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
				SPI_Pincfg->GPIO_PinNumber = GPIO_PIN12;
				MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);
			}

			// PB13 : SPI2_SCK
			// Slave input floating
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN13;
			MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);

			// PB14 : SPI2_MISO
			// full duplex / master input floating
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_INPUT_FLOAT;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN14;
			MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);

			// PB15 : SPI1_MOSI
			// full duplex / master alternative function push-pull
			SPI_Pincfg->GPIO_MODE = GPIO_MODE_AF_PP;
			SPI_Pincfg->GPIO_PinNumber = GPIO_PIN15;
			SPI_Pincfg->GPIO_OUTPUT_speed = GPIO_SPEED_10M;
			MCAL_GPIO_INIT(GPIOB, SPI_Pincfg);
		}
	}
}

/**================================================================
 * @Fn               -MCAL_SPI_Transmit
 * @brief            -transmit data in transmit buffer
 * param[in]         -SPIx :where x can be 1,2 depending on device used
 * param[in]         -Txbuffer :it is the buffer i want to send it
 * param[in]         -pollingmechanism :it is the interrupt mechanism enabled or not
 * @retval           -none
 * Note              -none
 */
void MCAL_SPI_Transmit(SPI_t* SPIx, uint16_t* PTxbuffer,polling_state_t pollingmechanism)
{
	if(pollingmechanism == pollingEn)
	{
		while( !((SPIx->SR) & SPI_SR_TXE) );
	}

	SPIx->DR = *PTxbuffer;
}

/**================================================================
 * @Fn               -MCAL_SPI_Transmit
 * @brief            -transmit data in transmit buffer
 * param[in]         -SPIx :where x can be 1,2 depending on device used
 * param[in]         -Rxbuffer :it is the buffer i want to receive in it
 * param[in]         -pollingmechanism :it is the interrupt mechanism enabled or not
 * @retval           -none
 * Note              -none
 */
void MCAL_SPI_Recieve(SPI_t* SPIx, uint16_t* PRxbuffer,polling_state_t pollingmechanism)
{
	if(pollingmechanism == pollingEn)
	{
		while( !((SPIx->SR) & SPI_SR_RXNE) );
	}

	*PRxbuffer = SPIx->DR ;
}

/**================================================================
 * @Fn               -MCAL_SPI_TX_RX
 * @brief            -transmit data in transmit buffer
 * param[in]         -SPIx :where x can be 1,2 depending on device used
 * param[in]         -Txbuffer :it is the buffer i want to send and recieve in it
 * param[in]         -pollingmechanism :it is the interrupt mechanism enabled or not
 * @retval           -none
 * Note              -none
 */
void MCAL_SPI_TX_RX(SPI_t* SPIx, uint16_t* PTxRxbuffer,polling_state_t pollingmechanism)
{
	if(pollingmechanism == pollingEn)
	{
		while( !((SPIx->SR) & SPI_SR_TXE) );
	}

	SPIx->DR = *PTxRxbuffer;

	if(pollingmechanism == pollingEn)
	{
		while( !((SPIx->SR) & SPI_SR_RXNE) );
	}

	*PTxRxbuffer = SPIx->DR ;
}


/*
 * ======================================================================
 *                   IRQ CALL BACK
 *======================================================================
 */

void SPI1_IRQHandler()
{
	SPI_IRQ_t IRQ_SRC;
	IRQ_SRC.TXE = ( ( (SPI1->SR) & (1<<1) ) >> 1);
	IRQ_SRC.RXNE = ( ( (SPI1->SR) & (1<<0) ) >> 0);
	IRQ_SRC.ERRI = ( ( (SPI1->SR) & (1<<4) ) >> 4);

	Global_SPI_config[SPI1_INDEX]->IRQ_CallBack(IRQ_SRC);

}

void SPI2_IRQHandler()
{
	SPI_IRQ_t IRQ_SRC;
	IRQ_SRC.TXE = ( ( (SPI2->SR) & (1<<1) ) >> 1);
	IRQ_SRC.RXNE = ( ( (SPI2->SR) & (1<<0) ) >> 0);
	IRQ_SRC.ERRI = ( ( (SPI2->SR) & (1<<4) ) >> 4);

	Global_SPI_config[SPI2_INDEX]->IRQ_CallBack(IRQ_SRC);

}


/*
 * ======================================================================
 *                   End of SPI  driver.c
 *======================================================================
 */






