// Include Libraries
#include <Console.h>

// Define Object
Console Terminal(Serial);

void setup() {

	// Start Serial Stream
    Serial.begin(115200);

	// Start Terminal
    Terminal.Begin();

	// Draw Terminal Base
	Terminal.PowerStat();

}

void loop() {

	// Print Terminal Text
	Terminal.Text(2, 13, RED, String(millis()));
	
}