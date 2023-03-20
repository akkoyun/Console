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
#include "ANSI_Code.h"
#include "Data_Struct.h"

// Console Class
class Console {

	// Private Functions
	private:

		// Console Variables
		struct Console_Variable_Struct {
			
			// Char Type Variable
			unsigned char Char_Type = 0;

			// Color Variable
			unsigned char Text_Color = 0;
			unsigned char	BG_Color = 0;

		} Variables;

	// Protected Functions
	protected:

		/**
		 * @brief Stream Variable.
		 */
		HardwareSerial * Console_Serial;

		// Clear functions
		void Clear(const unsigned char _Type) {

			// Set Char Mode
			Console_Serial->print((char)27);
			Console_Serial->print((char)91);
			Console_Serial->print(_Type);
			if (_Type != 3) Console_Serial->print((char)75);
			if (_Type == 3) Console_Serial->print((char)74);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Normal char mode function.
		void Char_Type(const unsigned char _Type) {

			// Control for Char Type
			if (this->Variables.Char_Type != _Type) {

				// Set Char Mode
				Console_Serial->print((char)27);
				Console_Serial->print((char)91);
				Console_Serial->print(_Type);
				Console_Serial->print((char)109);

				// Flush
				Console_Serial->flush();

				// Command Delay
				delay(1);

				// Set Variable
				this->Variables.Char_Type = _Type;

			}

		}

		// Change Cursor Visibility Function.
		void Cursor_Type(const bool _State) {

			// Print Command
			Console_Serial->print((char)27);
			Console_Serial->print((char)91);
			Console_Serial->print((char)63);
			Console_Serial->print((char)50);
			Console_Serial->print((char)53);

			// Set Cursor Visibility
			if (_State) Console_Serial->print((char)104);
			if (!_State) Console_Serial->print((char)108);

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Set Cursor Position Function.
		void Set_Cursor(const unsigned char _X, const unsigned char _Y) {

			// Print Command
			Console_Serial->print((char)27); // ESC
			Console_Serial->print((char)91); // [
			Console_Serial->print(_X); // X
			Console_Serial->print((char)59); // ;
			Console_Serial->print(_Y); // Y
			Console_Serial->print((char)72); // H

			// Flush
			Console_Serial->flush();

			// Command Delay
			delay(1);

		}

		// Set Text Color Function.
		void Text_Color(const unsigned char _Color) {

			// Control for Text Color
			if (this->Variables.Text_Color != _Color) {

				// Set Text Color.
				Console_Serial->print((char)27); // ESC
				Console_Serial->print((char)91); // [
				Console_Serial->print(_Color);
				Console_Serial->print((char)109); // m

				// Flush
				Console_Serial->flush();

				// Command Delay
				delay(1);

				// Set Variable
				this->Variables.Text_Color = _Color;

			}

		}

		// Set Back Ground Color Function.
		void BG_Color(uint8_t _Color) {

			// Control for Back Ground Color
			if (this->Variables.BG_Color != _Color) {

				// Set Text Color.
				Console_Serial->print((char)27); // ESC
				Console_Serial->print((char)91); // [
				Console_Serial->print(_Color + 10);
				Console_Serial->print((char)109); // m

				// Flush
				Console_Serial->flush();

				// Command Delay
				delay(1);

				// Set Variable
				this->Variables.BG_Color = _Color;

			}

		}

		// Terminal Beep Sound Function.
		void Beep(void) {

			// Beep Terminal.
			Console_Serial->print((char)7);

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
			this->Char_Type(Terminal_Normal);

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
			this->Char_Type(Terminal_Low);

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
			this->Formatted_Text(_X1, _Y1 + 2, Terminal_YELLOW, Terminal_Normal, String(_Text));

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
			this->Set_Cursor(_X + 6, _Y + 2); Console_Serial->print(F("ICCID")); 		this->Dot(_X + 6, (_Y + 2 + 5), (_Wide - 2 - 22 - 5)); this->Bracket(_X + 6, _Y + _Wide - 22, 19);

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
			this->Box(_X, _Y, (_X + 3), (_Y + _Wide), "", 0, false, false);

			// Print Texts
			this->Set_Cursor(_X + 1, _Y + 2); Console_Serial->print(F("S:"));
			this->Set_Cursor(_X + 2, _Y + 2); Console_Serial->print(F("P:"));

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

				this->Text(_X, _Y + i, Terminal_GRAY, F("."));

			}

		}

		// uint64 to String Converter Function
		char* Number2HexString(char* _Output, unsigned char* _Input, size_t _Length) {
				char* ptr = _Output;
				for (int i = _Length-1; i >= 0 ; i--)
					ptr += sprintf(ptr, "%02X", _Input[i]);
				return ptr;
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
			this->Clear(Terminal_Clear_Screen);

			// Set Char Type
			this->Char_Type(Terminal_Normal);

			// Reset Text Color
			this->Text_Color(Terminal_WHITE);

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
			Console::Box(1, 1, 45, 122, "", 0, true,true);

			// Print Uptime Header
			Console::Formatted_Text(2, 3, Terminal_WHITE, Terminal_Normal, F("Up Time :"));

			// Print Header
			Console::Formatted_Text(2, 55, Terminal_WHITE, Terminal_Bold, F("PowerStat V4"));

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
			Console::Box(24, 2, 36, 81, "JSON", 0, false, false);

			// Draw Status Box
			Console::Status_Detail(24, 82, 39);

			// Draw Pressure Box
			Console::Pressure_Detail(28, 82, 39);

			// Draw Evergy
			Console::Voltage_Detail(37, 2, 39);
			Console::Current_Detail(37, 42, 39);
			Console::Power_Detail(37, 82, 39);

		}

		// Print UpTime
		void UpTime(void) {

			// Print Millis
			Console::Formatted_Text(2, 13, Terminal_BLUE, Terminal_Bold, String(millis()));
			
		}

		// OK Decide Function.
		void OK_Decide(const bool _Result, const uint8_t _X, const uint8_t _Y) {

			// Print Command State
			if (_Result) {

				// Print OK 
				Console::Formatted_Text(_X, _Y, Terminal_GREEN, Terminal_Normal, F(" OK "));

			} else {

				// Print Text
				Console::Formatted_Text(_X, _Y, Terminal_RED, Terminal_RapidBlink, F("FAIL"));

			}
	
		}

		// Hardware Diagnostic
		void Hardware_Diagnostic(uint8_t _Status) {

			// Diagnostics
			Console::Formatted_Text(5, 35, (bitRead(_Status, 0) == true ? Terminal_GREEN : Terminal_RED), (bitRead(_Status, 0) == true ? Terminal_Normal : Terminal_RapidBlink), (bitRead(_Status, 0) == true ? F(" OK ") : F("FAIL")));
			Console::Formatted_Text(6, 35, (bitRead(_Status, 1) == true ? Terminal_GREEN : Terminal_RED), (bitRead(_Status, 1) == true ? Terminal_Normal : Terminal_RapidBlink), (bitRead(_Status, 1) == true ? F(" OK ") : F("FAIL")));
			Console::Formatted_Text(7, 35, (bitRead(_Status, 2) == true ? Terminal_GREEN : Terminal_RED), (bitRead(_Status, 2) == true ? Terminal_Normal : Terminal_RapidBlink), (bitRead(_Status, 2) == true ? F(" OK ") : F("FAIL")));
			Console::Formatted_Text(8, 35, (bitRead(_Status, 3) == true ? Terminal_GREEN : Terminal_RED), (bitRead(_Status, 3) == true ? Terminal_Normal : Terminal_RapidBlink), (bitRead(_Status, 3) == true ? F(" OK ") : F("FAIL")));
			Console::Formatted_Text(9, 35, (bitRead(_Status, 4) == true ? Terminal_GREEN : Terminal_RED), (bitRead(_Status, 4) == true ? Terminal_Normal : Terminal_RapidBlink), (bitRead(_Status, 4) == true ? F(" OK ") : F("FAIL")));
			Console::Formatted_Text(10, 35, (bitRead(_Status, 5) == true ? Terminal_GREEN : Terminal_RED), (bitRead(_Status, 5) == true ? Terminal_Normal : Terminal_RapidBlink), (bitRead(_Status, 5) == true ? F(" OK ") : F("FAIL")));
			Console::Formatted_Text(11, 35, (bitRead(_Status, 6) == true ? Terminal_GREEN : Terminal_RED), (bitRead(_Status, 6) == true ? Terminal_Normal : Terminal_RapidBlink), (bitRead(_Status, 6) == true ? F(" OK ") : F("FAIL")));

		}

		// Print Serial ID
		void Serial_ID(char * _Value) {

			// Print Text
			Console::Formatted_Text(5, 63, Terminal_GREEN, Terminal_Normal, String(_Value));

		}

		// Print Version
		void Version(void) {

			// Print Text
			Console::Formatted_Text(6, 71, Terminal_GREEN, Terminal_Normal, String(__Firmware__));
			Console::Formatted_Text(7, 71, Terminal_GREEN, Terminal_Normal, String(__Hardware__));
			
		}

		// Print Environment
		void Environment(float _T, float _H) {

			// Clear Text
			Console::Formatted_Text(8, 72, Terminal_CYAN, Terminal_Normal, F("     "));
			Console::Formatted_Text(9, 72, Terminal_CYAN, Terminal_Normal, F("     "));

			// Print Text
			Console::Formatted_Text(8, 72, Terminal_CYAN, Terminal_Normal, String(_T, 2));
			Console::Formatted_Text(9, 72, Terminal_CYAN, Terminal_Normal, String(_H, 2));
			
		}

		// Print Interval Parameters
		void Interval(uint8_t * _Online, uint8_t * _Offline) {
			
			// Set Char
			Console::Char_Type(Terminal_Normal);

			// Set Color
			Console::Text_Color(Terminal_CYAN);

			// Declare Variable
			char _Online_Interval[4];
			char _Offline_Interval[4];

			// Handle Interval
			sprintf(_Online_Interval, "%03d", *((uint8_t*)_Online));
			sprintf(_Offline_Interval, "%03d", *((uint8_t*)_Offline));

			// Print Text
			Console::Set_Cursor(10, 72); Console::Console_Serial->print(_Online_Interval);
			Console::Set_Cursor(11, 72); Console::Console_Serial->print(_Offline_Interval);

		}

		// Print Battery Parameters
		void Battery(Battery_Struct* _Bat) {

			// Print Text
			Console::Formatted_Text(5, 113, Terminal_CYAN, Terminal_Normal, String(_Bat->IV, 2));
			Console::Formatted_Text(6, 112, Terminal_CYAN, Terminal_Normal, String(_Bat->T, 2));
			Console::Formatted_Text(7, 110, Terminal_CYAN, Terminal_Normal, String(_Bat->IC, 2));
			Console::Formatted_Text(8, 112, Terminal_CYAN, Terminal_Normal, String(_Bat->SOC, 2));
			Console::Formatted_Text(9, 112, Terminal_CYAN, Terminal_Normal, String(_Bat->FB));
			Console::Formatted_Text(10, 112, Terminal_CYAN, Terminal_Normal, String(_Bat->IB));

			// Print Charge Status
			switch (_Bat->Charge) {

				// Not Charging
				case 0: {

					// Print Text
					Console::Formatted_Text(11, 105, Terminal_RED, Terminal_Normal, F("Not Charging  "));

					// End Switch
					break;

				}

				// Pre Charging
				case 1: {

					// Print Text
					Console::Formatted_Text(11, 105, Terminal_MAGENTA, Terminal_Normal, F("Pre Charging  "));

					// End Switch
					break;

				}

				// Fast Charging
				case 2: {

					// Print Text
					Console::Formatted_Text(11, 105, Terminal_CYAN, Terminal_Normal, F("Fast  Charging"));

					// End Switch
					break;

				}

				// Charge Done
				case 3: {

					// Print Text
					Console::Formatted_Text(11, 105, Terminal_GREEN, Terminal_Normal, F("Charge Done   "));

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
			if (_Status) Console::Formatted_Text(2, 103, Terminal_GREEN, Terminal_Bold, F("    Pump is Active"));
			if (!_Status) Console::Formatted_Text(2, 103, Terminal_RED, Terminal_Bold, F("Pump is Not Active"));

		}

		// Print Battery Parameters
		void GSM(GSM_Init_Struct* _GSM_Init) {

			// Print Text
			Console::Formatted_Text(17, 38, Terminal_CYAN, Terminal_Normal, String(_GSM_Init->Manufacturer));
			Console::Formatted_Text(18, 38, Terminal_CYAN, Terminal_Normal, String(_GSM_Init->Model));
			Console::Formatted_Text(20, 24, Terminal_CYAN, Terminal_Normal, String(_GSM_Init->IMEI));
			Console::Formatted_Text(21, 29, Terminal_CYAN, Terminal_Normal, String(_GSM_Init->Serial));
			Console::Formatted_Text(22, 20, Terminal_CYAN, Terminal_Normal, String(_GSM_Init->ICCID));

			// Handle Firmware
			char _Formatted_Firmware[10];
			sprintf(_Formatted_Firmware, "%02d.%02d.%03d", _GSM_Init->Firmware_1, _GSM_Init->Firmware_2, _GSM_Init->Firmware_3);
			Console::Formatted_Text(19, 30, Terminal_CYAN, Terminal_Normal, String(_Formatted_Firmware));

		}

		// Print Interval Parameters
		void Connection_Time(uint8_t * _ConnTime) {

			// Declare Variable
			char _Connection[5];

			// Handle TimeStamp
			sprintf(_Connection, "%04d", *((uint8_t*)_ConnTime));

			// Print Text
			Console::Formatted_Text(17, 75, Terminal_CYAN, Terminal_Normal, String(_Connection));

		}

		// Print Signal Level
		void Signal_Level(uint8_t * _dbm) {

			// Declare Variable
			char _Signal[4];

			// Handle TimeStamp
			sprintf(_Signal, "%03d", *((uint8_t*)_dbm));

			// Print Text
			Console::Formatted_Text(18, 65, Terminal_WHITE, Terminal_Normal, F("[-   ]"));
			Console::Formatted_Text(18, 67, Terminal_CYAN, Terminal_Normal, String(_Signal));

			// Calculate Signal Level
			if (*((uint8_t*)_dbm) >= 51 and *((uint8_t*)_dbm) < 65) {

				// Print Signal Bar
				Console::Formatted_Text(18, 74, Terminal_GREEN, Terminal_Bold, F("XXXXX"));

			} else if (*((uint8_t*)_dbm) >= 66 and *((uint8_t*)_dbm) < 77) {

				// Print Signal Bar
				Console::Formatted_Text(18, 74, Terminal_GREEN, Terminal_Normal, F("XXXX_"));

			} else if (*((uint8_t*)_dbm) >= 78 and *((uint8_t*)_dbm) < 89) {

				// Print Signal Bar
				Console::Formatted_Text(18, 74, Terminal_GREEN, Terminal_Normal, F("XXX__"));

			} else if (*((uint8_t*)_dbm) >= 90 and *((uint8_t*)_dbm) < 101) {

				// Print Signal Bar
				Console::Formatted_Text(18, 74, Terminal_YELLOW, Terminal_Normal, F("XX___"));

			} else if (*((uint8_t*)_dbm) >= 102 and *((uint8_t*)_dbm) < 111) {

				// Print Signal Bar
				Console::Formatted_Text(18, 74, Terminal_YELLOW, Terminal_Normal, F("X____"));

			} else if (*((uint8_t*)_dbm) >= 112 and *((uint8_t*)_dbm) < 113) {

				// Print Signal Bar
				Console::Formatted_Text(18, 74, Terminal_RED, Terminal_Normal, F("_____"));

			}

		}

		// Print Operator
		void Operator(uint16_t * _Operator) {

			// Clear Text
			Console::Set_Cursor(19, 74); Console::Console_Serial->print(F("     "));

			// Print Operator
			Console::Formatted_Text(19, 74, Terminal_CYAN, Terminal_Normal, String(*((uint16_t*)_Operator)));

		}

		// Print IP Address
		void IP_Address(uint8_t _Segment_1, uint8_t _Segment_2, uint8_t _Segment_3, uint8_t _Segment_4) {

			// Handle IP
			char _IP[16];
			sprintf(_IP, "%03d.%03d.%03d.%03d", _Segment_1, _Segment_2, _Segment_3, _Segment_4);
			Console::Formatted_Text(20, 64, Terminal_CYAN, Terminal_Normal, String(_IP));

		}

		// Print Operator
		void Location(uint16_t * _LAC, uint16_t * _CellID) {

			// Set Char
			Console::Char_Type(Terminal_Normal);

			// Set Color
			Console::Text_Color(Terminal_CYAN);

			// Clear Text
			Console::Set_Cursor(21, 75); Console::Console_Serial->print(F("    "));
			Console::Set_Cursor(22, 75); Console::Console_Serial->print(F("    "));

			// Print Text
			Console::Set_Cursor(21, 75); Console::Console_Serial->print((*((uint16_t*)_LAC)), HEX);
			Console::Set_Cursor(22, 75); Console::Console_Serial->print((*((uint16_t*)_CellID)), HEX);

		}

		// Print Pressure
		void Pressure(Pressure_Struct* _Pressure, float _MinLimit, float _MaxLimit, float _Slope, float _SlopeLimit) {

			// Set Text Color
			Console::Text_Color(Terminal_CYAN);

			// Set Char Type
			Console::Char_Type(Terminal_Normal);

			// Print Pressure Value
			Console::Set_Cursor(30, 110); Console::Console_Serial->print(String(_Pressure->Min, 3));
			Console::Set_Cursor(31, 110); Console::Console_Serial->print(String(_Pressure->Max, 3));
			Console::Set_Cursor(32, 110); Console::Console_Serial->print(String(_Pressure->Average, 3));
			Console::Set_Cursor(33, 110); Console::Console_Serial->print(String(_Pressure->Deviation, 3));
			Console::Set_Cursor(35, 114); Console::Console_Serial->print(String(_Pressure->DataCount));
			Console::Set_Cursor(30, 102); Console::Console_Serial->print(String(_MinLimit, 2));
			Console::Set_Cursor(31, 102); Console::Console_Serial->print(String(_MaxLimit, 2));

			// Control for High Pressure
			if (_Pressure->Instant <= 1) {

				// Set Text Color
				Console::Text_Color(Terminal_RED);

				// Set Char Type
				Console::Char_Type(Terminal_RapidBlink);

				// Print Pressure Value
				Console::Set_Cursor(29, 102); Console::Console_Serial->print(F(" LOW"));

				// Print Pressure Value
				Console::Set_Cursor(29, 110); Console::Console_Serial->print(String(_Pressure->Instant, 3));

			} else if (_Pressure->Instant >= 2) {

				// Set Text Color
				Console::Text_Color(Terminal_RED);

				// Set Char Type
				Console::Char_Type(Terminal_RapidBlink);

				// Print Pressure Value
				Console::Set_Cursor(29, 102); Console::Console_Serial->print(F("HIGH"));

				// Print Pressure Value
				Console::Set_Cursor(29, 110); Console::Console_Serial->print(String(_Pressure->Instant, 3));

			} else if (_Pressure->Instant > 1 and _Pressure->Instant < 2) {

				// Set Text Color
				Console::Text_Color(Terminal_CYAN);

				// Set Char Type
				Console::Char_Type(Terminal_Normal);

				// Print Pressure Value
				Console::Set_Cursor(29, 102); Console::Console_Serial->print(F("    "));

				// Print Pressure Value
				Console::Set_Cursor(29, 110); Console::Console_Serial->print(String(_Pressure->Instant, 3));

			}


			// Control for Slope Limit
			if (_Slope >= _SlopeLimit) {

				// Set Text Color
				Console::Text_Color(Terminal_RED);

				// Set Char Type
				Console::Char_Type(Terminal_RapidBlink);

				// Print Pressure Value
				Console::Set_Cursor(34, 102); Console::Console_Serial->print(F("RISE"));

				// Print Pressure Slope
				Console::Set_Cursor(34, 110); Console::Console_Serial->print(String(_Slope, 5));

			} else if (_Slope <= (-1 * _SlopeLimit)) {

				// Set Text Color
				Console::Text_Color(Terminal_RED);

				// Set Char Type
				Console::Char_Type(Terminal_RapidBlink);

				// Print Pressure Value
				Console::Set_Cursor(34, 102); Console::Console_Serial->print(F("DROP"));

				// Print Pressure Slope
				Console::Set_Cursor(34, 110); Console::Console_Serial->print(String(_Slope, 5));

			} else {

				// Set Text Color
				Console::Text_Color(Terminal_CYAN);

				// Set Char Type
				Console::Char_Type(Terminal_Normal);

				// Print Pressure Value
				Console::Set_Cursor(34, 102); Console::Console_Serial->print(F("    "));

				// Print Pressure Slope
				Console::Set_Cursor(34, 110); Console::Console_Serial->print(String(_Slope, 5));

			}

		}

		// Print Operator
		void Status(uint32_t _Status, uint32_t _Publish) {

			// Set Char
			Console::Char_Type(Terminal_Normal);

			// Set Color
			Console::Text_Color(Terminal_CYAN);

			// Handle Status Text
			Console::Set_Cursor(25, 87); Console::Console_Serial->print(_Status, BIN);
			Console::Set_Cursor(26, 87); Console::Console_Serial->print(_Publish, BIN);

		}







};

#endif /* defined(__Console__) */