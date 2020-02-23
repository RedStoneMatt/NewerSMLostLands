#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <timekeeper.h>

const char* TCarcNameList [] = {
	"clock",
	NULL
};

extern "C" void PlaySoundWithFunctionB4(void *spc, nw4r::snd::SoundHandle *handle, int id, int unk);
static nw4r::snd::StrmSoundHandle handle;

u8 hijackMusicWithSongName(const char *songName, int themeID, bool hasFast, int channelCount, int trackCount, int *wantRealStreamID);

void ClockMusicPlayer() {
	if (handle.Exists())
		handle.Stop(0);

	int sID;
	hijackMusicWithSongName("sfx/clock", -1, false, 2, 1, &sID);
	PlaySoundWithFunctionB4(SoundRelatedClass, &handle, sID, 1);
}


class daTimeClock_c : public dEn_c {
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	mHeapAllocator_c allocator;
	m3d::mdl_c bodyModel;

	static daTimeClock_c *build();

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


void daTimeClock_c::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
	ClockMusicPlayer();
	OSReport("Time: %d\n", dGameDisplay_c::instance->timer);
	TimeKeeper::instance->setTime(dGameDisplay_c::instance->timer + 10);
	this->Delete(1);
}

bool daTimeClock_c::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daTimeClock_c::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daTimeClock_c::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daTimeClock_c::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}

bool daTimeClock_c::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daTimeClock_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daTimeClock_c::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}
bool daTimeClock_c::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daTimeClock_c::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat1_Fireball_E_Explosion(apThis, apOther);
}

bool daTimeClock_c::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) {
	return true;
}



daTimeClock_c *daTimeClock_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daTimeClock_c));
	return new(buffer) daTimeClock_c;
}


int daTimeClock_c::onCreate() {

	allocator.link(-1, GameHeaps[0], 0, 0x20);

	nw4r::g3d::ResFile rf(getResource("clock", "g3d/clock.brres"));
	bodyModel.setup(rf.GetResMdl("Clock"), &allocator, 0x224, 1, 0);
	SetupTextures_MapObj(&bodyModel, 0);

	allocator.unlink();

	ActivePhysics::Info HitMeBaby;
	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = -3.0;
	HitMeBaby.xDistToEdge = 12.0;
	HitMeBaby.yDistToEdge = 15.0;
	HitMeBaby.category1 = 0x5;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0xFFFFFFFF;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	this->scale.x = 0.39;
	this->scale.y = 0.39;
	this->scale.z = 0.39;

	this->pos.z = 3300.0;

	this->onExecute();
	return true;
}


int daTimeClock_c::onDelete() {
	return true;
}

int daTimeClock_c::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void daTimeClock_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int daTimeClock_c::onExecute() {
	updateModelMatrices();

	this->rot.y -= 0x200;
	return true;
}

