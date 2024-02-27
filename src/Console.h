#ifndef __Console__
#define __Console__

	// Include Arduino Library
	#ifndef Arduino_h
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
			explicit Console(Stream &_Serial) {

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

			// Set Cursor Position Function.
			void Set_Cursor(const uint8_t _X, const uint8_t _Y) {

				// Control for Debug Mode
				#ifdef _DEBUG_

					// Print Cursor Position
					Console_Serial->print(F("\e["));
					Console_Serial->print(_X);
					Console_Serial->print(F(";"));
					Console_Serial->print(_Y);
					Console_Serial->print(F("H"));

				#endif

			}

			// Set Text Color Function.
			void Text_Color(const uint8_t _Color) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Control for Buffer
					if (_Color != this->Buffer.Text_Color) {

						// Print Cursor Position
						Console_Serial->print(F("\e["));
						Console_Serial->print(_Color);
						Console_Serial->print(F("m"));

						// Update Buffer Variable
						this->Buffer.Text_Color = _Color;

					}

				#endif

			}

			// Set Text Format Function
			void Text_Format(const uint8_t _Format) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Control for Buffer
					if (_Format != this->Buffer.Text_Format) {

						// Print Cursor Position
						Console_Serial->print(F("\e["));
						Console_Serial->print(_Format);
						Console_Serial->print(F("m"));

						// Update Buffer Variable
						this->Buffer.Text_Format = _Format;

					}

				#endif

			}

			// Set Back Ground Color Function.
			void Background_Color(const uint8_t _Color) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Control for Buffer
					if (_Color != this->Buffer.Background_Color) {

						// Print Cursor Position
						Console_Serial->print(F("\e["));
						Console_Serial->print((uint8_t)(_Color + 10));
						Console_Serial->print(F("m"));

						// Update Buffer Variable
						this->Buffer.Background_Color = _Color;

					}

				#endif

			}

			// Print Text to Specified Position and Color.
			void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const __FlashStringHelper * _Value) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Cursor Position
					this->Set_Cursor(_X, _Y); 

					// Set Text Color
					this->Text_Color(_Color); 

					// Print Text			
					Console_Serial->print(_Value);

				#endif

			}
			void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const char _Value) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Cursor Position
					this->Set_Cursor(_X, _Y); 

					// Set Text Color
					this->Text_Color(_Color); 

					// Print Text			
					Console_Serial->print(_Value);

				#endif

			}
			void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const char* _Value) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Cursor Position
					this->Set_Cursor(_X, _Y); 

					// Set Text Color
					this->Text_Color(_Color); 

					// Print Text			
					Console_Serial->print(_Value);

				#endif

			}
			template<typename T> void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, T _Value) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Cursor Position
					this->Set_Cursor(_X, _Y); 

					// Set Text Color
					this->Text_Color(_Color); 

					// Print Text			
					Console_Serial->print(_Value);

				#endif

			}

			// Draw Box Function.
			void Box(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2, const __FlashStringHelper * _Text, const uint8_t _Number = 0, const bool _Header = false, const bool _Footer = false) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Color
					this->Text_Color(_Console_WHITE_);

					// Set Text Format
					this->Text_Format(_Console_DIM_);

					// Print Corners
					this->Text(_X1, _Y1, _Console_WHITE_, F("┌"));
					this->Text(_X2, _Y1, _Console_WHITE_, F("└"));
					this->Text(_X1, _Y2, _Console_WHITE_, F("┐"));
					this->Text(_X2, _Y2, _Console_WHITE_, F("┘"));

					// Print Lines
					for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {

						// Print Lines
						this->Text(i, _Y1, _Console_WHITE_, F("│"));
						this->Text(i, _Y2, _Console_WHITE_, F("│"));

					}
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {

						// Print Lines
						this->Text(_X1, i, _Console_WHITE_, F("─"));
						this->Text(_X2, i, _Console_WHITE_, F("─"));

					}

					// Print Header
					this->Text(_X1, _Y1 + 2, _Console_YELLOW_, _Text);

					// Print Header Number

					// Print Header Number
					if (_Number > 0) {

						// Set Text Color
						this->Text_Color(_Console_GRAY_);

						// Set Cursor Position
						this->Set_Cursor(_X1, _Y2 - 5);

						// Print HEX
						Serial.printf(F("[%02hhu]"), _Number);

					}

					// Draw Header
					if (_Header) {

						// Print Corners
						this->Text(_X1 + 2, _Y1, _Console_WHITE_, F("├"));
						this->Text(_X1 + 2, _Y2, _Console_WHITE_, F("┤"));

						// Print Lines
						for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) this->Text(_X1 + 2, i, _Console_WHITE_, F("─"));

					}
					
					// Draw Footer			
					if (_Footer) {

						// Print Corners
						this->Text(_X2 - 2, _Y1, _Console_WHITE_, F("├"));
						this->Text(_X2 - 2, _Y2, _Console_WHITE_, F("┤"));

						// Print Lines
						for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) this->Text(_X2 - 2, i, _Console_WHITE_, F("─"));

					}

				#endif

			}

			// Horizontal Line Divider Function.
			void Divider(const bool _Type, const uint8_t _X, const uint8_t _Y, const uint8_t _Length, const bool _End = false) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Control Horizontal divider type
					if (_Type == HORIZONTAL) {

						// Print Corners
						if (_End) {

							// Print Corners
							this->Text(_X, _Y, _Console_WHITE_, F("├"));
							this->Text(_X, _Y + _Length, _Console_WHITE_, F("┤"));

						}

						// Print Line
						for (uint8_t i = _Y + 1; i <= _Y + _Length - 1; i++) {this->Text(_X, i, _Console_WHITE_, F("─"));}

					}

					// Control Vertical divider type
					if (_Type == VERTICAL) {

						// Print Corners
						if (_End) {

							// Print Corners
							this->Text(_X, _Y, _Console_WHITE_, F("┬"));
							this->Text(_X + _Length, _Y, _Console_WHITE_, F("┴"));

						}

						// Print Line
						for (uint8_t i = _X + 1; i <= _X + _Length - 1; i++) this->Text(i, _Y, _Console_WHITE_, F("│"));

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

			// Dot Space Function.
			void Space(const uint8_t _X, const uint8_t _Y, const uint8_t _Count) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print Dots
					for (uint8_t i = 0; i < _Count; i++) {

						// Print Dot
						this->Text(_X, _Y + i, _Console_GRAY_, F(" "));

					}

				#endif

			}

			// Bracket Place Holder Function.
			void Bracket(const uint8_t _X, const uint8_t _Y, const uint8_t _Size) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print Bracket Start
					this->Text(_X, _Y, _Console_WHITE_, F("["));

					// Print Bracket Left
					this->Text(_X, _Y + _Size, _Console_WHITE_, F("]"));

				#endif

			}

			// GSM Command Proccess
			void AT_Command(const __FlashStringHelper * _Command) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Declare Line Size
					uint8_t _Message_Size = 35;

					// Clear Line
					this->Space(_Console_AT_Status_X_, _Console_AT_Status_Y_, _Message_Size);

					// Print Dot
					this->Dot(_Console_AT_Status_X_, _Console_AT_Status_Y_ + sizeof(_Command), _Message_Size - sizeof(_Command) - 5);

					// Print Command
					this->Text(_Console_AT_Status_X_, _Console_AT_Status_Y_, _Console_WHITE_, _Command);

					// Print Response Wait Bracket
					this->Bracket(_Console_AT_Status_X_, _Console_AT_Status_Y_ + _Message_Size - 5, 5);

					// Print Response Wait Dot
					this->Text(_Console_AT_Status_X_, _Console_AT_Status_Y_ + _Message_Size - 4, _Console_BLUE_, F(" .. "));

				#endif

			}

			// OK Decide Function.
			void OK(const bool _Result) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print Command State
					if (_Result) {

						// Success
						this->Text(_Console_AT_Status_X_, _Console_AT_Status_Y_ + 32, _Console_GREEN_, F("OK"));

					} else {

						// Fail
						this->Text(_Console_AT_Status_X_, _Console_AT_Status_Y_ + 31, _Console_RED_, F("FAIL"));

					}

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

			// Print HEX Function
			void Print_HEX(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const uint8_t _Value) {

				// Set Text Color
				this->Text_Color(_Color);

				// Set Cursor Position
				this->Set_Cursor(_X, _Y);

				// Print HEX
				Serial.printf(F("0x%02X"), _Value);

			}
			void Print_HEX(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const uint16_t _Value) {

				// Set Text Color
				this->Text_Color(_Color);

				// Set Cursor Position
				this->Set_Cursor(_X, _Y);

				// Print HEX
				Serial.printf(F("0x%02X%02X"), (_Value >> 8), (_Value & 0xFF));

			}
			void Print_HEX(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const uint32_t _Value) {

				// Set Text Color
				this->Text_Color(_Color);

				// Set Cursor Position
				this->Set_Cursor(_X, _Y);

				// Print HEX
				Serial.printf(F("0x%02X%02X%02X%02X"), (_Value >> 24), (_Value >> 16), (_Value >> 8), (_Value & 0xFF));

			}

	};

	// Console Class
	class PowerStat_Console : public Console {

		// Public Context
		private:

			// Control for Debug Mode
			#ifdef _DEBUG_

				// Hardware Diagnostic Box Print Function.
				void Diagnostic(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw Hardware Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, F("Hardware Diagnostic"), 1, false, false);

					// Print Text
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("I2C RTC (0x52)")); 				Console::Dot(_X1 + 1, _Y1 + 16, (_Y2 - 7) - (_Y1 + 16)); 	Console::Bracket(_X1 + 1, _Y2 - 7, 5);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("I2C Serial ID (0x50)")); 		Console::Dot(_X1 + 2, _Y1 + 22, (_Y2 - 7) - (_Y1 + 22));	Console::Bracket(_X1 + 2, _Y2 - 7, 5);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("I2C Temperature (0x40)")); 		Console::Dot(_X1 + 3, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24));	Console::Bracket(_X1 + 3, _Y2 - 7, 5);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("I2C Battery Gauge (0x36)")); 	Console::Dot(_X1 + 4, _Y1 + 26, (_Y2 - 7) - (_Y1 + 26));	Console::Bracket(_X1 + 4, _Y2 - 7, 5);
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("I2C Battery Charger (0x6B)")); 	Console::Dot(_X1 + 5, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28));	Console::Bracket(_X1 + 5, _Y2 - 7, 5);
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Energy Analyser")); 			Console::Dot(_X1 + 6, _Y1 + 17, (_Y2 - 7) - (_Y1 + 17)); 	Console::Bracket(_X1 + 6, _Y2 - 7, 5);

				}

				// Detail Box Print Function.
				void Device_Detail(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw Hardware Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, F("Hardware Detail"), 2, false, false);

					// Print Text
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("Serial ID")); 			Console::Dot(_X1 + 1, _Y1 + 11, (_Y2 - 19) - (_Y1 + 11)); 	Console::Bracket(_X1 + 1, _Y2 - 19, 17);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Firmware Version")); 	Console::Dot(_X1 + 2, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	Console::Bracket(_X1 + 2, _Y2 - 11, 9);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("Hardware Version")); 	Console::Dot(_X1 + 3, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	Console::Bracket(_X1 + 3, _Y2 - 11, 9);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("Module Temperature")); 	Console::Dot(_X1 + 4, _Y1 + 20, (_Y2 - 10) - (_Y1 + 20)); 	Console::Bracket(_X1 + 4, _Y2 - 10, 8); Console::Text(_X1 + 4, _Y2 - 3, _Console_WHITE_, F("C"));
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Module Humidity")); 	Console::Dot(_X1 + 5, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	Console::Bracket(_X1 + 5, _Y2 - 10, 8); Console::Text(_X1 + 5, _Y2 - 3, _Console_WHITE_, F("%"));
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Send Interval"));		Console::Dot(_X1 + 6, _Y1 + 15, (_Y2 - 10) - (_Y1 + 15)); 	Console::Bracket(_X1 + 6, _Y2 - 10, 8); Console::Text(_X1 + 6, _Y2 - 5, _Console_WHITE_, F("Min"));

				}

				// Battery Print Function.
				void Battery(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw Hardware Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, F("Battery"), 3, false, false);

					// Print Text
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("Instant Voltage")); 			Console::Dot(_X1 + 1, _Y1 + 17, (_Y2 - 9) - (_Y1 + 17)); 	Console::Bracket(_X1 + 1, _Y2 - 9, 7);		Console::Text(_X1 + 1, _Y2 - 3, _Console_WHITE_, F("V"));
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Temperature")); 				Console::Dot(_X1 + 2, _Y1 + 13, (_Y2 - 10) - (_Y1 + 13)); 	Console::Bracket(_X1 + 2, _Y2 - 10, 8);		Console::Text(_X1 + 2, _Y2 - 3, _Console_WHITE_, F("C"));
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("Average Current")); 			Console::Dot(_X1 + 3, _Y1 + 17, (_Y2 - 13) - (_Y1 + 17)); 	Console::Bracket(_X1 + 3, _Y2 - 13, 11);	Console::Text(_X1 + 3, _Y2 - 4, _Console_WHITE_, F("mA"));
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("State of Charge")); 			Console::Dot(_X1 + 4, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	Console::Bracket(_X1 + 4, _Y2 - 10, 8);		Console::Text(_X1 + 4, _Y2 - 3, _Console_WHITE_, F("%"));
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Instant Battery Capacity"));	Console::Dot(_X1 + 5, _Y1 + 26, (_Y2 - 10) - (_Y1 + 26)); 	Console::Bracket(_X1 + 5, _Y2 - 10, 8);		Console::Text(_X1 + 5, _Y2 - 4, _Console_WHITE_, F("mA"));
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Charge State")); 				Console::Dot(_X1 + 6, _Y1 + 14, (_Y2 - 15) - (_Y1 + 14)); 	Console::Bracket(_X1 + 6, _Y2 - 15, 13);

				}

				// GSM Detail Function.
				void GSM_Hardware(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, F("GSM Detail"), 4, false, false);

					// Print Text	
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("Manufacturer"));	Console::Dot(_X1 + 1, _Y1 + 14, (_Y2 - 5) - (_Y1 + 14)); 	Console::Bracket(_X1 + 1, _Y2 - 5, 3);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Model"));			Console::Dot(_X1 + 2, _Y1 + 7, (_Y2 - 5) - (_Y1 + 7)); 		Console::Bracket(_X1 + 2, _Y2 - 5, 3);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("Firmware"));		Console::Dot(_X1 + 3, _Y1 + 10, (_Y2 - 12) - (_Y1 + 10)); 	Console::Bracket(_X1 + 3, _Y2 - 12, 10);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("IMEI"));			Console::Dot(_X1 + 4, _Y1 + 6, (_Y2 - 18) - (_Y1 + 6)); 	Console::Bracket(_X1 + 4, _Y2 - 18, 16);
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Serial ID"));		Console::Dot(_X1 + 5, _Y1 + 11, (_Y2 - 13) - (_Y1 + 11)); 	Console::Bracket(_X1 + 5, _Y2 - 13, 11);
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("ICCID"));			Console::Dot(_X1 + 6, _Y1 + 7, (_Y2 - 22) - (_Y1 + 7)); 	Console::Bracket(_X1 + 6, _Y2 - 22, 20);

				}

				// GSM Connection Detail Function.
				void GSM_Operator(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, F("GSM Connection"), 5, false, false);

					// Print Text	
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("Connection Time"));	Console::Dot(_X1 + 1, _Y1 + 17, (_Y2 - 8) - (_Y1 + 17)); 	Console::Bracket(_X1 + 1, _Y2 - 8, 6);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Signal Level"));	Console::Dot(_X1 + 2, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	Console::Bracket(_X1 + 2, _Y2 - 8, 6);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("GSM Operator"));	Console::Dot(_X1 + 3, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	Console::Bracket(_X1 + 3, _Y2 - 8, 6);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("IP Address"));		Console::Dot(_X1 + 4, _Y1 + 12, (_Y2 - 18) - (_Y1 + 12)); 	Console::Bracket(_X1 + 4, _Y2 - 18, 16);
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Connection Type"));	Console::Dot(_X1 + 5, _Y1 + 17, (_Y2 - 12) - (_Y1 + 17)); 	Console::Bracket(_X1 + 5, _Y2 - 12, 10);
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Socket"));			Console::Dot(_X1 + 6, _Y1 + 8, (_Y2 - 20) - (_Y1 + 8)); 	Console::Bracket(_X1 + 6, _Y2 - 20, 18);

				}

				// GSM FOTA
				void GSM_FOTA_Detail(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, F("FOTA"), 6, false, false);

					// Print Text	
					Console::Text(_X1 + 1, _Y1 + 2, _Console_WHITE_, F("File ID"));			Console::Dot(_X1 + 1, _Y1 + 9, (_Y2 - 16) - (_Y1 + 9)); 		Console::Bracket(_X1 + 1, _Y2 - 16, 14);
					Console::Text(_X1 + 2, _Y1 + 2, _Console_WHITE_, F("Download Status"));	Console::Dot(_X1 + 2, _Y1 + 17, (_Y2 - 7) - (_Y1 + 17)); 	Console::Bracket(_X1 + 2, _Y2 - 7, 5);
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("FTP File Size"));		Console::Dot(_X1 + 3, _Y1 + 15, (_Y2 - 10) - (_Y1 + 15)); 	Console::Bracket(_X1 + 3, _Y2 - 10, 8);
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("SD File Size"));		Console::Dot(_X1 + 4, _Y1 + 14, (_Y2 - 10) - (_Y1 + 14)); 	Console::Bracket(_X1 + 4, _Y2 - 10, 8);
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Download Percent"));	Console::Dot(_X1 + 5, _Y1 + 18, (_Y2 - 8) - (_Y1 + 18)); 	Console::Bracket(_X1 + 5, _Y2 - 8, 6);		Console::Text(_X1 + 5, _Y2 - 3, _Console_WHITE_, F("%"));
					Console::Text(_X1 + 6, _Y1 + 2, _Console_WHITE_, F("Download Time"));		Console::Dot(_X1 + 6, _Y1 + 15, (_Y2 - 11) - (_Y1 + 15)); 	Console::Bracket(_X1 + 6, _Y2 - 11, 9);		Console::Text(_X1 + 6, _Y2 - 5, _Console_WHITE_, F("Sec"));

				}

				// Pressure Stats
				void Pressure(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, F("Pressure"), 7, false, false);

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

				}

				// PowerStat V4 Publish Bit Table
				void Status_Detail(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2) {

					// Draw GSM Connection Diagnostic Box
					Console::Box(_X1, _Y1, _X2, _Y2, F(""), 0, false, false);

					// Print Header
					Console::Text(_X1 + 1, _Y1 + 23, _Console_WHITE_, F("S  CT CS CR -  II VI HF LF HI HV LV -  -  -  -  -  -  PR PD HP LP -  IN SA MP TH -  T  S  R  P"));

					// Print Divider
					Console::Divider(HORIZONTAL, _X1 + 2, _Y1 + 1, _Y2 - 4, false);

					// Print Text
					Console::Text(_X1 + 3, _Y1 + 2, _Console_WHITE_, F("Status")); 
					Console::Text(_X1 + 4, _Y1 + 2, _Console_WHITE_, F("Publish")); 
					Console::Text(_X1 + 5, _Y1 + 2, _Console_WHITE_, F("Stop")); 
					
					// Print HEX
					Console::Bracket(_X1 + 3, _Y1 + 10, 11);
					Console::Bracket(_X1 + 4, _Y1 + 10, 11);
					Console::Bracket(_X1 + 5, _Y1 + 10, 11);

					// Print Status Placeholder
					Console::Text(_X1 + 3, _Y1 + 23, _Console_GRAY_, F("X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X"));
					Console::Text(_X1 + 4, _Y1 + 23, _Console_GRAY_, F("X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X"));
					Console::Text(_X1 + 5, _Y1 + 23, _Console_GRAY_, F("X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X  X"));

				}

			#endif

		// Private Context
		public:

			// Class Constructor
			explicit PowerStat_Console(Stream &_Serial) : Console(_Serial) {}

			// PowerStat V4 Batch Function.
			void Begin(const uint8_t _X = 1, const uint8_t _Y = 1) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Start VT100 Console
					Console::Begin();

					// Draw Main Box
					Console::Box(_X, _Y, _X + 46, _Y + 121, F(""), 0, true, true);

					// Print Main Header Text
					Console::Text_Format(_Console_BRIGHT_);
					Console::Text(_X + 1, _Y + 54, _Console_WHITE_, F("PowerStat V4"));
					Console::Text_Format(_Console_RST_);

					// Header Titles
					Console::Text(_X + 1, _Y + 2, _Console_WHITE_, F("Up Time :"));
//					Console::Text(_X + 1, _Y + 98, _Console_WHITE_, F("Send Time (mS) :"));

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
					Console::Box(_X + 19, _Y + 1, _X + 21, _Y + 80, F(""), 0, false, false);
					Console::Box(_X + 19, _Y + 81, _X + 21, _Y + 120, F(""), 0, false, false);

					// JSON Box
					Console::Box(_X + 22, _Y + 1, _X + 30, _Y + 80, F("JSON"), 0, false, false);

					// Pressure Detail
					this->Pressure(_X + 22, _Y + 81, _X + 30, _Y + 120);

					// Draw Voltage Box
					Console::Box(_X + 31, _Y + 1, _X + 36, _Y + 40, F("Voltage"), 8, false, false);

					// Draw Current Box
					Console::Box(_X + 31, _Y + 41, _X + 36, _Y + 80, F("Current"), 9, false, false);

					// Draw Power Box
					Console::Box(_X + 31, _Y + 81, _X + 36, _Y + 120, F("Power"), 10, false, false);

					// Draw Mask
					this->Status_Detail(_X + 37, _Y + 1, _X + 43, _Y + 120);

					// Print Board Type
					#if defined(_B107AA_)
						Console::Text(_X + 45, _Y + 114, _Console_YELLOW_, F("B107AA"));
					#elif defined(_B108AA_)
						Console::Text(_X + 45, _Y + 114, _Console_YELLOW_, F("B108AA"));
					#endif

					// Print Interrupt Status Footer
					Console::Text(_X + 44, _Y + 70, _Console_WHITE_, F("┬")); Console::Text(_X + 45, _Y + 70, _Console_WHITE_, F("│")); Console::Text(_X + 46, _Y + 70, _Console_WHITE_, F("┴"));
					Console::Text(_X + 44, _Y + 80, _Console_WHITE_, F("┬")); Console::Text(_X + 45, _Y + 80, _Console_WHITE_, F("│")); Console::Text(_X + 46, _Y + 80, _Console_WHITE_, F("┴"));
					Console::Text(_X + 44, _Y + 90, _Console_WHITE_, F("┬")); Console::Text(_X + 45, _Y + 90, _Console_WHITE_, F("│")); Console::Text(_X + 46, _Y + 90, _Console_WHITE_, F("┴"));
					Console::Text(_X + 44, _Y + 100, _Console_WHITE_, F("┬")); Console::Text(_X + 45, _Y + 100, _Console_WHITE_, F("│")); Console::Text(_X + 46, _Y + 100, _Console_WHITE_, F("┴"));
					Console::Text(_X + 44, _Y + 112, _Console_WHITE_, F("┬")); Console::Text(_X + 45, _Y + 112, _Console_WHITE_, F("│")); Console::Text(_X + 46, _Y + 112, _Console_WHITE_, F("┴"));
					Console::Text(_X + 45, _Y + 72, _Console_WHITE_, F("EN1 [ ]"));
					Console::Text(_X + 45, _Y + 82, _Console_WHITE_, F("EN2 [ ]"));
					Console::Text(_X + 45, _Y + 92, _Console_WHITE_, F("ENV [ ]"));
					Console::Text(_X + 45, _Y + 102, _Console_WHITE_, F("RS485 [ ]"));

				#endif

			}

			// Set Status 
			void Show_Status(const uint8_t _Type, uint32_t _Register) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print HEX Value
					this->Print_HEX(40 + _Type, 13, _Console_GRAY_, _Register);

					// Print Bits
					if (bitRead(_Register, 0)) {Console::Text(40+_Type, 118, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 118, _Console_RED_, F("L"));}
					if (bitRead(_Register, 1)) {Console::Text(40+_Type, 115, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 115, _Console_RED_, F("L"));}
					if (bitRead(_Register, 2)) {Console::Text(40+_Type, 112, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 112, _Console_RED_, F("L"));}
					if (bitRead(_Register, 3)) {Console::Text(40+_Type, 109, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 109, _Console_RED_, F("L"));}
					if (bitRead(_Register, 4)) {Console::Text(40+_Type, 106, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 106, _Console_RED_, F("L"));}
					if (bitRead(_Register, 5)) {Console::Text(40+_Type, 103, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 103, _Console_RED_, F("L"));}
					if (bitRead(_Register, 6)) {Console::Text(40+_Type, 100, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 100, _Console_RED_, F("L"));}
					if (bitRead(_Register, 7)) {Console::Text(40+_Type, 97, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 97, _Console_RED_, F("L"));}
					if (bitRead(_Register, 8)) {Console::Text(40+_Type, 94, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 94, _Console_RED_, F("L"));}
					if (bitRead(_Register, 9)) {Console::Text(40+_Type, 91, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 91, _Console_RED_, F("L"));}
					if (bitRead(_Register, 10)) {Console::Text(40+_Type, 88, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 88, _Console_RED_, F("L"));}
					if (bitRead(_Register, 11)) {Console::Text(40+_Type, 85, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 85, _Console_RED_, F("L"));}
					if (bitRead(_Register, 12)) {Console::Text(40+_Type, 82, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 82, _Console_RED_, F("L"));}
					if (bitRead(_Register, 13)) {Console::Text(40+_Type, 79, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 79, _Console_RED_, F("L"));}
					if (bitRead(_Register, 14)) {Console::Text(40+_Type, 76, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 76, _Console_RED_, F("L"));}
					if (bitRead(_Register, 15)) {Console::Text(40+_Type, 73, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 73, _Console_RED_, F("L"));}
					if (bitRead(_Register, 16)) {Console::Text(40+_Type, 70, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 70, _Console_RED_, F("L"));}
					if (bitRead(_Register, 17)) {Console::Text(40+_Type, 67, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 67, _Console_RED_, F("L"));}
					if (bitRead(_Register, 18)) {Console::Text(40+_Type, 64, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 64, _Console_RED_, F("L"));}
					if (bitRead(_Register, 19)) {Console::Text(40+_Type, 61, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 61, _Console_RED_, F("L"));}
					if (bitRead(_Register, 20)) {Console::Text(40+_Type, 58, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 58, _Console_RED_, F("L"));}
					if (bitRead(_Register, 21)) {Console::Text(40+_Type, 55, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 55, _Console_RED_, F("L"));}
					if (bitRead(_Register, 22)) {Console::Text(40+_Type, 52, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 52, _Console_RED_, F("L"));}
					if (bitRead(_Register, 23)) {Console::Text(40+_Type, 49, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 49, _Console_RED_, F("L"));}
					if (bitRead(_Register, 24)) {Console::Text(40+_Type, 46, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 46, _Console_RED_, F("L"));}
					if (bitRead(_Register, 25)) {Console::Text(40+_Type, 43, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 43, _Console_RED_, F("L"));}
					if (bitRead(_Register, 26)) {Console::Text(40+_Type, 40, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 40, _Console_RED_, F("L"));}
					if (bitRead(_Register, 27)) {Console::Text(40+_Type, 37, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 37, _Console_RED_, F("L"));}
					if (bitRead(_Register, 28)) {Console::Text(40+_Type, 34, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 34, _Console_RED_, F("L"));}
					if (bitRead(_Register, 29)) {Console::Text(40+_Type, 31, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 31, _Console_RED_, F("L"));}
					if (bitRead(_Register, 30)) {Console::Text(40+_Type, 28, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 28, _Console_RED_, F("L"));}
					if (bitRead(_Register, 31)) {Console::Text(40+_Type, 25, _Console_GREEN_, F("H"));} else {Console::Text(40+_Type, 25, _Console_RED_, F("L"));}

				#endif

			}

			// Show Message
			void Show_Message(const uint8_t _Color, const __FlashStringHelper *_Message) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Clear Message Area
					Console::Space(_Console_Message_X_, _Console_Message_Y_, 75);

					// Print Message
					Console::Text(_Console_Message_X_, _Console_Message_Y_, _Color, _Message);

				#endif

			}
			void Show_Message(const uint8_t _Color, const char _Message) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Clear Message Area
					Console::Space(_Console_Message_X_, _Console_Message_Y_, 75);

					// Print Message
					Console::Text(_Console_Message_X_, _Console_Message_Y_, _Color, _Message);

				#endif

			}
			void Show_Message(const uint8_t _Color, const char * _Message) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Clear Message Area
					Console::Space(_Console_Message_X_, _Console_Message_Y_, 75);

					// Print Message
					Console::Text(_Console_Message_X_, _Console_Message_Y_, _Color, _Message);

				#endif

			}

			// Show RSSI
			void Show_RSSI(const uint8_t _X = 1, const uint8_t _Y = 1, const uint8_t _RSSI = 0) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Set Text Color
					this->Text_Color(_Console_WHITE_);

					// Set Cursor Position
					this->Set_Cursor(_X, _Y);

					// Print HEX
					Serial.printf(F("[-%3hhu]"), _RSSI);

				#endif

			}

			// Show Signal Quality
			void Show_Signal_Quality(const uint8_t _X = 1, const uint8_t _Y = 1, const uint8_t _Quality = 0) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print Signal Level Placeholder
					Console::Text(_X, _Y, _Console_GRAY_, F("_____"));

					// Print Signal Level Bar
					for (uint8_t i = 1; i <= _Quality; i++) Console::Text(_X, (_Y - 1) + i, _Console_GRAY_, F("X"));

				#endif

			}

			// Connection Type Function
			void Show_Connection_Type(const uint8_t _X = 1, const uint8_t _Y = 1, const uint8_t _Type = 0) {

				// Control for Debug Mode
			    #ifdef _DEBUG_

					// Print Connection Type
					if (_Type == 0) this->Text(_X, _Y, _Console_RED_, F("---"));
					else if (_Type == 1) this->Text(_X, _Y, _Console_GREEN_, F(" 2G"));
					else if (_Type == 2) this->Text(_X, _Y, _Console_GREEN_, F(" 3G"));
					else if (_Type == 3) this->Text(_X, _Y, _Console_GREEN_, F("LTE"));
					else if (_Type == 4) this->Text(_X, _Y, _Console_GREEN_, F("TDS"));

				#endif

			}

	};

#endif /* defined(__Console__) */