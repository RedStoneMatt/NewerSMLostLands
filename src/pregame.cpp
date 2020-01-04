#include <game.h>
#include "levelinfo.h"
#include <newer.h>

extern int powerupthing;

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
			*P_luijiIcon_00_o, *P_luijiIcon_10_o, *P_coinStage_00,
			*P_Header_00, *P_Upper_00;

		nw4r::lyt::Pane
			*N_mario_00, *N_luiji_00, *N_kinoB_01, *N_kinoY_00,
			*N_zankiPos_x[4], *N_zanki_00,
			*Null_battPosxP[4], *N_batt_x[4],
			*N_batt, *N_otasukePlay_00,
			*N_Header_00;

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
extern "C" int CheckExistingPowerup(void * Player);

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
			convLevelName[i] = srcLevelName[i];
			i++;
		}
		convLevelName[i] = 0;
		LevelNameShadow->SetString(convLevelName);
		LevelName->SetString(convLevelName);

		wchar_t levelNumber[32];
		wcscpy(levelNumber, L"World ");
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

void levelsamplething(m2d::EmbedLayout_c *layout) {
}

void powerlayoutthing(m2d::EmbedLayout_c *layout) {
}

#include "fileload.h"
void PregameLytHandler::hijack_loadLevelNumber() {
	LoadPregameStyleNameAndNumber(&layout);
	static File tpl;
	// static File tpll;
	
	
	nw4r::lyt::Picture *LevelSample;
	LevelSample = layout.findPictureByName("LevelSample");
	// nw4r::lyt::Picture *P_marioIcon_00;
	// P_marioIcon_00 = layout.findPictureByName("P_marioIcon_00");
	
	
	// this is not the greatest way to read a file but I suppose it works in a pinch
	char tplName[64];
	sprintf(tplName, "/LevelSamples/%02d-%02d.tpl", CurrentWorld+1, CurrentLevel+1);
	if (tpl.open(tplName)) {
		LevelSample->material->texMaps[0].ReplaceImage((TPLPalette*)tpl.ptr(), 0);
	}	
	
	// dAcPy_c *player1;
	// dAcPy_c *player2;
	// dAcPy_c *player3;
	// dAcPy_c *player4;
	// player1 = dAcPy_c::findByID(0);
	// player2 = dAcPy_c::findByID(1);
	// player3 = dAcPy_c::findByID(2);
	// player4 = dAcPy_c::findByID(3);
	// int p1 = CheckExistingPowerup(player1); // Powerups - 0 = small; 1 = big; 2 = fire; 3 = mini; 4 = prop; 5 = peng; 6 = ice; 7 = hammer
	// int p2 = CheckExistingPowerup(player2);
	// int p3 = CheckExistingPowerup(player3);
	// int p4 = CheckExistingPowerup(player4);
	// p1 = powerupthing;
	
	// OSReport("CurrentWorld = %d and CurrentLevel = %d\n", CurrentWorld+1, CurrentLevel+1);
	// OSReport("p1 = %d, p2 = %d, p3 = %d, p4 = %d\n", p1, p2, p3, p4);
	
	// char tpllName[64];
	// sprintf(tpllName, "/LevelSamples/im_marioIcon_0%d.tpl\n", p1);
	// OSReport("tpllName = %s", tpllName);
	// if (tpll.open(tpllName)) {
		// LevelSample->material->texMaps[0].ReplaceImage((TPLPalette*)tpll.ptr(), 0);
	// }
}




