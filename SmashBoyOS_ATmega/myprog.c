#include "allHeaders.h"

int myprog(){
    lcd_draw_fullscreen_bmp(img);	
	delayMs(3000);
	lcd_clear();
	lcd_set_cursor(0, 0);
	lcd_puts(small_font, "Main Menu");
	lcd_draw_line(0, 10, 127, 10, BLACK);
	lcd_set_cursor(5, 12);
	lcd_puts(small_font, "Tetris");
	lcd_set_cursor(5, 20);
	lcd_puts(small_font, "Snake");
	lcd_set_cursor(5, 27);
	lcd_puts(small_font, "Pong");
    
    return 1;
}