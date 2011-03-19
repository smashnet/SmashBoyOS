#ifndef _LCD_H
#define _LCD_H

SDL_Surface *screen;
uint8_t scr[128][64];

int lcd_init();
void lcd_draw_fullscreen_bmp(Uint8 *bitmap);
void lcd_set_pixel(int x, int y, Uint8 color);
void lcd_clear();
void lcd_invert();
void lcd_draw_line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color);
void lcd_draw_rect(uint8_t x,uint8_t y,uint8_t width,uint8_t height,uint8_t color);
void lcd_fill_rect(uint8_t x,uint8_t y,uint8_t width,uint8_t height,uint8_t color);
uint8_t font_number_of_chars(uint8_t* font);
uint8_t font_first_char(uint8_t*font);
uint8_t font_char_width(uint8_t* font,uint8_t chr);
uint8_t font_char_present(uint8_t* font,uint8_t chr);
uint8_t font_char_height(uint8_t*font);
uint16_t font_start_offset(uint8_t*font,uint8_t chr);
void lcd_set_cursor(uint8_t x, uint8_t y);
void lcd_putc(uint8_t* font,uint8_t chr);
void lcd_puts(uint8_t* font,char* string);
void lcd_puts_p(uint8_t* font,char* string);

#endif
