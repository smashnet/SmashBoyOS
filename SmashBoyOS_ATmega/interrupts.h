#ifndef _INTERRUPTS_H
#define _INTERRUPTS_H

#include "allHeaders.h"

volatile unsigned char zustand[6];
volatile unsigned char pushed[6];

ISR(TIMER0_OVF_vect);
void getButtons();
void delayMs(int ms);
void initTimer();

#endif