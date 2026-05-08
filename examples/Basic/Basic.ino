// Include Console Library
#include <Console.h>

// Create Console Object
Console Terminal(Serial);

void setup() {

	// Start Serial Stream
	Serial.begin(115200);

	// Initialize Terminal
	Terminal.Begin();

	// Draw a Box (row1, col1, row2, col2, title, number, header, footer)
	Terminal.Box(1, 1, 10, 40, F("Console Demo"), 1, true, false);

	// Print Text
	Terminal.Text(3, 3, _Console_YELLOW_, F("Voltage  :"));
	Terminal.Text(4, 3, _Console_YELLOW_, F("Current  :"));
	Terminal.Text(5, 3, _Console_YELLOW_, F("Uptime   :"));

	// Draw a Horizontal Divider
	Terminal.Divider(_Console_HORIZONTAL_, 7, 1, 38, true);

	// Print HEX Values
	Terminal.Text(9, 3, _Console_GRAY_, F("Device ID:"));
	Terminal.Print_HEX(9, 14, _Console_CYAN_, (uint32_t)0xDEADBEEF);

	// Show AT Command Flow
	Terminal.AT_Command(F("AT+GMR"));
	delay(500);
	Terminal.OK(true);

	// Beep
	Terminal.Beep();

}

void loop() {

	// Update Values
	Terminal.Text(3, 14, SELECT_COLOR(33, 10, 50), F("33.2 V"));
	Terminal.Text(4, 14, _Console_GREEN_,           F(" 1.4 A"));
	Terminal.Text(5, 14, _Console_WHITE_,           millis() / 1000);

	delay(1000);

}
