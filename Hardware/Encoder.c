#include "GPIO.h"

s16 Encoder_Count;

void Encoder_Init(void)
{
	RCC_APB2PeriphClockCmd($Encoder_GPIORCC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $Encoder_GPIOPin1 | $Encoder_GPIOPin2;
	GPIO_Init($Encoder_GPIOPort, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig($Encoder_AFIOPort,$Encoder_AFIOPin1);
	GPIO_EXTILineConfig($Encoder_AFIOPort,$Encoder_AFIOPin2);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = $Encoder_EXTILine1 | $Encoder_EXTILine2;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = $Encoder_EXTITrigger;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_PriorityGroupConfig($NVIC_PriorityGroup);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = $Encoder_EXTIChannel1;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = $Encoder_EXTIPre1;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = $Encoder_EXTISub1;
	NVIC_Init(&NVIC_InitStruct);
	NVIC_InitStruct.NVIC_IRQChannel = $Encoder_EXTIChannel2;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = $Encoder_EXTIPre2;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = $Encoder_EXTISub2;
	NVIC_Init(&NVIC_InitStruct);
}

s16 Encoder_Get(void)
{
	s16 temp;
	temp = Encoder_Count;
	Encoder_Count = 0;
	return temp;
}

void EXTI0_IRQHandler(void)
{
	if(EXTI_GetITStatus($Encoder_EXTILine1) == SET)
	{
		if(GPIO_ReadInputDataBit($Encoder_GPIOPort,$Encoder_GPIOPin2) == 0) Encoder_Count--;
		EXTI_ClearITPendingBit($Encoder_EXTILine1);
	}
}

void EXTI1_IRQHandler(void)
{
	if(EXTI_GetITStatus($Encoder_EXTILine2) == SET)
	{
		if(GPIO_ReadInputDataBit($Encoder_GPIOPort,$Encoder_GPIOPin1) == 0) Encoder_Count++;
		EXTI_ClearITPendingBit($Encoder_EXTILine2);
	}
}
