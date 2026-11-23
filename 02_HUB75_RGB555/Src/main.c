#include "hub75.h"
#include "stm32f10x.h"
#include "delay.h"
#include "image1.h"

uint16_t  *gram_rgb_555=( uint16_t*)gImage_rgb;

void TIM2_Init(uint16_t period) {
    TIM_TimeBaseInitTypeDef TIM_TimeBaseStructure;
    NVIC_InitTypeDef NVIC_InitStructure;

    // 使能定时器 2 时钟
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    // 定时器基本配置
    TIM_TimeBaseStructure.TIM_Period = period - 1; //period可改
    TIM_TimeBaseStructure.TIM_Prescaler = 72 - 1; // 1MHz
    TIM_TimeBaseStructure.TIM_ClockDivision = TIM_CKD_DIV1;
    TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseStructure);

    // 使能定时器 2 中断
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

    // 配置 NVIC
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_Init(&NVIC_InitStructure);

    // 启动定时器
    TIM_Cmd(TIM2, ENABLE);
}


void TIM2_IRQHandler(void) {
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) != RESET) {
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);

	//HUB75_RefreshScreen();
			
    }
}

int main(void) {
    // 初始化硬件
     GPIO_Config();
    TIM2_Init(500); // 设置定时器周期，根据需要调整

	

    while (1) 
		{
		//	gram_rgb_555=( uint16_t*)gImage_rgb1;
							for(int aaa=0;aaa<10;aaa++)
			{
							led_DRamDis(gram_rgb_555);
			}
	

	
    }
		
		
}

