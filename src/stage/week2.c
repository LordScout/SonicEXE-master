#include "week2.h"

#include "../mem.h"
#include "../archive.h"

//Week 2 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //Background
	Gfx_Tex tex_back1; //Window
} Back_Week2;

//Week 2 background functions
void Back_Week2_DrawBG(StageBack *back)
{
	Back_Week2 *this = (Back_Week2*)back;
	
	fixed_t fx, fy;
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	//Draw window
	RECT window_src = {0, 0, 256, 144};
	RECT_FIXED window_dst = {
		FIXED_DEC(-240,1) - fx,
		FIXED_DEC(-155,1) - fy,
		FIXED_DEC(512,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back1, &window_src, &window_dst, stage.camera.bzoom);
	
	//Draw window light
	RECT windowl_src = {0, 0, 0, 0};
	RECT_FIXED windowl_dst = {
		FIXED_DEC(-180,1) - fx,
		FIXED_DEC(12,1) - fy,
		FIXED_DEC(512,1),
		FIXED_DEC(512,1)
	};
	
	Stage_DrawTex(&this->tex_back1, &windowl_src, &windowl_dst, stage.camera.bzoom);
	
	//Draw background
	RECT back_src = {0, 0, 256, 201};
	RECT_FIXED back_dst = {
		FIXED_DEC(-275,1) - fx,
		FIXED_DEC(-170,1) - fy,
		FIXED_DEC(450,1),
		FIXED_DEC(425,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &back_src, &back_dst, stage.camera.bzoom);
	
	#if SCREEN_WIDTH > 320
		RECT backl_src = {0, 0, 1, 256};
		RECT_FIXED backl_dst = {
			FIXED_DEC(-185,1) - FIXED_DEC(SCREEN_WIDEADD,2) - fx,
			FIXED_DEC(-125,1) - fy,
			FIXED_DEC(SCREEN_WIDEADD,2),
			FIXED_DEC(267,1)
		};
		RECT backr_src = {255, 0, 0, 256};
		RECT_FIXED backr_dst = {
			FIXED_DEC(168,1) - fx,
			FIXED_DEC(-125,1) - fy,
			FIXED_DEC(SCREEN_WIDEADD,2),
			FIXED_DEC(267,1)
		};
		
		Stage_DrawTex(&this->tex_back0, &backl_src, &backl_dst, stage.camera.bzoom);
		Stage_DrawTex(&this->tex_back0, &backr_src, &backr_dst, stage.camera.bzoom);
	#endif
}

void Back_Week2_Free(StageBack *back)
{
	Back_Week2 *this = (Back_Week2*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week2_New(void)
{
	//Allocate background structure
	Back_Week2 *this = (Back_Week2*)Mem_Alloc(sizeof(Back_Week2));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = NULL;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week2_DrawBG;
	this->back.free = Back_Week2_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK2\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Mem_Free(arc_back);
	
	return (StageBack*)this;
}
