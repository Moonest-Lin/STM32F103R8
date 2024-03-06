#ifndef __DHT11_H__
#define __DHT11_H__

extern u8 DHT11_Data[5];

void DHT11_Init(void);
u8 DHT11_GetData(void);

#endif

