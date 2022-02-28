#include <STC15F2K60S2.H>
#include "iic.h"
#include "onewire.h"
#define u8 unsigned char
u8 code duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
u8 dis_smg[8];
u8 temp;
void Timer0Init(void)		//1??@11.0592MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TL0 = 0xCD;		//??????
	TH0 = 0xD4;		//??????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
	
	EA=1;
	ET0=1;
}

void run()
{
	if(temp<20)
	{
		dis_smg[0]=10;
		dis_smg[2]=10;
		dis_smg[1]=1;
		dac_out(0);
	}
	else if(temp<23)
	{
		dis_smg[0]=11;
		dis_smg[2]=11;
		dis_smg[1]=11;
	}
	else
	{
		dis_smg[0]=10;
		dis_smg[2]=10;
		dis_smg[1]=2;
		dac_out(255);
	}
}



void main()
{
	P2=0xa0;P0=0x00;P2=0x00;
	P2=0x80;P0=0xff;P2=0x00;
	Timer0Init();
	dis_smg[0]=11;dis_smg[1]=11;dis_smg[2]=11;dis_smg[3]=11;dis_smg[4]=11;dis_smg[5]=11;
	while(1)
	{
		temp=(unsigned char)read_temperature();
		dis_smg[6]=temp/10;
		dis_smg[7]=temp%10;
		run();
	}
	
}


void timer0() interrupt 1 using 1
{
	static unsigned char count=0,i=0;
	count++;
	if(count==1)
	{
		count=0;
		P2=0Xc0;P0=0x00;P2=0x00;
		P2=0Xc0;P0=0x01<<i;P2=0x00;
		P2=0Xe0;P0=duanma[dis_smg[i]];P2=0x00;
		i++;
		if(i==8)i=0;
	}
}