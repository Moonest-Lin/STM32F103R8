#include "GPIO.h"

void Motor_Init(void)
{
	RCC_APB1PeriphClockCmd($Motor_TIMRCC, ENABLE);
	
	RCC_APB2PeriphClockCmd($Motor_GPIORCC, ENABLE);
	RCC_APB2PeriphClockCmd($MotorIN_GPIORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $Motor_GPIOPin;	
	GPIO_Init($Motor_GPIOPort, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = $MotorIN1_GPIOPin | $MotorIN2_GPIOPin;	
	GPIO_Init($MotorIN_GPIOPort, &GPIO_InitStruct);
	
	TIM_InternalClockConfig($Motor_TIM);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 100-1;				//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 36-1;			//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit($Motor_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;						//CCR
	TIM_OC3Init($Motor_TIM,&TIM_OCInitStructure);
	
	TIM_Cmd($Motor_TIM, ENABLE);
}

void Motor_SetCompare3(u16 Compare)
{
	TIM_SetCompare3($Motor_TIM,Compare);
}

void Motor_SetSpeed(s8 Speed)
{
	if (Speed >= 0)
	{
		GPIO_SetBits($MotorIN_GPIOPort,$MotorIN1_GPIOPin);
		GPIO_ResetBits($MotorIN_GPIOPort,$MotorIN2_GPIOPin);
		Motor_SetCompare3(Speed);
	}
	else
	{
		GPIO_SetBits($MotorIN_GPIOPort,$MotorIN2_GPIOPin);
		GPIO_ResetBits($MotorIN_GPIOPort,$MotorIN1_GPIOPin);
		Motor_SetCompare3(-Speed);
	}
}
