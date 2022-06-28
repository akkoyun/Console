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

		/**
		 * @brief Horizontal Line Divider Function.
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
		 * @param _X1 Start Cursor X
		 * @param _Y1 Start Cursor Y
		 * @param _Length Length
		 * @param _End End Symbol
		 */
		void Vertical_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length) {

			//Set Color
			Text_Color(WHITE);

			// Print Corners
			Set_Cursor(_X1, _Y1); _Console->println(F("┬"));
			Set_Cursor(_X1 + _Length, _Y1); _Console->println(F("┴"));

			// Print Lines
			for (uint8_t i = _X1 + 1; i <= _X1 + _Length - 1; i++) {Set_Cursor(i, _Y1); _Console->println(F("│"));}

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
			Text(_X1 + 1, _Y1 + 2, WHITE, F("AT#REGMODE=1"));					Dot(_X1 + 1, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14)); 	Bracket(_X1 + 1, _Y2 - 7, 5);
			Text(_X1 + 2, _Y1 + 2, WHITE, F("AT#TXMONMODE=1"));					Dot(_X1 + 2, _Y1 + 15, (_Y2 - 7) - (_Y1 + 15)); 	Bracket(_X1 + 2, _Y2 - 7, 5);
			Text(_X1 + 3, _Y1 + 2, WHITE, F("AT+CREG=0"));						Dot(_X1 + 3, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 3, _Y2 - 7, 5);
			Text(_X1 + 4, _Y1 + 2, WHITE, F("AT+CGREG=0"));						Dot(_X1 + 4, _Y1 + 12, (_Y2 - 7) - (_Y1 + 12)); 	Bracket(_X1 + 4, _Y2 - 7, 5);
			Text(_X1 + 5, _Y1 + 2, WHITE, F("AT#SCFG=1,1,1500,90,600,50"));		Dot(_X1 + 5, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28)); 	Bracket(_X1 + 5, _Y2 - 7, 5);
			Text(_X1 + 6, _Y1 + 2, WHITE, F("AT#SCFG=2,1,1500,90,300,50"));		Dot(_X1 + 6, _Y1 + 28, (_Y2 - 7) - (_Y1 + 28)); 	Bracket(_X1 + 6, _Y2 - 7, 5);
			Text(_X1 + 7, _Y1 + 2, WHITE, F("AT#SCFGEXT=2,1,0,1,0,0"));			Dot(_X1 + 7, _Y1 + 24, (_Y2 - 7) - (_Y1 + 24)); 	Bracket(_X1 + 7, _Y2 - 7, 5);
			Text(_X1 + 8, _Y1 + 2, WHITE, F("AT+CGDCONT=1,\"IP\",\"mgbs\""));	Dot(_X1 + 8, _Y1 + 26, (_Y2 - 7) - (_Y1 + 26)); 	Bracket(_X1 + 8, _Y2 - 7, 5);
			Text(_X1 + 9, _Y1 + 2, WHITE, F("AT#SERVIFO"));						Dot(_X1 + 9, _Y1 + 12, (_Y2 - 7) - (_Y1 + 12)); 	Bracket(_X1 + 9, _Y2 - 7, 5);
			Text(_X1 + 10, _Y1 + 2, WHITE, F("AT+CGACT=1,1"));					Dot(_X1 + 10, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14));	Bracket(_X1 + 10, _Y2 - 7, 5);
			Text(_X1 + 11, _Y1 + 2, WHITE, F("AT+CGPADDR=1"));					Dot(_X1 + 11, _Y1 + 14, (_Y2 - 7) - (_Y1 + 14));	Bracket(_X1 + 11, _Y2 - 7, 5);
			Text(_X1 + 12, _Y1 + 2, WHITE, F("AT#HTTPCFG=1,\"*****\",80,0"));	Dot(_X1 + 12, _Y1 + 27, (_Y2 - 7) - (_Y1 + 27)); 	Bracket(_X1 + 12, _Y2 - 7, 5);
			Text(_X1 + 13, _Y1 + 2, WHITE, F("AT#ICMP=1"));						Dot(_X1 + 13, _Y1 + 11, (_Y2 - 7) - (_Y1 + 11)); 	Bracket(_X1 + 13, _Y2 - 7, 5);

		}

		/**
		 * @brief Battery GSM Detail Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
		void Print_GSM_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

			// Draw GSM Connection Diagnostic Box
			Draw_Box(_X1, _Y1, _X2, _Y2, "GSM Detail", 6, false, false);

			// Print Text	
			Text(_X1 + 1, _Y1 + 2, WHITE, F("Manufacturer"));	Dot(_X1 + 1, _Y1 + 14, (_Y2 - 4) - (_Y1 + 14)); 	Bracket(_X1 + 1, _Y2 - 4, 2);
			Text(_X1 + 2, _Y1 + 2, WHITE, F("Model"));			Dot(_X1 + 2, _Y1 + 7, (_Y2 - 4) - (_Y1 + 7)); 		Bracket(_X1 + 2, _Y2 - 4, 2);
			Text(_X1 + 3, _Y1 + 2, WHITE, F("Firmware"));		Dot(_X1 + 3, _Y1 + 11, (_Y2 - 12) - (_Y1 + 11)); 	Bracket(_X1 + 3, _Y2 - 12, 10);
			Text(_X1 + 4, _Y1 + 2, WHITE, F("IMEI"));			Dot(_X1 + 4, _Y1 + 6, (_Y2 - 18) - (_Y1 + 6)); 		Bracket(_X1 + 4, _Y2 - 18, 16);
			Text(_X1 + 5, _Y1 + 2, WHITE, F("Serial ID"));		Dot(_X1 + 5, _Y1 + 11, (_Y2 - 13) - (_Y1 + 11)); 	Bracket(_X1 + 5, _Y2 - 13, 11);
			Text(_X1 + 6, _Y1 + 2, WHITE, F("ICCID"));			Dot(_X1 + 6, _Y1 + 7, (_Y2 - 22) - (_Y1 + 7)); 		Bracket(_X1 + 6, _Y2 - 22, 20);

		}

		/**
		 * @brief GSM Connection Detail Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
		void Print_GSM_Connection_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

			// Draw GSM Connection Diagnostic Box
			Draw_Box(_X1, _Y1, _X2, _Y2, "Connection", 7, false, false);

			// Print Text	
			Text(_X1 + 1, _Y1 + 2, WHITE, F("GSM Connection Time"));	Dot(_X1 + 1, _Y1 + 21, (_Y2 - 7) - (_Y1 + 21)); 	Bracket(_X1 + 1, _Y2 - 7, 5);
			Text(_X1 + 2, _Y1 + 2, WHITE, F("RSSI Level"));				Dot(_X1 + 2, _Y1 + 12, (_Y2 - 5) - (_Y1 + 12)); 	Bracket(_X1 + 2, _Y2 - 5, 3);
			Text(_X1 + 3, _Y1 + 2, WHITE, F("GSM Operator"));			Dot(_X1 + 3, _Y1 + 14, (_Y2 - 8) - (_Y1 + 14)); 	Bracket(_X1 + 3, _Y2 - 8, 6);
			Text(_X1 + 4, _Y1 + 2, WHITE, F("IP Address"));				Dot(_X1 + 4, _Y1 + 12, (_Y2 - 18) - (_Y1 + 12)); 	Bracket(_X1 + 4, _Y2 - 18, 16);
			Text(_X1 + 5, _Y1 + 2, WHITE, F("Socket Status"));			Dot(_X1 + 5, _Y1 + 15, (_Y2 - 13) - (_Y1 + 15)); 	Bracket(_X1 + 5, _Y2 - 12, 10);

		}

		/**
		 * @brief Power Detail Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
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

		/**
		 * @brief Power Fault Detail Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
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

		/**
		 * @brief State Detail Function.
		 * @param _X1 Left Upper Cursor X Position
		 * @param _Y1 Left Upper Cursor Y Position
		 * @param _X2 Right Lower Cursor X Position
		 * @param _Y2 Right Lower Cursor Y Position
		 */
		void Print_State_Detail(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2) {

			// Draw State Box
			Draw_Box(_X1, _Y1, _X2, _Y2, "", 0, false, false);
			Vertical_Divider(_X1, _Y1 + 105, 2);

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
			Text(_X1 + 1, _Y1 + 113, WHITE, F("Bar"));

		}

	public:

		/**
		 * @brief Construct a new Console object
		 */
		Console(void) {

		}

		/**
		 * @brief Begin Serial VT100 Console.
		 * @param _Serial Terminal UART Channel.
		 */
		void Begin(Stream &_Serial, bool _Boot) {

			//Set serial port
			if (!_Boot) _Console = &_Serial;

			// Cursor Off
			if (_Boot) Cursor(false);

			// Clear Screen
			if (_Boot) Clear(SCREEN);

			// Reset Delay
			if (_Boot) delay(5);

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
		 * @brief OK Decide Function.
		 * @param _Result Result Input
		 * @param _X Cursor X
		 * @param _Y Cursor Y
		 */
		void OK_Decide(bool _Result, uint8_t _X, uint8_t _Y) {

			// Print Command State
			if (_Result) {

				Text(_X, _Y, GREEN, F(" OK "));

			} else {

				Text(_X, _Y, RED, F("FAIL"));

			}
	
		}

		/**
		 * @brief PowerStat Terminal Batch
		 */
		void PowerStat(void) {

			// Draw Main Box
			Draw_Box(1, 1, 52, 120, "", 0, true, true);

			// Print Main Header Text
			this->Text(2, 53, WHITE, F("PowerStat V3"));

			// Header Titles
			this->Text(2, 3, WHITE, F("Up Time : "));

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

			// Draw GSM Detail Box
			this->Print_GSM_Detail(13, 80, 20, 119);

			// Draw GSM Connection Detail Box
			this->Print_GSM_Connection_Detail(21, 80, 27, 119);

			// GSM Power Box
			this->Draw_Box(28, 2, 30, 119, "", 0, false, false);

			// Power Box
			this->Print_Power_Detail(31, 2, 38, 60);

			// Power Check
			this->Print_Power_Fault_Detail(31, 61, 38, 119);

			// State Detail Box
			this->Print_State_Detail(39, 2, 41, 119);

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

		}







		void FilterStat(void) {

			// Draw Main Screen
			Draw_Box(1, 1, 49, 120, "", 0, true, 1);
			//Print_Box_Title(1,1,59,F("FilterStat V3"));

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

			// Solenoid Box
			Draw_Box(31, 2, 36, 98, "", 0, false, false);
			Draw_Box(31, 99, 36, 119, "", 0, false, false);
			Horizontal_Divider(33,2,96,true);
			Horizontal_Divider(33,99,20,true);
			Vertical_Divider(33,8,3);
			Vertical_Divider(33,14,3);
			Vertical_Divider(33,20,3);
			Vertical_Divider(33,26,3);
			Vertical_Divider(33,32,3);
			Vertical_Divider(33,38,3);
			Vertical_Divider(33,44,3);
			Vertical_Divider(33,50,3);
			Vertical_Divider(33,56,3);
			Vertical_Divider(33,62,3);
			Vertical_Divider(33,68,3);
			Vertical_Divider(33,74,3);
			Vertical_Divider(33,80,3);
			Vertical_Divider(33,86,3);
			Vertical_Divider(33,92,3);

			Vertical_Divider(31,26,2);
			Vertical_Divider(31,50,2);
			Vertical_Divider(31,74,2);

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
			Text(41, 101, WHITE, F("Stabilizer....[ ]"));
			Text(42, 101, WHITE, F("HydroCyclone..[ ]"));
			Text(43, 101, WHITE, F("Irrigation....[ ]"));
			//Text(44, 101, WHITE, F("IDLE..........[ ]"));

			Vertical_Divider(47,99,2);
			
		}
		void I2C_Scanner_Table(void) {

			// Draw Console Table
			for (uint8_t i = 1; i <= 23; i = i + 2) {Horizontal_Divider(i, 1, 120, false);}
			Vertical_Divider(1, 1, 22);
			for (uint8_t i = 9; i <= 120; i = i + 7) {Vertical_Divider(3, i, 18);}
			Vertical_Divider(1, 121, 22);

			// Draw Corners
			Set_Cursor(1,1); Serial.print(F("┌"));
			Set_Cursor(1,121); Serial.print(F("┐"));
			Set_Cursor(23,1); Serial.print(F("└"));
			Set_Cursor(23,121); Serial.print(F("┘"));

			// Draw T
			for (uint8_t i = 3; i <= 21; i = i + 2) {Set_Cursor(i,1); Serial.print(F("├"));}
			for (uint8_t i = 3; i <= 21; i = i + 2) {Set_Cursor(i,121); Serial.print(F("┤"));}
			
			// Draw Cross Section
			for (uint8_t i = 5; i <= 19; i = i + 2) {for (uint8_t j = 9; j <= 120; j = j + 7) {Set_Cursor(i,j); Serial.print(F("┼"));}}
			
			// Write Text
			//Print_Box_Title(1,1,60,F("I2C DEVICE EXPLORER"));
			Text(22,3,WHITE,F("Total connected device :"));
			Text(22,86,WHITE,F("Current Mux Channel [0-8] :"));
			Text(24,100,WHITE,F("github.com/akkoyun"));

			// Print headers
			uint8_t _C = 0;
			for (uint8_t i = 6; i <= 21; i = i + 2) {
				Set_Cursor(i,3); Serial.print(F("0x"));
				Set_Cursor(i,5); Serial.print(_C);
				Set_Cursor(i,6); Serial.print(F("_"));
				_C++;
			}
			uint8_t _R = 0;
			for (uint8_t i = 11; i <= 121; i = i + 7) {
				Set_Cursor(4,i); Serial.print(F("0x_"));
				Set_Cursor(4,i+3); Serial.print(_R, HEX);
				_R++;
			}

		}
		void MAX78630(void) {

			// Draw Main Screen
			Draw_Box(1, 1, 40, 80, "", 0, true, true);
			//Print_Box_Title(1,1,40,F("MAX78630 Energy Meter"));

			// Draw Voltage
			Draw_Box(4, 2, 27, 32, "Voltage", 1, false, false);
			Text(6, 4, WHITE, F("VScale")); Dot(6, 10, 11); Bracket(6, 21, 9); Text(6, 29, WHITE, F(""));
			Text(7, 4, WHITE, F("VA_GAIN")); Dot(7, 11, 10); Bracket(7, 21, 9); Text(7, 29, WHITE, F(""));
			Text(8, 4, WHITE, F("VB_GAIN")); Dot(8, 11, 10); Bracket(8, 21, 9); Text(8, 29, WHITE, F(""));
			Text(9, 4, WHITE, F("VC_GAIN")); Dot(9, 11, 10); Bracket(9, 21, 9); Text(9, 29, WHITE, F(""));
			Text(10, 4, WHITE, F("VA_OFFS")); Dot(10, 11, 10); Bracket(10, 21, 9); Text(10, 29, WHITE, F(""));
			Text(11, 4, WHITE, F("VB_OFFS")); Dot(11, 11, 10); Bracket(11, 21, 9); Text(11, 29, WHITE, F(""));
			Text(12, 4, WHITE, F("VC_OFFS")); Dot(12, 11, 10); Bracket(12, 21, 9); Text(12, 29, WHITE, F(""));
			Text(13, 4, WHITE, F("HPF_COEF_V")); Dot(13, 14, 7); Bracket(13, 21, 9); Text(13, 29, WHITE, F(""));
			Text(14, 4, WHITE, F("VA_RMS")); Dot(14, 10, 11); Bracket(14, 21, 9); Text(14, 29, WHITE, F("V"));
			Text(15, 4, WHITE, F("VB_RMS")); Dot(15, 10, 11); Bracket(15, 21, 9); Text(15, 29, WHITE, F("V"));
			Text(16, 4, WHITE, F("VC_RMS")); Dot(16, 10, 11); Bracket(16, 21, 9); Text(16, 29, WHITE, F("V"));
			Text(17, 4, WHITE, F("VT_RMS")); Dot(17, 10, 11); Bracket(17, 21, 9); Text(17, 29, WHITE, F("V"));
			Text(18, 4, WHITE, F("VA")); Dot(18, 6, 15); Bracket(18, 21, 9); Text(18, 29, WHITE, F("V"));
			Text(19, 4, WHITE, F("VB")); Dot(19, 6, 15); Bracket(19, 21, 9); Text(19, 29, WHITE, F("V"));
			Text(20, 4, WHITE, F("VC")); Dot(20, 6, 15); Bracket(20, 21, 9); Text(20, 29, WHITE, F("V"));
			Text(21, 4, WHITE, F("VA_FUND")); Dot(21, 11, 10); Bracket(21, 21, 9); Text(21, 29, WHITE, F("V"));
			Text(22, 4, WHITE, F("VB_FUND")); Dot(22, 11, 10); Bracket(22, 21, 9); Text(22, 29, WHITE, F("V"));
			Text(23, 4, WHITE, F("VC_FUND")); Dot(23, 11, 10); Bracket(23, 21, 9); Text(23, 29, WHITE, F("V"));
			Text(24, 4, WHITE, F("VA_HARM")); Dot(24, 11, 10); Bracket(24, 21, 9); Text(24, 29, WHITE, F("V"));
			Text(25, 4, WHITE, F("VB_HARM")); Dot(25, 11, 10); Bracket(25, 21, 9); Text(25, 29, WHITE, F("V"));
			Text(26, 4, WHITE, F("VC_HARM")); Dot(26, 11, 10); Bracket(26, 21, 9); Text(26, 29, WHITE, F("V"));

			// Draw Voltage
			Draw_Box(4, 33, 27, 63, "Current", 1, false, false);
			Text(6, 35, WHITE, F("IScale")); Dot(6, 41, 11); Bracket(6, 52, 9); Text(6, 60, WHITE, F(""));
			Text(7, 35, WHITE, F("IA_GAIN")); Dot(7, 42, 10); Bracket(7, 52, 9); Text(7, 60, WHITE, F(""));
			Text(8, 35, WHITE, F("IB_GAIN")); Dot(8, 42, 10); Bracket(8, 52, 9); Text(8, 60, WHITE, F(""));
			Text(9, 35, WHITE, F("IC_GAIN")); Dot(9, 42, 10); Bracket(9, 52, 9); Text(9, 60, WHITE, F(""));
			Text(10, 35, WHITE, F("IA_OFFS")); Dot(10, 42, 10); Bracket(10, 52, 9); Text(10, 60, WHITE, F(""));
			Text(11, 35, WHITE, F("IB_OFFS")); Dot(11, 42, 10); Bracket(11, 52, 9); Text(11, 60, WHITE, F(""));
			Text(12, 35, WHITE, F("IC_OFFS")); Dot(12, 42, 10); Bracket(12, 52, 9); Text(12, 60, WHITE, F(""));
			Text(13, 35, WHITE, F("HPF_COEF_I")); Dot(13, 45, 7); Bracket(13, 52, 9); Text(13, 29, WHITE, F(""));
			Text(14, 35, WHITE, F("IA_RMS")); Dot(14, 41, 11); Bracket(14, 52, 9); Text(14, 60, WHITE, F("A"));
			Text(15, 35, WHITE, F("IB_RMS")); Dot(15, 41, 11); Bracket(15, 52, 9); Text(15, 60, WHITE, F("A"));
			Text(16, 35, WHITE, F("IC_RMS")); Dot(16, 41, 11); Bracket(16, 52, 9); Text(16, 60, WHITE, F("A"));
			Text(17, 35, WHITE, F("IT_RMS")); Dot(17, 41, 11); Bracket(17, 52, 9); Text(17, 60, WHITE, F("A"));
			Text(18, 35, WHITE, F("IA")); Dot(18, 37, 15); Bracket(18, 52, 9); Text(18, 60, WHITE, F("A"));
			Text(19, 35, WHITE, F("IB")); Dot(19, 37, 15); Bracket(19, 52, 9); Text(19, 60, WHITE, F("A"));
			Text(20, 35, WHITE, F("IC")); Dot(20, 37, 15); Bracket(20, 52, 9); Text(20, 60, WHITE, F("A"));
			Text(21, 35, WHITE, F("IA_FUND")); Dot(21, 42, 10); Bracket(21, 52, 9); Text(21, 60, WHITE, F("A"));
			Text(22, 35, WHITE, F("IB_FUND")); Dot(22, 42, 10); Bracket(22, 52, 9); Text(22, 60, WHITE, F("A"));
			Text(23, 35, WHITE, F("IC_FUND")); Dot(23, 42, 10); Bracket(23, 52, 9); Text(23, 60, WHITE, F("A"));
			Text(24, 35, WHITE, F("IA_HARM")); Dot(24, 42, 10); Bracket(24, 52, 9); Text(24, 60, WHITE, F("A"));
			Text(25, 35, WHITE, F("IB_HARM")); Dot(25, 42, 10); Bracket(25, 52, 9); Text(25, 60, WHITE, F("A"));
			Text(26, 35, WHITE, F("IC_HARM")); Dot(26, 42, 10); Bracket(26, 52, 9); Text(26, 60, WHITE, F("A"));

			// Draw Frequency
			Draw_Box(28, 2, 33, 32, "Frequency", 1, false, false);
			Text(30, 4, WHITE, F("Frequency")); Dot(30, 13, 8); Bracket(30, 21, 9); Text(30, 28, WHITE, F("Hz"));
			Text(31, 4, WHITE, F("F_MIN")); Dot(31, 9, 12); Bracket(31, 21, 9); Text(31, 28, WHITE, F("Hz"));
			Text(32, 4, WHITE, F("F_MAX")); Dot(32, 9, 12); Bracket(32, 21, 9); Text(32, 28, WHITE, F("Hz"));

		}
		void Telit_xE910(void) {

			// Draw Main Screen
			Draw_Box(1, 1, 24, 120, "", 0, true, true);
			//Print_Box_Title(1,1,60,F("GSM Test Procedure"));

			// Draw GSM Setup Box
			Draw_Box(4, 2, 18, 39, "GSM Setup", 1, false, false);
			Text(5, 4, WHITE, F("ATE=0")); Dot(5, 9, 23); Bracket(5, 32, 5); Text(5, 33, YELLOW, F(" ** "));
			Text(6, 4, WHITE, F("AT+CMEE=1")); Dot(6, 13, 19); Bracket(6, 32, 5); Text(6, 33, YELLOW, F(" ** "));
			Text(7, 4, WHITE, F("AT+FCLASS=0")); Dot(7, 15, 17); Bracket(7, 32, 5); Text(7, 33, YELLOW, F(" ** "));
			Text(8, 4, WHITE, F("AT&K0")); Dot(8, 9, 23); Bracket(8, 32, 5); Text(8, 33, YELLOW, F(" ** "));
			Text(9, 4, WHITE, F("AT+CPIN?")); Dot(9, 12, 20); Bracket(9, 32, 5); Text(9, 33, YELLOW, F(" ** "));
			Text(10, 4, WHITE, F("AT+CGSN")); Dot(10, 11, 21); Bracket(10, 32, 5); Text(10, 33, YELLOW, F(" ** "));
			Text(11, 4, WHITE, F("AT+GSN")); Dot(11, 10, 22); Bracket(11, 32, 5); Text(11, 33, YELLOW, F(" ** "));
			Text(12, 4, WHITE, F("AT+CCID")); Dot(12, 11, 21); Bracket(12, 32, 5); Text(12, 33, YELLOW, F(" ** "));
			Text(13, 4, WHITE, F("AT+GMI")); Dot(13, 10, 22); Bracket(13, 32, 5); Text(13, 33, YELLOW, F(" ** "));
			Text(14, 4, WHITE, F("AT+GMM")); Dot(14, 10, 22); Bracket(14, 32, 5); Text(14, 33, YELLOW, F(" ** "));
			Text(15, 4, WHITE, F("AT+GMR")); Dot(15, 10, 22); Bracket(15, 32, 5); Text(15, 33, YELLOW, F(" ** "));
			Text(16, 4, WHITE, F("AT+SLED=2")); Dot(16, 13, 19); Bracket(16, 32, 5); Text(16, 33, YELLOW, F(" ** "));
			Text(17, 4, WHITE, F("AT#E2SLRI=50")); Dot(17, 16, 16); Bracket(17, 32, 5); Text(17, 33, YELLOW, F(" ** "));

			// GSM Connection Box
			Draw_Box(4, 40, 18, 79, "GSM Connection", 2, false, false);
			Text(5, 42, WHITE, F("AT#REGMODE=1")); Dot(5, 54, 18); Bracket(5, 72, 5); Text(5, 73, YELLOW, F(" ** "));
			Text(6, 42, WHITE, F("AT#TXMONMODE=1")); Dot(6, 56, 16); Bracket(6, 72, 5); Text(6, 73, YELLOW, F(" ** "));
			Text(7, 42, WHITE, F("AT+CREG=0")); Dot(7, 51, 21); Bracket(7, 72, 5); Text(7, 73, YELLOW, F(" ** "));
			Text(8, 42, WHITE, F("AT+CGREG=0")); Dot(8, 52, 20); Bracket(8, 72, 5); Text(8, 73, YELLOW, F(" ** "));
			Text(9, 42, WHITE, F("AT#SCFG=1,1,1500,90,600,50")); Dot(9, 68, 4); Bracket(9, 72, 5); Text(9, 73, YELLOW, F(" ** "));
			Text(10, 42, WHITE, F("AT#SCFG=2,1,1500,90,300,50")); Dot(10, 68, 4); Bracket(10, 72, 5); Text(10, 73, YELLOW, F(" ** "));
			Text(11, 42, WHITE, F("AT#SCFGEXT=2,1,0,1,0,0")); Dot(11, 64, 8); Bracket(11, 72, 5); Text(11, 73, YELLOW, F(" ** "));
			Text(12, 42, WHITE, F("AT+CGDCONT=1,\"IP\",\"mgbs\"")); Dot(12, 66, 6); Bracket(12, 72, 5); Text(12, 73, YELLOW, F(" ** "));
			Text(13, 42, WHITE, F("AT#SERVIFO")); Dot(13, 52, 20); Bracket(13, 72, 5); Text(13, 73, YELLOW, F(" ** "));
			Text(14, 42, WHITE, F("AT+SGACT=1,1")); Dot(14, 54, 18); Bracket(14, 72, 5); Text(14, 73, YELLOW, F(" ** "));
			Text(15, 42, WHITE, F("AT#HTTPCFG=1,\"*****\",80,0")); Dot(15, 67, 5); Bracket(15, 72, 5); Text(15, 73, YELLOW, F(" ** "));
			Text(16, 42, WHITE, F("AT#ICMP=1")); Dot(16, 51, 21); Bracket(16, 72, 5); Text(16, 73, YELLOW, F(" ** "));
			Text(17, 42, WHITE, F("AT#FRWL..")); Dot(17, 51, 21); Bracket(17, 72, 5); Text(17, 73, YELLOW, F(" ** "));

		//	Text(14, 42, WHITE, F("AT+CGACT=1,1")); Dot(14, 54, 18); Bracket(14, 72, 5); Text(14, 73, YELLOW, F(" ** "));
		//	Text(15, 42, WHITE, F("AT+CGPADDR=1")); Dot(15, 54, 18); Bracket(15, 72, 5); Text(15, 73, YELLOW, F(" ** "));
		//	Text(16, 42, WHITE, F("AT#HTTPCFG=1,\"*****\",80,0")); Dot(16, 67, 5); Bracket(16, 72, 5); Text(16, 73, YELLOW, F(" ** "));
		//	Text(17, 42, WHITE, F("AT#ICMP=1")); Dot(17, 51, 21); Bracket(17, 72, 5); Text(17, 73, YELLOW, F(" ** "));

			// GSM Detail Box
			Draw_Box(4, 80, 11, 119, "GSM Detail", 3, false, false);
			Text(5, 82, WHITE, F("Manufacturer")); Dot(5, 94, 21); Bracket(5, 115, 2);
			Text(6, 82, WHITE, F("Model")); Dot(6, 87, 28); Bracket(6, 115, 2);
			Text(7, 82, WHITE, F("Firmware")); Dot(7, 90, 7); Bracket(7, 106, 11);
			Text(8, 82, WHITE, F("IMEI")); Dot(8, 86, 15); Bracket(8, 101, 16);
			Text(9, 82, WHITE, F("Serial ID")); Dot(9, 91, 15); Bracket(9, 106, 11);
			Text(10, 82, WHITE, F("SIM ICCID")); Dot(10, 91, 6); Bracket(10, 97, 20);

			// Connection Box
			Draw_Box(12, 80, 18, 119, "Connection", 4, false, false);
			Text(13, 82, WHITE, F("GSM Connection Time")); Dot(13, 101, 11); Bracket(13, 112, 5);
			Text(14, 82, WHITE, F("RSSI Level")); Dot(14, 92, 22); Bracket(14, 114, 3);
			Text(15, 82, WHITE, F("GSM Operator")); Dot(15, 94, 17); Bracket(15, 111, 6);
			Text(16, 82, WHITE, F("IP Address")); Dot(16, 92, 9); Bracket(16, 101, 16);
			Text(17, 82, WHITE, F("Socket Listen Status")); Dot(17, 102, 5); Bracket(17, 107, 10);

			// JSON Data Box
			Draw_Box(19, 2, 21, 119, "", 8, false, false);

			Text(23, 3, WHITE, F("[1] Initialize Modem"));
			Text(23, 25, WHITE, F("[2] Connect"));
			Text(23, 38, WHITE, F("[3] Time Update"));
			Text(23, 55, WHITE, F("[4] Send HTTP Pack"));
			
		}
		void MAX78630_Voltmeter(void) {

			// Draw Main Screen
			Draw_Box(1, 1, 14, 84, "", 0, true, true);
			//Print_Box_Title(1,1,42,F("MAX78630 Volt Meter"));

			// Draw Voltage
			Draw_Box(5, 3, 10, 28, "Phase R", 1, false, false);
			Draw_Box(5, 30, 10, 55, "Phase S", 2, false, false);
			Draw_Box(5, 57, 10, 82, "Phase T", 3, false, false);

			Text(7, 5, WHITE, F("VA_RMS......[       V]"));
			Text(8, 5, WHITE, F("VA_MIN......[       V]"));
			Text(9, 5, WHITE, F("VA_MAX......[       V]"));

			Text(7, 32, WHITE, F("VB_RMS......[       V]"));
			Text(8, 32, WHITE, F("VB_MIN......[       V]"));
			Text(9, 32, WHITE, F("VB_MAX......[       V]"));

			Text(7, 59, WHITE, F("VC_RMS......[       V]"));
			Text(8, 59, WHITE, F("VC_MIN......[       V]"));
			Text(9, 59, WHITE, F("VC_MAX......[       V]"));
			
		}

};

#endif /* defined(__Console__) */