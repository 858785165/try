#include <STC12C5A60S2.H>
#include "iic.h"
#include "intrins.h"
#define u8 unsigned char
u8 code duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
u8 dis_smg[8];
u8 temp;
bit flag=0;
sbit buzz=P0^6;
sbit relay=P0^4;
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

void Timer0Init(void)		//1??@11.0592MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TL0 = 0xCD;		//??????
	TH0 = 0xD4;		//??????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
	
	ET0=1;
	
}

void main()
{
	P2=0xa0;P0=0x00;P2=0x00;
	P2=0x80;P0=0xff;P2=0x00;
	Timer0Init();
	write_adc(0x03);
	dis_smg[0]=11;dis_smg[1]=11;dis_smg[2]=11;dis_smg[3]=11;dis_smg[4]=11;
	while(1)
	{
		EA=0;
		temp=(unsigned char)read_adc(0x03);
		EA=1;
		dis_smg[5]=temp/100;
		dis_smg[6]=temp/10%10;
		dis_smg[7]=temp%10;
				if(temp<100)
			{
				P2=0Xa0;buzz=1;relay=0;P2=0x00;
				P2=0X80;P0=~0x00;P2=0x00;
			}
			else if(temp<200)
			{
				P2=0Xa0;buzz=0;relay=0;P2=0x00;
				P2=0X80;P0=~0x01;P2=0x00;
			}
			if(temp>200)
			{
					P2=0Xa0;buzz=0;relay=0;P2=0x00;
					P2=0X80;P0=~0x02;P2=0x00;
					Delay500ms();
					P2=0X80;P0=~0x00;P2=0x00;	
				  Delay500ms();
			}
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
