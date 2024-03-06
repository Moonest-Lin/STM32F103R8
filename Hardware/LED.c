#include "GPIO.h"

/*********************
LED
*********************/
void LED_Init(void)
{
	RCC_APB2PeriphClockCmd($LED0_GPIORCC | $LED1_GPIORCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Pin = $LED0_GPIOPin;	
	GPIO_Init($LED0_GPIOPort, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = $LED1_GPIOPin;
	GPIO_Init($LED1_GPIOPort, &GPIO_InitStruct);
	
	GPIO_SetBits($LED0_GPIOPort, $LED0_GPIOPin);
	GPIO_SetBits($LED1_GPIOPort, $LED1_GPIOPin);
}

void LED_Set(u8 led,u8 state)
{
	if(led==1)
	{
		if(state==0) GPIO_SetBits($LED0_GPIOPort, $LED0_GPIOPin);
		else if(state==1) GPIO_ResetBits($LED0_GPIOPort, $LED0_GPIOPin);
	}
	else if(led==2)
	{
		if(state==0) GPIO_SetBits($LED1_GPIOPort, $LED1_GPIOPin);
		else if(state==1) GPIO_ResetBits($LED1_GPIOPort, $LED1_GPIOPin);
	}
}

void LED_Reversal(u8 led)
{
	if(led==1)
	{
		if(GPIO_ReadOutputDataBit($LED0_GPIOPort, $LED0_GPIOPin)==0)
			GPIO_SetBits($LED0_GPIOPort, $LED0_GPIOPin);
		else
			GPIO_ResetBits($LED0_GPIOPort, $LED0_GPIOPin);
	}
	else if(led==2)
	{
		if(GPIO_ReadOutputDataBit($LED1_GPIOPort, $LED1_GPIOPin)==0)
			GPIO_SetBits($LED1_GPIOPort, $LED1_GPIOPin);
		else
			GPIO_ResetBits($LED1_GPIOPort, $LED1_GPIOPin);
	}
}	
