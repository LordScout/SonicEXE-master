#define XA_LENGTH(x) (((u64)(x) * 75) / 100 * IO_SECT_SIZE) //Centiseconds to sectors in bytes (w)

typedef struct
{
	XA_File file;
	u32 length;
} XA_TrackDef;

static const XA_TrackDef xa_tracks[] = {
	//MENU.XA
	{XA_Menu, XA_LENGTH(7130)}, //XA_GettinFreaky
	{XA_Menu, XA_LENGTH(3840)},  //XA_GameOver
	//WEEK1A.XA
	{XA_Week1A, XA_LENGTH(18800)}, //XA_Bopeebo
	{XA_Week1A, XA_LENGTH(17000)}, //XA_Fresh
	//WEEK1B.XA
	{XA_Week1B, XA_LENGTH(12100)}, //XA_Dadbattle
	{XA_Week1B, XA_LENGTH(6800)}, //XA_Tutorial
	//WEEK3A.XA
	{XA_Week3A, XA_LENGTH(7100)},  //XA_Pico
	{XA_Week3A, XA_LENGTH(10000)}, //XA_Philly
	//WEEK3B.XA
	{XA_Week3B, XA_LENGTH(10700)}, //XA_Blammed
};

static const char *xa_paths[] = {
	"\\MUSIC\\MENU.XA;1",   //XA_Menu
	"\\MUSIC\\WEEK1A.XA;1", //XA_Week1A
	"\\MUSIC\\WEEK1B.XA;1", //XA_Week1B
	"\\MUSIC\\WEEK3A.XA;1", //XA_Week3A
	"\\MUSIC\\WEEK3B.XA;1", //XA_Week3B
	NULL,
};

typedef struct
{
	const char *name;
	boolean vocal;
} XA_Mp3;

static const XA_Mp3 xa_mp3s[] = {
	//MENU.XA
	{"freaky", false},   //XA_GettinFreaky
	{"gameover", false}, //XA_GameOver
	//WEEK1A.XA
	{"bopeebo", true}, //XA_Bopeebo
	{"fresh", true},   //XA_Fresh
	//WEEK1B.XA
	{"dadbattle", true}, //XA_Dadbattle
	{"tutorial", false}, //XA_Tutorial
	//WEEK3A.XA
	{"pico", true},   //XA_Pico
	{"philly", true}, //XA_Philly
	//WEEK3B.XA
	{"blammed", true}, //XA_Blammed
	
	{NULL, false}
};
