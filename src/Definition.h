// Debug Mode Definitions
//#define _DEBUG_

// Color Definitions
#define _Console_BLACK_					(uint8_t)30
#define _Console_RED_					(uint8_t)31
#define _Console_GREEN_					(uint8_t)32
#define _Console_YELLOW_				(uint8_t)33
#define _Console_BLUE_					(uint8_t)34
#define _Console_MAGENTA_				(uint8_t)35
#define _Console_CYAN_					(uint8_t)36
#define _Console_WHITE_					(uint8_t)37
#define _Console_GRAY_					(uint8_t)90

// Text Format Definitions
#define _Console_RST_					(uint8_t)0
#define _Console_BRIGHT_				(uint8_t)1
#define _Console_DIM_					(uint8_t)2
#define _Console_UNDERSCORE_			(uint8_t)4
#define _Console_BLINK_					(uint8_t)5
#define _Console_REVERSE_				(uint8_t)7
#define _Console_HIDDEN_				(uint8_t)8

// Clear Type Definitions
#define _Console_LINE_AFTER_CURSOR_		(uint8_t)0
#define _Console_LINE_TO_CURSOR_		(uint8_t)1
#define _Console_LINE_					(uint8_t)2
#define _Console_SCREEN_				(uint8_t)3
#define _Console_ALL_					(uint8_t)4

// Divider Definitions
#define HORIZONTAL						(bool)true
#define VERTICAL						(bool)false

// Color Choice
#define SELECT_COLOR(_VALUE, _MIN, _MAX) ((_VALUE) <= (_MIN) ? _Console_RED_ : ((_VALUE) >= (_MAX) ? _Console_GREEN_ : _Console_WHITE_))

// Console Definitions
#ifndef _Console_Message_X_
    #define _Console_Message_X_			(uint8_t)21
#endif
#ifndef _Console_Message_Y_
    #define _Console_Message_Y_			(uint8_t)4
#endif
#ifndef _Console_AT_Status_X_
    #define _Console_AT_Status_X_		(uint8_t)21
#endif
#ifndef _Console_AT_Status_Y_
    #define _Console_AT_Status_Y_		(uint8_t)84
#endif