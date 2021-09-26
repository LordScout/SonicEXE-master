#include "dad.h"

#include "../mem.h"
#include "../archive.h"
#include "../stage.h"
#include "../main.h"

//Dad character structure
enum
{
	Dad_ArcMain_Idle0,
	Dad_ArcMain_Idle1,
	Dad_ArcMain_Idle2,
	Dad_ArcMain_Idle3,
	Dad_ArcMain_Left,
	Dad_ArcMain_Left1,
	Dad_ArcMain_Left2,
	Dad_ArcMain_Left3,
	Dad_ArcMain_Down,
	Dad_ArcMain_Down1,
	Dad_ArcMain_Down2,
	Dad_ArcMain_Up,
	Dad_ArcMain_Up1,
	Dad_ArcMain_Up2,
	Dad_ArcMain_Right,
	Dad_ArcMain_Right1,
	Dad_ArcMain_Right2,
	
	Dad_Arc_Max,
};

typedef struct
{
	//Character base structure
	Character character;
	
	//Render data and state
	IO_Data arc_main;
	IO_Data arc_ptr[Dad_Arc_Max];
	
	Gfx_Tex tex;
	u8 frame, tex_id;
} Char_Dad;

//Dad character definitions
static const CharFrame char_dad_frame[] = {
	{Dad_ArcMain_Idle0, {  0,   0, 134, 182}, { 42, 178}}, //0 idle 1
	{Dad_ArcMain_Idle1, {  0,   0, 132, 183}, { 40, 178}}, //1 idle 2
	{Dad_ArcMain_Idle2, {  0,   0, 128, 182}, { 36, 178}}, //2 idle 3
	{Dad_ArcMain_Idle3, {  0,   0, 129, 182}, { 37, 178}}, //3 idle 4
	
	{Dad_ArcMain_Left, {  0,   0,  228, 141}, {155, 130}}, //4 left 1
	{Dad_ArcMain_Left1, {  0,   0, 226, 142}, {156, 131}}, //5 left 2
	{Dad_ArcMain_Left2, {  0,   0, 225, 142}, {156, 131}}, //5 left 2
	{Dad_ArcMain_Left3, {  0,   0, 226, 142}, {156, 131}}, //5 left 2

	{Dad_ArcMain_Down, {  0,   0, 154, 137}, { 43, 133}}, //6 down 1
	{Dad_ArcMain_Down1, {  0,   0, 156, 141}, { 45, 137}}, //7 down 2
	{Dad_ArcMain_Down2, {  0,   0, 155, 140}, { 44, 136}}, //7 down 2

	{Dad_ArcMain_Up, {  0,   0, 129, 188}, { 54, 188}}, //8 up 1
	{Dad_ArcMain_Up1, {  0,   0, 124, 181}, { 50, 180}}, //9 up 2
	{Dad_ArcMain_Up2, {  0,   0, 124, 180}, { 50, 180}}, //9 up 2
	
	{Dad_ArcMain_Right, {  0,   0, 161, 167}, { 50, 164}}, //10 right 1
	{Dad_ArcMain_Right1, {  0,   0, 162, 168}, { 50, 164}}, //11 right 2
	{Dad_ArcMain_Right2, {  0,   0, 162, 168}, { 50, 164}}, //11 right 2
};

static const Animation char_dad_anim[CharAnim_Max] = {
	{2, (const u8[]){ 1,  2,  3,  0, ASCR_BACK, 1}}, //CharAnim_Idle
	{2, (const u8[]){ 4,  5, 6, 7, ASCR_BACK, 1}},         //CharAnim_Left
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_LeftAlt
	{2, (const u8[]){ 8,  9, 10, ASCR_BACK, 1}},         //CharAnim_Down
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_DownAlt
	{2, (const u8[]){11, 12, 13, ASCR_BACK, 1}},         //CharAnim_Up
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_UpAlt
	{2, (const u8[]){14, 15, 16, ASCR_BACK, 1}},         //CharAnim_Right
	{0, (const u8[]){ASCR_CHGANI, CharAnim_Idle}},   //CharAnim_RightAlt
};

//Dad character functions
void Char_Dad_SetFrame(void *user, u8 frame)
{
	Char_Dad *this = (Char_Dad*)user;
	
	//Check if this is a new frame
	if (frame != this->frame)
	{
		//Check if new art shall be loaded
		const CharFrame *cframe = &char_dad_frame[this->frame = frame];
		if (cframe->tex != this->tex_id)
			Gfx_LoadTex(&this->tex, this->arc_ptr[this->tex_id = cframe->tex], 0);
	}
}

void Char_Dad_Tick(Character *character)
{
	Char_Dad *this = (Char_Dad*)character;
	
	if ((stage.stage_id == StageId_1_2) && stage.song_step >= 908)
	{
		this->character.focus_x = FIXED_DEC(65, 1);
		this->character.focus_y = FIXED_DEC(-115, 1);
		this->character.focus_zoom = FIXED_DEC(13, 10);
	}

	if ((stage.stage_id == StageId_1_2) && stage.song_step >= 912)
	{
		this->character.focus_x = FIXED_DEC(65, 1);
		this->character.focus_y = FIXED_DEC(-115, 1);
		this->character.focus_zoom = FIXED_DEC(18, 10);
	}

	if ((stage.stage_id == StageId_1_2) && stage.song_step >= 916)
	{
		this->character.focus_x = FIXED_DEC(65, 1);
		this->character.focus_y = FIXED_DEC(-115, 1);
		this->character.focus_zoom = FIXED_DEC(20, 10);
	}

	if ((stage.stage_id == StageId_1_2) && stage.song_step >= 920)
	{
		this->character.focus_x = FIXED_DEC(65, 1);
		this->character.focus_y = FIXED_DEC(-115, 1);
		this->character.focus_zoom = FIXED_DEC(1, 1);
	}

	//Perform idle dance
	if ((character->pad_held & (INPUT_LEFT | INPUT_DOWN | INPUT_UP | INPUT_RIGHT)) == 0)
		Character_PerformIdle(character);
	
	//Animate and draw
	Animatable_Animate(&character->animatable, (void*)this, Char_Dad_SetFrame);
	Character_Draw(character, &this->tex, &char_dad_frame[this->frame]);
}

void Char_Dad_SetAnim(Character *character, u8 anim)
{
	//Set animation
	Animatable_SetAnim(&character->animatable, anim);
	Character_CheckStartSing(character);
}

void Char_Dad_Free(Character *character)
{
	Char_Dad *this = (Char_Dad*)character;
	
	//Free art
	Mem_Free(this->arc_main);
}

Character *Char_Dad_New(fixed_t x, fixed_t y)
{
	//Allocate dad object
	Char_Dad *this = Mem_Alloc(sizeof(Char_Dad));
	if (this == NULL)
	{
		sprintf(error_msg, "[Char_Dad_New] Failed to allocate dad object");
		ErrorLock();
		return NULL;
	}
	
	//Initialize character
	this->character.tick = Char_Dad_Tick;
	this->character.set_anim = Char_Dad_SetAnim;
	this->character.free = Char_Dad_Free;
	
	Animatable_Init(&this->character.animatable, char_dad_anim);
	Character_Init((Character*)this, x, y);
	
	//Set character stage information
	this->character.spec = 0;
	
	this->character.health_i = 1;
	
	this->character.focus_x = FIXED_DEC(65,1);
	this->character.focus_y = FIXED_DEC(-115,1);
	this->character.focus_zoom = FIXED_DEC(1,1);
	
	//Load art
	this->arc_main = IO_Read("\\CHAR\\DAD.ARC;1");
	
	const char **pathp = (const char *[]){
		"idle0.tim", //Dad_ArcMain_Idle0
		"idle1.tim", //Dad_ArcMain_Idle1
		"idle2.tim", //Dad_ArcMain_Idle2
		"idle3.tim", //Dad_ArcMain_Idle3
		"left.tim",  //Dad_ArcMain_Left
		"left1.tim",  //Dad_ArcMain_Left1
		"left2.tim",  //Dad_ArcMain_Left2
		"left3.tim",  //Dad_ArcMain_Left3
		"down.tim",  //Dad_ArcMain_Down
		"down1.tim",  //Dad_ArcMain_Down1
		"down2.tim",  //Dad_ArcMain_Down2
		"up.tim",    //Dad_ArcMain_Up
		"up1.tim",    //Dad_ArcMain_Up1
		"up2.tim",    //Dad_ArcMain_Up2
		"right.tim", //Dad_ArcMain_Right
		"right1.tim", //Dad_ArcMain_Right1
		"right2.tim", //Dad_ArcMain_Right2
		NULL
	};
	IO_Data *arc_ptr = this->arc_ptr;
	for (; *pathp != NULL; pathp++)
		*arc_ptr++ = Archive_Find(this->arc_main, *pathp);
	
	//Initialize render state
	this->tex_id = this->frame = 0xFF;
	
	return (Character*)this;
}
