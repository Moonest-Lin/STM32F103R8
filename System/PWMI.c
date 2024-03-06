#include "GPIO.h"

void PWMI_Init(void)
{
	RCC_APB1PeriphClockCmd($PWMI_TIMRCC, ENABLE);
	
	RCC_APB2PeriphClockCmd($PWMI_GPIORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $PWMI_GPIOPin;	
	GPIO_Init($PWMI_GPIOPort, &GPIO_InitStruct);
	
	TIM_InternalClockConfig($PWMI_TIM);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 65536-1;				//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;			//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit($PWMI_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_ICInitTypeDef TIM_ICInitStructure;
	
	TIM_ICInitStructure.TIM_Channel = TIM_Channel_1;
	TIM_ICInitStructure.TIM_ICFilter = 0xF;
	TIM_ICInitStructure.TIM_ICPolarity = TIM_ICPolarity_Rising;
	TIM_ICInitStructure.TIM_ICPrescaler = TIM_ICPSC_DIV1;
	TIM_ICInitStructure.TIM_ICSelection = TIM_ICSelection_DirectTI;
	TIM_PWMIConfig($PWMI_TIM,&TIM_ICInitStructure);
	
	TIM_SelectInputTrigger($PWMI_TIM,TIM_TS_TI1FP1);
	
	TIM_SelectSlaveMode($PWMI_TIM,TIM_SlaveMode_Reset);
	
	TIM_Cmd($PWMI_TIM,ENABLE);
}

u32 PWMI_GetFreq(void)
{
	return 1000000 / (TIM_GetCapture1($PWMI_TIM) + 1);
}

u32 PWMI_GetDuty(void)
{
	return (TIM_GetCapture2($PWMI_TIM)+1) *100 / (TIM_GetCapture1($PWMI_TIM)+1);
}
