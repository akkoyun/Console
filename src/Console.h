#ifndef __Console__
#define __Console__

// Define Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif

typedef enum {
	BLACK	            = 30,
	RED		            = 31,
	GREEN	            = 32,
	YELLOW	            = 33,
	BLUE	            = 34,
	MAGENTA	            = 35,
	CYAN	            = 36,
	WHITE	            = 37,
	GRAY	            = 90
} Colors;

typedef enum {
	RST			        = 0,
	BRIGHT		        = 1,
	DIM			        = 2,
	UNDERSCORE	        = 4,
	BLINK		        = 5,
	REVERSE		        = 7,
	HIDDEN		        = 8	
} TextFormat;

class Console {

	private:

		enum Clear_Type {
			LINE_AFTER_CURSOR 	= 0,
			LINE_TO_CURSOR 		= 1,
			LINE 		    	= 2,
			SCREEN 			    = 3,
			ALL 			    = 4
		};

		Stream *_Console;

		/**
		 * @brief Draw Box Function.
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
			Text_Color(WHITE);

			// Set Text Format
			_Console->print(F("\e["));
			_Console->print(DIM);
			_Console->write('m');

			// Print Corners
			Set_Cursor(_X1, _Y1); _Console->println(F("┌"));
			Set_Cursor(_X2, _Y1); _Console->println(F("└"));
			Set_Cursor(_X1, _Y2); _Console->println(F("┐"));
			Set_Cursor(_X2, _Y2); _Console->println(F("┘"));

			// Print Lines
			for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {
				
				Set_Cursor(i, _Y1); _Console->println(F("│"));
				Set_Cursor(i, _Y2); _Console->println(F("│"));

			}
			for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
				
				Set_Cursor(_X1, i); _Console->println(F("─"));
				Set_Cursor(_X2, i); _Console->println(F("─"));
				
			}

			// Print Header
			Text_Color(YELLOW); Set_Cursor(_X1, _Y1 + 2); _Console->println(_Text);

			// Print Header Number
			if (_Number != 0) {
				Text_Color(WHITE); Set_Cursor(_X1, _Y2 - 4); _Console->println(F("[ ]"));
				Text_Color(YELLOW); Set_Cursor(_X1, _Y2 - 3); _Console->println(_Number);
			}

			// Draw Header
			if (_Header) {

				// Set Text Color
				Text_Color(WHITE);

				// Print Corners
				Set_Cursor(_X1 + 2, _Y1); _Console->println(F("├"));
				Set_Cursor(_X1 + 2, _Y2); _Console->println(F("┤"));

				// Print Lines
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
					
					Set_Cursor(_X1 + 2, i); _Console->println(F("─"));
					
				}

			}
			
			// Draw Footer			
			if (_Footer) {

			// Set Text Color
			Text_Color(WHITE);

				// Print Corners
				Set_Cursor(_X2 - 2, _Y1); _Console->println(F("├"));
				Set_Cursor(_X2 - 2, _Y2); _Console->println(F("┤"));

				// Print Lines
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) {
					
					Set_Cursor(_X2 - 2, i); _Console->println(F("─"));
					
				}

			}
			
		}

		/**
		 * @brief Dot Print Function.
		 * @param _X Cursor X Position
		 * @param _Y Cursor Y Position
		 * @param _Count Dot Length
		 */
		void Dot(uint8_t _X, uint8_t _Y, uint8_t _Count) {

			for (uint8_t i = 0; i < _Count; i++) {

				Text(_X, _Y + i, WHITE, F("."));

			}

		}

		/**
		 * @brief Bracket Place Holder Function.
		 * @param _X Cursor X Position.
		 * @param _Y Cursor Y Position.
		 * @param _Space Bracket Size.
		 */
		void Bracket(uint8_t _X, uint8_t _Y, uint8_t _Space) {

			// Print Bracket Start
			Text(_X, _Y, WHITE, F("["));

			// Print Bracket Left
			Text(_X, _Y + _Space, WHITE, F("]"));

		}









		void _Send_CMD(uint8_t _val);
		void _Format_Text(uint8_t _val);

	public:

		/**
		 * @brief Begin Serial VT100 Console.
		 * @param _Serial Terminal UART Channel.
		 */
		void Begin(Stream &_Serial) {
	
			//Set serial port
			_Console = &_Serial;

			// Cursor Off
			Cursor(false);

			// Clear Screen
			Clear(SCREEN);

			// Reset Delay
			delay(5);

		}

		/**
		 * @brief Change Cursor Visibility Function.
		 * @param _State Cursor State.
		 */
		void Cursor(bool _State) {

			// Cursor On
			if (_State) _Console->print(F("\e[?25h"));	

			// Cursor Off
			if (_State) _Console->print(F("\e[?25l"));	

		}

		/**
		 * @brief Set Cursor Position Function.
		 * @param _X Cursor X Position.
		 * @param _Y Cursor Y Position.
		 */
		void Set_Cursor(uint8_t _X, uint8_t _Y) {

			// Set Cursor Position
			_Console->print(F("\e["));
			_Console->print(_X);
			_Console->print(F(";"));
			_Console->print(_Y);
			_Console->print(F("H"));

		}

		/**
		 * @brief Terminal Beep Sound Function.
		 */
		void Beep(void) {

			// Beep Terminal.
			_Console->print(F("\x07"));

		}

		/**
		 * @brief Clear Terminal Function.
		 * @param _Type Clear Type.
		 */
		void Clear(uint8_t _Type) {

			// Clear Screen
			if (_Type == LINE_AFTER_CURSOR) _Console->print(F("\e[K"));
			if (_Type == LINE_TO_CURSOR) _Console->print(F("\e[1K"));
			if (_Type == LINE) _Console->print(F("\e[2K"));
			if (_Type == SCREEN) _Console->print(F("\e[2J"));
			if (_Type == ALL) _Console->print(F("\e[1;1H\e[2J"));

		}

		/**
		 * @brief Print Text to Specified Position and Color.
		 * @param _X X Position.
		 * @param _Y Y Position.
		 * @param _Color Color.
		 * @param _Value Text Value.
		 */
		void Text(uint8_t _X, uint8_t _Y, Colors _Color, String _Value) {

			// Set Text Cursor Position
			Set_Cursor(_X, _Y); 

			// Set Text Color
			Text_Color(_Color); 

			// Print Text			
			_Console->println(_Value);

		}

		/**
		 * @brief Set Text Color Function.
		 * @param _Color Color
		 */
		void Text_Color(Colors _Color) {

			// Set Text Color.
			_Console->print(F("\e["));
			_Console->print(_Color);
			_Console->write('m');

		}

		/**
		 * @brief Set Back Ground Color Function.
		 * @param _Color Color.
		 */
		void Background_Color(Colors _Color) {

			// Set Back Ground Color.
			_Console->print(F("\e["));
			_Console->print(_Color + 10);
			_Console->write('m');

		}

		/**
		 * @brief Hardware Diagnostic Box Print Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
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

		/**
		 * @brief Detail Box Print Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
		void Print_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

			// Draw Hardware Diagnostic Box
			Draw_Box(_X1, _Y1, _X2, _Y2, "Detail", 2, false, false);

			// Print Text
			Text(_X1 + 1, _Y1 + 2, WHITE, F("Serial ID")); 			Dot(_X1 + 1, _Y1 + 11, (_Y2 - 19) - (_Y1 + 11)); 	Bracket(_X1 + 1, _Y2 - 19, 17);
			Text(_X1 + 2, _Y1 + 2, WHITE, F("Firmware Version")); 	Dot(_X1 + 2, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	Bracket(_X1 + 2, _Y2 - 11, 9);
			Text(_X1 + 3, _Y1 + 2, WHITE, F("Hardware Version")); 	Dot(_X1 + 3, _Y1 + 18, (_Y2 - 11) - (_Y1 + 18)); 	Bracket(_X1 + 3, _Y2 - 11, 9);
			Text(_X1 + 4, _Y1 + 2, WHITE, F("Module Temperature")); Dot(_X1 + 4, _Y1 + 20, (_Y2 - 6) - (_Y1 + 20)); 	Bracket(_X1 + 4, _Y2 - 10, 8);	Text(_X1 + 4, _Y2 - 3, WHITE, F("C"));
			Text(_X1 + 5, _Y1 + 2, WHITE, F("Module Humidity")); 	Dot(_X1 + 5, _Y1 + 17, (_Y2 - 6) - (_Y1 + 17)); 	Bracket(_X1 + 5, _Y2 - 10, 8);	Text(_X1 + 5, _Y2 - 3, WHITE, F("%"));
			Text(_X1 + 6, _Y1 + 2, WHITE, F("Device State")); 		Dot(_X1 + 6, _Y1 + 14, (_Y2 - 6) - (_Y1 + 14)); 	Bracket(_X1 + 6, _Y2 - 6, 4);
			Text(_X1 + 7, _Y1 + 2, WHITE, F("Fault State")); 		Dot(_X1 + 7, _Y1 + 13, (_Y2 - 6) - (_Y1 + 13)); 	Bracket(_X1 + 7, _Y2 - 6, 4);

		}

		/**
		 * @brief Battery Print Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
		void Print_Battery(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

			// Draw Hardware Diagnostic Box
			Draw_Box(_X1, _Y1, _X2, _Y2, "Battery", 3, false, false);

			// Print Text
			Text(_X1 + 1, _Y1 + 2, WHITE, F("Instant Voltage")); 			Dot(_X1 + 1, _Y1 + 17, (_Y2 - 9) - (_Y1 + 17)); 	Bracket(_X1 + 1, _Y2 - 9, 7);	Text(_X1 + 1, _Y2 - 3, WHITE, F("V"));
			Text(_X1 + 2, _Y1 + 2, WHITE, F("Temperature")); 				Dot(_X1 + 2, _Y1 + 13, (_Y2 - 8) - (_Y1 + 13)); 	Bracket(_X1 + 2, _Y2 - 10, 8);	Text(_X1 + 2, _Y2 - 3, WHITE, F("C"));
			Text(_X1 + 3, _Y1 + 2, WHITE, F("Average Current")); 			Dot(_X1 + 3, _Y1 + 17, (_Y2 - 13) - (_Y1 + 17)); 	Bracket(_X1 + 3, _Y2 - 13, 11);	Text(_X1 + 3, _Y2 - 4, WHITE, F("mA"));
			Text(_X1 + 4, _Y1 + 2, WHITE, F("State of Charge")); 			Dot(_X1 + 4, _Y1 + 17, (_Y2 - 10) - (_Y1 + 17)); 	Bracket(_X1 + 4, _Y2 - 10, 8);	Text(_X1 + 4, _Y2 - 3, WHITE, F("%"));
			Text(_X1 + 5, _Y1 + 2, WHITE, F("Full Battery Capacity")); 		Dot(_X1 + 5, _Y1 + 23, (_Y2 - 10) - (_Y1 + 23)); 	Bracket(_X1 + 5, _Y2 - 10, 8);	Text(_X1 + 5, _Y2 - 4, WHITE, F("mA"));
			Text(_X1 + 6, _Y1 + 2, WHITE, F("Instant Battery Capacity")); 	Dot(_X1 + 6, _Y1 + 26, (_Y2 - 10) - (_Y1 + 26)); 	Bracket(_X1 + 6, _Y2 - 10, 8);	Text(_X1 + 6, _Y2 - 4, WHITE, F("mA"));
			Text(_X1 + 7, _Y1 + 2, WHITE, F("Cycle Count")); 				Dot(_X1 + 7, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 7, _Y2 - 7, 5);

		}

		/**
		 * @brief Battery GSM Initialize Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
		void Print_GSM_Setup(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

			// Draw GSM Setup Diagnostic Box
			Draw_Box(_X1, _Y1, _X2, _Y2, "GSM Setup", 4, false, false);

			// Print Text	
			Text(_X1 + 1, _Y1 + 2, WHITE, F("ATE=0"));			Dot(_X1 + 1, _Y1 + 7, (_Y2 - 7) - (_Y1 + 7)); 		Bracket(_X1 + 1, _Y2 - 7, 5);	Text(_X1 + 1, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 2, _Y1 + 2, WHITE, F("AT+CMEE=1"));		Dot(_X1 + 2, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 2, _Y2 - 7, 5);	Text(_X1 + 2, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 3, _Y1 + 2, WHITE, F("AT+FCLASS=0"));	Dot(_X1 + 3, _Y1 + 13, (_Y2 - 7) - (_Y1 + 13)); 	Bracket(_X1 + 3, _Y2 - 7, 5);	Text(_X1 + 3, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 4, _Y1 + 2, WHITE, F("AT&K0"));			Dot(_X1 + 4, _Y1 + 7, (_Y2 - 7) - (_Y1 + 7)); 		Bracket(_X1 + 4, _Y2 - 7, 5);	Text(_X1 + 4, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 5, _Y1 + 2, WHITE, F("AT+CPIN?"));		Dot(_X1 + 5, _Y1 + 10, (_Y2 - 7) - (_Y1 + 10)); 	Bracket(_X1 + 5, _Y2 - 7, 5);	Text(_X1 + 5, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 6, _Y1 + 2, WHITE, F("AT+CGSN"));		Dot(_X1 + 6, _Y1 + 9, (_Y2 - 7) - (_Y1 + 9)); 		Bracket(_X1 + 6, _Y2 - 7, 5);	Text(_X1 + 6, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 7, _Y1 + 2, WHITE, F("AT+GSN"));			Dot(_X1 + 7, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8)); 		Bracket(_X1 + 7, _Y2 - 7, 5);	Text(_X1 + 7, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 8, _Y1 + 2, WHITE, F("AT+CCID"));		Dot(_X1 + 8, _Y1 + 9, (_Y2 - 7) - (_Y1 + 9)); 		Bracket(_X1 + 8, _Y2 - 7, 5);	Text(_X1 + 8, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 9, _Y1 + 2, WHITE, F("AT+GMI"));			Dot(_X1 + 9, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8)); 		Bracket(_X1 + 9, _Y2 - 7, 5);	Text(_X1 + 9, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 10, _Y1 + 2, WHITE, F("AT+GMM"));		Dot(_X1 + 10, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8));	 	Bracket(_X1 + 10, _Y2 - 7, 5);	Text(_X1 + 10, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 11, _Y1 + 2, WHITE, F("AT+GMR"));		Dot(_X1 + 11, _Y1 + 8, (_Y2 - 7) - (_Y1 + 8));	 	Bracket(_X1 + 11, _Y2 - 7, 5);	Text(_X1 + 11, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 12, _Y1 + 2, WHITE, F("AT+SLED=2"));		Dot(_X1 + 12, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 12, _Y2 - 7, 5);	Text(_X1 + 12, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 13, _Y1 + 2, WHITE, F("AT#E2SLRI=50"));	Dot(_X1 + 13, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14)); 	Bracket(_X1 + 13, _Y2 - 7, 5);	Text(_X1 + 13, _Y2 - 6, WHITE, F("...."));

		}

		/**
		 * @brief Battery GSM Connection Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
		void Print_GSM_Connection(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

			// Draw GSM Connection Diagnostic Box
			Draw_Box(_X1, _Y1, _X2, _Y2, "GSM Connection", 5, false, false);

			// Print Text	
			Text(_X1 + 1, _Y1 + 2, WHITE, F("AT#REGMODE=1"));					Dot(_X1 + 1, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14)); 	Bracket(_X1 + 1, _Y2 - 7, 5);	Text(_X1 + 1, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 2, _Y1 + 2, WHITE, F("AT#TXMONMODE=1"));					Dot(_X1 + 2, _Y1 + 15, (_Y2 - 7) - (_Y1 + 15)); 	Bracket(_X1 + 2, _Y2 - 7, 5);	Text(_X1 + 2, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 3, _Y1 + 2, WHITE, F("AT+CREG=0"));						Dot(_X1 + 3, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 3, _Y2 - 7, 5);	Text(_X1 + 3, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 4, _Y1 + 2, WHITE, F("AT+CGREG=0"));						Dot(_X1 + 4, _Y1 + 12, (_Y2 - 7) - (_Y1 + 12)); 	Bracket(_X1 + 4, _Y2 - 7, 5);	Text(_X1 + 4, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 5, _Y1 + 2, WHITE, F("AT#SCFG=1,1,1500,90,600,50"));		Dot(_X1 + 5, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28)); 	Bracket(_X1 + 5, _Y2 - 7, 5);	Text(_X1 + 5, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 6, _Y1 + 2, WHITE, F("AT#SCFG=2,1,1500,90,300,50"));		Dot(_X1 + 6, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28)); 	Bracket(_X1 + 6, _Y2 - 7, 5);	Text(_X1 + 6, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 7, _Y1 + 2, WHITE, F("AT#SCFGEXT=2,1,0,1,0,0"));			Dot(_X1 + 7, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24)); 	Bracket(_X1 + 7, _Y2 - 7, 5);	Text(_X1 + 7, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 8, _Y1 + 2, WHITE, F("AT+CGDCONT=1,\"IP\",\"mgbs\""));	Dot(_X1 + 8, _Y1 + 26, (_Y2 - 7) - (_Y1 + 26)); 	Bracket(_X1 + 8, _Y2 - 7, 5);	Text(_X1 + 8, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 9, _Y1 + 2, WHITE, F("AT#SERVIFO"));						Dot(_X1 + 9, _Y1 + 12, (_Y2 - 7) - (_Y1 + 12)); 	Bracket(_X1 + 9, _Y2 - 7, 5);	Text(_X1 + 9, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 10, _Y1 + 2, WHITE, F("AT+CGACT=1,1"));					Dot(_X1 + 10, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14));	Bracket(_X1 + 10, _Y2 - 7, 5);	Text(_X1 + 10, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 11, _Y1 + 2, WHITE, F("AT+CGPADDR=1"));					Dot(_X1 + 11, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14));	Bracket(_X1 + 11, _Y2 - 7, 5);	Text(_X1 + 11, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 12, _Y1 + 2, WHITE, F("AT#HTTPCFG=1,\"*****\",80,0"));	Dot(_X1 + 12, _Y1 + 27, (_Y2 - 7) - (_Y1 + 27)); 	Bracket(_X1 + 12, _Y2 - 7, 5);	Text(_X1 + 12, _Y2 - 6, WHITE, F("...."));
			Text(_X1 + 13, _Y1 + 2, WHITE, F("AT#ICMP=1"));						Dot(_X1 + 13, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 13, _Y2 - 7, 5);	Text(_X1 + 13, _Y2 - 6, WHITE, F("...."));

		}


		/**
		 * @brief PowerStat Terminal Batch
		 */
		void PowerStat(void) {

			// Draw Main Box
			Draw_Box(1, 1, 52, 120, "", 0, true, true);

			// Print Main Header Text
			Print_Box_Title(1,1,60,F("PowerStat V3"));

			// Header Titles
			Text(2, 3, WHITE, F("Up Time : "));

			// Draw Hardware Diagnostic
			this->Print_Diagnostic(4, 2, 12, 39);

			// Draw Detail Box
			this->Print_Detail(4, 40, 12, 79);

			// Draw Battery Box
			this->Print_Battery(4, 80, 12, 119);

			// Draw GSM Setup Box
			this->Print_GSM_Setup(13, 2, 27, 39);

			// Draw GSM Connection Box
			this->Print_GSM_Connection(13, 40, 27, 79);


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

			// Power Box
			Draw_Box(31, 2, 38, 60, "Power", 0, false, false);
			Draw_3Row_Abstract_Table(32,6);
			Draw_Box(31, 61, 38, 119, "Power Check", 0, false, false);
			Draw_3Row_Limit_Table(32,64);

			Text(40, 4, WHITE, F("R [ ] -"));
			Text(40, 12, WHITE, F("S [ ] -"));
			Text(40, 20, WHITE, F("T [ ] -"));
			Text(40, 28, WHITE, F("M1 [ ] -"));
			Text(40, 37, WHITE, F("M2 [ ] -"));
			Text(40, 46, WHITE, F("M3 [ ] -"));
			Text(40, 55, WHITE, F("Th [ ] -"));
			Text(40, 64, WHITE, F("Mp [ ]"));

			// JSON Data Box
			Draw_Box(28, 2, 30, 119, "", 8, false, false);
			Draw_Box(42, 2, 49, 119, "Data", 0, false, false);
			Draw_Box(39, 2, 41, 119, "", 8, false, false);

			// Print Instant Value
			Text(40, 115, WHITE, F("Bar"));
			
		}







		
		void Text_Format(TextFormat _Format);
		void Print(String _Value);
		void Print(const uint32_t _Value);
		void OK_Decide(bool _Result, uint8_t _X, uint8_t _Y);


		void Print_Box_Title(uint8_t _X1, uint8_t _Y1, uint8_t _X2, String _Title);
		void Draw_Horizontal_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length, bool _End);
		void Draw_Vertical_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length);
		void Draw_3Row_Stat_Table(uint8_t _X1, uint8_t _Y1);
		void Draw_3Row_Abstract_Table(uint8_t _X1, uint8_t _Y1);
		void Draw_1Row_Stat_Table(uint8_t _X1, uint8_t _Y1, String _Variable);
		void Draw_3Row_Limit_Table(uint8_t _X1, uint8_t _Y1);

		// Predefined Drawing Functions
		void FilterStat(void);
		void I2C_Scanner_Table(void);
		void MAX78630(void);
		void Telit_xE910(void);
		void MAX78630_Voltmeter(void);
};

extern Console Terminal;

#endif /* defined(__Console__) */