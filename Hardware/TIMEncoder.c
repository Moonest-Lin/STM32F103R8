#include "GPIO.h"

void TIMEncoder_Init(void)
{
	RCC_APB1PeriphClockCmd($TIMEncoder_TIMRCC, ENABLE);
	
	RCC_APB2PeriphClockCmd($TIMEncoder_GPIORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $TIMEncoder_GPIOPin1 | $TIMEncoder_GPIOPin2;	
	GPIO_Init($TIMEncoder_GPIOPort, &GPIO_InitStruct);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536-1;				//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 1-1;					//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit($TIMEncoder_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICStructInit(&TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit($TIMEncoder_TIM,&TIM_ICInitStructure);
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_2;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInit($TIMEncoder_TIM,&TIM_ICInitStructure);
	
	TIM_EncoderInterfaceConfig($TIMEncoder_TIM,TIM_EncoderMode_TI12,TIM_ICPolarity_Rising,TIM_ICPolarity_Rising);
	
	TIM_Cmd($TIMEncoder_TIM,ENABLE);
}

s16 TIMEncoder_GetLocation(void)
{
	return TIM_GetCounter($TIMEncoder_TIM);
}

s16 TIMEncoder_GetSpeed(void)
{
	s16 Temp;
	Temp = TIM_GetCounter($TIMEncoder_TIM);
	TIM_SetCounter($TIMEncoder_TIM,0);
	return Temp;
}
