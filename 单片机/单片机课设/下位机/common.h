#ifndef _COMMON_H
#define _COMMON_H

#include "reg52.h"
#include<intrins.h>		

typedef unsigned int u16;	
typedef unsigned char u8;
#ifndef uchar
#define uchar unsigned char
#endif

#ifndef uint 
#define uint unsigned int
#endif

char* num8tochar(u8 num);
char* num16tochar(u16 num);

#endif