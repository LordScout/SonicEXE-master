#include "week1.h"

#include "../archive.h"
#include "../mem.h"
#include "../stage.h"

//Week 1 background structure
typedef struct
{
	//Stage background base structure
	StageBack back;
	
	//Textures
	Gfx_Tex tex_back0; //Stage and back
	Gfx_Tex tex_back1; //Curtains
} Back_Week1;

//Week 1 background functions
void Back_Week1_DrawBG(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	fixed_t fx, fy;
	
	//Draw curtains
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT curtainl_src = {0, 0, 70, 206};
	RECT_FIXED curtainl_dst = {
		FIXED_DEC(-260,1) - fx,
		FIXED_DEC(-120,1) - fy,
		FIXED_DEC(70,1),
		FIXED_DEC(206,1)
	};
	RECT curtainr_src = {0, 0, 0, 0};
	RECT_FIXED curtainr_dst = {
		FIXED_DEC(1,1) + FIXED_DEC(SCREEN_WIDEOADD,2) - fx,
		FIXED_DEC(1,1) - fy,
		FIXED_DEC(1,1),
		FIXED_DEC(1,1)
	};
	
	Stage_DrawTex(&this->tex_back1, &curtainl_src, &curtainl_dst, stage.camera.bzoom);
	Stage_DrawTex(&this->tex_back1, &curtainr_src, &curtainr_dst, stage.camera.bzoom);
	
	//Draw stage
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT stage_src = {0, 0, 256, 59};
	RECT_FIXED stage_dst = {
		FIXED_DEC(-255,1) - FIXED_DEC(SCREEN_WIDEOADD,2) - fx,
		FIXED_DEC(50,1) - fy,
		FIXED_DEC(428,1) + FIXED_DEC(SCREEN_WIDEOADD,1),
		FIXED_DEC(106,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &stage_src, &stage_dst, stage.camera.bzoom);
	
	//Draw back
	fx = stage.camera.x * 2 / 3;
	fy = stage.camera.y * 2 / 3;
	
	RECT backl_src = {0, 59, 256, 197};
	RECT_FIXED backl_dst = {
		FIXED_DEC(-250,1) - fx,
		FIXED_DEC(-175,1) - fy,
		FIXED_DEC(450,1),
		FIXED_DEC(350,1)
	};
	RECT backr_src = {0, 0, 0, 0};
	RECT_FIXED backr_dst = {
		FIXED_DEC(60,1) - fx,
		FIXED_DEC(-110,1) - fy,
		FIXED_DEC(136,1),
		FIXED_DEC(120,1)
	};
	RECT backf_src = {0, 59, 1, 1};
	RECT backf_dst = {
		0,
		0,
		SCREEN_WIDTH,
		SCREEN_HEIGHT,
	};
	
	Stage_DrawTex(&this->tex_back0, &backl_src, &backl_dst, stage.camera.bzoom);
	Stage_DrawTex(&this->tex_back0, &backr_src, &backr_dst, stage.camera.bzoom);
	Gfx_DrawTex(&this->tex_back0, &backf_src, &backf_dst);
}

void Back_Week1_Free(StageBack *back)
{
	Back_Week1 *this = (Back_Week1*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week1_New(void)
{
	//Allocate background structure
	Back_Week1 *this = (Back_Week1*)Mem_Alloc(sizeof(Back_Week1));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = NULL;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week1_DrawBG;
	this->back.free = Back_Week1_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK1\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);
	Mem_Free(arc_back);
	
	return (StageBack*)this;
}
