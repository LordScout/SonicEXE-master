#include "mom.h"

#include "../mem.h"
#include "../archive.h"
#include "../stage.h"
#include "../main.h"
#include "../timer.h"

//Mom character structure
enum
{
	Mom_ArcMain_Idle0,
	Mom_ArcMain_Idle1,
	Mom_ArcMain_Idle2,
	Mom_ArcMain_Idle3,
	Mom_ArcMain_Left,
	Mom_ArcMain_Left1,
	Mom_ArcMain_Left2,
	Mom_ArcMain_Down,
	Mom_ArcMain_Down1,
	Mom_ArcMain_Down2,
	Mom_ArcMain_Up,
	Mom_ArcMain_Up1,
	Mom_ArcMain_Up2,
	Mom_ArcMain_Right,
	Mom_ArcMain_Right1,
	Mom_ArcMain_Right2,
	
	Mom_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[Mom_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_Mom;

//Mom character definitions
static const CharFrame char_mom_frame[] = {
	{Mom_ArcMain_Idle0, {  0,   0, 161, 231}, { 90, 215}}, //0 idle 1
	{Mom_ArcMain_Idle1, {  0,   0, 162, 231}, { 90, 215}}, //1 idle 2
	{Mom_ArcMain_Idle2, {  0,   0, 160, 231}, { 89, 215}}, //2 idle 3
	{Mom_ArcMain_Idle3, {  0,   0, 162, 231}, { 90, 215}}, //3 idle 4
	
	{Mom_ArcMain_Left, {  0,   0, 184, 220}, {108, 215}}, //4 left 1
	{Mom_ArcMain_Left1, {  0,   0, 185, 221}, {106, 216}}, //5 left 1
	{Mom_ArcMain_Left2, {  0,   0, 185, 220}, {106, 216}},
	
	{Mom_ArcMain_Down, {  0,   0, 181, 202}, {111, 188}}, //6 down 1
	{Mom_ArcMain_Down1, {  0,   0, 172, 207}, {102, 193}}, //7 down 2
	{Mom_ArcMain_Down2, {  0,   0, 171, 206}, {102, 193}}, //7 down 2
	
	{Mom_ArcMain_Up, {  0,   0, 166, 255}, { 89, 241}}, //8 up 1
	{Mom_ArcMain_Up1, {  0,   0, 166, 245}, { 90, 232}}, //9 up 2
	{Mom_ArcMain_Up2, {  0,   0, 165, 241}, { 90, 228}},

	{Mom_ArcMain_Right, {  0,   0, 207, 214}, { 94, 210}}, //10 right 1
	{Mom_ArcMain_Right1, {  0,   0, 196, 215}, {102, 211}}, //11 right 2
	{Mom_ArcMain_Right2, {  0,   0, 197, 214}, {102, 211}}, //11 right 2
};

static const Animation char_mom_anim[CharAnim_Max] = {
	{4, (const u8[]){ 0,  1,  2,  3, ASCR_BACK, 1}}, //CharAnim_Idle
	{3, (const u8[]){ 4,  5, 6, ASCR_BACK, 1}},         //CharAnim_Left
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_LeftAlt
	{3, (const u8[]){ 7,  8, 9, ASCR_BACK, 1}},         //CharAnim_Down
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_DownAlt
	{3, (const u8[]){ 10,  11, 12, ASCR_BACK, 1}},         //CharAnim_Up
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_UpAlt
	{3, (const u8[]){13, 14, 15, ASCR_BACK, 1}},         //CharAnim_Right
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_RightAlt
};

//Mom character functions
void Char_Mom_SetFrame(void *user, u8 frame)
{
	Char_Mom *this = (Char_Mom*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_mom_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_Mom_Tick(Character *character)
{
	Char_Mom *this = (Char_Mom*)character;
	
	//Perform idle dance
	Character_PerformIdle(character);
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_Mom_SetFrame);
	Character_Draw(character, &this->tex, &char_mom_frame[this->frame]);
}

void Char_Mom_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_Mom_Free(Character *character)
{
	Char_Mom *this = (Char_Mom*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_Mom_New(fixed_t x, fixed_t y)
{
	//Allocate mom object
	Char_Mom *this = Mem_Alloc(sizeof(Char_Mom));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_Mom_New] Failed to allocate mom object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_Mom_Tick;
	this->character.set_anim = Char_Mom_SetAnim;
	this->character.free = Char_Mom_Free;
	
	Animatable_Init(&this->character.animatable, char_mom_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character stage information
	this->character.health_i = 4;
	
	this->character.focus_x = FIXED_DEC(65,1);
	this->character.focus_y = FIXED_DEC(-115,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\MOM.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim", //Mom_ArcMain_Idle0
		"idle1.tim", //Mom_ArcMain_Idle1
		"idle2.tim", //Mom_ArcMain_Idle2
		"idle3.tim", //Mom_ArcMain_Idle3
		"left.tim",  //Mom_ArcMain_Left
		"left1.tim",  //Mom_ArcMain_Left1
		"left2.tim",  //Mom_ArcMain_Left2
		"down.tim",  //Mom_ArcMain_Down
		"down1.tim",  //Mom_ArcMain_Down1
		"down2.tim",  //Mom_ArcMain_Down2
		"up.tim",    //Mom_ArcMain_Up
		"up1.tim",    //Mom_ArcMain_Up1
		"up2.tim",    //Mom_ArcMain_Up2
		"right.tim", //Mom_ArcMain_Right
		"right1.tim", //Mom_ArcMain_Right1
		"right2.tim", //Mom_ArcMain_Right2
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
