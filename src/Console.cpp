// Include Header File
#include "Console.h"

void Console::Begin(Stream &_Serial) {

	//Set serial port
	_Console = &_Serial;

	// Cursor Off
	Cursor(false);

	// Clear Screen
	Clear(SCREEN);

	// Reset Delay
	delay(5);

}
void Console::Clear(uint8_t _Type) {

	// Clear Screen
	if (_Type == LINE_AFTER_CURSOR) _Console->print(F("\e[K"));
	if (_Type == LINE_TO_CURSOR) _Console->print(F("\e[1K"));
	if (_Type == LINE) _Console->print(F("\e[2K"));
	if (_Type == SCREEN) _Console->print(F("\e[2J"));
	if (_Type == ALL) _Console->print(F("\e[1;1H\e[2J"));

}
void Console::Beep(void) {

	_Console->print(F("\x07"));
	
}

// Cursor Functions
void Console::Cursor(bool _State) {

	// Cursor On
	if (_State == true) _Console->print(F("\e[?25h"));	

	// Cursor Off
	if (_State == false) _Console->print(F("\e[?25l"));	

}
void Console::Set_Cursor(uint8_t _x, uint8_t _y) {

	_Send_CMD(_x);
	_Console->print(F(";"));
	_Console->print(_y);
	_Console->print(F("H"));

}

// Print Functions
void Console::Text(uint8_t _x, uint8_t _y, Colors _Color, String _Value) {

	// Print Text
	Text_Color(_Color); 
	Set_Cursor(_x, _y); 
	_Console->println(_Value);

}
void Console::Print(String _Value) {

	// Cursor On
	_Console->print(_Value);

}
void Console::Print(const uint32_t _Value) {

	// Cursor On
	_Console->print(_Value);

}
void Console::Text_Color(Colors _Color) {

	_Format_Text((uint8_t)_Color);

}
void Console::Text_Format(TextFormat _Format) {

	_Format_Text((uint8_t)_Format);

}

void Console::OK_Decide(bool _Result, uint8_t _X, uint8_t _Y) {

	// Print Command State
	if (_Result) {
		Text(_X, _Y+1, GREEN, F("OK"));
	} else {
		Text(_X, _Y, RED, F("FAIL"));
	}
	
}

void Console::Background_Color(Colors _Color) {

	_Format_Text((uint8_t)_Color + 10);

}

// Box Drawing Functions
void Console::Draw_Box(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2, String _Text, uint8_t _Number, bool _Header, bool _Footer) {

	//Set Color
	Text_Color(WHITE);
	Text_Format(DIM);

	// Print Corners
	Set_Cursor(_X1, _Y1); _Console->println(F("┌"));
	Set_Cursor(_X1, _Y2); _Console->println(F("┐"));
	Set_Cursor(_X2, _Y1); _Console->println(F("└"));
	Set_Cursor(_X2, _Y2); _Console->println(F("┘"));

	// Print Lines
	for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {Set_Cursor(i, _Y1); _Console->println(F("│"));}
	for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {Set_Cursor(i, _Y2); _Console->println(F("│"));}
	for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {Set_Cursor(_X1, i); _Console->println(F("─"));}
	for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {Set_Cursor(_X2, i); _Console->println(F("─"));}

	// Print Header
	Text_Color(YELLOW); Set_Cursor(_X1, _Y1 + 2); _Console->println(_Text);
	Text_Color(WHITE); Set_Cursor(_X1, _Y2 - 4); _Console->println(F("["));
	Text_Color(YELLOW); Set_Cursor(_X1, _Y2 - 3); _Console->println(_Number);
	Text_Color(WHITE); Set_Cursor(_X1, _Y2 - 2); _Console->println(F("]"));

	// Draw Footer
	if (_Header) Draw_Box_Header(_X1, _Y1, _X2, _Y2);
	if (_Footer) Draw_Box_Footer(_X1, _Y1, _X2, _Y2);

}
void Console::Draw_Box_Footer(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

	//Set Color
	Text_Color(WHITE);
	Text_Format(DIM);

	// Print Corners
	Set_Cursor(_X2 - 2, _Y1); _Console->println(F("├"));
	Set_Cursor(_X2 - 2, _Y2); _Console->println(F("┤"));

	// Print Lines
	for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {Set_Cursor(_X2 - 2, i); _Console->println(F("─"));}

}
void Console::Draw_Box_Header(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

	//Set Color
	Text_Color(WHITE);
	Text_Format(DIM);

	// Print Corners
	Set_Cursor(_X1 + 2, _Y1); _Console->println(F("├"));
	Set_Cursor(_X1 + 2, _Y2); _Console->println(F("┤"));

	// Print Lines
	for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {Set_Cursor(_X1 + 2, i); _Console->println(F("─"));}

}
void Console::Draw_Horizontal_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length, bool _End) {

	//Set Color
	Text_Color(WHITE);
	Text_Format(DIM);

	// Print Corners
	if (_End == true) {
		Set_Cursor(_X1, _Y1); Serial.println(F("├"));
		Set_Cursor(_X1, _Y1 + _Length); Serial.println(F("┤"));
	}

	// Print Lines
	for (uint8_t i = _Y1 + 1; i <= _Y1 + _Length - 1; i++) {Set_Cursor(_X1, i); Serial.println(F("─"));}

}
void Console::Draw_Vertical_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length) {

	//Set Color
	Text_Color(WHITE);
	Text_Format(DIM);

	// Print Corners
	Set_Cursor(_X1, _Y1); _Console->println(F("┬"));
	Set_Cursor(_X1 + _Length, _Y1); _Console->println(F("┴"));

	// Print Lines
	for (uint8_t i = _X1 + 1; i <= _X1 + _Length - 1; i++) {Set_Cursor(i, _Y1); _Console->println(F("│"));}

}
void Console::Print_Box_Title(uint8_t _X1, uint8_t _Y1, uint8_t _Y2, String _Title) {

	// Calculate Position
	uint8_t _Width = _Y2 - _Y1;
	uint8_t _Text_Size = _Title.length();
	uint8_t _Position = (_Width) - (_Text_Size / 2);

	// Print Header
	Text_Color(WHITE); 
	Text_Format(BRIGHT);
	Set_Cursor(_X1 + 1, _Position); 
	_Console->println(_Title);
	Text_Format(RST);

}

// Stats Table
void Console::Draw_3Row_Stat_Table(uint8_t _X1, uint8_t _Y1) {

	//32,5

	Draw_Horizontal_Divider(_X1 + 1, _Y1, 50, false);
	Draw_Horizontal_Divider(_X1 + 5, _Y1, 50, false);

	Draw_Vertical_Divider(_X1 + 1,_Y1 + 9,4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 19,4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 29,4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 39,4);

	Text(_X1, _Y1 + 11, WHITE, F("Instant"));
	Text(_X1, _Y1 + 21, WHITE, F("Minimum"));
	Text(_X1, _Y1 + 31, WHITE, F("Maximum"));
	Text(_X1, _Y1 + 41, WHITE, F("Average"));

	Text(_X1 + 2, _Y1 + 1, WHITE, F("Phase R"));
	Text(_X1 + 3, _Y1 + 1, WHITE, F("Phase S"));
	Text(_X1 + 4, _Y1 + 1, WHITE, F("Phase T"));


}
void Console::Draw_3Row_Abstract_Table(uint8_t _X1, uint8_t _Y1) {

	//32,5

	Draw_Horizontal_Divider(_X1 + 1, _Y1, 50, false);
	Draw_Horizontal_Divider(_X1 + 5, _Y1, 50, false);

	Draw_Vertical_Divider(_X1 + 1,_Y1 + 9,4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 19,4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 29,4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 39,4);

	Text(_X1, _Y1 + 11, WHITE, F("Voltage"));
	Text(_X1, _Y1 + 21, WHITE, F("Current"));
	Text(_X1, _Y1 + 32, WHITE, F("Freq"));
	Text(_X1, _Y1 + 42, WHITE, F("Cos Fi"));

	Text(_X1 + 2, _Y1 + 1, WHITE, F("Phase R"));
	Text(_X1 + 3, _Y1 + 1, WHITE, F("Phase S"));
	Text(_X1 + 4, _Y1 + 1, WHITE, F("Phase T"));


}
void Console::Draw_3Row_Limit_Table(uint8_t _X1, uint8_t _Y1) {

	//32,64

	Draw_Horizontal_Divider(_X1 + 1, _Y1 - 1, 54, false);
	Draw_Horizontal_Divider(_X1 + 5, _Y1 - 1, 54, false);

	Draw_Vertical_Divider(_X1 + 1,_Y1 + 8, 4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 15, 4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 22, 4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 30, 4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 38, 4);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 46, 4);

	Text(_X1, _Y1 + 11, WHITE, F("LV"));
	Text(_X1, _Y1 + 18, WHITE, F("HV"));
	Text(_X1, _Y1 + 25, WHITE, F("LFQ"));
	Text(_X1, _Y1 + 33, WHITE, F("HFQ"));
	Text(_X1, _Y1 + 41, WHITE, F("VIM"));
	Text(_X1, _Y1 + 49, WHITE, F("IIM"));

	Text(_X1 + 2, _Y1, WHITE, F("Max"));
	Text(_X1 + 3, _Y1, WHITE, F("State"));
	Text(_X1 + 4, _Y1, WHITE, F("Min"));

	Text(_X1 + 3, _Y1 + 11, WHITE, F("[ ]"));
	Text(_X1 + 3, _Y1 + 18, WHITE, F("[ ]"));
	Text(_X1 + 3, _Y1 + 25, WHITE, F("[ ]"));
	Text(_X1 + 3, _Y1 + 33, WHITE, F("[ ]"));
	Text(_X1 + 3, _Y1 + 41, WHITE, F("[ ]"));
	Text(_X1 + 3, _Y1 + 49, WHITE, F("[ ]"));

}
void Console::Draw_1Row_Stat_Table(uint8_t _X1, uint8_t _Y1, String _Variable) {

	//32,5

	Draw_Horizontal_Divider(_X1 + 1, _Y1, 50, false);
	Draw_Horizontal_Divider(_X1 + 3, _Y1, 50, false);

	Draw_Vertical_Divider(_X1 + 1,_Y1 + 9,2);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 19,2);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 29,2);
	Draw_Vertical_Divider(_X1 + 1,_Y1 + 39,2);

	Text(_X1, _Y1 + 11, WHITE, F("Instant"));
	Text(_X1, _Y1 + 21, WHITE, F("Minimum"));
	Text(_X1, _Y1 + 31, WHITE, F("Maximum"));
	Text(_X1, _Y1 + 41, WHITE, F("Average"));

	Text(_X1 + 2, _Y1 + 1, WHITE, _Variable);


}

// Private Functions
void Console::_Send_CMD(uint8_t _val) {

	_Console->print(F("\e["));
	_Console->print(_val);

}
void Console::_Format_Text(uint8_t _val) {

	_Send_CMD(_val);
	_Console->write('m');

}

// Batch Functions
void Console::Dot(uint8_t _X, uint8_t _Y, uint8_t _Count) {

	for (uint8_t i = 0; i < _Count; i++) {

		Text(_X, _Y + i, WHITE, F("."));

	}

}
void Console::Bracket(uint8_t _X, uint8_t _Y, uint8_t _Space) {

	Text(_X, _Y, WHITE, F("["));
	for (uint8_t i = 0; i < _Space; i++) Text(_X, _Y + i + 1, WHITE, F(" "));
	Text(_X, _Y + _Space, WHITE, F("]"));

}
void Console::FilterStat(void) {

	// Draw Main Screen
    Draw_Box(1, 1, 49, 120, "", 0, true, 1);
    Print_Box_Title(1,1,59,F("FilterStat V3"));

	// Header Titles
	Text(2, 3, WHITE, F("Up Time : "));

	// Draw Hardware Diagnostic
    Draw_Box(4, 2, 12, 39, "Hardware Diagnostic", 1, false, false);
	Text(5, 4, WHITE, F("I2C Multiplexer (0x70)")); Dot(5, 26, 6); Bracket(5, 32, 5);
	Text(6, 4, WHITE, F("I2C RTC (0x52)")); Dot(6, 18, 14); Bracket(6, 32, 5);
	Text(7, 4, WHITE, F("I2C Serial ID (0x50)")); Dot(7, 24, 8); Bracket(7, 32, 5);
	Text(8, 4, WHITE, F("I2C Temperature (0x40)")); Dot(8, 26, 6); Bracket(8, 32, 5);
	Text(9, 4, WHITE, F("I2C Battery Gauge (0x36)")); Dot(9, 28, 4); Bracket(9, 32, 5);
	Text(10, 4, WHITE, F("I2C Battery Charger (0x6B)")); Dot(10, 30, 2); Bracket(10, 32, 5);
	Text(11, 4, WHITE, F("SD Card Connection")); Dot(11, 22, 10); Bracket(11, 32, 5);

	// Draw Detail Box
    Draw_Box(4, 40, 12, 79, "Detail", 2, false, false);
	Text(5, 42, WHITE, F("Serial ID")); Dot(5, 51, 9); Bracket(5, 60, 17);
	Text(6, 42, WHITE, F("Firmware Version")); Dot(6, 58, 10); Bracket(6, 68, 9);
	Text(7, 42, WHITE, F("Hardware Version")); Dot(7, 58, 10); Bracket(7, 68, 9);
	Text(8, 42, WHITE, F("Module Temperature")); Dot(8, 60, 9); Bracket(8, 69, 8); Text(8, 76, WHITE, F("C"));
	Text(9, 42, WHITE, F("Module Humidity")); Dot(9, 57, 12); Bracket(9, 69, 8); Text(9, 76, WHITE, F("%"));

	// Draw Battery Box
    Draw_Box(4, 80, 12, 119, "Battery", 3, false, false);
	Text(5, 82, WHITE, F("Instant Voltage")); Dot(5, 97, 13); Bracket(5, 110, 7);  Text(5, 116, WHITE, F("V"));
	Text(6, 82, WHITE, F("Temperature")); Dot(6, 93, 16); Bracket(6, 109, 8); Text(6, 116, WHITE, F("C"));
	Text(7, 82, WHITE, F("Average Current")); Dot(7, 97, 10); Bracket(7, 107, 10); Text(7, 115, WHITE, F("mA"));
	Text(8, 82, WHITE, F("State of Charge")); Dot(8, 97, 14); Bracket(8, 111, 6); Text(8, 116, WHITE, F("%"));
	Text(9, 82, WHITE, F("Full Battery Capacity")); Dot(9, 103, 6); Bracket(9, 109, 8); Text(9, 115, WHITE, F("mA"));
	Text(10, 82, WHITE, F("Instant Battery Capacity")); Dot(10, 106, 3); Bracket(10, 109, 8); Text(10, 115, WHITE, F("mA"));
	Text(11, 82, WHITE, F("Cycle Count")); Dot(11, 93, 19); Bracket(11, 112, 5);

	// Draw GSM Setup Box
    Draw_Box(13, 2, 27, 39, "GSM Setup", 4, false, false);
	Text(14, 4, WHITE, F("ATE=0")); Dot(14, 9, 23); Bracket(14, 32, 5); Text(14, 33, YELLOW, F(" ** "));
	Text(15, 4, WHITE, F("AT+CMEE=1")); Dot(15, 13, 19); Bracket(15, 32, 5); Text(15, 33, YELLOW, F(" ** "));
	Text(16, 4, WHITE, F("AT+FCLASS=0")); Dot(16, 15, 17); Bracket(16, 32, 5); Text(16, 33, YELLOW, F(" ** "));
	Text(17, 4, WHITE, F("AT&K0")); Dot(17, 9, 23); Bracket(17, 32, 5); Text(17, 33, YELLOW, F(" ** "));
	Text(18, 4, WHITE, F("AT+CPIN?")); Dot(18, 12, 20); Bracket(18, 32, 5); Text(18, 33, YELLOW, F(" ** "));
	Text(19, 4, WHITE, F("AT+CGSN")); Dot(19, 11, 21); Bracket(19, 32, 5); Text(19, 33, YELLOW, F(" ** "));
	Text(20, 4, WHITE, F("AT+GSN")); Dot(20, 10, 22); Bracket(20, 32, 5); Text(20, 33, YELLOW, F(" ** "));
	Text(21, 4, WHITE, F("AT+CCID")); Dot(21, 11, 21); Bracket(21, 32, 5); Text(21, 33, YELLOW, F(" ** "));
	Text(22, 4, WHITE, F("AT+GMI")); Dot(22, 10, 22); Bracket(22, 32, 5); Text(22, 33, YELLOW, F(" ** "));
	Text(23, 4, WHITE, F("AT+GMM")); Dot(23, 10, 22); Bracket(23, 32, 5); Text(23, 33, YELLOW, F(" ** "));
	Text(24, 4, WHITE, F("AT+GMR")); Dot(24, 10, 22); Bracket(24, 32, 5); Text(24, 33, YELLOW, F(" ** "));
	Text(25, 4, WHITE, F("AT+SLED=2")); Dot(25, 13, 19); Bracket(25, 32, 5); Text(25, 33, YELLOW, F(" ** "));
	Text(26, 4, WHITE, F("AT#E2SLRI=50")); Dot(26, 16, 16); Bracket(26, 32, 5); Text(26, 33, YELLOW, F(" ** "));

	// GSM Connection Box
    Draw_Box(13, 40, 27, 79, "GSM Connection", 5, false, false);
	Text(14, 42, WHITE, F("AT#REGMODE=1")); Dot(14, 54, 18); Bracket(14, 72, 5); Text(14, 73, YELLOW, F(" ** "));
	Text(15, 42, WHITE, F("AT#TXMONMODE=1")); Dot(15, 56, 16); Bracket(15, 72, 5); Text(15, 73, YELLOW, F(" ** "));
	Text(16, 42, WHITE, F("AT+CREG=0")); Dot(16, 51, 21); Bracket(16, 72, 5); Text(16, 73, YELLOW, F(" ** "));
	Text(17, 42, WHITE, F("AT+CGREG=0")); Dot(17, 52, 20); Bracket(17, 72, 5); Text(17, 73, YELLOW, F(" ** "));
	Text(18, 42, WHITE, F("AT#SCFG=1,1,1500,90,600,50")); Dot(18, 68, 4); Bracket(18, 72, 5); Text(18, 73, YELLOW, F(" ** "));
	Text(19, 42, WHITE, F("AT#SCFG=2,1,1500,90,300,50")); Dot(19, 68, 4); Bracket(19, 72, 5); Text(19, 73, YELLOW, F(" ** "));
	Text(20, 42, WHITE, F("AT#SCFGEXT=2,1,0,1,0,0")); Dot(20, 64, 8); Bracket(20, 72, 5); Text(20, 73, YELLOW, F(" ** "));
	Text(21, 42, WHITE, F("AT+CGDCONT=1,\"IP\",\"mgbs\"")); Dot(21, 66, 6); Bracket(21, 72, 5); Text(21, 73, YELLOW, F(" ** "));
	Text(22, 42, WHITE, F("AT#SERVIFO")); Dot(22, 52, 20); Bracket(22, 72, 5); Text(22, 73, YELLOW, F(" ** "));
	Text(23, 42, WHITE, F("AT+CGACT=1,1")); Dot(23, 54, 18); Bracket(23, 72, 5); Text(23, 73, YELLOW, F(" ** "));
	Text(24, 42, WHITE, F("AT+CGPADDR=1")); Dot(24, 54, 18); Bracket(24, 72, 5); Text(24, 73, YELLOW, F(" ** "));
	Text(25, 42, WHITE, F("AT#HTTPCFG=1,\"*****\",80,0")); Dot(25, 67, 5); Bracket(25, 72, 5); Text(25, 73, YELLOW, F(" ** "));
	Text(26, 42, WHITE, F("AT#ICMP=1")); Dot(26, 51, 21); Bracket(26, 72, 5); Text(26, 73, YELLOW, F(" ** "));

	// GSM Detail Box
    Draw_Box(13, 80, 20, 119, "GSM Detail", 6, false, false);
	Text(14, 82, WHITE, F("Manufacturer")); Dot(14, 94, 21); Bracket(14, 115, 2);
	Text(15, 82, WHITE, F("Model")); Dot(15, 87, 28); Bracket(15, 115, 2);
	Text(16, 82, WHITE, F("Firmware")); Dot(16, 90, 16); Bracket(16, 106, 11);
	Text(17, 82, WHITE, F("IMEI")); Dot(17, 86, 15); Bracket(17, 101, 16);
	Text(18, 82, WHITE, F("Serial ID")); Dot(18, 91, 15); Bracket(18, 106, 11);
	Text(19, 82, WHITE, F("SIM ICCID")); Dot(19, 91, 6); Bracket(19, 97, 20);

	// Connection Box
	Draw_Box(21, 80, 27, 119, "Connection", 7, false, false);
	Text(22, 82, WHITE, F("GSM Connection Time")); Dot(22, 101, 11); Bracket(22, 112, 5);
	Text(23, 82, WHITE, F("RSSI Level")); Dot(23, 92, 22); Bracket(23, 114, 3);
	Text(24, 82, WHITE, F("GSM Operator")); Dot(24, 94, 17); Bracket(24, 111, 6);
	Text(25, 82, WHITE, F("IP Address")); Dot(25, 92, 9); Bracket(25, 101, 16);
	Text(26, 82, WHITE, F("Socket Listen Status")); Dot(26, 102, 5); Bracket(26, 107, 10);

	// Selenoid Box
    Draw_Box(31, 2, 36, 98, "", 0, false, false);
    Draw_Box(31, 99, 36, 119, "", 0, false, false);
	Draw_Horizontal_Divider(33,2,96,true);
	Draw_Horizontal_Divider(33,99,20,true);
	Draw_Vertical_Divider(33,8,3);
	Draw_Vertical_Divider(33,14,3);
	Draw_Vertical_Divider(33,20,3);
	Draw_Vertical_Divider(33,26,3);
	Draw_Vertical_Divider(33,32,3);
	Draw_Vertical_Divider(33,38,3);
	Draw_Vertical_Divider(33,44,3);
	Draw_Vertical_Divider(33,50,3);
	Draw_Vertical_Divider(33,56,3);
	Draw_Vertical_Divider(33,62,3);
	Draw_Vertical_Divider(33,68,3);
	Draw_Vertical_Divider(33,74,3);
	Draw_Vertical_Divider(33,80,3);
	Draw_Vertical_Divider(33,86,3);
	Draw_Vertical_Divider(33,92,3);

	Draw_Vertical_Divider(31,26,2);
	Draw_Vertical_Divider(31,50,2);
	Draw_Vertical_Divider(31,74,2);

	Text(32, 6, WHITE, F("Expander A [    ]"));
	Text(32, 30, WHITE, F("Expander B [    ]"));
	Text(32, 54, WHITE, F("Expander C [    ]"));
	Text(32, 77, WHITE, F("Expander D [    ]"));
	Text(34, 4, WHITE, F("S01"));
	Text(34, 10, WHITE, F("S02"));
	Text(34, 16, WHITE, F("S03"));
	Text(34, 22, WHITE, F("S04"));
	Text(34, 28, WHITE, F("S05"));
	Text(34, 34, WHITE, F("S06"));
	Text(34, 40, WHITE, F("S07"));
	Text(34, 46, WHITE, F("S08"));
	Text(34, 52, WHITE, F("S09"));
	Text(34, 58, WHITE, F("S10"));
	Text(34, 64, WHITE, F("S11"));
	Text(34, 70, WHITE, F("S12"));
	Text(34, 76, WHITE, F("S13"));
	Text(34, 82, WHITE, F("S14"));
	Text(34, 88, WHITE, F("S15"));
	Text(34, 94, WHITE, F("S16"));
	Text(32, 101, WHITE, F("P-Delta       Bar"));
	Text(34, 101, WHITE, F("P-In          Bar"));
	Text(35, 101, WHITE, F("P-Out         Bar"));

	// JSON Data Box
    Draw_Box(28, 2, 30, 119, "", 8, false, false);

	// Setting Detail
    Draw_Box(37, 2, 46, 98, "Data", 0, false, false);


	// Setting Section
    Draw_Box(37, 99, 46, 119, "Setting", 0, false, false);
	Text(39, 101, WHITE, F("Filter Count.[  ]"));
	Text(40, 101, WHITE, F("State.......[   ]"));
	Text(41, 101, WHITE, F("Stabiliser....[ ]"));
	Text(42, 101, WHITE, F("HydroSyclone..[ ]"));
	Text(43, 101, WHITE, F("Irrigation....[ ]"));
	//Text(44, 101, WHITE, F("IDLE..........[ ]"));

	Draw_Vertical_Divider(47,99,2);

}

// Define Library Class
Console Terminal;

// 1903