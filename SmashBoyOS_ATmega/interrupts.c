#include "allHeaders.h"

volatile unsigned char zustand[6];
volatile unsigned char pushed[6] = {0,0,0,0,0,0};
volatile unsigned char left = 0;
volatile unsigned char right = 0;

ISR(TIMER0_OVF_vect){
	getButtons();	
}

void getButtons(){
    // ------------------------------- Taste A -------------------------------
	if(zustand[0] == 0 && !(AB_BUTTON_PIN & (1<<A)))   //Taster wird gedrueckt (steigende Flanke)
    {
        zustand[0] = 1;
        pushed[0] = 1;
    }
    else if (zustand[0] == 1 && !(AB_BUTTON_PIN & (1<<A)))   //Taster wird gehalten
    {
         zustand[0] = 2;
         pushed[0] = 0;
    }
    else if (zustand[0] == 2 && (AB_BUTTON_PIN & (1<<A)))   //Taster wird losgelassen (fallende Flanke)
    {
        zustand[0] = 3;
        pushed[0] = 0;
    }
    else if (zustand[0] == 3 && (AB_BUTTON_PIN & (1<<A)))   //Taster losgelassen
    {
        zustand[0] = 0;
        pushed[0] = 0;
    }
	// ------------------------------- Taste B -------------------------------
	if(zustand[1] == 0 && !(AB_BUTTON_PIN & (1<<B)))   //Taster wird gedrueckt (steigende Flanke)
    {
        zustand[1] = 1;
        pushed[1] = 1;
    }
    else if (zustand[1] == 1 && !(AB_BUTTON_PIN & (1<<B)))   //Taster wird gehalten
    {
         zustand[1] = 2;
         pushed[1] = 0;
    }
    else if (zustand[1] == 2 && (AB_BUTTON_PIN & (1<<B)))   //Taster wird losgelassen (fallende Flanke)
    {
        zustand[1] = 3;
        pushed[1] = 0;
    }
    else if (zustand[1] == 3 && (AB_BUTTON_PIN & (1<<B)))   //Taster losgelassen
    {
        zustand[1] = 0;
        pushed[1] = 0;
    }
	// ------------------------------- Taste UP -------------------------------
	if(zustand[2] == 0 && !(STEER_BUTTON_PIN & (1<<UP)))   //Taster wird gedrueckt (steigende Flanke)
    {
        zustand[2] = 1;
        pushed[2] = 1;
    }
    else if (zustand[2] == 1 && !(STEER_BUTTON_PIN & (1<<UP)))   //Taster wird gehalten
    {
         zustand[2] = 2;
         pushed[2] = 0;
    }
    else if (zustand[2] == 2 && (STEER_BUTTON_PIN & (1<<UP)))   //Taster wird losgelassen (fallende Flanke)
    {
        zustand[2] = 3;
        pushed[2] = 0;
    }
    else if (zustand[2] == 3 && (STEER_BUTTON_PIN & (1<<UP)))   //Taster losgelassen
    {
        zustand[2] = 0;
        pushed[2] = 0;
    }
	// ------------------------------- Taste DOWN -------------------------------
	if(zustand[3] == 0 && !(STEER_BUTTON_PIN & (1<<DOWN)))   //Taster wird gedrueckt (steigende Flanke)
    {
        zustand[3] = 1;
        pushed[3] = 1;
    }
    else if (zustand[3] == 1 && !(STEER_BUTTON_PIN & (1<<DOWN)))   //Taster wird gehalten
    {
         zustand[3] = 2;
         pushed[3] = 0;
    }
    else if (zustand[3] == 2 && (STEER_BUTTON_PIN & (1<<DOWN)))   //Taster wird losgelassen (fallende Flanke)
    {
        zustand[3] = 3;
        pushed[3] = 0;
    }
    else if (zustand[3] == 3 && (STEER_BUTTON_PIN & (1<<DOWN)))   //Taster losgelassen
    {
        zustand[3] = 0;
        pushed[3] = 0;
    }
	// ------------------------------- Taste RIGHT -------------------------------
	if(zustand[4] == 0 && !(STEER_BUTTON_PIN & (1<<RIGHT)))   //Taster wird gedrueckt (steigende Flanke)
    {
		zustand[4] = 1;
	    pushed[4] = 1;
    }
    else if (zustand[4] == 1 && !(STEER_BUTTON_PIN & (1<<RIGHT)))   //Taster wird gehalten
    {
         zustand[4] = 2;
         pushed[4] = 0;
    }
    else if (zustand[4] == 2 && (STEER_BUTTON_PIN & (1<<RIGHT)))   //Taster wird losgelassen (fallende Flanke)
    {
        zustand[4] = 3;
        pushed[4] = 0;
    }
    else if (zustand[4] == 3 && (STEER_BUTTON_PIN & (1<<RIGHT)))   //Taster losgelassen
    {
        zustand[4] = 0;
        pushed[4] = 0;
    }
	// ------------------------------- Taste LEFT -------------------------------
	if(zustand[5] == 0 && !(STEER_BUTTON_PIN & (1<<LEFT)))   //Taster wird gedrueckt (steigende Flanke)
    {
		zustand[5] = 1;
		pushed[5] = 1;
    }
    else if (zustand[5] == 1 && !(STEER_BUTTON_PIN & (1<<LEFT)))   //Taster wird gehalten
    {
         zustand[5] = 2;
         pushed[5] = 0;
    }
    else if (zustand[5] == 2 && (STEER_BUTTON_PIN & (1<<LEFT)))   //Taster wird losgelassen (fallende Flanke)
    {
        zustand[5] = 3;
        pushed[5] = 0;
    }
    else if (zustand[5] == 3 && (STEER_BUTTON_PIN & (1<<LEFT)))   //Taster losgelassen
    {
        zustand[5] = 0;
        pushed[5] = 0;
    }
}

void delayMs(int ms){
	_delay_ms(ms);
}

void initTimer(){
	// Configure interrupts, prescaler 64
	// On F_CPU 16000000 ISR invokes 976,5625 times per second
	cbi(TCCR0,CS02);
	sbi(TCCR0,CS01);
	sbi(TCCR0,CS00);
	// Activate Timer0 interrupt on overflow flag
	sbi(TIMSK,TOIE0);
}