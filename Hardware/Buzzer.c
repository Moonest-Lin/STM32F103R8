#include "GPIO.h"

void BUZZER_Init(void)
{
	RCC_APB2PeriphClockCmd($Buzzer_GPIORCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	
	GPIO_InitStruct.GPIO_Pin = $Buzzer_GPIOPin;	
	GPIO_Init($Buzzer_GPIOPort, &GPIO_InitStruct);
	
//	GPIO_SetBits($Buzzer_GPIOPort, $Buzzer_GPIOPin);
}

void Buzzer_Set(u8 state)
{
	if(state==1) GPIO_SetBits($Buzzer_GPIOPort, $Buzzer_GPIOPin);
	else if(state==0) GPIO_ResetBits($Buzzer_GPIOPort, $Buzzer_GPIOPin);
}

void Buzzer_Reversal(void)
{
	if(GPIO_ReadOutputDataBit($Buzzer_GPIOPort, $Buzzer_GPIOPin)==0)
		GPIO_SetBits($Buzzer_GPIOPort, $Buzzer_GPIOPin);
	else
		GPIO_ResetBits($Buzzer_GPIOPort, $Buzzer_GPIOPin);
}	
