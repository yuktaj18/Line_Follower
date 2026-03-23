/*
 * stm32f103xx_rcc_driver.c
 *
 *  Created on: 24-Dec-2025
 *      Author: yukta
 */

#include "stm32f103xx_rcc_driver.h"

//AHB_Prescaler
uint16_t AHB_PreScaler[8]={2,4,8,16,64,128,256,512};
//APB1_Prescaler
uint16_t APB1_PreScaler[4]={2,4,8,16};
//APB2_Prescaler
uint16_t APB2_PreScaler[4]={2,4,8,16};

/*
 * RCC Clock value
 */
uint32_t RCC_PLLValue(void)
{
	uint32_t pllValue =0;
	return pllValue;
}


uint32_t RCC_GetPCLK1Value(void)
{
	uint32_t pclk1,SystemClk;
	uint8_t clksrc,temp,ahbp,apb1p;
//which clk source is used
	clksrc = ((RCC->RCC_CFGR >> 2)&0x3);

	if (clksrc == 0 )
	{
		SystemClk = 8000000;
	}
	else if (clksrc == 1 )
	{
		SystemClk = 16000000;
	}
	else if (clksrc == 2 )
	{
		SystemClk = RCC_PLLValue();
	}
//What is the ahb prescaler
	temp = ((RCC->RCC_CFGR >> 2)& 0xF);
	if (temp < 8)
	{
		ahbp = 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp-8];
	}
	temp=0;
//What is the apb1 prescaler
	temp = ((RCC->RCC_CFGR >> 8)& 0x7);
		if (temp < 4)
		{
			apb1p = 1;
		}
		else
		{
			apb1p = APB1_PreScaler[temp-4];
		}

		pclk1 = ((SystemClk/ahbp)/apb1p);


	return pclk1;
}




uint32_t RCC_GetPCLK2Value(void)
{
	uint32_t pclk2,SystemClk;
	uint8_t clksrc,temp,ahbp,apb2p;
//which clk source is used
	clksrc = ((RCC->RCC_CFGR >> 2)&0x3);

	if (clksrc == 0 )
	{
		SystemClk = 8000000;
	}
	else if (clksrc == 1 )
	{
		SystemClk = 16000000;
	}
	else if (clksrc == 2 )
	{
		SystemClk = RCC_PLLValue();
	}
//What is the ahb prescaler
	temp = ((RCC->RCC_CFGR >> 2)& 0xF);
	if (temp < 8)
	{
		ahbp = 1;
	}
	else
	{
		ahbp = AHB_PreScaler[temp-8];
	}
	temp=0;
//What is the apb2 prescaler
	temp = ((RCC->RCC_CFGR >> 11)& 0x7);
		if (temp < 4)
		{
			apb2p = 1;
		}
		else
		{
			apb2p = APB2_PreScaler[temp-4];
		}

		pclk2 = ((SystemClk / ahbp)/apb2p);


	return pclk2;
}
