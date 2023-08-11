#ifndef __Console__
#define __Console__

	// Define Arduino Library
	#ifndef __Arduino__
		#include <Arduino.h>
	#endif

	// Include Definition File
	#include "Definition.h"

	// Include Config File
	#include "Config.h"

	// Console Class
	class Console {

		private:

			// Stream Variable
			Stream * Console_Serial;

			// Variable Declaration
			struct Struct_Console_Buffer {

				// Text Color
				uint8_t Text_Color = 255;

				// Background Color
				uint8_t Background_Color = 255;

				// Text Format
				uint8_t Text_Format = 255;

			} Buffer;

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
			void Box(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2, String _Text = "", const uint8_t _Number = 0, const bool _Header = false, const bool _Footer = false) {

				// Set Text Color
				this->Text_Color(WHITE);

				// Set Text Format
				this->Text_Format(DIM);

				// Print Corners
				this->Set_Cursor(_X1, _Y1); Console_Serial->print(F("┌"));
				this->Set_Cursor(_X2, _Y1); Console_Serial->print(F("└"));
				this->Set_Cursor(_X1, _Y2); Console_Serial->print(F("┐"));
				this->Set_Cursor(_X2, _Y2); Console_Serial->print(F("┘"));

				// Print Lines
				for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {
					
					this->Set_Cursor(i, _Y1); Console_Serial->print(F("│"));
					this->Set_Cursor(i, _Y2); Console_Serial->print(F("│"));

				}
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
					
					this->Set_Cursor(_X1, i); Console_Serial->print(F("─"));
					this->Set_Cursor(_X2, i); Console_Serial->print(F("─"));
					
				}

				// Print Header
				this->Text_Color(YELLOW); this->Set_Cursor(_X1, _Y1 + 2); Console_Serial->print(_Text);

				// Print Header Number
				if (_Number != 0) {
					this->Text_Color(WHITE); this->Set_Cursor(_X1, _Y2 - 5); Console_Serial->print(F("[  ]"));
					if (_Number < 10) {
						this->Text_Color(YELLOW); this->Set_Cursor(_X1, _Y2 - 4); Console_Serial->print(F("0"));
						this->Text_Color(YELLOW); this->Set_Cursor(_X1, _Y2 - 3); Console_Serial->print(_Number);
					} else {
						this->Text_Color(YELLOW); this->Set_Cursor(_X1, _Y2 - 4); Console_Serial->print(_Number);
					}
				}

				// Draw Header
				if (_Header) {

					// Set Text Color
					this->Text_Color(WHITE);

					// Print Corners
					this->Set_Cursor(_X1 + 2, _Y1); Console_Serial->print(F("├"));
					this->Set_Cursor(_X1 + 2, _Y2); Console_Serial->print(F("┤"));

					// Print Lines
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
						
						this->Set_Cursor(_X1 + 2, i); Console_Serial->print(F("─"));
						
					}

				}
				
				// Draw Footer			
				if (_Footer) {

					// Set Text Color
					this->Text_Color(WHITE);

					// Print Corners
					this->Set_Cursor(_X2 - 2, _Y1); Console_Serial->print(F("├"));
					this->Set_Cursor(_X2 - 2, _Y2); Console_Serial->print(F("┤"));

					// Print Lines
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
						
						this->Set_Cursor(_X2 - 2, i); Console_Serial->print(F("─"));
						
					}

				}

			}

			// Dot Print Function.
			void Dot(const uint8_t _X, const uint8_t _Y, const uint8_t _Count) {

				// Print Dots
				for (uint8_t i = 0; i < _Count; i++) {

					// Print Dot
					this->Text(_X, _Y + i, GRAY, F("."));

				}

			}

			// Bracket Place Holder Function.
			void Bracket(const uint8_t _X, const uint8_t _Y, const uint8_t _Space) {

				// Print Bracket Start
				this->Text(_X, _Y, WHITE, F("["));

				// Print Bracket Left
				this->Text(_X, _Y + _Space, WHITE, F("]"));

			}

			// Horizontal Line Divider Function.
			void Divider(const bool _Type, const uint8_t _X, const uint8_t _Y, const uint8_t _Length, const bool _End = false) {

				//Set Color
				this->Text_Color(WHITE);

				// Control Horizontal divider type
				if (_Type == HORIZONTAL) {

					// Print Corners
					if (_End) {

						// Print Corners
						this->Set_Cursor(_X, _Y); Console_Serial->print(F("├"));
						this->Set_Cursor(_X, _Y + _Length); Console_Serial->print(F("┤"));

					}

					// Print Line
					for (uint8_t i = _Y + 1; i <= _Y + _Length - 1; i++) {this->Set_Cursor(_X, i); Console_Serial->print(F("─"));}

				}

				// Control Vertical divider type
				if (_Type == VERTICAL) {

					// Print Corners
					if (_End) {

						// Print Corners
						this->Set_Cursor(_X, _Y); Console_Serial->print(F("┬"));
						this->Set_Cursor(_X + _Length, _Y); Console_Serial->print(F("┴"));

					}

					// Print Lines
					for (uint8_t i = _X + 1; i <= _X + _Length - 1; i++) {this->Set_Cursor(i, _Y); Console_Serial->print(F("│"));}

				}

			}

			// Set Text Color Function.
			void Text_Color(uint8_t _Color) {

				// Control for Buffer
				if (_Color != this->Buffer.Text_Color) {

					// Set Text Color.
					Console_Serial->print(F("\e["));
					Console_Serial->print(_Color);
					Console_Serial->write('m');

					// Update Buffer Variable
					this->Buffer.Text_Color = _Color;

				}

			}

			// Set Back Ground Color Function.
			void Background_Color(uint8_t _Color) {

				// Control for Buffer
				if (_Color != this->Buffer.Background_Color) {

					// Set Back Ground Color.
					Console_Serial->print(F("\e["));
					Console_Serial->print(_Color + 10);
					Console_Serial->write('m');

					// Update Buffer Variable
					this->Buffer.Background_Color = _Color;

				}

			}

			// Set Text Format Function
			void Text_Format(const uint8_t _Format) {

				// Control for Buffer
				if (_Format != this->Buffer.Text_Format) {

					// Set Text Format
					Console_Serial->print(F("\e["));
					Console_Serial->print(_Format);
					Console_Serial->write('m');

					// Update Buffer Variable
					this->Buffer.Text_Format = _Format;

				}

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

		public:

			// Construct a new Console object
			Console(Stream &_Serial) {

				// Set Serial
				this->Console_Serial = &_Serial;

			}

			// Begin Console.
			void Begin(void) {

				// Cursor Off
				this->Cursor(false);

				// Clear Screen
				this->Clear(SCREEN);

				// Set Text Color
				this->Text_Color(WHITE);

				// Reset Delay
				delay(5);

			}

			// Terminal Beep Sound Function.
			void Beep(void) {

				// Beep Terminal.
				Console_Serial->print(F("\x07"));

			}

			// Print Text to Specified Position and Color.
			void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, String _Value) {

				// Set Text Cursor Position
				Set_Cursor(_X, _Y); 

				// Set Text Color
				Text_Color(_Color); 

				// Print Text			
				Console_Serial->print(String(_Value));

			}

			// OK Decide Function.
			void OK(const bool _Result, const uint8_t _X, const uint8_t _Y) {

				// Print Command State
				if (_Result) {

					// Success
					this->Text(_X, _Y, GREEN, F(" OK "));

				} else {

					// Fail
					this->Text(_X, _Y, RED, F("FAIL"));

				}
		
			}

			// GSM Command Prcocess
			void AT_Command(uint8_t _X, uint8_t _Y, String _Command) {

				// Set Text Cursor Position
				this->Set_Cursor(_X, _Y);

				// Clear Line
				for (uint8_t i = 0; i < 30; i++) Console_Serial->print(F(" "));

				// Print Dot
				this->Text(_X, _Y, GRAY, F(".............................."));

				// Print Command
				this->Text(_X, _Y, WHITE, _Command);

				// Print Response Wait Dot
				this->Text(_X, _Y + 31, BLUE, F(" .. "));
		
			}

			/* Console Device Functions */

			// PowerStat Batchs
			#if defined(PowerStat)

				// Hardware Diagnostic Box Print Function.
				void Diagnostic(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw Hardware Diagnostic Box
					this->Box(_X1, _Y1, _X2, _Y2, "Hardware Diagnostic", 1, false, false);

					// Print Text
					this->Text(_X1 + 1, _Y1 + 2, WHITE, F("I2C Multiplexer (0x70)")); 		this->Dot(_X1 + 1, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24));	this->Bracket(_X1 + 1, _Y2 - 7, 5);
					this->Text(_X1 + 2, _Y1 + 2, WHITE, F("I2C RTC (0x52)")); 				this->Dot(_X1 + 2, _Y1 + 16, (_Y2 - 7) - (_Y1 + 16)); 	this->Bracket(_X1 + 2, _Y2 - 7, 5);
					this->Text(_X1 + 3, _Y1 + 2, WHITE, F("I2C Serial ID (0x50)")); 		this->Dot(_X1 + 3, _Y1 + 22, (_Y2 - 7) - (_Y1 + 22));	this->Bracket(_X1 + 3, _Y2 - 7, 5);
					this->Text(_X1 + 4, _Y1 + 2, WHITE, F("I2C Temperature (0x40)")); 		this->Dot(_X1 + 4, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24));	this->Bracket(_X1 + 4, _Y2 - 7, 5);
					this->Text(_X1 + 5, _Y1 + 2, WHITE, F("I2C Battery Gauge (0x36)")); 	this->Dot(_X1 + 5, _Y1 + 26, (_Y2 - 7) - (_Y1 + 26));	this->Bracket(_X1 + 5, _Y2 - 7, 5);
					this->Text(_X1 + 6, _Y1 + 2, WHITE, F("I2C Battery Charger (0x6B)")); 	this->Dot(_X1 + 6, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28));	this->Bracket(_X1 + 6, _Y2 - 7, 5);
					this->Text(_X1 + 7, _Y1 + 2, WHITE, F("SD Card Connection")); 			this->Dot(_X1 + 7, _Y1 + 20, (_Y2 - 7) - (_Y1 + 20)); 	this->Bracket(_X1 + 7, _Y2 - 7, 5);

				}

				// Detail Box Print Function.
				void Device_Detail(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw Hardware Diagnostic Box
					this->Box(_X1, _Y1, _X2, _Y2, "Hardware Detail", 2, false, false);

					// Print Text
					this->Text(_X1 + 1, _Y1 + 2, WHITE, F("Serial ID")); 				this->Dot(_X1 + 1, _Y1 + 11, (_Y2 - 19) - (_Y1 + 11)); 	this->Bracket(_X1 + 1, _Y2 - 19, 17);
					this->Text(_X1 + 2, _Y1 + 2, WHITE, F("Firmware Version")); 		this->Dot(_X1 + 2, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	this->Bracket(_X1 + 2, _Y2 - 11, 9);
					this->Text(_X1 + 3, _Y1 + 2, WHITE, F("Hardware Version")); 		this->Dot(_X1 + 3, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	this->Bracket(_X1 + 3, _Y2 - 11, 9);
					this->Text(_X1 + 4, _Y1 + 2, WHITE, F("Module Temperature")); 		this->Dot(_X1 + 4, _Y1 + 20, (_Y2 - 10) - (_Y1 + 20)); 	this->Bracket(_X1 + 4, _Y2 - 10, 8); this->Text(_X1 + 4, _Y2 - 3, WHITE, F("C"));
					this->Text(_X1 + 5, _Y1 + 2, WHITE, F("Module Humidity")); 			this->Dot(_X1 + 5, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	this->Bracket(_X1 + 5, _Y2 - 10, 8); this->Text(_X1 + 5, _Y2 - 3, WHITE, F("%"));
					this->Text(_X1 + 6, _Y1 + 2, WHITE, F("Online Send Interval"));		this->Dot(_X1 + 6, _Y1 + 22, (_Y2 - 10) - (_Y1 + 22)); 	this->Bracket(_X1 + 6, _Y2 - 10, 8); this->Text(_X1 + 6, _Y2 - 5, WHITE, F("Min"));
					this->Text(_X1 + 7, _Y1 + 2, WHITE, F("Offline Send Interval")); 	this->Dot(_X1 + 7, _Y1 + 23, (_Y2 - 10) - (_Y1 + 23)); 	this->Bracket(_X1 + 7, _Y2 - 10, 8); this->Text(_X1 + 7, _Y2 - 5, WHITE, F("Min"));

				}
				
				// Battery Print Function.
				void Battery(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw Hardware Diagnostic Box
					this->Box(_X1, _Y1, _X2, _Y2, "Battery", 3, false, false);

					// Print Text
					this->Text(_X1 + 1, _Y1 + 2, WHITE, F("Instant Voltage")); 			this->Dot(_X1 + 1, _Y1 + 17, (_Y2 - 9) - (_Y1 + 17)); 	this->Bracket(_X1 + 1, _Y2 - 9, 7);		this->Text(_X1 + 1, _Y2 - 3, WHITE, F("V"));
					this->Text(_X1 + 2, _Y1 + 2, WHITE, F("Temperature")); 				this->Dot(_X1 + 2, _Y1 + 13, (_Y2 - 10) - (_Y1 + 13)); 	this->Bracket(_X1 + 2, _Y2 - 10, 8);	this->Text(_X1 + 2, _Y2 - 3, WHITE, F("C"));
					this->Text(_X1 + 3, _Y1 + 2, WHITE, F("Average Current")); 			this->Dot(_X1 + 3, _Y1 + 17, (_Y2 - 13) - (_Y1 + 17)); 	this->Bracket(_X1 + 3, _Y2 - 13, 11);	this->Text(_X1 + 3, _Y2 - 4, WHITE, F("mA"));
					this->Text(_X1 + 4, _Y1 + 2, WHITE, F("State of Charge")); 			this->Dot(_X1 + 4, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	this->Bracket(_X1 + 4, _Y2 - 10, 8);	this->Text(_X1 + 4, _Y2 - 3, WHITE, F("%"));
					this->Text(_X1 + 5, _Y1 + 2, WHITE, F("Full Battery Capacity")); 	this->Dot(_X1 + 5, _Y1 + 23, (_Y2 - 10) - (_Y1 + 23)); 	this->Bracket(_X1 + 5, _Y2 - 10, 8);	this->Text(_X1 + 5, _Y2 - 4, WHITE, F("mA"));
					this->Text(_X1 + 6, _Y1 + 2, WHITE, F("Instant Battery Capacity"));	this->Dot(_X1 + 6, _Y1 + 26, (_Y2 - 10) - (_Y1 + 26)); 	this->Bracket(_X1 + 6, _Y2 - 10, 8);	this->Text(_X1 + 6, _Y2 - 4, WHITE, F("mA"));
					this->Text(_X1 + 7, _Y1 + 2, WHITE, F("Charge State")); 			this->Dot(_X1 + 7, _Y1 + 14, (_Y2 - 15) - (_Y1 + 14)); 	this->Bracket(_X1 + 7, _Y2 - 15, 13);

				}

				// GSM Detail Function.
				void GSM_Hardware(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					this->Box(_X1, _Y1, _X2, _Y2, "GSM Detail", 4, false, false);

					// Print Text	
					this->Text(_X1 + 1, _Y1 + 2, WHITE, F("Manufacturer"));	this->Dot(_X1 + 1, _Y1 + 14, (_Y2 - 4) - (_Y1 + 14)); 	this->Bracket(_X1 + 1, _Y2 - 4, 2);
					this->Text(_X1 + 2, _Y1 + 2, WHITE, F("Model"));		this->Dot(_X1 + 2, _Y1 + 7, (_Y2 - 4) - (_Y1 + 7)); 	this->Bracket(_X1 + 2, _Y2 - 4, 2);
					this->Text(_X1 + 3, _Y1 + 2, WHITE, F("Firmware"));		this->Dot(_X1 + 3, _Y1 + 10, (_Y2 - 12) - (_Y1 + 10)); 	this->Bracket(_X1 + 3, _Y2 - 12, 10);
					this->Text(_X1 + 4, _Y1 + 2, WHITE, F("IMEI"));			this->Dot(_X1 + 4, _Y1 + 6, (_Y2 - 18) - (_Y1 + 6)); 	this->Bracket(_X1 + 4, _Y2 - 18, 16);
					this->Text(_X1 + 5, _Y1 + 2, WHITE, F("Serial ID"));	this->Dot(_X1 + 5, _Y1 + 11, (_Y2 - 13) - (_Y1 + 11)); 	this->Bracket(_X1 + 5, _Y2 - 13, 11);
					this->Text(_X1 + 6, _Y1 + 2, WHITE, F("ICCID"));		this->Dot(_X1 + 6, _Y1 + 7, (_Y2 - 22) - (_Y1 + 7)); 	this->Bracket(_X1 + 6, _Y2 - 22, 20);

				}

				// GSM Connection Detail Function.
				void GSM_Operator(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					this->Box(_X1, _Y1, _X2, _Y2, "GSM Connection", 5, false, false);

					// Print Text	
					this->Text(_X1 + 1, _Y1 + 2, WHITE, F("GSM Connection Time"));	this->Dot(_X1 + 1, _Y1 + 21, (_Y2 - 7) - (_Y1 + 21)); 	this->Bracket(_X1 + 1, _Y2 - 7, 5);
					this->Text(_X1 + 2, _Y1 + 2, WHITE, F("Signal Level"));			this->Dot(_X1 + 2, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	this->Bracket(_X1 + 2, _Y2 - 8, 6);
					this->Text(_X1 + 3, _Y1 + 2, WHITE, F("GSM Operator"));			this->Dot(_X1 + 3, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	this->Bracket(_X1 + 3, _Y2 - 8, 6);
					this->Text(_X1 + 4, _Y1 + 2, WHITE, F("IP Address"));			this->Dot(_X1 + 4, _Y1 + 12, (_Y2 - 18) - (_Y1 + 12)); 	this->Bracket(_X1 + 4, _Y2 - 18, 16);
					this->Text(_X1 + 5, _Y1 + 2, WHITE, F("LAC"));					this->Dot(_X1 + 5, _Y1 + 5, (_Y2 - 7) - (_Y1 + 5)); 	this->Bracket(_X1 + 5, _Y2 - 7, 5);
					this->Text(_X1 + 6, _Y1 + 2, WHITE, F("CELL ID"));				this->Dot(_X1 + 6, _Y1 + 9, (_Y2 - 7) - (_Y1 + 9)); 	this->Bracket(_X1 + 6, _Y2 - 7, 5);

				}

				// GSM FOTA
				void GSM_FOTA_Detail(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					this->Box(_X1, _Y1, _X2, _Y2, "FOTA", 6, false, false);

					// Print Text	
					this->Text(_X1 + 1, _Y1 + 2, WHITE, F("File ID"));			this->Dot(_X1 + 1, _Y1 + 9, (_Y2 - 9) - (_Y1 + 9)); 	this->Bracket(_X1 + 1, _Y2 - 9, 7);
					this->Text(_X1 + 2, _Y1 + 2, WHITE, F("Download Status"));	this->Dot(_X1 + 2, _Y1 + 17, (_Y2 - 7) - (_Y1 + 17)); 	this->Bracket(_X1 + 2, _Y2 - 7, 5);
					this->Text(_X1 + 3, _Y1 + 2, WHITE, F("FTP File Size"));	this->Dot(_X1 + 3, _Y1 + 15, (_Y2 - 10) - (_Y1 + 15)); 	this->Bracket(_X1 + 3, _Y2 - 10, 8);
					this->Text(_X1 + 4, _Y1 + 2, WHITE, F("SD File Size"));		this->Dot(_X1 + 4, _Y1 + 14, (_Y2 - 10) - (_Y1 + 14)); 	this->Bracket(_X1 + 4, _Y2 - 10, 8);
					this->Text(_X1 + 5, _Y1 + 2, WHITE, F("Download Percent"));	this->Dot(_X1 + 5, _Y1 + 18, (_Y2 - 8) - (_Y1 + 18)); 	this->Bracket(_X1 + 5, _Y2 - 8, 6);		this->Text(_X1 + 5, _Y2 - 3, WHITE, F("%"));
					this->Text(_X1 + 6, _Y1 + 2, WHITE, F("Download Time"));	this->Dot(_X1 + 6, _Y1 + 15, (_Y2 - 11) - (_Y1 + 15)); 	this->Bracket(_X1 + 6, _Y2 - 11, 9);	this->Text(_X1 + 6, _Y2 - 5, WHITE, F("Sec"));

				}

				// Pressure Stats
				void Pressure(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					this->Box(_X1, _Y1, _X2, _Y2, "Pressure", 7, false, false);

					// Print Text	
					this->Text(_X1 + 1, _Y1 + 2, WHITE, F("Instant"));		this->Dot(_X1 + 1, _Y1 + 9, (_Y2 - 12) - (_Y1 + 9)); 	this->Bracket(_X1 + 1, _Y2 - 12, 10); this->Text(_X1 + 1, _Y2 - 5, WHITE, F("Bar"));
					this->Text(_X1 + 2, _Y1 + 2, WHITE, F("Min"));			this->Dot(_X1 + 2, _Y1 + 5, (_Y2 - 12) - (_Y1 + 5)); 	this->Bracket(_X1 + 2, _Y2 - 12, 10); this->Text(_X1 + 2, _Y2 - 5, WHITE, F("Bar"));
					this->Text(_X1 + 3, _Y1 + 2, WHITE, F("Max"));			this->Dot(_X1 + 3, _Y1 + 5, (_Y2 - 12) - (_Y1 + 5)); 	this->Bracket(_X1 + 3, _Y2 - 12, 10); this->Text(_X1 + 3, _Y2 - 5, WHITE, F("Bar"));
					this->Text(_X1 + 4, _Y1 + 2, WHITE, F("Avarage"));		this->Dot(_X1 + 4, _Y1 + 9, (_Y2 - 12) - (_Y1 + 9)); 	this->Bracket(_X1 + 4, _Y2 - 12, 10); this->Text(_X1 + 4, _Y2 - 5, WHITE, F("Bar"));
					this->Text(_X1 + 5, _Y1 + 2, WHITE, F("Deviation"));	this->Dot(_X1 + 5, _Y1 + 11, (_Y2 - 12) - (_Y1 + 11)); 	this->Bracket(_X1 + 5, _Y2 - 12, 10); this->Text(_X1 + 5, _Y2 - 5, WHITE, F("Bar"));
					this->Text(_X1 + 6, _Y1 + 2, WHITE, F("Slope"));		this->Dot(_X1 + 6, _Y1 + 7, (_Y2 - 12) - (_Y1 + 7)); 	this->Bracket(_X1 + 6, _Y2 - 12, 10); this->Text(_X1 + 6, _Y2 - 3, WHITE, F("%"));
					this->Text(_X1 + 7, _Y1 + 2, WHITE, F("Data Count"));	this->Dot(_X1 + 7, _Y1 + 12, (_Y2 - 6) - (_Y1 + 12)); 	this->Bracket(_X1 + 7, _Y2 - 6, 4);

					// Limit Detail
					this->Text(_X1 + 2, _Y1 + 16, WHITE, F("[     Bar]"));
					this->Text(_X1 + 3, _Y1 + 16, WHITE, F("[     Bar]"));
					this->Text(_X1 + 6, _Y1 + 20, WHITE, F("[   %]"));

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

				// PowerStat V4 Batch Function.
				void PowerStatV4(const uint8_t _X = 1, const uint8_t _Y = 1) {

					// Start VT100 Console
					this->Begin();

					// Draw Main Box
					this->Box(_X, _Y, _X + 47, _Y + 121, "", 0, true, true);

					// Print Main Header Text
					this->Text_Format(BRIGHT);
					this->Text(_X + 1, _Y + 54, WHITE, F("PowerStat V4"));
					this->Text_Format(RST);

					// Header Titles
					this->Text(_X + 1, _Y + 2, WHITE, F("Up Time :"));
					this->Text(_X + 1, _Y + 98, WHITE, F("Send Time (mS) :"));

					// Draw Hardware Diagnostic
					this->Diagnostic(_X + 3, _Y + 1, _X + 11, _Y + 40);

					// Draw Detail Box
					this->Device_Detail(_X + 3, _Y + 41, _X + 11, _Y + 80);

					// Draw Battery Box
					this->Battery(_X + 3, _Y + 81, _X + 11, _Y + 120);

					// Draw Command Box
					this->Box(_X + 12, _Y + 1, _X + 14, _Y + 40, "", 0, false, false);

					// Draw Description Box
					this->Box(_X + 12, _Y + 41, _X + 14, _Y + 80, "", 0, false, false);

					// Draw Status Box
					this->Box(_X + 12, _Y + 81, _X + 14, _Y + 120, "", 0, false, false);
					this->Text(_X + 13, _Y + 83, WHITE, "Device Status"); this->Dot(_X + 13, _Y + 96, 11); this->Bracket(_X + 13, _Y + 107, 11); this->Text(_X + 13, _Y + 108, GRAY, "0x");

					// Draw GSM Detail Box
					this->GSM_Hardware(_X + 15, _Y + 1, _X + 22, _Y + 40);

					// Draw GSM Connection Box
					this->GSM_Operator(_X + 15, _Y + 41, _X + 22, _Y + 80);

					// Draw FOTA Detail Box
					this->GSM_FOTA_Detail(_X + 15, _Y + 81, _X + 22, _Y + 120);

					// JSON Box
					this->Box(_X + 23, _Y + 1, _X + 31, _Y + 80, "JSON", 0, false, false);

					// Pressure Detail
					this->Pressure(_X + 23, _Y + 81, _X + 31, _Y + 120);

					// Draw Voltage Box
					this->Box(_X + 32, _Y + 1, _X + 37, _Y + 40, "Voltage", 8, false, false);

					// Draw Current Box
					this->Box(_X + 32, _Y + 41, _X + 37, _Y + 80, "Current", 8, false, false);

					// Draw Power Box
					this->Box(_X + 32, _Y + 81, _X + 37, _Y + 120, "Power", 8, false, false);

					// Draw Status
					this->Box(_X + 38, _Y + 1, _X + 40, _Y + 120, "", 0, false, false);
					this->Text(_X + 39, _Y + 3, WHITE, "Status  :");

					// Draw Mask
					this->Box(_X + 41, _Y + 1, _X + 44, _Y + 120, "", 0, false, false);
					this->Text(_X + 42, _Y + 3, WHITE, "Publish :");
					this->Text(_X + 43, _Y + 3, WHITE, "Stop    :");

				}

			#endif

			// WeatherStat Batchs
			#if defined(WeatherStat)

				// Hardware Diagnostic Box Print Function.
				void Diagnostic(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw Hardware Diagnostic Box
					this->Box(_X1, _Y1, _X2, _Y2, "Hardware Diagnostic", 1, false, false);

					// Print Text
					this->Text(_X1 + 1, _Y1 + 2, WHITE, F("I2C Multiplexer (0x70)")); 		this->Dot(_X1 + 1, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24));	this->Bracket(_X1 + 1, _Y2 - 7, 5);
					this->Text(_X1 + 2, _Y1 + 2, WHITE, F("Serial ID (0x50)")); 			this->Dot(_X1 + 2, _Y1 + 18, (_Y2 - 7) - (_Y1 + 18));	this->Bracket(_X1 + 2, _Y2 - 7, 5);
					this->Text(_X1 + 3, _Y1 + 2, WHITE, F("Temperature Sensor (0x40)")); 	this->Dot(_X1 + 3, _Y1 + 27, (_Y2 - 7) - (_Y1 + 27));	this->Bracket(_X1 + 3, _Y2 - 7, 5);
					this->Text(_X1 + 4, _Y1 + 2, WHITE, F("UV Sensor (0x60)")); 			this->Dot(_X1 + 4, _Y1 + 18, (_Y2 - 7) - (_Y1 + 18));	this->Bracket(_X1 + 4, _Y2 - 7, 5);
					this->Text(_X1 + 5, _Y1 + 2, WHITE, F("Air Pressure Sensor (0x00)")); 	this->Dot(_X1 + 5, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28));	this->Bracket(_X1 + 5, _Y2 - 7, 5);
					this->Text(_X1 + 6, _Y1 + 2, WHITE, F("DP Sensor 1 (0x25)"));	 		this->Dot(_X1 + 6, _Y1 + 20, (_Y2 - 7) - (_Y1 + 20));	this->Bracket(_X1 + 6, _Y2 - 7, 5);
					this->Text(_X1 + 7, _Y1 + 2, WHITE, F("DP Sensor 2 (0x25)"));	 		this->Dot(_X1 + 7, _Y1 + 20, (_Y2 - 7) - (_Y1 + 20));	this->Bracket(_X1 + 7, _Y2 - 7, 5);
					this->Text(_X1 + 8, _Y1 + 2, WHITE, F("DP Sensor 3 (0x25)"));	 		this->Dot(_X1 + 8, _Y1 + 20, (_Y2 - 7) - (_Y1 + 20));	this->Bracket(_X1 + 8, _Y2 - 7, 5);
					this->Text(_X1 + 9, _Y1 + 2, WHITE, F("Battery Gauge (0x36)")); 		this->Dot(_X1 + 9, _Y1 + 22, (_Y2 - 7) - (_Y1 + 22));	this->Bracket(_X1 + 9, _Y2 - 7, 5);
					this->Text(_X1 + 10, _Y1 + 2, WHITE, F("Battery Charger (0x6B)")); 		this->Dot(_X1 + 10, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24));	this->Bracket(_X1 + 10, _Y2 - 7, 5);

				}

				// WeatherStat Terminal Batch
				void WeatherStatV2(const uint8_t _X = 1, const uint8_t _Y = 1) {

					// Start VT100 Console
					this->Begin();

					// Draw Main Box
					this->Box(_X, _Y, _X + 34, _Y + 121, "", 0, true, true);

					// Print Main Header Text
					this->Text_Format(BRIGHT); this->Text(_X + 1, _Y + 54, WHITE, F("WeatherStat V3")); this->Text_Format(RST);

					// Header Titles
					this->Text_Format(DIM); this->Text(_X + 1, _Y + 2, GRAY, F("Up Time :")); this->Text_Format(RST);

					// Draw Hardware Diagnostic
					this->Diagnostic(_X + 3, _Y + 1, _X + 14, _Y + 40);

					// Header Titles
					this->Text_Format(DIM); this->Text(_X + 33, _Y + 92, WHITE, F("Device ID :"));

				}

			#endif

			// FilterStat Batchs
			#if defined(FilterStat)

				// FilterStat Terminal Batch
				void FilterStatV2(void) {

					// Draw Main Screen
					this->Box(1, 1, 49, 120, "", 0, true, 1);
					//Print_Box_Title(1,1,59,F("FilterStat V3"));

					// Header Titles
					this->Text(2, 3, WHITE, F("Up Time : "));

					// Draw Hardware Diagnostic
					this->Box(4, 2, 12, 39, "Hardware Diagnostic", 1, false, false);
					this->Text(5, 4, WHITE, F("I2C Multiplexer (0x70)")); this->Dot(5, 26, 6); this->Bracket(5, 32, 5);
					this->Text(6, 4, WHITE, F("I2C RTC (0x52)")); this->Dot(6, 18, 14); this->Bracket(6, 32, 5);
					this->Text(7, 4, WHITE, F("I2C Serial ID (0x50)")); this->Dot(7, 24, 8); this->Bracket(7, 32, 5);
					this->Text(8, 4, WHITE, F("I2C Temperature (0x40)")); this->Dot(8, 26, 6); this->Bracket(8, 32, 5);
					this->Text(9, 4, WHITE, F("I2C Battery Gauge (0x36)")); this->Dot(9, 28, 4); this->Bracket(9, 32, 5);
					this->Text(10, 4, WHITE, F("I2C Battery Charger (0x6B)")); this->Dot(10, 30, 2); this->Bracket(10, 32, 5);
					this->Text(11, 4, WHITE, F("SD Card Connection")); this->Dot(11, 22, 10); this->Bracket(11, 32, 5);

					// Draw Detail Box
					this->Box(4, 40, 12, 79, "Detail", 2, false, false);
					this->Text(5, 42, WHITE, F("Serial ID")); this->Dot(5, 51, 9); this->Bracket(5, 60, 17);
					this->Text(6, 42, WHITE, F("Firmware Version")); this->Dot(6, 58, 10); this->Bracket(6, 68, 9);
					this->Text(7, 42, WHITE, F("Hardware Version")); this->Dot(7, 58, 10); this->Bracket(7, 68, 9);
					this->Text(8, 42, WHITE, F("Module Temperature")); this->Dot(8, 60, 9); this->Bracket(8, 69, 8); this->Text(8, 76, WHITE, F("C"));
					this->Text(9, 42, WHITE, F("Module Humidity")); this->Dot(9, 57, 12); this->Bracket(9, 69, 8); this->Text(9, 76, WHITE, F("%"));

					// Draw Battery Box
					this->Box(4, 80, 12, 119, "Battery", 3, false, false);
					this->Text(5, 82, WHITE, F("Instant Voltage")); this->Dot(5, 97, 13); this->Bracket(5, 110, 7);  this->Text(5, 116, WHITE, F("V"));
					this->Text(6, 82, WHITE, F("Temperature")); this->Dot(6, 93, 16); this->Bracket(6, 109, 8); this->Text(6, 116, WHITE, F("C"));
					this->Text(7, 82, WHITE, F("Average Current")); this->Dot(7, 97, 10); this->Bracket(7, 107, 10); this->Text(7, 115, WHITE, F("mA"));
					this->Text(8, 82, WHITE, F("State of Charge")); this->Dot(8, 97, 14); this->Bracket(8, 111, 6); this->Text(8, 116, WHITE, F("%"));
					this->Text(9, 82, WHITE, F("Full Battery Capacity")); this->Dot(9, 103, 6); this->Bracket(9, 109, 8); this->Text(9, 115, WHITE, F("mA"));
					this->Text(10, 82, WHITE, F("Instant Battery Capacity")); this->Dot(10, 106, 3); this->Bracket(10, 109, 8); this->Text(10, 115, WHITE, F("mA"));
					this->Text(11, 82, WHITE, F("Cycle Count")); this->Dot(11, 93, 19); this->Bracket(11, 112, 5);

					// Draw GSM Setup Box
					this->Box(13, 2, 27, 39, "GSM Setup", 4, false, false);
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
					this->Box(13, 40, 27, 79, "GSM Connection", 5, false, false);
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
					this->Box(13, 80, 20, 119, "GSM Detail", 6, false, false);
					this->Text(14, 82, WHITE, F("Manufacturer")); this->Dot(14, 94, 21); this->Bracket(14, 115, 2);
					this->Text(15, 82, WHITE, F("Model")); this->Dot(15, 87, 28); this->Bracket(15, 115, 2);
					this->Text(16, 82, WHITE, F("Firmware")); this->Dot(16, 90, 16); this->Bracket(16, 106, 11);
					this->Text(17, 82, WHITE, F("IMEI")); this->Dot(17, 86, 15); this->Bracket(17, 101, 16);
					this->Text(18, 82, WHITE, F("Serial ID")); this->Dot(18, 91, 15); this->Bracket(18, 106, 11);
					this->Text(19, 82, WHITE, F("SIM ICCID")); this->Dot(19, 91, 6); this->Bracket(19, 97, 20);

					// Connection Box
					this->Box(21, 80, 27, 119, "Connection", 7, false, false);
					this->Text(22, 82, WHITE, F("GSM Connection Time")); this->Dot(22, 101, 11); this->Bracket(22, 112, 5);
					this->Text(23, 82, WHITE, F("RSSI Level")); this->Dot(23, 92, 22); this->Bracket(23, 114, 3);
					this->Text(24, 82, WHITE, F("GSM Operator")); this->Dot(24, 94, 17); this->Bracket(24, 111, 6);
					this->Text(25, 82, WHITE, F("IP Address")); this->Dot(25, 92, 9); this->Bracket(25, 101, 16);
					this->Text(26, 82, WHITE, F("Socket Listen Status")); this->Dot(26, 102, 5); this->Bracket(26, 107, 10);

					// Solenoid Box
					this->Box(31, 2, 36, 98, "", 0, false, false);
					this->Box(31, 99, 36, 119, "", 0, false, false);
					this->Divider(HORIZONTAL,33,2,96,true);
					this->Divider(HORIZONTAL,33,99,20,true);
					this->Divider(VERTICAL,33,8,3);
					this->Divider(VERTICAL,33,14,3);
					this->Divider(VERTICAL,33,20,3);
					this->Divider(VERTICAL,33,26,3);
					this->Divider(VERTICAL,33,32,3);
					this->Divider(VERTICAL,33,38,3);
					this->Divider(VERTICAL,33,44,3);
					this->Divider(VERTICAL,33,50,3);
					this->Divider(VERTICAL,33,56,3);
					this->Divider(VERTICAL,33,62,3);
					this->Divider(VERTICAL,33,68,3);
					this->Divider(VERTICAL,33,74,3);
					this->Divider(VERTICAL,33,80,3);
					this->Divider(VERTICAL,33,86,3);
					this->Divider(VERTICAL,33,92,3);
					this->Divider(VERTICAL,31,26,2);
					this->Divider(VERTICAL,31,50,2);
					this->Divider(VERTICAL,31,74,2);
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
					this->Box(28, 2, 30, 119, "", 8, false, false);

					// Setting Detail
					this->Box(37, 2, 46, 98, "Data", 0, false, false);

					// Setting Section
					this->Box(37, 99, 46, 119, "Setting", 0, false, false);
					this->Text(39, 101, WHITE, F("Filter Count.[  ]"));
					this->Text(40, 101, WHITE, F("State.......[   ]"));
					this->Text(41, 101, WHITE, F("Stabilizer....[ ]"));
					this->Text(42, 101, WHITE, F("HydroCyclone..[ ]"));
					this->Text(43, 101, WHITE, F("Irrigation....[ ]"));
					//Text(44, 101, WHITE, F("IDLE..........[ ]"));

					this->Divider(VERTICAL,47,99,2);

				}

			#endif

			/* Console Tool Functions */

			// I2C Scanner Batch
			#if defined(I2C_SCANNER)

				// I2C Scanner
				void I2C_Scanner(void) {

					// Draw Console Table Grid
					for (uint8_t i = 1; i <= 23; i = i + 2) this->Divider(HORIZONTAL, i, 1, 120, false);
					this->Divider(VERTICAL, 1, 1, 22);
					for (uint8_t i = 9; i <= 120; i = i + 7) this->Divider(VERTICAL, 3, i, 18);
					this->Divider(VERTICAL, 1, 121, 22);

					// Draw Corners
					this->Text(1, 1, WHITE, F("┌"));
					this->Text(1, 121, WHITE, F("┐"));
					this->Text(23, 1, WHITE, F("└"));
					this->Text(23, 121, WHITE, F("┘"));

					// Draw T
					for (uint8_t i = 3; i <= 21; i = i + 2) {this->Set_Cursor(i,1); Console_Serial->print(F("├"));}
					for (uint8_t i = 3; i <= 21; i = i + 2) {this->Set_Cursor(i,121); Console_Serial->print(F("┤"));}
					
					// Draw Cross Section
					for (uint8_t i = 5; i <= 19; i = i + 2) {for (uint8_t j = 9; j <= 120; j = j + 7) {this->Set_Cursor(i,j); Console_Serial->print(F("┼"));}}
					
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

			#endif

			// HDC2010 TH Meter Batch
			#if defined(TH_METER)

				// HDC2010 TH Meter
				void TH_Meter(void) {

						// Draw Main Screen
						this->Box(1, 1, 8, 38, "HDC2010 T/H Sensor", 1, false, true);
						this->Text(3, 3, WHITE, F("Temperature..........[         C ]"));
						this->Text(4, 3, WHITE, F("Humidity.............[         % ]"));
						this->Text(7, 3, WHITE, F("Function Time............[    ms ]"));
					
				}

			#endif

			// MAX78630 Voltage Meter Batch
			#if defined(VOLTMETER)

				// MAX78630 Voltmeter Terminal Batch
				void Voltmeter(void) {

					// Draw Main Screen
					this->Box(1, 1, 14, 84, "", 0, true, true);

					// Draw Voltage
					this->Box(5, 3, 10, 28, "Phase R", 1, false, false);
					this->Box(5, 30, 10, 55, "Phase S", 2, false, false);
					this->Box(5, 57, 10, 82, "Phase T", 3, false, false);

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

			#endif

			// MAX78630 Full Terminal Batch
			#if defined(MAX78630_FULL)

				// Full_Energy_Analayzer
				void Full_Energy_Analayzer(void) {

					// Draw Main Screen
					this->Box(1, 1, 41, 160, "", 0, true, false);
					this->Text(2, 68, WHITE, F("MAX78630 Energy Analyzer"));

					// Draw Voltage
					this->Box(5, 2, 13, 77, "Voltage", 1, false, false);
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
					this->Box(5, 78, 13, 159, "Current", 2, false, false);
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
					this->Box(15, 2, 22, 132, "Power", 3, false, false);
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
					this->Box(15, 133, 22, 159, "Device", 4, false, false);
					this->Text(16, 135, WHITE, F("Device Addres :"));
					this->Text(17, 135, WHITE, F("Firmware      :"));
					this->Text(18, 135, WHITE, F("Baud          :"));
					this->Text(19, 135, WHITE, F("Temperature   :"));
					this->Text(20, 135, WHITE, F("VScale        :"));
					this->Text(21, 135, WHITE, F("IScale        :"));

					// Draw Min/Max Mask
					this->Box(24, 2, 29, 104, "Min/Max Mask", 5, false, false);
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
					this->Box(24, 105, 29, 123, "Other", 7, false, false);
					this->Text(25, 107, WHITE, F("STICKY......[ ]"));
					this->Text(26, 107, WHITE, F("FREQ....[     ]"));
					this->Text(27, 107, WHITE, F("BUCKET_L [    ]"));
					this->Text(28, 107, WHITE, F("BUCKET_H [    ]"));

					// Draw Status Limits
					this->Box(30, 2, 34, 123, "Status Limits", 8, false, false);
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
					this->Box(24, 124, 34, 159, "Status", 9, false, false);
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
					this->Box(36, 2, 40, 159, "Energy Counter", 10, false, false);
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

			#endif

			// Analog Pressure Meter Batch
			#if defined(ANALOG_PRESSURE)

				// Analog Pressure Meter
				void Analog_Pressure_Meter(void) {

					// Draw Main Screen
					this->Box(1, 1, 8, 38, "Analog P Sensor", 1, false, true);
					this->Text(3, 3, WHITE, F("Pressure...........[         Bar ]"));
					this->Text(4, 3, WHITE, F("Deviation..............[         ]"));
					this->Text(7, 3, WHITE, F("Function Time............[    ms ]"));

				}

			#endif

			// PostOffice Terminal Batch
			#if defined(POSTOFFICE_TEST)

				// Telit xE910 Terminal Batch
				void Telit_xE910(void) {

					// Draw Main Box
					this->Box(1, 1, 30, 120, "", 0, true, true);

					// Print Main Header Text
					this->Text(2, 50, WHITE, F("PostOffice Test Procedure"));

					// Header Titles
					this->Text(2, 3, WHITE, F("Up Time : "));
					this->Text(2, 100, WHITE, F("Firmware : "));

					// Draw GSM Setup Box
					this->Box(4, 2, 24, 39, "GSM Setup", 1, false, false);
					for (uint8_t i = 5; i < 24; i++) {Dot(i, 4, 28); Bracket(i, 32, 5);}
				
					// Draw GSM Connection Box
					this->Box(4, 2, 24, 39, "GSM Connection", 2, false, false);
					for (uint8_t i = 5; i < 24; i++) {Dot(i, 42, 30); Bracket(i, 72, 5);}
					
					// Draw GSM Detail Box
					this->GSM_Hardware(4, 80, 11, 119);

					// Draw GSM Connection Detail Box
					this->Box(12, 80, 19, 119, "Connection", 4, false, false);
					for (uint8_t i = 13; i < 19; i++) Dot(i, 82, 30); 
					this->Text(13, 82, WHITE, F("GSM Connection Time")); Bracket(13, 112, 5);
					this->Text(14, 82, WHITE, F("Signal Level")); Bracket(14, 111, 6);
					this->Text(15, 82, WHITE, F("GSM Operator")); Bracket(15, 111, 6);
					this->Text(16, 82, WHITE, F("IP Address")); Bracket(16, 101, 16);
					this->Text(17, 82, WHITE, F("LAC")); Bracket(17, 112, 5);
					this->Text(18, 82, WHITE, F("Cell ID")); Bracket(18, 112, 5);

					// JSON Data Box
					this->Box(25, 2, 27, 79, "", 6, false, false);

					// Draw GSM Connection Detail Box
					this->Box(20, 80, 27, 119, "Firmware", 5, false, false);
					for (uint8_t i = 21; i < 27; i++) Dot(i, 82, 30); 

					this->Text(21, 82, WHITE, F("File ID")); Bracket(21, 110, 7);
					this->Text(22, 82, WHITE, F("Download Status")); Bracket(22, 112, 5);
					this->Text(23, 82, WHITE, F("FTP File Size")); Bracket(23, 109, 8);
					this->Text(24, 82, WHITE, F("SD File Size")); Bracket(24, 109, 8);
					this->Text(25, 82, WHITE, F("Download Percent")); Bracket(25, 111, 6); this->Text(25, 116, WHITE, F("%"));
					this->Text(26, 82, WHITE, F("Download Time")); Bracket(26, 108, 9); this->Text(26, 114, WHITE, F("Sec"));

				}

			#endif

	};

#endif /* defined(__Console__) */