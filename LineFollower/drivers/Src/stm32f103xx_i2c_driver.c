/*
 * stm32f1xx_i2c_driver.c
 *
 *  Created on: 23-Dec-2025
 *      Author: yukta
 */

#include "stm32f103xx_i2c_driver.h"
#include "stm32f103xx_rcc_driver.h"

static void I2C_GenerateStartCondition(I2C_Reg_Def_t *pI2Cx);
static void I2C_ExecuteAddressPhaseMasterWrite(I2C_Reg_Def_t *pI2Cx, uint8_t SlaveAddr);
static void I2C_GenerateStopCondition(I2C_Reg_Def_t *pI2Cx);
static void delay(void);

uint32_t dummyRead = 0;
uint8_t temp = 0;

static void delay()
{

	for(uint32_t i = 0 ; i < 500000/2 ; i ++);


}

static void I2C_GenerateStartCondition(I2C_Reg_Def_t *pI2Cx)
{
	pI2Cx->I2C_CR1 |=(1<< I2C_CR1_START);

	while(!(I2C_GetFlagStatus(pI2Cx, I2C_SR1_SB_FLAG)));

	dummyRead = pI2Cx->I2C_SR1;
	(void)dummyRead;



}

static void I2C_ExecuteAddressPhaseMasterWrite(I2C_Reg_Def_t *pI2Cx, uint8_t SlaveAddr)
{
	temp = SlaveAddr;
	temp = (temp<<1)|0x00;
	SlaveAddr = temp ;

	pI2Cx->I2C_DR = SlaveAddr;

	while(!(I2C_GetFlagStatus(pI2Cx, I2C_SR1_ADDR_FLAG)));

	 dummyRead = pI2Cx->I2C_SR1;
	 dummyRead = pI2Cx->I2C_SR2;
	(void)dummyRead;

}


static void I2C_GenerateStopCondition(I2C_Reg_Def_t *pI2Cx)
{


	pI2Cx->I2C_CR1 |=(1<< I2C_CR1_STOP);


}

/*
 * I2C Clock Ctrl
 */
void I2C_PeriClockControl(I2C_Reg_Def_t *pI2Cx, uint8_t EnorDi)
{


	 if ( EnorDi == ENABLE)
	 	 {
		 	 if (pI2Cx == I2C_1)
		 	 {
		 		I2C1_PCLK_EN();
		 	 }
		 	 else if (pI2Cx == I2C_2)
		 	 {
		 		I2C2_PCLK_EN();
		 	 }



	 	 }
	 else
	 {
		 	 	 if (pI2Cx == I2C_1)
		 	 	 {
		 	 		I2C1_PCLK_DI();
		 	 	 }
		 	 	 else if (pI2Cx == I2C_2)
		 	 	 {
		 	 		I2C2_PCLK_DI();
		 	 	 }

	 }
}




/*
 * I2C Peripheral Control
 */
void EnableI2C(I2C_Reg_Def_t *pI2Cx, uint8_t EnorDi){


		 if ( EnorDi == ENABLE)
			 	 {
				 	 pI2Cx->I2C_CR1 |= (1 << I2C_CR1_PE);
			 	 }
			 else
			 {
				 pI2Cx->I2C_CR1 &= ~(1 << I2C_CR1_PE);

			 }

	 }
void EnableACK(I2C_Reg_Def_t *pI2Cx, uint8_t EnorDi){


		 if ( EnorDi == ENABLE)
			 	 {
				 	 pI2Cx->I2C_CR1 |= (1 << I2C_CR1_ACK);
			 	 }
			 else
			 {
				 pI2Cx->I2C_CR1 &= ~(1 << I2C_CR1_ACK);

			 }

	 }
/*
 * I2C SWRST Bit
 */
/*
 * I2C Peripheral Control
 */
void Enable_SWRST(I2C_Reg_Def_t *pI2Cx, uint8_t EnorDi){


		 if ( EnorDi == ENABLE)
			 	 {
				 	 pI2Cx->I2C_CR1 |= (1 << I2C_CR1_SWRST);
			 	 }
			 else
			 {
				 pI2Cx->I2C_CR1 &= ~(1 << I2C_CR1_SWRST);

			 }

	 }

/*
 * I2C Initialization
 *
 */

void I2C_Init(I2C_Handle_t *pI2CHandle)
{
	uint32_t temp =0;

	//I2C ReMap Pins

	if(pI2CHandle->I2C_Config.I2C_ReMap == SET)
	{
				 AFIO->AFIO_MAPR |= (1<<1);

	}

	//Reset I2C peripheral
	Enable_SWRST(pI2CHandle->pI2Cx,SET);

	Enable_SWRST(pI2CHandle->pI2Cx,RESET);


	//Clock enable
	I2C_PeriClockControl(pI2CHandle->pI2Cx,1);

	// Freq of CR2
	temp |= (RCC_GetPCLK1Value()/1000000U);
	pI2CHandle->pI2Cx->I2C_CR2 = (temp & 0x3F);
	temp = 0;
	//program the device own address
	//14 bit should be set
	temp |= (1 << 14) ;
	temp |= pI2CHandle->I2C_Config.I2C_DeviceAddress << 1;
	pI2CHandle->pI2Cx->I2C_OAR1 |= temp;

	//CCR calculation
	uint16_t ccr_value = 0;
	temp = 0;
	if(pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCLSpeed_STD)
	{
		// mode is standrad mode
		//Configure mode
		temp |= (0 << I2C_CCR_F_S);
		ccr_value = (RCC_GetPCLK1Value() /(2 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		temp |= (ccr_value & 0xFFF);
	}
	else
	{
		// mode is fast
		//Configure mode
		temp |= (1 << I2C_CCR_F_S);
		temp |= (pI2CHandle->I2C_Config.I2C_FMDutyCycle << I2C_CCR_DUTY );
		if (pI2CHandle->I2C_Config.I2C_FMDutyCycle == I2C_FM_DUTY_2)
		{
			ccr_value = (RCC_GetPCLK1Value() /(3 * pI2CHandle->I2C_Config.I2C_SCLSpeed));


		}
		else
		{
			ccr_value = (RCC_GetPCLK1Value() /(25 * pI2CHandle->I2C_Config.I2C_SCLSpeed));
		}
		temp |= (ccr_value & 0xFFF);

	}
	pI2CHandle->pI2Cx->I2C_CCR |= temp;
	temp = 0;

	//Trise Calculation
	if (pI2CHandle->I2C_Config.I2C_SCLSpeed <= I2C_SCLSpeed_STD)
	{
		//mode is standard mode
		temp = ((RCC_GetPCLK1Value() / 1000000U)+1);
	}
	else
	{

		//mode is fast mode
		temp = (((RCC_GetPCLK1Value() * 300) / 1000000000U)+1);

	}
	pI2CHandle->pI2Cx->I2C_TRISE &=(0<<6);
	pI2CHandle->pI2Cx->I2C_TRISE |= (temp & 0x3F);


}

/*
 * I2C Reset
 */
void I2C_DeInit(I2C_Reg_Def_t *pI2Cx)
{

			 	 if (pI2Cx == I2C_1)
			 	 {
			 		I2C1_Reg_Reset();
			 	 }
			 	 else
			 	 {
			 		I2C2_Reg_Reset();
			 	 }


}

/*
 * I2C Send Data and Recieve
 */
void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uint8_t len,uint8_t SlaveAddress)
{

	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//SEnd the address of slave with read/write bit
	I2C_ExecuteAddressPhaseMasterWrite(pI2CHandle->pI2Cx,SlaveAddress);

	//Send Data

	while(len > 0)
	{
		while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_TXE_FLAG) );
		pI2CHandle->pI2Cx->I2C_DR = *pTxBuffer;
		pTxBuffer++;
		len--;


	}
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_BTF_FLAG) );

	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);





}

//I2C write byte one byte
void I2C_MasterOneByteSendMem(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uint8_t SlaveAddress,uint8_t maddress)
{

	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//SEnd the address of slave with read/write bit
	I2C_ExecuteAddressPhaseMasterWrite(pI2CHandle->pI2Cx,SlaveAddress);
	//Send Reg Address
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_TXE_FLAG) );
	pI2CHandle->pI2Cx->I2C_DR = maddress;

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_BTF_FLAG) );
	//Start
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//SEnd the address of slave with read/write bit
	I2C_ExecuteAddressPhaseMasterWrite(pI2CHandle->pI2Cx,SlaveAddress);
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_TXE_FLAG) );

	pI2CHandle->pI2Cx->I2C_DR = *pTxBuffer;

	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_BTF_FLAG));
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

}

//Receive one byte

void I2C_MasterReceiveData_OneByteMem(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer,uint8_t SlaveAddress,uint8_t maddress)
{

	//Generate Start
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

	//SEnd the address of slave with read/write bit
	I2C_ExecuteAddressPhaseMasterWrite(pI2CHandle->pI2Cx,SlaveAddress);

	//Wait for TXE and and write reg address to read from
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_TXE_FLAG) );
	pI2CHandle->pI2Cx->I2C_DR = maddress;

	//Check for BTF flag
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_BTF_FLAG) );


//Generate Start
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);

//Send slave address with 1 bit for read
	I2C_ExecuteAddressPhaseMasterRead(pI2CHandle->pI2Cx,SlaveAddress);

//Disable ACK
	EnableACK(pI2CHandle->pI2Cx,0);

//Generate Stop Condition
	I2C_GenerateStopCondition(pI2CHandle->pI2Cx);

//Check rxne flag
	while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_RXNE_FLAG));

//Store the dr value in buffer

	*pRxBuffer = pI2CHandle->pI2Cx->I2C_DR;



}




//Read Multi Byte

void I2C_MasterReceiveData_MultiByteMem(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer,uint8_t SlaveAddress,uint8_t madress,uint8_t len)
{
	//Generate Start Condition
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
	//Send slave Address to write
	I2C_ExecuteAddressPhaseMasterWrite(pI2CHandle->pI2Cx,SlaveAddress);
	delay();
	//Send Register Address
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_TXE_FLAG) );
	pI2CHandle->pI2Cx->I2C_DR = madress;
	while(! I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_BTF_FLAG) );
	//Recive the data
	//Send Repeated Start
	I2C_GenerateStartCondition(pI2CHandle->pI2Cx);
	//Send slave Address for read
	I2C_ExecuteAddressPhaseMasterRead(pI2CHandle->pI2Cx,SlaveAddress);
	//Enable ACK
	EnableACK(pI2CHandle->pI2Cx, 1);

	while (len>0)
	{

		if (len == 1)
		{
			//Disable ACK
			EnableACK(pI2CHandle->pI2Cx, 0);
			//Generate Stop Condition
			I2C_GenerateStopCondition(pI2CHandle->pI2Cx);
			//Wait Until RXNE is set
			while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_RXNE_FLAG));

			*pRxBuffer = pI2CHandle->pI2Cx->I2C_DR ;

			break;


		}

		else
		{
			//Wait Until RXNE is set
			while(!I2C_GetFlagStatus(pI2CHandle->pI2Cx,I2C_SR1_RXNE_FLAG));
			*pRxBuffer = pI2CHandle->pI2Cx->I2C_DR ;
			pRxBuffer++;
			len--;

		}

	}

}


uint8_t I2C_GetFlagStatus(I2C_Reg_Def_t *pI2Cx, uint8_t FlagName)
{

	if (pI2Cx->I2C_SR1 & FlagName)
	{
		return FlagSet;
	}
	return FlagReset;

}




