// class dGameDisplay_c {
	// public:
		// m2d::EmbedLayout_c layout;

		// nw4r::lyt::Pane *rootPane;

		// nw4r::lyt::TextBox
			// *T_otaChuS_00, *T_otaChu_01,
			// *T_x_01, *T_x_02, *T_x_03, *T_x_04,
			// *T_left_0x[4], *T_InfoS_00, *T_Info_00, *T_coin_00,
			// *T_score_00, *T_time_00;

		// nw4r::lyt::Picture
			// *P_baseS_0x[2], *P_base_0x[2], *P_otasukeIcon_00,
			// *P_marioIcon_00, *P_luijiIcon_00, *P_kinoB_00, *P_kinoY_00,
			// *P_coin_00, *P_collectOff_0x[3], *P_collection_0x[3],
			// *P_timer_00;

		// nw4r::lyt::Pane
			// *N_proportionL_00, *N_otasukeChu_00, *N_areaZanki_00, *N_left_00,
			// *N_marioIcon_00, *N_luigiIcon_00, *N_kinoB_00, *N_kinoY_00,
			// *N_otasukeInfo_00, *N_text_00,
			// *N_areaCoin_00, *N_coin_0x[2],
			// *N_collection_00, *N_coin1st_00, *N_coin2nd_00, *N_coin3rd_00,
			// *N_proportionR_00, *N_areaScore_00, *N_score_00,
			// *N_time_00;


		// dStateMgr_c state;

		// u32 coins;
		// u32 timer;
		// u32 score;
		// u32 mustAtLeast2ForScoreToCount;
		// u32 coinBox;
		// u32 timerBox;
		// u32 scoreBox;
		// u32 StarCoin1;
		// u32 StarCoin2;
		// u32 StarCoin3;
		
		// int onExecute_orig();

		// int powerlayout(); // replaces 801580D0
// };

// int dGameDisplay_c::powerlayout() {
	// int orig = this->onExecute_orig();
	// static File tpl;
	
	
	// nw4r::lyt::Picture *Mario;
	// Mario = layout.findPictureByName("P_marioIcon_00");
	// if (Mario == 0) {
		// return orig;
	// }
	
	// this is not the greatest way to read a file but I suppose it works in a pinch   <--- old treeki comment from pregame.cpp
	// char tplName[64];
	// sprintf(tplName, "/LevelSamples/im_marioIcon_02.tpl");
	// if (tpl.open(tplName)) {
		// Mario->material->texMaps[0].ReplaceImage((TPLPalette*)tpl.ptr(), 0);
	// }	
	// return orig;
// }

// int dGameDisplay_c::powerlayout() {
    // static File TPL_FILE;

    // int orig_val = this->onExecute_orig();

    // this is not the greatest way to read a file but I suppose it works in a pinch
    // char tpl_name[64];
    // sprintf(tpl_name, "/LevelSamples/im_marioIcon_02.tpl");
    // int res = TPL_FILE.open(tpl_name);
    // OSReport("TPL_FILE.open('%s'): %d\n", tpl_name, res);
    // if (res != 0) {
        // this->P_marioIcon_00->material->texMaps[0].ReplaceImage((TPLPalette*)TPL_FILE.ptr(), 0);
    // }

    // return orig_val;
// }
// extern "C" int CheckExistingPowerup(void * Player);

#include <game.h>
#include "levelinfo.h"
#include <newer.h>

class dGameDisplay_c : dBase_c {
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
		u32 _494;
		u32 _498;
		u32 _49C;
		u32 _4A0;
		u32 _4A4;
		u32 _4A8;
		u32 _4AC;
		u32 _4B0;
		u32 _4B4;
		u32 _4B8;
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

int levelBeginPowerupID;

u32 dAcPy_c::patch_thing(u32 powerup_id) {
	// OSReport("1\n");
    static File TPL_FILE;
	// OSReport("2\n");
    u32 orig_val = this->setPowerup_orig(powerup_id);
	// OSReport("3\n");

	if(dGameDisplay_c::instance == NULL) {
		return orig_val;
	}

    // TODO: we can get this pointer from dGameDisplay_c::instance directly
    nw4r::lyt::Picture* mario_pic = dGameDisplay_c::instance->layout.findPictureByName("P_marioIcon_00");
	// OSReport("4\n");

    OSReport("mario_pic: %p\n", mario_pic);
	if (dGameDisplay_c::instance == NULL) {
        // Save the powerup id to be used when creating the game display
        levelBeginPowerupID = powerup_id;
        return orig_val;
    }

    // this is not the greatest way to read a file but I suppose it works in a pinch
    char tpl_name[64];
    OSReport("powerup = %d\n", powerup_id);
    if (powerup_id == 0 || powerup_id == 3) {
        powerup_id = 1;
    } else if (powerup_id == 6) {
        powerup_id = 3;
    } else if (powerup_id == 7) {
        powerup_id = 6;
    }

    sprintf(tpl_name, "/LevelSamples/im_marioIcon_0%d.tpl", powerup_id);

    int res = TPL_FILE.open(tpl_name);
    OSReport("TPL_FILE.open('%s'): %d\n", tpl_name, res);
    if (res != 0) {
        mario_pic->material->texMaps[0].ReplaceImage((TPLPalette*)TPL_FILE.ptr(), 0);
    }

    return orig_val;
}

int dGameDisplay_c::patch_fix() {
	OSReport("1\n");
    static File TPL_FILE;
	OSReport("2\n");
    int orig_val = this->onCreate_orig();
	OSReport("3\n");
    
    // TODO: we can get this pointer from dGameDisplay_c::instance directly
    nw4r::lyt::Picture* mario_pic = this->layout.findPictureByName("P_marioIcon_00");
	OSReport("4\n");

    if (mario_pic == NULL) {
        return orig_val;
    }

    // this is not the greatest way to read a file but I suppose it works in a pinch
    char tpl_name[64];
    OSReport("powerup = %d\n", levelBeginPowerupID);
    if (levelBeginPowerupID == 0 || levelBeginPowerupID == 3) {
        levelBeginPowerupID = 1;
    } else if (levelBeginPowerupID == 6) {
        levelBeginPowerupID = 3;
    } else if (levelBeginPowerupID == 7) {
        levelBeginPowerupID = 6;
    }

    sprintf(tpl_name, "/LevelSamples/im_marioIcon_0%d.tpl", levelBeginPowerupID);

    int res = TPL_FILE.open(tpl_name);
    OSReport("TPL_FILE.open('%s'): %d\n", tpl_name, res);
    if (res != 0) {
        mario_pic->material->texMaps[0].ReplaceImage((TPLPalette*)TPL_FILE.ptr(), 0);
    }

    return orig_val;
}


