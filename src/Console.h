#ifndef __Console__
#define __Console__

	// Define Arduino Library
	#ifndef __Arduino__
		#include <Arduino.h>
	#endif

	// Color Definitions
	#define BLACK				(uint8_t)30
	#define RED					(uint8_t)31
	#define GREEN				(uint8_t)32
	#define YELLOW				(uint8_t)33
	#define BLUE				(uint8_t)34
	#define MAGENTA				(uint8_t)35
	#define CYAN				(uint8_t)36
	#define WHITE				(uint8_t)37
	#define GRAY				(uint8_t)90

	// Text Format Definitions
	#define RST					(uint8_t)0
	#define BRIGHT				(uint8_t)1
	#define DIM					(uint8_t)2
	#define UNDERSCORE			(uint8_t)4
	#define BLINK				(uint8_t)5
	#define REVERSE				(uint8_t)7
	#define HIDDEN				(uint8_t)8

	// Clear Type Definitions
	#define LINE_AFTER_CURSOR 	(uint8_t)0
	#define LINE_TO_CURSOR 		(uint8_t)1
	#define LINE 		    	(uint8_t)2
	#define SCREEN 			    (uint8_t)3
	#define ALL 			    (uint8_t)4

	// Console Class
	class Console {

		private:

			// Stream Variable
			Stream * Console_Serial;

			// Clear Terminal Function.
			void Clear(const uint8_t _Type) {

				// Clear Terminal Type
				switch (_Type) {

					// Clear Line After Cursor
					case LINE_AFTER_CURSOR: {

						// Print Clear Line After Cursor Command
						Console_Serial->print(F("\e[K"));

						// End Case
						break;

					}

					// Clear Line to Cursor
					case LINE_TO_CURSOR: {

						// Print Clear Line to Cursor Command
						Console_Serial->print(F("\e[1K"));

						// End Case
						break;

					}

					// Clear Line
					case LINE: {

						// Print Clear Line Command
						Console_Serial->print(F("\e[2K"));

						// End Case
						break;

					}

					// Clear Screen
					case SCREEN: {

						// Print Clear Screen Command
						Console_Serial->print(F("\e[2J"));

						// End Case
						break;

					}

					// Clear All
					case ALL: {

						// Print Clear All Command
						Console_Serial->print(F("\e[1;1H\e[2J"));

						// End Case
						break;

					}

					// Default
					default: {

						// End Case
						break;

					}

				}

			}

			// Change Cursor Visibility Function.
			void Cursor(const bool _State) {

				// Cursor On
				if (_State) Console_Serial->print(F("\e[?25h"));	

				// Cursor Off
				if (!_State) Console_Serial->print(F("\e[?25l"));	

			}

			// Draw Box Function.
			void Draw_Box(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2, String _Text, uint8_t _Number, bool _Header, bool _Footer) {

				// Set Text Color
				this->Text_Color(WHITE);

				// Set Text Format
				this->Text_Format(DIM);

				// Print Corners
				this->Set_Cursor(_X1, _Y1); Console_Serial->println(F("┌"));
				this->Set_Cursor(_X2, _Y1); Console_Serial->println(F("└"));
				this->Set_Cursor(_X1, _Y2); Console_Serial->println(F("┐"));
				this->Set_Cursor(_X2, _Y2); Console_Serial->println(F("┘"));

				// Print Lines
				for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {
					
					this->Set_Cursor(i, _Y1); Console_Serial->println(F("│"));
					this->Set_Cursor(i, _Y2); Console_Serial->println(F("│"));

				}
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
					
					this->Set_Cursor(_X1, i); Console_Serial->println(F("─"));
					this->Set_Cursor(_X2, i); Console_Serial->println(F("─"));
					
				}

				// Print Header
				this->Text_Color(YELLOW); this->Set_Cursor(_X1, _Y1 + 2); Console_Serial->println(_Text);

				// Print Header Number
				if (_Number != 0) {
					this->Text_Color(WHITE); this->Set_Cursor(_X1, _Y2 - 4); Console_Serial->println(F("[ ]"));
					this->Text_Color(YELLOW); this->Set_Cursor(_X1, _Y2 - 3); Console_Serial->println(_Number);
				}

				// Draw Header
				if (_Header) {

					// Set Text Color
					this->Text_Color(WHITE);

					// Print Corners
					this->Set_Cursor(_X1 + 2, _Y1); Console_Serial->println(F("├"));
					this->Set_Cursor(_X1 + 2, _Y2); Console_Serial->println(F("┤"));

					// Print Lines
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
						
						this->Set_Cursor(_X1 + 2, i); Console_Serial->println(F("─"));
						
					}

				}
				
				// Draw Footer			
				if (_Footer) {

					// Set Text Color
					this->Text_Color(WHITE);

					// Print Corners
					this->Set_Cursor(_X2 - 2, _Y1); Console_Serial->println(F("├"));
					this->Set_Cursor(_X2 - 2, _Y2); Console_Serial->println(F("┤"));

					// Print Lines
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
						
						this->Set_Cursor(_X2 - 2, i); Console_Serial->println(F("─"));
						
					}

				}
				
			}

			// Dot Print Function.
			void Dot(uint8_t _X, uint8_t _Y, uint8_t _Count) {

				for (uint8_t i = 0; i < _Count; i++) {

					this->Text(_X, _Y + i, GRAY, F("."));

				}

			}

			// Bracket Place Holder Function.
			void Bracket(uint8_t _X, uint8_t _Y, uint8_t _Space) {

				// Print Bracket Start
				this->Text(_X, _Y, WHITE, F("["));

				// Print Bracket Left
				this->Text(_X, _Y + _Space, WHITE, F("]"));

			}

			// Horizontal Line Divider Function.
			void Horizontal_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length, bool _End) {

				//Set Color
				Text_Color(WHITE);

				// Print Corners
				if (_End) {

					Set_Cursor(_X1, _Y1); Serial.println(F("├"));
					Set_Cursor(_X1, _Y1 + _Length); Serial.println(F("┤"));

				}

				// Print Lines
				for (uint8_t i = _Y1 + 1; i <= _Y1 + _Length - 1; i++) {

					Set_Cursor(_X1, i); Serial.println(F("─"));

				}
		
			}

			// Vertical Line Divider Function.
			void Vertical_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length) {

				//Set Color
				Text_Color(WHITE);

				// Print Corners
				Set_Cursor(_X1, _Y1); Console_Serial->println(F("┬"));
				Set_Cursor(_X1 + _Length, _Y1); Console_Serial->println(F("┴"));

				// Print Lines
				for (uint8_t i = _X1 + 1; i <= _X1 + _Length - 1; i++) {Set_Cursor(i, _Y1); Console_Serial->println(F("│"));}

			}

			// Hardware Diagnostic Box Print Function.
			void Print_Diagnostic(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw Hardware Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "Hardware Diagnostic", 1, false, false);

				// Print Text
				Text(_X1 + 1, _Y1 + 2, WHITE, F("I2C Multiplexer (0x70)")); 	Dot(_X1 + 1, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24));		Bracket(_X1 + 1, _Y2 - 7, 5);
				Text(_X1 + 2, _Y1 + 2, WHITE, F("I2C RTC (0x52)")); 			Dot(_X1 + 2, _Y1 + 16, (_Y2 - 7) - (_Y1 + 16)); 	Bracket(_X1 + 2, _Y2 - 7, 5);
				Text(_X1 + 3, _Y1 + 2, WHITE, F("I2C Serial ID (0x50)")); 		Dot(_X1 + 3, _Y1 + 22, (_Y2 - 7) - (_Y1 + 22));		Bracket(_X1 + 3, _Y2 - 7, 5);
				Text(_X1 + 4, _Y1 + 2, WHITE, F("I2C Temperature (0x40)")); 	Dot(_X1 + 4, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24));		Bracket(_X1 + 4, _Y2 - 7, 5);
				Text(_X1 + 5, _Y1 + 2, WHITE, F("I2C Battery Gauge (0x36)")); 	Dot(_X1 + 5, _Y1 + 26, (_Y2 - 7) - (_Y1 + 26));		Bracket(_X1 + 5, _Y2 - 7, 5);
				Text(_X1 + 6, _Y1 + 2, WHITE, F("I2C Battery Charger (0x6B)")); Dot(_X1 + 6, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28));		Bracket(_X1 + 6, _Y2 - 7, 5);
				Text(_X1 + 7, _Y1 + 2, WHITE, F("SD Card Connection")); 		Dot(_X1 + 7, _Y1 + 20, (_Y2 - 7) - (_Y1 + 20)); 	Bracket(_X1 + 7, _Y2 - 7, 5);

			}

			// Detail Box Print Function.
			void Print_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw Hardware Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "Hardware Detail", 2, false, false);

				// Print Text
				Text(_X1 + 1, _Y1 + 2, WHITE, F("Serial ID")); 				Dot(_X1 + 1, _Y1 + 11, (_Y2 - 19) - (_Y1 + 11)); 	Bracket(_X1 + 1, _Y2 - 19, 17);
				Text(_X1 + 2, _Y1 + 2, WHITE, F("Firmware Version")); 		Dot(_X1 + 2, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	Bracket(_X1 + 2, _Y2 - 11, 9);
				Text(_X1 + 3, _Y1 + 2, WHITE, F("Hardware Version")); 		Dot(_X1 + 3, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	Bracket(_X1 + 3, _Y2 - 11, 9);
				Text(_X1 + 4, _Y1 + 2, WHITE, F("Module Temperature")); 	Dot(_X1 + 4, _Y1 + 20, (_Y2 - 10) - (_Y1 + 20)); 	Bracket(_X1 + 4, _Y2 - 10, 8); Text(_X1 + 4, _Y2 - 3, WHITE, F("C"));
				Text(_X1 + 5, _Y1 + 2, WHITE, F("Module Humidity")); 		Dot(_X1 + 5, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	Bracket(_X1 + 5, _Y2 - 10, 8); Text(_X1 + 5, _Y2 - 3, WHITE, F("%"));
				Text(_X1 + 6, _Y1 + 2, WHITE, F("Online Send Interval")); 	Dot(_X1 + 6, _Y1 + 22, (_Y2 - 10) - (_Y1 + 22)); 	Bracket(_X1 + 6, _Y2 - 10, 8); Text(_X1 + 6, _Y2 - 5, WHITE, F("Min"));
				Text(_X1 + 7, _Y1 + 2, WHITE, F("Offline Send Interval")); 	Dot(_X1 + 7, _Y1 + 23, (_Y2 - 10) - (_Y1 + 23)); 	Bracket(_X1 + 7, _Y2 - 10, 8); Text(_X1 + 7, _Y2 - 5, WHITE, F("Min"));

			}

			// Battery Print Function.
			void Print_Battery(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw Hardware Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "Battery", 3, false, false);

				// Print Text
				Text(_X1 + 1, _Y1 + 2, WHITE, F("Instant Voltage")); 			Dot(_X1 + 1, _Y1 + 17, (_Y2 - 9) - (_Y1 + 17)); 	Bracket(_X1 + 1, _Y2 - 9, 7);	Text(_X1 + 1, _Y2 - 3, WHITE, F("V"));
				Text(_X1 + 2, _Y1 + 2, WHITE, F("Temperature")); 				Dot(_X1 + 2, _Y1 + 13, (_Y2 - 10) - (_Y1 + 13)); 	Bracket(_X1 + 2, _Y2 - 10, 8);	Text(_X1 + 2, _Y2 - 3, WHITE, F("C"));
				Text(_X1 + 3, _Y1 + 2, WHITE, F("Average Current")); 			Dot(_X1 + 3, _Y1 + 17, (_Y2 - 13) - (_Y1 + 17)); 	Bracket(_X1 + 3, _Y2 - 13, 11);	Text(_X1 + 3, _Y2 - 4, WHITE, F("mA"));
				Text(_X1 + 4, _Y1 + 2, WHITE, F("State of Charge")); 			Dot(_X1 + 4, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	Bracket(_X1 + 4, _Y2 - 10, 8);	Text(_X1 + 4, _Y2 - 3, WHITE, F("%"));
				Text(_X1 + 5, _Y1 + 2, WHITE, F("Full Battery Capacity")); 		Dot(_X1 + 5, _Y1 + 23, (_Y2 - 10) - (_Y1 + 23)); 	Bracket(_X1 + 5, _Y2 - 10, 8);	Text(_X1 + 5, _Y2 - 4, WHITE, F("mA"));
				Text(_X1 + 6, _Y1 + 2, WHITE, F("Instant Battery Capacity")); 	Dot(_X1 + 6, _Y1 + 26, (_Y2 - 10) - (_Y1 + 26)); 	Bracket(_X1 + 6, _Y2 - 10, 8);	Text(_X1 + 6, _Y2 - 4, WHITE, F("mA"));
				Text(_X1 + 7, _Y1 + 2, WHITE, F("Charge State")); 				Dot(_X1 + 7, _Y1 + 14, (_Y2 - 15) - (_Y1 + 14)); 	Bracket(_X1 + 7, _Y2 - 15, 13);

			}

			// Battery GSM Initialize Function.
			void Print_GSM_Setup(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw GSM Setup Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "GSM Setup", 4, false, false);

				// Print Text	
				Text(_X1 + 1, _Y1 + 2, WHITE, F("ATE=0"));			Dot(_X1 + 1, _Y1 + 7, (_Y2 - 7) - (_Y1 + 7)); 		Bracket(_X1 + 1, _Y2 - 7, 5);
				Text(_X1 + 2, _Y1 + 2, WHITE, F("AT+CMEE=1"));		Dot(_X1 + 2, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 2, _Y2 - 7, 5);
				Text(_X1 + 3, _Y1 + 2, WHITE, F("AT+FCLASS=0"));	Dot(_X1 + 3, _Y1 + 13, (_Y2 - 7) - (_Y1 + 13)); 	Bracket(_X1 + 3, _Y2 - 7, 5);
				Text(_X1 + 4, _Y1 + 2, WHITE, F("AT&K0"));			Dot(_X1 + 4, _Y1 + 7, (_Y2 - 7) - (_Y1 + 7)); 		Bracket(_X1 + 4, _Y2 - 7, 5);
				Text(_X1 + 5, _Y1 + 2, WHITE, F("AT+CPIN?"));		Dot(_X1 + 5, _Y1 + 10, (_Y2 - 7) - (_Y1 + 10)); 	Bracket(_X1 + 5, _Y2 - 7, 5);
				Text(_X1 + 6, _Y1 + 2, WHITE, F("AT+CGSN"));		Dot(_X1 + 6, _Y1 + 9, (_Y2 - 7) - (_Y1 + 9)); 		Bracket(_X1 + 6, _Y2 - 7, 5);
				Text(_X1 + 7, _Y1 + 2, WHITE, F("AT+GSN"));			Dot(_X1 + 7, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8)); 		Bracket(_X1 + 7, _Y2 - 7, 5);
				Text(_X1 + 8, _Y1 + 2, WHITE, F("AT+CCID"));		Dot(_X1 + 8, _Y1 + 9, (_Y2 - 7) - (_Y1 + 9)); 		Bracket(_X1 + 8, _Y2 - 7, 5);
				Text(_X1 + 9, _Y1 + 2, WHITE, F("AT+GMI"));			Dot(_X1 + 9, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8)); 		Bracket(_X1 + 9, _Y2 - 7, 5);
				Text(_X1 + 10, _Y1 + 2, WHITE, F("AT+GMM"));		Dot(_X1 + 10, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8));	 	Bracket(_X1 + 10, _Y2 - 7, 5);
				Text(_X1 + 11, _Y1 + 2, WHITE, F("AT+GMR"));		Dot(_X1 + 11, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8));	 	Bracket(_X1 + 11, _Y2 - 7, 5);
				Text(_X1 + 12, _Y1 + 2, WHITE, F("AT+SLED=2"));		Dot(_X1 + 12, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 12, _Y2 - 7, 5);
				Text(_X1 + 13, _Y1 + 2, WHITE, F("AT#E2SLRI=50"));	Dot(_X1 + 13, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14)); 	Bracket(_X1 + 13, _Y2 - 7, 5);

			}

			// Battery GSM Connection Function.
			void Print_GSM_Connection(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw GSM Connection Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "GSM Connection", 5, false, false);

				// Print Text	
				Text(_X1 + 1, _Y1 + 2, WHITE, F("AT#REGMODE=0"));					Dot(_X1 + 1, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14)); 	Bracket(_X1 + 1, _Y2 - 7, 5);
				Text(_X1 + 2, _Y1 + 2, WHITE, F("AT#TXMONMODE=1"));					Dot(_X1 + 2, _Y1 + 15, (_Y2 - 7) - (_Y1 + 15)); 	Bracket(_X1 + 2, _Y2 - 7, 5);
				Text(_X1 + 3, _Y1 + 2, WHITE, F("AT+COPS=0,2,28601"));				Dot(_X1 + 3, _Y1 + 18, (_Y2 - 7) - (_Y1 + 18)); 	Bracket(_X1 + 3, _Y2 - 7, 5);
				Text(_X1 + 4, _Y1 + 2, WHITE, F("AT#AUTOBND=1"));					Dot(_X1 + 4, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14)); 	Bracket(_X1 + 4, _Y2 - 7, 5);
				Text(_X1 + 5, _Y1 + 2, WHITE, F("AT+CREG=0"));						Dot(_X1 + 5, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 5, _Y2 - 7, 5);
				Text(_X1 + 6, _Y1 + 2, WHITE, F("AT+CGREG=0"));						Dot(_X1 + 6, _Y1 + 12, (_Y2 - 7) - (_Y1 + 12)); 	Bracket(_X1 + 6, _Y2 - 7, 5);
				Text(_X1 + 7, _Y1 + 2, WHITE, F("AT+CGDCONT=1,\"IP\",\"mgbs\""));	Dot(_X1 + 7, _Y1 + 26, (_Y2 - 7) - (_Y1 + 26)); 	Bracket(_X1 + 7, _Y2 - 7, 5);
				Text(_X1 + 8, _Y1 + 2, WHITE, F("AT#SGACT=1,1"));					Dot(_X1 + 8, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14));		Bracket(_X1 + 8, _Y2 - 7, 5);
				Text(_X1 + 9, _Y1 + 2, WHITE, F("AT+CSQ")); 						Dot(_X1 + 9, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8)); 		Bracket(_X1 + 9, _Y2 - 7, 5);
				Text(_X1 + 10, _Y1 + 2, WHITE, F("AT#FRWL=1...")); 					Dot(_X1 + 10, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14));	Bracket(_X1 + 10, _Y2 - 7, 5);
				Text(_X1 + 11, _Y1 + 2, WHITE, F("AT#ICMP=1"));						Dot(_X1 + 11, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 11, _Y2 - 7, 5);
				Text(_X1 + 12, _Y1 + 2, WHITE, F("AT#MONI"));						Dot(_X1 + 12, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8)); 		Bracket(_X1 + 12, _Y2 - 7, 5);
				Text(_X1 + 13, _Y1 + 2, WHITE, F("AT+CCLK?"));						Dot(_X1 + 13, _Y1 + 9, (_Y2 - 7) - (_Y1 + 9)); 		Bracket(_X1 + 13, _Y2 - 7, 5);

			}

			// Battery GSM Detail Function.
			void Print_GSM_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw GSM Connection Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "GSM Detail", 4, false, false);

				// Print Text	
				Text(_X1 + 1, _Y1 + 2, WHITE, F("Manufacturer"));	Dot(_X1 + 1, _Y1 + 14, (_Y2 - 4) - (_Y1 + 14)); 	Bracket(_X1 + 1, _Y2 - 4, 2);
				Text(_X1 + 2, _Y1 + 2, WHITE, F("Model"));			Dot(_X1 + 2, _Y1 + 7, (_Y2 - 4) - (_Y1 + 7)); 		Bracket(_X1 + 2, _Y2 - 4, 2);
				Text(_X1 + 3, _Y1 + 2, WHITE, F("Firmware"));		Dot(_X1 + 3, _Y1 + 10, (_Y2 - 12) - (_Y1 + 10)); 	Bracket(_X1 + 3, _Y2 - 12, 10);
				Text(_X1 + 4, _Y1 + 2, WHITE, F("IMEI"));			Dot(_X1 + 4, _Y1 + 6, (_Y2 - 18) - (_Y1 + 6)); 		Bracket(_X1 + 4, _Y2 - 18, 16);
				Text(_X1 + 5, _Y1 + 2, WHITE, F("Serial ID"));		Dot(_X1 + 5, _Y1 + 11, (_Y2 - 13) - (_Y1 + 11)); 	Bracket(_X1 + 5, _Y2 - 13, 11);
				Text(_X1 + 6, _Y1 + 2, WHITE, F("ICCID"));			Dot(_X1 + 6, _Y1 + 7, (_Y2 - 22) - (_Y1 + 7)); 		Bracket(_X1 + 6, _Y2 - 22, 20);

			}

			// GSM Connection Detail Function.
			void Print_GSM_Connection_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw GSM Connection Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "GSM Connection", 5, false, false);

				// Print Text	
				Text(_X1 + 1, _Y1 + 2, WHITE, F("GSM Connection Time"));	Dot(_X1 + 1, _Y1 + 21, (_Y2 - 7) - (_Y1 + 21)); 	Bracket(_X1 + 1, _Y2 - 7, 5);
				Text(_X1 + 2, _Y1 + 2, WHITE, F("Signal Level"));			Dot(_X1 + 2, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	Bracket(_X1 + 2, _Y2 - 8, 6);
				Text(_X1 + 3, _Y1 + 2, WHITE, F("GSM Operator"));			Dot(_X1 + 3, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	Bracket(_X1 + 3, _Y2 - 8, 6);
				Text(_X1 + 4, _Y1 + 2, WHITE, F("IP Address"));				Dot(_X1 + 4, _Y1 + 12, (_Y2 - 18) - (_Y1 + 12)); 	Bracket(_X1 + 4, _Y2 - 18, 16);
				Text(_X1 + 5, _Y1 + 2, WHITE, F("LAC"));					Dot(_X1 + 5, _Y1 + 5, (_Y2 - 7) - (_Y1 + 5)); 		Bracket(_X1 + 5, _Y2 - 7, 5);
				Text(_X1 + 6, _Y1 + 2, WHITE, F("CELL ID"));				Dot(_X1 + 6, _Y1 + 9, (_Y2 - 7) - (_Y1 + 9)); 		Bracket(_X1 + 6, _Y2 - 7, 5);

			}

			// GSM FOTA
			void Print_GSM_FOTA_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw GSM Connection Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "FOTA", 6, false, false);

				// Print Text	
				Text(_X1 + 1, _Y1 + 2, WHITE, F("File ID"));			Dot(_X1 + 1, _Y1 + 9, (_Y2 - 9) - (_Y1 + 9)); 		Bracket(_X1 + 1, _Y2 - 9, 7);
				Text(_X1 + 2, _Y1 + 2, WHITE, F("Download Status"));	Dot(_X1 + 2, _Y1 + 17, (_Y2 - 7) - (_Y1 + 17)); 	Bracket(_X1 + 2, _Y2 - 7, 5);
				Text(_X1 + 3, _Y1 + 2, WHITE, F("FTP File Size"));		Dot(_X1 + 3, _Y1 + 15, (_Y2 - 10) - (_Y1 + 15)); 	Bracket(_X1 + 3, _Y2 - 10, 8);
				Text(_X1 + 4, _Y1 + 2, WHITE, F("SD File Size"));		Dot(_X1 + 4, _Y1 + 14, (_Y2 - 10) - (_Y1 + 14)); 	Bracket(_X1 + 4, _Y2 - 10, 8);
				Text(_X1 + 5, _Y1 + 2, WHITE, F("Download Percent"));	Dot(_X1 + 5, _Y1 + 18, (_Y2 - 8) - (_Y1 + 18)); 	Bracket(_X1 + 5, _Y2 - 8, 6);	Text(_X1 + 5, _Y2 - 3, WHITE, F("%"));
				Text(_X1 + 6, _Y1 + 2, WHITE, F("Download Time"));		Dot(_X1 + 6, _Y1 + 15, (_Y2 - 11) - (_Y1 + 15)); 	Bracket(_X1 + 6, _Y2 - 11, 9);	Text(_X1 + 6, _Y2 - 5, WHITE, F("Sec"));

			}

			// Pressure Stats
			void Print_Pressure_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw GSM Connection Diagnostic Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "Pressure", 7, false, false);

				// Print Text	
				Text(_X1 + 1, _Y1 + 2, WHITE, F("Instant"));	Dot(_X1 + 1, _Y1 + 9, (_Y2 - 12) - (_Y1 + 9)); 		Bracket(_X1 + 1, _Y2 - 12, 10); Text(_X1 + 1, _Y2 - 5, WHITE, F("Bar"));
				Text(_X1 + 2, _Y1 + 2, WHITE, F("Min"));		Dot(_X1 + 2, _Y1 + 5, (_Y2 - 12) - (_Y1 + 5)); 		Bracket(_X1 + 2, _Y2 - 12, 10); Text(_X1 + 2, _Y2 - 5, WHITE, F("Bar"));
				Text(_X1 + 3, _Y1 + 2, WHITE, F("Max"));		Dot(_X1 + 3, _Y1 + 5, (_Y2 - 12) - (_Y1 + 5)); 		Bracket(_X1 + 3, _Y2 - 12, 10); Text(_X1 + 3, _Y2 - 5, WHITE, F("Bar"));
				Text(_X1 + 4, _Y1 + 2, WHITE, F("Avarage"));	Dot(_X1 + 4, _Y1 + 9, (_Y2 - 12) - (_Y1 + 9)); 		Bracket(_X1 + 4, _Y2 - 12, 10); Text(_X1 + 4, _Y2 - 5, WHITE, F("Bar"));
				Text(_X1 + 5, _Y1 + 2, WHITE, F("Deviation"));	Dot(_X1 + 5, _Y1 + 11, (_Y2 - 12) - (_Y1 + 11)); 	Bracket(_X1 + 5, _Y2 - 12, 10); Text(_X1 + 5, _Y2 - 5, WHITE, F("Bar"));
				Text(_X1 + 6, _Y1 + 2, WHITE, F("Slope"));		Dot(_X1 + 6, _Y1 + 7, (_Y2 - 12) - (_Y1 + 7)); 		Bracket(_X1 + 6, _Y2 - 12, 10); Text(_X1 + 6, _Y2 - 3, WHITE, F("%"));
				Text(_X1 + 7, _Y1 + 2, WHITE, F("Data Count"));	Dot(_X1 + 7, _Y1 + 12, (_Y2 - 6) - (_Y1 + 12)); 	Bracket(_X1 + 7, _Y2 - 6, 4);

				// Limit Detail
				Text(_X1 + 2, _Y1 + 16, WHITE, F("[     Bar]"));
				Text(_X1 + 3, _Y1 + 16, WHITE, F("[     Bar]"));
				Text(_X1 + 6, _Y1 + 20, WHITE, F("[   %]"));

			}

			// Power Detail Function.
			void Print_Power_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw State Box
				this->Draw_Box(_X1, _Y1, _X2, _Y2, "Power", 0, false, false);

				// Draw Horizontal Lines
				Horizontal_Divider(_X1 + 2, _Y1 + 4, 49, false);
				Horizontal_Divider(_X1 + 6, _Y1 + 4, 49, false);

				// Draw Vertical Lines
				Vertical_Divider(_X1 + 2, _Y1 + 13, 4);
				Vertical_Divider(_X1 + 2, _Y1 + 23, 4);
				Vertical_Divider(_X1 + 2, _Y1 + 33, 4);
				Vertical_Divider(_X1 + 2, _Y1 + 43, 4);

				// Print Text
				Text(_X1 + 1, _Y1 + 15, WHITE, F("Voltage"));
				Text(_X1 + 1, _Y1 + 25, WHITE, F("Current"));
				Text(_X1 + 1, _Y1 + 36, WHITE, F("Freq"));
				Text(_X1 + 1, _Y1 + 46, WHITE, F("Cos Fi"));
				Text(_X1 + 3, _Y1 + 5, WHITE, F("Phase R"));
				Text(_X1 + 4, _Y1 + 5, WHITE, F("Phase S"));
				Text(_X1 + 5, _Y1 + 5, WHITE, F("Phase T"));

			}

			// Power Fault Detail Function.
			void Print_Power_Fault_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw State Box
				this->Draw_Box(_X1, _Y1, _X2, _Y2, "Power Fault", 0, false, false);

				Horizontal_Divider(_X1 + 2, _Y1 + 2, 54, false);
				Horizontal_Divider(_X1 + 6, _Y1 + 2, 54, false);

				Vertical_Divider(_X1 + 2, _Y1 + 11, 4);
				Vertical_Divider(_X1 + 2, _Y1 + 18, 4);
				Vertical_Divider(_X1 + 2, _Y1 + 25, 4);
				Vertical_Divider(_X1 + 2, _Y1 + 33, 4);
				Vertical_Divider(_X1 + 2, _Y1 + 41, 4);
				Vertical_Divider(_X1 + 2, _Y1 + 49, 4);

				Text(_X1 + 1, _Y1 + 14, WHITE, F("LV"));
				Text(_X1 + 1, _Y1 + 21, WHITE, F("HV"));
				Text(_X1 + 1, _Y1 + 28, WHITE, F("LFQ"));
				Text(_X1 + 1, _Y1 + 36, WHITE, F("HFQ"));
				Text(_X1 + 1, _Y1 + 44, WHITE, F("VIM"));
				Text(_X1 + 1, _Y1 + 52, WHITE, F("IIM"));

				Text(_X1 + 3, _Y1 + 3, WHITE, F("Max"));
				Text(_X1 + 4, _Y1 + 3, WHITE, F("Fault"));
				Text(_X1 + 5, _Y1 + 3, WHITE, F("Min"));

				Text(_X1 + 4, _Y1 + 14, WHITE, F("[ ]"));
				Text(_X1 + 4, _Y1 + 21, WHITE, F("[ ]"));
				Text(_X1 + 4, _Y1 + 28, WHITE, F("[ ]"));
				Text(_X1 + 4, _Y1 + 36, WHITE, F("[ ]"));
				Text(_X1 + 4, _Y1 + 44, WHITE, F("[ ]"));
				Text(_X1 + 4, _Y1 + 52, WHITE, F("[ ]"));
				
			}

			// State Detail Function.
			void Print_State_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

				// Draw State Box
				Draw_Box(_X1, _Y1, _X2, _Y2, "", 0, false, false);
				Vertical_Divider(_X1, _Y1 + 100, 2);

				// Print Text	
				Text(_X1 + 1, _Y1 + 2, WHITE, F("R [ ] -"));
				Text(_X1 + 1, _Y1 + 10, WHITE, F("S [ ] -"));
				Text(_X1 + 1, _Y1 + 18, WHITE, F("T [ ] -"));
				Text(_X1 + 1, _Y1 + 26, WHITE, F("M1 [ ] -"));
				Text(_X1 + 1, _Y1 + 35, WHITE, F("M2 [ ] -"));
				Text(_X1 + 1, _Y1 + 44, WHITE, F("M3 [ ] -"));
				Text(_X1 + 1, _Y1 + 53, WHITE, F("Th [ ] -"));
				Text(_X1 + 1, _Y1 + 62, WHITE, F("Mp [ ]"));

				// Print Instant Value
				Text(_X1 + 1, _Y1 + 103, WHITE, F("Command"));

			}

		public:

			// Construct a new Console object
			Console(Stream &_Serial) {

				//Set serial port
				this->Console_Serial = &_Serial;

			}

			// Begin Console.
			void Begin(void) {

				// Cursor Off
				this->Cursor(false);

				// Clear Screen
				this->Clear(SCREEN);

				// Reset Delay
				delay(5);

			}

			// Set Cursor Position Function.
			void Set_Cursor(uint8_t _X, uint8_t _Y) {

				// Set Cursor Position
				Console_Serial->print(F("\e["));
				Console_Serial->print(_X);
				Console_Serial->print(F(";"));
				Console_Serial->print(_Y);
				Console_Serial->print(F("H"));

			}

			// Terminal Beep Sound Function.
			void Beep(void) {

				// Beep Terminal.
				Console_Serial->print(F("\x07"));

			}

			// Print Text to Specified Position and Color.
			void Text(uint8_t _X, uint8_t _Y, uint8_t _Color, String _Value) {

				// Set Text Cursor Position
				Set_Cursor(_X, _Y); 

				// Set Text Color
				Text_Color(_Color); 

				// Print Text			
				Console_Serial->println(String(_Value));

			}

			// Set Text Color Function.
			void Text_Color(uint8_t _Color) {

				// Set Text Color.
				Console_Serial->print(F("\e["));
				Console_Serial->print(_Color);
				Console_Serial->write('m');

			}

			// Set Text Format Function
			void Text_Format(const uint8_t _Format) {

				// Set Text Format
				Serial.print(F("\e["));
				Serial.print(_Format);
				Serial.write('m');

			}

			// Set Back Ground Color Function.
			void Background_Color(uint8_t _Color) {

				// Set Back Ground Color.
				Console_Serial->print(F("\e["));
				Console_Serial->print(_Color + 10);
				Console_Serial->write('m');

			}

			// OK Decide Function.
			void OK_Decide(bool _Result, uint8_t _X, uint8_t _Y) {

				// Print Command State
				if (_Result) {

					Text(_X, _Y, GREEN, F(" OK "));

				} else {

					Text(_X, _Y, RED, F("FAIL"));

				}
		
			}

			// GSM Command Prcocess
			void GSM_Command(uint8_t _X, uint8_t _Y, String _Command) {

				// Set Text Cursor Position
				Set_Cursor(_X, _Y); 

				// Clear Line
				for (uint8_t i = 0; i < 30; i++) Console_Serial->print(F(" "));
				
				// Print Dot
				Text(_X, _Y, GRAY, F(".............................."));

				// Print Command
				Text(_X, _Y, WHITE, _Command);

				// Print Response Wait Dot
				Text(_X, _Y + 31, BLUE, F(" .. "));
		
			}

			// PowerStat V4 Publish Bit Table
			void Status_Variables(uint8_t _Mask_Type, uint32_t _Publish_Mask) {

				// Set Mask X Position
				uint8_t _X = 40 + _Mask_Type;

				this->Text(_X, 15, (((_Publish_Mask & (1UL << STATUS_PUMP)) >> STATUS_PUMP) ? GREEN : RED), F("P"));
				this->Text(_X, 18, (((_Publish_Mask & (1UL << STATUS_PHASE_R)) >> STATUS_PHASE_R) ? GREEN : RED), F("VR"));
				this->Text(_X, 22, (((_Publish_Mask & (1UL << STATUS_PHASE_S)) >> STATUS_PHASE_S) ? GREEN : RED), F("VS"));
				this->Text(_X, 26, (((_Publish_Mask & (1UL << STATUS_PHASE_T)) >> STATUS_PHASE_T) ? GREEN : RED), F("VT"));
				if (_Mask_Type == 0) this->Text(_X, 30, ((((PINK) >> (4)) & 0x01) ? GREEN : RED), F("M1"));
				if (_Mask_Type == 0) this->Text(_X, 34, ((((PINK) >> (3)) & 0x01) ? GREEN : RED), F("M2"));
				if (_Mask_Type == 0) this->Text(_X, 38, ((((PINK) >> (2)) & 0x01) ? GREEN : RED), F("M3"));
				this->Text(_X, 42, (((_Publish_Mask & (1UL << STATUS_FAULT_TH)) >> STATUS_FAULT_TH) ? GREEN : RED), F("TH"));
				this->Text(_X, 46, (((_Publish_Mask & (1UL << STATUS_FAULT_MP)) >> STATUS_FAULT_MP) ? GREEN : RED), F("MP"));
				this->Text(_X, 50, (((_Publish_Mask & (1UL << STATUS_FAULT_SA)) >> STATUS_FAULT_SA) ? GREEN : RED), F("SA"));
				this->Text(_X, 54, (((_Publish_Mask & (1UL << STATUS_P_LOW)) >> STATUS_P_LOW) ? GREEN : RED), F("PL"));
				this->Text(_X, 58, (((_Publish_Mask & (1UL << STATUS_P_HIGH)) >> STATUS_P_HIGH) ? GREEN : RED), F("PH"));
				this->Text(_X, 62, (((_Publish_Mask & (1UL << STATUS_P_DROP)) >> STATUS_P_DROP) ? GREEN : RED), F("PD"));
				this->Text(_X, 66, (((_Publish_Mask & (1UL << STATUS_P_RISE)) >> STATUS_P_RISE) ? GREEN : RED), F("PR"));
				this->Text(_X, 70, (((_Publish_Mask & (1UL << STATUS_V_LOW)) >> STATUS_V_LOW) ? GREEN : RED), F("VL"));
				this->Text(_X, 74, (((_Publish_Mask & (1UL << STATUS_V_HIGH)) >> STATUS_V_HIGH) ? GREEN : RED), F("VH"));
				this->Text(_X, 78, (((_Publish_Mask & (1UL << STATUS_I_HIGH)) >> STATUS_I_HIGH) ? GREEN : RED), F("IH"));
				this->Text(_X, 82, (((_Publish_Mask & (1UL << STATUS_FQ_LOW)) >> STATUS_FQ_LOW) ? GREEN : RED), F("FQL"));
				this->Text(_X, 87, (((_Publish_Mask & (1UL << STATUS_FQ_HIGH)) >> STATUS_FQ_HIGH) ? GREEN : RED), F("FQH"));
				this->Text(_X, 92, (((_Publish_Mask & (1UL << STATUS_V_IMBALANCE)) >> STATUS_V_IMBALANCE) ? GREEN : RED), F("VIM"));
				this->Text(_X, 97, (((_Publish_Mask & (1UL << STATUS_I_IMBALANCE)) >> STATUS_I_IMBALANCE) ? GREEN : RED), F("IIM"));
				this->Text(_X, 108, (((_Publish_Mask & (1UL << STATUS_P_SENSOR)) >> STATUS_P_SENSOR) ? GREEN : RED), F("PS"));
				this->Text(_X, 112, (((_Publish_Mask & (1UL << STATUS_SD)) >> STATUS_SD) ? GREEN : RED), F("SD"));
				this->Text(_X, 116, (((_Publish_Mask & (1UL << STATUS_SYSTEM)) >> STATUS_SYSTEM) ? GREEN : RED), F("SYS"));

			}

			/* Console Template Functions */

			// I2C Scanner Terminal Batch
			void I2C_Scanner_Table(void) {

				// Draw Console Table Grid
				for (uint8_t i = 1; i <= 23; i = i + 2) Horizontal_Divider(i, 1, 120, false);
				Vertical_Divider(1, 1, 22);
				for (uint8_t i = 9; i <= 120; i = i + 7) Vertical_Divider(3, i, 18);
				Vertical_Divider(1, 121, 22);

				// Draw Corners
				this->Text(1, 1, WHITE, F("┌"));
				this->Text(1, 121, WHITE, F("┐"));
				this->Text(23, 1, WHITE, F("└"));
				this->Text(23, 121, WHITE, F("┘"));

				// Draw T
				for (uint8_t i = 3; i <= 21; i = i + 2) {Set_Cursor(i,1); Serial.print(F("├"));}
				for (uint8_t i = 3; i <= 21; i = i + 2) {Set_Cursor(i,121); Serial.print(F("┤"));}
				
				// Draw Cross Section
				for (uint8_t i = 5; i <= 19; i = i + 2) {for (uint8_t j = 9; j <= 120; j = j + 7) {Set_Cursor(i,j); Serial.print(F("┼"));}}
				
				// Write Text
				this->Text(1, 60, WHITE, F("I2C Device Explorer"));
				this->Text(22, 3, WHITE, F("Total connected device :"));
				this->Text(22, 86, WHITE, F("Current Mux Channel [0-8] :"));
				this->Text(24, 100, WHITE, F("github.com/akkoyun"));

				// Print Colum Headers
				uint8_t _C = 0;
				for (uint8_t i = 6; i <= 21; i = i + 2) {
					this->Text(i, 3, WHITE, F("0x"));
					this->Text(i, 5, WHITE, String(_C));
					this->Text(i, 6, WHITE, F("_"));
					_C++;
				}

				// Print Row Headers
				uint8_t _R = 0;
				for (uint8_t i = 11; i <= 121; i = i + 7) {
					this->Text(4, i, WHITE, F("0x_"));
					this->Text(4, i + 3, WHITE, String(_R, HEX));
					_R++;
				}

			}

			// MAX78630 Terminal Batch
			void MAX78630(void) {

				// Draw Main Box
				this->Draw_Box(1, 1, 40, 80, "", 0, true, true);

				// Print Header 
				this->Text(1, 40, WHITE, F("MAX78630 Energy Meter"));

				// Draw Voltage
				this->Draw_Box(4, 2, 27, 32, "Voltage", 1, false, false);
				this->Text(6, 4, WHITE, F("VScale")); this->Dot(6, 10, 11); this->Bracket(6, 21, 9); this->Text(6, 29, WHITE, F(""));
				this->Text(7, 4, WHITE, F("VA_GAIN")); this->Dot(7, 11, 10); this->Bracket(7, 21, 9); this->Text(7, 29, WHITE, F(""));
				this->Text(8, 4, WHITE, F("VB_GAIN")); this->Dot(8, 11, 10); this->Bracket(8, 21, 9); this->Text(8, 29, WHITE, F(""));
				this->Text(9, 4, WHITE, F("VC_GAIN")); this->Dot(9, 11, 10); this->Bracket(9, 21, 9); this->Text(9, 29, WHITE, F(""));
				this->Text(10, 4, WHITE, F("VA_OFFS")); this->Dot(10, 11, 10); this->Bracket(10, 21, 9); this->Text(10, 29, WHITE, F(""));
				this->Text(11, 4, WHITE, F("VB_OFFS")); this->Dot(11, 11, 10); this->Bracket(11, 21, 9); this->Text(11, 29, WHITE, F(""));
				this->Text(12, 4, WHITE, F("VC_OFFS")); this->Dot(12, 11, 10); this->Bracket(12, 21, 9); this->Text(12, 29, WHITE, F(""));
				this->Text(13, 4, WHITE, F("HPF_COEF_V")); this->Dot(13, 14, 7); this->Bracket(13, 21, 9); this->Text(13, 29, WHITE, F(""));
				this->Text(14, 4, WHITE, F("VA_RMS")); this->Dot(14, 10, 11); this->Bracket(14, 21, 9); this->Text(14, 29, WHITE, F("V"));
				this->Text(15, 4, WHITE, F("VB_RMS")); this->Dot(15, 10, 11); this->Bracket(15, 21, 9); this->Text(15, 29, WHITE, F("V"));
				this->Text(16, 4, WHITE, F("VC_RMS")); this->Dot(16, 10, 11); this->Bracket(16, 21, 9); this->Text(16, 29, WHITE, F("V"));
				this->Text(17, 4, WHITE, F("VT_RMS")); this->Dot(17, 10, 11); this->Bracket(17, 21, 9); this->Text(17, 29, WHITE, F("V"));
				this->Text(18, 4, WHITE, F("VA")); this->Dot(18, 6, 15); this->Bracket(18, 21, 9); this->Text(18, 29, WHITE, F("V"));
				this->Text(19, 4, WHITE, F("VB")); this->Dot(19, 6, 15); this->Bracket(19, 21, 9); this->Text(19, 29, WHITE, F("V"));
				this->Text(20, 4, WHITE, F("VC")); this->Dot(20, 6, 15); this->Bracket(20, 21, 9); this->Text(20, 29, WHITE, F("V"));
				this->Text(21, 4, WHITE, F("VA_FUND")); this->Dot(21, 11, 10); this->Bracket(21, 21, 9); this->Text(21, 29, WHITE, F("V"));
				this->Text(22, 4, WHITE, F("VB_FUND")); this->Dot(22, 11, 10); this->Bracket(22, 21, 9); this->Text(22, 29, WHITE, F("V"));
				this->Text(23, 4, WHITE, F("VC_FUND")); this->Dot(23, 11, 10); this->Bracket(23, 21, 9); this->Text(23, 29, WHITE, F("V"));
				this->Text(24, 4, WHITE, F("VA_HARM")); this->Dot(24, 11, 10); this->Bracket(24, 21, 9); this->Text(24, 29, WHITE, F("V"));
				this->Text(25, 4, WHITE, F("VB_HARM")); this->Dot(25, 11, 10); this->Bracket(25, 21, 9); this->Text(25, 29, WHITE, F("V"));
				this->Text(26, 4, WHITE, F("VC_HARM")); this->Dot(26, 11, 10); this->Bracket(26, 21, 9); this->Text(26, 29, WHITE, F("V"));

				// Draw Voltage
				this->Draw_Box(4, 33, 27, 63, "Current", 1, false, false);
				this->Text(6, 35, WHITE, F("IScale")); this->Dot(6, 41, 11); this->Bracket(6, 52, 9); this->Text(6, 60, WHITE, F(""));
				this->Text(7, 35, WHITE, F("IA_GAIN")); this->Dot(7, 42, 10); this->Bracket(7, 52, 9); this->Text(7, 60, WHITE, F(""));
				this->Text(8, 35, WHITE, F("IB_GAIN")); this->Dot(8, 42, 10); this->Bracket(8, 52, 9); this->Text(8, 60, WHITE, F(""));
				this->Text(9, 35, WHITE, F("IC_GAIN")); this->Dot(9, 42, 10); this->Bracket(9, 52, 9); this->Text(9, 60, WHITE, F(""));
				this->Text(10, 35, WHITE, F("IA_OFFS")); this->Dot(10, 42, 10); this->Bracket(10, 52, 9); this->Text(10, 60, WHITE, F(""));
				this->Text(11, 35, WHITE, F("IB_OFFS")); this->Dot(11, 42, 10); this->Bracket(11, 52, 9); this->Text(11, 60, WHITE, F(""));
				this->Text(12, 35, WHITE, F("IC_OFFS")); this->Dot(12, 42, 10); this->Bracket(12, 52, 9); this->Text(12, 60, WHITE, F(""));
				this->Text(13, 35, WHITE, F("HPF_COEF_I")); this->Dot(13, 45, 7); this->Bracket(13, 52, 9); this->Text(13, 29, WHITE, F(""));
				this->Text(14, 35, WHITE, F("IA_RMS")); this->Dot(14, 41, 11); this->Bracket(14, 52, 9); this->Text(14, 60, WHITE, F("A"));
				this->Text(15, 35, WHITE, F("IB_RMS")); this->Dot(15, 41, 11); this->Bracket(15, 52, 9); this->Text(15, 60, WHITE, F("A"));
				this->Text(16, 35, WHITE, F("IC_RMS")); this->Dot(16, 41, 11); this->Bracket(16, 52, 9); this->Text(16, 60, WHITE, F("A"));
				this->Text(17, 35, WHITE, F("IT_RMS")); this->Dot(17, 41, 11); this->Bracket(17, 52, 9); this->Text(17, 60, WHITE, F("A"));
				this->Text(18, 35, WHITE, F("IA")); this->Dot(18, 37, 15); this->Bracket(18, 52, 9); this->Text(18, 60, WHITE, F("A"));
				this->Text(19, 35, WHITE, F("IB")); this->Dot(19, 37, 15); this->Bracket(19, 52, 9); this->Text(19, 60, WHITE, F("A"));
				this->Text(20, 35, WHITE, F("IC")); this->Dot(20, 37, 15); this->Bracket(20, 52, 9); this->Text(20, 60, WHITE, F("A"));
				this->Text(21, 35, WHITE, F("IA_FUND")); this->Dot(21, 42, 10); this->Bracket(21, 52, 9); this->Text(21, 60, WHITE, F("A"));
				this->Text(22, 35, WHITE, F("IB_FUND")); this->Dot(22, 42, 10); this->Bracket(22, 52, 9); this->Text(22, 60, WHITE, F("A"));
				this->Text(23, 35, WHITE, F("IC_FUND")); this->Dot(23, 42, 10); this->Bracket(23, 52, 9); this->Text(23, 60, WHITE, F("A"));
				this->Text(24, 35, WHITE, F("IA_HARM")); this->Dot(24, 42, 10); this->Bracket(24, 52, 9); this->Text(24, 60, WHITE, F("A"));
				this->Text(25, 35, WHITE, F("IB_HARM")); this->Dot(25, 42, 10); this->Bracket(25, 52, 9); this->Text(25, 60, WHITE, F("A"));
				this->Text(26, 35, WHITE, F("IC_HARM")); this->Dot(26, 42, 10); this->Bracket(26, 52, 9); this->Text(26, 60, WHITE, F("A"));

				// Draw Frequency
				this->Draw_Box(28, 2, 33, 32, "Frequency", 1, false, false);
				this->Text(30, 4, WHITE, F("Frequency")); this->Dot(30, 13, 8); this->Bracket(30, 21, 9); this->Text(30, 28, WHITE, F("Hz"));
				this->Text(31, 4, WHITE, F("F_MIN")); this->Dot(31, 9, 12); this->Bracket(31, 21, 9); this->Text(31, 28, WHITE, F("Hz"));
				this->Text(32, 4, WHITE, F("F_MAX")); this->Dot(32, 9, 12); this->Bracket(32, 21, 9); this->Text(32, 28, WHITE, F("Hz"));

			}

			// PowerStat Terminal Batch
			void PowerStat(uint8_t _X = 1, uint8_t _Y = 1) {

				// Draw Main Box
				this->Draw_Box(_X, _Y, _X + 51, _Y + 119, "", 0, true, true);

				// Print Main Header Text
				this->Text(_X + 1, _Y + 52, WHITE, F("PowerStat V3"));

				// Header Titles
				this->Text(2, 3, WHITE, F("Counter : "));

				// Draw Hardware Diagnostic
				this->Print_Diagnostic(_X + 3, _Y + 1, _X + 11, _Y + 38);

				// Draw Detail Box
				this->Print_Detail(_X + 3, _Y + 39, _X + 11, _Y + 78);

				// Draw Battery Box
				this->Print_Battery(_X + 3, _Y + 79, _X + 11, _Y + 118);

				// Draw GSM Setup Box
				this->Print_GSM_Setup(_X + 12, _Y + 1, _X + 26, _Y + 38);

				// Draw GSM Connection Box
				this->Print_GSM_Connection(_X + 12, _Y + 39, _X + 26, _Y + 78);

				// Draw GSM Detail Box
				this->Print_GSM_Detail(_X + 12, _Y + 79, _X + 19, _Y + 118);

				// Draw GSM Connection Detail Box
				this->Print_GSM_Connection_Detail(_X + 20, _Y + 79, _X + 26, _Y + 118);

				// GSM Power Box
				this->Draw_Box(_X + 27, _Y + 1, _X + 29, _Y + 118, "", 0, false, false);

				// Power Box
				this->Print_Power_Detail(_X + 30, _Y + 1, _X + 37, _Y + 59);

				// Power Check
				this->Print_Power_Fault_Detail(_X + 30, _Y + 60, _X + 37, _Y + 118);

				// State Detail Box
				this->Print_State_Detail(_X + 38, _Y + 1, _X + 40, _Y + 118);

				// Data Box
				this->Draw_Box(42, 2, 49, 119, "JSON", 0, false, false);

				// Footer Dividers
				this->Text(50, 30, WHITE, F("┬"));
				this->Text(50, 62, WHITE, F("┬"));
				this->Text(50, 92, WHITE, F("┬"));
				this->Text(51, 30, WHITE, F("│"));
				this->Text(51, 62, WHITE, F("│"));
				this->Text(51, 92, WHITE, F("│"));
				this->Text(52, 30, WHITE, F("┴"));
				this->Text(52, 62, WHITE, F("┴"));
				this->Text(52, 92, WHITE, F("┴"));

				// Footer Texts
				this->Text(51, 3, WHITE, F("Interval :"));
				this->Text(51, 17, WHITE, F("min"));
				this->Text(51, 21, WHITE, F("/"));
				this->Text(51, 26, WHITE, F("min"));
				this->Text(51, 32, WHITE, F("Regression Limit : %"));
				this->Text(51, 64, WHITE, F("Pressure Slope : %"));
				this->Text(51, 94, WHITE, F("Pressure :"));
				this->Text(51, 113, WHITE, F("Bar"));

				// Fault Control Box
				this->Draw_Box(53, 1, 55, 120, "", 0, false, false);

				// Fault Texts
				this->Text(54, 3, WHITE, F("PL [ ] - Th [ ] - MP [ ] - RA [ ] - VC [ ] - FQC [ ] - PFC [ ] - VIMBC [ ] - IIMBC [ ] - PIC [ ] - PDC [ ]"));

			}
			void PowerStatV4(const uint8_t _X = 1, const uint8_t _Y = 1) {

				// Start VT100 Console
				this->Begin();

				// Draw Main Box
				this->Draw_Box(_X, _Y, _X + 47, _Y + 121, "", 0, true, true);

				// Print Main Header Text
				this->Text_Format(BRIGHT);
				this->Text(_X + 1, _Y + 54, WHITE, F("PowerStat V4"));
				this->Text_Format(RST);

				// Header Titles
				this->Text(_X + 1, _Y + 2, WHITE, F("Up Time :"));
				this->Text(_X + 1, _Y + 98, WHITE, F("Send Time (mS) :"));

				// Draw Hardware Diagnostic
				this->Print_Diagnostic(_X + 3, _Y + 1, _X + 11, _Y + 40);

				// Draw Detail Box
				this->Print_Detail(_X + 3, _Y + 41, _X + 11, _Y + 80);

				// Draw Battery Box
				this->Print_Battery(_X + 3, _Y + 81, _X + 11, _Y + 120);

				// Draw Command Box
				this->Draw_Box(_X + 12, _Y + 1, _X + 14, _Y + 40, "", 0, false, false);

				// Draw Description Box
				this->Draw_Box(_X + 12, _Y + 41, _X + 14, _Y + 80, "", 0, false, false);

				// Draw Status Box
				this->Draw_Box(_X + 12, _Y + 81, _X + 14, _Y + 120, "", 0, false, false);
				this->Text(_X + 13, _Y + 83, WHITE, "Device Status"); this->Dot(_X + 13, _Y + 96, 11); this->Bracket(_X + 13, _Y + 107, 11); this->Text(_X + 13, _Y + 108, GRAY, "0x");

				// Draw GSM Detail Box
				this->Print_GSM_Detail(_X + 15, _Y + 1, _X + 22, _Y + 40);

				// Draw GSM Connection Box
				this->Print_GSM_Connection_Detail(_X + 15, _Y + 41, _X + 22, _Y + 80);

				// Draw FOTA Detail Box
				this->Print_GSM_FOTA_Detail(_X + 15, _Y + 81, _X + 22, _Y + 120);

				// JSON Box
				this->Draw_Box(_X + 23, _Y + 1, _X + 31, _Y + 80, "JSON", 0, false, false);

				// Pressure Detail
				this->Print_Pressure_Detail(_X + 23, _Y + 81, _X + 31, _Y + 120);

				// Draw Voltage Box
				this->Draw_Box(_X + 32, _Y + 1, _X + 37, _Y + 40, "Voltage", 8, false, false);

				// Draw Current Box
				this->Draw_Box(_X + 32, _Y + 41, _X + 37, _Y + 80, "Current", 8, false, false);

				// Draw Power Box
				this->Draw_Box(_X + 32, _Y + 81, _X + 37, _Y + 120, "Power", 8, false, false);

				// Draw Status
				this->Draw_Box(_X + 38, _Y + 1, _X + 40, _Y + 120, "", 0, false, false);
				this->Text(_X + 39, _Y + 3, WHITE, "Status  :");

				// Draw Mask
				this->Draw_Box(_X + 41, _Y + 1, _X + 44, _Y + 120, "", 0, false, false);
				this->Text(_X + 42, _Y + 3, WHITE, "Publish :");
				this->Text(_X + 43, _Y + 3, WHITE, "Stop    :");

			}

			// FilterStat Terminal Batch
			void FilterStat(void) {

				// Draw Main Screen
				this->Draw_Box(1, 1, 49, 120, "", 0, true, 1);
				//Print_Box_Title(1,1,59,F("FilterStat V3"));

				// Header Titles
				this->Text(2, 3, WHITE, F("Up Time : "));

				// Draw Hardware Diagnostic
				this->Draw_Box(4, 2, 12, 39, "Hardware Diagnostic", 1, false, false);
				this->Text(5, 4, WHITE, F("I2C Multiplexer (0x70)")); this->Dot(5, 26, 6); this->Bracket(5, 32, 5);
				this->Text(6, 4, WHITE, F("I2C RTC (0x52)")); this->Dot(6, 18, 14); this->Bracket(6, 32, 5);
				this->Text(7, 4, WHITE, F("I2C Serial ID (0x50)")); this->Dot(7, 24, 8); this->Bracket(7, 32, 5);
				this->Text(8, 4, WHITE, F("I2C Temperature (0x40)")); this->Dot(8, 26, 6); this->Bracket(8, 32, 5);
				this->Text(9, 4, WHITE, F("I2C Battery Gauge (0x36)")); this->Dot(9, 28, 4); this->Bracket(9, 32, 5);
				this->Text(10, 4, WHITE, F("I2C Battery Charger (0x6B)")); this->Dot(10, 30, 2); this->Bracket(10, 32, 5);
				this->Text(11, 4, WHITE, F("SD Card Connection")); this->Dot(11, 22, 10); this->Bracket(11, 32, 5);

				// Draw Detail Box
				this->Draw_Box(4, 40, 12, 79, "Detail", 2, false, false);
				this->Text(5, 42, WHITE, F("Serial ID")); this->Dot(5, 51, 9); this->Bracket(5, 60, 17);
				this->Text(6, 42, WHITE, F("Firmware Version")); this->Dot(6, 58, 10); this->Bracket(6, 68, 9);
				this->Text(7, 42, WHITE, F("Hardware Version")); this->Dot(7, 58, 10); this->Bracket(7, 68, 9);
				this->Text(8, 42, WHITE, F("Module Temperature")); this->Dot(8, 60, 9); this->Bracket(8, 69, 8); this->Text(8, 76, WHITE, F("C"));
				this->Text(9, 42, WHITE, F("Module Humidity")); this->Dot(9, 57, 12); this->Bracket(9, 69, 8); this->Text(9, 76, WHITE, F("%"));

				// Draw Battery Box
				this->Draw_Box(4, 80, 12, 119, "Battery", 3, false, false);
				this->Text(5, 82, WHITE, F("Instant Voltage")); this->Dot(5, 97, 13); this->Bracket(5, 110, 7);  this->Text(5, 116, WHITE, F("V"));
				this->Text(6, 82, WHITE, F("Temperature")); this->Dot(6, 93, 16); this->Bracket(6, 109, 8); this->Text(6, 116, WHITE, F("C"));
				this->Text(7, 82, WHITE, F("Average Current")); this->Dot(7, 97, 10); this->Bracket(7, 107, 10); this->Text(7, 115, WHITE, F("mA"));
				this->Text(8, 82, WHITE, F("State of Charge")); this->Dot(8, 97, 14); this->Bracket(8, 111, 6); this->Text(8, 116, WHITE, F("%"));
				this->Text(9, 82, WHITE, F("Full Battery Capacity")); this->Dot(9, 103, 6); this->Bracket(9, 109, 8); this->Text(9, 115, WHITE, F("mA"));
				this->Text(10, 82, WHITE, F("Instant Battery Capacity")); this->Dot(10, 106, 3); this->Bracket(10, 109, 8); this->Text(10, 115, WHITE, F("mA"));
				this->Text(11, 82, WHITE, F("Cycle Count")); this->Dot(11, 93, 19); this->Bracket(11, 112, 5);

				// Draw GSM Setup Box
				this->Draw_Box(13, 2, 27, 39, "GSM Setup", 4, false, false);
				this->Text(14, 4, WHITE, F("ATE=0")); this->Dot(14, 9, 23); this->Bracket(14, 32, 5); this->Text(14, 33, YELLOW, F(" ** "));
				this->Text(15, 4, WHITE, F("AT+CMEE=1")); this->Dot(15, 13, 19); this->Bracket(15, 32, 5); this->Text(15, 33, YELLOW, F(" ** "));
				this->Text(16, 4, WHITE, F("AT+FCLASS=0")); this->Dot(16, 15, 17); this->Bracket(16, 32, 5); this->Text(16, 33, YELLOW, F(" ** "));
				this->Text(17, 4, WHITE, F("AT&K0")); this->Dot(17, 9, 23); this->Bracket(17, 32, 5); this->Text(17, 33, YELLOW, F(" ** "));
				this->Text(18, 4, WHITE, F("AT+CPIN?")); this->Dot(18, 12, 20); this->Bracket(18, 32, 5); this->Text(18, 33, YELLOW, F(" ** "));
				this->Text(19, 4, WHITE, F("AT+CGSN")); this->Dot(19, 11, 21); this->Bracket(19, 32, 5); this->Text(19, 33, YELLOW, F(" ** "));
				this->Text(20, 4, WHITE, F("AT+GSN")); this->Dot(20, 10, 22); this->Bracket(20, 32, 5); this->Text(20, 33, YELLOW, F(" ** "));
				this->Text(21, 4, WHITE, F("AT+CCID")); this->Dot(21, 11, 21); this->Bracket(21, 32, 5); this->Text(21, 33, YELLOW, F(" ** "));
				this->Text(22, 4, WHITE, F("AT+GMI")); this->Dot(22, 10, 22); this->Bracket(22, 32, 5); this->Text(22, 33, YELLOW, F(" ** "));
				this->Text(23, 4, WHITE, F("AT+GMM")); this->Dot(23, 10, 22); this->Bracket(23, 32, 5); this->Text(23, 33, YELLOW, F(" ** "));
				this->Text(24, 4, WHITE, F("AT+GMR")); this->Dot(24, 10, 22); this->Bracket(24, 32, 5); this->Text(24, 33, YELLOW, F(" ** "));
				this->Text(25, 4, WHITE, F("AT+SLED=2")); this->Dot(25, 13, 19); this->Bracket(25, 32, 5); this->Text(25, 33, YELLOW, F(" ** "));
				this->Text(26, 4, WHITE, F("AT#E2SLRI=50")); this->Dot(26, 16, 16); this->Bracket(26, 32, 5); this->Text(26, 33, YELLOW, F(" ** "));

				// GSM Connection Box
				this->Draw_Box(13, 40, 27, 79, "GSM Connection", 5, false, false);
				this->Text(14, 42, WHITE, F("AT#REGMODE=1")); this->Dot(14, 54, 18); this->Bracket(14, 72, 5); this->Text(14, 73, YELLOW, F(" ** "));
				this->Text(15, 42, WHITE, F("AT#TXMONMODE=1")); this->Dot(15, 56, 16); this->Bracket(15, 72, 5); this->Text(15, 73, YELLOW, F(" ** "));
				this->Text(16, 42, WHITE, F("AT+CREG=0")); this->Dot(16, 51, 21); this->Bracket(16, 72, 5); this->Text(16, 73, YELLOW, F(" ** "));
				this->Text(17, 42, WHITE, F("AT+CGREG=0")); this->Dot(17, 52, 20); this->Bracket(17, 72, 5); this->Text(17, 73, YELLOW, F(" ** "));
				this->Text(18, 42, WHITE, F("AT#SCFG=1,1,1500,90,600,50")); this->Dot(18, 68, 4); this->Bracket(18, 72, 5); this->Text(18, 73, YELLOW, F(" ** "));
				this->Text(19, 42, WHITE, F("AT#SCFG=2,1,1500,90,300,50")); this->Dot(19, 68, 4); this->Bracket(19, 72, 5); this->Text(19, 73, YELLOW, F(" ** "));
				this->Text(20, 42, WHITE, F("AT#SCFGEXT=2,1,0,1,0,0")); this->Dot(20, 64, 8); this->Bracket(20, 72, 5); this->Text(20, 73, YELLOW, F(" ** "));
				this->Text(21, 42, WHITE, F("AT+CGDCONT=1,\"IP\",\"mgbs\"")); this->Dot(21, 66, 6); this->Bracket(21, 72, 5); this->Text(21, 73, YELLOW, F(" ** "));
				this->Text(22, 42, WHITE, F("AT#SERVIFO")); this->Dot(22, 52, 20); this->Bracket(22, 72, 5); this->Text(22, 73, YELLOW, F(" ** "));
				this->Text(23, 42, WHITE, F("AT+CGACT=1,1")); this->Dot(23, 54, 18); this->Bracket(23, 72, 5); this->Text(23, 73, YELLOW, F(" ** "));
				this->Text(24, 42, WHITE, F("AT+CGPADDR=1")); this->Dot(24, 54, 18); this->Bracket(24, 72, 5); this->Text(24, 73, YELLOW, F(" ** "));
				this->Text(25, 42, WHITE, F("AT#HTTPCFG=1,\"*****\",80,0")); this->Dot(25, 67, 5); this->Bracket(25, 72, 5); this->Text(25, 73, YELLOW, F(" ** "));
				this->Text(26, 42, WHITE, F("AT#ICMP=1")); this->Dot(26, 51, 21); this->Bracket(26, 72, 5); this->Text(26, 73, YELLOW, F(" ** "));

				// GSM Detail Box
				this->Draw_Box(13, 80, 20, 119, "GSM Detail", 6, false, false);
				this->Text(14, 82, WHITE, F("Manufacturer")); this->Dot(14, 94, 21); this->Bracket(14, 115, 2);
				this->Text(15, 82, WHITE, F("Model")); this->Dot(15, 87, 28); this->Bracket(15, 115, 2);
				this->Text(16, 82, WHITE, F("Firmware")); this->Dot(16, 90, 16); this->Bracket(16, 106, 11);
				this->Text(17, 82, WHITE, F("IMEI")); this->Dot(17, 86, 15); this->Bracket(17, 101, 16);
				this->Text(18, 82, WHITE, F("Serial ID")); this->Dot(18, 91, 15); this->Bracket(18, 106, 11);
				this->Text(19, 82, WHITE, F("SIM ICCID")); this->Dot(19, 91, 6); this->Bracket(19, 97, 20);

				// Connection Box
				this->Draw_Box(21, 80, 27, 119, "Connection", 7, false, false);
				this->Text(22, 82, WHITE, F("GSM Connection Time")); this->Dot(22, 101, 11); this->Bracket(22, 112, 5);
				this->Text(23, 82, WHITE, F("RSSI Level")); this->Dot(23, 92, 22); this->Bracket(23, 114, 3);
				this->Text(24, 82, WHITE, F("GSM Operator")); this->Dot(24, 94, 17); this->Bracket(24, 111, 6);
				this->Text(25, 82, WHITE, F("IP Address")); this->Dot(25, 92, 9); this->Bracket(25, 101, 16);
				this->Text(26, 82, WHITE, F("Socket Listen Status")); this->Dot(26, 102, 5); this->Bracket(26, 107, 10);

				// Solenoid Box
				this->Draw_Box(31, 2, 36, 98, "", 0, false, false);
				this->Draw_Box(31, 99, 36, 119, "", 0, false, false);
				this->Horizontal_Divider(33,2,96,true);
				this->Horizontal_Divider(33,99,20,true);
				this->Vertical_Divider(33,8,3);
				this->Vertical_Divider(33,14,3);
				this->Vertical_Divider(33,20,3);
				this->Vertical_Divider(33,26,3);
				this->Vertical_Divider(33,32,3);
				this->Vertical_Divider(33,38,3);
				this->Vertical_Divider(33,44,3);
				this->Vertical_Divider(33,50,3);
				this->Vertical_Divider(33,56,3);
				this->Vertical_Divider(33,62,3);
				this->Vertical_Divider(33,68,3);
				this->Vertical_Divider(33,74,3);
				this->Vertical_Divider(33,80,3);
				this->Vertical_Divider(33,86,3);
				this->Vertical_Divider(33,92,3);
				this->Vertical_Divider(31,26,2);
				this->Vertical_Divider(31,50,2);
				this->Vertical_Divider(31,74,2);
				this->Text(32, 6, WHITE, F("Expander A [    ]"));
				this->Text(32, 30, WHITE, F("Expander B [    ]"));
				this->Text(32, 54, WHITE, F("Expander C [    ]"));
				this->Text(32, 77, WHITE, F("Expander D [    ]"));
				this->Text(34, 4, WHITE, F("S01"));
				this->Text(34, 10, WHITE, F("S02"));
				this->Text(34, 16, WHITE, F("S03"));
				this->Text(34, 22, WHITE, F("S04"));
				this->Text(34, 28, WHITE, F("S05"));
				this->Text(34, 34, WHITE, F("S06"));
				this->Text(34, 40, WHITE, F("S07"));
				this->Text(34, 46, WHITE, F("S08"));
				this->Text(34, 52, WHITE, F("S09"));
				this->Text(34, 58, WHITE, F("S10"));
				this->Text(34, 64, WHITE, F("S11"));
				this->Text(34, 70, WHITE, F("S12"));
				this->Text(34, 76, WHITE, F("S13"));
				this->Text(34, 82, WHITE, F("S14"));
				this->Text(34, 88, WHITE, F("S15"));
				this->Text(34, 94, WHITE, F("S16"));
				this->Text(32, 101, WHITE, F("P-Delta       Bar"));
				this->Text(34, 101, WHITE, F("P-In          Bar"));
				this->Text(35, 101, WHITE, F("P-Out         Bar"));

				// JSON Data Box
				this->Draw_Box(28, 2, 30, 119, "", 8, false, false);

				// Setting Detail
				this->Draw_Box(37, 2, 46, 98, "Data", 0, false, false);

				// Setting Section
				this->Draw_Box(37, 99, 46, 119, "Setting", 0, false, false);
				this->Text(39, 101, WHITE, F("Filter Count.[  ]"));
				this->Text(40, 101, WHITE, F("State.......[   ]"));
				this->Text(41, 101, WHITE, F("Stabilizer....[ ]"));
				this->Text(42, 101, WHITE, F("HydroCyclone..[ ]"));
				this->Text(43, 101, WHITE, F("Irrigation....[ ]"));
				//Text(44, 101, WHITE, F("IDLE..........[ ]"));

				this->Vertical_Divider(47,99,2);

			}

			// Telit xE910 Terminal Batch
			void Telit_xE910(void) {

				// Draw Main Box
				this->Draw_Box(1, 1, 30, 120, "", 0, true, true);

				// Print Main Header Text
				this->Text(2, 50, WHITE, F("PostOffice Test Procedure"));

				// Header Titles
				this->Text(2, 3, WHITE, F("Up Time : "));
				this->Text(2, 100, WHITE, F("Firmware : "));

				// Draw GSM Setup Box
				this->Draw_Box(4, 2, 24, 39, "GSM Setup", 1, false, false);
				for (uint8_t i = 5; i < 24; i++) {Dot(i, 4, 28); Bracket(i, 32, 5);}
			
				// Draw GSM Connection Box
				this->Draw_Box(4, 2, 24, 39, "GSM Connection", 2, false, false);
				for (uint8_t i = 5; i < 24; i++) {Dot(i, 42, 30); Bracket(i, 72, 5);}
				
				// Draw GSM Detail Box
				this->Print_GSM_Detail(4, 80, 11, 119);

				// Draw GSM Connection Detail Box
				this->Draw_Box(12, 80, 19, 119, "Connection", 4, false, false);
				for (uint8_t i = 13; i < 19; i++) Dot(i, 82, 30); 
				this->Text(13, 82, WHITE, F("GSM Connection Time")); Bracket(13, 112, 5);
				this->Text(14, 82, WHITE, F("Signal Level")); Bracket(14, 111, 6);
				this->Text(15, 82, WHITE, F("GSM Operator")); Bracket(15, 111, 6);
				this->Text(16, 82, WHITE, F("IP Address")); Bracket(16, 101, 16);
				this->Text(17, 82, WHITE, F("LAC")); Bracket(17, 112, 5);
				this->Text(18, 82, WHITE, F("Cell ID")); Bracket(18, 112, 5);

				// JSON Data Box
				this->Draw_Box(25, 2, 27, 79, "", 6, false, false);

				// Draw GSM Connection Detail Box
				this->Draw_Box(20, 80, 27, 119, "Firmware", 5, false, false);
				for (uint8_t i = 21; i < 27; i++) Dot(i, 82, 30); 

				this->Text(21, 82, WHITE, F("File ID")); Bracket(21, 110, 7);
				this->Text(22, 82, WHITE, F("Download Status")); Bracket(22, 112, 5);
				this->Text(23, 82, WHITE, F("FTP File Size")); Bracket(23, 109, 8);
				this->Text(24, 82, WHITE, F("SD File Size")); Bracket(24, 109, 8);
				this->Text(25, 82, WHITE, F("Download Percent")); Bracket(25, 111, 6); this->Text(25, 116, WHITE, F("%"));
				this->Text(26, 82, WHITE, F("Download Time")); Bracket(26, 108, 9); this->Text(26, 114, WHITE, F("Sec"));

			}

			// MAX78630 Voltmeter Terminal Batch
			void MAX78630_Voltmeter(void) {

				// Draw Main Screen
				this->Draw_Box(1, 1, 14, 84, "", 0, true, true);
				//Print_Box_Title(1,1,42,F("MAX78630 Volt Meter"));

				// Draw Voltage
				this->Draw_Box(5, 3, 10, 28, "Phase R", 1, false, false);
				this->Draw_Box(5, 30, 10, 55, "Phase S", 2, false, false);
				this->Draw_Box(5, 57, 10, 82, "Phase T", 3, false, false);

				this->Text(7, 5, WHITE, F("VA_RMS......[       V]"));
				this->Text(8, 5, WHITE, F("VA_MIN......[       V]"));
				this->Text(9, 5, WHITE, F("VA_MAX......[       V]"));

				this->Text(7, 32, WHITE, F("VB_RMS......[       V]"));
				this->Text(8, 32, WHITE, F("VB_MIN......[       V]"));
				this->Text(9, 32, WHITE, F("VB_MAX......[       V]"));

				this->Text(7, 59, WHITE, F("VC_RMS......[       V]"));
				this->Text(8, 59, WHITE, F("VC_MIN......[       V]"));
				this->Text(9, 59, WHITE, F("VC_MAX......[       V]"));

			}

			// HDC2010 TH Meter
			void HDC2010_TH_Meter(void) {

					// Draw Main Screen
					this->Draw_Box(1, 1, 8, 38, "HDC2010 T/H Sensor", 1, false, true);
					this->Text(3, 3, WHITE, F("Temperature..........[         C ]"));
					this->Text(4, 3, WHITE, F("Humidity.............[         % ]"));
					this->Text(7, 3, WHITE, F("Function Time............[    ms ]"));
				
				}

			// Analog Pressure Meter
			void Analog_Pressure_Meter(void) {

					// Draw Main Screen
					this->Draw_Box(1, 1, 8, 38, "Analog P Sensor", 1, false, true);
					this->Text(3, 3, WHITE, F("Pressure...........[         Bar ]"));
					this->Text(4, 3, WHITE, F("Deviation..............[         ]"));
					this->Text(7, 3, WHITE, F("Function Time............[    ms ]"));

				}

			// Full_Energy_Analayzer
			void Full_Energy_Analayzer(void) {

					// Draw Main Screen
					this->Draw_Box(1, 1, 41, 160, "", 0, true, false);
					this->Text(2, 68, WHITE, F("MAX78630 Energy Analyzer"));

					// Draw Voltage
					this->Draw_Box(5, 2, 13, 77, "Voltage", 1, false, false);
					this->Text(7, 4, WHITE, F("────────┬──────────┬──────────┬──────────┬──────────┬─────────┬─────────"));
					this->Text(8, 12, WHITE, F("│          │          │          │          │         │"));
					this->Text(9, 12, WHITE, F("│          │          │          │          │         │"));
					this->Text(10, 12, WHITE, F("│          │          │          │          │         │"));
					this->Text(11, 12, WHITE, F("│          │          │          │          │         │"));
					this->Text(12, 4, WHITE, F("────────┴──────────┴──────────┴──────────┴──────────┴─────────┴─────────"));
					this->Text(8, 4, WHITE, F("Phase R"));
					this->Text(9, 4, WHITE, F("Phase S"));
					this->Text(10, 4, WHITE, F("Phase T"));
					this->Text(11, 4, WHITE, F("Average"));
					this->Text(6, 15, WHITE, F("Instant"));
					this->Text(6, 28, WHITE, F("RMS"));
					this->Text(6, 37, WHITE, F("Fund."));
					this->Text(6, 48, WHITE, F("Harm."));
					this->Text(6, 59, WHITE, F("Offset"));
					this->Text(6, 70, WHITE, F("Gain"));
					this->Text(11, 14, WHITE, F("--------"));
					this->Text(11, 36, WHITE, F("--------"));
					this->Text(11, 47, WHITE, F("--------"));
					this->Text(11, 58, WHITE, F("-------"));
					this->Text(11, 68, WHITE, F("-------"));

					// Draw Current
					this->Draw_Box(5, 78, 13, 159, "Current", 2, false, false);
					this->Text(7, 80, WHITE, F("────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────"));
					this->Text(8, 88, WHITE, F("│         │         │         │         │         │         │"));
					this->Text(9, 88, WHITE, F("│         │         │         │         │         │         │"));
					this->Text(10, 88, WHITE, F("│         │         │         │         │         │         │"));
					this->Text(11, 88, WHITE, F("│         │         │         │         │         │         │"));
					this->Text(12, 80, WHITE, F("────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────"));
					this->Text(8, 80, WHITE, F("Phase R"));
					this->Text(9, 80, WHITE, F("Phase S"));
					this->Text(10, 80, WHITE, F("Phase T"));
					this->Text(11, 80, WHITE, F("Average"));
					this->Text(6, 90, WHITE, F("Instant"));
					this->Text(6, 101, WHITE, F("Peak"));
					this->Text(6, 112, WHITE, F("RMS"));
					this->Text(6, 121, WHITE, F("Fund."));
					this->Text(6, 131, WHITE, F("Harm."));
					this->Text(6, 141, WHITE, F("Offset"));
					this->Text(6, 152, WHITE, F("Gain"));
					this->Text(11, 90, WHITE, F("-------"));
					this->Text(11, 100, WHITE, F("-------"));
					this->Text(11, 120, WHITE, F("-------"));
					this->Text(11, 130, WHITE, F("-------"));
					this->Text(11, 140, WHITE, F("-------"));
					this->Text(11, 150, WHITE, F("-------"));

					// Draw Power
					this->Draw_Box(15, 2, 22, 132, "Power", 3, false, false);
					this->Text(17, 4, WHITE, F("────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬─────────┬─────────┬──────────"));
					this->Text(18, 12, WHITE, F("│          │          │          │          │          │          │          │          │         │         │"));
					this->Text(19, 12, WHITE, F("│          │          │          │          │          │          │          │          │         │         │"));
					this->Text(20, 12, WHITE, F("│          │          │          │          │          │          │          │          │         │         │"));
					this->Text(21, 12, WHITE, F("│          │          │          │          │          │          │          │          │         │         │"));
					this->Text(18, 4, WHITE, F("Phase R"));
					this->Text(19, 4, WHITE, F("Phase S"));
					this->Text(20, 4, WHITE, F("Phase T"));
					this->Text(21, 4, WHITE, F("Average"));
					this->Text(16, 15, WHITE, F("Active"));
					this->Text(16, 25, WHITE, F("ReActive"));
					this->Text(16, 36, WHITE, F("Apparent"));
					this->Text(16, 49, WHITE, F("Harm."));
					this->Text(16, 60, WHITE, F("Fund."));
					this->Text(16, 69, WHITE, F("Harm.R."));
					this->Text(16, 80, WHITE, F("Fund.R."));
					this->Text(16, 92, WHITE, F("VAFUND"));
					this->Text(16, 102, WHITE, F("Power F."));
					this->Text(16, 112, WHITE, F("P. Offs."));
					this->Text(16, 123, WHITE, F("Q. Offs."));
					this->Text(21, 47, WHITE, F("--------"));
					this->Text(21, 58, WHITE, F("--------"));
					this->Text(21, 69, WHITE, F("--------"));
					this->Text(21, 80, WHITE, F("--------"));
					this->Text(21, 91, WHITE, F("--------"));
					this->Text(21, 113, WHITE, F("-----"));
					this->Text(21, 124, WHITE, F("-----"));

					// Draw Device
					this->Draw_Box(15, 133, 22, 159, "Device", 4, false, false);
					this->Text(16, 135, WHITE, F("Device Addres :"));
					this->Text(17, 135, WHITE, F("Firmware      :"));
					this->Text(18, 135, WHITE, F("Baud          :"));
					this->Text(19, 135, WHITE, F("Temperature   :"));
					this->Text(20, 135, WHITE, F("VScale        :"));
					this->Text(21, 135, WHITE, F("IScale        :"));

					// Draw Min/Max Mask
					this->Draw_Box(24, 2, 29, 104, "Min/Max Mask", 5, false, false);
					this->Text(26, 4, WHITE, F("──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────"));
					this->Text(27, 14, WHITE, F("│          │          │          │          │          │          │          │"));
					this->Text(28, 14, WHITE, F("│          │          │          │          │          │          │          │"));
					this->Text(27, 4, WHITE, F("Minimum"));
					this->Text(28, 4, WHITE, F("Maximum"));
					this->Text(25, 17, WHITE, F("Mask-0"));
					this->Text(25, 28, WHITE, F("Mask-1"));
					this->Text(25, 39, WHITE, F("Mask-2"));
					this->Text(25, 50, WHITE, F("Mask-3"));
					this->Text(25, 61, WHITE, F("Mask-4"));
					this->Text(25, 72, WHITE, F("Mask-5"));
					this->Text(25, 83, WHITE, F("Mask-6"));
					this->Text(25, 94, WHITE, F("Mask-7"));

					// Draw Other
					this->Draw_Box(24, 105, 29, 123, "Other", 7, false, false);
					this->Text(25, 107, WHITE, F("STICKY......[ ]"));
					this->Text(26, 107, WHITE, F("FREQ....[     ]"));
					this->Text(27, 107, WHITE, F("BUCKET_L [    ]"));
					this->Text(28, 107, WHITE, F("BUCKET_H [    ]"));

					// Draw Status Limits
					this->Draw_Box(30, 2, 34, 123, "Status Limits", 8, false, false);
					this->Text(32, 4, WHITE, F("────────┬───────────┬───────────┬──────────┬──────────┬──────────┬──────────┬────────┬───────┬───────┬────────┬───────"));
					this->Text(33, 12, WHITE, F("│           │           │          │          │          │          │        │       │       │        │"));
					this->Text(33, 4, WHITE, F("Limit"));
					this->Text(31, 14, WHITE, F("V_IMB_MAX"));
					this->Text(31, 26, WHITE, F("I_IMB_MAX"));
					this->Text(31, 38, WHITE, F("VRMS_MIN"));
					this->Text(31, 49, WHITE, F("VRMS_MAX"));
					this->Text(31, 60, WHITE, F("VSAG_LIM"));
					this->Text(31, 71, WHITE, F("IRMS_MAX"));
					this->Text(31, 82, WHITE, F("PF_MIN"));
					this->Text(31, 91, WHITE, F("T_MIN"));
					this->Text(31, 99, WHITE, F("T_MAX"));
					this->Text(31, 107, WHITE, F("F_MIN"));
					this->Text(31, 116, WHITE, F("F_MAX"));

					// Draw Status
					this->Draw_Box(24, 124, 34, 159, "Status", 9, false, false);
					this->Text(25, 126, WHITE, F("OV_VRMSA....[ ]"));
					this->Text(26, 126, WHITE, F("UN_VRMSA....[ ]"));
					this->Text(27, 126, WHITE, F("OV_VRMSB....[ ]"));
					this->Text(28, 126, WHITE, F("UN_VRMSB....[ ]"));
					this->Text(29, 126, WHITE, F("OV_VRMSC....[ ]"));
					this->Text(30, 126, WHITE, F("UN_VRMSC....[ ]"));
					this->Text(31, 126, WHITE, F("OV_IRMSA....[ ]"));
					this->Text(32, 126, WHITE, F("OV_IRMSB....[ ]"));
					this->Text(33, 126, WHITE, F("OV_IRMSC....[ ]"));
					this->Text(25, 144, WHITE, F("OV_FREQ....[ ]"));
					this->Text(26, 144, WHITE, F("UN_FREQ....[ ]"));
					this->Text(27, 144, WHITE, F("UN_PFA.....[ ]"));
					this->Text(28, 144, WHITE, F("UN_PFB.....[ ]"));
					this->Text(29, 144, WHITE, F("UN_PFC.....[ ]"));
					this->Text(30, 144, WHITE, F("VA_SAG.....[ ]"));
					this->Text(31, 144, WHITE, F("VB_SAG.....[ ]"));
					this->Text(32, 144, WHITE, F("VC_SAG.....[ ]"));
					this->Text(33, 144, WHITE, F("V_IMBAL....[ ]"));

					// Draw Energy
					this->Draw_Box(36, 2, 40, 159, "Energy Counter", 10, false, false);
					this->Text(38, 4, WHITE, F("────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬────────────┬────────────┬────────────┬────────────┬────────────┬─────────────"));
					this->Text(39, 12, WHITE, F("│          │          │          │          │          │          │            │            │            │            │            │"));
					this->Text(37, 15, WHITE, F("WHA_POS"));
					this->Text(37, 26, WHITE, F("WHA_NEG"));
					this->Text(37, 37, WHITE, F("WHB_POS"));
					this->Text(37, 48, WHITE, F("WHB_NEG"));
					this->Text(37, 59, WHITE, F("WHC_POS"));
					this->Text(37, 70, WHITE, F("WHC_NEG"));
					this->Text(37, 81, WHITE, F("VARHA_POS"));
					this->Text(37, 94, WHITE, F("VARHA_NEG"));
					this->Text(37, 107, WHITE, F("VARHB_POS"));
					this->Text(37, 120, WHITE, F("VARHB_NEG"));
					this->Text(37, 133, WHITE, F("VARHC_POS"));
					this->Text(37, 146, WHITE, F("VARHC_NEG"));
				
				}

	};

#endif /* defined(__Console__) */