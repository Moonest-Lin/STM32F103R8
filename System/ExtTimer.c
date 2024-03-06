#include "GPIO.h"

void EXTTIMER_Init(void)
{
	RCC_APB1PeriphClockCmd($ExtTimer_TIMRCC, ENABLE);
	RCC_APB2PeriphClockCmd($ExtTimer_GPIORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = $ExtTimer_GPIOPin;
	GPIO_Init($ExtTimer_GPIOPort, &GPIO_InitStruct);
	
	TIM_ETRClockMode2Config($ExtTimer_TIM, TIM_ExtTRGPSC_OFF, TIM_ExtTRGPolarity_NonInverted, 0x00);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1-1;
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit($ExtTimer_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_ClearFlag($ExtTimer_TIM, TIM_IT_Update);
	
	TIM_ITConfig($ExtTimer_TIM, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig($NVIC_PriorityGroup);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = $ExtTimer_TIMChannel;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = $ExtTimer_TIMPre;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = $ExtTimer_TIMSub;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd($ExtTimer_TIM, ENABLE);
}

u16 EXTTIMER_GetCounter(void)
{
	return TIM_GetCounter($ExtTimer_TIM);
}

/*
void TIM2_IRQHandler(void)
{
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
	{
		
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
*/
