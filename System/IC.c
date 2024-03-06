#include "GPIO.h"

void IC_Init(void)
{
	RCC_APB1PeriphClockCmd($IC_TIMRCC, ENABLE);
	
	RCC_APB2PeriphClockCmd($IC_GPIORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $IC_GPIOPin;	
	GPIO_Init($IC_GPIOPort, &GPIO_InitStruct);
	
	TIM_InternalClockConfig($IC_TIM);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536-1;				//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;			//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit($IC_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_ICInit($IC_TIM,&TIM_ICInitStructure);
	
	TIM_SelectInputTrigger($IC_TIM,TIM_TS_TI1FP1);
	
	TIM_SelectSlaveMode($IC_TIM,TIM_SlaveMode_Reset);
	
	TIM_Cmd($IC_TIM,ENABLE);
}

u32 IC_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1($IC_TIM) + 1);
}
