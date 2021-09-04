#ifndef _FONT_H
#define _FONT_H

#include "gfx.h"

//Font types
typedef enum
{
	Font_Bold,
} Font;

typedef enum
{
	FontAlign_Left,
	FontAlign_Center,
	FontAlign_Right,
} FontAlign;

typedef struct FontData
{
	//Font functions and data
	s32 (*get_width)(struct FontData *this, const char *text);
	void (*draw)(struct FontData *this, const char *text, s32 x, s32 y, FontAlign align);
	
	Gfx_Tex tex;
} FontData;

//Font functions
void FontData_Load(FontData *this, Font font);

#endif
