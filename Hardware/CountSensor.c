#include "GPIO.h"

u16 CountSensor_Count;

void CountSensor_Init(void)
{
	RCC_APB2PeriphClockCmd($CountSensor_GPIORCC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = $CountSensor_GPIOPin;
	GPIO_Init($CountSensor_GPIOPort, &GPIO_InitStruct);
	
	GPIO_EXTILineConfig($CountSensor_AFIOPort,$CountSensor_AFIOPin);
	
	EXTI_InitTypeDef EXTI_InitStruct;
	EXTI_InitStruct.EXTI_Line = $CountSensor_EXTILine;
	EXTI_InitStruct.EXTI_LineCmd = ENABLE;
	EXTI_InitStruct.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStruct.EXTI_Trigger = $CountSensor_EXTITrigger;
	EXTI_Init(&EXTI_InitStruct);
	
	NVIC_PriorityGroupConfig($NVIC_PriorityGroup);
	
	NVIC_InitTypeDef NVIC_InitStruct;
	NVIC_InitStruct.NVIC_IRQChannel = $CountSensor_EXTIChannel;
	NVIC_InitStruct.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority = $CountSensor_EXTIPre;
	NVIC_InitStruct.NVIC_IRQChannelSubPriority = $CountSensor_EXTISub;
	NVIC_Init(&NVIC_InitStruct);
}

u16 CountSensor_GetCount(void)
{
	return CountSensor_Count;
}

void EXTI15_10_IRQHandler(void)
{
	if(EXTI_GetITStatus($CountSensor_EXTILine) == SET)
	{
		CountSensor_Count++;
		EXTI_ClearITPendingBit($CountSensor_EXTILine);
	}
}
