#include "allHeaders.h"

SDL_Surface *screen;
uint8_t scr[128][64];
uint8_t cursor_x;
uint8_t cursor_y;

int lcd_init(){
	Uint32 initflags = SDL_INIT_VIDEO;  /* See documentation for details */
	Uint8  video_bpp = 8;
	Uint32 videoflags = SDL_HWSURFACE;
	
	/* Initialize the SDL library */
	if ( SDL_Init(initflags) < 0 ) {
		fprintf(stderr, "Couldn't initialize SDL: %s\n",
				SDL_GetError());
		exit(1);
	}
	
	/* Set 516x260 video mode */
	screen=SDL_SetVideoMode(516,260, video_bpp, videoflags);
	if (screen == NULL) {
		fprintf(stderr, "Couldn't set 516x260x%d video mode: %s\n",
				video_bpp, SDL_GetError());
		SDL_Quit();
		exit(2);
	}
	
	SDL_Rect new;
	new.x = 0;
	new.y = 0;
	new.w = 516;
	new.h = 260;
	SDL_FillRect(screen, &new, SDL_MapRGB(screen->format, 170, 220, 100));
	new.x = 2;
	new.y = 2;
	new.w = 3;
	new.h = 3;
	int i = 0;
	int j = 0;
	for(i = 0; i < 128; i++){
		for(j = 0; j < 64; j++){
			SDL_FillRect(screen, &new, SDL_MapRGB(screen->format, 120, 170, 50));
			new.y += 4;
			scr[i][j] = 0;
		}
		new.y = 2;
		new.x += 4;
	}
	
	SDL_UpdateRect(screen, 0, 0, 0, 0);
	
	return 1;
}

void lcd_draw_fullscreen_bmp(uint8_t* bitmap){
	int i = 0;
	int j = 0;
	uint8_t cmp = 1;
	
	for(i = 0; i < 1024; i++){
		for(j = 0; j < 8; j++){
			if(j == 0){
				cmp = 1;
			}else{
				cmp *= 2;
			}
			if(bitmap[i] & cmp){
				lcd_set_pixel(127-(i%128), 63-((i/128)*8+j), 1);
			}
		}
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void lcd_set_pixel(int x, int y, Uint8 color){
	if(x >= 128 || y >= 64) return;
	SDL_Rect pixel;
	pixel.w = 3;
	pixel.h = 3;
	pixel.x = x*4+2;
	pixel.y = y*4+2;
	
	if(color > 0){
		scr[x][y] = 1;
		SDL_FillRect(screen, &pixel, SDL_MapRGB(screen->format, 0, 0, 0));
	}else{
		scr[x][y] = 0;
		SDL_FillRect(screen, &pixel, SDL_MapRGB(screen->format, 120, 170, 50));
	}
}

void lcd_clear(){
	int i = 0;
	int j = 0;
	for(i = 0; i < 128; i++){
		for(j = 0; j < 64; j++){
			lcd_set_pixel(i, j, 0);
		}
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void lcd_invert(){
	int i = 0;
	int j = 0;
	for(i = 0; i < 128; i++){
		for(j = 0; j < 64; j++){
			if(scr[i][j] == 0){
				lcd_set_pixel(i, j, 1);
			}else{
				lcd_set_pixel(i, j, 0);
			}
		}
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void lcd_draw_line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
	uint8_t cnt;
	
	uint8_t dy,dx,x,y;
	int8_t	addx, addy;
	int16_t err;
	
	if (x1==x2 || y1==y2)
	{
		if (x1==x2)
		{
			for (cnt=min(y1,y2);cnt<=max(y1,y2);cnt++)			
				lcd_set_pixel(x1,cnt,color);			
		}
		else
		{
			for (cnt=min(x1,x2);cnt<=max(x1,x2);cnt++)			
				lcd_set_pixel(cnt,y1,color);			
		}
	}
	else
	{
   		dx = max(x1,x2)-min(x1,x2);
   		dy = max(y1,y2)-min(y1,y2);
		
   		x = x1;
   		y = y1;
		
	   	if(x1 > x2)
			addx = -1;
	   	else
			addx = 1;
		
	   	if(y1 > y2)
			addy = -1;
	   	else
			addy = 1;
		
	   	if(dx >= dy)
	   	{
			err = 2*dy - dx;
			
			for(cnt=0; cnt<=dx; ++cnt)
			{
				lcd_set_pixel(x, y, color);
				
				if(err < 0)
				{
					err += 2*dy;
					x += addx;
				}
				else
				{
					err += 2*dy - 2*dx;
					x += addx;
					y += addy;
				}
			}
	   	}
	   	else
	   	{
			err = 2*dx - dy;
			
			for(cnt=0; cnt<=dy; ++cnt)
			{
				lcd_set_pixel(x, y, color);
				
				if(err < 0)
				{
					err += 2*dx;
					y += addy;
				}
				else
				{
					err += 2*dx - 2*dy;
					x += addx;
					y += addy;
				}
			}
	  	}	
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void lcd_draw_rect(uint8_t x,uint8_t y,uint8_t width,uint8_t height,uint8_t color)
{
	lcd_draw_line(x,y,x+width-1,y,color);					// Top Line
	lcd_draw_line(x+width-1,y,x+width-1,y+height-1,color); 	// Left Line
	lcd_draw_line(x,y+height-1,x+width-1,y+height-1,color);	// Bottom Line
	lcd_draw_line(x,y,x,y+height-1,color);					// Right Line
}

void lcd_fill_rect(uint8_t x,uint8_t y,uint8_t width,uint8_t height,uint8_t color)
{
	uint8_t cnt_x,cnt_y;
	for (cnt_y=y;cnt_y<y+height;cnt_y++)				// fill screen using set_pixel (slow) but needs less memory
		for (cnt_x=x;cnt_x<x+width;cnt_x++)
			lcd_set_pixel(cnt_x,cnt_y,color);
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

// text-output functions

uint8_t font_number_of_chars(uint8_t* font)	
{	
	return(font[5]); // return number of characters stored in this font	
}

uint8_t font_first_char(uint8_t*font)	
{	
	return(font[4]); // return the first used char of the font	
}

uint8_t font_char_width(uint8_t* font,uint8_t chr)
{
	return(font[6+(chr-font_first_char(font))]);	// return the width of the given character
}


uint8_t font_char_present(uint8_t* font,uint8_t chr)
{
	if ( (chr>= font_first_char(font)) && (chr<=font_first_char(font) + font_number_of_chars(font)-1)) // check if char is present
		return(1);
	else
		return(0);
}

uint8_t font_char_height(uint8_t*font)
{
	return(font[3]); // return the first used char of the font
}

uint16_t font_start_offset(uint8_t*font,uint8_t chr) 
{
	uint16_t offset=(uint16_t)0x0000;
	uint8_t cnt;
	uint8_t height= (font_char_height(font)-1)/8;
	
	for (cnt= font_first_char(font);cnt<chr;cnt++)
	{
		offset+=font_char_width(font,cnt) * (height+1); // width * (number of pages) needed for each char
	}	
	
	offset+=font_number_of_chars(font)+6;				// add 6 for the header-bytes and the number of bytes need for the width-array
	
	return offset;
}

void lcd_set_cursor(uint8_t x, uint8_t y){		
	if(x<128)	cursor_x=x;
	if(y<64) 	cursor_y=y;
}

void lcd_putc(uint8_t* font,uint8_t chr)
{
	uint8_t x,page,bit,data,cnt=0;
	
	if (font_char_present(font,chr)==1)	// print only if letter is present in font
	{
		if ( ( (cursor_x + font_char_width(font,chr)) <128)  && ((cursor_y+font_char_height(font))<=64))	// only print leeter if it fits in screen
		{
			uint16_t offset= font_start_offset(font,chr);	// get the position of the first byte in font-array
			
			for(page=0;page<=(font_char_height(font)-1)/8;page++)	// write all pages(rows)
			{				
				for (x=cursor_x;x<cursor_x + font_char_width(font,chr);x++)	//fill "pages"
				{
					data= font[offset+cnt++];
					
					if ( page==font_char_height(font)/8)		
						data>>=8-(font_char_height(font)%8);	// if char height is bigger than 8 we have to remove some leading zeros
				
					for (bit=0;bit<8;bit++)
					{
						if ((data&(1<<bit))!=0)
							lcd_set_pixel(x,cursor_y+page*8+bit,BLACK);
					}
				}			
			}			
			cursor_x += font_char_width(font,chr)+1;
			
			
		}
	}
}

void lcd_puts(uint8_t* font,char* string){
	while(*string){
		lcd_putc(font,*string++);
	}
	SDL_UpdateRect(screen, 0, 0, 0, 0);
}

void lcd_puts_p(uint8_t* font,char* string){
	while(*string){
		lcd_putc(font,*string++);
	}
}