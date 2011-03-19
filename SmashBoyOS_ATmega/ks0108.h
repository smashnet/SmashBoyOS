// ##################################################################################################
// #																								#
// #   Name: ks0108.h																				#
// #   Author: Andre Fabricius  (mailto:master.andre@web.de)										#
// #   Date: 13.08.08 18:32																		    #
// #   Description: Header for GLCD routines for KS0108 or compatibel controllers				    #
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

// ##################################################################################################
// #																								#
// #		  Test-Configuration:	ATMEGA8535 @ 16MHz												#
// #								PowerTip PG12864K (PG12864WRF-KNN-H)							#
// #								WinAVR-20070525													#
// #								AVR Studio V4.13 Build 571										#
// #																								#
// #Also successfully tested on:	ATMEGA32 @ 16Mhz												#
// #								TG12864B-13														#
// #								CrossPack-AVR-20100115											#
// #								avr-gcc															#
// ##################################################################################################

#ifndef	MYLCD_H
#define MYLCD_H
#include "allHeaders.h"

// # User and Extra Configurations, defines and prototypes moved to "defines.h"


	// low level lcd	
	void lcd_chip_select(uint8_t);
	void lcd_write_cmd(uint8_t,uint8_t);
	void lcd_write_data(uint8_t,uint8_t);
	void lcd_write(uint8_t,uint8_t);
	uint8_t lcd_read_data(uint8_t);
	void wait_while_chip_is_busy();
	
	// lcd
	void lcd_init();
	void lcd_clear();
	void lcd_set_pixel(uint8_t,uint8_t,uint8_t);
	void lcd_invert();
	#ifndef NO_BMP
	void lcd_draw_fullscreen_bmp(uint8_t*);
	#endif



	// low level font
	#ifndef NO_TEXT
	uint8_t font_number_of_chars(uint8_t*);
	uint8_t font_first_char(uint8_t*);
	uint8_t font_char_width(uint8_t*,uint8_t);
	uint8_t font_char_height();
	uint16_t font_start_offset(uint8_t*,uint8_t);
	uint8_t font_char_present(uint8_t*,uint8_t);	

	// font
	void lcd_set_cursor(uint8_t, uint8_t);	
	void lcd_putc(uint8_t*,uint8_t);
	void lcd_puts(uint8_t*, char* );
	void lcd_puts_p(uint8_t*, char* PROGMEM );
	#endif



	// graphics
	#ifndef NO_GRAPHICS
	void lcd_draw_line(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
	void lcd_draw_rect(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
	void lcd_fill_rect(uint8_t,uint8_t,uint8_t,uint8_t,uint8_t);
	#endif

#endif
