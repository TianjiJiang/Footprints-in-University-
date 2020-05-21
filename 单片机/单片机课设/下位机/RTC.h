#ifndef __RTC_H_
#define __RTC_H_

#include "common.h"

sbit DSIO=P3^4;
sbit RST=P3^5;
sbit SCLK=P3^6;

void Ds1302Init();
void Ds1302ReadTime();

//---加入全局变量--//

extern uchar RTIME[7];	//real time
extern uchar SET_TIME[7]; //used to set real time

#endif