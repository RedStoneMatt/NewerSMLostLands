#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <stage.h>
#include "boss.h"

extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);

const char *ChestnutFileList[] = {"chestnut", 0};

class daEnChestnut_c : public dEn_c {
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

	static daEnChestnut_c *build();

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


void daEnChestnut_c::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
	PlaySound(this, SE_EMY_CS_TERESA_BEAT_YOU);
	ExitStage(WORLD_MAP, 0, exittype, transition);
}

bool daEnChestnut_c::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daEnChestnut_c::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daEnChestnut_c::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daEnChestnut_c::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}

bool daEnChestnut_c::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {

}
bool daEnChestnut_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {

}
bool daEnChestnut_c::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {

}
bool daEnChestnut_c::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daEnChestnut_c::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat1_Fireball_E_Explosion(apThis, apOther);
}

bool daEnChestnut_c::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}



daEnChestnut_c *daEnChestnut_c::build() {
	void *buf = AllocFromGameHeap1(sizeof(daEnChestnut_c));
	return new(buf) daEnChestnut_c;
}



int daEnChestnut_c::onCreate() {

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


int daEnChestnut_c::onDelete() {
	return true;
}

int daEnChestnut_c::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void daEnChestnut_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int daEnChestnut_c::onExecute() {
	updateModelMatrices();

	this->rot.x += 0x200;
	return true;
}

