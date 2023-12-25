// Include Libraries
#include <Console.h>

// Define Object
PowerStat_Console Terminal(Serial);

void setup() {

	// Start Serial Stream
    Serial.begin(115200);

	// Start Terminal
    Terminal.Begin();

}

void loop() {

	// Print Terminal Text
	Terminal.Text(2, 13, _Console_RED_, String(millis()));
	
}