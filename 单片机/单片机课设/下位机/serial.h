/**************************************************************************************
波特率设置为19200
SBuff is the buff of data come from serial											  
***************************************************************************************/

#ifndef _SERIAL_H
#define _SERIAL_H

#include "common.h"


extern unsigned char RcvData[11]; // used to save data recieved
extern unsigned char New_Cmd;
void UsartInit(void);
void wait_serial_cmd();	  
void serial_print(char*);
void serial_printu8(char* str, u8 count);

#endif