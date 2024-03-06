#include "GPIO.h"
#include "delay.h"

void LightSensor_Init(void)
{
	RCC_APB2PeriphClockCmd($LightSensor_GPIORCC, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Pin = $LightSensor_GPIOPin;	
	
	GPIO_Init($LightSensor_GPIOPort, &GPIO_InitStruct);
}

u8 LightSensor_GetState(void)
{
	u8 LightSensorState = 0;
	if (GPIO_ReadInputDataBit($LightSensor_GPIOPort,$LightSensor_GPIOPin)==0)
	{
		Delay_ms(20);
		while(GPIO_ReadInputDataBit($LightSensor_GPIOPort,$LightSensor_GPIOPin)==0);
		Delay_ms(20);
		LightSensorState = 1;
	}
	return LightSensorState;
}
