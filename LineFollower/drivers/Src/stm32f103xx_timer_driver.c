/*
 * stm32f103xx_timer_driver.c
 *
 *  Created on: 02-Feb-2026
 *      Author: yukta
 */

# include "stm32f103xx_timer_driver.h"



void Timer_PeripheralClock_Enable(TIMER_Reg_Def_t *pTIMx, uint8_t EnOrDi)
{
	if (EnOrDi == 1)
	{
		if (pTIMx == TIMER1)
		{
			TIMER1_PCLK_EN();

		}
		else if (pTIMx == TIMER2)
		{
			TIMER2_PCLK_EN();
		}
		else if (pTIMx == TIMER3)
		{
			TIMER3_PCLK_EN();
		}
		else if (pTIMx == TIMER4)
		{
			TIMER4_PCLK_EN();
		}
	}
	else
	{

		if (pTIMx == TIMER1)
		{
			TIMER1_PCLK_DI();

		}
		else if (pTIMx == TIMER2)
		{
			TIMER2_PCLK_DI();
		}
		else if (pTIMx == TIMER3)
		{
			TIMER3_PCLK_DI();
		}
		else if (pTIMx == TIMER4)
		{
			TIMER4_PCLK_DI();
		}

	}

}

void Timer_PWM_Init(PWM_Handle_t *pPWMHandle)
{
	uint16_t temp = 0;
	//Clock enable
	Timer_PeripheralClock_Enable(pPWMHandle->pTIMx,1);
	//Remap of timer pins

	if (pPWMHandle->PWM_PinConfig.RemapCtrl == 1)
	{


		if (pPWMHandle->pTIMx == TIMER2)
		{
			AFIO->AFIO_MAPR |= pPWMHandle->PWM_PinConfig.RemapVal << ALTFUNC_TIM2_REMAP;
		}

		else if (pPWMHandle->pTIMx == TIMER3)
		{
			AFIO->AFIO_MAPR |= pPWMHandle->PWM_PinConfig.RemapVal << ALTFUNC_TIM3_REMAP;
		}
		else if (pPWMHandle->pTIMx ==TIMER4)
		{
			AFIO->AFIO_MAPR |= pPWMHandle->PWM_PinConfig.RemapVal << ALTFUNC_TIM4_REMAP;
		}

	}

	uint8_t val = 0;
	//Load prescalar value
	pPWMHandle->pTIMx->TIM_PSC = pPWMHandle->PWM_PinConfig.PRESCL_val;


	//Load arr value
	pPWMHandle->pTIMx->TIM_ARR = pPWMHandle->PWM_PinConfig.ARR_val;

	//Enable OC_PE Bit and give PWM mode value
	if ((pPWMHandle->PWM_PinConfig.TIM_Chnl == TIM_CHNL_1 )||(pPWMHandle->PWM_PinConfig.TIM_Chnl == TIM_CHNL_2 ) )
	{
		val = 16 - (16 / pPWMHandle->PWM_PinConfig.TIM_Chnl);
		temp |= (1<< (val+3));
		temp |= (pPWMHandle->PWM_PinConfig.PWM_Mode <<(val + 4));
		pPWMHandle->pTIMx->TIM_CCMR1 |= temp;
	}
	else
	{

			val = 16 - (16 / (pPWMHandle->PWM_PinConfig.TIM_Chnl - 2 ));
			temp |= (1<< (val+3));
			temp |= (pPWMHandle->PWM_PinConfig.PWM_Mode <<(val + 4));
			pPWMHandle->pTIMx->TIM_CCMR2 = temp;

	}

	temp = 0;

	//Enable ARPE bit bit, dir bit
	temp |= 1 << TIMER_CR1_ARPE;
	if ((pPWMHandle->PWM_PinConfig.PWM_Mode == PWM_CMS_1)||(pPWMHandle->PWM_PinConfig.PWM_Mode == PWM_CMS_2)||(pPWMHandle->PWM_PinConfig.PWM_Mode == PWM_CMS_3))
	{
		temp |= pPWMHandle->PWM_PinConfig.PWM_Mode << TIMER_CR1_CMS;
	}
	pPWMHandle->pTIMx->TIM_CR1	|= temp;


	//Enable UG bit

		pPWMHandle->pTIMx->TIM_EGR = (1 << TIMER_EGR_UG);

		//Polarity

		if (pPWMHandle->PWM_PinConfig.TIM_Chnl == 1)
		{

			pPWMHandle->pTIMx->TIM_CCER |=(1 << TIMER_CCER_CC1E);
			pPWMHandle->pTIMx->TIM_CCER |=(pPWMHandle->PWM_PinConfig.PWM_pol << TIMER_CCER_CC1P);

		}
		else if (pPWMHandle->PWM_PinConfig.TIM_Chnl == 2)
		{
			pPWMHandle->pTIMx->TIM_CCER |=(1 << TIMER_CCER_CC2E);
			pPWMHandle->pTIMx->TIM_CCER |=(pPWMHandle->PWM_PinConfig.PWM_pol <<TIMER_CCER_CC2P);
		}
		else if (pPWMHandle->PWM_PinConfig.TIM_Chnl == 3)
		{
			pPWMHandle->pTIMx->TIM_CCER |= (1 <<TIMER_CCER_CC3E);
			pPWMHandle->pTIMx->TIM_CCER |=(pPWMHandle->PWM_PinConfig.PWM_pol <<TIMER_CCER_CC3P);
		}
		else if (pPWMHandle->PWM_PinConfig.TIM_Chnl == 4)
		{
			pPWMHandle->pTIMx->TIM_CCER |= (1 <<TIMER_CCER_CC4E);
			pPWMHandle->pTIMx->TIM_CCER |=(pPWMHandle->PWM_PinConfig.PWM_pol << TIMER_CCER_CC4P);
		}

		//Enter cnt val
		pPWMHandle->pTIMx->TIM_CNT |= pPWMHandle->PWM_PinConfig.CNT_val;

		pPWMHandle->pTIMx->TIM_CR1 |= 1 << TIMER_CR1_CEN;


}

void Timer_PWM_DutyCycle(TIMER_Reg_Def_t *pTIMx, uint16_t DutyCycleVal, uint8_t Tim_Chnl)
{


		if (Tim_Chnl == 1)
		{
			pTIMx->TIM_CCR1 = DutyCycleVal;

		}
		else if (Tim_Chnl == 2)
		{
			pTIMx->TIM_CCR2 = DutyCycleVal;

		}
		else if (Tim_Chnl == 3)
		{
			pTIMx->TIM_CCR3 = DutyCycleVal;
		}
		else if (Tim_Chnl == 4)
		{
			pTIMx->TIM_CCR4 = DutyCycleVal;
		}

}


