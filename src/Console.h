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

// Console Class
class Console {

	// Private Functions
	private:

		// Console Variables
		struct Console_Variable_Struct {
			
			// Char Type Variable
			uint8_t Char_Type = __Normal__;

			// Color Variable
			uint8_t Text_Color = Terminal_WHITE;
			uint8_t	BG_Color = Terminal_BLACK;

		} Variables;

	// Protected Functions
	protected:

		/**
		 * @brief Stream Variable.
		 */
		HardwareSerial * Console_Serial;

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

		// Normal char mode function.
		void Char_Type(const uint8_t _Type) {

			// Set Char Mode
			switch (_Type) {

				case __Normal__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __Normal__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_Normal__);

						// Set Variable
						this->Variables.Char_Type = __Normal__;

					}

					// End Switch
					break;

				}
				case __Bold__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __Bold__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_Bold__);

						// Set Variable
						this->Variables.Char_Type = __Bold__;

					}

					// End Switch
					break;

				}
				case __Low__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __Low__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_Low__);

						// Set Variable
						this->Variables.Char_Type = __Low__;

					}

					// End Switch
					break;

				}
				case __Italic__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __Italic__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_Italic__);

						// Set Variable
						this->Variables.Char_Type = __Italic__;

					}

					// End Switch
					break;

				}
				case __UnderLine__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __UnderLine__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_UnderLine__);

						// Set Variable
						this->Variables.Char_Type = __UnderLine__;

					}

					// End Switch
					break;

				}
				case __SlowBlink__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __SlowBlink__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_SlowBlink__);

						// Set Variable
						this->Variables.Char_Type = __SlowBlink__;

					}

					// End Switch
					break;

				}
				case __RapidBlink__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __RapidBlink__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_RapidBlink__);

						// Set Variable
						this->Variables.Char_Type = __RapidBlink__;

					}

					// End Switch
					break;

				}
				case __Reverse__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __Reverse__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_Reverse__);

						// Set Variable
						this->Variables.Char_Type = __Reverse__;

					}

					// End Switch
					break;

				}
				case __Hide__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __Hide__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_Hide__);

						// Set Variable
						this->Variables.Char_Type = __Hide__;

					}

					// End Switch
					break;

				}
				case __Overline__: {

					// Control for Char Type
					if (this->Variables.Char_Type != __Overline__) {

						// Set Char Mode
						Console_Serial->write(__ANSI_Char_OverLine__);

						// Set Variable
						this->Variables.Char_Type = __Overline__;

					}

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

			// Control for Text Color
			if (this->Variables.Text_Color != _Color) {

				// Set Text Color.
				Console_Serial->print(F("\033["));
				Console_Serial->print(_Color);
				Console_Serial->print(F("m"));

				// Set Variable
				this->Variables.Text_Color = _Color;

				// Flush
				Console_Serial->flush();

				// Command Delay
				delay(1);

			}

		}

		// Set Back Ground Color Function.
		void BG_Color(uint8_t _Color) {

			// Control for Back Ground Color
			if (this->Variables.BG_Color != _Color) {

				// Set Back Ground Color.
				Console_Serial->print(F("\033["));
				Console_Serial->print(_Color + 10);
				Console_Serial->write('m');

				// Set Variable
				this->Variables.BG_Color = _Color;

				// Flush
				Console_Serial->flush();

				// Command Delay
				delay(1);

			}

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
			if (_Wide < 36) _Wide = 36;

			// Draw Hardware Diagnostic
			this->Box(_X, _Y, (_X + 7), (_Y + _Wide), "GSM Details", 4, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Manufacturer"));	this->Dot(_X + 1, (_Y + 2 + 12), (_Wide - 2 - 4 - 12)); this->Bracket(_X + 1, _Y + _Wide - 4, 1);
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Model")); 		this->Dot(_X + 2, (_Y + 2 + 5), (_Wide - 2 - 4 - 5)); this->Bracket(_X + 2, _Y + _Wide - 4, 1);
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("Firmware")); 	this->Dot(_X + 3, (_Y + 2 + 8), (_Wide - 2 - 12 - 8)); this->Bracket(_X + 3, _Y + _Wide - 12, 9);
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("IMEI")); 		this->Dot(_X + 4, (_Y + 2 + 4), (_Wide - 2 - 18 - 4)); this->Bracket(_X + 4, _Y + _Wide - 18, 15);
			this->Set_Cursor(_X + 5, _Y + 2); Console_Serial->print(F("Serial ID")); 	this->Dot(_X + 5, (_Y + 2 + 9), (_Wide - 2 - 13 - 9)); this->Bracket(_X + 5, _Y + _Wide - 13, 10);
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("ICCID")); 		this->Dot(_X + 6, (_Y + 2 + 5), (_Wide - 2 - 22 - 5)); this->Bracket(_X + 6, _Y + _Wide - 22, 10);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Connection Box
		void Connection_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Hardware Diagnostic
			this->Box(_X, _Y, (_X + 7), (_Y + _Wide), "Connection Details", 5, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Connection Time"));		this->Dot(_X + 1, (_Y + 2 + 15), (_Wide - 2 - 7 - 15)); this->Bracket(_X + 1, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Signal Level")); 		this->Dot(_X + 2, (_Y + 2 + 12), (_Wide - 2 - 8 - 12)); this->Bracket(_X + 2, _Y + _Wide - 8, 5);
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("GSM Operator")); 		this->Dot(_X + 3, (_Y + 2 + 12), (_Wide - 2 - 8 - 12)); this->Bracket(_X + 3, _Y + _Wide - 8, 5);
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("IP Address")); 			this->Dot(_X + 4, (_Y + 2 + 10), (_Wide - 2 - 18 - 10)); this->Bracket(_X + 4, _Y + _Wide - 18, 15);
			this->Set_Cursor(_X + 5, _Y + 2); Console_Serial->print(F("LAC")); 					this->Dot(_X + 5, (_Y + 2 + 3), (_Wide - 2 - 7 - 3)); this->Bracket(_X + 5, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("Cell ID")); 				this->Dot(_X + 6, (_Y + 2 + 7), (_Wide - 2 - 7 - 7)); this->Bracket(_X + 6, _Y + _Wide - 7, 4);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// FOTA Box
		void FOTA_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Hardware Diagnostic
			this->Box(_X, _Y, (_X + 7), (_Y + _Wide), "FOTA", 6, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("File ID"));			this->Dot(_X + 1, (_Y + 2 + 7), (_Wide - 2 - 9 - 7)); this->Bracket(_X + 1, _Y + _Wide - 9, 6);
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Download Status")); 	this->Dot(_X + 2, (_Y + 2 + 15), (_Wide - 2 - 7 - 15)); this->Bracket(_X + 2, _Y + _Wide - 7, 4);
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("FTP File Size")); 	this->Dot(_X + 3, (_Y + 2 + 13), (_Wide - 2 - 10 - 13)); this->Bracket(_X + 3, _Y + _Wide - 10, 7);
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("SD File Size")); 	this->Dot(_X + 4, (_Y + 2 + 12), (_Wide - 2 - 10 - 12)); this->Bracket(_X + 4, _Y + _Wide - 10, 7);
			this->Set_Cursor(_X + 5, _Y + 2); Console_Serial->print(F("Download Percent")); this->Dot(_X + 5, (_Y + 2 + 16), (_Wide - 2 - 8 - 16)); this->Bracket(_X + 5, _Y + _Wide - 8, 5); this->Set_Cursor(_X + 5, _Y + _Wide - 3); Console_Serial->print(F("%"));
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("Download Time")); 	this->Dot(_X + 6, (_Y + 2 + 13), (_Wide - 2 - 11 - 13)); this->Bracket(_X + 6, _Y + _Wide - 11, 8); this->Set_Cursor(_X + 6, _Y + _Wide - 5); Console_Serial->print(F("Sec"));

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Status Box
		void Status_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Hardware Diagnostic
			this->Box(_X, _Y, (_X + 2), (_Y + _Wide), "", 0, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Device Status :"));

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Pressure Box
		void Pressure_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Pressure Box
			this->Box(_X, _Y, (_X + 8), (_Y + _Wide), "Pressure", 7, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Instant"));		this->Dot(_X + 1, (_Y + 2 + 7), (_Wide - 2 - 12 - 7)); this->Bracket(_X + 1, _Y + _Wide - 12, 9); this->Set_Cursor(_X + 1, _Y + _Wide - 5); Console_Serial->print(F("Bar"));
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Min")); 			this->Dot(_X + 2, (_Y + 2 + 3), (_Wide - 2 - 12 - 3)); this->Bracket(_X + 2, _Y + _Wide - 12, 9); this->Set_Cursor(_X + 2, _Y + _Wide - 5); Console_Serial->print(F("Bar"));
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("Max")); 			this->Dot(_X + 3, (_Y + 2 + 3), (_Wide - 2 - 12 - 3)); this->Bracket(_X + 3, _Y + _Wide - 12, 9); this->Set_Cursor(_X + 3, _Y + _Wide - 5); Console_Serial->print(F("Bar"));
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("Average")); 		this->Dot(_X + 4, (_Y + 2 + 7), (_Wide - 2 - 12 - 7)); this->Bracket(_X + 4, _Y + _Wide - 12, 9); this->Set_Cursor(_X + 4, _Y + _Wide - 5); Console_Serial->print(F("Bar"));
			this->Set_Cursor(_X + 5, _Y + 2); Console_Serial->print(F("Deviation")); 	this->Dot(_X + 5, (_Y + 2 + 9), (_Wide - 2 - 12 - 9)); this->Bracket(_X + 5, _Y + _Wide - 12, 9); this->Set_Cursor(_X + 5, _Y + _Wide - 5); Console_Serial->print(F("Bar"));
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("Slope")); 		this->Dot(_X + 6, (_Y + 2 + 5), (_Wide - 2 - 12 - 5)); this->Bracket(_X + 6, _Y + _Wide - 12, 9); this->Set_Cursor(_X + 6, _Y + _Wide - 3); Console_Serial->print(F("%"));
			this->Set_Cursor(_X + 7, _Y + 2); Console_Serial->print(F("Data Count"));	this->Dot(_X + 7, (_Y + 2 + 10), (_Wide - 2 - 8 - 10)); this->Bracket(_X + 7, _Y + _Wide - 8, 5);
 			this->Set_Cursor(_X + 1, _Y + _Wide - 20); Console_Serial->print(F("[    ]"));
 			this->Set_Cursor(_X + 2, _Y + _Wide - 20); Console_Serial->print(F("[    ]"));
 			this->Set_Cursor(_X + 3, _Y + _Wide - 20); Console_Serial->print(F("[    ]"));
 			this->Set_Cursor(_X + 6, _Y + _Wide - 20); Console_Serial->print(F("[    ]"));

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Voltage Box
		void Voltage_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Pressure Box
			this->Box(_X, _Y, (_X + 5), (_Y + _Wide), "Voltage", 8, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Phase R"));		this->Dot(_X + 1, (_Y + 2 + 7), (_Wide - 2 - 7 - 11)); this->Bracket(_X + 1, _Y + _Wide - 11, 8); this->Set_Cursor(_X + 1, _Y + _Wide - 3); Console_Serial->print(F("V"));
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Phase S"));		this->Dot(_X + 2, (_Y + 2 + 7), (_Wide - 2 - 7 - 11)); this->Bracket(_X + 2, _Y + _Wide - 11, 8); this->Set_Cursor(_X + 2, _Y + _Wide - 3); Console_Serial->print(F("V"));
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("Phase T"));		this->Dot(_X + 3, (_Y + 2 + 7), (_Wide - 2 - 7 - 11)); this->Bracket(_X + 3, _Y + _Wide - 11, 8); this->Set_Cursor(_X + 3, _Y + _Wide - 3); Console_Serial->print(F("V"));
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("Frequency"));	this->Dot(_X + 4, (_Y + 2 + 9), (_Wide - 2 - 9 - 11)); this->Bracket(_X + 4, _Y + _Wide - 11, 8); this->Set_Cursor(_X + 4, _Y + _Wide - 4); Console_Serial->print(F("Hz"));

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Current Box
		void Current_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Pressure Box
			this->Box(_X, _Y, (_X + 5), (_Y + _Wide), "Current", 8, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Phase R"));		this->Dot(_X + 1, (_Y + 2 + 7), (_Wide - 2 - 7 - 11)); this->Bracket(_X + 1, _Y + _Wide - 11, 8); this->Set_Cursor(_X + 1, _Y + _Wide - 3); Console_Serial->print(F("A"));
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Phase S"));		this->Dot(_X + 2, (_Y + 2 + 7), (_Wide - 2 - 7 - 11)); this->Bracket(_X + 2, _Y + _Wide - 11, 8); this->Set_Cursor(_X + 2, _Y + _Wide - 3); Console_Serial->print(F("A"));
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("Phase T"));		this->Dot(_X + 3, (_Y + 2 + 7), (_Wide - 2 - 7 - 11)); this->Bracket(_X + 3, _Y + _Wide - 11, 8); this->Set_Cursor(_X + 3, _Y + _Wide - 3); Console_Serial->print(F("A"));
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("Multiplier"));	this->Dot(_X + 4, (_Y + 2 + 10), (_Wide - 2 - 10 - 8)); this->Bracket(_X + 4, _Y + _Wide - 8, 5);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Power Box
		void Power_Detail(const uint8_t _X, const uint8_t _Y, uint8_t _Wide) {

			// Handle Wide
			if (_Wide < 36) _Wide = 36;

			// Draw Pressure Box
			this->Box(_X, _Y, (_X + 5), (_Y + _Wide), "Power", 8, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("Active Power"));		this->Dot(_X + 1, (_Y + 2 + 12), (_Wide - 2 - 12 - 11)); this->Bracket(_X + 1, _Y + _Wide - 11, 8);
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("Reactive Power"));	this->Dot(_X + 2, (_Y + 2 + 14), (_Wide - 2 - 14 - 11)); this->Bracket(_X + 2, _Y + _Wide - 11, 8);
			this->Set_Cursor(_X + 3, _Y + 2); Console_Serial->print(F("Apparent Power"));	this->Dot(_X + 3, (_Y + 2 + 14), (_Wide - 2 - 14 - 11)); this->Bracket(_X + 3, _Y + _Wide - 11, 8);
			this->Set_Cursor(_X + 4, _Y + 2); Console_Serial->print(F("Cos Fi"));			this->Dot(_X + 4, (_Y + 2 + 6), (_Wide - 2 - 6 - 8)); this->Bracket(_X + 4, _Y + _Wide - 8, 5);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Dot Print Function.
		void Dot(uint8_t _X, uint8_t _Y, uint8_t _Count) {

			for (uint8_t i = 0; i < _Count; i++) {

				this->Text(_X, _Y + i, GRAY, F("."));

			}

		}

	public:

		// Console Constructor
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

			// Reset Delay
			delay(1);

		}

};

// PowerStat Class
class PowerStat_Console : private Console {

	// Public Functions
	public:

		// PowerStat Constructor
		PowerStat_Console(HardwareSerial &_Serial) : Console(_Serial) {

		}

		// PowerStat Console Begin
		void Begin(void) {

			// Begin Console
			Console::Begin();

			// Draw Main Box
			Console::Box(1, 1, 44, 122, "", 0, true,true);

			// Print Uptime Header
			Console::Formatted_Text(2, 3, Terminal_WHITE, __Normal__, F("Up Time :"));

			// Print Header
			Console::Formatted_Text(2, 55, Terminal_WHITE, __Bold__, F("PowerStat V4"));

			// Draw Child Box
			Console::Hardware_Diagnostic(4, 2, 39);
			Console::Hardware_Detail(4, 42, 39);
			Console::Battery_Detail(4, 82, 39);

			// Draw Message Box
			Console::Box(13, 2, 15, 121, "", 0, false, false);

			// Draw GSM Box
			Console::GSM_Detail(16, 2, 39);
			Console::Connection_Detail(16, 42 ,39);
			Console::FOTA_Detail(16, 82, 39);

			// Draw JSON Box
			Console::Box(24, 2, 35, 81, "JSON", 0, false, false);

			// Draw Status Box
			Console::Status_Detail(24, 82, 39);

			// Draw Pressure Box
			Console::Pressure_Detail(27, 82, 39);

			// Draw Evergy
			Console::Voltage_Detail(36, 2, 39);
			Console::Current_Detail(36, 42, 39);
			Console::Power_Detail(36, 82, 39);

		}

		// Print UpTime
		void UpTime(void) {

			// Print Millis
			Console::Formatted_Text(2, 13, Terminal_MAGENTA, __Bold__, String(millis()));
			
		}

		// OK Decide Function.
		void OK_Decide(const bool _Result, const uint8_t _X, const uint8_t _Y) {

			// Print Command State
			if (_Result) {

				// Print OK 
				Console::Formatted_Text(_X, _Y, Terminal_GREEN, __Normal__, F(" OK "));

			} else {

				// Print Text
				Console::Formatted_Text(_X, _Y, Terminal_RED, __RapidBlink__, F("FAIL"));

			}
	
		}

		// Print Serial ID
		void Serial_ID(char * _Value) {

			// Print Text
			Console::Formatted_Text(5, 63, Terminal_GREEN, __Normal__, String(_Value));

		}

		// Print Version
		void Version(void) {

			// Print Text
			Console::Formatted_Text(6, 71, Terminal_GREEN, __Normal__, String(__Firmware__));
			Console::Formatted_Text(7, 71, Terminal_GREEN, __Normal__, String(__Hardware__));
			
		}

		// Print Environment
		void Environment(float _T, float _H) {

			// Clear Text
			Console::Formatted_Text(8, 72, Terminal_CYAN, __Normal__, F("     "));
			Console::Formatted_Text(9, 72, Terminal_CYAN, __Normal__, F("     "));

			// Print Text
			Console::Formatted_Text(8, 72, Terminal_CYAN, __Normal__, String(_T, 2));
			Console::Formatted_Text(9, 72, Terminal_CYAN, __Normal__, String(_H, 2));
			
		}

		// Print Interval Parameters
		void Interval(uint8_t _Online, uint8_t _Offline) {
			
			// Clear Text
			Console::Formatted_Text(10, 72, Terminal_CYAN, __Normal__, F("  "));
			Console::Formatted_Text(11, 72, Terminal_CYAN, __Normal__, F("  "));

			// Print Text
			Console::Formatted_Text(10, 72, Terminal_GREEN, __Normal__, String(_Online));
			Console::Formatted_Text(11, 72, Terminal_GREEN, __Normal__, String(_Offline));
		}

		// Print Battery Parameters
		void Battery(float _IV, float _T, float _IC, float _SOC, uint16_t _FB, uint16_t _IB, uint8_t _Charge) {

			// Clear Text
			Console::Set_Cursor(5, 113); Console::Console_Serial->print(F("    "));
			Console::Set_Cursor(6, 112); Console::Console_Serial->print(F("     "));
			Console::Set_Cursor(7, 110); Console::Console_Serial->print(F("       "));
			Console::Set_Cursor(8, 112); Console::Console_Serial->print(F("     "));
			Console::Set_Cursor(9, 112); Console::Console_Serial->print(F("    "));
			Console::Set_Cursor(10, 112); Console::Console_Serial->print(F("    "));
			Console::Set_Cursor(11, 105); Console::Console_Serial->print(F("              "));

			// Print Text
			Console::Formatted_Text(5, 113, Terminal_CYAN, __Normal__, String(_IV, 2));
			Console::Formatted_Text(6, 112, Terminal_CYAN, __Normal__, String(_T, 2));
			Console::Formatted_Text(7, 110, Terminal_CYAN, __Normal__, String(_IC, 2));
			Console::Formatted_Text(8, 112, Terminal_CYAN, __Normal__, String(_SOC, 2));
			Console::Formatted_Text(9, 112, Terminal_CYAN, __Normal__, String(_FB));
			Console::Formatted_Text(10, 112, Terminal_CYAN, __Normal__, String(_IB));

			// Print Charge Status
			switch (_Charge) {

				// Not Charging
				case 0: {

					// Print Text
					Console::Formatted_Text(11, 105, Terminal_RED, __Normal__, F("Not Charging  "));

					// End Switch
					break;

				}

				// Pre Charging
				case 1: {

					// Print Text
					Console::Formatted_Text(11, 105, Terminal_MAGENTA, __Normal__, F("Pre Charging  "));

					// End Switch
					break;

				}

				// Fast Charging
				case 2: {

					// Print Text
					Console::Formatted_Text(11, 105, Terminal_CYAN, __Normal__, F("Fast  Charging"));

					// End Switch
					break;

				}

				// Charge Done
				case 3: {

					// Print Text
					Console::Formatted_Text(11, 105, Terminal_GREEN, __Normal__, F("Charge Done   "));

					// End Switch
					break;

				}

				// Default
				default: {

					// End Switch
					break;

				}

			}

		}

		// Print Pump Status
		void Pump_Status(bool _Status) {

			// Clear Text
			Console::Set_Cursor(2, 103); Console::Console_Serial->print(F("                  "));

			// Print Pump Status
			if (_Status) Console::Formatted_Text(2, 103, Terminal_GREEN, __Bold__, F("    Pump is Active"));
			if (!_Status) Console::Formatted_Text(2, 103, Terminal_RED, __Bold__, F("Pump is Not Active"));

		}

		// Print Battery Parameters
		void GSM(uint8_t _Manufacturer, uint8_t _Model, uint16_t _Firmware_Segment1, uint16_t _Firmware_Segment2, uint16_t _Firmware_Segment3, char * _IMEI, uint32_t _Serial, char * _ICCID) {

			// Clear Text
			Console::Set_Cursor(17, 38); Console::Console_Serial->print(F(" "));
			Console::Set_Cursor(18, 38); Console::Console_Serial->print(F(" "));
			Console::Set_Cursor(19, 30); Console::Console_Serial->print(F("         "));
			Console::Set_Cursor(20, 24); Console::Console_Serial->print(F("               "));
			Console::Set_Cursor(21, 29); Console::Console_Serial->print(F("          "));
			Console::Set_Cursor(22, 20); Console::Console_Serial->print(F("                   "));

			// Print Text
			Console::Formatted_Text(17, 38, Terminal_CYAN, __Normal__, String(_Manufacturer));
			Console::Formatted_Text(18, 38, Terminal_CYAN, __Normal__, String(_Model));
			Console::Formatted_Text(20, 24, Terminal_CYAN, __Normal__, String(_IMEI));
			Console::Formatted_Text(21, 29, Terminal_CYAN, __Normal__, String(_Serial));
			Console::Formatted_Text(22, 20, Terminal_CYAN, __Normal__, String(_ICCID));

			// Declare Variable
			char _Firmware[10];

			// Handle TimeStamp
			sprintf(_Firmware, "%02d.%02d.%03d", _Firmware_Segment1, _Firmware_Segment2, _Firmware_Segment3);

			// Print Text
			Console::Formatted_Text(19, 30, Terminal_CYAN, __Normal__, String(_Firmware));

		}

		// Print Interval Parameters
		void Connection_Time(uint8_t _ConnTime) {

			// Declare Variable
			char _Connection[5];

			// Handle TimeStamp
			sprintf(_Connection, "%04d", _ConnTime);

			// Print Text
			Console::Formatted_Text(17, 75, Terminal_GREEN, __Normal__, String(_Connection));

		}

		// Print Signal Level
		void Signal_Level(uint8_t _dbm) {

			// Declare Variable
			char _Signal[4];

			// Handle TimeStamp
			sprintf(_Signal, "%03d", _dbm);

			// Print Text
			Console::Formatted_Text(18, 65, Terminal_GRAY, __Normal__, F("[-   ]"));
			Console::Formatted_Text(18, 67, Terminal_GRAY, __Normal__, String(_Signal));

			// Calculate Signal Level
			if (_dbm >= 51 and _dbm < 65) Console::Formatted_Text(18, 74, Terminal_GREEN, __Bold__, F("XXXXX"));
			if (_dbm >= 66 and _dbm < 77) Console::Formatted_Text(18, 74, Terminal_GREEN, __Normal__, F("XXXX_"));
			if (_dbm >= 78 and _dbm < 89) Console::Formatted_Text(18, 74, Terminal_GREEN, __Normal__, F("XXX__"));
			if (_dbm >= 90 and _dbm < 101) Console::Formatted_Text(18, 74, Terminal_YELLOW, __Normal__, F("XX___"));
			if (_dbm >= 102 and _dbm < 111) Console::Formatted_Text(18, 74, Terminal_YELLOW, __Normal__, F("X____"));
			if (_dbm >= 112 and _dbm < 113) Console::Formatted_Text(18, 74, Terminal_RED, __Normal__, F("_____"));

		}






};

#endif /* defined(__Console__) */