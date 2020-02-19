#include <game.h>
#include "levelinfo.h"
#include <newer.h>

//To anyone who'll read this, please read this before continuing:
//A big thanks to Grop, he helped me to do 90% of this code, that guy is literally a god, and he deserves to be thanked.
//So thank you very much Grop, you're an awesome person :)

void change_icon(int powerup, nw4r::lyt::Picture* player_icon, int player);

class dGameDisplay_c : dBase_c { //The dGameDisplay_c class, very important.
    public:
        m2d::EmbedLayout_c layout;
        mEf::es2 effect;
        u32 _330;
        u32 _334;
        u32 _338;
        u32 _33C;
        u32 _340;
        u32 _344;
        u32 _348;
        u32 _34C;
        u32 _350;
        u32 _354;
        u32 _358;
        u32 _35C;
        u32 _360;
        u32 _364;
        u32 _368;
        u32 _36C;
        u32 _370;
        u32 _374;
        u32 _378;
        u32 _37C;
        u32 _380;
        u32 _384;
        u32 _388;
        u32 _38C;
        u32 _390;
        u32 _394;
        u32 _398;
        u32 _39C;
        u32 _3A0;
        u32 _3A4;
        dStateMgr_c state;
        u32 _3CC;
        u32 _3D0;
        u32 _3D4;
        u32 _3D8;
        u32 coins;
        u32 timer;
        u32 _3E4;
        u32 score;
        u32 _3EC;
        u32 _3F0;
        u32 _3F4;
        u32 _3F8;
        u32 _3FC;
        u32 _400;
        u32 _404;
        u32 _408;
        u32 _40C;
        u32 _410;
        u32 _414;
        u32 _418;
        u32 _41C;
        u32 _420;
        u32 _424;
        u32 _428;
        u32 _42C;
        u32 _430;
        u32 mustAtLeast2ForScoreToCount;
        u32 _438;
        u32 _43C;
        u32 _440;
        u32 _444;
        u8 _448;
        u8 _449;
        u8 _44A;
        u8 _44B;
        u32 _44C;
        u8 _450;
        u8 _451;
        u8 _452;
        u8 _453;
        u8 _454;
        u8 _455;
        u8 _456;
        u8 _457;
        u32 _458;
        u32 _45C;
        u32 _460;
        u32 _464;
        u32 _468;
        u32 _46C;
        u32 _470;
        u32 _474;
        u32 _478;
        u32 _47C;
        u32 _480;
        u32 _484;
        u32 _488;
        u32 _48C;
        u32 _490;
        nw4r::lyt::Picture* p_collectOff_00;
        nw4r::lyt::Picture* p_collection_00;
        nw4r::lyt::Picture* p_collectOff_01;
        nw4r::lyt::Picture* p_collection_01;
        nw4r::lyt::Picture* p_collectOff_02;
        nw4r::lyt::Picture* p_collection_02;
        nw4r::lyt::Picture* p_marioIcon_00;
        nw4r::lyt::Picture* p_luijiIcon_00;
        nw4r::lyt::Picture* p_kinoB_00;
        nw4r::lyt::Picture* p_kinoY_00;
        u32 _4BC;
        u32 _4C0;
        u32 _4C4;
        u32 _4C8;
        u32 _4CC;
        u32 _4D0;
        u32 _4D4;
        u32 _4D8;
        nw4r::lyt::TextBox* coinBox;
        nw4r::lyt::TextBox* timerBox;
        nw4r::lyt::TextBox* scoreBox;
        u32 _4E8;
        u32 _4EC;
        u32 _4F0;
        u32 _4F4;
        u8  _4F8;
        void* StarCoin1;
        void* StarCoin2;
        void* StarCoin3;
        u8  _505;
        u8  _506;
        u8  _507;
        u8 blob1[0x51C - 0x508];
        u32 _51C;
        u8 blob2[0x5A0 - 0x508];
        u32 _5A0;
       
        static dGameDisplay_c* instance;
        int onCreate_orig();
        int patch_fix();
};
 
#include "fileload.h"

// Preparing the files to read

static int INITIAL_POWERUP1;
static int INITIAL_POWERUP2;
static int INITIAL_POWERUP3;
static int INITIAL_POWERUP4;

static File MARIO_ICON_TPL_FILE;
static File LUIGI_ICON_TPL_FILE;
static File KINOB_ICON_TPL_FILE;
static File KINOY_ICON_TPL_FILE;

int res_m;
int res_l;
int res_kb;
int res_ky;


u32 dAcPy_c::patch_thing(u32 powerup_id) { //the function that is executed when the powerup changes
    u32 orig_val = this->setPowerup_orig(powerup_id); //to preserve the original dAcPy_c::setPowerup function
	
	int player = Player_ID[this->which_player]; //detect which player is what character
 
    if (dGameDisplay_c::instance == NULL) { //if the gameScene layout hasn't been created yet, memorize the values to use them later
		if(player == 0) {
			INITIAL_POWERUP1 = powerup_id;
		}
		if(player == 1) {
			INITIAL_POWERUP2 = powerup_id;
		}
		if(player == 3) {
			INITIAL_POWERUP3 = powerup_id;
		}
		if(player == 2) {
			INITIAL_POWERUP4 = powerup_id;
		}
        return orig_val;
    }
	
	nw4r::lyt::Picture* player_icon; //much shit to make to game change use the change_icon function to change the correct images
	if(player == 0) {
		player_icon = dGameDisplay_c::instance->p_marioIcon_00;
		INITIAL_POWERUP1 = powerup_id;
		change_icon(INITIAL_POWERUP1, dGameDisplay_c::instance->p_marioIcon_00, 0);
	}	
	if(player == 1) {
		player_icon = dGameDisplay_c::instance->p_luijiIcon_00;
		INITIAL_POWERUP2 = powerup_id;
		change_icon(INITIAL_POWERUP2, dGameDisplay_c::instance->p_luijiIcon_00, 1);
	}	
	if(player == 3) {
		player_icon = dGameDisplay_c::instance->p_kinoB_00;
		INITIAL_POWERUP4 = powerup_id;
		change_icon(INITIAL_POWERUP4, dGameDisplay_c::instance->p_kinoY_00, 2);
	}	
	if(player == 2) {
		player_icon = dGameDisplay_c::instance->p_kinoY_00;
		INITIAL_POWERUP3 = powerup_id;
		change_icon(INITIAL_POWERUP3, dGameDisplay_c::instance->p_kinoB_00, 3);
	}

 
    if (player_icon == NULL) { //if the pane wasn't found, returning the original value to avoid a crash
        return orig_val;
    }
 
    return orig_val; //returning original function
}
 
int dGameDisplay_c::patch_fix() { //the function that is executed when the gameScene layout is created
    int orig_val = this->onCreate_orig(); //to preserve the original dGameDisplay_c::onCreate function


    OSReport("player_icon: %p\n", this->p_marioIcon_00); //debugging

    if (this->p_marioIcon_00 == NULL) { //if the pane wasn't found, returning the original value to avoid a crash
        return orig_val;
    }

    change_icon(INITIAL_POWERUP1, this->p_marioIcon_00, 0); //setting up the correct icons for the different players using the change_icon function
    change_icon(INITIAL_POWERUP2, this->p_luijiIcon_00, 1);
    change_icon(INITIAL_POWERUP4, this->p_kinoB_00, 3);
    change_icon(INITIAL_POWERUP3, this->p_kinoY_00, 2);

    return orig_val;
}

void change_icon(int powerup, nw4r::lyt::Picture* player_icon, int player) { //the function to change the icons (duh)


    OSReport("powerup = %d\n", powerup); //debugging

    char tpl_name_m[64]; //creating the tpl names chars
    char tpl_name_l[64];
    char tpl_name_kb[64];
    char tpl_name_ky[64];
    if (powerup == 0 || powerup == 3) { //converting the IG-Powerup IDs to the TPL-Powerup IDs
        powerup = 1;
    } else if (powerup == 6) {
        powerup = 3;
    } else if (powerup == 7) {
        powerup = 6;
    }
	
	

	if(player == 0) { //much shit to replace the correct images with the correct ones
		sprintf(tpl_name_m, "/LevelSamples/im_marioIcon_0%d.tpl", powerup); //creating TPL name for mario
		res_m = MARIO_ICON_TPL_FILE.open(tpl_name_m); //opening the TPL and store it in a res file
		if (res_m == 0) { //if it doesn't exist, then return to avoid a crash
			return;
		}
		OSReport("MARIO_ICON_TPL_FILE.open('%s'): %d\n", tpl_name_m, res_m); //debugging
		player_icon->material->texMaps[0].ReplaceImage( //replacing the actual image with the new one
        (TPLPalette*) MARIO_ICON_TPL_FILE.ptr(), 0
		);
	}	
	if(player == 1) {
		sprintf(tpl_name_l, "/LevelSamples/im_luijiIcon_0%d.tpl", powerup);
		res_l = LUIGI_ICON_TPL_FILE.open(tpl_name_l);
		if (res_l == 0) {
			return;
		}
		OSReport("LUIGI_ICON_TPL_FILE.open('%s'): %d\n", tpl_name_l, res_l);
		player_icon->material->texMaps[0].ReplaceImage(
        (TPLPalette*) LUIGI_ICON_TPL_FILE.ptr(), 0
		);
	}	
	if(player == 3) {
		sprintf(tpl_name_kb, "/LevelSamples/im_kinoBIcon_0%d.tpl", powerup);
		res_kb = KINOB_ICON_TPL_FILE.open(tpl_name_kb);
		if (res_kb == 0) {
			return;
		}
		OSReport("KINOB_ICON_TPL_FILE.open('%s'): %d\n", tpl_name_kb, res_kb);
		player_icon->material->texMaps[0].ReplaceImage(
        (TPLPalette*) KINOB_ICON_TPL_FILE.ptr(), 0
		);
	}	
	if(player == 2) {
		sprintf(tpl_name_ky, "/LevelSamples/im_kinoYIcon_0%d.tpl", powerup);
		res_ky = KINOY_ICON_TPL_FILE.open(tpl_name_ky);
		if (res_ky == 0) {
			return;
		}
		OSReport("KINOY_ICON_TPL_FILE.open('%s'): %d\n", tpl_name_ky, res_ky);
		player_icon->material->texMaps[0].ReplaceImage(
        (TPLPalette*) KINOY_ICON_TPL_FILE.ptr(), 0
		);
	}
}