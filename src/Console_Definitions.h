// Text Format Definitions
#define __Normal__			    0
#define __Bold__			    1
#define __Low__				    2
#define __Italic__		        3
#define __UnderLine__		    4
#define __SlowBlink__		    5
#define __RapidBlink__		    6
#define __Reverse__			    7
#define __Hide__			    8
#define __Overline__	    	9

// Clear Type Definitions
#define __Clear_AfterLine__		0
#define __Clear_BeforeLine__	1
#define __Clear_Line__		    2
#define __Clear_Screen__		3

// Terminal Colors
#define Terminal_BLACK			30
#define Terminal_RED			31
#define Terminal_GREEN			32
#define Terminal_YELLOW			33
#define Terminal_BLUE			34
#define Terminal_MAGENTA		35
#define Terminal_CYAN			36
#define Terminal_WHITE			37
#define Terminal_GRAY			90
















// Color Definitions
#define BLACK				    30
#define RED					    31
#define GREEN				    32
#define YELLOW				    33
#define BLUE				    34
#define MAGENTA				    35
#define CYAN				    36
#define WHITE				    37
#define GRAY				    90





// Template Definitions
// #define CONSOLE_TEMPLATE_I2C_SCANNER
// #define CONSOLE_TEMPLATE_MAX78630
#define CONSOLE_TEMPLATE_POWERSTAT
// #define CONSOLE_TEMPLATE_FILTERSTAT
// #define CONSOLE_TEMPLATE_GE910
// #define CONSOLE_TEMPLATE_VOLTMETER
// #define CONSOLE_TEMPLATE_TH_METER
// #define CONSOLE_TEMPLATE_PRESSURE
// #define CONSOLE_TEMPLATE_MAX78630_FULL


// Text Format Definitions
#define RST					(uint8_t)0
#define BRIGHT				(uint8_t)1
#define DIM					(uint8_t)2
#define UNDERSCORE			(uint8_t)4
#define BLINK				(uint8_t)5
#define REVERSE				(uint8_t)7
#define HIDDEN				(uint8_t)8

// Clear Type Definitions
#define LINE_AFTER_CURSOR 	(uint8_t)0
#define LINE_TO_CURSOR 		(uint8_t)1
#define LINE 		    	(uint8_t)2
#define SCREEN 			    (uint8_t)3
#define ALL 			    (uint8_t)4
