#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <stage.h>
#include "boss.h"


const char* YParcNameList [] = {
	"pakkun",
	NULL	
};

class daCustomPakkun : public dEn_c {
	int onCreate();
	int onDelete();
	int onExecute();
	int onDraw();

	mHeapAllocator_c allocator;
	nw4r::g3d::ResFile resFile;
	m3d::mdl_c bodyModel;
	m3d::anmChr_c animationChr;
	
	const char *brresName;

	u32 timer;
	u32 filename;
	bool isDieing;
	int delayforshooting;
	
	int spawnersettings;
	int type;

	static daCustomPakkun *build();

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

	USING_STATES(daCustomPakkun);
	DECLARE_STATE(Attack);
	DECLARE_STATE(Outro);
};

daCustomPakkun *daCustomPakkun::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daCustomPakkun));
	return new(buffer) daCustomPakkun;
}



CREATE_STATE(daCustomPakkun, Attack);
CREATE_STATE(daCustomPakkun, Outro);



void daCustomPakkun::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) { 
	this->_vf220(apOther->owner);
}
void daCustomPakkun::yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther) { this->_vf220(apOther->owner); }
bool daCustomPakkun::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
	bindAnimChr_and_setUpdateRate("dead", 1, 0.0, 1.0);
	doStateChange(&StateID_Outro);
	return true;
}
bool daCustomPakkun::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	this->_vf220(apOther->owner);
	return true;
}
bool daCustomPakkun::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	this->_vf220(apOther->owner);
	return true;
}
bool daCustomPakkun::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
	bindAnimChr_and_setUpdateRate("dead", 1, 0.0, 1.0);
	doStateChange(&StateID_Outro);
	return true;
}
bool daCustomPakkun::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	bindAnimChr_and_setUpdateRate("dead", 1, 0.0, 1.0);
	doStateChange(&StateID_Outro);
	return true;
}

bool daCustomPakkun::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {
	return false;
}
bool daCustomPakkun::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	bindAnimChr_and_setUpdateRate("dead", 1, 0.0, 1.0);
	doStateChange(&StateID_Outro);
	return true;
}
bool daCustomPakkun::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	this->_vf220(apOther->owner);
	return true;
}




void daCustomPakkun::bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate) {
	nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr(name);
	this->animationChr.bind(&this->bodyModel, anmChr, unk);
	this->bodyModel.bindAnim(&this->animationChr, unk2);
	this->animationChr.setUpdateRate(rate);
}


void daCustomPakkun::setupBodyModel() {
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("pakkun", this->brresName);
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("pakkun");
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_Enemy(&bodyModel, 0);

	bool ret;
	nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr("fire_wait_up");
	ret = this->animationChr.setup(mdl, anmChr, &this->allocator, 0);

	allocator.unlink();
}


int daCustomPakkun::onCreate() {

	this->type = this->settings >> 28 & 0xF;
	if (this->type == 0) {
		this->brresName = "g3d/t01.brres";
	}
	if (this->type == 1) {
		this->brresName = "g3d/t02.brres";
	}
	if (this->type == 2) {
		this->brresName = "g3d/t03.brres";
	}
	if (this->type == 3) {
		this->brresName = "g3d/t04.brres";
	}
	if (this->type == 4) {
		this->brresName = "g3d/t05.brres";
	}
	
	setupBodyModel();


	this->scale = (Vec){1.0, 1.0, 1.0};
	this->rot.x = 0; // X is vertical axis
	this->rot.y = 0xD800; // Y is horizontal axis
	this->rot.z = 0; // Z is ... an axis >.>
	this->direction = 1; // Heading left.

	ActivePhysics::Info HitMeBaby;
	
	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 0.0;

	HitMeBaby.xDistToEdge = 15.0;
	HitMeBaby.yDistToEdge = 15.0; 

	HitMeBaby.category1 = 0x3;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0x8028E;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();


	bindAnimChr_and_setUpdateRate("fire_wait_up", 1, 0.0, 1.0);

	doStateChange(&StateID_Attack);

	this->onExecute();
	return true;
}

int daCustomPakkun::onDelete() {
	return true;
}

int daCustomPakkun::onExecute() {
	acState.execute();
	updateModelMatrices();

	if(this->animationChr.isAnimationDone()) {
		this->animationChr.setCurrentFrame(0.0);
	}

	return true;
}


int daCustomPakkun::onDraw() {
	bodyModel.scheduleForDrawing();
	bodyModel._vf1C();
	return true;
}


void daCustomPakkun::updateModelMatrices() {
	// This won't work with wrap because I'm lazy.
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}


// Attack State

void daCustomPakkun::beginState_Attack() {
}

void daCustomPakkun::executeState_Attack() {
	u8 facing = dSprite_c__getXDirectionOfFurthestPlayerRelativeToVEC3(this, this->pos);
	if (facing != this->direction) {
		this->direction = facing;
		if (this->direction == 1) {
			this->rot.y = 0xD800;
		}
		else {
			this->rot.y = 0x2800;
		}
	}
	if(this->animationChr.isAnimationDone() && this->delayforshooting == 2) {
		bindAnimChr_and_setUpdateRate("fire_wait_up", 1, 0.0, 1.0);
		this->animationChr.setCurrentFrame(0.0);
		this->delayforshooting -= 2;
	}
	if(this->delayforshooting == 0 || this->delayforshooting == 1) {
		if(this->animationChr.isAnimationDone()) {
			if(this->delayforshooting == 1) {
				bindAnimChr_and_setUpdateRate("fire_attack_down", 1, 0.0, 1.0);
			}
			this->animationChr.setCurrentFrame(0.0);
			this->delayforshooting++;
		}
	}
	if(this->animationChr.getCurrentFrame() == 26.00 && this->delayforshooting == 2) {
		Actors shootItem;
		int soundID;
		if (type == 0) {
			shootItem = BROS_ICEBALL;
			soundID = SE_EMY_ICE_BROS_ICE;
			this->spawnersettings = 0;
		}
		if (type == 1) {
			//Unused because for some reason the hammer don't spawn
			shootItem = HAMMER;
			soundID = SE_EMY_HAMMER_BROS_HAMMER;
			this->spawnersettings = 0;
		}
		if (type == 2) {
			shootItem = BIGHANA_MGR;
			soundID = SE_EMY_PAKKUN_FIRE;
			this->spawnersettings = 0;
		}
		if (type == 3) {
			shootItem = BIGHANA_MGR;
			soundID = SE_EMY_PAKKUN_MOUTH;
			this->spawnersettings = 1;
		}
		if (type == 4) {
			shootItem = BIGHANA_MGR;
			soundID = SE_PLY_CANNON_SHOT;
			this->spawnersettings = 2;
		}
		if (this->direction == 1) {
			S16Vec nullRot = {0,0,0};
			dStageActor_c *spawner = create(shootItem, this->spawnersettings, &this->pos, &nullRot, 0);
			*((u32 *) (((char *) spawner) + 0x3DC)) = this->id;
			
			spawner->x_speed_inc = 0.0f;
			spawner->y_speed_inc = 0.0f;
			
			float totalSpeed = 1.0f;

			dAc_Py_c *mario = GetSpecificPlayerActor(0);
			float ratio = (this->pos.y - mario->pos.y) / (this->pos.x - mario->pos.x);
			spawner->speed.x = sqrtf(totalSpeed * totalSpeed / (1 + ratio * ratio));
			spawner->speed.x = spawner->speed.x * -1;
			spawner->speed.y = ratio * spawner->speed.x;
			
			spawner->pos.x -= 7.5;
		}
		if (this->direction == 0) {
			S16Vec nullRot = {0,0,0};
			dStageActor_c *spawner = create(shootItem, this->spawnersettings, &this->pos, &nullRot, 0);
			*((u32 *) (((char *) spawner) + 0x3DC)) = this->id;

			spawner->x_speed_inc = 0.0f;
			spawner->y_speed_inc = 0.0f;

			float totalSpeed = 1.0f;

			dAc_Py_c *mario = GetSpecificPlayerActor(0);
			float ratio = (this->pos.y - mario->pos.y) / (this->pos.x - mario->pos.x);
			spawner->speed.x = sqrtf(totalSpeed * totalSpeed / (1 + ratio * ratio));
			spawner->speed.y = ratio * spawner->speed.x;
			
			spawner->pos.x += 7.5;
		}
		
		PlaySoundAsync(this, soundID);
	}
	
	
	if(this->animationChr.isAnimationDone()) {
		this->animationChr.setCurrentFrame(0.0);
	}
}
void daCustomPakkun::endState_Attack() {
}

// Outro State

void daCustomPakkun::beginState_Outro() {
	this->removeMyActivePhysics();
	PlaySound(this, SE_EMY_BLOW_PAKKUN_DOWN);
}
void daCustomPakkun::executeState_Outro() {
	if(this->animationChr.isAnimationDone()) {
		this->Delete(1);
	}
}
void daCustomPakkun::endState_Outro() { 

}





