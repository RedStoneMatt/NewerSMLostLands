#include <common.h>
#include <game.h>
#include <newer.h>
#include "sfx.h"
#include "powerlayout.h"
#include "koopatlas/hud.h"

// Replaces: EN_LIFT_ROTATION_HALF (Sprite 107; Profile ID 481 @ 80AF96F8)


dPowerLayout_c *dPowerLayout_c::instance = 0;
dPowerLayout_c *dPowerLayout_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(dPowerLayout_c));
	dPowerLayout_c *c = new(buffer) dPowerLayout_c;

	instance = c;
	return c;
}

#define ANIM_BOX_APPEAR 0
#define ANIM_BOX_DISAPPEAR 1

extern int MessageBoxIsShowing;

/*****************************************************************************/
// Events
int dPowerLayout_c::onCreate() {
	if (!layoutLoaded) {
		if (!layout.loadArc("firegame.arc", false))
			return false;

		static const char *brlanNames[1] = {
			"gameScene_37_inMarioCoin.brlan",
		};

		static const char *groupNames[2] = {
			"P_marioIcon_00", "P_marioIcon_01",
		};

		layout.build("gameScene_37.brlyt");

		if (IsWideScreen()) {
			layout.layout.rootPane->scale.x = 1.0f;
			layout.layout.rootPane->scale.y = 1.15789f;
		}

		layout.loadAnimations(brlanNames, 2);
		layout.loadGroups(groupNames, (int[2]){0,1}, 2);
		layout.disableAllAnimations();

		layout.drawOrder = 1;

		layoutLoaded = true;
	}
	layout.findPictureByName("P_luijiIcon_00")->SetVisible(0);
	layout.findPictureByName("P_kinoB_00")->SetVisible(0);
	layout.findPictureByName("P_kinoY_00")->SetVisible(0);

	visible = true;
	//layout.enableNonLoopAnim(ANIM_BOX_APPEAR);
	return true;
}
extern "C" int CheckExistingPowerup(void * Player);
int dPowerLayout_c::onExecute() {
	state.execute();

	layout.execAnimations();
	layout.update();
	dAcPy_c *player1;
	dAcPy_c *player2;
	dAcPy_c *player3;
	dAcPy_c *player4;
	player1 = dAcPy_c::findByID(0);
	player2 = dAcPy_c::findByID(0);
	player3 = dAcPy_c::findByID(0);
	player4 = dAcPy_c::findByID(0);
	int p1 = CheckExistingPowerup(player1);
	int p2 = CheckExistingPowerup(player2);
	int p3 = CheckExistingPowerup(player3);
	int p4 = CheckExistingPowerup(player4);
	// Powerups - 0 = small; 1 = big; 2 = fire; 3 = mini; 4 = prop; 5 = peng; 6 = ice; 7 = hammer
	if(p1 == 0) {
		layout.findPictureByName("P_marioIcon_00")->SetVisible(1); //classic
		layout.findPictureByName("P_marioIcon_01")->SetVisible(0); //fire
		layout.findPictureByName("P_marioIcon_02")->SetVisible(0); //ice
		layout.findPictureByName("P_marioIcon_03")->SetVisible(0); //prop
		layout.findPictureByName("P_marioIcon_04")->SetVisible(0); //peng
		layout.findPictureByName("P_marioIcon_05")->SetVisible(0); //hammer
	}
	if(p1 == 1) {
		layout.findPictureByName("P_marioIcon_00")->SetVisible(1); //classic
		layout.findPictureByName("P_marioIcon_01")->SetVisible(0); //fire
		layout.findPictureByName("P_marioIcon_02")->SetVisible(0); //ice
		layout.findPictureByName("P_marioIcon_03")->SetVisible(0); //prop
		layout.findPictureByName("P_marioIcon_04")->SetVisible(0); //peng
		layout.findPictureByName("P_marioIcon_05")->SetVisible(0); //hammer
	}
	if(p1 == 2) {
		layout.findPictureByName("P_marioIcon_00")->SetVisible(0); //classic
		layout.findPictureByName("P_marioIcon_01")->SetVisible(1); //fire
		layout.findPictureByName("P_marioIcon_02")->SetVisible(0); //ice
		layout.findPictureByName("P_marioIcon_03")->SetVisible(0); //prop
		layout.findPictureByName("P_marioIcon_04")->SetVisible(0); //peng
		layout.findPictureByName("P_marioIcon_05")->SetVisible(0); //hammer
	}
	if(p1 == 3) {
		layout.findPictureByName("P_marioIcon_00")->SetVisible(1); //classic
		layout.findPictureByName("P_marioIcon_01")->SetVisible(0); //fire
		layout.findPictureByName("P_marioIcon_02")->SetVisible(0); //ice
		layout.findPictureByName("P_marioIcon_03")->SetVisible(0); //prop
		layout.findPictureByName("P_marioIcon_04")->SetVisible(0); //peng
		layout.findPictureByName("P_marioIcon_05")->SetVisible(0); //hammer
	}
	if(p1 == 4) {
		layout.findPictureByName("P_marioIcon_00")->SetVisible(0); //classic
		layout.findPictureByName("P_marioIcon_01")->SetVisible(0); //fire
		layout.findPictureByName("P_marioIcon_02")->SetVisible(0); //ice
		layout.findPictureByName("P_marioIcon_03")->SetVisible(1); //prop
		layout.findPictureByName("P_marioIcon_04")->SetVisible(0); //peng
		layout.findPictureByName("P_marioIcon_05")->SetVisible(0); //hammer
	}
	if(p1 == 5) {
		layout.findPictureByName("P_marioIcon_00")->SetVisible(0); //classic
		layout.findPictureByName("P_marioIcon_01")->SetVisible(0); //fire
		layout.findPictureByName("P_marioIcon_02")->SetVisible(0); //ice
		layout.findPictureByName("P_marioIcon_03")->SetVisible(0); //prop
		layout.findPictureByName("P_marioIcon_04")->SetVisible(1); //peng
		layout.findPictureByName("P_marioIcon_05")->SetVisible(0); //hammer
	}
	if(p1 == 6) {
		layout.findPictureByName("P_marioIcon_00")->SetVisible(0); //classic
		layout.findPictureByName("P_marioIcon_01")->SetVisible(0); //fire
		layout.findPictureByName("P_marioIcon_02")->SetVisible(1); //ice
		layout.findPictureByName("P_marioIcon_03")->SetVisible(0); //prop
		layout.findPictureByName("P_marioIcon_04")->SetVisible(0); //peng
		layout.findPictureByName("P_marioIcon_05")->SetVisible(0); //hammer
	}
	if(p1 == 7) {
		layout.findPictureByName("P_marioIcon_00")->SetVisible(0); //classic
		layout.findPictureByName("P_marioIcon_01")->SetVisible(0); //fire
		layout.findPictureByName("P_marioIcon_02")->SetVisible(0); //ice
		layout.findPictureByName("P_marioIcon_03")->SetVisible(0); //prop
		layout.findPictureByName("P_marioIcon_04")->SetVisible(0); //peng
		layout.findPictureByName("P_marioIcon_05")->SetVisible(1); //hammer
	}
	int pl1 = SearchForIndexOfPlayerID(0);
	int pl2 = SearchForIndexOfPlayerID(1);
	int pl3 = SearchForIndexOfPlayerID(2);
	int pl4 = SearchForIndexOfPlayerID(3);
	OSReport("player 1 -> %d\nplayer 2 -> %d\nplayer 3 -> %d\nplayer 4 -> %d\n", pl1, pl2, pl3, pl4);

	return true;
}

int dPowerLayout_c::onDraw() {
	if (visible) {
		layout.scheduleForDrawing();
	}
	
	return true;
}

int dPowerLayout_c::onDelete() {
	instance = 0;

	MessageBoxIsShowing = false;
	if (canCancel && StageC4::instance)
		StageC4::instance->_1D = 0; // disable no-pause
	msgDataLoader.unload();

	return layout.free();
}

/*****************************************************************************/
// Load Resources
CREATE_STATE_E(dPowerLayout_c, LoadRes);

void dPowerLayout_c::executeState_LoadRes() {
	if (msgDataLoader.load("/LostlASM/Messages.bin")) {
		state.setState(&StateID_Wait);
	} else {
	}
}

/*****************************************************************************/
// Waiting
CREATE_STATE_E(dPowerLayout_c, Wait);

void dPowerLayout_c::executeState_Wait() {
	// null
}

/*****************************************************************************/
// Show Box
void dPowerLayout_c::showMessage(int id, bool canCancel, int delay) {
	if (!this) {
		OSReport("ADD A MESSAGE BOX MANAGER YOU MORON\n");
		return;
	}

	// get the data file
	header_s *data = (header_s*)msgDataLoader.buffer;

	const wchar_t *title = 0, *msg = 0;

	for (int i = 0; i < data->count; i++) {
		if (data->entry[i].id == id) {
			title = (const wchar_t*)((u32)data + data->entry[i].titleOffset);
			msg = (const wchar_t*)((u32)data + data->entry[i].msgOffset);
			break;
		}
	}

	if (title == 0) {
		OSReport("Message Box: Message %08x not found\n", id);
		return;
	}

	// layout.findTextBoxByName("T_title")->SetString(title);
	// layout.findTextBoxByName("T_msg")->SetString(msg);

	this->canCancel = canCancel;
	this->delay = delay;
	// layout.findPictureByName("button")->SetVisible(canCancel);

	state.setState(&StateID_BoxAppearWait);
}


CREATE_STATE(dPowerLayout_c, BoxAppearWait);

void dPowerLayout_c::beginState_BoxAppearWait() {
	visible = true;
	MessageBoxIsShowing = true;
	StageC4::instance->_1D = 1; // enable no-pause
	layout.enableNonLoopAnim(ANIM_BOX_APPEAR);

	nw4r::snd::SoundHandle handle;
	PlaySoundWithFunctionB4(SoundRelatedClass, &handle, SE_SYS_KO_DIALOGUE_IN, 1);
}

void dPowerLayout_c::executeState_BoxAppearWait() {
	if (!layout.isAnimOn(ANIM_BOX_APPEAR)) {
		state.setState(&StateID_ShownWait);
	}
}

void dPowerLayout_c::endState_BoxAppearWait() { }

/*****************************************************************************/
// Wait For Player To Finish
CREATE_STATE(dPowerLayout_c, ShownWait);

void dPowerLayout_c::beginState_ShownWait() { }
void dPowerLayout_c::executeState_ShownWait() {
	if (canCancel) {
		int nowPressed = Remocon_GetPressed(GetActiveRemocon());

		if (nowPressed & WPAD_TWO)
			state.setState(&StateID_BoxDisappearWait);
	}

	if (delay > 0) {
		delay--;
		if (delay == 0)
			state.setState(&StateID_BoxDisappearWait);
	}
}
void dPowerLayout_c::endState_ShownWait() { }

/*****************************************************************************/
// Hide Box
CREATE_STATE(dPowerLayout_c, BoxDisappearWait);

void dPowerLayout_c::beginState_BoxDisappearWait() {
	layout.enableNonLoopAnim(ANIM_BOX_DISAPPEAR);

	nw4r::snd::SoundHandle handle;
	PlaySoundWithFunctionB4(SoundRelatedClass, &handle, SE_SYS_DIALOGUE_OUT_AUTO, 1);
}

void dPowerLayout_c::executeState_BoxDisappearWait() {
	if (!layout.isAnimOn(ANIM_BOX_DISAPPEAR)) {
		state.setState(&StateID_Wait);

		for (int i = 0; i < 2; i++)
			layout.resetAnim(i);
		layout.disableAllAnimations();
	}
}

void dPowerLayout_c::endState_BoxDisappearWait() {
	visible = false;
	MessageBoxIsShowing = false;
	if (canCancel && StageC4::instance)
		StageC4::instance->_1D = 0; // disable no-pause
}



/*****************************************************************************/
/*****************************************************************************/
/*****************************************************************************/
// Replaces: EN_BLUR (Sprite 152; Profile ID 603 @ 80ADD890)


class dPowerUnused_c : public daEnBlockMain_c {
public:
	TileRenderer tile;
	Physics::Info physicsInfo;

	int onCreate();
	int onDelete();
	int onExecute();

	void calledWhenUpMoveExecutes();
	void calledWhenDownMoveExecutes();

	void blockWasHit(bool isDown);

	USING_STATES(dPowerUnused_c);
	DECLARE_STATE(Wait);

	static dPowerUnused_c *build();
};


CREATE_STATE(dPowerUnused_c, Wait);


int dPowerUnused_c::onCreate() {
	blockInit(pos.y);

	physicsInfo.x1 = -8;
	physicsInfo.y1 = 16;
	physicsInfo.x2 = 8;
	physicsInfo.y2 = 0;

	physicsInfo.otherCallback1 = &daEnBlockMain_c::OPhysicsCallback1;
	physicsInfo.otherCallback2 = &daEnBlockMain_c::OPhysicsCallback2;
	physicsInfo.otherCallback3 = &daEnBlockMain_c::OPhysicsCallback3;

	physics.setup(this, &physicsInfo, 3, currentLayerID);
	physics.flagsMaybe = 0x260;
	physics.callback1 = &daEnBlockMain_c::PhysicsCallback1;
	physics.callback2 = &daEnBlockMain_c::PhysicsCallback2;
	physics.callback3 = &daEnBlockMain_c::PhysicsCallback3;
	physics.addToList();

	TileRenderer::List *list = dBgGm_c::instance->getTileRendererList(0);
	list->add(&tile);

	tile.x = pos.x - 8;
	tile.y = -(16 + pos.y);
	tile.tileNumber = 0x98;

	doStateChange(&dPowerUnused_c::StateID_Wait);

	return true;
}


int dPowerUnused_c::onDelete() {
	TileRenderer::List *list = dBgGm_c::instance->getTileRendererList(0);
	list->remove(&tile);

	physics.removeFromList();

	return true;
}


int dPowerUnused_c::onExecute() {
	acState.execute();
	physics.update();
	blockUpdate();

	tile.setPosition(pos.x-8, -(16+pos.y), pos.z);
	tile.setVars(scale.x);

	// now check zone bounds based on state
	if (acState.getCurrentState()->isEqual(&StateID_Wait)) {
		checkZoneBoundaries(0);
	}

	return true;
}


dPowerUnused_c *dPowerUnused_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(dPowerUnused_c));
	return new(buffer) dPowerUnused_c;
}


void dPowerUnused_c::blockWasHit(bool isDown) {
	pos.y = initialY;

	if (dPowerLayout_c::instance)
		dPowerLayout_c::instance->showMessage(settings);
	else
		Delete(false);

	physics.setup(this, &physicsInfo, 3, currentLayerID);
	physics.addToList();
	
	doStateChange(&StateID_Wait);
}



void dPowerUnused_c::calledWhenUpMoveExecutes() {
	if (initialY >= pos.y)
		blockWasHit(false);
}

void dPowerUnused_c::calledWhenDownMoveExecutes() {
	if (initialY <= pos.y)
		blockWasHit(true);
}



void dPowerUnused_c::beginState_Wait() {
}

void dPowerUnused_c::endState_Wait() {
}

void dPowerUnused_c::executeState_Wait() {
	int result = blockResult();

	if (result == 0)
		return;

	if (result == 1) {
		doStateChange(&daEnBlockMain_c::StateID_UpMove);
		anotherFlag = 2;
		isGroundPound = false;
	} else {
		doStateChange(&daEnBlockMain_c::StateID_DownMove);
		anotherFlag = 1;
		isGroundPound = true;
	}
}


