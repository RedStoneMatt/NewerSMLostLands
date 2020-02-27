#include <game.h>
#include "levelinfo.h"
#include <newer.h>
#include <timekeeper.h>

//To anyone who'll read this, please read this before continuing:
//A big thanks to Grop, he helped me to do 90% of this code, that guy is literally a god, and he deserves to be thanked.
//So thank you very much Grop, you're an awesome person :)

void change_icon(int powerup, nw4r::lyt::Picture* player_icon, int player);


 
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
		player_icon->material->texMaps[0].ReplaceImage(
        (TPLPalette*) KINOY_ICON_TPL_FILE.ptr(), 0
		);
	}
}