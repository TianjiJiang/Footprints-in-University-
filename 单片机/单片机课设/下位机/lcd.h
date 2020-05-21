#ifndef __LCD_H_
#define __LCD_H_

#include "common.h"

#define LCD1602_DB  P0      //data bus 数据总线
sbit LCD1602_RS = P2^6;
sbit LCD1602_RW = P2^5;
sbit LCD1602_EN = P2^7;	 

void LcdShowStr(unsigned char x,unsigned char y,unsigned char *str);     //显示字符串
void InitLcd1602();              //1602初始化
void DisplayOneChar(unsigned char X, unsigned char Y, unsigned char DData);
void LcdClearScreen();

#endif
