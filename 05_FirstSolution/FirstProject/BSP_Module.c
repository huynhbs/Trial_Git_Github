/*
* Sample code 
* Apply for STM32F1
*/
#include "Button_Driver.h"

ButtonHandler_t Button1;
/* Interupt fuction 10ms to check GPIO status*/
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef* htim)
{
	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == RESET)
	{
		/*Button is pushing*/
		Button1.LowCallback

	}

	if (HAL_GPIO_ReadPin(GPIOA, GPIO_PIN_0) == SET)
	{
		/*Button is released*/

	}
}