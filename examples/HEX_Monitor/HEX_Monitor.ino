// AT status area positioned inside the AT Log box
#define _Console_AT_Status_X_   14
#define _Console_AT_Status_Y_   3

// Include Console Library
#include <Console.h>

// Create Console Object
Console Terminal(Serial);

// Simulated register map
struct Device_Registers {
	uint8_t  Status;
	uint8_t  Config;
	uint16_t ADC_Raw;
	uint32_t Device_ID;
} Registers = { 0xA5, 0x3C, 0x0000, 0xDEADBEEF };

void Draw_Layout(void) {

	// Register Monitor Box (rows 1-10, cols 1-50)
	Terminal.Box(1, 1, 10, 50, F("Register Monitor"), 0, true, false);

	Terminal.Text(4, 3, _Console_YELLOW_, F("Status    :"));
	Terminal.Text(5, 3, _Console_YELLOW_, F("Config    :"));
	Terminal.Text(6, 3, _Console_YELLOW_, F("ADC Raw   :"));
	Terminal.Text(7, 3, _Console_YELLOW_, F("Device ID :"));

	// Bit Field Box (rows 12-18, cols 1-50)
	Terminal.Box(12, 1, 18, 50, F("Bit Field  [Status Register]"), 0, true, false);

	Terminal.Text(15, 3, _Console_YELLOW_, F("7  6  5  4  3  2  1  0"));

	// AT Log Box (rows 12-20, cols 52-88)
	Terminal.Box(12, 52, 18, 88, F("AT Log"), 0, true, false);

}

void Draw_Bits(const uint8_t _Row, const uint8_t _Col, const uint8_t _Value) {

	for (int8_t i = 7; i >= 0; i--) {
		uint8_t Bit_Col = _Col + (7 - i) * 3;
		if (_Value & (1 << i)) Terminal.Text(_Row, Bit_Col, _Console_GREEN_, '1');
		else                   Terminal.Text(_Row, Bit_Col, _Console_RED_,   '0');
	}

}

void Simulate_AT(void) {

	struct { const __FlashStringHelper * Cmd; bool Result; } Commands[] = {
		{ F("AT"),          true  },
		{ F("AT+CREG?"),   true  },
		{ F("AT+CSQ"),     true  },
		{ F("AT+CGDCONT"), false },
	};

	static uint8_t Index = 0;
	Terminal.AT_Command(Commands[Index].Cmd);
	delay(300);
	Terminal.OK(Commands[Index].Result);
	Index = (Index + 1) % 4;

}

void Update_Values(void) {

	// Simulate changing registers
	Registers.Status  = (uint8_t)(millis() / 500) & 0xFF;
	Registers.ADC_Raw = (uint16_t)(analogRead(A0));

	// Print hex registers
	Terminal.Print_HEX(4, 15, _Console_CYAN_, Registers.Status);
	Terminal.Print_HEX(5, 15, _Console_CYAN_, Registers.Config);
	Terminal.Print_HEX(6, 15, _Console_CYAN_, Registers.ADC_Raw);
	Terminal.Print_HEX(7, 15, _Console_CYAN_, Registers.Device_ID);

	// Draw bit field for Status register
	Draw_Bits(16, 3, Registers.Status);

}

void setup() {

	Serial.begin(115200);
	Terminal.Begin();
	Draw_Layout();

}

void loop() {

	Update_Values();
	Simulate_AT();
	delay(500);

}
