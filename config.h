#ifndef __CONFIG_H__
#define __CONFIG_H__

#include "iic.h"
#include <STC15F2K60S2.H>
#include "absacc.h"


#define u8 unsigned char
#define u16 unsigned int


#define stat0 0
#define stat1 1
#define stat2 2
#define nokey 0xff

u8 count=0;     //定时器中的计数
u8 jishu=0;     //计数界面中的计数值
u8 key_flag=0;  //开启按键按下
u8 led_count=0; //led灯的

u8 mode_set= 0;
u8 undefined_key=0; 
u8 disbuf[] ={0,1.11};

u8 volt_seting=0;
                           //   0    1    2    3    4    5    6    7    8    9    
unsigned char code NumNodot[]={0x3F,0x06,0x5B,0x4F,0x66,0x6D,0x7D,0x07,0x7F,0x6F};
                           //   N   P    U  black
unsigned char code biaoshi[]={0x37,0x73,0x78,0x00,};
                             //0.  1.     2. 3.    4.   5.   6.    7.  8.   9.  -1
unsigned char code Numdot[]={0xBF,0x86,0xDB,0xCF,0xE6,0xED,0xFD,0x87,0xFF,0xEF,0x46}; 




#endif