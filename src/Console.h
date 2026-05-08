#ifndef Console_h
#define Console_h

	// Include Arduino Library
	#ifndef Arduino_h
		#include <Arduino.h>
	#endif

	// Include Definition File
	#include "Definition.h"

	// Stream forward declaration fallback for non-Arduino IntelliSense environments
	#ifndef Stream_h
		class Stream {
			public:
				virtual size_t print(char)                         = 0;
				virtual size_t print(const char *)                 = 0;
				virtual size_t print(unsigned char, int = 10)      = 0;
				virtual size_t print(unsigned int, int = 10)       = 0;
				virtual size_t print(unsigned long, int = 10)      = 0;
				virtual size_t print(const __FlashStringHelper *)  = 0;
		};
	#endif

	// Console Class
	class Console {

		// Private Context
		private:

			// Stream Variable
			Stream * Console_Serial;

			// Color / Format Buffer
			struct Struct_Console_Buffer {
				uint8_t Text_Color       = 255;
				uint8_t Background_Color = 255;
				uint8_t Text_Format      = 255;
			} Buffer;

			// Print Single HEX Byte with Leading Zero.
			inline void _Print_Hex_Byte(const uint8_t _Val) {
				if (_Val < 0x10) Console_Serial->print('0');
				Console_Serial->print(_Val, HEX);
			}

		// Public Context
		public:

			// Constructor.
			explicit Console(Stream &_Serial) {
				this->Console_Serial = &_Serial;
			}

			// Begin Console.
			void Begin(void) {
				this->Cursor(false);
				this->Clear(_Console_SCREEN_);
				this->Text_Color(_Console_WHITE_);
				delay(5);
			}

			// Clear Terminal Function.
			void Clear(const uint8_t _Type) {
				switch (_Type) {
					case _Console_LINE_AFTER_CURSOR_: Console_Serial->print(FPSTR(_Console_CLR_EOL));  break;
					case _Console_LINE_TO_CURSOR_:    Console_Serial->print(FPSTR(_Console_CLR_BOL));  break;
					case _Console_LINE_:              Console_Serial->print(FPSTR(_Console_CLR_LINE)); break;
					case _Console_SCREEN_:            Console_Serial->print(FPSTR(_Console_CLR_SCR));  break;
					case _Console_ALL_:               Console_Serial->print(FPSTR(_Console_CLR_ALL));  break;
					default: break;
				}
			}

			// Change Cursor Visibility Function.
			void Cursor(const bool _State) {
				if (_State) Console_Serial->print(FPSTR(_Console_CUR_SHOW));
				else        Console_Serial->print(FPSTR(_Console_CUR_HIDE));
			}

			// Set Cursor Position Function.
			void Set_Cursor(const uint8_t _X, const uint8_t _Y) {
				Console_Serial->print(FPSTR(_Console_ESC));
				Console_Serial->print(_X);
				Console_Serial->print(';');
				Console_Serial->print(_Y);
				Console_Serial->print('H');
			}

			// Set Text Color Function.
			void Text_Color(const uint8_t _Color) {
				if (_Color != this->Buffer.Text_Color) {
					Console_Serial->print(FPSTR(_Console_ESC));
					Console_Serial->print(_Color);
					Console_Serial->print('m');
					this->Buffer.Text_Color = _Color;
				}
			}

			// Set Text Format Function.
			void Text_Format(const uint8_t _Format) {
				if (_Format != this->Buffer.Text_Format) {
					Console_Serial->print(FPSTR(_Console_ESC));
					Console_Serial->print(_Format);
					Console_Serial->print('m');
					this->Buffer.Text_Format = _Format;
					// RST invalidates all SGR attributes including color.
					if (_Format == _Console_RST_) {
						this->Buffer.Text_Color       = 255;
						this->Buffer.Background_Color = 255;
					}
				}
			}

			// Set Background Color Function.
			void Background_Color(const uint8_t _Color) {
				if (_Color != this->Buffer.Background_Color) {
					Console_Serial->print(FPSTR(_Console_ESC));
					Console_Serial->print((uint8_t)(_Color + 10));
					Console_Serial->print('m');
					this->Buffer.Background_Color = _Color;
				}
			}

			// Print Text to Specified Position and Color.
			void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const __FlashStringHelper * _Value) {
				this->Set_Cursor(_X, _Y);
				this->Text_Color(_Color);
				Console_Serial->print(_Value);
			}
			void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const char _Value) {
				this->Set_Cursor(_X, _Y);
				this->Text_Color(_Color);
				Console_Serial->print(_Value);
			}
			void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const char * _Value) {
				this->Set_Cursor(_X, _Y);
				this->Text_Color(_Color);
				Console_Serial->print(_Value);
			}
			template<typename T> void Text(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, T _Value) {
				this->Set_Cursor(_X, _Y);
				this->Text_Color(_Color);
				Console_Serial->print(_Value);
			}

			// Draw Box Function.
			void Box(const uint8_t _X1, const uint8_t _Y1, const uint8_t _X2, const uint8_t _Y2, const __FlashStringHelper * _Text, const uint8_t _Number = 0, const bool _Header = false, const bool _Footer = false) {

				this->Text_Color(_Console_WHITE_);
				this->Text_Format(_Console_DIM_);

				// Corners.
				this->Set_Cursor(_X1, _Y1); Console_Serial->print(FPSTR(_Console_TL));
				this->Set_Cursor(_X2, _Y1); Console_Serial->print(FPSTR(_Console_BL));
				this->Set_Cursor(_X1, _Y2); Console_Serial->print(FPSTR(_Console_TR));
				this->Set_Cursor(_X2, _Y2); Console_Serial->print(FPSTR(_Console_BR));

				// Vertical Lines.
				for (uint8_t i = _X1 + 1; i <= _X2 - 1; i++) {
					this->Set_Cursor(i, _Y1); Console_Serial->print(FPSTR(_Console_VL));
					this->Set_Cursor(i, _Y2); Console_Serial->print(FPSTR(_Console_VL));
				}

				// Top Horizontal Line.
				this->Set_Cursor(_X1, _Y1 + 1);
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) Console_Serial->print(FPSTR(_Console_HL));

				// Bottom Horizontal Line.
				this->Set_Cursor(_X2, _Y1 + 1);
				for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) Console_Serial->print(FPSTR(_Console_HL));

				// Title.
				this->Text_Color(_Console_YELLOW_);
				this->Set_Cursor(_X1, _Y1 + 2);
				Console_Serial->print(_Text);

				// Number.
				if (_Number > 0) {
					this->Text_Color(_Console_GRAY_);
					this->Set_Cursor(_X1, _Y2 - 5);
					Console_Serial->print('[');
					if (_Number < 10) Console_Serial->print('0');
					Console_Serial->print(_Number);
					Console_Serial->print(']');
				}

				// Header Divider.
				if (_Header) {
					this->Text_Color(_Console_WHITE_);
					this->Set_Cursor(_X1 + 2, _Y1); Console_Serial->print(FPSTR(_Console_JL));
					this->Set_Cursor(_X1 + 2, _Y2); Console_Serial->print(FPSTR(_Console_JR));
					this->Set_Cursor(_X1 + 2, _Y1 + 1);
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) Console_Serial->print(FPSTR(_Console_HL));
				}

				// Footer Divider.
				if (_Footer) {
					this->Text_Color(_Console_WHITE_);
					this->Set_Cursor(_X2 - 2, _Y1); Console_Serial->print(FPSTR(_Console_JL));
					this->Set_Cursor(_X2 - 2, _Y2); Console_Serial->print(FPSTR(_Console_JR));
					this->Set_Cursor(_X2 - 2, _Y1 + 1);
					for (uint8_t i = _Y1 + 1; i <= _Y2 - 1; i++) Console_Serial->print(FPSTR(_Console_HL));
				}

			}

			// Line Divider Function.
			void Divider(const bool _Type, const uint8_t _X, const uint8_t _Y, const uint8_t _Length, const bool _End = false) {

				this->Text_Color(_Console_WHITE_);

				if (_Type == _Console_HORIZONTAL_) {
					if (_End) {
						this->Set_Cursor(_X, _Y);           Console_Serial->print(FPSTR(_Console_JL));
						this->Set_Cursor(_X, _Y + _Length); Console_Serial->print(FPSTR(_Console_JR));
					}
					this->Set_Cursor(_X, _Y + 1);
					for (uint8_t i = _Y + 1; i <= _Y + _Length - 1; i++) Console_Serial->print(FPSTR(_Console_HL));
				} else {
					if (_End) {
						this->Set_Cursor(_X, _Y);           Console_Serial->print(FPSTR(_Console_JT));
						this->Set_Cursor(_X + _Length, _Y); Console_Serial->print(FPSTR(_Console_JB));
					}
					for (uint8_t i = _X + 1; i <= _X + _Length - 1; i++) {
						this->Set_Cursor(i, _Y);
						Console_Serial->print(FPSTR(_Console_VL));
					}
				}

			}

			// Dot Fill Function.
			void Dot(const uint8_t _X, const uint8_t _Y, const uint8_t _Count) {
				if (_Count == 0) return;
				this->Set_Cursor(_X, _Y);
				this->Text_Color(_Console_GRAY_);
				for (uint8_t i = 0; i < _Count; i++) Console_Serial->print('.');
			}

			// Space Fill Function.
			void Space(const uint8_t _X, const uint8_t _Y, const uint8_t _Count) {
				if (_Count == 0) return;
				this->Set_Cursor(_X, _Y);
				this->Text_Color(_Console_GRAY_);
				for (uint8_t i = 0; i < _Count; i++) Console_Serial->print(' ');
			}

			// Bracket Placeholder Function.
			void Bracket(const uint8_t _X, const uint8_t _Y, const uint8_t _Size) {
				this->Text(_X, _Y,         _Console_WHITE_, '[');
				this->Text(_X, _Y + _Size, _Console_WHITE_, ']');
			}

			// GSM AT Command Display.
			void AT_Command(const __FlashStringHelper * _Command) {
				constexpr uint8_t _Message_Size = 35;
				const uint8_t _Cmd_Len = (uint8_t)strlen_P((PGM_P)_Command);

				this->Space(_Console_AT_Status_X_, _Console_AT_Status_Y_, _Message_Size);
				this->Text(_Console_AT_Status_X_, _Console_AT_Status_Y_, _Console_WHITE_, _Command);
				if (_Cmd_Len + 5 < _Message_Size) {
					this->Dot(_Console_AT_Status_X_, _Console_AT_Status_Y_ + _Cmd_Len, _Message_Size - _Cmd_Len - 5);
				}
				this->Bracket(_Console_AT_Status_X_, _Console_AT_Status_Y_ + _Message_Size - 5, 5);
				this->Text(_Console_AT_Status_X_, _Console_AT_Status_Y_ + _Message_Size - 4, _Console_BLUE_, FPSTR(_Console_WAIT));
			}

			// OK / Fail Result Display.
			void OK(const bool _Result) {
				if (_Result) this->Text(_Console_AT_Status_X_, _Console_AT_Status_Y_ + 32, _Console_GREEN_, FPSTR(_Console_OK));
				else         this->Text(_Console_AT_Status_X_, _Console_AT_Status_Y_ + 31, _Console_RED_,   FPSTR(_Console_FAIL));
			}

			// Terminal Beep Sound Function.
			void Beep(void) {
				Console_Serial->print(FPSTR(_Console_BEEP));
			}

			// Print HEX Value at Position.
			void Print_HEX(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const uint8_t _Value) {
				this->Text_Color(_Color);
				this->Set_Cursor(_X, _Y);
				Console_Serial->print(FPSTR(_Console_HEX));
				this->_Print_Hex_Byte(_Value);
			}
			void Print_HEX(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const uint16_t _Value) {
				this->Text_Color(_Color);
				this->Set_Cursor(_X, _Y);
				Console_Serial->print(FPSTR(_Console_HEX));
				this->_Print_Hex_Byte((_Value >> 8) & 0xFF);
				this->_Print_Hex_Byte(_Value & 0xFF);
			}
			void Print_HEX(const uint8_t _X, const uint8_t _Y, const uint8_t _Color, const uint32_t _Value) {
				this->Text_Color(_Color);
				this->Set_Cursor(_X, _Y);
				Console_Serial->print(FPSTR(_Console_HEX));
				this->_Print_Hex_Byte((_Value >> 24) & 0xFF);
				this->_Print_Hex_Byte((_Value >> 16) & 0xFF);
				this->_Print_Hex_Byte((_Value >>  8) & 0xFF);
				this->_Print_Hex_Byte(_Value & 0xFF);
			}

	};

#endif /* Console_h */
