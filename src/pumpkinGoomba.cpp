#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <dCourse.h>
#include <playerAnim.h>
#include <stage.h>

u32 setTime = 10;
u32 keepTime;
extern u32 GameTimer;
#define time *(u32*)((GameTimer) + 0x4)


struct TimerSpecial {
	u32 id;			// 0x00
	u32 settings;	// 0x04
	u16 name;		// 0x08
	u8 _0A[6];		// 0x0A
	u8 _10[0x9C];	// 0x10
	float x;		// 0xAC
	float y;		// 0xB0
	float z;		// 0xB4
	u8 _B8[0x318];	// 0xB8
	// Any variables you add to the class go here; starting at offset 0x3D0
	u64 eventFlag;	// 0x3D0
	u8 type;		// 0x3D4
	u8 effect;		// 0x3D5
	u8 lastEvState;	// 0x3D6
	u8 func;		// 0x3D7
	u32 keepTime;
	u32 setTime = 10;
};

bool TimerSpecial_Create(TimerSpecial *self) {
	char eventNum	= (self->settings >> 24)	& 0xFF;
	self->eventFlag = (u64)1 << (eventNum - 1);
	
	self->keepTime  = 0;
	
	self->type		= (self->settings)			& 15;
	self->effect	= (self->settings >> 4)		& 15;
	self->setTime	= (self->settings >> 8)     & 0xFFFF;

	self->lastEvState = 0xFF;
	
	//TimerSpecial_Update(self);
	
	return true;
}

bool TimerSpecial_Execute(TimerSpecial *self) {
	if (self->keepTime > 0) {
		time = self->keepTime; }

	//TimerSpecial_Update(self);
	return true;
}

extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);

const char* Notees[2] = {
	"sfx/clock",
	"sfx/clock"
};

extern "C" void PlaySoundWithFunctionB4(void *spc, nw4r::snd::SoundHandle *handle, int id, int unk);
static nw4r::snd::StrmSoundHandle handle;

u8 hijackMusicWithSongName(const char *songName, int themeID, bool hasFast, int channelCount, int trackCount, int *wantRealStreamID);

void BonusMusicPlayert(int id) {
	if (handle.Exists())
		handle.Stop(0);

	int sID;
	hijackMusicWithSongName(Notees[1], -1, false, 2, 1, &sID);
	PlaySoundWithFunctionB4(SoundRelatedClass, &handle, sID, 1);
	}

const char* GParcNameList [] = {
	"clock",
	"wing",
	NULL
};

class dGoombaPie : public dEn_c {
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();
	int Songs[16][4][16][3];
	int song;
 	int chorus;
	int currentNotee;

	mHeapAllocator_c allocator;
	m3d::mdl_c bodyModel;
	nw4r::g3d::ResFile resFile;

	static dGoombaPie *build();

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

void pieCollisionCallback(ActivePhysics *one, ActivePhysics *two) {

		dEn_c::collisionCallback(one, two);
}
	

void dGoombaPie::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
	BonusMusicPlayert(Songs[song][chorus][currentNotee][1]-1);
	time = (setTime << 0xC) -1;

	this->Delete(1);
}

bool dGoombaPie::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dGoombaPie::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dGoombaPie::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dGoombaPie::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}

bool dGoombaPie::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dGoombaPie::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dGoombaPie::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {

	BonusMusicPlayert(Songs[song][chorus][currentNotee][1]-1);
	time = (setTime << 0xC) -1; // Possibly - 0xFFF?
	this->Delete(1);
	return true;
}
bool dGoombaPie::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool dGoombaPie::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat1_Fireball_E_Explosion(apThis, apOther);
}

bool dGoombaPie::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}



dGoombaPie *dGoombaPie::build() {
	void *buffer = AllocFromGameHeap1(sizeof(dGoombaPie));
	return new(buffer) dGoombaPie;
}


int dGoombaPie::onCreate() {


	// Model creation
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("I_star", "g3d/clock.brres");
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("Clock");
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
	HitMeBaby.callback = &pieCollisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	this->onExecute();
	return true;
}


int dGoombaPie::onDelete() {
	return true;
}

int dGoombaPie::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void dGoombaPie::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int dGoombaPie::onExecute() {
	updateModelMatrices();

	this->rot.y += 0x200;
	return true;
}