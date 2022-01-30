/**
 * @file Console.cpp
 * @author Mehmet Gunce Akkoyun (akkoyun@me.com)
 * @brief VT100 Based Serial Console Library.
 * @version 01.00.00
 * @date 2022-01-30
 * @copyright Copyright (c) 2022
 */

// Include Header File
#include <Console.h>






_Console::_Console(void) {
	_serial = NULL;
}

void _Console::_sendCMD(uint8_t val) {
	_serial->write("\e[");
	_serial->print(val);
}

void _Console::_formatText(uint8_t val) {
	_sendCMD(val);
	_serial->write('m');
}

void _Console::begin(Stream &_ser) {
	//Set serial port
	_serial = &_ser;
	
	reset();
}

void _Console::reset(void) {
	_serial->write(VT_TERMINAL_RESET);
	_serial->flush();
	delay(10);
}


void _Console::cursorUp(uint8_t n) {
	_sendCMD(n);
	_serial->write('A');
}

void _Console::cursorDown(uint8_t n) {
	_sendCMD(n);
	_serial->write('B');
}

void _Console::cursorRight(uint8_t n) {
	_sendCMD(n);
	_serial->write('C');
}

void _Console::cursorLeft(uint8_t n) {
	_sendCMD(n);
	_serial->write('D');
}

void _Console::setCursor(uint8_t x, uint8_t y) {
	_sendCMD(x);
	_serial->write(';');
	_serial->print(y);
	_serial->write('H');
}

void _Console::cursorOn(void) {
	_serial->write(VT_CURSOR_ON);
}

void _Console::cursorOff(void) {
	_serial->write(VT_CURSOR_OFF);
}

void _Console::cursorHome(void) {
	_serial->write(VT_CURSOR_HOME);
}

void _Console::cursorSave(void) {
	_serial->write(VT_CURSOR_SAVE);
}

void _Console::cursorRestore(void) {
	_serial->write(VT_CURSOR_RESTORE);
}


void _Console::clearLineAfter(void) {
	_serial->write(VT_CLR_LINE_AFTER_CURSOR);
}

void _Console::clearLineBefore(void) {
	_serial->write(VT_CLR_LINE_TO_CURSOR);
}

void _Console::clearLine(void) {
	_serial->write(VT_CLR_LINE);
}

void _Console::clearScreen(void) {
	_serial->write(VT_CLR_SCREEN);
}

void _Console::clearAll(void) {
	_serial->write(VT_CLR_ALL);
}


void _Console::setBackgroundColor(VT100_Colors color) {
	_formatText((uint8_t)color + 10);
}

void _Console::setTextColor(VT100_Colors color) {
	_formatText((uint8_t)color);
}

void _Console::formatText(VT100_TextFormat format) {
	_formatText((uint8_t)format);
}





// Define Library Class
_Console Console;

// 1903