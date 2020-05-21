#ifndef __HX711_H__
#define __HX711_H__


#include "common.h"

//IO设置
sbit HX711_DOUT=P3^7; 
sbit HX711_SCK=P2^2; 

//函数或者变量声明

extern long Weight_food;
extern long Weight_self;
//extern char Weight_flag; // 0 nothing;1 over weight; 2 负重量
void WeightInit();
void GetWeight();
void feed();
#endif