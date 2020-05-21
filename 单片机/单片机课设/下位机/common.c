#include "common.h"

char* num8tochar(u8 num)
{	
	char ret[4];
    ret[0] = num/100 + 0x30;
	ret[1] = num%100/10 + 0x30;
    ret[2] = num%10 + 0x30;
	ret[3] = 0;
    return(ret);
}

char* num16tochar(u16 num)
{
	char ret[6];
	ret[0] = num/10000 + 0x30;
    ret[1] = num%10000/1000 + 0x30;
    ret[2] = num%1000/100 + 0x30;
	ret[3] = num%100/10 + 0x30;
    ret[4] = num%10 + 0x30;
	ret[5] = 0;
    return(ret);
}