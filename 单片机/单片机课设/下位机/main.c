
#include "main.h"

uchar feed_time[10] = {0};
uchar feed_weigth[10] = {0};
uchar feed_times = 0;
uchar now_feed_time = 1; // to mark which weight standerd usings
bit isSendFull = 1;

bit isauto = 0; //0 is auto;1 is manual 
uchar key = 0;


void VeryLongTimeDelay()
{
	uint iii,jjj;
	for(iii = 0;iii <6000 ;iii++)
		for(jjj = 0; jjj <20;jjj++);
}
void TimeDelay()
{
	uint iii;
	for(iii = 0;iii <200 ;iii++);
}
#ifndef	hx711
void feed_delay(char i)
{
	u16 a;
	while(i--)
	{
		a = 60000;
		while(a--);
	}
}
#endif

void ParamInit() // basic param init
{
	/* 
	==addr==	==data==
		0		time1
		1		weight1
		2		time2
		3		weight2
		4		time3
		4		weight3
		*		*
		*		*
		*		*
	end with 0x00
	*/
	uchar i;
	uchar tmp;
	for(i = 0;i<10;i++)
	{
		tmp = At24c02Read(i*2);
		if (tmp == 0x25) break;
		feed_time[i] = tmp;
		feed_weigth[i] = At24c02Read(i*2+1);
	}
	feed_times = i;
	LcdClearScreen();
	LcdShowStr(1,0,"Param Init");
	if(i == 1)
		LcdShowStr(4,1,"error!");
	else
		LcdShowStr(4,1,"success!");
		VeryLongTimeDelay();
		LcdClearScreen();
	now_feed_time = feed_times + 1;
}


void init()
{
	P1 = 0x00;
	UsartInit();
	InitLcd1602();
#ifdef hx711
	WeightInit();
#endif
	ParamInit();
	
}



uchar isenough()	 //to test the food box wether food fed is enough
{

#ifdef hx711
	int i = 5000;
	while(i--);
	GetWeight();
//	serial_print(num16tochar(Weight_food));
//	serial_print("g\n");
	if (now_feed_time <= feed_times)
		if(Weight_food < (feed_weigth[now_feed_time] - CORRECTION) * 10) return 0;
		else return 1;
	else
		if(Weight_food < (feed_weigth[0] - CORRECTION) * 10) return 0;
		else return 1;
#else
	 return 1;

#endif

}

uchar isfeed() //to test  wether it's time to feed
{

	char i;
	char ret = 0;
	Ds1302ReadTime();
	TimeDelay();
	for(i = 0; i< feed_times;i++)
	{
		if (RTIME[2] == feed_time[i])
		{
			if (RTIME[2] == feed_time[now_feed_time]) 
				break;
			else
			{
				now_feed_time = i;
				ret = 1;
			}
		}
	}
	return ret;
}

uchar isempty() //to test the food box wether is empty
{
	measure();
	TimeDelay();
	if (S > 1000)
	{
		serial_print("Empty\n");
		isSendFull = 1;
		return 1;
	}
	else
	{
		if(isSendFull)
		{
			serial_print("Not Empty\n");
		 	isSendFull = 0;
		}
		return 0;
	}
}

void Keypro()
{
	P1 = 0xf0;
	TimeDelay();
	key = P1 & 0xf0;
	if (key != 0xF0)
	{
		TimeDelay();
		P1 = 0xf0;
		key = P1 & 0xf0;
		if (key == 0xF0) key = 0;
	}
	if (key == 0x70)
	{
		isauto = ~isauto;
		key = 0;
	}
}

void isopened()	 //to test wether box is opend
{
	if(openPin == 0)
	{
		serial_print("box opened\n");
		LcdShowStr(0,0,"Box Opened");
		VeryLongTimeDelay();
		LcdClearScreen();
		LcdShowStr(0,0,"Please close it");
		while(!openPin);
		LcdClearScreen();
		LcdShowStr(0,0,"Box Closed");
		serial_print("box closed\n");
		isSendFull = 1;
		VeryLongTimeDelay();
		LcdClearScreen();
	}	
}

void feed()
{
	EA = 0;
#ifdef hx711
	if(isenough())
	{
		LcdClearScreen();
		LcdShowStr(0,0,"Food is enough!");
		VeryLongTimeDelay();
		serial_print("don't need to feed\n");
		LcdClearScreen();
	}
	else
#endif
	{
		LcdClearScreen();
		LcdShowStr(0,0,"Feeding..");
		serial_print("feed start\n");
		open();
#ifdef hx711
		while(!isenough());
#else
		feed_delay(feed_weigth[now_feed_time]);
#endif
		LcdClearScreen();
		LcdShowStr(0,0,"Closeing..");
		close();
		LcdClearScreen();
		LcdShowStr(0,0,"Closed");
		VeryLongTimeDelay();
		LcdClearScreen();
		serial_print("Feed over\n");
		isSendFull = 1;
	}
	EA = 1;
}

void ShowTime()
{
	LcdShowStr(0,0,"20");
	DisplayOneChar(2,0,((RTIME[6] >> 4)&0x0f)|0x30);
	DisplayOneChar(3,0,(RTIME[6]&0x0f)|0x30);
	
	DisplayOneChar(4,0,'-');
	DisplayOneChar(5,0,((RTIME[4] >> 4)&0x0F)|0x30);
	DisplayOneChar(6,0,(RTIME[4]&0x0f)|0x30);
	
	DisplayOneChar(7,0,'-');
	DisplayOneChar(8,0,((RTIME[3] >> 4)&0x0F)|0x30);
	DisplayOneChar(9,0,(RTIME[3]&0x0f)|0x30);
	

	DisplayOneChar(6,1,((RTIME[2] >> 4)&0x0F)|0x30);
	DisplayOneChar(7,1,(RTIME[2]&0x0f)|0x30);
	
	DisplayOneChar(8,1,':');
	DisplayOneChar(9,1,((RTIME[1] >> 4)&0x0F)|0x30);
	DisplayOneChar(10,1,(RTIME[1]&0x0f)|0x30);
	
	DisplayOneChar(11,1,':');
	DisplayOneChar(12,1,((RTIME[0] >> 4)&0x0F)|0x30);
	DisplayOneChar(13,1,(RTIME[0]&0x0f)|0x30);
	
}

void main()
{	
	bit show = 1;
	char i = 0;
	init();
	while(1)
	{
		isopened();
		if(isempty())
		{
			LcdClearScreen();
			LcdShowStr(0,1,"NO stored food!");
			VeryLongTimeDelay();
			LcdClearScreen();
		}
		CmdPro();
		Keypro();
		LcdClearScreen();
		if(!isauto)
		{
			if(isfeed()) feed();
			if (key == 0xB0)
			{
				show = ~show;
				key = 0;
				if (now_feed_time > feed_times)	i = 0;
				else i = now_feed_time;
			}
			if (key == 0xD0)
			{
				i ++;
				if (i >= feed_times) i = 0;
				key = 0;
			}
			if (key == 0xE0)
			{
				i --;
				if (i < 0) i = feed_times-1;
				key = 0;
			}
				
			if (show == 1)
			{
				LcdShowStr(15,0,"A");
				ShowTime();
			}
			else
			{
				LcdShowStr(0,0,"Feed Plan:");
				LcdShowStr(0,1,"Time:");
				DisplayOneChar(5,1,((feed_time[i] >> 4)&0x0f)|0x30);
				DisplayOneChar(6,1,(feed_time[i]&0x0f)|0x30);
				LcdShowStr(8,1,"WT:");
				LcdShowStr(11,1,num8tochar(feed_weigth[i]));
				LcdShowStr(14,1,"0g");
			}
		}
		else
		{
			isfeed();
			if (key == 0xB0)
			{
				feed();
				key = 0;
			}
			if (key == 0xD0)
			{
				LcdShowStr(0,1,"manual open");
				serial_print("MOPEN\n");
				isSendFull = 1;
				open();
				LcdClearScreen();
				key = 0;
			}
			if (key == 0xE0)
			{
				LcdShowStr(0,1,"manual close");
				serial_print("MCLOSE\n");
				isSendFull = 1;
				close();
				LcdClearScreen();
				key = 0;
			}
			LcdShowStr(15,0,"M");
			_nop_();
			ShowTime();
		}
		isenough();	
	}
}

