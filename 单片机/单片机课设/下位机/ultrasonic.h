/*
use T0 for a short time
use P2.1 and P2.0 (can be changed)

*/

#ifndef _ULTRASONIC_H
#define _ULTRASONIC_H

#include "common.h"


sbit Trig = P2^3;
sbit Echo = P2^4;

void measure(void);

extern unsigned long S;

#endif