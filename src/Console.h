#ifndef __Console__
#define __Console__

// Define Arduino Library
#ifndef __Arduino__
#include <Arduino.h>
#endif

// Define Registers
#ifndef __Console_Defination__
#include <Console_Defination.h>
#endif

class Console {

	private:
	
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

		void Draw_Box(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2, char *_Text, uint8_t _Number, bool _Header, bool _Footer);
		void Draw_Box_Header(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2);
		void Draw_Box_Footer(uint8_t _X1, uint8_t _Y1, uint8_t _X2, uint8_t _Y2);
		void Print_Box_Title(uint8_t _X1, uint8_t _Y1, uint8_t _X2, String _Title);
		void Draw_Horizontal_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length, bool _End);
		void Draw_Vertical_Divider(uint8_t _X1, uint8_t _Y1, uint8_t _Length);
		void Draw_3Row_Stat_Table(uint8_t _X1, uint8_t _Y1);
		void Draw_1Row_Stat_Table(uint8_t _X1, uint8_t _Y1, String _Variable);

		void B100BB(void);

};

extern Console Terminal;

#endif /* defined(__Console__) */