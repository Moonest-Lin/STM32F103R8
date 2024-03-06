#include "stm32f10x.h"
#include "led.h"
#include "delay.h"
#include "key.h"
#include "usart.h"
#include "dht11.h"
#include "oled.h"
#include <stdio.h>

int main(void)
{
	KEY_Init();
	Serial_Init();
	DHT11_Init();	
	OLED_Init();
	OLED_ShowChar(1,1,'A');
	OLED_ShowString(2,1,"Hello");
	while(1)
	{	
		if(KEY_GetNum())
		{
			if(DHT11_GetData())
				printf("temp:%d.%d   humi:%d.%d\r\n",DHT11_Data[0],DHT11_Data[1],DHT11_Data[2],DHT11_Data[3]);
			else
				printf("Error!\r\n");
		}
	}
}
