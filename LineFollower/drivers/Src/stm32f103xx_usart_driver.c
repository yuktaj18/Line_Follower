/*
 * stm32f103xx_usart_driver.c
 *
 *  Created on: 14-Dec-2025
 *      Author: yukta
 */

#include "stm32f103xx_usart_driver.h"
/*
 * Peripheral Clock setup
 */
void USART_PeriClockControl(USART_Reg_Def_t *pUSARTx, uint8_t EnorDi){
	if ( EnorDi == ENABLE)
	 {
	 	 if (pUSARTx == USART1)
	 	 {
	 		USART1_PCLK_EN();
	 	 }
	 	 else if (pUSARTx == USART2)
	 	 {
	 		USART2_PCLK_EN();
	 	 }
	 	 else if (pUSARTx == USART3)
	 	 {
	 		USART3_PCLK_EN();
	 	 }



	 }
	else
	{
			if (pUSARTx == USART1)
			 	 {
			 		USART1_PCLK_DI();
			 	 }
			 	 else if (pUSARTx == USART2)
			 	 {
			 		USART2_PCLK_DI();
			 	 }
			 	 else if (pUSARTx == USART3)
			 	 {
			 		USART3_PCLK_DI();
			 	 }

	}
	}
/*
 * BaudRate Calculation
 */
void USART_SetBaudRate(USART_Reg_Def_t *pUSARTx, uint32_t BaudRate)
{

	//Variable to hold the APB clock
		uint32_t PCLKx;

		uint32_t usartdiv;

		//variables to hold Mantissa and Fraction values
		uint32_t M_part,F_part;

	  uint32_t tempreg=0;


// System Clock Value
	  if (pUSARTx == USART1)
	  {

		  //apb2 clcok
		  PCLKx = RCC_GetPCLK2Value();
	  }
	  else
	  {
		  //apb1
		  PCLKx = RCC_GetPCLK1Value();
	  }
//Baud calculation

	  usartdiv = (PCLKx/(16*BaudRate));

//Calculate M part
	  M_part = usartdiv/100;
//Placing M part in appropriate bit position.
	  tempreg |= M_part << 4;
//Calculate final fraction
	  F_part = (usartdiv - (M_part*100));

	  F_part = ((( F_part * 16)+ 50) / 100) & ((uint8_t)0x0F);

	  tempreg |= F_part;

	  pUSARTx->USART_BRR = tempreg;
}

/*
 * Init and De-init
 */
void USART_Init(USART_Handle_t *pUSARTHandle)
{

	uint32_t temp =0;

	//PeriClock Enable
	USART_PeriClockControl(pUSARTHandle->pUSARTx,ENABLE);
/******************************CR1 Reg**********************************************/
	//ModeConfig
	if(pUSARTHandle->USART_Config.USART_Mode ==  USART_MODE_ONLY_TX)
	{
		temp |= (1<<USART_CR1_TX_EN);
	}
	else if (pUSARTHandle->USART_Config.USART_Mode ==  USART_MODE_ONLY_RX)
	{
		temp |= (1<<USART_CR1_RX_EN);
	}
	else if (pUSARTHandle->USART_Config.USART_Mode ==  USART_MODE_TXRX)
	{
		temp |= ((1<<USART_CR1_TX_EN)|(1<<USART_CR1_RX_EN));

	}

	//WordLength
	temp |= pUSARTHandle->USART_Config.USART_WordLength << USART_CR1_M ;

	//Parity Control

	if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN )
	{
		temp |= (1<<USART_CR1_PCE);
	}
	else if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_EN_EVEN )
	{
		temp |= (1<<USART_CR1_PCE);
		temp |= (1<<USART_CR1_PS);


	}
	pUSARTHandle->pUSARTx->USART_CR1 = temp ;

/****************************************CR2*************************************************/

	temp = 0;

	//Stop Bits
	temp |= pUSARTHandle->USART_Config.USART_NoOfStopBits << USART_CR2_STOP_BIT;

	pUSARTHandle->pUSARTx->USART_CR2 = temp ;

/**************************************CR3***************************************************/

	temp = 0;

	if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS)
	{
			temp |= 1 << USART_CR3_CTSE;
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_RTS)
	{
			temp |= 1 << USART_CR3_RTSE;
	}
	else if(pUSARTHandle->USART_Config.USART_HWFlowControl == USART_HW_FLOW_CTRL_CTS_RTS)
	{
		temp |= 1 << USART_CR3_CTSE;

		temp |= 1 << USART_CR3_RTSE;
	}

	pUSARTHandle->pUSARTx->USART_CR3 = temp ;

	temp = 0;

/*****************************BRR Reg*************************************************/

//Baud Rate


	//USART_SetBaudRate(pUSARTHandle->pUSARTx,pUSARTHandle->USART_Config.USART_BaudRate);
	//temp = 8000000/(16*115200L);
	pUSARTHandle->pUSARTx->USART_BRR = 0x45 ;


}


void USART_DeInit(USART_Reg_Def_t *pUSARTx)
{
	if (pUSARTx == USART1)
		{
			USART1_Reg_Reset();
		}
		else if (pUSARTx == USART2)
		{
			USART2_Reg_Reset();
		}
		else if (pUSARTx == USART3)
		{
			USART3_Reg_Reset();
		}




	}

void USART_SendData(USART_Handle_t *pUSARTHandle, uint8_t *pTxBuffer, uint32_t Len)
{
	/*while(1)
	{
	while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TXE_FLAG));
	pUSARTHandle->pUSARTx->USART_DR =0x55;
	}
	//while(!USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TC_FLAG));
	//while(1) ;
*/

	uint16_t *pdata;
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until TXE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TXE_FLAG));

         //Check the USART_WordLength item for 9BIT or 8BIT in a frame
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//if 9BIT, load the DR with 2bytes masking the bits other than first 9 bits
			pdata = (uint16_t*) pTxBuffer;
			pUSARTHandle->pUSARTx->USART_DR = (*pdata & (uint16_t)0x01FF);

			//check for USART_ParityControl
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used in this transfer. so, 9bits of user data will be sent
				//Implement the code to increment pTxBuffer twice
				pTxBuffer++;
				pTxBuffer++;
			}
			else
			{
				//Parity bit is used in this transfer . so , 8bits of user data will be sent
				//The 9th bit will be replaced by parity bit by the hardware
				pTxBuffer++;
			}
		}
		else
		{
			//This is 8bit data transfer
			pUSARTHandle->pUSARTx->USART_DR = (*pTxBuffer  & (uint8_t)0xFF);

			//Implement the code to increment the buffer address
			pTxBuffer++;

		}
	}

	//Implement the code to wait till TC flag is set in the SR
	while( ! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_TC_FLAG));

}


void USART_ReceiveData(USART_Handle_t *pUSARTHandle, uint8_t *pRxBuffer, uint32_t Len)
{
   //Loop over until "Len" number of bytes are transferred
	for(uint32_t i = 0 ; i < Len; i++)
	{
		//Implement the code to wait until RXNE flag is set in the SR
		while(! USART_GetFlagStatus(pUSARTHandle->pUSARTx,USART_RXNE_FLAG));

		//Check the USART_WordLength to decide whether we are going to receive 9bit of data in a frame or 8 bit
		if(pUSARTHandle->USART_Config.USART_WordLength == USART_WORDLEN_9BITS)
		{
			//We are going to receive 9bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used. so, all 9bits will be of user data

				//read only first 9 bits. so, mask the DR with 0x01FF
				*((uint16_t*) pRxBuffer) = (pUSARTHandle->pUSARTx->USART_DR  & (uint16_t)0x01FF);

				//Now increment the pRxBuffer two times
				pRxBuffer++;
				pRxBuffer++;
			}
			else
			{
				//Parity is used, so, 8bits will be of user data and 1 bit is parity
				 *pRxBuffer = (pUSARTHandle->pUSARTx->USART_DR  & (uint8_t)0xFF);

				 //Increment the pRxBuffer
				 pRxBuffer++;
			}
		}
		else
		{
			//We are going to receive 8bit data in a frame

			//check are we using USART_ParityControl control or not
			if(pUSARTHandle->USART_Config.USART_ParityControl == USART_PARITY_DISABLE)
			{
				//No parity is used , so all 8bits will be of user data

				//read 8 bits from DR
				 *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->USART_DR & (uint8_t)0xFF) ;
			}

			else
			{
				//Parity is used, so , 7 bits will be of user data and 1 bit is parity

				//read only 7 bits , hence mask the DR with 0X7F
				 *pRxBuffer = (uint8_t)(pUSARTHandle->pUSARTx->USART_DR & (uint8_t)0x7F);

			}

			//increment the pRxBuffer
			pRxBuffer++;
		}
	}

}


void USART_PeripheralControl(USART_Reg_Def_t *pUSARTx, uint8_t EnOrDi)
{
	if (EnOrDi == ENABLE)
	{
		pUSARTx->USART_CR1 |=(1<<USART_CR1_UE);

	}
	else
	{
		pUSARTx->USART_CR1 &= ~(1<<USART_CR1_UE);
	}

}

uint8_t USART_GetFlagStatus(USART_Reg_Def_t *pUSARTx , uint32_t FlagName)
{
		if (pUSARTx->USART_SR & FlagName)
		{
			return FlagSet;
		}

		return FlagReset;

}


