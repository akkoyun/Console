// Define Debug Mode
#define _DEBUG_

// Include Libraries
#include <Console.h>

// Define Object
PowerStat_Console Terminal(Serial);

void setup() {

	// Start Serial Stream
    Serial.begin(115200);

	// Start Terminal
    Terminal.Begin();

	Terminal.AT_Command(F("AT+GMR"));
	delay(1000);
	Terminal.OK(true);

	// Show Message
	Terminal.Show_Message(_Console_BLUE_, F("Hello World!"));

}

void loop() {

	// Print Terminal Text
	Terminal.Text(2, 13, _Console_RED_, String(millis()));

	// Print Status Register
	Terminal.Show_Status(1, millis());
	
}