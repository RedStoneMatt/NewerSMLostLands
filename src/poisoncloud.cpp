#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <timekeeper.h>

bool isPlayerPoisoned[4];
bool playerCollisionFrame;
int howmuchpassed;

const char* BLarcNameList [] = {
	"clock",
	NULL
};

extern "C" bool SpawnEffect(const char*, int, Vec*, S16Vec*, Vec*);


class daPoisonCloud_c : public dEn_c {
	int onCreate();
	int onExecute();
	int onDelete();
	int onDraw();

	mHeapAllocator_c allocator;
	m3d::mdl_c bodyModel;

	u64 eventFlag;
	u32 timer;
	u32 delay;

	u32 effect;
	u8 type;

	static daPoisonCloud_c *build();

	void poisonDamage(ActivePhysics *apOther);

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



void daPoisonCloud_c::poisonDamage(ActivePhysics *apOther) {
	howmuchpassed = 0;
	playerCollisionFrame = true;
	nw4r::lyt::Picture *poisonusbar = dGameDisplay_c::instance->layout.findPictureByName("P_PoisonBar_00");
	if(poisonusbar->size.y > 0) {
		VEC2 shit = {poisonusbar->size.x, poisonusbar->size.y - 0.1f};
		poisonusbar->size = shit;
	}
	if(poisonusbar->size.y <= 0) {
		this->_vf220(apOther->owner);
		VEC2 shit = {poisonusbar->size.x, 49.0f};
		poisonusbar->size = shit;
	}
	dAcPy_c *player = (dAcPy_c *)apOther->owner;
	isPlayerPoisoned[((player->which_player >> 0) & 0xF)] = true;
}

void daPoisonCloud_c::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
	poisonDamage(apOther);
}

bool daPoisonCloud_c::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
	poisonDamage(apOther);
	return false;
}
bool daPoisonCloud_c::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
	poisonDamage(apOther);
	return false;
}
bool daPoisonCloud_c::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daPoisonCloud_c::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}

bool daPoisonCloud_c::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
	return false;
}
bool daPoisonCloud_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) {
	return false;
}
bool daPoisonCloud_c::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
	return false;
}
bool daPoisonCloud_c::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}
bool daPoisonCloud_c::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat1_Fireball_E_Explosion(apThis, apOther);
}

bool daPoisonCloud_c::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther) {
	return collisionCat9_RollingObject(apThis, apOther);
}



daPoisonCloud_c *daPoisonCloud_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daPoisonCloud_c));
	return new(buffer) daPoisonCloud_c;
}


int daPoisonCloud_c::onCreate() {

	allocator.link(-1, GameHeaps[0], 0, 0x20);

	nw4r::g3d::ResFile rf(getResource("clock", "g3d/clock.brres"));
	bodyModel.setup(rf.GetResMdl("ClockGreen"), &allocator, 0x224, 1, 0);
	SetupTextures_MapObj(&bodyModel, 0);

	allocator.unlink();

	ActivePhysics::Info HitMeBaby;
	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = -3.0;
	HitMeBaby.xDistToEdge = 24.0;
	HitMeBaby.yDistToEdge = 30.0;
	HitMeBaby.category1 = 0x5;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0xFFFFFFFF;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();

	this->scale.x = 1.0;
	this->scale.y = 1.0;
	this->scale.z = 1.0;

	this->pos.x -= 120.0;
	this->pos.z = 3300.0;

	this->onExecute();
	return true;
}


int daPoisonCloud_c::onDelete() {
	return true;
}

int daPoisonCloud_c::onDraw() {
	bodyModel.scheduleForDrawing();
	return true;
}


void daPoisonCloud_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}

int daPoisonCloud_c::onExecute() {
	updateModelMatrices();

	timer++;

	this->rot.x += 0x200;
	return true;
}


int dAcPy_c::newOnExecute() {
	int orig_val = this->onExecute_orig();
	// OSReport("playerCollisionFrame: %d | howmuchpassed: %d | isPlayerPoisoned[]: %d\n", playerCollisionFrame, howmuchpassed, isPlayerPoisoned[((this->which_player >> 0) & 0xF)]);
	if(playerCollisionFrame) {
		if(!isPlayerPoisoned[((this->which_player >> 0) & 0xF)]) {
			nw4r::lyt::Picture *poisonusbar = dGameDisplay_c::instance->layout.findPictureByName("P_PoisonBar_00");
			if(poisonusbar->size.y <= 49) {
				VEC2 shit = {poisonusbar->size.x, poisonusbar->size.y + 0.1f};
				poisonusbar->size = shit;
			}
		}
	}
	howmuchpassed++;
	if(howmuchpassed > 10) {
		playerCollisionFrame = false;
		isPlayerPoisoned[((this->which_player >> 0) & 0xF)] = false;
		howmuchpassed = 0;
	}
	if(!playerCollisionFrame) {
		nw4r::lyt::Picture *poisonusbar = dGameDisplay_c::instance->layout.findPictureByName("P_PoisonBar_00");
		if(poisonusbar->size.y <= 49) {
			VEC2 shit = {poisonusbar->size.x, poisonusbar->size.y + 0.1f};
			poisonusbar->size = shit;
		}
	}
	return orig_val;
}