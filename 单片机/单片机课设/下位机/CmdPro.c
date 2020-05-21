#include "CmdPro.h"
/*

Commend Format
Head:
	{
		T: time
		F: feed information
		W: weight infomation(Read Only)
		M: manual feed
		S: ultrasonic distance
	}
Middle:	
	{
		S: SET
		R: Read
	}
Info:
	{
		Time: 
			[second,min,hour,day,month,week,year]
		Feed_info：
			[addr,time,weight]
	}
*/
void CmdPro()
{
	uchar i;
	wait_serial_cmd();
	if(New_Cmd)
	{
		New_Cmd = 0;
//		serial_print(RcvData);
//		serial_print("R\n");
		switch(RcvData[0])
		{
			case 'T':
			{
				if(RcvData[1] == 'S')
				{
					for(i = 0; i < 7; i++)
					{
						SET_TIME[i] = RcvData[i+2];
					}
					Ds1302Init();
				}
				else if(RcvData[1] == 'R')
				{
					serial_printu8(RTIME,7);
					serial_print("\n");
				}
				break;
			}
			case 'F':
			{
				if(RcvData[1] == 'S')
				{
					At24c02Write(RcvData[2]*2+1,RcvData[4]);
					for(i = 0; i<200;i++);
					for(i = 0; i<200;i++);
					At24c02Write(RcvData[2]*2,RcvData[3]);
					for(i = 0; i<200;i++);
					for(i = 0; i<200;i++);
					if (RcvData[3] == 0x25)
						ParamInit();
				}
				else if(RcvData[1] == 'R')
				{
					serial_print("FT");
					serial_printu8(feed_time,feed_times);
					serial_print("\n");
					serial_print("FW");
					serial_printu8(feed_weigth,feed_times);
					serial_print("\n");
				}
				break;
			}
			case 'W':
			{

				if(RcvData[1] == 'R')
				{
#ifdef hx711
					serial_print(num16tochar(Weight_food));
					serial_print("g\n");
#else
					serial_print("NO HX711");
#endif
				}
				break;
			}
			case 'M':
			{
				feed();
			}
			break;
			case 'S':
			{
				if(RcvData[1] == 'R')
				{
					serial_print(num16tochar(S));
					serial_print("cm\n");
				}
			}break;
		}
//		serial_print("ACK CMD\n");
	}
}