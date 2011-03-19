#ifndef _DEFINES_H
#define _DEFINES_H

#include "allHeaders.h"

#ifndef F_CPU
#define F_CPU	16000000UL
#endif

#define sbi(A,B)	(A |= (1 << B))
#define cbi(A,B)	(A &= ~(1 << B))

#define SETBIT(A,B)	(A |= (1 << B))
#define CLRBIT(A,B)	(A &= ~(1 << B))

#define	STEER_BUTTON_PIN	PINB
#define	AB_BUTTON_PIN		PIND
#define	UP					0
#define DOWN				1
#define	RIGHT				2
#define LEFT				3
#define A					2
#define	B					3

	//###############################################################################################
	//# 																							#
	//# User Configurations																			#
	//#																								#
	//###############################################################################################
	
	// Ports
	#define LCD_CMD_PORT		PORTD		// Command Output Register
	#define LCD_CMD_DDR			DDRD		// Data Direction Register for Command Port
	#define LCD_CS_PORT			PORTC		// ChipSelect Port
	#define LCD_CS_DDR			DDRC		// Data Direction Registe for ChipSelect

	#define LCD_DATA_PIN		PINA		// Data Input Register
	#define LCD_DATA_PORT		PORTA		// Data Output Register
	#define LCD_DATA_DDR		DDRA		// Data Direction Register for Data Port

	// Command Port Bits
	#define CD					0x04		// Data/Control (RS) PinNumber
	#define RW					0x05		// R/W PinNumber
	#define EN					0x06		// EN  PinNumber
	#define CS1					0x01		// CS1 PinNumber
	#define CS2					0x00		// CS2 PinNumber	
	//#define LCD_NO_RES					// uncomment this line if you have an pullup on reset
	
	#ifndef LCD_NO_RES
		#define RES				0x07		// Reset Pin
	#endif


	//###############################################################################################
	//# 																							#
	//# Extra configuration																			#
	//#																								#
	//###############################################################################################

	//#define FASTTEXT 			// comment this if you get bad text output
								// draws Text much faster (writes whole pages without using set_pixel)	
								// only recommended to use if font has an height of 8 (or multipel)
								// using y-positions,0,8,16,24... lcd_set_line(uint8_t line)
	#define FLIP_H				// turns output 180degree. If this is selected, FASTTEXT wont work 
								// properly

	//#define NO_BMPS			// if you do not need bitmaps
	//#define NO_GRAPHICS		// if you do not need lines/rects/circels
	//#define NO_BRESENHAM		// if you only use horizontal or vertical lines (or rects) (~264 Bytes)
	//#define NO_TEXT			// if you do not need text output

	//###############################################################################################
	//# 																							#
	//# Defines																						#
	//#																								#
	//###############################################################################################

	// Chips
	#define CHIP1				0x01
	#define CHIP2				0x02

	// Commands
	#define LCD_ON				0x3F
	#define LCD_OFF				0x3E
	#define LCD_SET_ADD			0x40
	#define LCD_SET_PAGE		0xB8
	#define LCD_DISP_START		0xC0
	#define LCD_BUSY			0x80

	// Pixel Colors
	#define BLACK				0x01
	#define WHITE				0x00

	// Lines

	#define LINE0				0x00
	#define LINE1				0x08
	#define LINE2				0x10
	#define LINE3				0x18
	#define LINE4				0x20
	#define LINE5				0x28
	#define LINE6				0x30
	#define LINE7				0x38


	//###############################################################################################
	//# 																							#
	//# Prototyes																					#
	//#																								#
	//###############################################################################################

	#define max(a, b) ((a)>(b)?(a):(b)) 
	#define min(a, b) ((a)>(b)?(b):(a))


#endif