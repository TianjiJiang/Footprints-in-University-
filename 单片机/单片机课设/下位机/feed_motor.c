#include "feed_motor.h"

void delay(u16);

#ifdef servo 
sbit signal = P1^2;
void open()
{	
	u8 i;
	u8 j = 80;
	for(k = 0;k < 100;k++) 
	{
		for(i = 0;i<100;i++)
		{
			signal = (i < j)?1:0;
		}
	}					
}
void close()
{	
	u8 i;
	u8 j = 10;
	for(k = 0;k < 100;k++) 
	{
		for(i = 0;i<100;i++)
		{
			signal = (i < j)?1:0;
		}
	}					
}
#endif

#ifdef step5
#define SPEED 750
u8 list[] = {0x04,0x08,0x01,0x02};
void open()
{
	u8 i,j;
	for(j = 250; j > 1; j--)
	{
		for(i = 0; i < 4; i++)
		{
			P1 = list[i]; 
			delay(SPEED); 
		}
		
	}
	P1 = 0x00;
}

void close()
{
	u8 i,j;
	for(j = 250; j > 1; j--)
	{
		for(i = 4; i >0; i--)
		{
			P1 = list[i-1]; 
			delay(SPEED); 
		}
		P1 = 0x00;	
	}
}
#endif

#ifdef step4
#define SPEED 200

u8 list[] = {0x0B,0x0E,0x07,0x0D};

void open()
{
	u8 i,j;
	for(j = 100; j > 1; j--)
	{
		for(i = 0; i < 4; i++)
		{
			P1 = list[i];
			delay(SPEED);  
		}
		
	}
}

void close()
{
	u8 i,j;
	for(j = 100; j > 1; j--)
	{
		for(i = 4; i > 0; i--)
		{
			P1 = list[i];
			delay(SPEED);  
		}
		
	}
}

#endif

void delay(u16 i)
{
	while(i--);	
}