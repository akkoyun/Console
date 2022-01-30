/**
 * @file Console.h
 * @author Mehmet Gunce Akkoyun (akkoyun@me.com)
 * @brief VT100 Based Serial Console Library.
 * @version 01.00.00
 * @date 2022-01-30
 * @copyright Copyright (c) 2022
 */

#ifndef __Console__
#define __Console__

// Define Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif


//Reset
#define VT_TERMINAL_RESET			"\ec" //Wait >10ms after this command before sending any other commands

//Erasing
#define VT_CLR_LINE_AFTER_CURSOR	"\e[K"
#define VT_CLR_LINE_TO_CURSOR		"\e[1K"
#define VT_CLR_LINE					"\e[2K"
#define	VT_CLR_SCREEN				"\e[2J"
#define VT_CLR_ALL					"\e[1;1H\e[2J"

//Cursor
#define VT_CURSOR_OFF				"\e[?25l"
#define VT_CURSOR_ON				"\e[?25h"
#define VT_CURSOR_HOME				"\e[H"
#define VT_CURSOR_SAVE				"\e7"
#define VT_CURSOR_RESTORE			"\e8"
#define VT_CURSOR_UP				"\e[A"
#define VT_CURSOR_DOWN				"\e[B"
#define VT_CURSOR_RIGHT				"\e[C"
#define VT_CURSOR_LEFT				"\e[D"

//Text
#define VT_TEXT_DEFAULT				"\e[0m"
#define VT_TEXT_BRIGHT				"\e[1m"
#define VT_TEXT_DIM					"\e[2m"
#define VT_TEXT_UNDERSCORE			"\e[4m"
#define VT_TEXT_BLINK				"\e[5m"
#define VT_TEXT_REVERSE				"\e[7m"
#define VT_TEXT_HIDDEN				"\e[8m"

//Text colors
#define VT_FOREGROUND_BLACK			"\e[30m"
#define VT_FOREGROUND_RED			"\e[31m"
#define VT_FOREGROUND_GREEN			"\e[32m"
#define VT_FOREGROUND_YELLOW		"\e[33m"
#define VT_FOREGROUND_BLUE			"\e[34m"
#define VT_FOREGROUND_MAGNETA		"\e[35m"
#define VT_FOREGROUND_CYAN			"\e[36m"
#define VT_FOREGROUND_WHITE			"\e[37m"
#define VT_FOREGROUND_DEFAULT		"\e[39m"

//Background colors
#define VT_BACKGROUND_BLACK			"\e[40m"
#define VT_BACKGROUND_RED			"\e[41m"
#define VT_BACKGROUND_GREEN			"\e[42m"
#define VT_BACKGROUND_YELLOW		"\e[43m"
#define VT_BACKGROUND_BLUE			"\e[44m"
#define VT_BACKGROUND_MAGNETA		"\e[45m"
#define VT_BACKGROUND_CYAN			"\e[46m"
#define VT_BACKGROUND_WHITE			"\e[47m"
#define VT_BACKGROUND_DEFAULT		"\e[49m"

/**
	\brief	Enum defining all available text and background colors for the VT100 terminal
*/
typedef enum
{
	VT_BLACK	= 30,	//!< Black
	VT_RED		= 31,	//!< Red
	VT_GREEN	= 32,	//!< Green
	VT_YELLOW	= 33,	//!< Yellow
	VT_BLUE		= 34,	//!< Blue
	VT_MAGENTA	= 35,	//!< Magenta
	VT_CYAN		= 36,	//!< Cyan
	VT_WHITE	= 37,	//!< White
	VT_DEFAULT	= 39	//!< Default color of terminal
} VT100_Colors;

/**
	\brief	Enumg defining all available text formatting options (beside colors)
*/
typedef enum
{
	VT_RESET		= 0,	//!< Reset all formats to standard
	VT_BRIGHT		= 1,	//!< Bold text?
	VT_DIM			= 2,	//!< Cursive text?
	VT_UNDERSCORE	= 4,	//!< Underscore text
	VT_BLINK		= 5,	//!< Blink text at cursor
	VT_REVERSE		= 7,	//!< Reverse writing direction
	VT_HIDDEN		= 8		//!< Hide text?
} VT100_TextFormat;





class _Console {

	public:

		VT100_Control(void);
		void begin(Stream &_ser);
		void reset(void);
		void cursorUp(uint8_t n = 1);
		void cursorDown(uint8_t n = 1);
		void cursorLeft(uint8_t n = 1);
		void cursorRight(uint8_t n = 1);
		void setCursor(uint8_t x, uint8_t y);
		void cursorOn(void);
		void cursorOff(void);
		void cursorHome(void);
		void cursorSave(void);
		void cursorRestore(void);
		void clearLineAfter(void);
		void clearLineBefore(void);
		void clearLine(void);
		void clearScreen(void);
		void clearAll(void);
		void setBackgroundColor(VT100_Colors color = VT_DEFAULT);
		void setTextColor(VT100_Colors color = VT_DEFAULT);
		void formatText(VT100_TextFormat format = VT_RESET);

	private:
	
		Stream *_serial;
		void _sendCMD(uint8_t val);
		void _formatText(uint8_t val);

};

extern _Console Console;

#endif /* defined(__Console__) */