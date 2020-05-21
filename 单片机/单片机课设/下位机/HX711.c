#include "HX711.h"

long Weight_self = 0;
long Weight_food = 0;

unsigned long ReadCount(void)
{
	unsigned long Count;
	unsigned char i;
	HX711_SCK=0; // 使能 AD （ PD_SCK  置低）
	Count=0;
	while(HX711_DOUT); //AD 转换未结束则等待，否则开始读取
	for (i=0;i<24;i++)
	{
		HX711_SCK=1; //PD_SCK  置高（发送脉冲）
		Count=Count<<1; // 下降沿来时变量 Count 左移一位，右侧补零
		HX711_SCK=0; //PD_SCK  置低
		if(HX711_DOUT) Count++;
	}
	HX711_SCK=1;
	Count=Count^0x800000;// 第 25 个脉冲下降沿来时，转换数据
	HX711_SCK=0;
	return(Count);
}

void GetWeight()
{
	Weight_food= ReadCount();
	Weight_food = Weight_food-Weight_self;
	if(Weight_food < 0) 
	{
		Weight_food = 0;
//		Weight_flag = 2;
		return;
	}
	Weight_food = (unsigned int)((float)Weight_food/9);	 //349
//	if(Weight_food > 5000) 
//		{
			//Weight_flag = 1;
			return;
//		}
//	else
	//	Weight_flag = 0;

}
void WeightInit()
{
	Weight_self = ReadCount();
}