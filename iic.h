#ifndef _IIC_H
#define _IIC_H

unsigned char read_pcf(unsigned char ch);
unsigned char read_at24c02(unsigned char add);
void write_at24c02(unsigned char add,unsigned char dat);

#endif