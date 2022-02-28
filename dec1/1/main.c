#include <STC15F2K60S2.H>
#define u8 unsigned char

u8 TAB[]={0x18,0x24,0x42,0x81,0x18,0x24,0x42,0x81};

void Timer0Init(void)		//5??@12.000MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TL0 = 0xA0;		//??????
	TH0 = 0x15;		//??????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
	ET0=1;
	EA=1;
}


void main()
{
	Timer0Init();
	while(1)
	{
		
	}
}

void timer0() interrupt 1 using 1
{
	static unsigned char count=0,i=0;
	count++;
	if(count==100)
	{
		count=0;
		P2=0X00;P0=0X00;P2=0X00;
		P2=0X80;P0=~TAB[i];P2=0x00;
		i++;
		if(i==8)i=0;
	}
}