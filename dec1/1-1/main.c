#include <STC15F2K60S2.H>
#define u8 unsigned char
#include "intrins.h"
u8 TAB[]={0x18,0x24,0x42,0x81,0x18,0x24,0x42,0x81};

void Delay500ms()		//@11.0592MHz
{
	unsigned char i, j, k;

	_nop_();
	_nop_();
	i = 22;
	j = 3;
	k = 227;
	do
	{
		do
		{
			while (--k);
		} while (--j);
	} while (--i);
}

void main()
{
	while(1)
	{
		u8 i;
		for(i=0;i<9;i++)
		{
		P2=0X00;P0=0X00;P2=0X00;
		P2=0X80;P0=~TAB[i];P2=0x00;
		Delay500ms();
	  
		}
}
}
