#include "GPIO.h"

u32 DECtoBCD(u32 num)
{
    u32 label=10,i=16,bcd=0;
	while(num>=label)
    {
        label *= 10;
        i *= 16;
    }
	label /= 10;
    i /= 16;
	while(label>0)
	{
		bcd += num/label%10*i;
		label /= 10;
        i /= 16;
	}
	return bcd;
}

u32 BCDtoDEC(u32 num)
{
    u32 label=16,i=10,dec=0;
	while(num>=label)
    {
        label *= 16;
        i *= 10;
    }
	label /= 16;
    i /= 10;
	while(label>0)
	{
		dec += num/label%16*i;
		label /= 16;
        i /= 10;
	}
	return dec;
}
