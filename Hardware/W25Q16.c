#include "GPIO.h"

void W25Qxx_Init(void)
{
	RCC_APB2PeriphClockCmd($W25Q16_GPIORCC, ENABLE);
	RCC_APB2PeriphClockCmd($W25Q16CS_GPIORCC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SPI1, ENABLE);
	
	GPIO_InitTypeDef GPIO_InitStruct;
	GPIO_InitStruct.GPIO_Speed = GPIO_Speed_10MHz;
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_InitStruct.GPIO_Pin = $W25Q16CLK_GPIOPin|$W25Q16MOSI_GPIOPin;	
	GPIO_Init($W25Q16_GPIOPort, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStruct.GPIO_Pin = $W25Q16MISO_GPIOPin;	
	GPIO_Init($W25Q16_GPIOPort, &GPIO_InitStruct);
	
	GPIO_InitStruct.GPIO_Mode = GPIO_Mode_Out_PP;
	GPIO_InitStruct.GPIO_Pin = $W25Q16CS_GPIOPin;	
	GPIO_Init($W25Q16CS_GPIOPort, &GPIO_InitStruct);
	
	SPI_InitTypeDef SPI_InitStruct;
	SPI_InitStruct.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStruct.SPI_Mode = SPI_Mode_Master;
	SPI_InitStruct.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStruct.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStruct.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStruct.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStruct.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_4;
	SPI_InitStruct.SPI_FirstBit = SPI_FirstBit_MSB;
	SPI_Init(SPI1,&SPI_InitStruct);
	
	SPI_Cmd(SPI1,ENABLE);
}

u8 W25Qxx_RW(u8 data)
{
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI1,data);
	while(!SPI_I2S_GetFlagStatus(SPI1,SPI_I2S_FLAG_RXNE));
	return SPI_I2S_ReceiveData(SPI1);
}
