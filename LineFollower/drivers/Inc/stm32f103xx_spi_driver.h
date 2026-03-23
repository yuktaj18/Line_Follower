/*
 * stm32f103xx_spi_driver.h
 *
 *  Created on: Nov 17, 2025
 *      Author: yukta
 */

#ifndef INC_STM32F103XX_SPI_DRIVER_H_
#define INC_STM32F103XX_SPI_DRIVER_H_

#include "stm32f103xx.h"



/*
 * SPI configuration
 */
typedef struct {

	uint8_t SPI_DeviceMode;				//Selects whether mcu is master or slave
	uint8_t SPI_BusConfig;				//Selects whether commuincation is full duplex,half duplex or simplex
	uint8_t SPI_DFF;					//Configures whether 8 or 16 bit data frame is to be used
	uint8_t SPI_CPHA;					//Configures CPHA
	uint8_t SPI_CPOL;					//Configures CPOL
	uint8_t SPI_SSM;					//Slave configuration
	uint8_t SPI_Speed;					//Speed config of the commuincation



}SPI_Config_t;


/*
 * SPI Handle
 */
typedef struct
{

	SPI_Reg_Def_t *pSPIx;
	SPI_Config_t SPI_PinConfig;

}SPI_Handle_t;




/*
 * SPI CR1 Register bit
 */

#define SPI_CR1_MSTR_BIT 				2
#define SPI_CR1_CPOL_BIT				1
#define SPI_CR1_CPHA_BIT				0
#define SPI_CR1_BIDIMODE_BIT			15
#define SPI_CR1_BIDIOE_BIT				14
#define SPI_CR1_RX_ONLY_BIT				10
#define SPI_CR1_DFF_BIT					11
#define SPI_CR1_SSM_BIT					9
#define SPI_CR1_SSI_BIT					8
#define SPI_CR1_SPE_BIT 				6
#define SPI_CR1_BR_BIT					3

/*
 * SPI CR2 Register Bit
 */
#define SPI_CR2_RXDMAEN_BIT				0
#define SPI_CR2_TXDMAEN_BIT				1
#define SPI_CR2_SSOE_BIT				2
#define SPI_CR2_ERRIE_BIT				5
#define SPI_CR2_RXNEIE_BIT				6
#define SPI_CR2_TXEIE_BIT				7

/*
 * SPI SR Register
 */

#define SPI_SR_RXNE_BIT					0
#define SPI_SR_TXE_BIT					1
#define SPI_SR_CHSIDE_BIT				2
#define SPI_SR_UDR_BIT					3
#define SPI_SR_CRCERR_BIT				4
#define SPI_SR_MODF_BIT					5
#define SPI_SR_OVR_BIT					6
#define SPI_SR_BSY_BIT					7



/*
 * Device Mode Configuration
 */
#define MSTR_Master				1
#define MSTR_Slave				0

/*
 * Bus Config
 */

#define SPI_BusConfig_FullDuplex		1
#define SPI_BusConfig_HalfDuplex		2
#define SPI_BusConfig_Simplex_Rx		3

/*
 * SPE bit enable
 * DFF config bits
 */
#define SPE_ENABLE 				1 		//SPI Enable
#define SPE_DISABLE				0		//SPI Disable
#define DFF_8					0		//8 bit data frame	selection
#define DFF_16					1		//16 bit data frame selection

/*
 * CPHA
 */
#define CPHA_RisingEdge			0
#define CPHA_FallingEdge		1
/*
 * CPOL
 */

#define CPOL_0					0 		//CK to 0 when idle
#define CPOL_1					1		//CK to 1 when idle
/*
 * Slave Select
 */
#define SoftwareSlaveDisable	0
#define SoftwareSlaveSelect		1

/*
 * SPI Baud Rate / Speed
 */

#define fPCLK_2 				0b000
#define fPCLK_4 				0b001
#define fPCLK_8 				0b010
#define fPCLK_16 				0b011
#define fPCLK_32 				0b100
#define fPCLK_64 				0b101
#define fPCLK_128 				0b110
#define fPCLK_256 				0b111

/*
 * SPI SR Flag
 */
#define SPI_TXE_FLAG            (1 << SPI_SR_TXE_BIT)
#define SPI_RXNE_FLAG           (1 << SPI_SR_RXNE_BIT)
#define SPI_BSY_FLAG            (1 << SPI_SR_BSY_BIT)
/**************************************************************************************************************************

                           API for users to work with GPIO

 ***************************************************************************************************************************/

/*
 * SPI clock setup
 */
void SPI_PeriClockControl(SPI_Reg_Def_t *pSPIx, uint8_t EnorDi);                              //Enable the GPIO clk
void EnableSpi(SPI_Reg_Def_t *pSPIx, uint8_t EnorDi);
void EnableSSOE_BIT(SPI_Reg_Def_t *pSPIx, uint8_t EnorDi);
void EnableSSI_BIT(SPI_Reg_Def_t *pSPIx, uint8_t EnorDi);
/*
 * SPI initializtion
 */
void SPI_Init(SPI_Handle_t *pSPIHandle );                                                    //Initalize the gpio
void SPI_DeInit(SPI_Reg_Def_t *pSPIx);                                                      //DeInitialize the GPIO
/*
 * Flag Reset
 */
uint8_t SPI_GetFlagStatus(SPI_Reg_Def_t *pSPIx, uint8_t FlagName) ;
/*
 * Data read and write
 */
void SPI_SendData(SPI_Reg_Def_t *pSPIx, uint8_t *pTxBuffer, uint32_t len);
void SPI_ReceiveData(SPI_Reg_Def_t *pSPIx, uint8_t *pRxBuffer, uint32_t len);

/*
 * Interrupt Configuration
 */
//Enable and Disable Priority
void SPI_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi );
//Priroity Config
void SPI_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);

//IRQ Config , configuring priority,type of interrupt
void SPI_IRQHandling(uint8_t PinNumber);                                                                        //Whenever interrupt occurs , this function can be used to process the interrupt


























#endif /* INC_STM32F103XX_SPI_DRIVER_H_ */
