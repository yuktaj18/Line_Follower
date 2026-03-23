/*
 * stm32f103xx_usart_driver.h
 *
 *  Created on: 14-Dec-2025
 *      Author: yukta
 */

#ifndef INC_STM32F103XX_USART_DRIVER_H_
#define INC_STM32F103XX_USART_DRIVER_H_

#include "stm32f103xx.h"

/*
 * USART configuration
 */
typedef struct {

	uint8_t USART_Mode;
	uint32_t USART_BaudRate;
	uint8_t USART_NoOfStopBits;
	uint8_t USART_WordLength;
	uint8_t USART_ParityControl;
	uint8_t USART_HWFlowControl;
	uint8_t USART_Speed;



}USART_Config_t;


typedef struct{

	USART_Reg_Def_t *pUSARTx;
	USART_Config_t USART_Config;
	}USART_Handle_t;



/*
 *@USART_Mode
 *Possible options for USART_Mode
 */
#define USART_MODE_ONLY_TX 0
#define USART_MODE_ONLY_RX 1
#define USART_MODE_TXRX  2

/*
 *@USART_Baud
 *Possible options for USART_Baud
 */
#define USART_STD_BAUD_2400					2400
#define USART_STD_BAUD_9600					9600
#define USART_STD_BAUD_19200 				19200
#define USART_STD_BAUD_57600 				57600
#define USART_STD_BAUD_115200 				115200
#define USART_STD_BAUD_230400 				230400
#define USART_STD_BAUD_460800 				460800
#define USART_STD_BAUD_921600 				921600
#define USART_STD_BAUD_225M					2250000
#define SUART_STD_BAUD_4_5M 				4500000


/*
 *@USART_ParityControl
 *Possible options for USART_ParityControl
 */
#define USART_PARITY_EN_ODD   2
#define USART_PARITY_EN_EVEN  1
#define USART_PARITY_DISABLE   0

/*
 *@USART_WordLength
 *Possible options for USART_WordLength
 */
#define USART_WORDLEN_8BITS  0
#define USART_WORDLEN_9BITS  1

/*
 *@USART_NoOfStopBits
 *Possible options for USART_NoOfStopBits
 */
#define USART_STOPBITS_1     0b00
#define USART_STOPBITS_0_5   0b01
#define USART_STOPBITS_2     0b10
#define USART_STOPBITS_1_5   0b11

/*
 *@USART_HWFlowControl
 *Possible options for USART_HWFlowControl
 */
#define USART_HW_FLOW_CTRL_NONE    	0
#define USART_HW_FLOW_CTRL_CTS    	1
#define USART_HW_FLOW_CTRL_RTS    	2
#define USART_HW_FLOW_CTRL_CTS_RTS	3

/*
 * USART CR1 Reg
 */
#define USART_CR1_TX_EN				3
#define USART_CR1_RX_EN				2
#define USART_CR1_M					12
#define USART_CR1_PCE				10
#define USART_CR1_PS				9
#define USART_CR1_UE				13
/*
 * USART CR2 Reg
 */
#define USART_CR2_STOP_BIT			12
#define USART_CR2_CLK_EN			11
#define USART_CR2_CPOL				10
#define USART_CR2_CPHA				9
#define USART_CR2_ADD				0

/*
 * USART CR3 Reg
 */
#define USART_CR3_CTSIE				10
#define USART_CR3_CTSE				9
#define USART_CR3_RTSE				8
#define USART_CR3_HDSEL				3
#define USART_CR3_EIE				0


/*
 * USART SR
 */

#define USART_SR_PE					0
#define USART_SR_FE					1
#define USART_SR_NE					2
#define USART_SR_ORE				3
#define USART_SR_IDLE				4
#define USART_SR_RXNE				5
#define USART_SR_TC					6
#define USART_SR_TXE				7
#define USART_SR_LBD				8
#define USART_SR_CTS				9

//FLAG

#define USART_TXE_FLAG				(1 << USART_SR_TXE)
#define USART_TC_FLAG				(1 << USART_SR_TC)
#define USART_RXNE_FLAG				(1 << USART_SR_RXNE)


/*************************************************************************
 * API
 **************************************************************************/

/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_Reg_Def_t *pUSARTx, uint8_t EnorDi);
void USART_SetBaudRate(USART_Reg_Def_t *pUSARTx, uint32_t BaudRate);

/*
 * Init and De-init
 */
void USART_Init(USART_Handle_t *pUSARTHandle);
void USART_DeInit(USART_Reg_Def_t *pUSARTx);


/*
 * Data Send and Receive
 */
void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_SendDataIT(USART_Handle_t *pUSARTHandle,uint8_t *pTxBuffer, uint32_t Len);
uint8_t USART_ReceiveDataIT(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len);

/*
 * IRQ Configuration and ISR handling
 */
void USART_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi);
void USART_IRQPriorityConfig(uint8_t IRQNumber, uint32_t IRQPriority);
void USART_IRQHandling(USART_Handle_t *pHandle);

/*
 * Other Peripheral Control APIs
 */
void USART_PeripheralControl(USART_Reg_Def_t *pUSARTx, uint8_t EnOrDi);
uint8_t USART_GetFlagStatus(USART_Reg_Def_t *pUSARTx , uint32_t FlagName);
void USART_ClearFlag(USART_Reg_Def_t *pUSARTx, uint16_t StatusFlagName);

/*
 * Application callback
 */
void USART_ApplicationEventCallback(USART_Handle_t *pUSARTHandle,uint8_t AppEv);





















#endif /* INC_STM32F103XX_USART_DRIVER_H_ */
