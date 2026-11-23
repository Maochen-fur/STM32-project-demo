#include "sg90.h"



void SG90_Int(void)
{
	HAL_TIM_PWM_Start(&htim4,TIM_CHANNEL_3);
	SG90_Change(1500);
}


void SG90_Change(int vaule)
{
	__HAL_TIM_SET_COMPARE(&htim4,TIM_CHANNEL_3,vaule);
}



