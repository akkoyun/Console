#ifndef __Console__
#define __Console__

// Define Arduino Library
#ifndef __Arduino__
	#include <Arduino.h>
#endif

// Set Defaults
#ifndef __Firmware__
	#define	__Firmware__	"00.00.00"
#endif
#ifndef __Hardware__
	#define	__Hardware__	"00.00.00"
#endif

// Include Definitions
#include "Console_Definitions.h"
#include "ANSI_Code.h"

class Console {

	// Private Functions
	private:

		/**
		 * @brief Stream Variable.
		 */
		HardwareSerial * Console_Serial;

		// Normal char mode function.
		void Char_Type(const uint8_t _Type) {

			// Set Char Mode
			switch (_Type) {

				case __Normal__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_Normal__);

					// End Switch
					break;

				}
				case __Bold__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_Bold__);

					// End Switch
					break;

				}
				case __Low__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_Low__);

					// End Switch
					break;

				}
				case __Italic__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_Italic__);

					// End Switch
					break;

				}
				case __UnderLine__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_UnderLine__);

					// End Switch
					break;

				}
				case __SlowBlink__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_SlowBlink__);

					// End Switch
					break;

				}
				case __RapidBlink__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_RapidBlink__);

					// End Switch
					break;

				}
				case __Reverse__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_Reverse__);

					// End Switch
					break;

				}
				case __Hide__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_Hide__);

					// End Switch
					break;

				}
				case __Overline__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Char_OverLine__);

					// End Switch
					break;

				}
				default: {

					// End Switch
					break;

				}

			}

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Clear functions
		void Clear(const uint8_t _Type) {

			// Set Clear Mode
			switch (_Type) {

				case __Clear_AfterLine__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Clear_AfterLine__);

					// End Switch
					break;

				}
				case __Clear_BeforeLine__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Clear_BeforeLine__);

					// End Switch
					break;

				}
				case __Clear_Line__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Clear_Line__);

					// End Switch
					break;

				}
				case __Clear_Screen__: {

					// Set Char Mode
					Console_Serial->write(__ANSI_Clear_Screen__);

					// End Switch
					break;

				}
				default: {

					// End Switch
					break;

				}

			}

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Change Cursor Visibility Function.
		void Cursor_Type(bool _State) {

			// Cursor On
			if (_State) Console_Serial->print(__ANSI_Cursor_ON__);	

			// Cursor Off
			if (!_State) Console_Serial->print(__ANSI_Cursor_OFF__);	

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Set Cursor Position Function.
		void Set_Cursor(const uint8_t _X, const uint8_t _Y) {

			// Set Cursor Position
			Console_Serial->print(F("\033["));
			Console_Serial->print(_X);
			Console_Serial->print(F(";"));
			Console_Serial->print(_Y);
			Console_Serial->print(F("H"));

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Set Text Color Function.
		void Text_Color(const uint8_t _Color) {

			// Set Text Color.
			Console_Serial->print(F("\033["));
			Console_Serial->print(_Color);
			Console_Serial->print(F("m"));

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Set Back Ground Color Function.
		void BG_Color(uint8_t _Color) {

			// Set Back Ground Color.
			Console_Serial->print(F("\e["));
			Console_Serial->print(_Color + 10);
			Console_Serial->write('m');

		}

		// Terminal Beep Sound Function.
		void Beep(void) {

			// Beep Terminal.
			Console_Serial->print(F("\x07"));

			// Command Delay
			delay(1);

		}

		// Print Text to Specified Position and Color.
		void Formatted_Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const uint8_t _Char, String _Value) {

			// Set Text Cursor Position
			this->Set_Cursor(_X, _Y); 

			// Set Char Type
			this->Char_Type(_Char);

			// Set Text Color
			this->Text_Color(_Color); 

			// Print Text			
			Console_Serial->print(String(_Value));

			// Set Char Type
			this->Char_Type(__Normal__);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(2);

		}

		// Print Text to Specified Position and Color.
		void Text(uint8_t _X, uint8_t _Y, uint8_t _Color, String _Value) {

			// Set Text Cursor Position
			this->Set_Cursor(_X, _Y); 

			// Set Text Color
			this->Text_Color(_Color); 

			// Print Text			
			Console_Serial->print(String(_Value));

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Bracket Place Holder Function.
		void Bracket(const uint8_t _X, const uint8_t _Y, const uint8_t _Space) {

			// Set Text Color
			this->Text_Color(Terminal_WHITE);

			// Set Cursor Position
			this->Set_Cursor(_X, _Y);

			// Print Bracket Start
			Console_Serial->print("[");

			// Set Cursor Position
			this->Set_Cursor(_X, _Y + _Space + 1);

			// Print Bracket Start
			Console_Serial->print("]");

		}

		// OK Decide Function.
		void OK_Decide(const bool _Result, const uint8_t _X, const uint8_t _Y) {

			// Print Command State
			if (_Result) {

				// Print OK 
				Text(_X, _Y, Terminal_GREEN, F(" OK "));

			} else {

				// Print FAIL
				Text(_X, _Y, Terminal_RED, F("FAIL"));

			}
	
		}

		// Draw Box Function.
		void Box(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2, const String _Text, const uint8_t _Number, const bool _Header, const bool _Footer) {

			// Set Text Color
			this->Text_Color(Terminal_WHITE); 

			// Set Char Type
			this->Char_Type(__Low__);

			// Set Print Corner
			this->Set_Cursor(_X1, _Y1); Console_Serial->print(F("┌")); 
			this->Set_Cursor(_X2, _Y1); Console_Serial->print(F("└")); 
			this->Set_Cursor(_X1, _Y2); Console_Serial->print(F("┐")); 
			this->Set_Cursor(_X2, _Y2); Console_Serial->print(F("┘")); 

			// Print Lines
			for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {

				// Set Cursor
				this->Set_Cursor(i, _Y1); 

				// Print Line
				Console_Serial->print(F("│")); 

				// Set Cursor
				this->Set_Cursor(i, _Y2); 

				// Print Line
				Console_Serial->print(F("│"));

			}
			for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {

				// Set Cursor
				this->Set_Cursor(_X1, i); 

				// Print Line
				Console_Serial->print(F("─")); 

				// Set Cursor
				this->Set_Cursor(_X2, i); 

				// Print Line
				Console_Serial->print(F("─"));

			}

			// Draw Header
			if (_Header) {

				// Print Corners
				this->Set_Cursor(_X1 + 2, _Y1); Console_Serial->print(F("├"));
				this->Set_Cursor(_X1 + 2, _Y2); Console_Serial->print(F("┤"));

				// Print Lines
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {

					// Set Cursor
					this->Set_Cursor(_X1 + 2, i); 
	
					// Print Line
					Console_Serial->print(F("─"));
	
				}

			}

			// Draw Footer			
			if (_Footer) {

				// Print Corners
				this->Set_Cursor(_X2 - 2, _Y1); Console_Serial->print(F("├"));
				this->Set_Cursor(_X2 - 2, _Y2); Console_Serial->print(F("┤"));

				// Print Lines
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {

					// Set Cursor
					this->Set_Cursor(_X2 - 2, i);

					// Print Line
					Console_Serial->print(F("─"));

				}

			}

			// Print Header
			this->Formatted_Text(_X1, _Y1 + 2, Terminal_YELLOW, __Normal__, String(_Text));

			// Print Header Number
			if (_Number != 0) {

				// Print Bracket
				this->Bracket(_X1, _Y2 - 4, 1); 

				// Set Cursor
				this->Set_Cursor(_X1, _Y2 - 3); 

				// Set Text Color
				this->Text_Color(Terminal_GRAY); 
				
				// Print Number
				Console_Serial->print(_Number);

			}

			// Set Text Color (White)
			this->Text_Color(Terminal_WHITE);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Hardware Diagnostic Box
		void Hardware_Diagnostic(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Hardware Diagnostic
			this->Box(_X, _Y, (_X + 8), (_Y + _Wide), "Hardware Diagnostic", 1, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("I2C Multiplexer (0x70)"));		this->Dot(_X + 1, (_Y + 2 + 22), (_Wide - 2 - 7 - 22)); this->Bracket(_X + 1, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("I2C RTC (0x52)")); 				this->Dot(_X + 2, (_Y + 2 + 14), (_Wide - 2 - 7 - 14)); this->Bracket(_X + 2, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("I2C Serial ID (0x50)")); 		this->Dot(_X + 3, (_Y + 2 + 20), (_Wide - 2 - 7 - 20)); this->Bracket(_X + 3, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("I2C Temperature (0x40)")); 		this->Dot(_X + 4, (_Y + 2 + 22), (_Wide - 2 - 7 - 22)); this->Bracket(_X + 4, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 5, _Y + 2); Console_Serial->print(F("I2C Battery Gauge (0x36)")); 	this->Dot(_X + 5, (_Y + 2 + 24), (_Wide - 2 - 7 - 24)); this->Bracket(_X + 5, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("I2C Battery Charger (0x6B)")); 	this->Dot(_X + 6, (_Y + 2 + 26), (_Wide - 2 - 7 - 26)); this->Bracket(_X + 6, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 7, _Y + 2); Console_Serial->print(F("SD Card Connection")); 			this->Dot(_X + 7, (_Y + 2 + 18), (_Wide - 2 - 7 - 18)); this->Bracket(_X + 7, _Y + _Wide - 7, 4);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Hardware Detail Box
		void Hardware_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Hardware Diagnostic
			this->Box(_X, _Y, (_X + 8), (_Y + _Wide), "Hardware Detail", 2, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Serial ID"));				this->Dot(_X + 1, (_Y + 2 + 9), (_Wide - 2 - 19 - 9)); this->Bracket(_X + 1, _Y + _Wide - 19, 16);
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Firmware Version")); 		this->Dot(_X + 2, (_Y + 2 + 16), (_Wide - 2 - 11 - 16)); this->Bracket(_X + 2, _Y + _Wide - 11, 8);
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("Hardware Version")); 		this->Dot(_X + 3, (_Y + 2 + 16), (_Wide - 2 - 11 - 16)); this->Bracket(_X + 3, _Y + _Wide - 11, 8);
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("Module Temperature")); 		this->Dot(_X + 4, (_Y + 2 + 18), (_Wide - 2 - 10 - 18)); this->Bracket(_X + 4, _Y + _Wide - 10, 7); this->Set_Cursor(_X + 4, _Y + _Wide - 3); Console_Serial->print(F("C"));
			this->Set_Cursor(_X + 5, _Y + 2); Console_Serial->print(F("Module Humidity")); 			this->Dot(_X + 5, (_Y + 2 + 15), (_Wide - 2 - 10 - 15)); this->Bracket(_X + 5, _Y + _Wide - 10, 7); this->Set_Cursor(_X + 5, _Y + _Wide - 3); Console_Serial->print(F("%"));
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("Online Send Interval")); 	this->Dot(_X + 6, (_Y + 2 + 20), (_Wide - 2 - 10 - 20)); this->Bracket(_X + 6, _Y + _Wide - 10, 7); this->Set_Cursor(_X + 6, _Y + _Wide - 5); Console_Serial->print(F("Min"));
			this->Set_Cursor(_X + 7, _Y + 2); Console_Serial->print(F("Offline Send Interval"));	this->Dot(_X + 7, (_Y + 2 + 21), (_Wide - 2 - 10 - 21)); this->Bracket(_X + 7, _Y + _Wide - 10, 7); this->Set_Cursor(_X + 7, _Y + _Wide - 5); Console_Serial->print(F("Min"));

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Battery Box
		void Battery_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Hardware Diagnostic
			this->Box(_X, _Y, (_X + 8), (_Y + _Wide), "Battery", 3, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Instant Voltage"));			this->Dot(_X + 1, (_Y + 2 + 15), (_Wide - 2 - 9 - 15)); this->Bracket(_X + 1, _Y + _Wide - 9, 6); this->Set_Cursor(_X + 1, _Y + _Wide - 3); Console_Serial->print(F("V"));
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Temperature")); 				this->Dot(_X + 2, (_Y + 2 + 11), (_Wide - 2 - 10 - 11)); this->Bracket(_X + 2, _Y + _Wide - 10, 7); this->Set_Cursor(_X + 2, _Y + _Wide - 3); Console_Serial->print(F("C"));
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("Average Current")); 			this->Dot(_X + 3, (_Y + 2 + 15), (_Wide - 2 - 12 - 15)); this->Bracket(_X + 3, _Y + _Wide - 12, 9); this->Set_Cursor(_X + 3, _Y + _Wide - 4); Console_Serial->print(F("mA"));
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("State of Charge")); 			this->Dot(_X + 4, (_Y + 2 + 15), (_Wide - 2 - 9 - 15)); this->Bracket(_X + 4, _Y + _Wide - 10, 7); this->Set_Cursor(_X + 4, _Y + _Wide - 3); Console_Serial->print(F("%"));
			this->Set_Cursor(_X + 5, _Y + 2); Console_Serial->print(F("Full Battery Capacity")); 	this->Dot(_X + 5, (_Y + 2 + 21), (_Wide - 2 - 9 - 21)); this->Bracket(_X + 5, _Y + _Wide - 10, 7); this->Set_Cursor(_X + 5, _Y + _Wide - 4); Console_Serial->print(F("mA"));
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("Instant Battery Capacity")); this->Dot(_X + 6, (_Y + 2 + 24), (_Wide - 2 - 9 - 24)); this->Bracket(_X + 6, _Y + _Wide - 10, 7); this->Set_Cursor(_X + 6, _Y + _Wide - 4); Console_Serial->print(F("mA"));
			this->Set_Cursor(_X + 7, _Y + 2); Console_Serial->print(F("Charge State"));				this->Dot(_X + 7, (_Y + 2 + 12), (_Wide - 2 - 16 - 12)); this->Bracket(_X + 7, _Y + _Wide - 17, 14);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// GSM Box
		void GSM_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 75) _Wide = 75;

			// Draw Hardware Diagnostic
			this->Box(_X, _Y, (_X + 7), (_Y + _Wide), "GSM Details", 4, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Manufacturer"));			this->Dot(_X + 1, (_Y + 2 + 12), (_Wide - 2 - 43 - 12)); this->Bracket(_X + 1, _Y + _Wide - 43, 1);
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Model"));				this->Dot(_X + 2, (_Y + 2 + 5), (_Wide - 2 - 43 - 5)); this->Bracket(_X + 2, _Y + _Wide - 43, 1);
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("Firmware"));				this->Dot(_X + 3, (_Y + 2 + 8), (_Wide - 2 - 51 - 8)); this->Bracket(_X + 3, _Y + _Wide - 51, 9);
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("IMEI"));					this->Dot(_X + 4, (_Y + 2 + 4), (_Wide - 2 - 57 - 4)); this->Bracket(_X + 4, _Y + _Wide - 57, 15);
			this->Set_Cursor(_X + 5, _Y + 2); Console_Serial->print(F("Serial ID"));			this->Dot(_X + 5, (_Y + 2 + 9), (_Wide - 2 - 52 - 9)); this->Bracket(_X + 5, _Y + _Wide - 52, 10);
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("ICCID"));				this->Dot(_X + 6, (_Y + 2 + 5), (_Wide - 2 - 61 - 5)); this->Bracket(_X + 6, _Y + _Wide - 61, 19);
			this->Set_Cursor(_X + 1, _Y + 41); Console_Serial->print(F("GSM Connection Time"));	this->Dot(_X + 1, (_Y + 41 + 19), (_Wide - 2 - 46 - 19)); this->Bracket(_X + 1, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 2, _Y + 41); Console_Serial->print(F("Signal Level"));		this->Dot(_X + 2, (_Y + 41 + 12), (_Wide - 2 - 46 - 12)); this->Bracket(_X + 2, _Y + _Wide - 8, 5);
			this->Set_Cursor(_X + 3, _Y + 41); Console_Serial->print(F("GSM Operator"));		this->Dot(_X + 3, (_Y + 41 + 12), (_Wide - 2 - 46 - 12)); this->Bracket(_X + 3, _Y + _Wide - 8, 5);
			this->Set_Cursor(_X + 4, _Y + 41); Console_Serial->print(F("IP Address"));			this->Dot(_X + 4, (_Y + 41 + 10), (_Wide - 2 - 46 - 21)); this->Bracket(_X + 4, _Y + _Wide - 18, 15);
			this->Set_Cursor(_X + 5, _Y + 41); Console_Serial->print(F("LAC"));					this->Dot(_X + 5, (_Y + 41 + 3), (_Wide - 2 - 46 - 3)); this->Bracket(_X + 5, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 6, _Y + 41); Console_Serial->print(F("Cell ID"));				this->Dot(_X + 6, (_Y + 41 + 7), (_Wide - 2 - 46 - 7)); this->Bracket(_X + 6, _Y + _Wide - 7, 4);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}









		/**
		 * @brief Draw Box Function.
		 * @version 01.00.00
		 * @param _X1 Upper Left Corner X.
		 * @param _Y1 Upper Left Corner Y.
		 * @param _X2 Lower Right Corner X.
		 * @param _Y2 Lower Right Corner Y.
		 * @param _Text Header Text.
		 * @param _Number Box Number.
		 * @param _Header Box Header.
		 * @param _Footer Box Footer.
		 */
		void Draw_Box(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2, String _Text, uint8_t _Number, bool _Header, bool _Footer) {

			// Set Text Color
			this->Text_Color(WHITE);

			// Set Text Format
			Console_Serial->print(F("\e["));
			Console_Serial->print(DIM);
			Console_Serial->write('m');

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

		/**
		 * @brief Dot Print Function.
		 * @version 01.00.00
		 * @param _X Cursor X Position
		 * @param _Y Cursor Y Position
		 * @param _Count Dot Length
		 */
		void Dot(uint8_t _X, uint8_t _Y, uint8_t _Count) {

			for (uint8_t i = 0; i < _Count; i++) {

				this->Text(_X, _Y + i, GRAY, F("."));

			}

		}

		/**
		 * @brief Horizontal Line Divider Function.
		 * @version 01.00.00
		 * @param _X1 Start Cursor X
		 * @param _Y1 Start Cursor Y
		 * @param _Length Length
		 * @param _End End Symbol
		 */
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

		/**
		 * @brief Vertical Line Divider Function.
		 * @version 01.00.00
		 * @param _X1 Start Cursor X
		 * @param _Y1 Start Cursor Y
		 * @param _Length Length
		 * @param _End End Symbol
		 */
		void Vertical_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length) {

			//Set Color
			Text_Color(WHITE);

			// Print Corners
			Set_Cursor(_X1, _Y1); Console_Serial->println(F("┬"));
			Set_Cursor(_X1 + _Length, _Y1); Console_Serial->println(F("┴"));

			// Print Lines
			for (uint8_t i = _X1 + 1; i <= _X1 + _Length - 1; i++) {Set_Cursor(i, _Y1); Console_Serial->println(F("│"));}

		}

	public:

		/**
		 * @brief Construct a new Console object
		 * @version 01.00.00
		 */
		Console(HardwareSerial &_Serial) {

			//Set serial port
			this->Console_Serial = &_Serial;

		}

		// Begin Serial VT100 Console.
		void Begin(void) {

			// Start Serial
			Console_Serial->begin(115200);

			// Cursor Off
			this->Cursor_Type(false);

			// Clear Screen
			this->Clear(__Clear_Screen__);

			// Set Char Type
			this->Char_Type(__Normal__);

			// Draw Main Box
			this->Box(1, 1, 41, 122, "", 0, true,true);

			// Draw Child Box
			this->Hardware_Diagnostic(4, 2, 39);
			this->Hardware_Detail(4, 42, 39);
			this->Battery_Detail(4, 82, 39);

			// Draw Message Box
			this->Box(13, 2, 15, 121, "", 0, false, false);

			// Draw GSM Box
			this->GSM_Detail(16, 2, 79);

			// Reset Delay
			delay(1);

		}

		// Print UpTime
		void UpTime(void) {

			// Print Millis
			this->Formatted_Text(2, 13, CYAN, __Bold__, String(millis()));
			
		}

		// Print Serial ID
		void Serial_ID(char * _Value) {

			// Print Text
			this->Formatted_Text(5, 63, Terminal_GREEN, __Normal__, String(_Value));

		}

		// Print Version
		void Firmware(void) {

			// Print Text
			this->Formatted_Text(6, 71, Terminal_GREEN, __Normal__, String(__Firmware__));
			
		}
		void Hardware(void) {

			// Print Text
			this->Formatted_Text(7, 71, Terminal_GREEN, __Normal__, String(__Hardware__));
			
		}

		// Print Environment
		void Temperature(float _Value) {

			// Clear Text
			this->Formatted_Text(8, 72, Terminal_CYAN, __Normal__, F("     "));

			// Print Text
			this->Formatted_Text(8, 72, Terminal_CYAN, __Normal__, String(_Value, 2));
			
		}
		void Humidity(float _Value) {

			// Clear Text
			this->Formatted_Text(9, 72, Terminal_CYAN, __Normal__, F("     "));

			// Print Text
			this->Formatted_Text(9, 72, Terminal_CYAN, __Normal__, String(_Value, 2));

		}

		// Print Interval Parameters
		void OnlineInterval(uint8_t _Value) {

			// Clear Text
			this->Formatted_Text(10, 72, Terminal_CYAN, __Normal__, F("  "));

			// Print Text
			this->Formatted_Text(10, 72, Terminal_GREEN, __Normal__, String(_Value));
			
		}
		void OfflineInterval(uint8_t _Value) {

			// Clear Text
			this->Formatted_Text(11, 72, Terminal_CYAN, __Normal__, F("  "));

			// Print Text
			this->Formatted_Text(11, 72, Terminal_GREEN, __Normal__, String(_Value));
			
		}

		// Print Battery Parameters
		void Battery(float _IV, float _T, float _IC, float _SOC, uint16_t _FB, uint16_t _IB) {

			// Print Voltage
			this->Battery_Voltage(_IV);

			// Print Temperature
			this->Battery_Temperature(_T);

			// Print Current
			this->Battery_Current(_IC);

			// Print SOC
			this->Battery_SOC(_SOC);

			// Print Full Bat Cap
			this->Battery_FB(_FB);

			// Print Instabt Bat Cap
			this->Battery_IB(_IB);

		}
		void Battery_Voltage(float _Value) {

			// Clear Text
			this->Formatted_Text(5, 113, Terminal_CYAN, __Normal__, F("    "));

			// Print Text
			this->Formatted_Text(5, 113, Terminal_CYAN, __Normal__, String(_Value, 2));
			
		}
		void Battery_Temperature(float _Value) {

			// Clear Text
			this->Formatted_Text(6, 112, Terminal_CYAN, __Normal__, F("     "));

			// Print Text
			this->Formatted_Text(6, 112, Terminal_CYAN, __Normal__, String(_Value, 2));
			
		}
		void Battery_Current(float _Value) {

			// Clear Text
			this->Formatted_Text(7, 110, Terminal_CYAN, __Normal__, F("       "));

			// Print Text
			this->Formatted_Text(7, 110, Terminal_CYAN, __Normal__, String(_Value, 2));
			
		}
		void Battery_SOC(float _Value) {

			// Clear Text
			this->Formatted_Text(8, 112, Terminal_CYAN, __Normal__, F("     "));

			// Print Text
			this->Formatted_Text(8, 112, Terminal_CYAN, __Normal__, String(_Value, 2));
			
		}
		void Battery_FB(uint16_t _Value) {

			// Clear Text
			this->Formatted_Text(9, 112, Terminal_CYAN, __Normal__, F("    "));

			// Print Text
			this->Formatted_Text(9, 112, Terminal_CYAN, __Normal__, String(_Value));
			
		}
		void Battery_IB(uint16_t _Value) {

			// Clear Text
			this->Formatted_Text(10, 112, Terminal_CYAN, __Normal__, F("    "));

			// Print Text
			this->Formatted_Text(10, 112, Terminal_CYAN, __Normal__, String(_Value));
			
		}

		// Print Pump Status
		void Pump_Status(bool _Status) {

			//Pump is Not Active

			// Clear Text
			this->Formatted_Text(2, 103, Terminal_CYAN, __Normal__, F("                  "));

			// Print Pump Status
			if (_Status) this->Formatted_Text(2, 103, Terminal_GREEN, __Bold__, F("    Pump is Active"));
			if (!_Status) this->Formatted_Text(2, 103, Terminal_RED, __Bold__, F("Pump is Not Active"));

		}

};

#endif /* defined(__Console__) */