#include "HX711.h"

long Weight_self = 0;
long Weight_food = 0;

unsigned long ReadCount(void)
{
	unsigned long Count;
	unsigned char i;
	HX711_SCK=0; // ʹ�� AD �� PD_SCK  �õͣ�
	Count=0;
	while(HX711_DOUT); //AD ת��δ������ȴ�������ʼ��ȡ
	for (i=0;i<24;i++)
	{
		HX711_SCK=1; //PD_SCK  �øߣ��������壩
		Count=Count<<1; // �½�����ʱ���� Count ����һλ���Ҳಹ��
		HX711_SCK=0; //PD_SCK  �õ�
		if(HX711_DOUT) Count++;
	}
	HX711_SCK=1;
	Count=Count^0x800000;// �� 25 �������½�����ʱ��ת������
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