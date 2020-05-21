#ifndef _MAIN_H
#define _MAIN_H

//#define hx711 //wether use hx711

#include "serial.h"
#include "feed_motor.h"
#include "lcd.h"
#include "ultrasonic.h"
#include "mem.h"
#include "RTC.h"
#include "HX711.h"
#include "CmdPro.h"
#include "common.h"

#define CORRECTION 1//used to compensate the weight of food feeded while motor is moving;
sbit openPin = P3^3;

extern uchar feed_time[10];
extern uchar feed_weigth[10];
extern uchar feed_times;

void ParamInit();
#endif