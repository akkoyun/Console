#ifndef __Console_Defination__
#define __Console_Defination__

// Background Color Definations
#define BACKGROUND_BLACK		"\e[40m"
#define BACKGROUND_RED		    "\e[41m"
#define BACKGROUND_GREEN		"\e[42m"
#define BACKGROUND_YELLOW	    "\e[43m"
#define BACKGROUND_BLUE		    "\e[44m"
#define BACKGROUND_MAGNETA  	"\e[45m"
#define BACKGROUND_CYAN		    "\e[46m"
#define BACKGROUND_WHITE		"\e[47m"
#define BACKGROUND_DEFAULT  	"\e[49m"

// Cursor Definations
#define CURSOR_OFF				"\e[?25l"
#define CURSOR_ON				"\e[?25h"
#define CURSOR_HOME				"\e[H"
#define CURSOR_SAVE				"\e7"
#define CURSOR_RESTORE			"\e8"
#define CURSOR_UP				"\e[A"
#define CURSOR_DOWN				"\e[B"
#define CURSOR_RIGHT			"\e[C"
#define CURSOR_LEFT				"\e[D"

// Erasing Definations
#define CLR_LINE_AFTER_CURSOR	"\e[K"
#define CLR_LINE_TO_CURSOR		"\e[1K"
#define CLR_LINE				"\e[2K"
#define	CLR_SCREEN				"\e[2J"
#define CLR_ALL					"\e[1;1H\e[2J"

typedef enum
{
	BLACK	            = 30,
	RED		            = 31,
	GREEN	            = 32,
	YELLOW	            = 33,
	BLUE	            = 34,
	MAGENTA	            = 35,
	CYAN	            = 36,
	WHITE	            = 37,
	GRAY	            = 90

} Colors;

typedef enum
{
	RST			        = 0,
	BRIGHT		        = 1,
	DIM			        = 2,
	UNDERSCORE	        = 4,
	BLINK		        = 5,
	REVERSE		        = 7,
	HIDDEN		        = 8	
} TextFormat;

enum STATUS_Bits {
	LINE_AFTER_CURSOR 	= 0,
	LINE_TO_CURSOR 		= 1,
	LINE 		    	= 2,
	SCREEN 			    = 3,
	ALL 			    = 4
};

#endif
