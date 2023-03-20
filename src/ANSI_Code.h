#ifndef __ANSI_Code__
#define __ANSI_Code__

	// Text Format Definitions
	#define Terminal_Normal		    	(unsigned char)0
	#define Terminal_Bold		    	(unsigned char)1
	#define Terminal_Low		    	(unsigned char)2
	#define Terminal_Italic	        	(unsigned char)3
	#define Terminal_UnderLine	    	(unsigned char)4
	#define Terminal_SlowBlink	   		(unsigned char)5
	#define Terminal_RapidBlink	    	(unsigned char)6
	#define Terminal_Reverse	    	(unsigned char)7
	#define Terminal_Hide		    	(unsigned char)8
	#define Terminal_Overline	   		(unsigned char)9

	// Clear Type Definitions
	#define Terminal_Clear_AfterLine	(unsigned char)0
	#define Terminal_Clear_BeforeLine	(unsigned char)1
	#define Terminal_Clear_Line	    	(unsigned char)2
	#define Terminal_Clear_Screen		(unsigned char)3

	// Terminal Colors
	#define Terminal_BLACK				(unsigned char)30
	#define Terminal_RED				(unsigned char)31
	#define Terminal_GREEN				(unsigned char)32
	#define Terminal_YELLOW				(unsigned char)33
	#define Terminal_BLUE				(unsigned char)34
	#define Terminal_MAGENTA			(unsigned char)35
	#define Terminal_CYAN				(unsigned char)36
	#define Terminal_WHITE				(unsigned char)37
	#define Terminal_GRAY				(unsigned char)90

	// Define Clear Types
	#define __ANSI_Clear_AfterLine__	"\033[0K"
	#define __ANSI_Clear_BeforeLine__	"\033[1K"
	#define __ANSI_Clear_Line__			"\033[2K"
	#define __ANSI_Clear_Screen__		"\033[2J"

	// Cursor Types
	#define __ANSI_Cursor_ON__			"\033[?25h"
	#define __ANSI_Cursor_OFF__			"\033[?25l"


#endif