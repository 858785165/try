#include <STC15F2K60S2.H>
#include "intrins.h"
#define u8 unsigned char
#define stat0 0
#define stat1 1
#define stat2 2
#define nokey 0xff
u8 code duanma[]={0xc0,0xf9,0xa4,0xb0,0x99,0x92,0x82,0xf8,0x80,0x90,0xbf,0xff};
u8 TAB[8]={11,11,11,11,11,11,11,11};

void Delay100us()		//@11.0592MHz
{
	unsigned char i, j;

	_nop_();
	_nop_();
	i = 2;
	j = 15;
	do
	{
		while (--j);
	} while (--i);
}

u8 key_scan()
{
	static unsigned char stat=stat0;
	u8 key_temp=0,key_value;
	u8 key1,key2;
	
	P30=0;P31=0;P32=0;P33=0;P34=1;P35=1;P42=1;P44=1;
	if(P44==0) key1=0x70;
	if(P42==0) key1=0xb0;
	if(P35==0) key1=0xd0;
	if(P34==0) key1=0xe0;
	if((P44==1)&&(P42==1)&&(P35==1)&&(P34==1)) key1=0xf0;
	
	P30=1;P31=1;P32=1;P33=1;P34=0;P35=0;P42=0;P44=0;
	if(P33==0) key2=0x07;
	if(P32==0) key2=0x0b;
	if(P31==0) key2=0x0d;
	if(P30==0) key2=0x0e;
	if((P33==1)&&(P32==1)&&(P31==1)&&(P30==1)) key2=0x0f;
	
	key_temp = key1 |key2;
	
	switch(stat)
	{
		case stat0:
			if(key_temp!=nokey)
			{
				stat=stat1;
			}
		break;
		
		case stat1:
			if(key_temp==nokey)
			{
				stat=stat0;
			}
			else
			{
				switch(key_temp)
				{
					case 0x77:key_value=4;break;
					case 0x7b:key_value=5;break;
					case 0x7d:key_value=6;break;
					case 0x7e:key_value=7;break;
					
					case 0xb7:key_value=8;break;
					case 0xbb:key_value=9;break;
					case 0xbd:key_value=10;break;
					case 0xbe:key_value=11;break;
					
					case 0xd7:key_value=12;break;
					case 0xdb:key_value=13;break;
					case 0xdd:key_value=14;break;
					case 0xde:key_value=15;break;
					
					case 0xe7:key_value=16;break;
					case 0xeb:key_value=17;break;
					case 0xed:key_value=18;break;
					case 0xee:key_value=19;break;				
				}
				stat=stat2;
			}
			break;
		case stat2:
			if(key_temp==nokey)
			{
				stat=stat0;
			}
			break;
	}
	return key_value;
}

void dis_smg(u8 pos,u8 value)
{
	P2=0x00;P0=0x00;P2=0x00;
	P2=0xC0;P0=0X01<<pos;P2=0x00;
	P2=0xE0;P0=value;P2=0x00;
}


u8 key_val;
void main()
{
	P2=0xa0;P0=0x00;P2=0x00;
	P2=0x80;P0=0xff;P2=0x00;
	while(1)
	{
		u8 i=0;
		key_val=key_scan();
		switch(key_val)
		{
			case 4:TAB[6]=11;TAB[7]=4;break;
			case 5:TAB[6]=11;TAB[7]=5;break;
			case 6:TAB[6]=11;TAB[7]=6;break;
			case 7:TAB[6]=11;TAB[7]=7;break;
			
			case 8:TAB[7]=8;break;
			case 9:TAB[7]=9;break;
			case 10:TAB[6]=1;TAB[7]=0;break;
			case 11:TAB[6]=1;TAB[7]=1;break;
			
			case 12:TAB[6]=1;TAB[7]=2;break;
			case 13:TAB[6]=1;TAB[7]=3;break;
			case 14:TAB[6]=1;TAB[7]=4;break;
			case 15:TAB[6]=1;TAB[7]=5;break;
			
			case 16:TAB[6]=1;TAB[7]=6;break;
			case 17:TAB[6]=1;TAB[7]=7;break;
			case 18:TAB[6]=1;TAB[7]=8;break;
			case 19:TAB[6]=1;TAB[7]=9;break;
		}
		for(i=0;i<8;i++)
		{
			dis_smg(i,duanma[TAB[i]]);
			Delay100us();
		}
	}
}

