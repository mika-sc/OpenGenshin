
/*
	OPEN GENSHIN PROJECT
	
	An open-source Genshin Impact for DOS systems.
	
	Release under GNU GPL v3.0 .
	
	Date 03/06/23
*/
#include "lt__eng.h"
#include <time.h>
//#include "sprites.h"
//#include "animis.h"

LT_Sprite_State LT_Player_State;

byte Player_Animation[] = {		//Animations for player are fixed at these offsets
	16,16,16,16,17,17,17,17,	// 0 UP
	18,18,18,18,19,19,19,19,	// 1 DOWN
	8,9,10,11,12,13,14,15,		// 2 LEFT
	0,1,2,3,4,5,6,7,			// 3 RIGHT
	25,25,25,25,25,25,25,25,	// 4 JUMP/FALL LEFT
	24,24,24,24,24,24,24,24,	// 5 JUMP/FALL RIGHT
	20,20,20,21,21,22,22,23,	// 6 custom (die)
	26,27,28,29,29,28,27,26,	// 7 custom (happy)
	
};
byte Menu_Cursor_Animation[] = {0,1,2,3,3,3,3,3};
byte Ship_Animation[] = {//
	0,1,0,1,0,1,0,1,
	0,0,1,0,1,0,1,0,
	0,0,0,0,1,1,1,1,
	0,0,0,0,1,1,1,1,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,1,1,2,2,2,3,
	0,0,0,0,1,1,1,1,
};
byte Player_Animation_2[] = {//Prehistorik man animations	
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	5,5,6,6,7,7,8,8,
	0,0,1,1,2,2,3,3,
	9,9,9,9,9,9,9,9,
	4,4,4,4,4,4,4,4,
	4,4,4,4,4,4,4,4,
};
byte Enemy0_Animation[] = {//
	0,0,1,1,0,0,1,1,
	2,2,3,3,2,2,3,3,
	4,4,5,5,4,4,5,5,	
	6,6,7,7,6,6,7,7,		
	0,0,0,0,0,0,0,0,	
};
byte Enemy1_Animation[] = {//Bouncing balls
	0,1,2,3,4,3,2,1,
	0,1,2,3,4,3,2,1,
	0,1,2,3,4,3,2,1,	
	0,1,2,3,4,3,2,1,		
	0,1,2,3,4,3,2,1,	
};
byte Enemy2_Animation[] = {//Walking bots
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	8,9,10,11,12,13,14,15,	
	0,1,2,3,4,5,6,7,		
	0,0,0,0,0,0,0,0,	
};
byte Ball_Animation[] = {
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,0,0,0,0,0,0,0,
	0,1,2,3,4,5,6,7,	//Fall/Die
	};
byte Rocket_Animation[] = {0,1,0,2,0,1,0,2};




int running = 1;
int x,y = 0;
int i,j = 0;
int Scene = 0;
int menu_option = 0;
int menu_pos[10] = {108-16,116-16,124-16,132-16,140-16,148-16};
int game = 0;
int random;

//char VERSION[] = {'ALPHADOS1.0.0-230307-230307'};

void Print_Info_Wait_ENTER(word x, word y, int w, int h, unsigned char* text);
void Display_Intro();
void Load_Map();
void Run_Map();
void Save_Game();
void Charas_Set();
void Teleport();
void Wish();

void main(){
	LT_Setup();	//Allways the first, loads setup and initializes engine
	//if (LT_VIDEO_MODE == 0) LT_Logo("fi/logo_EGA.bmp");	//If you want a logo
	//if (LT_VIDEO_MODE == 1) 
	LT_Logo("fi/logo.bmp");

	//Load these or the engine will crash
	LT_Load_Font("fi/font.bmp"); //Load a font
	//Load a custom loading animation for Loading process
	//if (LT_VIDEO_MODE == 0) LT_Load_Animation("GFX/loadinge.bmp");
	//if (LT_VIDEO_MODE == 1) 
	LT_Load_Animation("fi/loading.bmp");

	LT_Set_Animation(4); //Loading animation speed
	
	//That's it, let's play
	
	LT_MODE = 0;
	game = 0;
	//MENU
	while (running){
		switch (game){
			case 0: Display_Intro(); break;
			case 1: Load_Map(); game = 2; break;
			case 2: Run_Map(); break;
			case 3: Save_Game(); break;
			//case 4: Run_Platform(); break;
			case 5: Charas_Set(); break;
			//case 6: Run_Platform1(); break;
			case 7: Teleport(); break;
			//case 8: Run_Puzzle(); break;
			case 9: Wish(); break;
			//case 10: Run_Shooter(); break;*/
		} 
	}
	
	LT_ExitDOS();
	
}


void Load_Sprites(){

    LT_Load_Tiles("fi/teyvat.bmp");
	LT_Load_Sprite("fi/aether.bmp",8,Player_Animation);
	LT_Load_Sprite("fi/ms_01ab.bmp",9,Enemy0_Animation);
	LT_Load_Sprite("fi/ms_02ky.bmp",12,Enemy1_Animation);
    LT_Load_Sprite("fi/ms_03ls.bmp",12,Enemy1_Animation);
    LT_Load_Sprite("fi/ms_04je.bmp",12,Enemy1_Animation);
    LT_Load_Sprite("fi/ms_05vt.bmp",12,Enemy1_Animation);

}

void Load_Map(){

	LT_Set_Loading_Interrupt(); 
	
	LT_Load_Map("fi/teyvat.tmx");
	/*if (LT_VIDEO_MODE == 0){
		LT_Load_Tiles("gfx/top_EGA.bmp");
		LT_Load_Sprite("GFX/playere.bmp",8,Player_Animation);
		LT_Load_Sprite("GFX/enemy2e.bmp",9,Enemy0_Animation);
		LT_Load_Sprite("GFX/enemy3e.bmp",12,Enemy1_Animation);
	}
	if (LT_VIDEO_MODE == 1){*/
		Load_Sprites();
	//}
	LT_Load_Music("music/adlib/game.imf",1);

	LT_Delete_Loading_Interrupt();
	
	LT_MODE = 0;
	
	Scene = 2;
}

void Run_Map(){
	int n;
	int dying = 0;
	LT_Reset_Sprite_Stack();
	LT_Init_Sprite(8,8*16,4*16);
	LT_Set_AI_Sprites(9,12,0,1);
	LT_Set_Sprite_Animation_Speed(8,1);
	LT_Set_Map(0);//unused y parameter
	
	Scene = 2;
	LT_MODE = 0;
	LT_SPRITE_MODE = 1;
	LT_IMAGE_MODE = 0;
	LT_ENDLESS_SIDESCROLL = 0;
	
	//Print_Info_Wait_ENTER(1,2,36,3,"A Top down style level, You can use it to create very symple adventure  games. PRESS ENTER.");
	
	while(Scene == 2){
		
		//LT_Print LT_Sprite_Stack/*cards>>1*/);
		
		LT_Cycle_palette(1,4);
		
		if (!dying){
			//In this mode sprite is controlled using U D L R
			LT_Player_State = LT_move_player(8);
			//Player animations run inside above function
		}
		
		//If collision tile = ?, end level
		if ((LT_Player_State.tilecol_number == 11) || (LT_Keys[LT_ESC])){
			Scene = 1; game = 0;
		}
		if (sprite[8].pos_y > (19*16)){Scene = 1; game = 0;}
		//if ((SCR_X>>1)&1)outportb(0x3d8, 1);
		//else outportb(0x3d8, 9);
		if (LT_Player_Col_Enemy()) dying = 1;
		
		if (dying) {
			LT_Set_Sprite_Animation(8,6);
			LT_Set_Sprite_Animation_Speed(8,8);
			if (sprite[8].frame == 23){
				//sfx
				Scene = 1;
				game = 2;
				sleep(1);
				LT_Fade_out(); 
			}
		}
		
		LT_Play_Music();
		//SCR_X and SCR_Y are predefined global variables 
		LT_Update(1,8);
	}
}

void Print_Info_Wait_ENTER(word x, word y, int w, int h, unsigned char* text){
	LT_Text_Speak_End = 0;
	while (!LT_Text_Speak_End){
		LT_Draw_Text_Box(x,y,w,h,1,text);
		LT_WaitVsync();
	}
	LT_Text_Speak_End = 0;
	Clearkb();
	while (!LT_Keys[LT_ENTER]);
	Clearkb();
	LT_Delete_Text_Box(x,y,w,h);
}


void Display_Intro(){
	int key_timmer = 0;
	int change = 0; //wait between key press
	int transition = 0;
	int Speaker_Menu[16] = {56,52,51,45,40,30,25,15,10,5,0,0,0,0,0,0};
	int Speaker_Select[16] = {90,80,70,60,50,30,10,5,10,30,50,60,70,60,50,30};
	unsigned char Adlib_Bell_Sound[11] = {0x02,0x07,0x02,0x00,0xF5,0x93,0xCB,0xF0,0x00,0x00,0x01};
	unsigned char Adlib_Select_Sound[11] = {0x62,0x04,0x04,0x1E,0xF7,0xB1,0xF0,0xF0,0x00,0x00,0x03};
	unsigned char Adlib_PacMan_Sound[11] = {0xF9,0xF3,0x00,0x94,0xF3,0x91,0xF0,0xF1,0x0E,0x00,0x03};

	time_t corrTime;
	struct tm *lt;
	int corrHour;
	
	time(&corrTime);
	lt = gmtime(&corrTime);
	corrHour = lt->tm_hour; 


	Scene = 1;
	menu_option = 0;
	SCR_X = 0;SCR_Y = 0;
	
	LT_SPRITE_MODE = 0;
	LT_IMAGE_MODE = 1;
	LT_ENDLESS_SIDESCROLL = 0;
	//Enable this to load stuff, it will fade out automatically
	//and show a cute animation
	LT_Set_Loading_Interrupt();
		/*if (LT_VIDEO_MODE == 0){
			LT_Load_Image("GFX/INTREGA.bmp"); //Load a 320x200 bkg image
			LT_Load_Sprite("GFX/orbE.bmp",0,0);
			LT_Load_Sprite("GFX/cursorbe.bmp",8, Menu_Cursor_Animation); //Load sprites to one of the fixed structs
			LT_Load_Sprite("GFX/RocketE.bmp",20,0);
		}
		if (LT_VIDEO_MODE == 1){
			LT_Load_Image("GFX/INTRVGA.bmp"); //Load a 320x240 bkg image
			LT_Load_Sprite("GFX/orb.bmp",0,0);
			LT_Load_Sprite("GFX/cursorb.bmp",8, Menu_Cursor_Animation); //Load sprites to one of the fixed structs
			LT_Load_Sprite("GFX/Rocketc.bmp",20,0);
		}*/
		if(corrHour >= 7 && corrHour <= 15)LT_Load_Image("fi/01menu.bmp");
		else LT_Load_Image("fi/02menu.bmp");
		//LT_Load_Sprite("fi/orb.bmp",0,0);
		LT_Load_Sprite("fi/cursor.bmp",8, Menu_Cursor_Animation); //Load sprites to one of the fixed structs
		//LT_Load_Sprite("GFX/Rocketc.bmp",20,0);

		
		//Some music
		if(corrHour >= 7 && corrHour <= 15)LT_Load_Music("music/ADLIB/GENSHIN/ms01them.imf",0);
		else LT_Load_Music("music/ADLIB/GENSHIN/ms02twil.imf",0);

	LT_Delete_Loading_Interrupt(); //End loading
	
	LT_Set_Sprite_Animation(8,0);
	LT_Set_Sprite_Animation_Speed(8,6);
	LT_MODE = 0;
	
	//Init Sprite at positions
	//LT_Init_Sprite(0,32,32);
	LT_Init_Sprite(8,0,0);
	//LT_Init_Sprite(20,0,0);
	
	//This box won't talk
	LT_Text_Speak_End = 0;
	LT_Draw_Text_Box(13,10,12,7,0,"SELECT                   LOAD GAME   SAVE GAME   CHARACTER   TELEPORT    WISH      ");
	//LT_Draw_Text_Box(13,10,12,7,0,"SELECT  DEMO             TOP DOWN    PLATFORM    PLATFORM 1  PUZZLE      SHOOTER   ");
	while (Scene == 1) {
		
		//sprite[0].pos_x++;
		//sprite[0].pos_y = 64 + (LT_COS[j]>>3);
		//if (sprite[0].pos_x > 320) sprite[0].pos_x = 0;
		
		//sprite[0].pos_x = 80 + (LT_COS[j]>>4);
		sprite[8].pos_x = 80 + (LT_COS[j]>>4);
		sprite[8].pos_y = transition+menu_pos[menu_option+1];
		
		//sprite[20].pos_x = 230;
		//sprite[20].pos_y = 60+ (LT_COS[j]>>3);
		
		if (i > 360) i = 0;
		i+=2;
		if (j > 356) {j = 0; sprite[8].anim_counter = 0;}
		j+=8;
		
		//Select 
		switch (change){
			case 0:
				if (LT_Keys[LT_UP] == 1) change = 1;
				if (LT_Keys[LT_DOWN] == 1) change = 2;
			break;
			case 1:
				if (menu_option > 0) transition--;
				else change = 0;
				if (transition == -8){
					if (LT_SFX_MODE == 0) LT_Play_PC_Speaker_SFX(Speaker_Menu);
					if (LT_SFX_MODE == 1) LT_Play_AdLib_SFX(Adlib_Select_Sound,2,2,2);
					menu_option --; 
					game-=2;
					change = 3;
					transition = 0;
				}
			break;
			case 2:
				if (menu_option < 4) transition++;
				else change = 0;
				if (transition == 8){
					if (LT_SFX_MODE == 0) LT_Play_PC_Speaker_SFX(Speaker_Menu);
					if (LT_SFX_MODE == 1) LT_Play_AdLib_SFX(Adlib_Select_Sound,2,2,2);
					menu_option ++; 
					game+=2;
					change = 3;
					transition = 0;
				}
			break;
			case 3:
				if (key_timmer == 8) {key_timmer = 0; change = 0;}
				key_timmer++;
			break;
		}
		
		if (menu_option < 0) menu_option = 0;
		if (menu_option > 4) menu_option = 4;		
		if (game < 1) game = 1;
		if (game > 9) game = 9;	
		
		if (LT_Keys[LT_ENTER]) {
			Scene = 3; 
			if (LT_SFX_MODE == 0) LT_Play_PC_Speaker_SFX(Speaker_Select);
			if (LT_SFX_MODE == 1) /*adlib*/;
		}
		if (LT_Keys[LT_JUMP]) {Scene = 0;game = 11;}
		if (LT_Keys[LT_ESC]) {Scene = 3;game = 255; running = 0;}

		LT_Play_Music();
		LT_Update(0, 0);
	}
	LT_Text_Speak_End = 0;
}

void Save_Game(){}
void Charas_Set(){}
void Teleport(){}
void Wish(){}

