#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <stage.h>
#include <playerAnim.h>
#include "boss.h"

extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);

const char* TLCarcNameList [] = {
	"tcloud",
	NULL
};

class dThunderCloud : public dEn_c {
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	mHeapAllocator_c allocator;
	m3d::mdl_c bodyModel;
	nw4r::g3d::ResFile resFile;

	u64 eventFlag;
	s32 timer;
	u32 delay;

	u32 effect;
	u8 type;
	dAcPy_c *player;;

	static dThunderCloud *build();
	int tim;

	void updateModelMatrices();
	void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther);
	
	int exittype;
	int transition;
};

extern "C" int CheckExistingPowerup(void * Player);
extern "C" void *dAcPy_c__ChangePowerupWithAnimation(void * Player, int powerup);
extern "C" void dAcPy_vf3F4(void* mario, void* other, int t);

void dThunderCloud::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
	int p = CheckExistingPowerup(apOther->owner);
	if (p != 0 && p != 3) {	// Powerups - 0 = small; 1 = big; 2 = fire; 3 = mini; 4 = prop; 5 = peng; 6 = ice; 7 = hammer
		dAcPy_c__ChangePowerupWithAnimation(apOther->owner, 0);
	}
	tim++;
	OSReport("I'm increasing my time to ", tim);
	if (tim == 120) {
		if (p == 0) {	// Powerups - 0 = small; 1 = big; 2 = fire; 3 = mini; 4 = prop; 5 = peng; 6 = ice; 7 = hammer
		dAcPy_c__ChangePowerupWithAnimation(apOther->owner, 3);
		}
		this->tim = 0;
	}
}

bool dThunderCloud::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dThunderCloud::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dThunderCloud::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dThunderCloud::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}

bool dThunderCloud::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {

}
bool dThunderCloud::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {

}
bool dThunderCloud::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {

}
bool dThunderCloud::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dThunderCloud::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat1_Fireball_E_Explosion(apThis, apOther);
}

bool dThunderCloud::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}



dThunderCloud *dThunderCloud::build() {
	void *buf = AllocFromGameHeap1(sizeof(dThunderCloud));
	return new(buf) dThunderCloud;
}



int dThunderCloud::onCreate() {

	this->exittype = this->settings >> 28 & 0xF;
	this->transition = this->settings >> 12 & 0xF;

	// Model creation
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("star_coin", "g3d/star_coin.brres");
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("star_coinA");
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);

	allocator.unlink();

	this->scale = (Vec){0.39, 0.39, 0.39};

	ActivePhysics::Info HitMeBaby;

	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 12.0;

	HitMeBaby.xDistToEdge = 8.0;
	HitMeBaby.yDistToEdge = 14.0;

	HitMeBaby.category1 = 0x3;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x01;
	HitMeBaby.bitfield2 = 0x820A0;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	this->onExecute();
	return true;
}


int dThunderCloud::onDelete() {
	return true;
}

int dThunderCloud::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void dThunderCloud::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int dThunderCloud::onExecute() {
	updateModelMatrices();

	this->rot.x += 0x200;
	return true;
}

