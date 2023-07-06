/*
 * stm32f103c6_SPI_driver.h
 *
 *  Created on: 7 Jun 2023
 *      Author: Dell
 */

#ifndef INC_STM32F103C6_SPI_DRIVER_H_
#define INC_STM32F103C6_SPI_DRIVER_H_

//-----------------------------
//Includes
//-----------------------------
#include "stm32f103c6.h"
#include "Stm32F103c6_gpio_driver.h"


//-----------------------------
//User type definitions (structures)
//config structure
//-----------------------------

//interrupt structure
typedef struct
{
	uint8_t TXE : 1;      // Tx buffer empty interrupt
	uint8_t RXNE : 1;     // Rx buffer not empty interrupt
	uint8_t ERRI : 1;     // Error interrupt
	uint8_t Reserved : 5;
}SPI_IRQ_t;

//configure structure
typedef struct
{
	uint16_t Device_Mode;           //configure SPI master or slave from @ref SPI_Device_Mode.

	uint16_t communication_Mode;    //configure SPI bidirectional Mode  from @ref SPI_communication_Mode.

	uint16_t Frame_format;          //configure LSB or MSB from @ref SPI_Frame_format.

	uint16_t CLK_Polarity;             //configure the Polarity of SPI Clock from @ref SPI_CLK_Polarity.

	uint16_t DataSize;               //configure the Size of SPI Data (8 BIT or 16 BIT )from @ref SPI_Data_Size.


	uint16_t CLK_Phase;               //configure the phase of SPI Clock from @ref SPI_CLK_Phase.

	uint16_t NSS;                //Specific which mange NSS signal (HW) or enable SSI (manage by SW)
									//from @ref SPI_NSS_define.

	uint16_t BaudRate_Prescaler;          //configure the SPI BaudRate prescaler from (APB1 if  using SPI2)
										//or from (APB2 if using SPI1 ) from @ref SPI_BaudRate_Prescaler.

	uint16_t IRQ_Enable;               //interrrupt enable from @ref SPI_IRQ_Enable


	void(*IRQ_CallBack)(SPI_IRQ_t IRQ_SRC); // function call back to call when interrrupt occured.

}SPI_config_t;


//-----------------------------
//Macros Configuration References
//-----------------------------
/*@ref Module_REF_NAME_define
 */

//@ref SPI_Device_Mode.
#define SPI_DEVICE_MODE_SLAVE      0
#define SPI_DEVICE_MODE_MASTER     (1<<2) // CR1 MSTR = 1

//@ref SPI_communication_Mode.
#define SPI_UNIDRICTIONAL_2LINES                0                    // 2-line unidirectional data mode selected CR1 (bit 15 : 0) && FULL DUPLEX(bit 10 : 0).
#define SPI_UNIDRICTIONAL_2LINES_RXONLY        (1 << 10)             //2-line unidirectional data mode selected CR1 (bit 15 : 0) && Recieve only(bit 10 : 1).
#define SPI_BIDRICTIONAL_1LINES_RXONLY         (1 << 15)             //1-line bidirectional data mode selected CR1 (bit 15 : 1) Recieve only(bit 14 : 0).
#define SPI_BIDRICTIONAL_1LINES_TXONLY         ((1 << 15) | (1<<14)) //1-line bidirectional data mode selected CR1 (bit 15 : 1) Transmit only(bit 14 : 1).

//@ref SPI_Frame_format.
#define SPI_MSB_TRANSMIT_FRIST        0
#define SPI_LSB_TRANSMIT_FRIST       (1<<7) // CR1 (BIT 7 : 1)

//@ref SPI_Data_Size.
#define SPI_DATA_SIZE_8BIT        0
#define SPI_DATA_SIZE_16BIT       (1<<11) // CR1 (BIT 11 : 1)

//@ref SPI_CLK_Polarity.
#define SPI_CLK_POLARITY_HIGH_WHEN_IDLE        0
#define SPI_CLK_POLARITY_LOW_WHEN_IDLE         (1<< 1) // CR2 (BIT 1 : 1)

//@ref SPI_CLK_Phase.
#define SPI_CLK_PHASE_1EDGE_FRIST_DATA_SAMPLING       0
#define SPI_CLK_PHASE_2EDGE_FRIST_DATA_SAMPLING       (1 << 0) // CR2 (BIT 0 : 1)

//@ref SPI_NSS_define.
// Hardware
#define NSS_HW_SLAVE                              0         // Hardware NSS management (CR1.SSM = 0 )
#define NSS_HW_MASTER_SSO_ENABLE                 (1 << 2)  // NSS output enabled (CR1.SSM = 0, CR2.SSOE = 1) can't work in multimaster
#define NSS_HW_MASTER_SSO_DISABLE                 0        // NSS output disabled (CR1.SSM = 0, CR2.SSOE = 0) can work in multimaster

// Software
#define NSS_SW_RESET                             (1 << 9)          // Software slave management disabled
#define NSS_SW_SET                               (1 << 9 | 1 << 8) // Software slave management enabled

//@ref SPI_BaudRate_Prescaler. CR1.BIT3 : CR1.BIT5
#define SPI_BAUDRATE_PRE_2 		  0
#define SPI_BAUDRATE_PRE_4        (0b001 << 3)
#define SPI_BAUDRATE_PRE_8        (0b010 << 3)
#define SPI_BAUDRATE_PRE_16       (0b011 << 3)
#define SPI_BAUDRATE_PRE_32       (0b100 << 3)
#define SPI_BAUDRATE_PRE_64       (0b101 << 3)
#define SPI_BAUDRATE_PRE_128      (0b110 << 3)
#define SPI_BAUDRATE_PRE_256      (0b111 << 3)

//@ref SPI_IRQ_Enable (CR2)
#define SPI_IRQ_Enable_NONE        0         // No interrupt enabled
#define SPI_IRQ_Enable_TXEIE      (1 << 7)   // TXE interrupt not masked. Used to generate an interrupt request when the TXE flag is set.
#define SPI_IRQ_Enable_RXNEIE     (1 << 6)   // RXNE interrupt not masked. Used to generate an interrupt request when the RXNE flag is set.
#define SPI_IRQ_Enable_ERRIE      (1 << 5)   // Error interrupt is enabled



/*
 * ====================================================================================================
 * ============================== APIs ================================
 * ====================================================================================================
 */

void MCAL_SPI_INIT(SPI_t* SPIx, SPI_config_t* SPI_config);
void MCAL_SPI_DEINIT(SPI_t* SPIx);

void MCAL_SPI_GPIO_SetPins(SPI_t *SPIx);

void MCAL_SPI_Transmit(SPI_t* SPIx, uint16_t* PTxbuffer,polling_state_t pollingmechanism);
void MCAL_SPI_Recieve(SPI_t* SPIx, uint16_t* PRxbuffer,polling_state_t pollingmechanism);
void MCAL_SPI_TX_RX(SPI_t* SPIx, uint16_t* PTxRxbuffer,polling_state_t pollingmechanism);


#endif /* INC_STM32F103C6_SPI_DRIVER_H_ */
