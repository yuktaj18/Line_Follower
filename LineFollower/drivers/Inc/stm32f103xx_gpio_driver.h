/*
 * stm32f103xx_gpio_driver.h
 *
 *  Created on: Oct 25, 2025
 *      Author: Dell
 */

#ifndef INC_STM32F103XX_GPIO_DRIVER_H_
#define INC_STM32F103XX_GPIO_DRIVER_H_

#include "stm32f103xx.h"


/*
 * Pin Config for gpio pin
 */

typedef struct
	{

	uint8_t GPIO_PinNumber;
	uint8_t GPIO_PinMode;
	uint8_t GPIO_AFIOControl;
	uint8_t GPIO_PinPuPdControl;
	uint8_t GPIO_InterruptMode;

	}GPIO_PinConfig_t;

typedef struct
	{
		uint8_t AFIO_PinAltFunModeControl;
		uint8_t AFIO_PinAltFunModePort;
		uint8_t AFIO_PinAltFunModePinNumber;

	}AFIO_PinConfig_t;


/*
 * Handle structure for gpio pin
 */
typedef struct
	{
		GPIO_RegDef_t *pGPIOx;
		GPIO_PinConfig_t GPIO_PinConfig;

	} GPIO_Handle_t;

typedef struct
		{
			AFIO_Reg_Def_t *pAFIO;
			AFIO_PinConfig_t AFIO_PinConfig;

		} AFIO_Handle_t;

/*
 * GPIO Pin Numbers
 */

#define GPIO_PIN_NO_0 				 0
#define GPIO_PIN_NO_1				 1
#define GPIO_PIN_NO_2				 2
#define GPIO_PIN_NO_3				 3
#define GPIO_PIN_NO_4				 4
#define GPIO_PIN_NO_5				 5
#define GPIO_PIN_NO_6				 6
#define GPIO_PIN_NO_7				 7
#define GPIO_PIN_NO_8				 8
#define GPIO_PIN_NO_9				 9
#define GPIO_PIN_NO_10				 10
#define GPIO_PIN_NO_11				 11
#define GPIO_PIN_NO_12				 12
#define GPIO_PIN_NO_13				 13
#define GPIO_PIN_NO_14				 14
#define GPIO_PIN_NO_15				 15

/*
 * GPIO Possible modes
 */
//Input Mode
#define GPIO_MODE_IN_Analog   					0b0000
#define GPIO_MODE_IN_Float 						0b0100
#define GPIO_MODE_IN_PullUpDwn 					0b1000

//Output Mode
#define GPIO_MODE_OUT_PushPull					0b0010     //Output speed is 2 Mhz
#define GPIO_MODE_OUT_OpenDrain					0b0110
//Alternate Function Mode
#define GPIO_MODE_ALTFUN_PushPull				0b1011
#define GPIO_MODE_ALTFUN_OpenDrain				0b1111

// For Pull Up Pull Down we need to configure Px_ODR register also
#define GPIO_PinPullUp_ODR						1
#define GPIO_PinPullDown_ODR					0

// Interrupt Mode
#define GPIO_MODE_INT_FT						4
#define GPIO_MODE_INT_RT						5
#define GPIO_MODE_INT_FRT						6

/*
 * AFIO GPIO Port
*/

#define PORTA                 0
#define PORTB				  1
#define PORTC			      2
#define PORTD			      3
#define PORTE                 4

/*
* ALTFUNC_MapReg
*/
#define ALTFUNC_MapReg1		  1
#define	ALTFUNC_MapReg2		  2

/*
 * AFIO Register Remap Bit Shift
 */

#define ALTFUNC_SPI1_REMAP							0
#define ALTFUNC_I2C1__REMAP							1
#define ALTFUNC_USART1_REMAP						2
#define ALTFUNC_USART2_REMAP						3
#define ALTFUNC_USART3__REMAP						4
#define ALTFUNC_TIM1_REMAP							6
#define ALTFUNC_TIM2_REMAP							8
#define ALTFUNC_TIM3_REMAP							10
#define ALTFUNC_TIM4_REMAP							12
#define ALTFUNC_CAN1_REMAP							13
#define ALTFUNC_PD01_REMAP							15
#define ALTFUNC_TIM5CH4_REMAP						16
#define ALTFUNC_ETH_REMAP							21
#define ALTFUNC_CAN2_REMAP							22
#define ALTFUNC_MII_RMII_SEL_REMAP					23
#define ALTFUNC_SWJ_CFG_REMAP						24
#define ALTFUNC_SPI3_REMAP							28
#define ALTFUNC_TIM2ITR1_IREMAP						29
#define ALTFUNC_PTP_PPS_REMAP						30


//Add mapr2 reg












/**************************************************************************************************************************

                           API for users to work with GPIO

 ***************************************************************************************************************************/

/*
 * Gpio clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi);                              //Enable the GPIO clk
void PwrEn(void);

/*
 * Gpio initializtion
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle);                                                    //Initalize the gpio
void GPIO_DeInit(GPIO_RegDef_t *pGPIOx);                                                      //DeInitialize the GPIO


/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);	                    //Read from a input pin of a gpio port
uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx);	                                       //Read from a the whole port of the gpio
void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx,uint8_t PinNumber,uint8_t Value);            //Write to output pin of the gpio
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx,uint16_t Value);                            //Write to output port of the gpio
void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber);                                //Toggle output pin

/*
 * Interrupt Configuration
 */
//Enable and Disable Priority
void GPIO_IRQInterruptConfig(uint8_t IRQNumber,uint8_t EnorDi );
//Priroity Config
void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority);

//IRQ Config , configuring priority,type of interrupt
void GPIO_IRQHandling(uint8_t PinNumber);                                                                        //Whenever interrupt occurs , this function can be used to process the interrupt




#endif /* INC_STM32F103XX_GPIO_DRIVER_H_ */
