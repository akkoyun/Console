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

		void _Send_CMD(uint8_t _val);
		void _Format_Text(uint8_t _val);

	public:

		void Begin(Stream &_Serial);
		void Cursor(bool _State);
		void Beep(void);
		void Clear(uint8_t _Type);
		void Set_Cursor(uint8_t _x, uint8_t _y);
		
		void Text(uint8_t _x, uint8_t _y, Colors _Color, String _Value);
		void Text_Color(Colors _Color);
		void Text_Format(TextFormat _Format);
		void Print(String _Value);
		void Print(const uint32_t _Value);
		void OK_Decide(bool _Result, uint8_t _X, uint8_t _Y);

		void Background_Color(Colors _Color);

		void Draw_Box(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2, String _Text, uint8_t _Number, bool _Header, bool _Footer);
		void Draw_Box_Header(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2);
		void Draw_Box_Footer(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2);
		void Print_Box_Title(uint8_t _X1, uint8_t _Y1, uint8_t _X2, String _Title);
		void Draw_Horizontal_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length, bool _End);
		void Draw_Vertical_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length);
		void Draw_3Row_Stat_Table(uint8_t _X1, uint8_t _Y1);
		void Draw_3Row_Abstract_Table(uint8_t _X1, uint8_t _Y1);
		void Draw_1Row_Stat_Table(uint8_t _X1, uint8_t _Y1, String _Variable);
		void Draw_3Row_Limit_Table(uint8_t _X1, uint8_t _Y1);

		// Predefined Drawing Functions
		void Dot(uint8_t _X, uint8_t _Y, uint8_t _Count);
		void Bracket(uint8_t _X, uint8_t _Y, uint8_t _Space);
		void FilterStat(void);

};

extern Console Terminal;

#endif /* defined(__Console__) */