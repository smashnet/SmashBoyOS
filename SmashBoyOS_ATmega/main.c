#include "allHeaders.h"

int main(void){
	// Initializations
	initButtons();
	initTimer();
	lcd_init();
	lcd_clear();
	sei();
	
	myprog();
	
	/*
	while(!pushed[0]);
	
	lcd_clear();
	
	while(1){
		if(pushed[0]) lcd_putc(small_font,'a');
		if(pushed[1]) lcd_putc(small_font,'b');
		if(pushed[2]) lcd_putc(small_font,'u');
		if(pushed[3]) lcd_putc(small_font,'d');
		if(pushed[4]) lcd_putc(small_font,'r');
		if(pushed[5]) lcd_putc(small_font,'l');
	}*/
	/*
	lcd_set_cursor(0,LINE0);
	lcd_puts(small_font,"SmashBoy Draft 1");
	
	lcd_draw_line(0,LINE1,127,LINE1,BLACK);
	
	lcd_set_cursor(0,LINE2);
	lcd_puts(small_font,"Stay tuned for more!");
	
	lcd_set_cursor(0,LINE4);
	lcd_puts(small_font,"Nico");
	*/

	return 0;
}

void initButtons(){
	//init buttons
	sbi(DDRD,2); // a
	sbi(DDRD,3); // b
	sbi(DDRB,0); // up
	sbi(DDRB,1); // down
	sbi(DDRB,2); // right
	sbi(DDRB,3); // left
	// pullups
	sbi(PORTD,2); // a
	sbi(PORTD,3); // b
	sbi(PORTB,0); // up
	sbi(PORTB,1); // down
	sbi(PORTB,2); // right
	sbi(PORTB,3); // left
}
