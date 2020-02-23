#include <common.h>
#include <game.h>
#include <actors.h>
#include "sfx.h"

class daEnTripleBlock_c : public daEnBlockMain_c {
public:
	TileRenderer tileRight;
	TileRenderer tileMiddle;
	TileRenderer tileLeft;
	Physics::Info physicsInfo;

	int onCreate();
	int onDelete();
	int onExecute();

	void calledWhenUpMoveExecutes();
	void calledWhenDownMoveExecutes();

	void blockWasHit(bool isDown);
	
	int wasIHit;
	int doOneTime;

	USING_STATES(daEnTripleBlock_c);
	DECLARE_STATE(Wait);

	static daEnTripleBlock_c *build();
};


CREATE_STATE(daEnTripleBlock_c, Wait);


int daEnTripleBlock_c::onCreate() {
	blockInit(pos.y);

	physicsInfo.x1 = -24;
	physicsInfo.y1 = 16;
	physicsInfo.x2 = 24;
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
	
	//Right
	list->add(&tileRight);

	tileRight.x = pos.x + 8;
	tileRight.y = -(16 + pos.y);
	tileRight.tileNumber = 0x9B;

	//Middle
	list->add(&tileMiddle);

	tileMiddle.x = pos.x - 8;
	tileMiddle.y = -(16 + pos.y);
	tileMiddle.tileNumber = 0x9A;

	//Left
	list->add(&tileLeft);

	tileLeft.x = pos.x - 24;
	tileLeft.y = -(16 + pos.y);
	tileLeft.tileNumber = 0x99;

	this->wasIHit = 0;
	this->pos.z = 200.0f;
	
	doStateChange(&daEnTripleBlock_c::StateID_Wait);

	return true;
}


int daEnTripleBlock_c::onDelete() {
	TileRenderer::List *list = dBgGm_c::instance->getTileRendererList(0);
	list->remove(&tileRight);
	list->remove(&tileMiddle);
	list->remove(&tileLeft);

	physics.removeFromList();

	return true;
}


int daEnTripleBlock_c::onExecute() {
	acState.execute();
	physics.update();
	blockUpdate();

	tileRight.setPosition(pos.x+8, -(16+pos.y), pos.z);
	tileRight.setVars(scale.x);
	
	tileMiddle.setPosition(pos.x-8, -(16+pos.y), pos.z);
	tileMiddle.setVars(scale.x);
	
	tileLeft.setPosition(pos.x-24, -(16+pos.y), pos.z);
	tileLeft.setVars(scale.x);

	// now check zone bounds based on state
	if (acState.getCurrentState()->isEqual(&StateID_Wait)) {
		checkZoneBoundaries(0);
	}

	return true;
}


daEnTripleBlock_c *daEnTripleBlock_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daEnTripleBlock_c));
	return new(buffer) daEnTripleBlock_c;
}


void daEnTripleBlock_c::blockWasHit(bool isDown) {
	pos.y = initialY;
	

	
	Vec coinPosL = (Vec){this->pos.x - 24, this->pos.y + 32, this->pos.z};
	Vec coinPosR = (Vec){this->pos.x + 8, this->pos.y + 32, this->pos.z};
	
	
	u32 enitemsettings;
	u32 reggieToIG[] = {0x0,0x1,0x2,0x7,0x9,0xE,0x11,0x15,0x19,0x6}; //Mushroom, Star, Coin, 1UP, Fire Flower, Ice Flower, Penguin, Propeller, Mini Shroom, Hammer
	u32 powerupToSet = reggieToIG[(this->settings >> 20 & 0xF)]; //Spritedata ID to EN_ITEM ID
	enitemsettings = 0 | (powerupToSet << 0) | (2 << 18) | (4 << 9) | (2 << 10); //Setting non-GP settings
	
	u32 coinsettings;
	coinsettings = 0 | (0x2 << 0) | (2 << 18) | (4 << 9) | (2 << 10);
	
	if(isGroundPound) { //Ignoring propeller because groundpound or not, it has to spawn by the top
		OSReport("isGroundPound\n");
		enitemsettings = 0 | (powerupToSet << 0) | (3 << 18) | (4 << 9) | (2 << 10);
		coinsettings = 0 | (0x2 << 0) | (3 << 18) | (4 << 9) | (2 << 10);
		coinPosL = (Vec){this->pos.x - 24, this->pos.y, this->pos.z};
		coinPosR = (Vec){this->pos.x + 8, this->pos.y, this->pos.z};
	}
	if(powerupToSet != 0x2 && powerupToSet != 0x15) { //Propeller does a different sound, Coin doesn't do any sound
		nw4r::snd::SoundHandle handle;
		PlaySoundWithFunctionB4(SoundRelatedClass, &handle, SE_OBJ_ITEM_APPEAR, 1);
	}
	if(powerupToSet == 0x15) { //Propeller sound
		nw4r::snd::SoundHandle handle;
		PlaySoundWithFunctionB4(SoundRelatedClass, &handle, SE_OBJ_ITEM_PRPL_APPEAR, 1);
	}
	dStageActor_c *PowerUp = dStageActor_c::create(EN_ITEM, enitemsettings, &this->pos, 0, 0);
	dStageActor_c *coinLeft = dStageActor_c::create(EN_COIN, coinsettings, &coinPosL, 0, 0); //Creating coins
	dStageActor_c *coinRight = dStageActor_c::create(EN_COIN, coinsettings, &coinPosR, 0, 0);

	physics.setup(this, &physicsInfo, 3, currentLayerID);
	physics.addToList();
	
	this->wasIHit = 1;
	doStateChange(&StateID_Wait);
}



void daEnTripleBlock_c::calledWhenUpMoveExecutes() {
	if (initialY >= pos.y)
		blockWasHit(false);
}

void daEnTripleBlock_c::calledWhenDownMoveExecutes() {
	if (initialY <= pos.y)
		blockWasHit(true);
}



void daEnTripleBlock_c::beginState_Wait() {
}

void daEnTripleBlock_c::endState_Wait() {
}

void daEnTripleBlock_c::executeState_Wait() {
	if(this->wasIHit == 0) {
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
	if(this->wasIHit == 1 && this->doOneTime == 0) { //Was already hit ? Change the tiles.
		tileRight.tileNumber = 0xA8;
		tileMiddle.tileNumber = 0xA7;
		tileLeft.tileNumber = 0xA6;
		this->doOneTime++;
	}
}