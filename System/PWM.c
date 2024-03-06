#include "GPIO.h"

void PWM_Init(void)
{
	RCC_APB1PeriphClockCmd($PWM_TIMRCC, ENABLE);
	
	RCC_APB2PeriphClockCmd($PWM_GPIORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $PWM_GPIOPin;	
	GPIO_Init($PWM_GPIOPort, &GPIO_InitStruct);
	
	TIM_InternalClockConfig($PWM_TIM);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;				//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 720-1;			//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit($PWM_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;						//CCR
	TIM_OC1Init($PWM_TIM,&TIM_OCInitStructure);
	
	TIM_Cmd($PWM_TIM, ENABLE);
}

void PWM_SetCompare1(u16 Compare)
{
	TIM_SetCompare1($PWM_TIM,Compare);
}

void PWM_SetPrescaler(u16 Prescaler)
{
	TIM_PrescalerConfig($PWM_TIM, Prescaler - 1, TIM_PSCReloadMode_Update);
}
