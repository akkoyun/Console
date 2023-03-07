#ifndef __ANSI_Code__
#define __ANSI_Code__

	// Text Format Definitions
	#define Terminal_Normal		    	0
	#define Terminal_Bold		    	1
	#define Terminal_Low		    	2
	#define Terminal_Italic	        	3
	#define Terminal_UnderLine	    	4
	#define Terminal_SlowBlink	   		5
	#define Terminal_RapidBlink	    	6
	#define Terminal_Reverse	    	7
	#define Terminal_Hide		    	8
	#define Terminal_Overline	   		9

	// Clear Type Definitions
	#define Terminal_Clear_AfterLine	0
	#define Terminal_Clear_BeforeLine	1
	#define Terminal_Clear_Line	    	2
	#define Terminal_Clear_Screen		3

	// Terminal Colors
	#define Terminal_BLACK				(uint8_t)30
	#define Terminal_RED				(uint8_t)31
	#define Terminal_GREEN				(uint8_t)32
	#define Terminal_YELLOW				(uint8_t)33
	#define Terminal_BLUE				(uint8_t)34
	#define Terminal_MAGENTA			(uint8_t)35
	#define Terminal_CYAN				(uint8_t)36
	#define Terminal_WHITE				(uint8_t)37
	#define Terminal_GRAY				(uint8_t)90

	// Define Char Types
	#define __ANSI_Char_Normal__		"\033[0m"
	#define __ANSI_Char_Bold__			"\033[1m"
	#define __ANSI_Char_Low__			"\033[2m"
	#define __ANSI_Char_Italic__		"\033[3m"
	#define __ANSI_Char_UnderLine__		"\033[4m"
	#define __ANSI_Char_SlowBlink__		"\033[5m"
	#define __ANSI_Char_RapidBlink__	"\033[6m"
	#define __ANSI_Char_Reverse__		"\033[7m"
	#define __ANSI_Char_Hide__			"\033[8m"
	#define __ANSI_Char_OverLine__		"\033[9m"

	// Define Clear Types
	#define __ANSI_Clear_AfterLine__	"\033[0K"
	#define __ANSI_Clear_BeforeLine__	"\033[1K"
	#define __ANSI_Clear_Line__			"\033[2K"
	#define __ANSI_Clear_Screen__		"\033[2J"

	// Cursor Types
	#define __ANSI_Cursor_ON__			"\033[?25h"
	#define __ANSI_Cursor_OFF__			"\033[?25l"


#endif