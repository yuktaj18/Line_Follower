/*
 * stm32f103xx_gpio_driver.c
 *
 *  Created on: Oct 25, 2025
 *      Author: Dell
 */

#include "stm32f103xx_gpio_driver.h"

/*
 * Gpio clock setup
 */
void GPIO_PeriClockControl(GPIO_RegDef_t *pGPIOx, uint8_t EnorDi) {
	if (EnorDi == ENABLE) {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_EN();
		} else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_EN();
		} else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_EN();
		} else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_EN();
		} else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_EN();
		}


	} else {
		if (pGPIOx == GPIOA) {
			GPIOA_PCLK_DI();
		} else if (pGPIOx == GPIOB) {
			GPIOB_PCLK_DI();
		} else if (pGPIOx == GPIOC) {
			GPIOC_PCLK_DI();
		} else if (pGPIOx == GPIOD) {
			GPIOD_PCLK_DI();
		} else if (pGPIOx == GPIOE) {
			GPIOE_PCLK_DI();
		}

	}

}
void PwrEn(void)
{
	PWR_EN();
}

/*
 * Gpio initializtion
 */
void GPIO_Init(GPIO_Handle_t *pGPIOHandle) {
	//PWR enable
	PwrEn();
	//Clock Enable
	GPIO_PeriClockControl(pGPIOHandle->pGPIOx,ENABLE);

	//AFIO
		if (pGPIOHandle->GPIO_PinConfig.GPIO_AFIOControl == 1)
			{
					AFIO_PCLK_EN();
			}


	uint32_t temp = 0;



	if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7) {
		// here for pin number greater than 7 we will be using GPIO_CRL
		pGPIOHandle->pGPIOx->GPIO_CRL &= ~(0xF << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)));
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)));
		pGPIOHandle->pGPIOx->GPIO_CRL |= temp;
		temp = 0;

	} else {
		// here for pin number greater than 7 we will be using GPIO_CRH
		temp = (pGPIOHandle->GPIO_PinConfig.GPIO_PinMode)<< (4 * ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) - 8));
		pGPIOHandle->pGPIOx->GPIO_CRH &= ~(0xF<< (4 * ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) - 8)));
		pGPIOHandle->pGPIOx->GPIO_CRH |= temp;
		temp = 0;

	}
	//Interrupt Mode

			if ((pGPIOHandle->GPIO_PinConfig.GPIO_InterruptMode == GPIO_MODE_INT_FT) || (pGPIOHandle->GPIO_PinConfig.GPIO_InterruptMode == GPIO_MODE_INT_RT) ||( pGPIOHandle->GPIO_PinConfig.GPIO_InterruptMode ==GPIO_MODE_INT_FRT))
			{

				//Configure EXTI Register in AFIO
				uint16_t temp3 = 0;
				uint16_t port = GPIO_BASEADDR_TO_CODE (pGPIOHandle->pGPIOx);

				//Configuring pin
				if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 3)

				{
					temp3 = (port) << (4 * (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
					AFIO->AFIO_EXTICR1 |= temp3;
					temp3 = 0;
				}
				else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 7)
				{
					temp3 = (port)<< (4 * ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) - 4));
					AFIO->AFIO_EXTICR2 |= temp3;
					temp3 = 0;
				}
				else if (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber <= 11)
				{

					temp3 = (port) << (4 * ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber) - 8));
					AFIO->AFIO_EXTICR3 |= temp3;
					temp3 = 0;
				} else
				{

					temp3 = (port)<< (4* ((pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber)- 11));
					AFIO->AFIO_EXTICR4 |= temp3;
					temp3 = 0;

				}
				//Configure Interrupt Triggering Type
				if (pGPIOHandle->GPIO_PinConfig.GPIO_InterruptMode == GPIO_MODE_INT_FT)
				{

					EXTI->EXTI_FTSR |= (1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
					EXTI->EXTI_RTSR &= ~(1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
				}
				else if (pGPIOHandle->GPIO_PinConfig.GPIO_InterruptMode == GPIO_MODE_INT_RT)
				{
					EXTI->EXTI_RTSR |= (1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
					EXTI->EXTI_FTSR &= ~(1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
				}
				else if (pGPIOHandle->GPIO_PinConfig.GPIO_InterruptMode == GPIO_MODE_INT_FRT)
				{
					EXTI->EXTI_FTSR |= (1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
					EXTI->EXTI_RTSR |= (1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
				}

				// Configure Interrupt Mask Register
				EXTI->EXTI_IMR |= (1 << (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));

			}

//PullUp and PullDown

	if ((pGPIOHandle->GPIO_PinConfig.GPIO_PinMode == GPIO_MODE_IN_PullUpDwn) ) {
		uint16_t temp2 = 0;
		temp2 = ((pGPIOHandle->GPIO_PinConfig.GPIO_PinPuPdControl)<< (pGPIOHandle->GPIO_PinConfig.GPIO_PinNumber));
		pGPIOHandle->pGPIOx->GPIO_ODR |= temp2;
		temp2 = 0;

	}

}

void GPIO_DeInit(GPIO_RegDef_t *pGPIOx)

{
	if (pGPIOx == GPIOA) {
		GPIOA_Reg_Reset();
	} else if (pGPIOx == GPIOB) {
		GPIOB_Reg_Reset();
	} else if (pGPIOx == GPIOC) {
		GPIOC_Reg_Reset();
	} else if (pGPIOx == GPIOD) {
		GPIOD_Reg_Reset();
	} else if (pGPIOx == GPIOE) {
		GPIOE_Reg_Reset();
	}

}


/*
 * Data read and write
 */
uint8_t GPIO_ReadFromInputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {

	uint8_t value = 0;
	value = (uint8_t) ((pGPIOx->GPIO_IDR >> PinNumber) & 0x00000001);

	return value;
}

uint16_t GPIO_ReadFromInputPort(GPIO_RegDef_t *pGPIOx) {
	uint16_t value = 0;
	value = (uint16_t) (pGPIOx->GPIO_IDR);

	return value;
}

void GPIO_WriteToOutputPin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber,
		uint8_t Value) {

	if (Value == GPIO_PIN_SET) {
		pGPIOx->GPIO_ODR |= (1 << PinNumber);
	} else {
		pGPIOx->GPIO_ODR &= ~(1 << PinNumber);
	}
}
void GPIO_WriteToOutputPort(GPIO_RegDef_t *pGPIOx, uint16_t Value) {

	 pGPIOx->GPIO_ODR = Value;
}

void GPIO_TogglePin(GPIO_RegDef_t *pGPIOx, uint8_t PinNumber) {

	pGPIOx->GPIO_ODR = pGPIOx->GPIO_ODR ^ (1 << PinNumber);
}
/*
 * Interrupt Configuration
 */
void GPIO_IRQInterruptConfig(uint8_t IRQNumber, uint8_t EnorDi)
{

	if (EnorDi == ENABLE)
		{

			if (IRQNumber <= 31)
			   {
					//Program ISER0 Reg
					*NVIC_ISER0_BASEADDR |= (1<<IRQNumber);
			   }
			else if (IRQNumber> 31 && IRQNumber < 64)
				{
					//Program ISER1 Reg
					*NVIC_ISER1_BASEADDR |= (1<<(IRQNumber % 32));
				}
			}
	else
		{

			if (IRQNumber <= 31)
				{
					//Program ICER1 Reg
					*NVIC_ICER0_BASEADDR |= (1<<IRQNumber);
				}
			else if (IRQNumber> 31 && IRQNumber < 64)
				{
					//Program ICER1 Reg
					*NVIC_ICER1_BASEADDR |= (1<<(IRQNumber % 32));
				}


		}

}

void GPIO_IRQPriorityConfig(uint8_t IRQNumber,uint8_t IRQPriority)
{
	//Find IRQ Reg

	uint8_t iprx = IRQNumber / 4;
	uint8_t iprx_section = IRQNumber % 4;
    uint8_t shift =  (8*iprx_section) + (8-NO_PR_BITS_ALLOCATED) ;
	*(NVIC_IPR0_BASEADDR + (iprx)) |=  (IRQPriority << shift);



}

void GPIO_IRQHandling(uint8_t PinNumber)
{

	//clear the exti pr register corresponding bit

	if (EXTI ->EXTI_PR & (1 << PinNumber))
		{
			//clear
			EXTI->EXTI_PR |=(1 << PinNumber);
		}


}
