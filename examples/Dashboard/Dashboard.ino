// Include Console Library
#include <Console.h>

// Create Console Object
Console Terminal(Serial);

// Simulated Sensor Values
float   Voltage     = 0.0;
float   Current     = 0.0;
uint8_t Temperature = 0;
uint8_t Humidity    = 0;

// Voltage Statistics
float    V_Min   = 999.0;
float    V_Max   = 0.0;
float    V_Avg   = 0.0;
uint16_t V_Count = 0;

void Draw_Layout(void) {

	// Power Box (rows 1-12, cols 1-38)
	Terminal.Box(1, 1, 12, 38, F("Power"), 1, true, false);

	Terminal.Text(4,  3, _Console_YELLOW_, F("Voltage  :"));
	Terminal.Text(5,  3, _Console_YELLOW_, F("Current  :"));
	Terminal.Text(6,  3, _Console_YELLOW_, F("Power    :"));

	Terminal.Text(8,  3, _Console_YELLOW_, F("Min      :"));
	Terminal.Text(9,  3, _Console_YELLOW_, F("Max      :"));
	Terminal.Text(10, 3, _Console_YELLOW_, F("Average  :"));

	// Environment Box (rows 1-12, cols 40-78)
	Terminal.Box(1, 40, 12, 78, F("Environment"), 2, true, false);

	Terminal.Text(4,  42, _Console_YELLOW_, F("Temperature :"));
	Terminal.Text(5,  42, _Console_YELLOW_, F("Humidity    :"));
	Terminal.Text(6,  42, _Console_YELLOW_, F("Dew Point   :"));

	// Status Bar (rows 14-18, cols 1-78)
	Terminal.Box(14, 1, 18, 78, F("Status"), 0, false, false);

	Terminal.Text(16, 3,  _Console_GRAY_, F("Uptime :"));
	Terminal.Text(16, 42, _Console_GRAY_, F("Loop   :"));

}

void Update_Values(void) {

	// Simulated readings
	Voltage     = 12.0 + (float)(millis() % 300) / 100.0;
	Current     =  1.5 + (float)(millis() % 100) / 100.0;
	Temperature = 20   + (millis() / 2000) % 40;
	Humidity    = 40   + (millis() / 3000) % 50;

	float Power    = Voltage * Current;
	float DewPoint = Temperature - ((100.0f - Humidity) / 5.0f);

	// Voltage statistics
	if (V_Count < 60000) V_Count++;
	if (Voltage < V_Min) V_Min = Voltage;
	if (Voltage > V_Max) V_Max = Voltage;
	V_Avg = V_Avg + (Voltage - V_Avg) / V_Count;

	// Power values
	Terminal.Text(4, 14, SELECT_COLOR(Voltage, 10.0f, 14.0f), Voltage);
	Terminal.Text(4, 21, SELECT_COLOR(Voltage, 10.0f, 14.0f), F("V"));

	Terminal.Text(5, 14, SELECT_COLOR(Current, 0.5f, 3.0f), Current);
	Terminal.Text(5, 21, SELECT_COLOR(Current, 0.5f, 3.0f), F("A"));

	Terminal.Text(6, 14, _Console_WHITE_, Power);
	Terminal.Text(6, 21, _Console_WHITE_, F("W"));

	// Voltage statistics
	Terminal.Text(8,  14, _Console_CYAN_, V_Min);
	Terminal.Text(8,  21, _Console_GRAY_, F("V"));
	Terminal.Text(9,  14, _Console_CYAN_, V_Max);
	Terminal.Text(9,  21, _Console_GRAY_, F("V"));
	Terminal.Text(10, 14, _Console_CYAN_, V_Avg);
	Terminal.Text(10, 21, _Console_GRAY_, F("V"));

	// Environment values
	Terminal.Text(4, 56, SELECT_COLOR(Temperature, 15, 35), Temperature);
	Terminal.Text(4, 59, SELECT_COLOR(Temperature, 15, 35), F("C"));

	Terminal.Text(5, 56, SELECT_COLOR(Humidity, 30, 70), Humidity);
	Terminal.Text(5, 59, SELECT_COLOR(Humidity, 30, 70), F("%"));

	Terminal.Text(6, 56, _Console_WHITE_, DewPoint);
	Terminal.Text(6, 59, _Console_WHITE_, F("C"));

	// Status bar
	Terminal.Text(16, 12, _Console_WHITE_, millis() / 1000);
	Terminal.Text(16, 18, _Console_GRAY_,  F("s"));

	static uint32_t Loop_Count = 0;
	Terminal.Text(16, 50, _Console_WHITE_, ++Loop_Count);

}

void setup() {

	Serial.begin(115200);
	Terminal.Begin();
	Draw_Layout();

}

void loop() {

	Update_Values();
	delay(500);

}
