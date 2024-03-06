#include "GPIO.h"

void Servo_Init(void)
{
	RCC_APB1PeriphClockCmd($Servo_TIMRCC, ENABLE);
	
	RCC_APB2PeriphClockCmd($Servo_GPIORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $Servo_GPIOPin;	
	GPIO_Init($Servo_GPIOPort, &GPIO_InitStruct);
	
	TIM_InternalClockConfig($Servo_TIM);
	
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStruct;
	TIM_TimeBaseInitStruct.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStruct.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStruct.TIM_Period = 20000-1;				//ARR
	TIM_TimeBaseInitStruct.TIM_Prescaler = 72-1;				//PSC
	TIM_TimeBaseInitStruct.TIM_RepetitionCounter=0;
	TIM_TimeBaseInit($Servo_TIM,&TIM_TimeBaseInitStruct);
	
	TIM_OCInitTypeDef TIM_OCInitStructure;
	TIM_OCStructInit(&TIM_OCInitStructure);
	TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1;
	TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
	TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
	TIM_OCInitStructure.TIM_Pulse = 0;						//CCR
	TIM_OC2Init($Servo_TIM,&TIM_OCInitStructure);
	
	TIM_Cmd($Servo_TIM, ENABLE);
}

void Servo_SetCompare2(u16 Compare)
{
	TIM_SetCompare2($Servo_TIM,Compare);
}

void Servo_SetAngle(float Angle)
{
	Servo_SetCompare2(Angle /180*2000+500);
}
