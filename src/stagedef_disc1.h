	{ //StageId_1_1 (Too Slow)
		//Characters
		{Char_BF_New,    FIXED_DEC(60,1),  FIXED_DEC(100,1)},
		{Char_XmasP_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,     FIXED_DEC(0,1),    FIXED_DEC(0,1)},
		
		//Stage background
		Back_Week1_New,
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(1,1),FIXED_DEC(13,10)},
		1, 1,
		XA_Bopeebo, 0,
		
		StageId_1_2, 0,
	},
	{ //StageId_1_2 (Endless)
		//Characters
		{Char_BF_New,    FIXED_DEC(60,1),  FIXED_DEC(100,1)},
		{Char_Dad_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,     FIXED_DEC(1000,1),    FIXED_DEC(1000,1)},
		
		//Stage background
		Back_Week2_New,
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(13,10),FIXED_DEC(18,10)},
		1, 2,
		XA_Fresh, 2,
		
		StageId_1_3, 0,
	},
	{ //StageId_1_3 (Execution)
		//Characters
		{Char_BF_New,    FIXED_DEC(60,1),  FIXED_DEC(100,1)},
		{Char_Mom_New, FIXED_DEC(-120,1),  FIXED_DEC(100,1)},
		{Char_GF_New,     FIXED_DEC(1000,1),    FIXED_DEC(1000,1)},
		
		//Stage background
		Back_Week7_New,
		
		//Song info
		{FIXED_DEC(13,10),FIXED_DEC(15,10),FIXED_DEC(23,10)},
		1, 3,
		XA_Dadbattle, 0,
		
		StageId_1_3, 0
	},
	{ //StageId_1_4 (Tutorial)
		//Characters
		{Char_BF_New,   FIXED_DEC(60,1),  FIXED_DEC(100,1)},
		{Char_Dad_New,   FIXED_DEC(0,1),  FIXED_DEC(-15,1)}, //TODO
		{Char_GF_New,    FIXED_DEC(0,1),    FIXED_DEC(0,1)},
		
		//Stage background
		Back_Week1_New,
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(1,1),FIXED_DEC(1,1)},
		1, 4,
		XA_Tutorial, 2,
		
		StageId_1_4, 0
	},

	{ //StageId_2_1 (Spookeez)
		//Characters
		{Char_BF_New,      FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Spook_New,  FIXED_DEC(-90,1),   FIXED_DEC(85,1)},
		{Char_GF_New,       FIXED_DEC(0,1),  FIXED_DEC(-15,1)},

		//Stage background
		Back_Week2_New,

		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(17,10),FIXED_DEC(24,10)},
		2, 1,
		XA_Pico, 0,

		StageId_2_2, STAGE_LOAD_FLAG
	},
	{ //StageId_2_2 (South)
		//Characters
		{Char_BF_New,      FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Spook_New,  FIXED_DEC(-90,1),   FIXED_DEC(85,1)},
		{Char_GF_New,       FIXED_DEC(0,1),  FIXED_DEC(-15,1)},

		//Stage background
		Back_Week2_New,

		//Song info
		{FIXED_DEC(11,10),FIXED_DEC(15,10),FIXED_DEC(22,10)},
		2, 2,
		XA_Pico, 2,

		StageId_2_3, STAGE_LOAD_FLAG | STAGE_LOAD_OPPONENT
	},
	{ //StageId_2_3 (Monster)
		//Characters
		{Char_BF_New,      FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Spook_New,  FIXED_DEC(-90,1),   FIXED_DEC(85,1)},
		{Char_GF_New,       FIXED_DEC(0,1),  FIXED_DEC(-15,1)},

		//Stage background
		Back_Week2_New,

		//Song info
		{FIXED_DEC(13,10),FIXED_DEC(13,10),FIXED_DEC(16,10)},
		2, 3,
		XA_Pico, 0,

		StageId_2_3, 0
	},
	
	{ //StageId_3_1 (Pico)
		//Characters
		{Char_BF_New,     FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Pico_New, FIXED_DEC(-105,1),   FIXED_DEC(85,1)},
		{Char_GF_New,      FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week3_New,
		
		//Song info
		{FIXED_DEC(12,10),FIXED_DEC(14,10),FIXED_DEC(16,10)},
		3, 1,
		XA_Pico, 0,
		
		StageId_3_1, STAGE_LOAD_FLAG
	},
	{ //StageId_3_2 (Philly)
		//Characters
		{Char_BF_New,     FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Pico_New, FIXED_DEC(-105,1),   FIXED_DEC(85,1)},
		{Char_GF_New,      FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week3_New,
		
		//Song info
		{FIXED_DEC(1,1),FIXED_DEC(13,10),FIXED_DEC(2,1)},
		3, 2,
		XA_Philly, 2,
		
		StageId_3_3, STAGE_LOAD_FLAG
	},
	{ //StageId_3_3 (Blammed)
		//Characters
		{Char_BF_New,     FIXED_DEC(56,1),   FIXED_DEC(85,1)},
		{Char_Pico_New, FIXED_DEC(-105,1),   FIXED_DEC(85,1)},
		{Char_GF_New,      FIXED_DEC(0,1),  FIXED_DEC(-15,1)},
		
		//Stage background
		Back_Week3_New,
		
		//Song info
		{FIXED_DEC(12,10),FIXED_DEC(15,10),FIXED_DEC(23,10)},
		3, 3,
		XA_Blammed, 0,
		
		StageId_3_3, 0
	},
