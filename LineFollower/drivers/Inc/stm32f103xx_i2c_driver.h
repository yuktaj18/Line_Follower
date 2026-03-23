/*
 * stm32f103xx_i2c_driver.h
 *
 *  Created on: 23-Dec-2025
 *      Author: yukta
 */

#ifndef INC_STM32F103XX_I2C_DRIVER_H_
#define INC_STM32F103XX_I2C_DRIVER_H_

#include "stm32f103xx.h"



/*
 * I2C Reg Bit definations
 */
//CR1

#define I2C_CR1_PE				0
#define I2C_CR1_NOSTRETCH		7
#define I2C_CR1_START			8
#define I2C_CR1_STOP			9
#define I2C_CR1_ACK				10
#define I2C_CR1_SWRST			15

//CR2
#define I2C_CR2_FREQ			0
#define I2C_CR2_ITERREN			8
#define I2C_CR2_ITEVTEN			9
#define I2C_CR2_ITBUFEN			10

//SR1
#define I2C_SR1_SB				0
#define I2C_SR1_ADDR			1
#define I2C_SR1_BTF				2
#define I2C_SR1_ADD10			3
#define I2C_SR1_STOPF			4
#define I2C_SR1_RXNE			6
#define I2C_SR1_TXE				7
#define I2C_SR1_BERR			8
#define I2C_SR1_ARLO			9
#define I2C_SR1_AF				10
#define I2C_SR1_OVR				11
#define I2C_SR1_PECERR			12
#define I2C_SR1_TIMEOUT			14

//SR2
#define I2C_SR2_MSL				0
#define I2C_SR2_BUSY			1
#define I2C_SR2_TRA				2
#define I2C_SR2_GENCALL			4
#define I2C_SR2_DUALF			7
#define I2C_SR2_PEC				8

//OAR1
#define I2C_OAR1_ADD0			0
#define I2C_OAR1_ADD_1_7		1
#define I2C_OAR1_ADD_8_9		8
#define I2C_OAR1_ADDMODE		15

//OAR2
#define I2C_OAR2_ENDUAL			0
#define I2C_OAR2_ADD2			1


//CCR
#define I2C_CCR_CCR				0
#define I2C_CCR_DUTY			14
#define I2C_CCR_F_S				15


typedef struct
{
	uint32_t I2C_SCLSpeed;
	uint8_t  I2C_DeviceAddress;
	uint8_t	 I2C_ACKControl;
	uint16_t I2C_FMDutyCycle;
	uint8_t  I2C_ReMap;

}I2C_Config_t;

typedef struct
{

	I2C_Reg_Def_t *pI2Cx;
	I2C_Config_t I2C_Config;

}I2C_Handle_t;


/*
 * I2C SCLSpeed
 */
#define I2C_SCLSpeed_STD	100000
#define I2C_SCLSpeed_FM_4K	400000
#define I2C_SCLSpeed_FM_2K	200000

/*
 * I2C_ACKControl
 */
#define I2C_ACK_EN			1
#define I2C_ACK_DI			0


/*
 * I2C_FMDutyCycle
 */
#define I2C_FM_DUTY_2		0
#define I2C_FM_DUTY_16_9	1

/*
 * I2C FLag
 */
#define I2C_SR1_SB_FLAG			(1 << I2C_SR1_SB)
#define I2C_SR1_ADDR_FLAG		(1 << I2C_SR1_ADDR)
#define I2C_SR1_BTF_FLAG		(1 << I2C_SR1_BTF)
#define I2C_SR1_STOPF_FLAG		(1 << I2C_SR1_STOPF)
#define I2C_SR1_RXNE_FLAG		(1 << I2C_SR1_RXNE)
#define I2C_SR1_TXE_FLAG		(1 << I2C_SR1_TXE)
#define I2C_SR1_BERR_FLAG		(1 << I2C_SR1_BERR)
#define I2C_SR1_ARLO_FLAG		(1 << I2C_SR1_ARLO)
#define I2C_SR1_AF_FLAG			(1 << I2C_SR1_AF)
#define I2C_SR1_OVR_FLAG		(1 << I2C_SR1_OVR)
#define I2C_SR1_TIMEOUT_FLAG	(1 << I2C_SR1_TIMEOUT)
#define I2C_SR2_MSL_FLAG		(1 << I2C_SR2_MSL)
/**************************************************************************************************************************

                           API for users to work with GPIO

 ***************************************************************************************************************************/

/*
 * I2C clock setup
 */
void I2C_PeriClockControl(I2C_Reg_Def_t *pI2Cx, uint8_t EnorDi);                              //Enable the GPIO clk
void EnableI2C(I2C_Reg_Def_t *pI2Cx, uint8_t EnorDi);
void Enable_SWRST(I2C_Reg_Def_t *pI2Cx, uint8_t EnorDi);
void EnableACK(I2C_Reg_Def_t *pI2Cx, uint8_t EnorDi);
/*
 * I2C initializtion
 */
void I2C_Init(I2C_Handle_t *pI2CHandle);                                                    //Initalize the gpio
void I2C_DeInit(I2C_Reg_Def_t *pI2Cx);                                                      //DeInitialize the GPIO
/*
 * I2C SEND and RCEIVE DATA
 */

void I2C_MasterSendData(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uint8_t len,uint8_t SlaveAddr);
void I2C_MasterOneByteSendMem(I2C_Handle_t *pI2CHandle,uint8_t *pTxBuffer,uint8_t SlaveAddress,uint8_t maddress);
void I2C_MasterReceiveData_OneByteMem(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer,uint8_t SlaveAddress,uint8_t maddress);
void I2C_MasterReceiveData_MultiByteMem(I2C_Handle_t *pI2CHandle,uint8_t *pRxBuffer,uint8_t SlaveAddress,uint8_t madress,uint8_t len);


/*
 * Flag Reset
 */
uint8_t I2C_GetFlagStatus(I2C_Reg_Def_t *pI2Cx, uint8_t FlagName) ;


#endif /* INC_STM32F103XX_I2C_DRIVER_H_ */
