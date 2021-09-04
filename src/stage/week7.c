#include "week7.h"

#include "../archive.h"
#include "../mem.h"
#include "../stage.h"
#include "../random.h"
#include "../mutil.h"
#include "../timer.h"

//Week 7 background functions
#define TANK_START_X FIXED_DEC(-400,1)
#define TANK_END_X    FIXED_DEC(400,1)
#define TANK_TIME_A FIXED_DEC(25,1)
#define TANK_TIME_B FIXED_DEC(45,1)

static void Back_Week7_LoadPicoChart(Back_Week7 *this)
{
	//Load Pico chart
	this->pico_chart = (u16*)IO_Read("\\WEEK7\\7.3P.CHT;1");
}

void Back_Week7_DrawFG(StageBack *back)
{
	Back_Week7 *this = (Back_Week7*)back;
	
	//Load Pico chart
	if (stage.stage_id == StageId_7_3 && this->pico_chart == NULL)
		Back_Week7_LoadPicoChart(this);
}

void Back_Week7_DrawBG(StageBack *back)
{
	Back_Week7 *this = (Back_Week7*)back;
	
	fixed_t fx, fy;
	
	//Draw foreground
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT fg_src = {0, 0, 256, 241};
	RECT_FIXED fg_dst = {
		FIXED_DEC(-225,1) - fx,
		FIXED_DEC(-225,1) - fy,
		FIXED_DEC(430,1),
		FIXED_DEC(400,1)
	};
	
	Stage_DrawTex(&this->tex_back0, &fg_src, &fg_dst, stage.camera.bzoom);
	
	//Draw ruins
	fx = stage.camera.x >> 2;
	fy = stage.camera.y >> 2;
	
	RECT ruinsf_src = {0, 0,256,200};
	RECT_FIXED ruinsf_dst = {
		FIXED_DEC(-240,1) - fx,
		FIXED_DEC(-200,1) - fy,
		FIXED_DEC(600,1),
		FIXED_DEC(300,1)
	};
	
	Stage_DrawTex(&this->tex_back3, &ruinsf_src, &ruinsf_dst, stage.camera.bzoom);
	
	fx = stage.camera.x / 6;
	fy = stage.camera.y / 6;
	
	RECT ruinsb_src = {0,  0, 256, 91};
	RECT_FIXED ruinsb_dst = {
		FIXED_DEC(-240,1) - fx,
		FIXED_DEC(-60,1) - fy,
		FIXED_DEC(100,1),
		FIXED_DEC(440,1)
	};
	
	Stage_DrawTex(&this->tex_back3, &ruinsb_src, &ruinsb_dst, stage.camera.bzoom);
	
	//Draw clouds
	fx = stage.camera.x;
	fy = stage.camera.y;
	
	RECT cloud_src = {0, 0, 0, 0};
	RECT_FIXED cloud_dst = {
		FIXED_DEC(-260,1) - fx,
		FIXED_DEC(-100,1) - fy,
		FIXED_DEC(26,1),
		FIXED_DEC(26,1)
	};
	
	Stage_DrawTex(&this->tex_back3, &cloud_src, &cloud_dst, stage.camera.bzoom);
	
	//Draw mountains
	fx = stage.camera.x >> 3;
	fy = stage.camera.y >> 3;
	
	RECT mountain_src = {0, 0, 0,  0};
	RECT_FIXED mountain_dst = {
		FIXED_DEC(-200,1) - fx,
		FIXED_DEC(-120,1) - fy,
		FIXED_DEC(260,1),
		FIXED_DEC(130,1)
	};
	
	Stage_DrawTex(&this->tex_back1, &mountain_src, &mountain_dst, stage.camera.bzoom);
}

void Back_Week7_Free(StageBack *back)
{
	Back_Week7 *this = (Back_Week7*)back;
	
	//Free structure
	Mem_Free(this);
}

StageBack *Back_Week7_New(void)
{
	//Allocate background structure
	Back_Week7 *this = (Back_Week7*)Mem_Alloc(sizeof(Back_Week7));
	if (this == NULL)
		return NULL;
	
	//Set background functions
	this->back.draw_fg = Back_Week7_DrawFG;
	this->back.draw_md = NULL;
	this->back.draw_bg = Back_Week7_DrawBG;
	this->back.free = Back_Week7_Free;
	
	//Load background textures
	IO_Data arc_back = IO_Read("\\WEEK7\\BACK.ARC;1");
	Gfx_LoadTex(&this->tex_back0, Archive_Find(arc_back, "back0.tim"), 0);
	Gfx_LoadTex(&this->tex_back1, Archive_Find(arc_back, "back1.tim"), 0);	
	Gfx_LoadTex(&this->tex_back3, Archive_Find(arc_back, "back3.tim"), 0);
	Mem_Free(arc_back);

	
	//Use sky coloured background
	Gfx_SetClear(245, 202, 81);
	
	//Load Pico chart
	if (stage.stage_id == StageId_7_3)
		Back_Week7_LoadPicoChart(this);
	else
		this->pico_chart = NULL;
	
	return (StageBack*)this;
}
