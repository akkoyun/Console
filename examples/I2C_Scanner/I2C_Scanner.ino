// Include Libraries
#include <Console.h>

// Define Object
I2C_Scanner_Console Terminal(Serial);

void setup() {

	// Start Serial Stream
    Serial.begin(115200);

	// Start Terminal
    Terminal.Begin();

}

void loop() {

	
}