#ifndef __Console__
#define __Console__

	// Define Arduino Library
	#ifndef __Arduino__
		#include <Arduino.h>
	#endif

	// Include Definition File
	#include "Definition.h"

	// Console Class
	class Console {

		// Private Context
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

		// Public Context
		public:

			// Construct a new Console object
			Console(Stream &_Serial) {

				// Set Serial
				this->Console_Serial = &_Serial;

			}

			// Begin Console.
			void Begin(void) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Cursor Off
					this->Cursor(false);

					// Clear Screen
					this->Clear(_Console_SCREEN_);

					// Set Text Color
					this->Text_Color(_Console_WHITE_);

					// Reset Delay
					delay(5);

				#endif

			}

			// Clear Terminal Function.
			void Clear(const uint8_t _Type) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Clear Terminal Type
					switch (_Type) {

						// Clear Line After Cursor
						case _Console_LINE_AFTER_CURSOR_: {

							// Print Clear Line After Cursor Command
							Console_Serial->print(F("\e[K"));

							// End Case
							break;

						}

						// Clear Line to Cursor
						case _Console_LINE_TO_CURSOR_: {

							// Print Clear Line to Cursor Command
							Console_Serial->print(F("\e[1K"));

							// End Case
							break;

						}

						// Clear Line
						case _Console_LINE_: {

							// Print Clear Line Command
							Console_Serial->print(F("\e[2K"));

							// End Case
							break;

						}

						// Clear Screen
						case _Console_SCREEN_: {

							// Print Clear Screen Command
							Console_Serial->print(F("\e[2J"));

							// End Case
							break;

						}

						// Clear All
						case _Console_ALL_: {

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

				#endif

			}

			// Change Cursor Visibility Function.
			void Cursor(const bool _State) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Cursor On
					if (_State) Console_Serial->print(F("\e[?25h"));	

					// Cursor Off
					if (!_State) Console_Serial->print(F("\e[?25l"));	

				#endif

			}

			// Draw Box Function.
			void Box(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2, String _Text = "", const uint8_t _Number = 0, const bool _Header = false, const bool _Footer = false) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Color
					this->Text_Color(_Console_WHITE_);

					// Set Text Format
					this->Text_Format(_Console_DIM_);

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
					this->Text_Color(_Console_YELLOW_); this->Set_Cursor(_X1, _Y1 + 2); Console_Serial->print(_Text);

					// Print Header Number
					if (_Number != 0) {
						this->Text_Color(_Console_WHITE_); this->Set_Cursor(_X1, _Y2 - 5); Console_Serial->print(F("[  ]"));
						if (_Number < 10) {
							this->Text_Color(_Console_YELLOW_); this->Set_Cursor(_X1, _Y2 - 4); Console_Serial->print(F("0"));
							this->Text_Color(_Console_YELLOW_); this->Set_Cursor(_X1, _Y2 - 3); Console_Serial->print(_Number);
						} else {
							this->Text_Color(_Console_YELLOW_); this->Set_Cursor(_X1, _Y2 - 4); Console_Serial->print(_Number);
						}
					}

					// Draw Header
					if (_Header) {

						// Set Text Color
						this->Text_Color(_Console_WHITE_);

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
						this->Text_Color(_Console_WHITE_);

						// Print Corners
						this->Set_Cursor(_X2 - 2, _Y1); Console_Serial->print(F("├"));
						this->Set_Cursor(_X2 - 2, _Y2); Console_Serial->print(F("┤"));

						// Print Lines
						for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
							
							this->Set_Cursor(_X2 - 2, i); Console_Serial->print(F("─"));
							
						}

					}

				#endif

			}

			// Dot Print Function.
			void Dot(const uint8_t _X, const uint8_t _Y, const uint8_t _Count) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print Dots
					for (uint8_t i = 0; i < _Count; i++) {

						// Print Dot
						this->Text(_X, _Y + i, _Console_GRAY_, F("."));

					}

				#endif

			}

			// Bracket Place Holder Function.
			void Bracket(const uint8_t _X, const uint8_t _Y, const uint8_t _Space) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print Bracket Start
					this->Text(_X, _Y, _Console_WHITE_, F("["));

					// Print Bracket Left
					this->Text(_X, _Y + _Space, _Console_WHITE_, F("]"));

				#endif

			}

			// Horizontal Line Divider Function.
			void Divider(const bool _Type, const uint8_t _X, const uint8_t _Y, const uint8_t _Length, const bool _End = false) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					//Set Color
					this->Text_Color(_Console_WHITE_);

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

				#endif

			}

			// Set Text Color Function.
			void Text_Color(uint8_t _Color) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Control for Buffer
					if (_Color != this->Buffer.Text_Color) {

						// Set Text Color.
						Console_Serial->print(F("\e["));
						Console_Serial->print(_Color);
						Console_Serial->write('m');

						// Update Buffer Variable
						this->Buffer.Text_Color = _Color;

					}

				#endif

			}

			// Set Back Ground Color Function.
			void Background_Color(uint8_t _Color) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Control for Buffer
					if (_Color != this->Buffer.Background_Color) {

						// Set Back Ground Color.
						Console_Serial->print(F("\e["));
						Console_Serial->print(_Color + 10);
						Console_Serial->write('m');

						// Update Buffer Variable
						this->Buffer.Background_Color = _Color;

					}

				#endif

			}

			// Set Text Format Function
			void Text_Format(const uint8_t _Format) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Control for Buffer
					if (_Format != this->Buffer.Text_Format) {

						// Set Text Format
						Console_Serial->print(F("\e["));
						Console_Serial->print(_Format);
						Console_Serial->write('m');

						// Update Buffer Variable
						this->Buffer.Text_Format = _Format;

					}

				#endif

			}

			// Set Cursor Position Function.
			void Set_Cursor(uint8_t _X, uint8_t _Y) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Cursor Position
					Console_Serial->print(F("\e["));
					Console_Serial->print(_X);
					Console_Serial->print(F(";"));
					Console_Serial->print(_Y);
					Console_Serial->print(F("H"));

				#endif

			}

			// Terminal Beep Sound Function.
			void Beep(void) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Beep Terminal.
					Console_Serial->print(F("\x07"));

				#endif

			}

			// Print Text to Specified Position and Color.
			void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, String _Value) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Cursor Position
					Set_Cursor(_X, _Y); 

					// Set Text Color
					Text_Color(_Color); 

					// Print Text			
					Console_Serial->print(String(_Value));

				#endif

			}

			// OK Decide Function.
			void OK(const bool _Result, const uint8_t _X, const uint8_t _Y) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print Command State
					if (_Result) {

						// Success
						this->Text(_X, _Y, _Console_GREEN_, F(" OK "));

					} else {

						// Fail
						this->Text(_X, _Y, _Console_RED_, F("FAIL"));

					}

				#endif

			}

			// GSM Command Proccess
			void AT_Command(uint8_t _X, uint8_t _Y, String _Command) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Cursor Position
					this->Set_Cursor(_X, _Y);

					// Clear Line
					for (uint8_t i = 0; i < 30; i++) Console_Serial->print(F(" "));

					// Print Dot
					this->Text(_X, _Y, _Console_GRAY_, F(".............................."));

					// Print Command
					this->Text(_X, _Y, _Console_WHITE_, _Command);

					// Print Response Wait Dot
					this->Text(_X, _Y + 31, _Console_BLUE_, F(" .. "));

				#endif

			}

	};

	// Console Class
	class PowerStat_Console : public Console {

		// Color Choice
		#define SELECT_COLOR(_VALUE, _MIN, _MAX) ((_VALUE) <= (_MIN) ? _Console_RED_ : ((_VALUE) >= (_MAX) ? _Console_GREEN_ : _Console_WHITE_))

		// Public Context
		private:

			// Hardware Diagnostic Box Print Function.
			void Diagnostic(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Draw Hardware Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, "Hardware Diagnostic", 1, false, false);

					// Print Text
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("I2C RTC (0x52)")); 				Console::Dot(_X1 + 1, _Y1 + 16, (_Y2 - 7) - (_Y1 + 16)); 	Console::Bracket(_X1 + 1, _Y2 - 7, 5);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("I2C Serial ID (0x50)")); 		Console::Dot(_X1 + 2, _Y1 + 22, (_Y2 - 7) - (_Y1 + 22));	Console::Bracket(_X1 + 2, _Y2 - 7, 5);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("I2C Temperature (0x40)")); 		Console::Dot(_X1 + 3, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24));	Console::Bracket(_X1 + 3, _Y2 - 7, 5);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("I2C Battery Gauge (0x36)")); 	Console::Dot(_X1 + 4, _Y1 + 26, (_Y2 - 7) - (_Y1 + 26));	Console::Bracket(_X1 + 4, _Y2 - 7, 5);
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("I2C Battery Charger (0x6B)")); 	Console::Dot(_X1 + 5, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28));	Console::Bracket(_X1 + 5, _Y2 - 7, 5);
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("SD Card Connection")); 			Console::Dot(_X1 + 6, _Y1 + 20, (_Y2 - 7) - (_Y1 + 20)); 	Console::Bracket(_X1 + 6, _Y2 - 7, 5);

				#endif

			}

			// Detail Box Print Function.
			void Device_Detail(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Draw Hardware Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, "Hardware Detail", 2, false, false);

					// Print Text
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("Serial ID")); 			Console::Dot(_X1 + 1, _Y1 + 11, (_Y2 - 19) - (_Y1 + 11)); 	Console::Bracket(_X1 + 1, _Y2 - 19, 17);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Firmware Version")); 	Console::Dot(_X1 + 2, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	Console::Bracket(_X1 + 2, _Y2 - 11, 9);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("Hardware Version")); 	Console::Dot(_X1 + 3, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	Console::Bracket(_X1 + 3, _Y2 - 11, 9);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("Module Temperature")); 	Console::Dot(_X1 + 4, _Y1 + 20, (_Y2 - 10) - (_Y1 + 20)); 	Console::Bracket(_X1 + 4, _Y2 - 10, 8); Console::Text(_X1 + 4, _Y2 - 3, _Console_WHITE_, F("C"));
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Module Humidity")); 	Console::Dot(_X1 + 5, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	Console::Bracket(_X1 + 5, _Y2 - 10, 8); Console::Text(_X1 + 5, _Y2 - 3, _Console_WHITE_, F("%"));
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Send Interval"));		Console::Dot(_X1 + 6, _Y1 + 15, (_Y2 - 10) - (_Y1 + 15)); 	Console::Bracket(_X1 + 6, _Y2 - 10, 8); Console::Text(_X1 + 6, _Y2 - 5, _Console_WHITE_, F("Min"));

				#endif

			}

			// Battery Print Function.
			void Battery(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Draw Hardware Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, "Battery", 3, false, false);

					// Print Text
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("Instant Voltage")); 			Console::Dot(_X1 + 1, _Y1 + 17, (_Y2 - 9) - (_Y1 + 17)); 	Console::Bracket(_X1 + 1, _Y2 - 9, 7);		Console::Text(_X1 + 1, _Y2 - 3, _Console_WHITE_, F("V"));
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Temperature")); 				Console::Dot(_X1 + 2, _Y1 + 13, (_Y2 - 10) - (_Y1 + 13)); 	Console::Bracket(_X1 + 2, _Y2 - 10, 8);		Console::Text(_X1 + 2, _Y2 - 3, _Console_WHITE_, F("C"));
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("Average Current")); 			Console::Dot(_X1 + 3, _Y1 + 17, (_Y2 - 13) - (_Y1 + 17)); 	Console::Bracket(_X1 + 3, _Y2 - 13, 11);	Console::Text(_X1 + 3, _Y2 - 4, _Console_WHITE_, F("mA"));
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("State of Charge")); 			Console::Dot(_X1 + 4, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	Console::Bracket(_X1 + 4, _Y2 - 10, 8);		Console::Text(_X1 + 4, _Y2 - 3, _Console_WHITE_, F("%"));
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Instant Battery Capacity"));	Console::Dot(_X1 + 5, _Y1 + 26, (_Y2 - 10) - (_Y1 + 26)); 	Console::Bracket(_X1 + 5, _Y2 - 10, 8);		Console::Text(_X1 + 5, _Y2 - 4, _Console_WHITE_, F("mA"));
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Charge State")); 				Console::Dot(_X1 + 6, _Y1 + 14, (_Y2 - 15) - (_Y1 + 14)); 	Console::Bracket(_X1 + 6, _Y2 - 15, 13);

				#endif

			}

			// GSM Detail Function.
			void GSM_Hardware(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, "GSM Detail", 4, false, false);

					// Print Text	
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("Manufacturer"));	Console::Dot(_X1 + 1, _Y1 + 14, (_Y2 - 4) - (_Y1 + 14)); 	Console::Bracket(_X1 + 1, _Y2 - 4, 2);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Model"));			Console::Dot(_X1 + 2, _Y1 + 7, (_Y2 - 4) - (_Y1 + 7)); 		Console::Bracket(_X1 + 2, _Y2 - 4, 2);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("Firmware"));		Console::Dot(_X1 + 3, _Y1 + 10, (_Y2 - 12) - (_Y1 + 10)); 	Console::Bracket(_X1 + 3, _Y2 - 12, 10);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("IMEI"));			Console::Dot(_X1 + 4, _Y1 + 6, (_Y2 - 18) - (_Y1 + 6)); 	Console::Bracket(_X1 + 4, _Y2 - 18, 16);
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Serial ID"));		Console::Dot(_X1 + 5, _Y1 + 11, (_Y2 - 13) - (_Y1 + 11)); 	Console::Bracket(_X1 + 5, _Y2 - 13, 11);
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("ICCID"));			Console::Dot(_X1 + 6, _Y1 + 7, (_Y2 - 22) - (_Y1 + 7)); 	Console::Bracket(_X1 + 6, _Y2 - 22, 20);

				#endif

			}

			// GSM Connection Detail Function.
			void GSM_Operator(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, "GSM Connection", 5, false, false);

					// Print Text	
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("GSM Connection Time"));	Console::Dot(_X1 + 1, _Y1 + 21, (_Y2 - 7) - (_Y1 + 21)); 	Console::Bracket(_X1 + 1, _Y2 - 7, 5);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Signal Level"));			Console::Dot(_X1 + 2, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	Console::Bracket(_X1 + 2, _Y2 - 8, 6);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("GSM Operator"));			Console::Dot(_X1 + 3, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	Console::Bracket(_X1 + 3, _Y2 - 8, 6);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("IP Address"));			Console::Dot(_X1 + 4, _Y1 + 12, (_Y2 - 18) - (_Y1 + 12)); 	Console::Bracket(_X1 + 4, _Y2 - 18, 16);
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("LAC"));					Console::Dot(_X1 + 5, _Y1 + 5, (_Y2 - 7) - (_Y1 + 5)); 		Console::Bracket(_X1 + 5, _Y2 - 7, 5);
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("CELL ID"));				Console::Dot(_X1 + 6, _Y1 + 9, (_Y2 - 7) - (_Y1 + 9)); 		Console::Bracket(_X1 + 6, _Y2 - 7, 5);

				#endif

			}

			// GSM FOTA
			void GSM_FOTA_Detail(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, "FOTA", 6, false, false);

					// Print Text	
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("File ID"));			Console::Dot(_X1 + 1, _Y1 + 9, (_Y2 - 9) - (_Y1 + 9)); 		Console::Bracket(_X1 + 1, _Y2 - 9, 7);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Download Status"));	Console::Dot(_X1 + 2, _Y1 + 17, (_Y2 - 7) - (_Y1 + 17)); 	Console::Bracket(_X1 + 2, _Y2 - 7, 5);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("FTP File Size"));		Console::Dot(_X1 + 3, _Y1 + 15, (_Y2 - 10) - (_Y1 + 15)); 	Console::Bracket(_X1 + 3, _Y2 - 10, 8);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("SD File Size"));		Console::Dot(_X1 + 4, _Y1 + 14, (_Y2 - 10) - (_Y1 + 14)); 	Console::Bracket(_X1 + 4, _Y2 - 10, 8);
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Download Percent"));	Console::Dot(_X1 + 5, _Y1 + 18, (_Y2 - 8) - (_Y1 + 18)); 	Console::Bracket(_X1 + 5, _Y2 - 8, 6);		Console::Text(_X1 + 5, _Y2 - 3, _Console_WHITE_, F("%"));
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Download Time"));		Console::Dot(_X1 + 6, _Y1 + 15, (_Y2 - 11) - (_Y1 + 15)); 	Console::Bracket(_X1 + 6, _Y2 - 11, 9);		Console::Text(_X1 + 6, _Y2 - 5, _Console_WHITE_, F("Sec"));

				#endif

			}

			// Pressure Stats
			void Pressure(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, "Pressure", 7, false, false);

					// Print Text	
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("Instant"));		Console::Dot(_X1 + 1, _Y1 + 9, (_Y2 - 12) - (_Y1 + 9)); 	Console::Bracket(_X1 + 1, _Y2 - 12, 10); Console::Text(_X1 + 1, _Y2 - 5, _Console_WHITE_, F("Bar"));
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Min"));			Console::Dot(_X1 + 2, _Y1 + 5, (_Y2 - 12) - (_Y1 + 5)); 	Console::Bracket(_X1 + 2, _Y2 - 12, 10); Console::Text(_X1 + 2, _Y2 - 5, _Console_WHITE_, F("Bar"));
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("Max"));			Console::Dot(_X1 + 3, _Y1 + 5, (_Y2 - 12) - (_Y1 + 5)); 	Console::Bracket(_X1 + 3, _Y2 - 12, 10); Console::Text(_X1 + 3, _Y2 - 5, _Console_WHITE_, F("Bar"));
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("Average"));		Console::Dot(_X1 + 4, _Y1 + 9, (_Y2 - 12) - (_Y1 + 9)); 	Console::Bracket(_X1 + 4, _Y2 - 12, 10); Console::Text(_X1 + 4, _Y2 - 5, _Console_WHITE_, F("Bar"));
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Deviation"));		Console::Dot(_X1 + 5, _Y1 + 11, (_Y2 - 12) - (_Y1 + 11)); 	Console::Bracket(_X1 + 5, _Y2 - 12, 10); Console::Text(_X1 + 5, _Y2 - 5, _Console_WHITE_, F("Bar"));
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Slope"));			Console::Dot(_X1 + 6, _Y1 + 7, (_Y2 - 12) - (_Y1 + 7)); 	Console::Bracket(_X1 + 6, _Y2 - 12, 10); Console::Text(_X1 + 6, _Y2 - 3, _Console_WHITE_, F("%"));
					Console::Text(_X1 + 7, _Y1 + 2, _Console_WHITE_, F("Data Count"));	Console::Dot(_X1 + 7, _Y1 + 12, (_Y2 - 6) - (_Y1 + 12)); 	Console::Bracket(_X1 + 7, _Y2 - 6, 4);

					// Limit Detail
					Console::Text(_X1 + 2, _Y1 + 16, _Console_WHITE_, F("[     Bar]"));
					Console::Text(_X1 + 3, _Y1 + 16, _Console_WHITE_, F("[     Bar]"));
					Console::Text(_X1 + 6, _Y1 + 20, _Console_WHITE_, F("[   %]"));

				#endif

			}

			// PowerStat V4 Publish Bit Table
			void Status_Variables(uint8_t _Mask_Type, uint32_t _Mask) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Mask X Position
					uint8_t _X = 40 + _Mask_Type;

					// Print Pump Status
					Console::Text(_X, 15, (bitRead(_Mask, 0) ? _Console_GREEN_ : _Console_RED_), F("P"));

					// Print Phase Status
					Console::Text(_X, 18, (bitRead(_Mask, 1) ? _Console_GREEN_ : _Console_RED_), F("VR"));
					Console::Text(_X, 22, (bitRead(_Mask, 2) ? _Console_GREEN_ : _Console_RED_), F("VS"));
					Console::Text(_X, 26, (bitRead(_Mask, 3) ? _Console_GREEN_ : _Console_RED_), F("VT"));

					// Print Relay Status
					if (_Mask_Type == 0) Console::Text(_X, 30, (bitRead(_Mask, 4) ? _Console_GREEN_ : _Console_RED_), F("M1"));
					if (_Mask_Type == 0) Console::Text(_X, 34, (bitRead(_Mask, 5) ? _Console_GREEN_ : _Console_RED_), F("M2"));
					if (_Mask_Type == 0) Console::Text(_X, 38, (bitRead(_Mask, 6) ? _Console_GREEN_ : _Console_RED_), F("M3"));

					// Print Fault Status
					Console::Text(_X, 42, (bitRead(_Mask, 7) ? _Console_GREEN_ : _Console_RED_), F("TH"));
					Console::Text(_X, 46, (bitRead(_Mask, 8) ? _Console_GREEN_ : _Console_RED_), F("MP"));
					Console::Text(_X, 50, (bitRead(_Mask, 9) ? _Console_GREEN_ : _Console_RED_), F("SA"));

					// Print Pressure Status
					Console::Text(_X, 54, (bitRead(_Mask, 10) ? _Console_GREEN_ : _Console_RED_), F("PL"));
					Console::Text(_X, 58, (bitRead(_Mask, 11) ? _Console_GREEN_ : _Console_RED_), F("PH"));
					Console::Text(_X, 62, (bitRead(_Mask, 12) ? _Console_GREEN_ : _Console_RED_), F("PD"));
					Console::Text(_X, 66, (bitRead(_Mask, 13) ? _Console_GREEN_ : _Console_RED_), F("PR"));

					// Print Energy Status
					Console::Text(_X, 70, (bitRead(_Mask, 14) ? _Console_GREEN_ : _Console_RED_), F("VL"));
					Console::Text(_X, 74, (bitRead(_Mask, 15) ? _Console_GREEN_ : _Console_RED_), F("VH"));
					Console::Text(_X, 78, (bitRead(_Mask, 16) ? _Console_GREEN_ : _Console_RED_), F("IH"));
					Console::Text(_X, 82, (bitRead(_Mask, 17) ? _Console_GREEN_ : _Console_RED_), F("FQL"));
					Console::Text(_X, 87, (bitRead(_Mask, 18) ? _Console_GREEN_ : _Console_RED_), F("FQH"));
					Console::Text(_X, 92, (bitRead(_Mask, 19) ? _Console_GREEN_ : _Console_RED_), F("VIM"));
					Console::Text(_X, 97, (bitRead(_Mask, 20) ? _Console_GREEN_ : _Console_RED_), F("IIM"));

					// Print Sensor Status
					Console::Text(_X, 108, (bitRead(_Mask, 21) ? _Console_GREEN_ : _Console_RED_), F("PS"));
					Console::Text(_X, 112, (bitRead(_Mask, 22) ? _Console_GREEN_ : _Console_RED_), F("SD"));
					Console::Text(_X, 116, (bitRead(_Mask, 23) ? _Console_GREEN_ : _Console_RED_), F("SYS"));

				#endif

			}

			// PowerStat V4 Publish Bit Table
			void Status_Detail(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, "", 0, false, false);

					// Print Header
					Console::Text(_X1 + 1, _Y1 + 23, _Console_WHITE_, "31 30 29 28 27 26 25 24 23 22 21 20 19 18 17 16 15 14 13 12 11 10 09 08 07 06 05 04 03 02 01 00");

					// Print Divider
					Console::Divider(HORIZONTAL, _X1 + 2, _Y1 + 1, _Y2 - 4, false);

					// Print Text
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, "Status"); 
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, "Publish"); 
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, "Stop"); 
					
					// Print HEX
					Console::Bracket(_X1 + 3, _Y1 + 10, 11); Console::Text(_X1 + 3, _Y1 + 11, _Console_GRAY_, "0x");
					Console::Bracket(_X1 + 4, _Y1 + 10, 11); Console::Text(_X1 + 4, _Y1 + 11, _Console_GRAY_, "0x");
					Console::Bracket(_X1 + 5, _Y1 + 10, 11); Console::Text(_X1 + 5, _Y1 + 11, _Console_GRAY_, "0x");

					// Print Status Placeholder
					Console::Text(_X1 + 3, _Y1 + 23, _Console_GRAY_, "X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X");
					Console::Text(_X1 + 4, _Y1 + 23, _Console_GRAY_, "X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X");
					Console::Text(_X1 + 5, _Y1 + 23, _Console_GRAY_, "X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X");

				#endif

			}

		// Private Context
		public:

			// Class Constructor
			PowerStat_Console(Stream &_Serial) : Console(_Serial) {


			}

			// PowerStat V4 Batch Function.
			void Begin(const uint8_t _X = 1, const uint8_t _Y = 1) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Start VT100 Console
					Console::Begin();

					// Draw Main Box
					Console::Box(_X, _Y, _X + 46, _Y + 121, "", 0, true, true);

					// Print Main Header Text
					Console::Text_Format(_Console_BRIGHT_);
					Console::Text(_X + 1, _Y + 54, _Console_WHITE_, F("PowerStat V4"));
					Console::Text_Format(_Console_RST_);

					// Header Titles
					Console::Text(_X + 1, _Y + 2, _Console_WHITE_, F("Up Time :"));
					Console::Text(_X + 1, _Y + 98, _Console_WHITE_, F("Send Time (mS) :"));

					// Draw Hardware Diagnostic
					this->Diagnostic(_X + 3, _Y + 1, _X + 10, _Y + 40);

					// Draw Detail Box
					this->Device_Detail(_X + 3, _Y + 41, _X + 10, _Y + 80);

					// Draw Battery Box
					this->Battery(_X + 3, _Y + 81, _X + 10, _Y + 120);

					// Draw GSM Detail Box
					this->GSM_Hardware(_X + 11, _Y + 1, _X + 18, _Y + 40);

					// Draw GSM Connection Box
					this->GSM_Operator(_X + 11, _Y + 41, _X + 18, _Y + 80);

					// Draw FOTA Detail Box
					this->GSM_FOTA_Detail(_X + 11, _Y + 81, _X + 18, _Y + 120);

					// Draw Command Box
					Console::Box(_X + 19, _Y + 1, _X + 21, _Y + 120, "", 0, false, false);

					// JSON Box
					Console::Box(_X + 22, _Y + 1, _X + 30, _Y + 80, "JSON", 0, false, false);

					// Pressure Detail
					this->Pressure(_X + 22, _Y + 81, _X + 30, _Y + 120);

					// Draw Voltage Box
					Console::Box(_X + 31, _Y + 1, _X + 36, _Y + 40, "Voltage", 8, false, false);

					// Draw Current Box
					Console::Box(_X + 31, _Y + 41, _X + 36, _Y + 80, "Current", 8, false, false);

					// Draw Power Box
					Console::Box(_X + 31, _Y + 81, _X + 36, _Y + 120, "Power", 8, false, false);

					// Draw Mask
					this->Status_Detail(_X + 37, _Y + 1, _X + 43, _Y + 120);

					// Print Board Type
					#if defined(_B107AA_)
						Console::Text(_X + 45, _Y + 114, _Console_YELLOW_, F("B107AA"));
					#elif defined(_B108AA_)
						Console::Text(_X + 45, _Y + 114, _Console_YELLOW_, F("B108AA"));
					#endif

				#endif

			}

	};

	// Console Class
	class I2C_Scanner_Console : public Console {

		// Private Context
		public:

			// Class Constructor
			I2C_Scanner_Console(Stream &_Serial) : Console(_Serial) {


			}

			// I2C Scanner Batch Function.
			void Begin (void) {

				// Start VT100 Console
				Console::Begin();

				// Draw Console Table Grid
				for (uint8_t i = 1; i <= 23; i = i + 2) Console::Divider(HORIZONTAL, i, 1, 120, false);

				// Draw Divider
				Console::Divider(VERTICAL, 1, 1, 22);

				// Draw Divider
				for (uint8_t i = 9; i <= 120; i = i + 7) Console::Divider(VERTICAL, 3, i, 18);

				// Draw Divider
				Console::Divider(VERTICAL, 1, 121, 22);

				// Draw Corners
				Console::Text(1, 1, _Console_WHITE_, F("┌"));
				Console::Text(1, 121, _Console_WHITE_, F("┐"));
				Console::Text(23, 1, _Console_WHITE_, F("└"));
				Console::Text(23, 121, _Console_WHITE_, F("┘"));

				// Draw T
				for (uint8_t i = 3; i <= 21; i = i + 2) {
					
					// Draw T Start
					Console::Text(i, 1, _Console_WHITE_, F("├"));

					// Draw T End
					Console::Text(i, 121, _Console_WHITE_, F("┤"));

				}

				// Draw Cross Section
				for (uint8_t i = 5; i <= 19; i = i + 2) for (uint8_t j = 9; j <= 120; j = j + 7) Console::Text(i, j, _Console_WHITE_, F("┼"));

				// Draw T
				for (uint8_t i = 9; i <= 114; i = i + 7) {
					
					// Draw T Start
					Console::Text(3, i, _Console_WHITE_, F("┬"));

					// Draw T End
					Console::Text(21, i, _Console_WHITE_, F("┴"));

				}


				// Write Text
				Console::Text(2, 50, _Console_CYAN_, F("I2C Device Explorer"));
				Console::Text(22, 3, _Console_WHITE_, F("Total connected device :"));
				Console::Text(22, 86, _Console_WHITE_, F("Current Mux Channel [0-8] :"));
				Console::Text(24, 103, _Console_WHITE_, F("github.com/akkoyun"));

				// Declare Column Variable
				uint8_t _C = 0;

				// Print Column Headers
				for (uint8_t i = 6; i <= 21; i = i + 2) {
					
					// Print Column Headers
					Console::Text(i, 3, _Console_YELLOW_, F("0x"));
					Console::Text(i, 5, _Console_YELLOW_, String(_C, HEX));
					Console::Text(i, 6, _Console_YELLOW_, F("_"));
					
					// Increment Column
					_C++;

				}

				// Declare Row Variable
				uint8_t _R = 0;

				// Print Row Headers
				for (uint8_t i = 11; i <= 121; i = i + 7) {
					
					// Print Row Headers
					Console::Text(4, i, _Console_YELLOW_, F("0x_"));
					Console::Text(4, i + 3, _Console_YELLOW_, String(_R, HEX));

					// Increment Row
					_R++;

				}

			}

	};

	// Console Class
	class TH_Meter_Console : public Console {

		// Private Context
		public:

			// Class Constructor
			TH_Meter_Console(Stream &_Serial) : Console(_Serial) {


			}

			// TH Meter Batch Function.
			void Begin (void) {

				// Draw Main Screen
				Console::Box(1, 1, 8, 38, "HDC2010 T/H Sensor", 1, false, true);
				Console::Text(3, 3, _Console_WHITE_, F("Temperature..........[         C ]"));
				Console::Text(4, 3, _Console_WHITE_, F("Humidity.............[         % ]"));
				Console::Text(7, 3, _Console_WHITE_, F("Function Time............[    ms ]"));

			}

	};

	// Console Class
	class Voltmeter_Console : public Console {

		// Private Context
		public:

			// Class Constructor
			Voltmeter_Console(Stream &_Serial) : Console(_Serial) {


			}

			// Voltmeter Batch Function.
			void Begin (void) {

				// Draw Main Screen
				Console::Box(1, 1, 14, 84, "", 0, true, true);

				// Draw Voltage
				Console::Box(5, 3, 10, 28, "Phase R", 1, false, false);
				Console::Box(5, 30, 10, 55, "Phase S", 2, false, false);
				Console::Box(5, 57, 10, 82, "Phase T", 3, false, false);

				Console::Text(7, 5, _Console_WHITE_, F("VA_RMS......[       V]"));
				Console::Text(8, 5, _Console_WHITE_, F("VA_MIN......[       V]"));
				Console::Text(9, 5, _Console_WHITE_, F("VA_MAX......[       V]"));

				Console::Text(7, 32, _Console_WHITE_, F("VB_RMS......[       V]"));
				Console::Text(8, 32, _Console_WHITE_, F("VB_MIN......[       V]"));
				Console::Text(9, 32, _Console_WHITE_, F("VB_MAX......[       V]"));

				Console::Text(7, 59, _Console_WHITE_, F("VC_RMS......[       V]"));
				Console::Text(8, 59, _Console_WHITE_, F("VC_MIN......[       V]"));
				Console::Text(9, 59, _Console_WHITE_, F("VC_MAX......[       V]"));

			}

	};

	// Console Class
	class MAX78630_Console : public Console {

		// Private Context
		public:

			// Class Constructor
			MAX78630_Console(Stream &_Serial) : Console(_Serial) {


			}

			// MAX78630 Batch Function.
			void Begin (void) {

				// Draw Main Screen
				Console::Box(1, 1, 41, 160, "", 0, true, false);
				Console::Text(2, 68, _Console_WHITE_, F("MAX78630 Energy Analyzer"));

				// Draw Voltage
				Console::Box(5, 2, 13, 77, "Voltage", 1, false, false);
				Console::Text(7, 4, _Console_WHITE_, F("────────┬──────────┬──────────┬──────────┬──────────┬─────────┬─────────"));
				Console::Text(8, 12, _Console_WHITE_, F("│          │          │          │          │         │"));
				Console::Text(9, 12, _Console_WHITE_, F("│          │          │          │          │         │"));
				Console::Text(10, 12, _Console_WHITE_, F("│          │          │          │          │         │"));
				Console::Text(11, 12, _Console_WHITE_, F("│          │          │          │          │         │"));
				Console::Text(12, 4, _Console_WHITE_, F("────────┴──────────┴──────────┴──────────┴──────────┴─────────┴─────────"));
				Console::Text(8, 4, _Console_WHITE_, F("Phase R"));
				Console::Text(9, 4, _Console_WHITE_, F("Phase S"));
				Console::Text(10, 4, _Console_WHITE_, F("Phase T"));
				Console::Text(11, 4, _Console_WHITE_, F("Average"));
				Console::Text(6, 15, _Console_WHITE_, F("Instant"));
				Console::Text(6, 28, _Console_WHITE_, F("RMS"));
				Console::Text(6, 37, _Console_WHITE_, F("Fund."));
				Console::Text(6, 48, _Console_WHITE_, F("Harm."));
				Console::Text(6, 59, _Console_WHITE_, F("Offset"));
				Console::Text(6, 70, _Console_WHITE_, F("Gain"));
				Console::Text(11, 14, _Console_WHITE_, F("--------"));
				Console::Text(11, 36, _Console_WHITE_, F("--------"));
				Console::Text(11, 47, _Console_WHITE_, F("--------"));
				Console::Text(11, 58, _Console_WHITE_, F("-------"));
				Console::Text(11, 68, _Console_WHITE_, F("-------"));

				// Draw Current
				Console::Box(5, 78, 13, 159, "Current", 2, false, false);
				Console::Text(7, 80, _Console_WHITE_, F("────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────┬─────────"));
				Console::Text(8, 88, _Console_WHITE_, F("│         │         │         │         │         │         │"));
				Console::Text(9, 88, _Console_WHITE_, F("│         │         │         │         │         │         │"));
				Console::Text(10, 88, _Console_WHITE_, F("│         │         │         │         │         │         │"));
				Console::Text(11, 88, _Console_WHITE_, F("│         │         │         │         │         │         │"));
				Console::Text(12, 80, _Console_WHITE_, F("────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────┴─────────"));
				Console::Text(8, 80, _Console_WHITE_, F("Phase R"));
				Console::Text(9, 80, _Console_WHITE_, F("Phase S"));
				Console::Text(10, 80, _Console_WHITE_, F("Phase T"));
				Console::Text(11, 80, _Console_WHITE_, F("Average"));
				Console::Text(6, 90, _Console_WHITE_, F("Instant"));
				Console::Text(6, 101, _Console_WHITE_, F("Peak"));
				Console::Text(6, 112, _Console_WHITE_, F("RMS"));
				Console::Text(6, 121, _Console_WHITE_, F("Fund."));
				Console::Text(6, 131, _Console_WHITE_, F("Harm."));
				Console::Text(6, 141, _Console_WHITE_, F("Offset"));
				Console::Text(6, 152, _Console_WHITE_, F("Gain"));
				Console::Text(11, 90, _Console_WHITE_, F("-------"));
				Console::Text(11, 100, _Console_WHITE_, F("-------"));
				Console::Text(11, 120, _Console_WHITE_, F("-------"));
				Console::Text(11, 130, _Console_WHITE_, F("-------"));
				Console::Text(11, 140, _Console_WHITE_, F("-------"));
				Console::Text(11, 150, _Console_WHITE_, F("-------"));

				// Draw Power
				Console::Box(15, 2, 22, 132, "Power", 3, false, false);
				Console::Text(17, 4, _Console_WHITE_, F("────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬─────────┬─────────┬──────────"));
				Console::Text(18, 12, _Console_WHITE_, F("│          │          │          │          │          │          │          │          │         │         │"));
				Console::Text(19, 12, _Console_WHITE_, F("│          │          │          │          │          │          │          │          │         │         │"));
				Console::Text(20, 12, _Console_WHITE_, F("│          │          │          │          │          │          │          │          │         │         │"));
				Console::Text(21, 12, _Console_WHITE_, F("│          │          │          │          │          │          │          │          │         │         │"));
				Console::Text(18, 4, _Console_WHITE_, F("Phase R"));
				Console::Text(19, 4, _Console_WHITE_, F("Phase S"));
				Console::Text(20, 4, _Console_WHITE_, F("Phase T"));
				Console::Text(21, 4, _Console_WHITE_, F("Average"));
				Console::Text(16, 15, _Console_WHITE_, F("Active"));
				Console::Text(16, 25, _Console_WHITE_, F("ReActive"));
				Console::Text(16, 36, _Console_WHITE_, F("Apparent"));
				Console::Text(16, 49, _Console_WHITE_, F("Harm."));
				Console::Text(16, 60, _Console_WHITE_, F("Fund."));
				Console::Text(16, 69, _Console_WHITE_, F("Harm.R."));
				Console::Text(16, 80, _Console_WHITE_, F("Fund.R."));
				Console::Text(16, 92, _Console_WHITE_, F("VAFUND"));
				Console::Text(16, 102, _Console_WHITE_, F("Power F."));
				Console::Text(16, 112, _Console_WHITE_, F("P. Offs."));
				Console::Text(16, 123, _Console_WHITE_, F("Q. Offs."));
				Console::Text(21, 47, _Console_WHITE_, F("--------"));
				Console::Text(21, 58, _Console_WHITE_, F("--------"));
				Console::Text(21, 69, _Console_WHITE_, F("--------"));
				Console::Text(21, 80, _Console_WHITE_, F("--------"));
				Console::Text(21, 91, _Console_WHITE_, F("--------"));
				Console::Text(21, 113, _Console_WHITE_, F("-----"));
				Console::Text(21, 124, _Console_WHITE_, F("-----"));

				// Draw Device
				Console::Box(15, 133, 22, 159, "Device", 4, false, false);
				Console::Text(16, 135, _Console_WHITE_, F("Device Address:"));
				Console::Text(17, 135, _Console_WHITE_, F("Firmware      :"));
				Console::Text(18, 135, _Console_WHITE_, F("Baud          :"));
				Console::Text(19, 135, _Console_WHITE_, F("Temperature   :"));
				Console::Text(20, 135, _Console_WHITE_, F("VScale        :"));
				Console::Text(21, 135, _Console_WHITE_, F("IScale        :"));

				// Draw Min/Max Mask
				Console::Box(24, 2, 29, 104, "Min/Max Mask", 5, false, false);
				Console::Text(26, 4, _Console_WHITE_, F("──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────"));
				Console::Text(27, 14, _Console_WHITE_, F("│          │          │          │          │          │          │          │"));
				Console::Text(28, 14, _Console_WHITE_, F("│          │          │          │          │          │          │          │"));
				Console::Text(27, 4, _Console_WHITE_, F("Minimum"));
				Console::Text(28, 4, _Console_WHITE_, F("Maximum"));
				Console::Text(25, 17, _Console_WHITE_, F("Mask-0"));
				Console::Text(25, 28, _Console_WHITE_, F("Mask-1"));
				Console::Text(25, 39, _Console_WHITE_, F("Mask-2"));
				Console::Text(25, 50, _Console_WHITE_, F("Mask-3"));
				Console::Text(25, 61, _Console_WHITE_, F("Mask-4"));
				Console::Text(25, 72, _Console_WHITE_, F("Mask-5"));
				Console::Text(25, 83, _Console_WHITE_, F("Mask-6"));
				Console::Text(25, 94, _Console_WHITE_, F("Mask-7"));

				// Draw Other
				Console::Box(24, 105, 29, 123, "Other", 7, false, false);
				Console::Text(25, 107, _Console_WHITE_, F("STICKY......[ ]"));
				Console::Text(26, 107, _Console_WHITE_, F("FREQ....[     ]"));
				Console::Text(27, 107, _Console_WHITE_, F("BUCKET_L [    ]"));
				Console::Text(28, 107, _Console_WHITE_, F("BUCKET_H [    ]"));

				// Draw Status Limits
				Console::Box(30, 2, 34, 123, "Status Limits", 8, false, false);
				Console::Text(32, 4, _Console_WHITE_, F("────────┬───────────┬───────────┬──────────┬──────────┬──────────┬──────────┬────────┬───────┬───────┬────────┬───────"));
				Console::Text(33, 12, _Console_WHITE_, F("│           │           │          │          │          │          │        │       │       │        │"));
				Console::Text(33, 4, _Console_WHITE_, F("Limit"));
				Console::Text(31, 14, _Console_WHITE_, F("V_IMB_MAX"));
				Console::Text(31, 26, _Console_WHITE_, F("I_IMB_MAX"));
				Console::Text(31, 38, _Console_WHITE_, F("VRMS_MIN"));
				Console::Text(31, 49, _Console_WHITE_, F("VRMS_MAX"));
				Console::Text(31, 60, _Console_WHITE_, F("VSAG_LIM"));
				Console::Text(31, 71, _Console_WHITE_, F("IRMS_MAX"));
				Console::Text(31, 82, _Console_WHITE_, F("PF_MIN"));
				Console::Text(31, 91, _Console_WHITE_, F("T_MIN"));
				Console::Text(31, 99, _Console_WHITE_, F("T_MAX"));
				Console::Text(31, 107, _Console_WHITE_, F("F_MIN"));
				Console::Text(31, 116, _Console_WHITE_, F("F_MAX"));

				// Draw Status
				Console::Box(24, 124, 34, 159, "Status", 9, false, false);
				Console::Text(25, 126, _Console_WHITE_, F("OV_VRMSA....[ ]"));
				Console::Text(26, 126, _Console_WHITE_, F("UN_VRMSA....[ ]"));
				Console::Text(27, 126, _Console_WHITE_, F("OV_VRMSB....[ ]"));
				Console::Text(28, 126, _Console_WHITE_, F("UN_VRMSB....[ ]"));
				Console::Text(29, 126, _Console_WHITE_, F("OV_VRMSC....[ ]"));
				Console::Text(30, 126, _Console_WHITE_, F("UN_VRMSC....[ ]"));
				Console::Text(31, 126, _Console_WHITE_, F("OV_IRMSA....[ ]"));
				Console::Text(32, 126, _Console_WHITE_, F("OV_IRMSB....[ ]"));
				Console::Text(33, 126, _Console_WHITE_, F("OV_IRMSC....[ ]"));
				Console::Text(25, 144, _Console_WHITE_, F("OV_FREQ....[ ]"));
				Console::Text(26, 144, _Console_WHITE_, F("UN_FREQ....[ ]"));
				Console::Text(27, 144, _Console_WHITE_, F("UN_PFA.....[ ]"));
				Console::Text(28, 144, _Console_WHITE_, F("UN_PFB.....[ ]"));
				Console::Text(29, 144, _Console_WHITE_, F("UN_PFC.....[ ]"));
				Console::Text(30, 144, _Console_WHITE_, F("VA_SAG.....[ ]"));
				Console::Text(31, 144, _Console_WHITE_, F("VB_SAG.....[ ]"));
				Console::Text(32, 144, _Console_WHITE_, F("VC_SAG.....[ ]"));
				Console::Text(33, 144, _Console_WHITE_, F("V_IMBAL....[ ]"));

				// Draw Energy
				Console::Box(36, 2, 40, 159, "Energy Counter", 10, false, false);
				Console::Text(38, 4, _Console_WHITE_, F("────────┬──────────┬──────────┬──────────┬──────────┬──────────┬──────────┬────────────┬────────────┬────────────┬────────────┬────────────┬─────────────"));
				Console::Text(39, 12, _Console_WHITE_, F("│          │          │          │          │          │          │            │            │            │            │            │"));
				Console::Text(37, 15, _Console_WHITE_, F("WHA_POS"));
				Console::Text(37, 26, _Console_WHITE_, F("WHA_NEG"));
				Console::Text(37, 37, _Console_WHITE_, F("WHB_POS"));
				Console::Text(37, 48, _Console_WHITE_, F("WHB_NEG"));
				Console::Text(37, 59, _Console_WHITE_, F("WHC_POS"));
				Console::Text(37, 70, _Console_WHITE_, F("WHC_NEG"));
				Console::Text(37, 81, _Console_WHITE_, F("VARHA_POS"));
				Console::Text(37, 94, _Console_WHITE_, F("VARHA_NEG"));
				Console::Text(37, 107, _Console_WHITE_, F("VARHB_POS"));
				Console::Text(37, 120, _Console_WHITE_, F("VARHB_NEG"));
				Console::Text(37, 133, _Console_WHITE_, F("VARHC_POS"));
				Console::Text(37, 146, _Console_WHITE_, F("VARHC_NEG"));
				
			}

	};

	// Console Class
	class Analog_Pressure_Console : public Console {

		// Private Context
		public:

			// Class Constructor
			Analog_Pressure_Console(Stream &_Serial) : Console(_Serial) {


			}

			// Analog Pressure Meter
			void Begin (void) {

				// Draw Main Screen
				Console::Box(1, 1, 8, 38, "Analog P Sensor", 1, false, true);
				Console::Text(3, 3, _Console_WHITE_, F("Pressure...........[         Bar ]"));
				Console::Text(4, 3, _Console_WHITE_, F("Deviation..............[         ]"));
				Console::Text(7, 3, _Console_WHITE_, F("Function Time............[    ms ]"));

			}

	};

#endif /* defined(__Console__) */