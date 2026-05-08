#ifndef Console_Definition_h
#define Console_Definition_h

	// Color Definitions
	constexpr uint8_t _Console_BLACK_				= 30;
	constexpr uint8_t _Console_RED_					= 31;
	constexpr uint8_t _Console_GREEN_				= 32;
	constexpr uint8_t _Console_YELLOW_				= 33;
	constexpr uint8_t _Console_BLUE_				= 34;
	constexpr uint8_t _Console_MAGENTA_				= 35;
	constexpr uint8_t _Console_CYAN_				= 36;
	constexpr uint8_t _Console_WHITE_				= 37;
	constexpr uint8_t _Console_GRAY_				= 90;

	// Text Format Definitions
	constexpr uint8_t _Console_RST_					= 0;
	constexpr uint8_t _Console_BRIGHT_				= 1;
	constexpr uint8_t _Console_DIM_					= 2;
	constexpr uint8_t _Console_UNDERSCORE_			= 4;
	constexpr uint8_t _Console_BLINK_				= 5;
	constexpr uint8_t _Console_REVERSE_				= 7;
	constexpr uint8_t _Console_HIDDEN_				= 8;

	// Clear Type Definitions
	constexpr uint8_t _Console_LINE_AFTER_CURSOR_	= 0;
	constexpr uint8_t _Console_LINE_TO_CURSOR_		= 1;
	constexpr uint8_t _Console_LINE_				= 2;
	constexpr uint8_t _Console_SCREEN_				= 3;
	constexpr uint8_t _Console_ALL_					= 4;

	// Divider Type Definitions
	constexpr bool _Console_HORIZONTAL_				= true;
	constexpr bool _Console_VERTICAL_				= false;

	// Color Choice
	template<typename T>
	inline uint8_t SELECT_COLOR(const T _VALUE, const T _MIN, const T _MAX) {
		return (_VALUE <= _MIN) ? _Console_RED_ : ((_VALUE >= _MAX) ? _Console_GREEN_ : _Console_WHITE_);
	}

	// Configurable Position Defaults
	#ifndef _Console_AT_Status_X_
		constexpr uint8_t _Console_AT_Status_X_ 	= 21;
	#endif
	#ifndef _Console_AT_Status_Y_
		constexpr uint8_t _Console_AT_Status_Y_ 	= 84;
	#endif

	// PROGMEM Definition
	#ifndef PROGMEM
		#define PROGMEM
	#endif

	// FPSTR Fallback Definition
	#ifndef FPSTR
		class __FlashStringHelper;
		#define FPSTR(p) (reinterpret_cast<const __FlashStringHelper *>(p))
	#endif

	// F() Fallback Definition
	#ifndef F
		#define F(string_literal) (string_literal)
	#endif

	// PROGMEM String Constants
	static const char _Console_ESC[]      PROGMEM = "\e[";
	static const char _Console_HEX[]      PROGMEM = "0x";
	static const char _Console_TL[]       PROGMEM = "┌";
	static const char _Console_TR[]       PROGMEM = "┐";
	static const char _Console_BL[]       PROGMEM = "└";
	static const char _Console_BR[]       PROGMEM = "┘";
	static const char _Console_VL[]       PROGMEM = "│";
	static const char _Console_HL[]       PROGMEM = "─";
	static const char _Console_JL[]       PROGMEM = "├";
	static const char _Console_JR[]       PROGMEM = "┤";
	static const char _Console_JT[]       PROGMEM = "┬";
	static const char _Console_JB[]       PROGMEM = "┴";
	static const char _Console_CLR_EOL[]  PROGMEM = "\e[K";
	static const char _Console_CLR_BOL[]  PROGMEM = "\e[1K";
	static const char _Console_CLR_LINE[] PROGMEM = "\e[2K";
	static const char _Console_CLR_SCR[]  PROGMEM = "\e[2J";
	static const char _Console_CLR_ALL[]  PROGMEM = "\e[1;1H\e[2J";
	static const char _Console_CUR_SHOW[] PROGMEM = "\e[?25h";
	static const char _Console_CUR_HIDE[] PROGMEM = "\e[?25l";
	static const char _Console_BEEP[]     PROGMEM = "\x07";
	static const char _Console_WAIT[]     PROGMEM = " .. ";
	static const char _Console_OK[]       PROGMEM = "OK";
	static const char _Console_FAIL[]     PROGMEM = "FAIL";

#endif /* Console_Definition_h */
