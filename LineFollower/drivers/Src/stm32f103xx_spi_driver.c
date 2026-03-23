/*
 * stm32f103xx_spi_driver.c
 *
 *  Created on: Nov 17, 2025
 *      Author: yukta
 */



/*************************************************************************************************************************
 * SPI Nucelof103rb board pin
	PA4       SPI1_NSS
    PA5       SPI1_SCK
    PA6	      SPI1_MISO
	PA7	   	  SPI1_MOSI

  	PB12       SPI2_NSS
    PB13       SPI2_SCK
    PB14	   SPI2_MISO
	PB15	   SPI2_MOSI
 ***********************************************************************************************************************/
#include "stm32f103xx_spi_driver.h"

/*
 * SPI clock setup
 */
void SPI_PeriClockControl(SPI_Reg_Def_t *pSPIx, uint8_t EnorDi)                             //Enable the SPI clk
{

 if ( EnorDi == ENABLE)
 	 {
	 	 if (pSPIx == SPI1)
	 	 {
	 		SPI1_PCLK_EN();
	 	 }
	 	 else if (pSPIx == SPI2)
	 	 {
	 		SPI2_PCLK_EN();
	 	 }



 	 }
 else
 {
	 	 	 if (pSPIx == SPI1)
	 	 	 {
	 	 		SPI1_PCLK_DI();
	 	 	 }
	 	 	 else if (pSPIx == SPI2)
	 	 	 {
	 	 		SPI2_PCLK_DI();
	 	 	 }

 }



}


/*
 * SPI initializtion
 */
void SPI_Init(SPI_Handle_t *pSPIHandle )                                                    //Initalize the spi
{
	//Pwr enable
	PwrEn();
	//Clock enable
	SPI_PeriClockControl(pSPIHandle->pSPIx, ENABLE);
	//Configuring SPI_CR1

	uint32_t temp =0;

	//Device Mode

	temp = (pSPIHandle->SPI_PinConfig.SPI_DeviceMode)<< SPI_CR1_MSTR_BIT ;

	// Bus Config

	if (pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BusConfig_FullDuplex)
	{
			// clear bidimode
		temp &= ~(1<< SPI_CR1_BIDIMODE_BIT);
	}
	else if (pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BusConfig_HalfDuplex)
	{
		temp |= (1<< SPI_CR1_BIDIMODE_BIT);
	}
	else if (pSPIHandle->SPI_PinConfig.SPI_BusConfig == SPI_BusConfig_Simplex_Rx)
	{
		temp &= ~(1<< SPI_CR1_BIDIMODE_BIT);
		temp |= (1<< SPI_CR1_RX_ONLY_BIT);
	}

	// DFF Config
		temp |= pSPIHandle->SPI_PinConfig.SPI_DFF << SPI_CR1_DFF_BIT;
	//CPHA Config
		temp |= pSPIHandle->SPI_PinConfig.SPI_CPHA  << SPI_CR1_CPHA_BIT ;
	// CPOL Config
		temp |= pSPIHandle->SPI_PinConfig.SPI_CPOL  << SPI_CR1_CPOL_BIT ;
	//SSM Config
		temp |= pSPIHandle->SPI_PinConfig.SPI_SSM << SPI_CR1_SSM_BIT;
	//Speed Config
		temp |= pSPIHandle->SPI_PinConfig.SPI_Speed << SPI_CR1_BR_BIT;

		pSPIHandle->pSPIx->SPI_CR1 = temp ;

		temp =0;
}


void EnableSpi(SPI_Reg_Def_t *pSPIx, uint8_t EnorDi)
{


	 if ( EnorDi == ENABLE)
	 	 {
		 	 pSPIx->SPI_CR1 |= (1 << SPI_CR1_SPE_BIT);
	 	 }
	 else
	 {
		 pSPIx->SPI_CR1 &= ~(1 << SPI_CR1_SPE_BIT);

	 }


}

void EnableSSOE_BIT(SPI_Reg_Def_t *pSPIx, uint8_t EnorDi)
{


	 if ( EnorDi == ENABLE)
	 	 {
		 	 pSPIx->SPI_CR2 |= (1 << SPI_CR2_SSOE_BIT);
	 	 }
	 else
	 {
		 pSPIx->SPI_CR2 &= ~(1 << SPI_CR2_SSOE_BIT);

	 }


}

void EnableSSI_BIT(SPI_Reg_Def_t *pSPIx, uint8_t EnorDi)
{


	 if ( EnorDi == ENABLE)
	 	 {
		 	 pSPIx->SPI_CR1 |= (1 << SPI_CR1_SSI_BIT);
	 	 }
	 else
	 {
		 pSPIx->SPI_CR1 &= ~(1 << SPI_CR1_SSI_BIT);

	 }


}

void SPI_DeInit(SPI_Reg_Def_t *pSPIx)                                                      //DeInitialize the spi
{
	if (pSPIx == SPI1)
	{
		SPI1_Reg_Reset();
	}
	else if (pSPIx == SPI2)
	{
		SPI2_Reg_Reset();
	}
}

uint8_t SPI_GetFlagStatus(SPI_Reg_Def_t *pSPIx, uint8_t FlagName)
{

	if (pSPIx->SPI_SR & FlagName)
	{
		return FlagSet;
	}
	return FlagReset;

}

void SPI_SendData(SPI_Reg_Def_t *pSPIx, uint8_t *pTxBuffer, uint32_t len)
{

		while (len>0 ){

			while (!SPI_GetFlagStatus(pSPIx,SPI_TXE_FLAG));

			if (pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF_BIT))
				{
				  //16 bit
				  pSPIx->SPI_DR = *((uint16_t *)pTxBuffer);
				  len--;
				  len--;
				  (uint16_t *)pTxBuffer ++;

				}
			else
				{
				  //8bit
				  pSPIx->SPI_DR = *pTxBuffer;
 	 	 	 	  len--;
				  pTxBuffer++;
				}


		}
}


void SPI_ReceiveData(SPI_Reg_Def_t *pSPIx, uint8_t *pRxBuffer, uint32_t len)
		{

			while (len>0 ){

				while (!SPI_GetFlagStatus(pSPIx,SPI_RXNE_FLAG));

				if (pSPIx->SPI_CR1 & (1 << SPI_CR1_DFF_BIT))
					{
					  //16 bit
					   *((uint16_t *)pRxBuffer) =pSPIx->SPI_DR ;
					  len--;
					  len--;
					  (uint16_t *)pRxBuffer ++;

					}
				else
					{
					  //8bit
					  *pRxBuffer = pSPIx->SPI_DR;
	 	 	 	 	  len--;
	 	 	 	 	 pRxBuffer++;
					}

		}

}

