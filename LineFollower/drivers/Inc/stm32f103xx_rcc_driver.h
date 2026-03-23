/*
 * stm32f103xx_rcc_driver.h
 *
 *  Created on: 24-Dec-2025
 *      Author: yukta
 */

#ifndef INC_STM32F103XX_RCC_DRIVER_H_
#define INC_STM32F103XX_RCC_DRIVER_H_


#include "stm32f103xx.h"

uint32_t RCC_GetPCLK1Value(void);
uint32_t RCC_GetPCLK2Value(void);
uint32_t RCC_PLLValue(void);


#endif /* INC_STM32F103XX_RCC_DRIVER_H_ */
