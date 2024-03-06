#include "GPIO.h"
#include <stdio.h>

u8 Serial_RxFlag;
u8 Serial_TxPacket[4];
u8 Serial_RxPacket[4];

void Serial_Init(void)
{
	RCC_APB2PeriphClockCmd($USART_RCC, ENABLE);
	RCC_APB2PeriphClockCmd($USARTIn_GPIORCC | $USARTOut_GPIORCC, ENABLE);

	GPIO_InitTypeDef GPIO_InitStruct;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $USARTOut_GPIOPin;	
	GPIO_Init($USARTOut_GPIOPort, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IPU;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStruct.GPIO_Pin = $USARTIn_GPIOPin;	
	GPIO_Init($USARTIn_GPIOPort, &GPIO_InitStruct);
	
	USART_InitTypeDef USART_InitStruture;
	USART_InitStruture.USART_BaudRate = 115200;
	USART_InitStruture.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	USART_InitStruture.USART_Mode = USART_Mode_Tx | USART_Mode_Rx;
	USART_InitStruture.USART_Parity = USART_Parity_No;
	USART_InitStruture.USART_StopBits = USART_StopBits_1;
	USART_InitStruture.USART_WordLength = USART_WordLength_8b;
	USART_Init(USART1,&USART_InitStruture);
	
	USART_ITConfig(USART1, USART_IT_RXNE, ENABLE);
	
	NVIC_PriorityGroupConfig($NVIC_PriorityGroup);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = $USART_Channel;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = $USART_Pre;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = $USART_Sub;
	NVIC_Init(&NVIC_InitStructure);
	
	USART_Cmd(USART1, ENABLE);
}

void Serial_SendByte(u8 Byte)
{
	USART_SendData(USART1,Byte);
	while (USART_GetFlagStatus(USART1,USART_FLAG_TXE) == RESET);
}

void Serial_SendArray(u8 *Array)
{
	u16 i;
	for(i=0;i<sizeof(Array)/sizeof(Array[0]);i++)
	{
		Serial_SendByte(Array[i]);
	}
}

void Serial_SendString(s8 *String)
{
	u8 i;
	for(i=0;String[i]!=0;i++)
	{
		Serial_SendByte(String[i]);
	}
}

void Serial_SendNum(u32 num)
{
	u32 label=10;
	while(num>=label)
		label *= 10;
	label /= 10;
	while(label>0)
	{
		Serial_SendByte(num/label%10+'0');
		label /= 10;
	}
}

int fputc(int data,FILE*file)
{
	while(!(USART1->SR &1<<7))
		{
		}
		USART1->DR = data;
		return data;
}

u8 Serial_GetRxFlag(void)
{
	if(Serial_RxFlag == 1)
	{
		Serial_RxFlag = 0;
		return 1;
	}
	else
		return 0;
}

void Serial_SendPacket(void)
{
	Serial_SendByte(0xFF);
	Serial_SendArray(Serial_TxPacket);
	Serial_SendByte(0xFE);
}

void USART1_IRQHandler(void)
{
	static u8 RxState = 0;
	static u8 i = 0;
	if(USART_GetITStatus(USART1, USART_IT_RXNE) == SET)
	{
		u8 RxData = USART_ReceiveData(USART1);
		if(RxState == 0)
		{
			if(RxData == 0xFF)
			{
				RxState = 1;
			}
		}
		else if(RxState == 1)
		{
			if(i<3)
			{
				Serial_RxPacket[i] = RxData;
				i++;
			}
			else
			{
				Serial_RxPacket[i] = RxData;
				i = 0;
				RxState = 2;
			}
		}
		else if(RxState == 2)
		{
			if(RxData == 0xFE)
			{
				Serial_RxFlag = 1;
				RxState = 0;
			}
		}
		USART_ClearITPendingBit(USART1, USART_IT_RXNE);
	}
}
