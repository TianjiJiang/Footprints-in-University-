
#include "ultrasonic.h"

			  
unsigned int  time=0;
unsigned long S=0;

void Count(void)
{
	 time=TH0*256+TL0;
	 TH0=0;
	 TL0=0;
	 S=(time*17.4)/100;     //算出来是CM
}
void  StartModule() 		         //启动模块
{
	  Trig=1;			                     //启动一次模块
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  _nop_(); 
	  _nop_(); 
	  _nop_(); 
	  _nop_();
	  Trig=0;
}

void measure(void)
{

	 TMOD|=0x01;		   //设T0为方式1，GATE=1；
	 TH0=0;
	 TL0=0;
	 EA=1;
	 StartModule();
     while(!Echo);			 //当RX为零时等待
     TR0=1;			    //开启计数
     while(Echo);			//当RX为1计数并等待
     TR0=0;				//关闭计数
     Count();			//计算		
}