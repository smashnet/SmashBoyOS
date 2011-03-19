#include "allHeaders.h"

// ##################################################################################################
// #																								#
// #   Name: ks0108.c																				#
// #   Author: Andre Fabricius  (mailto:master.andre@web.de)										#
// #   Date: 13.08.08 18:32																		    #
// #   Description: GLCD routines for KS0108 or compatibel controllers							    #
// #																								#
// ##################################################################################################
// #																								#
// # Copyright (C) 2008  Andre Fabricius															#
// #																								#
// # This program is free software; you can redistribute it and/or modify it under the terms of 	#
// # the GNU General Public License as published by the Free Software Foundation; either version 3 	#
// # of the License, or (at your option) any later version.											#
// #																								#
// # This program is distributed in the hope that it will be useful, but WITHOUT ANY WARRANTY; 		#				
// # without even the implied warranty of MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. 		#
// # See the GNU General Public License for more details.											#
// # You should have received a copy of the GNU General Public License along with this program; 	#
// # if not, see <http://www.gnu.org/licenses/>.													#
// #																								#
// ##################################################################################################



// ###############################################################################################
// # 																		   					 #
// # Low Level functions	(HW-LAYER)															 #
// #																							 #
// ###############################################################################################
volatile uint8_t cursor_x,cursor_y,invert=0; // cursor position
// ----------------------
// Controller selection
// ----------------------
void lcd_chip_select(uint8_t chip)
{
	if (chip == (CHIP1|CHIP2))
	{
		LCD_CS_PORT |=   (1<<CS1) | (1<<CS2);
		return;
	}

	if (chip == CHIP1)
	{
		LCD_CS_PORT &=	~(1<<CS2);	
		LCD_CS_PORT |=  (1<<CS1);	
		return;
	}

	if (chip == CHIP2)
	{ 							
	 	LCD_CS_PORT 	&=	~(1<<CS1);
		LCD_CS_PORT 	|=   (1<<CS2);
		return;
	}

	LCD_CS_PORT 	&=	~((1<<CS1)|(1<<CS2));
	return;	
}



// ---------------------------------
// Set Command mode, and write data
// ---------------------------------
void lcd_write_cmd(uint8_t cmd ,uint8_t chip)
{	
	lcd_chip_select(chip);
	LCD_CMD_PORT &= ~((1<<CD)|(1<<RW));		// we're in command mode
	lcd_write(cmd,chip);
}



// ---------------------------------
// Set Data mode, and write data
// ---------------------------------
void lcd_write_data(uint8_t data ,uint8_t chip)
{
	if (invert!=0)	data = ~data;	
	lcd_chip_select(chip);
	LCD_CMD_PORT |= (1<<CD);
	LCD_CMD_PORT &= ~(1<<RW);				// we're in data mode
	lcd_write(data,chip);
}



// ------------------------
// Write Data
// ------------------------
void lcd_write(uint8_t val,uint8_t chip)
{
	LCD_DATA_DDR = 0xff;
	LCD_DATA_PORT = val;

	LCD_CMD_PORT |= (1<<EN);
	_delay_us(1);					// >500ns
	LCD_CMD_PORT &= ~(1<<EN);

	if (chip== (CHIP1|CHIP2))
	{
		lcd_chip_select(CHIP1);
		wait_while_chip_is_busy();	// this could be exchanged by a little delay (this is the safe way)

		lcd_chip_select(CHIP2);
		wait_while_chip_is_busy();	

		lcd_chip_select(CHIP1|CHIP2);
	}
	else
	{
		wait_while_chip_is_busy();	// this could be exchanged by a little delay (this is the safe way)
	}

	LCD_DATA_PORT=0x00;					
}



// --------------------
// Read Data
// --------------------
uint8_t lcd_read_data(uint8_t chip)
{
	uint8_t temp_data;

	lcd_chip_select(chip);
	wait_while_chip_is_busy();

	LCD_DATA_DDR = 0xFF;	// perhaps some controllers prefer to pull
	LCD_DATA_PORT = 0xFF;

	LCD_DATA_DDR = 0x00;	// now data port is input

	LCD_CMD_PORT |= (1<<RW) | (1<<CD);

	LCD_CMD_PORT |= (1<<EN);	// request data
	_delay_us(1);				// wait a moment until data is (hopefully) stable
	if (invert!=0) 
		temp_data = ~LCD_DATA_PIN;	// read data	
	else
		temp_data = LCD_DATA_PIN;	// read data
	LCD_CMD_PORT &= ~(1<<EN);	// end of request

	wait_while_chip_is_busy();	// give him some time
	return(temp_data);
}



// -----------------------------------
// hmmm wait while chip is BUSY ?! 
// -----------------------------------
void wait_while_chip_is_busy()
{
	LCD_DATA_DDR = 0xFF;	// perhaps some controllers prefer to pull
	LCD_DATA_PORT= 0xFF;

	LCD_DATA_DDR = 0x00;	// dataport is input
	LCD_CMD_PORT &= ~(1<<CD);

	LCD_CMD_PORT |=(1<<RW)|(1<<EN);
	_delay_us(1);

	while((LCD_DATA_PIN & LCD_BUSY)!=0)	// poll busy flag
	{
		LCD_CMD_PORT &= ~(1<<EN);
		_delay_us(1);
		LCD_CMD_PORT |= (1<<EN);
		_delay_us(1);
	}

	LCD_CMD_PORT &= ~((1<<EN)|(1<<RW));
	LCD_DATA_DDR = 0xFF;
}


//###############################################################################################
//# 																							#
//# Basic Functions																				#
//#																								#
//###############################################################################################


// ----------------------
// Init LCD Controllers
// ----------------------
void lcd_init()
{
	#ifndef LCD_NO_RES
		LCD_CMD_DDR |= (1<<CD) | (1<<RW) | (1<<EN) | (1<<RES);
		LCD_CS_DDR	|= (1<<CS1) | (1<<CS2);
	#else
		LCD_CMD_DDR |= (1<<CD) | (1<<RW) | (1<<EN);
		LCD_CS_DDR	|= (1<<CS1) | (1<<CS2); 
	#endif

	lcd_chip_select(CHIP1|CHIP2);

	#ifndef LCD_NO_RES
	LCD_CMD_PORT &= ~(1<<RES);	// pull reset low for a moment
	
	_delay_ms(30);
	LCD_CMD_PORT |= (1<<RES);	// let reset rise	
	#endif

	lcd_write_cmd(LCD_ON,CHIP1|CHIP2);
	lcd_write_cmd(LCD_DISP_START|0,CHIP1|CHIP2);
	lcd_write_cmd(LCD_SET_ADD|0,CHIP1|CHIP2);
	lcd_write_cmd(LCD_SET_PAGE|0,CHIP1|CHIP2);

	cursor_x=0;cursor_y=0;	
}



//----------------------------
// Clear the Display
//----------------------------
void lcd_clear()
{
	uint8_t x,y;

	for (y=0;y<8;y++)
	{
		lcd_write_cmd(LCD_SET_PAGE|y,CHIP1|CHIP2);	//set page on both controllers
		lcd_write_cmd(LCD_SET_ADD|0,CHIP1|CHIP2);	//set adress on both controllers

		for (x=0;x<=63;x++)
			lcd_write_data(0x00,CHIP1|CHIP2);		//set all 64 pages of this line on both controllers to 0
	}

	lcd_write_cmd(LCD_SET_ADD|0,CHIP1|CHIP2);		//set hom home pos
	lcd_write_cmd(LCD_SET_PAGE|0,CHIP1|CHIP2);
}


//----------------------------
// Set Pixel BLACK or WHITE
//----------------------------
void lcd_set_pixel(uint8_t x,uint8_t y, uint8_t color)
{
	#ifdef FLIP_H
		y = 63-y;
		x = 127-x;
	#endif
	
	uint8_t current_chip=CHIP1;
	uint8_t temp=y/8;			// select page

	if ((x<128) && (y<64))		// check position
	{	
		if (x>63)				// select controller chip
		{
			current_chip=CHIP2;
			x-=64;
		}		
	
		lcd_write_cmd(LCD_SET_PAGE|temp,current_chip);	// goto page in which our pixel is stored
		lcd_write_cmd(LCD_SET_ADD|x,current_chip);	
			
		temp = lcd_read_data(current_chip);				// something buggy here !!! need one dummy read to get right data
		lcd_write_cmd(LCD_SET_ADD|x,current_chip);	

		temp = lcd_read_data(current_chip);
		lcd_write_cmd(LCD_SET_ADD|x,current_chip);	
		
		if (color==BLACK)		
			temp |= (1<<(y%8));							// change pixel color to black
		else
			temp &= ~(1<<(y%8));						// change pixel color to white

		lcd_write_data(temp,current_chip);
			
	}	

}

// ---------------------------------------------
// inverts the screen and sets mode to inverted
// ---------------------------------------------
void lcd_invert()
{

	uint8_t x,y,data;

	for (y=0;y<8;y++)
	{
		lcd_write_cmd(LCD_SET_PAGE|y,CHIP1|CHIP2);	//set page on both controllers

		for (x=0;x<=63;x++)
		{
			lcd_write_cmd(LCD_SET_ADD|x,CHIP1);	
			data=lcd_read_data(CHIP1);
			lcd_write_cmd(LCD_SET_ADD|x,CHIP1);	//read two times (dont know why, but else i get buggy outpur)
			data=lcd_read_data(CHIP1);

			lcd_write_cmd(LCD_SET_ADD|x,CHIP1);	
			lcd_write_data(~data,CHIP1);		//set inverter data
			
			lcd_write_cmd(LCD_SET_ADD|x,CHIP2);	// do the same on the second controller
			data=lcd_read_data(CHIP2);
			lcd_write_cmd(LCD_SET_ADD|x,CHIP2);	
			data=lcd_read_data(CHIP2);

			lcd_write_cmd(LCD_SET_ADD|x,CHIP2);	
			lcd_write_data(~data,CHIP2);		
		}
	}

	lcd_write_cmd(LCD_SET_ADD|0,CHIP1|CHIP2);		//set hom home pos
	lcd_write_cmd(LCD_SET_PAGE|0,CHIP1|CHIP2);

	invert++;
	invert %=2;
}


// ------------------------------------
// Draw an fullscreen Bitap 
// ------------------------------------
#ifndef NO_BMP
void lcd_draw_fullscreen_bmp(uint8_t* bitmap)
{  
	// INFO:
	// data is organized page after page (0-to-127)
	// (LSB-to-MSB TOP-to-Bottom)
	// from 0 to 127 in eight lines (127*8=1024 Byte)

	uint16_t byte=0;
	uint8_t x,y;
	for (y=0;y<8;y++)
	{
		lcd_write_cmd(LCD_SET_PAGE|y,CHIP1|CHIP2);	//	start a new page
		lcd_write_cmd(LCD_SET_ADD|0,CHIP1|CHIP2);	//  start at 0
		for (x=0;x<128;x++)
		{
			if (x<64)			
				lcd_write_data(pgm_read_byte(bitmap+(byte++)),CHIP1);			
			else			
				lcd_write_data(pgm_read_byte(bitmap+(byte++)),CHIP2);			
		}	
	}
	

	/* 
		this was used to test lcd_set_pixel	
		(can be used to overlay a bmp to current screen)
	*/

	/*	  	
	uint16_t byte=0;
	uint8_t x,y,bit,temp;
	for (y=0;y<8;y++)
	{
		 for(x=0;x<128;x++)
		 {
		 	temp= pgm_read_byte(bitmap+(byte++));
		 	for (bit=0;bit<8;bit++)			
				if ((temp& (1<<bit))!=0)
					lcd_set_pixel(x,y*8+bit,BLACK);			
		 }
	}
	*/
	
}
#endif //no-bmp



// ###############################################################################################
// # 																							 #
// # Text output																				 #
// #																							 #
// ###############################################################################################

#ifndef NO_TEXT
// ---------------------------------
// get the count of chars in font
// ---------------------------------
uint8_t font_number_of_chars(uint8_t* font)	
{	
	return(pgm_read_byte(font+5)); // return number of characters stored in this font	
}



// ---------------------------------
// get first char in font
// ---------------------------------
uint8_t font_first_char(uint8_t*font)	
{	
	return(pgm_read_byte(font+4)); // return the first used char of the font	
}



// ---------------------------------
// get width of given char
// ---------------------------------
uint8_t font_char_width(uint8_t* font,uint8_t chr)
{
	return(pgm_read_byte(font+6+(chr-font_first_char(font))));	// return the width of the given character
}


// ----------------------------------------
// check if given char is present in font
// ----------------------------------------
uint8_t font_char_present(uint8_t* font,uint8_t chr)
{
	if ( (chr>= font_first_char(font)) && (chr<=font_first_char(font) + font_number_of_chars(font)-1)) // check if char is present
		return(1);
	else
		return(0);
}

// ---------------------------------
// get height of font
// ---------------------------------
uint8_t font_char_height(uint8_t*font)
{
	return(pgm_read_byte(font+3)); // return the first used char of the font
}

// ---------------------------------
// get the start offset of char
// ---------------------------------
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

// ---------------------------------
// set cursor to x,y
// ---------------------------------
void lcd_set_cursor(uint8_t x, uint8_t y)
{		
	if(x<128)	cursor_x=x;
	if(y<64) 	cursor_y=y;
}

// ---------------------------------
// put char to screen
// ---------------------------------
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
				lcd_write_cmd(LCD_SET_PAGE|((cursor_y/8)+page),CHIP1|CHIP2);	// calc the current page

				if (cursor_x<64)	// set cursor to its poition (0 on the inactive controller so it can start directly on chip change)
				{
					lcd_write_cmd(LCD_SET_ADD|cursor_x,CHIP1);
					lcd_write_cmd(LCD_SET_ADD|0,CHIP2);
				}
				else
				{
					lcd_write_cmd(LCD_SET_ADD|(cursor_x-64),CHIP2);				
				}

				for (x=cursor_x;x<cursor_x + font_char_width(font,chr);x++)	//fill "pages"
				{
					data= pgm_read_byte(font+offset+cnt++);

					if ( page==font_char_height(font)/8)		
						data>>=8-(font_char_height(font)%8);	// if char height is bigger than 8 we have to remove some leading zeros
					
					#ifdef FASTTEXT								// this is much much faster than using set_pixel (see discription in header file)
					if (cursor_y%8==0 )
					{
						if (x<64)								
							lcd_write_data(data,CHIP1);						
						else									
							lcd_write_data(data,CHIP2);					
					}
					else
					#endif
					{
						for (bit=0;bit<8;bit++)
						{
							if ((data&(1<<bit))!=0)
							 lcd_set_pixel(x,cursor_y+page*8+bit,BLACK);
						}
					}
				}			
				
				#ifdef FASTTEXT
				if(cursor_y%8==0)
				{
					if (x<64)								
						lcd_write_data(0,CHIP1);						
					else									
						lcd_write_data(0,CHIP2);				
				}
				#endif
			}			
			cursor_x += font_char_width(font,chr)+1;


		}
	}
}



// ---------------------------------
// put string to screen (from ram)
// ---------------------------------
void lcd_puts(uint8_t* font,char* string)
{while(*string)lcd_putc(font,*string++);}



// ---------------------------------------
// put string to screen (from flash)
// use: lcd_puts_p(PSTR("HELLO WORLD"));
// ---------------------------------------
void lcd_puts_p(uint8_t* font,char* PROGMEM string)
{while(pgm_read_byte(string))lcd_putc(font,pgm_read_byte(string++));}

#endif //no-text


// ###############################################################################################
// # 																							 #
// # Graphics																					 #
// #																							 #
// ###############################################################################################
#ifndef NO_GRAPHICS


// ---------------------------------
// draw line on screen
// ---------------------------------
void lcd_draw_line(uint8_t x1,uint8_t y1,uint8_t x2,uint8_t y2,uint8_t color)
{
	uint8_t cnt;

	#ifndef NO_BRESENHAM
	uint8_t dy,dx,x,y;
	int8_t	addx, addy;
	int16_t err;
	#endif

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
	#ifndef NO_BRESENHAM	// see header
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
	#endif //no_bresenham
}


// ---------------------------------
// draw rectangle on screen
// ---------------------------------
void lcd_draw_rect(uint8_t x,uint8_t y,uint8_t width ,uint8_t height,uint8_t color)
{
	lcd_draw_line(x,y,x+width-1,y,color);					// Top Line
	lcd_draw_line(x+width-1,y,x+width-1,y+height-1,color); 	// Left Line
	lcd_draw_line(x,y+height-1,x+width-1,y+height-1,color);	// Bottom Line
	lcd_draw_line(x,y,x,y+height-1,color);					// Right Line
}


// ------------------------------------
// fills an rectangle with given color
// ------------------------------------
void lcd_fill_rect(uint8_t x,uint8_t y,uint8_t width,uint8_t height,uint8_t color)
{
	uint8_t cnt_x,cnt_y;
		for (cnt_y=y;cnt_y<y+height;cnt_y++)				// fill screen using set_pixel (slow) but needs less memory
			for (cnt_x=x;cnt_x<x+width;cnt_x++)
				lcd_set_pixel(cnt_x,cnt_y,color);

}

#endif //no-graphics
