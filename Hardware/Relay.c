#include "GPIO.h"

void Relay_Init(void)
{
	RCC_APB2PeriphClockCmd($Relay1_GPIORCC | $Relay2_GPIORCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Pin = $Relay1_GPIOPin;	
	GPIO_Init($Relay1_GPIOPort, &GPIO_InitStruct);
	GPIO_InitStruct.GPIO_Pin = $Relay2_GPIOPin;
	GPIO_Init($Relay2_GPIOPort, &GPIO_InitStruct);
	
	GPIO_SetBits($Relay1_GPIOPort, $Relay1_GPIOPin);
	GPIO_SetBits($Relay2_GPIOPort, $Relay2_GPIOPin);
}

void Relay_Set(u8 relay,u8 state)
{
	if(relay==1)
	{
		if(state==1) GPIO_SetBits($Relay1_GPIOPort, $Relay1_GPIOPin);
		else if(state==0) GPIO_ResetBits($Relay1_GPIOPort, $Relay1_GPIOPin);
	}
	else if(relay==2)
	{
		if(state==1) GPIO_SetBits($Relay2_GPIOPort, $Relay2_GPIOPin);
		else if(state==0) GPIO_ResetBits($Relay2_GPIOPort, $Relay2_GPIOPin);
	}
}

void Relay_Reversal(u8 relay)
{
	if(relay==1)
	{
		if(GPIO_ReadOutputDataBit($Relay1_GPIOPort, $Relay1_GPIOPin)==0)
			GPIO_SetBits($Relay1_GPIOPort, $Relay1_GPIOPin);
		else
			GPIO_ResetBits($Relay1_GPIOPort, $Relay1_GPIOPin);
	}
	else if(relay==2)
	{
		if(GPIO_ReadOutputDataBit($Relay2_GPIOPort, $Relay2_GPIOPin)==0)
			GPIO_SetBits($Relay2_GPIOPort, $Relay2_GPIOPin);
		else
			GPIO_ResetBits($Relay2_GPIOPort, $Relay2_GPIOPin);
	}
}	
