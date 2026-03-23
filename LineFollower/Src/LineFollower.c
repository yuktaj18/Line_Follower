/*
 * LineFollower.c
 *
 *  Created on: 09-Feb-2026
 *      Author: yukta
 */


#include "stm32f103xx.h"
PWM_Handle_t MotorSpeed_PwmHandle;
GPIO_Handle_t MotorSpeed_pwmGpio;
GPIO_Handle_t MotorControl_GpioHandle;
GPIO_Handle_t IRSensor_Gpio_handle;

uint8_t left ,right;

void delay() {

	for (uint32_t i = 0; i < 500000 / 2; i++)
		;

}

void MotorSpeed_PWM_Config() {
	MotorSpeed_PwmHandle.pTIMx = TIMER2;
	MotorSpeed_PwmHandle.PWM_PinConfig.ARR_val = 255;
	MotorSpeed_PwmHandle.PWM_PinConfig.PRESCL_val = 1000;
	MotorSpeed_PwmHandle.PWM_PinConfig.PWM_Mode = 0b110;
	MotorSpeed_PwmHandle.PWM_PinConfig.CNT_val = 0;

	//Time Channel 1
	MotorSpeed_PwmHandle.PWM_PinConfig.TIM_Chnl = TIM_CHNL_1;
	Timer_PWM_Init(&MotorSpeed_PwmHandle);

	//Timer Channel 2
	MotorSpeed_PwmHandle.PWM_PinConfig.TIM_Chnl = TIM_CHNL_2;
	Timer_PWM_Init(&MotorSpeed_PwmHandle);
}

void MotorSpeed_PWM_GPIO_Config() {

	MotorSpeed_pwmGpio.pGPIOx = GPIOA;
	MotorSpeed_pwmGpio.GPIO_PinConfig.GPIO_AFIOControl = 1;
	MotorSpeed_pwmGpio.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_ALTFUN_PushPull;

		//PA0
		MotorSpeed_pwmGpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_0;
		GPIO_Init(&MotorSpeed_pwmGpio);

		//PA1
		MotorSpeed_pwmGpio.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_1;
		GPIO_Init(&MotorSpeed_pwmGpio);
}

void MotorControl_GPIO_Config() {
	MotorControl_GpioHandle.pGPIOx = GPIOB;
	MotorControl_GpioHandle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_OUT_PushPull;


	//IN1
	MotorControl_GpioHandle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_8;
	GPIO_Init(&MotorControl_GpioHandle);

	//IN2
	MotorControl_GpioHandle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_6;
	GPIO_Init(&MotorControl_GpioHandle);

	//IN3
	MotorControl_GpioHandle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&MotorControl_GpioHandle);

	//IN4
	MotorControl_GpioHandle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_5;
	GPIO_Init(&MotorControl_GpioHandle);

	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 0);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_9, 0);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, 0);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, 0);
}


void IR_GPIO_Config() {
	IRSensor_Gpio_handle.pGPIOx = GPIOA;
	IRSensor_Gpio_handle.GPIO_PinConfig.GPIO_PinMode = GPIO_MODE_IN_Float;

	//Left IR
	IRSensor_Gpio_handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_9;
	GPIO_Init(&IRSensor_Gpio_handle);

	//Right IR
	IRSensor_Gpio_handle.GPIO_PinConfig.GPIO_PinNumber = GPIO_PIN_NO_4;
	GPIO_Init(&IRSensor_Gpio_handle);
}

void SetSpeed(uint8_t speed1,uint8_t speed2)
{
	//left
	Timer_PWM_DutyCycle(TIMER2, speed1, TIM_CHNL_1);
	delay();
	//right
	Timer_PWM_DutyCycle(TIMER2, speed2, TIM_CHNL_2);


}


void moveForward()
{

	SetSpeed(20,20);
	//Motor left
		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 1);
		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_9, 0);

	//Motor Right
		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, 1);
		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, 0);


}

void moveRight()
{


	SetSpeed(35,35);


	//Motor left
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 1);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_9, 0);
		//delay();
	//Motor Right

		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, 0);
		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, 1);

}

void moveLeft()
{

	SetSpeed(35,35);
	//Motor left
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 0);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_9, 1);


	//Motor Right

		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, 1);
		GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, 0);


}

void stop()
{


	//Motor left
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_8, 0);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_9, 0);


	//Motor Right
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_5, 1);
	GPIO_WriteToOutputPin(GPIOB, GPIO_PIN_NO_6, 0);


}



int main(void)
{
	IR_GPIO_Config();
	MotorControl_GPIO_Config();
	MotorSpeed_PWM_GPIO_Config();
	MotorSpeed_PWM_Config();


	while(1)
	{



		right = GPIO_ReadFromInputPin(GPIOA, 4);

		left =  GPIO_ReadFromInputPin(GPIOA, 9);

		if ((left == RESET )&&(right == RESET ))
		{
			moveForward();

		}
		else if ((left == RESET )&&(right == SET ))
		{
			moveRight();

		}

		else if ((left == SET )&&(right == RESET ))
		{
			moveLeft();


		}
		else if ((left == RESET )&&(right == RESET ))
		{

			stop();

		}

		delay();

	}

	return 0;
}
