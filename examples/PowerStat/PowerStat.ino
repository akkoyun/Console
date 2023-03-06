// Include Libraries
#include <Console.h>

// Define Object
PowerStat_Console Terminal(Serial);

void setup() {

	// Start Terminal
	Terminal.Begin();

	// Print Hardware Diagnostic Information
	Terminal.OK_Decide(true, 5, 35);
	Terminal.OK_Decide(true, 6, 35);
	Terminal.OK_Decide(false, 7, 35);
	Terminal.OK_Decide(true, 8, 35);
	Terminal.OK_Decide(true, 9, 35);
	Terminal.OK_Decide(true, 10, 35);
	Terminal.OK_Decide(true, 11, 35);

	// Print Serial ID
	Terminal.Serial_ID("D40000011D269470");

	// Print Verison
	Terminal.Version();

	// Print Environment
	Terminal.Environment(12.11, 13.11);

	// Print Interval
	Terminal.Interval(3, 5);

	// Print Pump Status
	Terminal.Pump_Status(true);

	// Print Battery
	Terminal.Battery(4.2, 33.12, 123.12, 98.99, 3000, 1200, 1);

	// Print GSM Parameters
	Terminal.GSM(1, 1, 2, 3, 4, "353613080366852", 1770241, "8990011916180288902");

	// Print Connection Time
	Terminal.Connection_Time(20);

	// Print Signal Level
	Terminal.Signal_Level(80);

}

void loop() {

	// Print Uptime
	Terminal.UpTime();
	
}