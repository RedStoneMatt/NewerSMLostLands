#include <game.h>
#include "levelinfo.h"
#include <newer.h>

class PregameLytHandler {
	public:
		m2d::EmbedLayout_c layout;

		nw4r::lyt::Pane *rootPane;

		nw4r::lyt::TextBox
			*T_minus_00, *T_world_00, *T_worldNum_00,
			*T_pictureFont_00, *T_corseNum_00,
			*T_remainder_00, *T_remainder_01, *T_remainder_02, *T_remainder_03,
			*T_remainder_10, *T_remainder_11, *T_remainder_12, *T_remainder_13,
			*T_x_00, *T_x_01, *T_x_02, *T_x_03, *T_x_10, *T_x_11, *T_x_12, *T_x_13,
			*T_x_00_o, *T_x_10_o,
			*T_otasukePlay_00, *T_otasukePlay_01,
			*T_recommend_00, *T_remainder_00_o, *T_remainder_10_o;

		nw4r::lyt::Picture
			*P_Wx_00[9], *P_coin_00, *P_free_00,
			*P_batB_0x[4], *P_bat_00,
			*P_batB_1x[4], *P_bat_01,
			*P_batB_2x[4], *P_bat_02,
			*P_batB_3x[4], *P_bat_03,
			*P_luijiIcon_00_o, *P_luijiIcon_10_o, *P_coinStage_00;

		nw4r::lyt::Pane
			*N_mario_00, *N_luiji_00, *N_kinoB_01, *N_kinoY_00,
			*N_zankiPos_x[4], *N_zanki_00,
			*Null_battPosxP[4], *N_batt_x[4],
			*N_batt, *N_otasukePlay_00;

		u8 layoutLoaded, somethingHasBeenDone, isVisible, hasShownLuigiThing_orSomething;

		u32 currentStateID;

		u32 _2E8;

		u32 countdownToEndabilityCopy, activePlayerCountMultBy4_maybe;
		u32 batteryLevels[4];
		u32 pgCountdown;

		void hijack_loadLevelNumber(); // replaces 80B6BDD0
};

// Notes:
// Deleted; P_coinStage_00, T_recommend_00, T_worldNum_00,
// T_-_00, T_pictureFont_00, T_corseNum_00, T_world_00
// P_Wx_00, P_coin_00, P_free_00

extern char CurrentLevel;
extern char CurrentWorld;
extern "C" int GetGameLanguage(int nyeh); //nyeh is always 4 for some reasons



void LoadPregameStyleNameAndNumber(m2d::EmbedLayout_c *layout) {
	nw4r::lyt::TextBox
		*LevelNumShadow, *LevelNum,
		*LevelNameShadow, *LevelName;

	LevelNumShadow = layout->findTextBoxByName("LevelNumShadow");
	LevelNum = layout->findTextBoxByName("LevelNum");
	LevelNameShadow = layout->findTextBoxByName("LevelNameShadow");
	LevelName = layout->findTextBoxByName("LevelName");

	// work out the thing now
	dLevelInfo_c::entry_s *level = dLevelInfo_c::s_info.searchBySlot(CurrentWorld, CurrentLevel);
	if (level) {
		wchar_t convLevelName[160];
		const char *srcLevelName = dLevelInfo_c::s_info.getNameForLevel(level);
		int i = 0;
		while (i < 159 && srcLevelName[i]) {
			convLevelName[i] = (unsigned char)(srcLevelName[i]);
			i++;
		}
		convLevelName[i] = 0;
		LevelNameShadow->SetString(convLevelName);
		LevelName->SetString(convLevelName);

		wchar_t levelNumber[32];
		if(GetGameLanguage(4) == 0) { // Japanese (by ?)
			wcscpy(levelNumber, L" ");
		}
		if(GetGameLanguage(4) == 1) { // English (by everyone actually)
			wcscpy(levelNumber, L"World ");
		}
		if(GetGameLanguage(4) == 2) { // German (by ?)
			wcscpy(levelNumber, L" ");
		}
		if(GetGameLanguage(4) == 3) { // French (by RedStoneMatt)
			wcscpy(levelNumber, L"Monde ");
		}
		if(GetGameLanguage(4) == 4) { // Spanish (by Sandre)
			wcscpy(levelNumber, L"Mundo ");
		}
		if(GetGameLanguage(4) == 5) { // Italian (by ?)
			wcscpy(levelNumber, L" ");
		}
		if(GetGameLanguage(4) == 6) { // Dutch (by ?)
			wcscpy(levelNumber, L" ");
		}
		getNewerLevelNumberString(level->displayWorld, level->displayLevel, &levelNumber[6]);

		LevelNum->SetString(levelNumber);

		// make the picture shadowy
		int sidx = 0;
		while (levelNumber[sidx]) {
			if (levelNumber[sidx] == 11) {
				levelNumber[sidx+1] = 0x200 | (levelNumber[sidx+1]&0xFF);
				sidx += 2;
			}
			sidx++;
		}
		LevelNumShadow->SetString(levelNumber);

	} else {
		LevelNameShadow->SetString(L"Not found in LevelInfo!");
		LevelName->SetString(L"Not found in LevelInfo!");
	}
}

#include "fileload.h"

// Preparing the files to read

static File PIZZA_ICON_TPL_FILE;		//Mario
static File CHICKEN_ICON_TPL_FILE;		//Luigi
static File BLUEBERRY_ICON_TPL_FILE;	//Blue Toad
static File IDIOT_ICON_TPL_FILE;		//Yellow Toad

int res_ma;
int res_lu;
int res_kbl;
int res_kyl;


void change_pregame_icon(int powerup, nw4r::lyt::Picture* player_icon, nw4r::lyt::Picture* player_shadow, int player) { //the function to change the icons (duh)

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
		res_ma = PIZZA_ICON_TPL_FILE.open(tpl_name_m); //opening the TPL and store it in a res file
		if (res_ma == 0) { //if it doesn't exist, then return to avoid a crash
			return;
		}
		player_icon->material->texMaps[0].ReplaceImage( //replacing the actual image with the new one
        (TPLPalette*) PIZZA_ICON_TPL_FILE.ptr(), 0
		);
		player_shadow->material->texMaps[0].ReplaceImage( //replacing the actual image with the new one
        (TPLPalette*) PIZZA_ICON_TPL_FILE.ptr(), 0
		);
	}	
	if(player == 1) {
		sprintf(tpl_name_l, "/LevelSamples/im_luijiIcon_0%d.tpl", powerup);
		res_lu = CHICKEN_ICON_TPL_FILE.open(tpl_name_l);
		if (res_lu == 0) {
			return;
		}
		player_icon->material->texMaps[0].ReplaceImage(
        (TPLPalette*) CHICKEN_ICON_TPL_FILE.ptr(), 0
		);
		player_shadow->material->texMaps[0].ReplaceImage(
        (TPLPalette*) CHICKEN_ICON_TPL_FILE.ptr(), 0
		);
	}	
	if(player == 2) {
		sprintf(tpl_name_kb, "/LevelSamples/im_kinoBIcon_0%d.tpl", powerup);
		res_kbl = BLUEBERRY_ICON_TPL_FILE.open(tpl_name_kb);
		if (res_kbl == 0) {
			return;
		}
		player_icon->material->texMaps[0].ReplaceImage(
        (TPLPalette*) BLUEBERRY_ICON_TPL_FILE.ptr(), 0
		);
		player_shadow->material->texMaps[0].ReplaceImage(
        (TPLPalette*) BLUEBERRY_ICON_TPL_FILE.ptr(), 0
		);
	}	
	if(player == 3) {
		sprintf(tpl_name_ky, "/LevelSamples/im_kinoYIcon_0%d.tpl", powerup);
		res_kyl = IDIOT_ICON_TPL_FILE.open(tpl_name_ky);
		if (res_kyl == 0) {
			return;
		}
		player_icon->material->texMaps[0].ReplaceImage(
        (TPLPalette*) IDIOT_ICON_TPL_FILE.ptr(), 0
		);
		player_shadow->material->texMaps[0].ReplaceImage(
        (TPLPalette*) IDIOT_ICON_TPL_FILE.ptr(), 0
		);
	}
}

void PregameLytHandler::hijack_loadLevelNumber() {
	LoadPregameStyleNameAndNumber(&layout);

	nw4r::lyt::Picture *LevelSample;
	LevelSample = layout.findPictureByName("LevelSample");

	// this is not the greatest way to read a file but I suppose it works in a pinch
	char tplName[64];
	sprintf(tplName, "/LevelSamples/%02d-%02d.tpl", CurrentWorld+1, CurrentLevel+1);
	static File tpl;
	if (tpl.open(tplName)) {
		LevelSample->material->texMaps[0].ReplaceImage((TPLPalette*)tpl.ptr(), 0);
	}
	if(Player_Active[0] == 1) {
		nw4r::lyt::Picture *marioicon = layout.findPictureByName("P_marioIcon_00");
		nw4r::lyt::Picture *marioshadow = layout.findPictureByName("P_marioIcon_10");
		change_pregame_icon(Player_Powerup[0], marioicon, marioshadow, 0);
	}
	if(Player_Active[1] == 1) {
		nw4r::lyt::Picture *luigiicon = layout.findPictureByName("P_luijiIcon_00");
		nw4r::lyt::Picture *luigishadow = layout.findPictureByName("P_luijiIcon_10");
		change_pregame_icon(Player_Powerup[Player_ID[1]], luigiicon, luigishadow, Player_ID[1]);
	}
	if(Player_Active[2] == 1) {
		nw4r::lyt::Picture *kinobicon = layout.findPictureByName("P_kinoB_00");
		nw4r::lyt::Picture *kinobshadow = layout.findPictureByName("P_kinoB_10");
		change_pregame_icon(Player_Powerup[Player_ID[2]], kinobicon, kinobshadow, Player_ID[2]);
	}
	if(Player_Active[3] == 1) {
		nw4r::lyt::Picture *kinoyicon = layout.findPictureByName("P_kinoY_00");
		nw4r::lyt::Picture *kinoyshadow = layout.findPictureByName("P_kinoY_10");
		change_pregame_icon(Player_Powerup[Player_ID[3]], kinoyicon, kinoyshadow, Player_ID[3]);
	}
}


