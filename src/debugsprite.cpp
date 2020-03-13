#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>




class daDebugSprite : public dEn_c {
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	mHeapAllocator_c allocator;
	m3d::mdl_c bodyModel;

	u64 eventFlag;
	s32 timer;
	u32 delay;

	u32 effect;
	u8 type;

	static daDebugSprite *build();

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

};


void daDebugSprite::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {

}

bool daDebugSprite::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daDebugSprite::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daDebugSprite::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daDebugSprite::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}

bool daDebugSprite::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daDebugSprite::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daDebugSprite::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daDebugSprite::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daDebugSprite::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat1_Fireball_E_Explosion(apThis, apOther);
}

bool daDebugSprite::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}



daDebugSprite *daDebugSprite::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daDebugSprite));
	return new(buffer) daDebugSprite;
}

extern "C" float pow(float num, float power);

int getNybbleValue(u32 settings, int fromNybble, int toNybble) {
	int numberOfNybble = (toNybble  - fromNybble) + 1;               //gets how many nybbles are used for the process (example: nybbles 4-6 -> there's nybbles 4, 5 and 6 used -> numberOfNybble = 3) 
	int valueToUse = 48 - (4 * toNybble);                            //gets the value to use with the bitshift at the end 
	int fShit = pow(16, numberOfNybble) - 1;                         //gets the value to use with the "&" operator at the end 
	OSReport("-> (settings >> %d) & 0x%x) => ", valueToUse, fShit);  //debugging
	return ((settings >> valueToUse) & fShit);                       //uses everything to make the nybble value 
}

int daDebugSprite::onCreate() {

	allocator.link(-1, GameHeaps[0], 0, 0x20);

	nw4r::g3d::ResFile rf(getResource("star_coin", "g3d/star_coin.brres"));
	bodyModel.setup(rf.GetResMdl("star_coinA"), &allocator, 0x224, 1, 0);
	SetupTextures_MapObj(&bodyModel, 0);

	allocator.unlink();

	ActivePhysics::Info HitMeBaby;
	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = -3.0;
	HitMeBaby.xDistToEdge = 12.0;
	HitMeBaby.yDistToEdge = 15.0;
	HitMeBaby.category1 = getNybbleValue(this->settings, 5, 7);                   //5-7
	HitMeBaby.category2 = getNybbleValue(this->settings, 8, 8);                   //8
	HitMeBaby.bitfield1 = getNybbleValue(this->settings, 9, 10);                  //9-10
	HitMeBaby.bitfield2 = 0xFFFFFFFF; //getNybbleValue(this->settings, 12, 12)    //12
	HitMeBaby.unkShort1C = getNybbleValue(this->settings, 11, 11);                //11
	HitMeBaby.callback = &dEn_c::collisionCallback;


	OSReport("----------\nDebugSprite:\n");
	OSReport("category1 = %x\n", getNybbleValue(this->settings, 5, 7));
	OSReport("category2 = %x\n", getNybbleValue(this->settings, 8, 8));
	OSReport("bitfield1 = %x\n", getNybbleValue(this->settings, 9, 10));
	OSReport("bitfield2 = %x\n", getNybbleValue(this->settings, 12, 12));
	OSReport("unkShort1C = %x\n", getNybbleValue(this->settings, 11, 11));
	OSReport("----------\n");

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	this->scale.x = 1.0;
	this->scale.y = 1.0;
	this->scale.z = 1.0;

	this->onExecute();
	return true;
}


int daDebugSprite::onDelete() {
	return true;
}

int daDebugSprite::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void daDebugSprite::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
}

int daDebugSprite::onExecute() {
	updateModelMatrices();

	return true;
}

