#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <stage.h>


const char* VParcNameList [] = {
	"pakkun",
	NULL	
};

class daPoisonBall : public dEn_c {
	int onCreate();
	int onDelete();
	int onExecute();
	int onDraw();

	mHeapAllocator_c allocator;
	nw4r::g3d::ResFile resFile;
	m3d::mdl_c bodyModel;
	m3d::anmChr_c animationChr;

	

	float Baseline;

	static daPoisonBall *build();

	void bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate);
	void setupBodyModel();
	void updateModelMatrices();

	void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	void yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther);

	USING_STATES(daPoisonBall);
	DECLARE_STATE(Main);
};

daPoisonBall *daPoisonBall::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daPoisonBall));
	return new(buffer) daPoisonBall;
}



CREATE_STATE(daPoisonBall, Main);

extern "C" void dAcPy_vf3F4(void* mario, void* other, int t);
extern "C" bool BigHanaFireball(dEn_c* t, ActivePhysics *apThis, ActivePhysics *apOther);
extern "C" void *dAcPy_c__ChangePowerupWithAnimation(void * Player, int powerup);
extern "C" int CheckExistingPowerup(void * Player);
extern "C" void *EN_LandbarrelPlayerCollision(dEn_c* t, ActivePhysics *apThis, ActivePhysics *apOther);
extern "C" char usedForDeterminingStatePress_or_playerCollision(dEn_c* t, ActivePhysics *apThis, ActivePhysics *apOther, int unk1);

void daPoisonBall::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) { 
	if(this->settings == 0) { // Types - 0 = Poison; 1 = Plant; 2 = Cannonball
		int p = CheckExistingPowerup(apOther->owner);
		if (p != 0 && p != 3) {	// Powerups - 0 = small; 1 = big; 2 = fire; 3 = mini; 4 = prop; 5 = peng; 6 = ice; 7 = hammer
			dAcPy_c__ChangePowerupWithAnimation(apOther->owner, 0);
		}
		else { this->_vf220(apOther->owner); }
		this->counter_504[apOther->owner->which_player] = 0x20;
	}
	if(this->settings == 1) {
		//EN_LandbarrelPlayerCollision(this, apThis, apOther);
		this->_vf220(apOther->owner);
	}
	if(this->settings == 2) {
		char hitType;
		hitType = usedForDeterminingStatePress_or_playerCollision(this, apThis, apOther, 0);
		if(hitType > 0) {
			VEC2 shit;
			shit.x = this->speed.x;
			shit.y = this->speed.y;
			dEn_c::killWithSpecifiedState(apOther->owner, &shit, &dEn_c::StateID_DieFumi, 0);
		}
		else {
			this->_vf220(apOther->owner);
		}
	}
}
void daPoisonBall::yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther) { this->_vf220(apOther->owner); }
bool daPoisonBall::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daPoisonBall::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	this->_vf220(apOther->owner);
	return true;
}
bool daPoisonBall::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	this->_vf220(apOther->owner);
	return true;
}
bool daPoisonBall::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daPoisonBall::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	this->Delete(1);
	return true;
}

bool daPoisonBall::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {
	return false;
}
bool daPoisonBall::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daPoisonBall::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	this->_vf220(apOther->owner);
	return true;
}




void daPoisonBall::bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate) {
	nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr(name);
	this->animationChr.bind(&this->bodyModel, anmChr, unk);
	this->bodyModel.bindAnim(&this->animationChr, unk2);
	this->animationChr.setUpdateRate(rate);
}


void daPoisonBall::setupBodyModel() {
		allocator.link(-1, GameHeaps[0], 0, 0x20);

		this->resFile.data = getResource("pakkun", "g3d/customball.brres");
		if(this->settings == 0) {
			nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("poison_ball");
			bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
			SetupTextures_Enemy(&bodyModel, 0);

			bool ret;
			nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr("customball");
			ret = this->animationChr.setup(mdl, anmChr, &this->allocator, 0);
		}
		if(this->settings == 1) {
			nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("plant_ball");
			bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
			SetupTextures_Enemy(&bodyModel, 0);

			bool ret;
			nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr("customball");
			ret = this->animationChr.setup(mdl, anmChr, &this->allocator, 0);
		}
		if(this->settings == 2) {
			nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("cannon_ball");
			bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
			SetupTextures_Enemy(&bodyModel, 0);

			bool ret;
			nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr("customball");
			ret = this->animationChr.setup(mdl, anmChr, &this->allocator, 0);
		}

		allocator.unlink();
}


int daPoisonBall::onCreate() {

	setupBodyModel();


	this->scale = (Vec){1.0, 1.0, 1.0};
	this->rot.x = 0; // X is vertical axis
	this->rot.y = 0xD800; // Y is horizontal axis
	this->rot.z = 0; // Z is ... an axis >.>
	this->direction = 1; // Heading left.

	this->speed.x = 0.0;
	this->speed.y = 0.0;
	this->Baseline = this->pos.y;

	ActivePhysics::Info HitMeBaby;
	
	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 0.0;

	HitMeBaby.xDistToEdge = 4.0;
	HitMeBaby.yDistToEdge = 4.0;

	HitMeBaby.category1 = 0x3;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0x8028E;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();


	bindAnimChr_and_setUpdateRate("customball", 1, 0.0, 1.0);

	doStateChange(&StateID_Main);

	this->onExecute();
	return true;
}

int daPoisonBall::onDelete() {
	return true;
}

int daPoisonBall::onExecute() {
	acState.execute();
	updateModelMatrices();

	HandleXSpeed();
	HandleYSpeed();
	doSpriteMovement();

	if(this->animationChr.isAnimationDone()) {
		this->animationChr.setCurrentFrame(0.0);
	}

	return true;
}


int daPoisonBall::onDraw() {
	bodyModel.scheduleForDrawing();
	bodyModel._vf1C();
	return true;
}


void daPoisonBall::updateModelMatrices() {
	// This won't work with wrap because I'm lazy.
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}


// Main State

void daPoisonBall::beginState_Main() {
	
}

void daPoisonBall::executeState_Main() {
	//this->pos.x += this->speed.x;
	//this->pos.y += this->speed.y;
	if(this->animationChr.isAnimationDone()) {
		this->animationChr.setCurrentFrame(0.0);
	}
}
void daPoisonBall::endState_Main() {

}