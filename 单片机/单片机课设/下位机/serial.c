
#include "serial.h"

unsigned int cmd_time;
u8 Scount = 0;
unsigned char RcvData[11] = {0};
unsigned char New_Cmd = 0;

void UsartInit()
{
	SCON=0X50;			
	TMOD=0X20;		
	PCON=0X80;	
	TH1=0XFD;				
	TL1=0XFD;
	ES=0;					
	EA=1;					
	TR1=1;
}

void Usart() interrupt 4
{
	u8 Sbuff;			 
	cmd_time = 50000;
	Sbuff=SBUF;
	if(Sbuff =='\n')
	{
		cmd_time = 0;
		Scount = 0;
		New_Cmd = 1;
	}
	else
	{
		RcvData[Scount++] = Sbuff;
		RcvData[Scount] = '\0';
	}
	RI = 0;	 
}

void wait_serial_cmd()	   // coperate with a global Buff
{
	cmd_time = 50000;
	ES = 1;
	while(cmd_time--);
	ES = 0;
}



void serial_print(char* str)
{
	while(*str)
	{
		SBUF= *str++;
		while(!TI);			 //等待发送数据完成
		TI=0;				 //清除发送完成标志位
	}
}

void serial_printu8(char* str, u8 count)
{
	while(count--)
	{
		SBUF= *str++;
		while(!TI);			 //等待发送数据完成
		TI=0;
	}
}
