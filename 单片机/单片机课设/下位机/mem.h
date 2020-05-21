#ifndef __MEM_H_
#define __MEM_H_

#include "common.h"

sbit SCL=P2^1;
sbit SDA=P2^0;


void At24c02Write(unsigned char addr,unsigned char dat);
unsigned char At24c02Read(unsigned char addr);

#endif
