#include "config.h"


void port(unsigned char p2,p0)
{
	P0 = 	p0;
	P2 = (P2&0X1F)|p2;
	P0 = p0;
}

void allinit()
{
	port(0x80,0xff);
	port(0xa0,0x00);
	port(0xc0,0xff);
	port(0xe0,0xff);
}

void Timer0Init(void)		//100??@11.0592MHz
{
	AUXR |= 0x80;		//?????1T??
	TMOD &= 0xF0;		//???????
	TL0 = 0xAE;		//???????
	TH0 = 0xFB;		//???????
	TF0 = 0;		//??TF0??
	TR0 = 1;		//???0????
	
	ET0 = 1;
	EA = 1;
}




u8 keyscan()
{
	static u8 key_stat = stat0;
	u8 key_value = 0,key_temp;
	u8 key1,key2;
	P30=0;P31=0;P32=0;P33=0;P34=1;P35=1;P42=1;P44=1;
	if(P44==0)key1=0x70;
	if(P42==0)key1=0xb0;
	if(P35==0)key1=0xd0;
	if(P44==0)key1=0xe0;
	P30=1;P31=1;P32=1;P33=1;P34=0;P35=0;P42=0;P44=0;
	if(P33==0)key2=0x07;
	if(P32==0)key2=0x0b;
	if(P31==0)key2=0x0d;
	if(P30==0)key2=0x0e;
	
	key_temp = key1 | key2;
	
	switch(key_stat)
	{
		case stat0:
			if(key_temp!=nokey)
			{
				key_stat = stat1;
			}
		case stat1:
			if(key_temp==nokey)
			{
				key_stat = stat0;
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
				key_stat = stat2;
			}
		case stat2:
			if(key_temp != nokey)
			{
				key_stat = stat0;
				break;
			}
	}
	
	return key_value;
}




void new_keyscan()
{
	static u8 key_stat = stat0;
	u8 key_value = 0,key_temp;
	u8 key1,key2;
	P30=0;P31=0;P32=0;P33=0;P34=1;P35=1;P42=1;P44=1;
	if(P44==0)key1=0x70;
	if(P42==0)key1=0xb0;
	if(P35==0)key1=0xd0;
	if(P44==0)key1=0xe0;
	P30=1;P31=1;P32=1;P33=1;P34=0;P35=0;P42=0;P44=0;
	if(P33==0)key2=0x07;
	if(P32==0)key2=0x0b;
	if(P31==0)key2=0x0d;
	if(P30==0)key2=0x0e;
	
	key_temp = key1 | key2;
	
	switch(key_stat)
	{
		case stat0:
			if(key_temp!=nokey)
			{
				key_stat = stat1;
			}
		case stat1:
			if(key_temp==nokey)
			{
				key_stat = stat0;
			}
			else
			{
				switch(key_temp)
				{
					case 0x77:undefined_key++;break;
					case 0x7b:undefined_key++;break;
					case 0x7d:undefined_key++;break;
					case 0x7e:undefined_key++;break;
					
					case 0xb7:undefined_key++;break;
					case 0xbb:undefined_key++;break;
					case 0xbd:undefined_key++;break;
					case 0xbe:undefined_key++;break;
					
					case 0xd7://S12
						undefined_key=0;
						if(mode_set==1)	write_at24c02(0x00,(u8)(volt_seting/10));
						if(++mode_set==3)mode_set=0;
					break;
					case 0xdb://S13
						undefined_key=0;
						if(mode_set==2)jishu=0;
					break;
					case 0xdd:undefined_key++;break;
					case 0xde:undefined_key++;break;
					
					case 0xe7://S16
						undefined_key=0;
						if(mode_set==1)
						{
							if(volt_seting==0)
								volt_seting=500;
							else
								volt_seting-=50;
						}
					break;
					case 0xeb:
					undefined_key=0;
						if(mode_set==1)
						{
							if(volt_seting>=500)
								volt_seting=0;
							else
								volt_seting+=50;
						}	
					break;
					case 0xed:undefined_key++;break;
					case 0xee:undefined_key++;break;
				}
				key_stat = stat2;
			}
		case stat2:
			if(key_temp != nokey)
			{
				key_stat = stat0;
				break;
			}
	}
}

void dis_smg(u8 pos,u8 value)
{
//	XBYTE[0xa000] = 0x01 << pos;
//	XBYTE[0xc000] = value;
	port(0xc0,0x01<<pos);
	port(0xe0,value);
}


void KBD()
{
	//设置键盘fla定是否有按键按下以及案件的松动
//	u8 num_1; 
	u8 num;
	num = keyscan();      //如何控制在模式1 的情况下，其他按键无效？？？？？
	switch(num)
	{
		case 12:
		{
			mode_set++;
			if(mode_set==3)
			{mode_set = 0;}
		}
		break;
		
		case 13:
			undefined_key = 0;
		break;
		default:undefined_key++;break;
	}
	num = 0;
	
}

void dis_mode()
{
	switch(mode_set)
	{
		case 0:
		{
			dis_smg(0,biaoshi[2]);
			dis_smg(0,biaoshi[2]);
			dis_smg(0,biaoshi[2]);
		}
			break;
		
		case 1:
			
		break;
		
		case 2:
			
		break;	
	}
}



void main()
{
	while(1)
	{
		if(key_flag)
		{
			key_flag=0;
			KBD();
		}
	}
}

void timer0() interrupt 1 using 1
{
	count++;
	if(count == 20)
	{
		key_flag=1;
		count = 0;
	}
	
}