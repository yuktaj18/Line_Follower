/*
 * stm32f103xx_timer_driver.h
 *
 *  Created on: 02-Feb-2026
 *      Author: yukta
 */


#ifndef INC_STM32F103XX_TIMER_DRIVER_H_
#define INC_STM32F103XX_TIMER_DRIVER_H_

# include "stm32f103xx.h"



#define TIM_CHNL_1		  1
#define TIM_CHNL_2		  2
#define	TIM_CHNL_3		  3
#define	TIM_CHNL_4	  	  4

#define PWM_CMS_1		  0b01
#define PWM_CMS_2		  0b10
#define	PWM_CMS_3		  0b11


/*
 * Timer peripheral bits
 */

//CR1
# define TIMER_CR1_CEN		0
# define TIMER_CR1_DIR		4
# define TIMER_CR1_CMS		5
# define TIMER_CR1_ARPE		7

//EGR
# define TIMER_EGR_UG		0
//CCER
# define TIMER__CCER_CC1NP	3
# define TIMER_CCER_CC1NE	2
# define TIMER_CCER_CC1P	1
# define TIMER_CCER_CC1E	0
# define TIMER_CCER_CC2NP	7
# define TIMER_CCER_CC2NE	6
# define TIMER_CCER_CC2P	5
# define TIMER_CCER_CC2E	4
# define TIMER_CCER_CC3NP	11
# define TIMER_CCER_CC3NE	10
# define TIMER_CCER_CC3P	9
# define TIMER_CCER_CC3E	8
# define TIMER_CCER_CC4P	13
# define TIMER_CCER_CC4E	12
# define TIMER_CCER_CC4NP	15






typedef struct
{

 uint16_t ARR_val;
 uint16_t PRESCL_val;
 uint16_t CNT_val;
 uint8_t PWM_Mode;
 uint8_t PWM_pol;
 uint8_t TIM_Chnl;
 uint8_t RemapCtrl;
 uint8_t RemapVal;


}Pwm_PinConfig_t;

typedef struct
{
	TIMER_Reg_Def_t *pTIMx;
	Pwm_PinConfig_t  PWM_PinConfig;


}PWM_Handle_t;


/*
 * Function declaration
 */

void Timer_PeripheralClock_Enable(TIMER_Reg_Def_t *pTIMx,uint8_t EnOrDi);
void Timer_PWM_Init(PWM_Handle_t *pPWMHandle);
void Timer_PWM_DutyCycle(TIMER_Reg_Def_t *pTIMx, uint16_t DutyCycleVal, uint8_t Tim_Chnl);


#endif /* INC_STM32F103XX_TIMER_DRIVER_H_ */
