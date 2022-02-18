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
	if (_Type == LINE_AFTER_CURSOR) _Console->write(CLR_LINE_AFTER_CURSOR);
	if (_Type == LINE_TO_CURSOR) _Console->write(CLR_LINE_TO_CURSOR);
	if (_Type == LINE) _Console->write(CLR_LINE);
	if (_Type == SCREEN) _Console->write(CLR_SCREEN);
	if (_Type == ALL) _Console->write(CLR_ALL);

}

// Cursor Functions
void Console::Cursor(bool _State) {

	// Cursor On
	if (_State == true) _Console->write(CURSOR_ON);	

	// Cursor Off
	if (_State == false) _Console->write(CURSOR_OFF);	

}
void Console::Set_Cursor(uint8_t _x, uint8_t _y) {

	_Send_CMD(_x);
	_Console->write(';');
	_Console->print(_y);
	_Console->write('H');

}

// Print Functions
void Console::Text(uint8_t _x, uint8_t _y, Colors _Color, String _Value) {

	// Print Text
	Terminal.Text_Color(_Color); 
	Terminal.Set_Cursor(_x, _y); 
	Serial.println(_Value);

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


void Console::Background_Color(Colors _Color) {

	_Format_Text((uint8_t)_Color + 10);

}

// Box Drawing Functions
void Console::Draw_Box(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2, char *_Text, uint8_t _Number, bool _Header, bool _Footer) {

	//Set Color
	Terminal.Text_Color(WHITE);
	Terminal.Text_Format(DIM);

	// Print Corners
	Terminal.Set_Cursor(_X1, _Y1); Serial.println("┌");
	Terminal.Set_Cursor(_X1, _Y2); Serial.println("┐");
	Terminal.Set_Cursor(_X2, _Y1); Serial.println("└");
	Terminal.Set_Cursor(_X2, _Y2); Serial.println("┘");

	// Print Lines
	for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {Terminal.Set_Cursor(i, _Y1); Serial.println("│");}
	for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {Terminal.Set_Cursor(i, _Y2); Serial.println("│");}
	for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {Terminal.Set_Cursor(_X1, i); Serial.println("─");}
	for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {Terminal.Set_Cursor(_X2, i); Serial.println("─");}

	// Print Header
	Terminal.Text_Color(YELLOW); Terminal.Set_Cursor(_X1, _Y1 + 2); Serial.println(_Text);
	Terminal.Text_Color(WHITE);Terminal.Set_Cursor(_X1, _Y2 - 4); Serial.println("[");
	Terminal.Text_Color(YELLOW); Terminal.Set_Cursor(_X1, _Y2 - 3); Serial.println(_Number);
	Terminal.Text_Color(WHITE);Terminal.Set_Cursor(_X1, _Y2 - 2); Serial.println("]");

	// Draw Footer
	if (_Header == true) Draw_Box_Header(_X1, _Y1, _X2, _Y2);
	if (_Footer == true) Draw_Box_Footer(_X1, _Y1, _X2, _Y2);

}
void Console::Draw_Box_Footer(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

	//Set Color
	Terminal.Text_Color(WHITE);
	Terminal.Text_Format(DIM);

	// Print Corners
	Terminal.Set_Cursor(_X2 - 2, _Y1); Serial.println("├");
	Terminal.Set_Cursor(_X2 - 2, _Y2); Serial.println("┤");

	// Print Lines
	for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {Terminal.Set_Cursor(_X2 - 2, i); Serial.println("─");}

}
void Console::Draw_Box_Header(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

	//Set Color
	Terminal.Text_Color(WHITE);
	Terminal.Text_Format(DIM);

	// Print Corners
	Terminal.Set_Cursor(_X1 + 2, _Y1); Serial.println("├");
	Terminal.Set_Cursor(_X1 + 2, _Y2); Serial.println("┤");

	// Print Lines
	for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {Terminal.Set_Cursor(_X1 + 2, i); Serial.println("─");}

}
void Console::Draw_Horizontal_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length, bool _End) {

	//Set Color
	Terminal.Text_Color(WHITE);
	Terminal.Text_Format(DIM);

	// Print Corners
	if (_End == true) {
		Terminal.Set_Cursor(_X1, _Y1); Serial.println("├");
		Terminal.Set_Cursor(_X1, _Y1 + _Length); Serial.println("┤");
	}

	// Print Lines
	for (uint8_t i = _Y1 + 1; i <= _Y1 + _Length - 1; i++) {Terminal.Set_Cursor(_X1, i); Serial.println("─");}

}
void Console::Draw_Vertical_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length) {

	//Set Color
	Terminal.Text_Color(WHITE);
	Terminal.Text_Format(DIM);

	// Print Corners
	Terminal.Set_Cursor(_X1, _Y1); Serial.println("┬");
	Terminal.Set_Cursor(_X1 + _Length, _Y1); Serial.println("┴");

	// Print Lines
	for (uint8_t i = _X1 + 1; i <= _X1 + _Length - 1; i++) {Terminal.Set_Cursor(i, _Y1); Serial.println("│");}

}
void Console::Print_Box_Title(uint8_t _X1, uint8_t _Y1, uint8_t _Y2, String _Title) {

	// Calculate Position
	uint8_t _Width = _Y2 - _Y1;
	uint8_t _Text_Size = _Title.length();
	uint8_t _Position = (_Width) - (_Text_Size / 2);

	// Print Header
	Terminal.Text_Color(WHITE); 
	Terminal.Text_Format(BRIGHT);
	Terminal.Set_Cursor(_X1 + 1, _Position); 
	Serial.println(_Title);
	Terminal.Text_Format(RESET);

}

// Stats Table
void Console::Draw_3Row_Stat_Table(uint8_t _X1, uint8_t _Y1) {

	//32,5

	Terminal.Draw_Horizontal_Divider(_X1 + 1, _Y1, 50, false);
	Terminal.Draw_Horizontal_Divider(_X1 + 5, _Y1, 50, false);

	Terminal.Draw_Vertical_Divider(_X1 + 1,_Y1 + 9,4);
	Terminal.Draw_Vertical_Divider(_X1 + 1,_Y1 + 19,4);
	Terminal.Draw_Vertical_Divider(_X1 + 1,_Y1 + 29,4);
	Terminal.Draw_Vertical_Divider(_X1 + 1,_Y1 + 39,4);

	Terminal.Text(_X1, _Y1 + 11, WHITE, "Instant");
	Terminal.Text(_X1, _Y1 + 21, WHITE, "Minimum");
	Terminal.Text(_X1, _Y1 + 31, WHITE, "Maximum");
	Terminal.Text(_X1, _Y1 + 41, WHITE, "Average");

	Terminal.Text(_X1 + 2, _Y1 + 1, WHITE, "Phase R");
	Terminal.Text(_X1 + 3, _Y1 + 1, WHITE, "Phase S");
	Terminal.Text(_X1 + 4, _Y1 + 1, WHITE, "Phase T");


}
void Console::Draw_1Row_Stat_Table(uint8_t _X1, uint8_t _Y1, String _Variable) {

	//32,5

	Terminal.Draw_Horizontal_Divider(_X1 + 1, _Y1, 50, false);
	Terminal.Draw_Horizontal_Divider(_X1 + 3, _Y1, 50, false);

	Terminal.Draw_Vertical_Divider(_X1 + 1,_Y1 + 9,2);
	Terminal.Draw_Vertical_Divider(_X1 + 1,_Y1 + 19,2);
	Terminal.Draw_Vertical_Divider(_X1 + 1,_Y1 + 29,2);
	Terminal.Draw_Vertical_Divider(_X1 + 1,_Y1 + 39,2);

	Terminal.Text(_X1, _Y1 + 11, WHITE, "Instant");
	Terminal.Text(_X1, _Y1 + 21, WHITE, "Minimum");
	Terminal.Text(_X1, _Y1 + 31, WHITE, "Maximum");
	Terminal.Text(_X1, _Y1 + 41, WHITE, "Average");

	Terminal.Text(_X1 + 2, _Y1 + 1, WHITE, _Variable);


}

// Private Functions
void Console::_Send_CMD(uint8_t _val) {

	_Console->write("\e[");
	_Console->print(_val);

}
void Console::_Format_Text(uint8_t _val) {

	_Send_CMD(_val);
	_Console->write('m');

}

// Batch Functions
void Console::B100BB(void) {

	// Draw Main Screen
    Terminal.Draw_Box(1, 1, 52, 120, "", 0, true, true);
    Terminal.Print_Box_Title(1,1,60,"PowerStat V2");

	// Header Titles
	Terminal.Text(2, 3, WHITE, "Up Time : ");

	// Draw Hardware Diagnostic
    Terminal.Draw_Box(4, 2, 12, 39, "Hardware Diagnostic", 1, false, false);
	Terminal.Text(5, 4, WHITE, "I2C Multiplexer (0x70)......[    ]");
	Terminal.Text(6, 4, WHITE, "I2C RTC (0x52)..............[    ]");
	Terminal.Text(7, 4, WHITE, "I2C Serial ID (0x50)........[    ]");
	Terminal.Text(8, 4, WHITE, "I2C Temperature (0x40)......[    ]");
	Terminal.Text(9, 4, WHITE, "I2C Battery Gauge (0x36)....[    ]");
	Terminal.Text(10, 4, WHITE, "I2C Battery Charger (0x6B)..[    ]");
	Terminal.Text(11, 4, WHITE, "SD Card Connection..........[    ]");

	// Draw Detail Box
    Terminal.Draw_Box(4, 40, 12, 79, "Detail", 2, false, false);
	Terminal.Text(5, 42, WHITE, "Serial ID.........[                ]");
	Terminal.Text(6, 42, WHITE, "Firmware Version..........[        ]");
	Terminal.Text(7, 42, WHITE, "Hardware Version..........[        ]");
	Terminal.Text(8, 42, WHITE, "Module Temperature.........[      C]");
	Terminal.Text(9, 42, WHITE, "Module Humidity............[      %]");
	Terminal.Text(10, 42, WHITE, "Device State...................[   ]");
	Terminal.Text(11, 42, WHITE, "Fault State....................[   ]");

	// Draw Battery Box
    Terminal.Draw_Box(4, 80, 12, 119, "Battery", 3, false, false);
	Terminal.Text(5, 82, WHITE, "Instant Voltage.............[     V]");
	Terminal.Text(6, 82, WHITE, "Temperature................[      C]");
	Terminal.Text(7, 82, WHITE, "Average Current..........[       mA]");
	Terminal.Text(8, 82, WHITE, "State of Charge..............[    %]");
	Terminal.Text(9, 82, WHITE, "Full Battery Capacity......[     mA]");
	Terminal.Text(10, 82, WHITE, "Instant Battery Capacity...[     mA]");
	Terminal.Text(11, 82, WHITE, "Cycle Count.....................[  ]");

	// Draw GSM Setup Box
    Terminal.Draw_Box(13, 2, 27, 39, "GSM Setup", 4, false, false);
	Terminal.Text(14, 4, WHITE, "ATE=0.......................[    ]");
	Terminal.Text(15, 4, WHITE, "AT+CMEE=1...................[    ]");
	Terminal.Text(16, 4, WHITE, "AT+FCLASS=0.................[    ]");
	Terminal.Text(17, 4, WHITE, "AT&K0.......................[    ]");
	Terminal.Text(18, 4, WHITE, "AT+CPIN?....................[    ]");
	Terminal.Text(19, 4, WHITE, "AT+CGSN.....................[    ]");
	Terminal.Text(20, 4, WHITE, "AT+GSN......................[    ]");
	Terminal.Text(21, 4, WHITE, "AT+CCID.....................[    ]");
	Terminal.Text(22, 4, WHITE, "AT+GMI......................[    ]");
	Terminal.Text(23, 4, WHITE, "AT+GMM......................[    ]");
	Terminal.Text(24, 4, WHITE, "AT+GMR......................[    ]");
	Terminal.Text(25, 4, WHITE, "AT+SLED=2...................[    ]");
	Terminal.Text(26, 4, WHITE, "AT#E2SLRI=50................[    ]");

	// GSM Connection Box
    Terminal.Draw_Box(13, 40, 27, 79, "GSM Connection", 5, false, false);
	Terminal.Text(14, 42, WHITE, "AT#REGMODE=1..................[    ]");
	Terminal.Text(15, 42, WHITE, "AT#TXMONMODE=1................[    ]");
	Terminal.Text(16, 42, WHITE, "AT+CREG=0.....................[    ]");
	Terminal.Text(17, 42, WHITE, "AT+CGREG=0....................[    ]");
	Terminal.Text(18, 42, WHITE, "AT#SCFG=1,1,1500,90,600,50....[    ]");
	Terminal.Text(19, 42, WHITE, "AT#SCFG=2,1,1500,90,300,50....[    ]");
	Terminal.Text(20, 42, WHITE, "AT#SCFGEXT=2,1,0,1,0,0........[    ]");
	Terminal.Text(21, 42, WHITE, "AT+CGDCONT=1,\"IP\",\"mgbs\"......[    ]");
	Terminal.Text(22, 42, WHITE, "AT#SERVIFO....................[    ]");
	Terminal.Text(23, 42, WHITE, "AT+CGACT=1,1..................[    ]");
	Terminal.Text(24, 42, WHITE, "AT+CGPADDR=1..................[    ]");
	Terminal.Text(25, 42, WHITE, "AT#HTTPCFG=1,\"*****\",80,0.....[    ]");
	Terminal.Text(26, 42, WHITE, "AT#ICMP=1.....................[    ]");

	// GSM Detail Box
    Terminal.Draw_Box(13, 80, 20, 119, "GSM Detail", 6, false, false);
	Terminal.Text(14, 82, WHITE, "Manufacturer.....................[ ]");
	Terminal.Text(15, 82, WHITE, "Model...................[          ]");
	Terminal.Text(16, 82, WHITE, "Firmware................[          ]");
	Terminal.Text(17, 82, WHITE, "IMEI...............[               ]");
	Terminal.Text(18, 82, WHITE, "Serial ID...............[          ]");
	Terminal.Text(19, 82, WHITE, "SIM ICCID......[                   ]");

	// Connection Box
	Terminal.Draw_Box(21, 80, 27, 119, "Connection", 7, false, false);
	Terminal.Text(22, 82, WHITE, "GSM Connection Time...........[    ]");
	Terminal.Text(23, 82, WHITE, "RSSI Level......................[  ]");
	Terminal.Text(24, 82, WHITE, "GSM Operator.................[     ]");
	Terminal.Text(25, 82, WHITE, "IP Address.........[               ]");
	Terminal.Text(26, 82, WHITE, "Socket Listen Status.....[         ]");

	// Power Box
    Terminal.Draw_Box(31, 2, 43, 119, "Power", 0, false, false);
	Terminal.Draw_Horizontal_Divider(38,2,117,true);
	Terminal.Draw_Vertical_Divider(31,60,12);
	Terminal.Draw_3Row_Stat_Table(32,5);
	Terminal.Draw_3Row_Stat_Table(32,63);
	Terminal.Draw_1Row_Stat_Table(39,5, "Freq");
	Terminal.Draw_1Row_Stat_Table(39,63, "Cos Fi");

	// JSON Data Box
    Terminal.Draw_Box(28, 2, 30, 119, "", 8, false, false);
    Terminal.Draw_Box(44, 2, 49, 119, "Data", 0, false, false);

}

// Define Library Class
Console Terminal;

// 1903