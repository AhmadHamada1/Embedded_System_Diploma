/*
 * stm32f103c6_UART_driver.h
 *
 *  Created on: 4 Feb 2023
 *      Author: Dell
 */

#ifndef INC_STM32F103C6_USART_DRIVER_H_
#define INC_STM32F103C6_USART_DRIVER_H_

#include "stm32f103c6.h"
#include "Stm32F103c6_gpio_driver.h"
#include "stm32f103c6_RCC_driver.h"

//config parameters
typedef struct
{
	uint8_t UART_Mode; //specify TX/RX Enable / Disable based on @ref UART_Mode_ref

	uint32_t BaudRate;//specify communiction between microcontrollers based on @ref UART_BaudRate_ref

	uint8_t Payload_Lentgh;//specify the lentgh of data based on @ref UART_PayloadLentgh_ref

	uint8_t parity;//specify the parity of data to check on it based on @ref UART_parity_ref

	uint8_t StopBit;//specify the number of StopBit based on @ref UART_StopBit_ref

	uint8_t HWFlowcontrol;//specify whether hardware flow control is enable or disable based on @ref UART_HWFlowcontrol_ref

	uint8_t IRQ_Enable; //Specifies UART IRQ TX/RX Enable/Disable based on @ref UART_IRQ_Enable_ref

	void (*P_IRQ_Callback)(void);// set the C Function() which will be called once the IRQ  Happen
}UART_config;

//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//================refrence Macros===========
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

//UART_Mode_ref

#define UART_Mode_TX                 (uint32_t)(1<<3) //Bit 3 TE: Transmitter enable This bit enables the transmitter. It is set and cleared by software.
#define UART_Mode_RX                 (uint32_t)(1<<2) //Bit 2 RE: Receiver enable This bit enables the receiver. It is set and cleared by software.
#define UART_Mode_TX_RX              (uint32_t)((1<<3) | (1<<2) )//to Enable both

//UART_BaudRate_ref

#define UART_BaudRate_2400           2400
#define UART_BaudRate_9600           9600
#define UART_BaudRate_19200          19200
#define UART_BaudRate_57600          57600
#define UART_BaudRate_115200         115200
#define UART_BaudRate_230400         230400
#define UART_BaudRate_460800         460800
#define UART_BaudRate_921600         921600
#define UART_BaudRate_2250000        2250000
#define UART_BaudRate_4500000        4500000

//UART_PayloadLentgh_ref

#define UART_PayloadLentgh_8bit      (uint32_t)(0)
#define UART_PayloadLentgh_9bit      (uint32_t)(1<<12)//Bit 12 M: Word length This bit determines the word length. It is set or cleared by software

//UART_parity_ref

#define UART_parity_NONE      (uint32_t)(0) //Bit 10 PCE: Parity control enable
#define UART_parity_EVEN      (uint32_t)(1<<10) //Bit 9 PS: Parity selection
#define UART_parity_ODD       (uint32_t)((1<<10) | (1<<9) ) //Bit 9 PS: Parity selection

//UART_StopBit_ref (Bits 13:12 STOP: STOP bits) (The 0.5 Stop bit and 1.5 Stop bit are not available for UART4 & UART5)

#define UART_StopBit_1             (uint32_t)(0)
#define UART_StopBit_Half          (uint32_t)(1<<12)
#define UART_StopBit_1andHalf    	(uint32_t)(3<<12)
#define UART_StopBit_2    			(uint32_t)(2<<12)

//UART_HWFlowcontrol_ref

#define UART_HWFlowcontrol_NONE         (uint32_t)(0)
#define UART_HWFlowcontrol_CTS          (uint32_t)(1<<9)//Bit 9 CTSE: CTS enable
#define UART_HWFlowcontrol_RTS          (uint32_t)(1<<8)//Bit 8 RTSE: RTS enable
#define UART_HWFlowcontrol_CTS_RTS      (uint32_t)( (1<<9) | (1<<8) )//Enable both

//UART_IRQ_Enable_ref

#define UART_IRQ_Enable_NONE             (uint32_t)(0)
#define UART_IRQ_Enable_TXE              (uint32_t)(1<<7)//transmit data register empty
#define UART_IRQ_Enable_TC               (uint32_t)(1<<6) //Transmission complete interrupt enable
#define UART_IRQ_Enable_RXNEIE           (uint32_t)(1<<5)//Recived data ready to read and overrun error detected
#define UART_IRQ_Enable_PE               (uint32_t)(1<<8) //parity error


//Baudrate calculation
//USARTDIV = fclk /(16*Baudrate)
//USARTDIV_Mul100  = (uint32)(100*fclk)/(16*Baudrate)
//USARTDIV_Mul100  = (uint32)(25*fclk)/(4*Baudrate)
//DIV_Mantissa_MUL100 = Integar part (USARTDIV) *100
//DIV_Mantissa = Integar part (USARTDIV)
//DIV_Fraction = ((USARTDIV_Mul100 - DIV_Mantissa_MUL100 ) * 16 )/100)

#define USARTDIV(_PCLK_,_BAUD_)                  (uint32_t)(_PCLK_/(16 * _BAUD_))
#define USARTDIV_Mul100(_PCLK_,_BAUD_)           (uint32_t)((25 * _PCLK_)/(4 * _BAUD_))
#define Mantissa_MUL100(_PCLK_,_BAUD_)           (uint32_t) (USARTDIV(_PCLK_,_BAUD_) * 100)
#define Mantissa(_PCLK_,_BAUD_)                  (uint32_t) (USARTDIV(_PCLK_,_BAUD_))
#define DIV_Fraction(_PCLK_,_BAUD_)              (uint32_t) (( USARTDIV_Mul100(_PCLK_,_BAUD_)  - Mantissa_MUL100(_PCLK_,_BAUD_)) * 16 )
#define UART_BRR_Register(_PCLK_,_BAUD_)         ( (Mantissa(_PCLK_,_BAUD_)) <<4 ) | ( (DIV_Fraction(_PCLK_,_BAUD_)) & 0xF)


//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-
//================APIS===========
//*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-

void MCAL_UART_init(UART_t* UARTx,UART_config* UART_cfg);
void MCAL_UART_Deinit(UART_t* UARTx);

void MCAL_UART_set_GPIO_pin(UART_t* UARTx);

void MCAL_UART_send_data(UART_t* UARTx, uint32_t* PTXBuffer, polling_state_t PollingMechanism);
void MCAL_UART_Recieve_data(UART_t* UARTx, uint32_t* PRXBuffer, polling_state_t PollingMechanism);

void MCAL_UART_wait_TC(UART_t* UARTx);


#endif /* INC_STM32F103C6_UART_DRIVER_H_ */
