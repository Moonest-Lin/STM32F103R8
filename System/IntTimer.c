#include "GPIO.h"

void INTTIMER_Init(void)
{
	RCC_APB1PeriphClockCmd($IntTimer_TIMRCC, ENABLE);
	
	TIM_InternalClockConfig($IntTimer_TIM);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 10000-1;
	TIM_TimeBaseInitStruct.TIM_Prescaler = 7200-1;	//1s
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit($IntTimer_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_ClearFlag($IntTimer_TIM, TIM_IT_Update);
	
	TIM_ITConfig($IntTimer_TIM, TIM_IT_Update, ENABLE);
	
	NVIC_PriorityGroupConfig($NVIC_PriorityGroup);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = $IntTimer_TIMChannel;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = $IntTimer_TIMPre;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = $IntTimer_TIMSub;
	NVIC_Init(&NVIC_InitStruct);
	
	TIM_Cmd($IntTimer_TIM, ENABLE);
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
