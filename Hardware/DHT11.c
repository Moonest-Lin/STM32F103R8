#include "GPIO.h"
#include "delay.h"

#define DHT11_Read GPIO_ReadInputDataBit($DHT11_GPIOPort, $DHT11_GPIOPin)

u8 DHT11_Data[5]={0};

void DHT11_Init(void)
{
	RCC_APB2PeriphClockCmd($DHT11_GPIORCC, ENABLE);
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_OD;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $DHT11_GPIOPin;	
	GPIO_Init($DHT11_GPIOPort, &GPIO_InitStruct);
	GPIO_SetBits($DHT11_GPIOPort, $DHT11_GPIOPin);
}

void DHT11_Set(u8 state)
{
	if(state==1) GPIO_SetBits($DHT11_GPIOPort, $DHT11_GPIOPin);
	else if(state==0) GPIO_ResetBits($DHT11_GPIOPort, $DHT11_GPIOPin);
}

u8 DHT11_RecBit(void)
{
	while(DHT11_Read);
	while(!DHT11_Read);
	Delay_us(40);
	return DHT11_Read;
}

u8 DHT11_RecByte(void)
{
	u8 byte = 0;
	for(u8 i=0;i<8;i++)
		byte |= (DHT11_RecBit()<<(7-i));
	return byte;
}


u8 DHT11_GetData(void)
{
	u8 temp = 0;
	DHT11_Set(0);
	Delay_ms(25);
	DHT11_Set(1);
	Delay_us(30);
	while(DHT11_Read)
	{
		temp++;
		Delay_ms(1);
		if(temp>100)
			return 0;
	}
	temp = 0;
	while(!DHT11_Read)
	{
		temp++;
		Delay_us(1);
		if(temp>100)
			return 0;
	}
	
	for(u8 i=0;i<5;i++)
		DHT11_Data[i] = DHT11_RecByte();
	
	if(DHT11_Data[0]+DHT11_Data[1]+DHT11_Data[2]+DHT11_Data[3]==DHT11_Data[4])
		return 1;
	else 
		return 0;
}
