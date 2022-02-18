// Define Libraries
#include <Console.h>

void setup() {

    Serial.begin(115200);
    Terminal.Begin(Serial);

	Terminal.B100BB();
}

void loop() {

    Terminal.Text_Color(RED);
    Terminal.Set_Cursor(2,13);
    Terminal.Print(millis());


}