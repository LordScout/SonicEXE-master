#include "loadscr.h"

#include "gfx.h"
#include "timer.h"
#include "io.h"
#include "audio.h"
#include "trans.h"

//Loading screen functions
void LoadScr_Start(void)
{
	//Stop music and make sure frame has been drawn
	Audio_StopXA();
	Gfx_Flip();
	
	//Load loading screen texture
	RECT loading_src = {0, 0, 256, 256};
	RECT loading_dst = {(SCREEN_WIDTH - 320) >> 1, (SCREEN_HEIGHT - 240) >> 1, 322, 241};
	Gfx_Tex loading_tex;
	Gfx_SetClear(202, 255, 77);
	Gfx_LoadTex(&loading_tex, IO_Read("\\MENU\\LOADING.TIM;1"), GFX_LOADTEX_FREE);
	Timer_Reset();
	
	//Draw loading screen and run transition
	Trans_Set();
	
	while (!Trans_Idle())
	{
		//Draw loading screen and end frame
		Timer_Tick();
		Trans_Tick();
		Gfx_DrawTex(&loading_tex, &loading_src, &loading_dst);
		Gfx_Flip();
	}
	
	//Draw an extra frame to avoid double buffering issues
	Gfx_DrawTex(&loading_tex, &loading_src, &loading_dst);
	Gfx_Flip();
}

void LoadScr_End(void)
{
	//Handle transition out
	Timer_Reset();
	Trans_Start();
	Gfx_DisableClear();
	while (!Trans_Tick())
	{
		Timer_Tick();
		Gfx_Flip();
	}
	Gfx_EnableClear();
}
