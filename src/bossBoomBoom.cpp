#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <stage.h>
#include "boss.h"

const char* BBarcNameList [] = {
	"bunbun",
	NULL	
};

class daBunbun : public daBoss {
public:
	int onCreate();
	int onDelete();
	int onExecute();
	int onDraw();

	mHeapAllocator_c allocator;
	nw4r::g3d::ResFile resFile;
	m3d::anmChr_c animationChr;
	m3d::anmClr_c animationClr;

	m3d::mdl_c bodyModel;


	char isDown;
	float XSpeed;
	u32 cmgr_returnValue;
	bool isBouncing;
	char isInSpace;
	char fromBehind;
	char isInvulnerable;
	int isInvulnerableCountdown;
	int isTurningCountdown;
	char charging;
	int directiontomove;

	float dying;

	static daBunbun *build();

	void bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate);
	void bindAnimClr_and_setUpdateRate(const char* name, int unk, float unk2, float rate);
	void updateModelMatrices();
	bool calculateTileCollisions();

	void powBlockActivated(bool isNotMPGP);

	void spriteCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	void playerCollision(ActivePhysics *apThis, ActivePhysics *apOther);
	void yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther);

	bool collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther);
	bool collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther);

	void addScoreWhenHit(void *other);

	USING_STATES(daBunbun);
	DECLARE_STATE(Intro);
	DECLARE_STATE(Charge);
	DECLARE_STATE(Turn);
	DECLARE_STATE(Damage);
	DECLARE_STATE(Outro);


};

daBunbun *daBunbun::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daBunbun));
	return new(buffer) daBunbun;
}

///////////////////////
// Externs and States
///////////////////////
	extern "C" void *EN_LandbarrelPlayerCollision(dEn_c* t, ActivePhysics *apThis, ActivePhysics *apOther);
	// CalculateDistanceFromActorsNextPosToFurthestPlayer???
	extern "C" int SmoothRotation(short* rot, u16 amt, int unk2);


	CREATE_STATE(daBunbun, Intro);
	CREATE_STATE(daBunbun, Charge);
	CREATE_STATE(daBunbun, Turn);
	CREATE_STATE(daBunbun, Damage);
	CREATE_STATE(daBunbun, Outro);


////////////////////////
// Collision Functions
////////////////////////

	void daBunbun::addScoreWhenHit(void *other) { };

	void daBunbun::spriteCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
		// if (apOther->owner->name == 390) { //time to get hurt
			// OSReport("YO SUP I'M A TOPMAN AND I'M COLLIDING WITH A FUCKING WALL [%d]\n", damage);
			// if (this->isInvulnerable) {
				// OSReport("I'm invulnerable so I'm ignoring it\n");
				// return;
			// }
			// this->damage += 1;
			// OSReport("I'm increasing my damage to %d\n", damage);
			// doStateChange(&StateID_Damage);

			// if (this->damage == 3) { doStateChange(&StateID_Outro); }
		// }
		// else { dEn_c::spriteCollision(apThis, apOther); }
	}

	void daBunbun::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
		char hitType;
		hitType = usedForDeterminingStatePress_or_playerCollision(this, apThis, apOther, 0);
		
		if(hitType > 0) {
			doStateChange(&StateID_Damage);
		}
		else {
			this->_vf220(apOther->owner);
		}

		deathInfo.isDead = 0;
		this->flags_4FC |= (1<<(31-7));
	}

	void daBunbun::yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
		this->playerCollision(apThis, apOther);
	}

	bool daBunbun::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
		this->playerCollision(apThis, apOther);
		return true;
	}
	bool daBunbun::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
		this->playerCollision(apThis, apOther);
		return true;
	}
	bool daBunbun::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
		this->playerCollision(apThis, apOther);
		return true;
	}

	bool daBunbun::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
		return true;
	}
	bool daBunbun::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther){
		DamagePlayer(this, apThis, apOther);
		return true;
	}


	bool daBunbun::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther){ return true; }
	bool daBunbun::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) { return true; }
	bool daBunbun::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther){ return true; }
	bool daBunbun::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) { return true; }
	bool daBunbun::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) { return true; }

void daBunbun::powBlockActivated(bool isNotMPGP) { }


bool daBunbun::calculateTileCollisions() {
	// Returns true if sprite should turn, false if not.

	HandleXSpeed();
	HandleYSpeed();
	doSpriteMovement();

	cmgr_returnValue = collMgr.isOnTopOfTile();
	collMgr.calculateBelowCollisionWithSmokeEffect();

	if (isBouncing) {
		stuffRelatingToCollisions(0.1875f, 1.0f, 0.5f);
		if (speed.y != 0.0f)
			isBouncing = false;
	}

	float xDelta = pos.x - last_pos.x;
	if (xDelta >= 0.0f)
		direction = 0;
	else
		direction = 1;

	if (collMgr.isOnTopOfTile()) {
		// Walking into a tile branch

		if (cmgr_returnValue == 0)
			isBouncing = true;

		if (speed.x != 0.0f) {
			//playWmEnIronEffect();
		}

		speed.y = 0.0f;

		// u32 blah = collMgr.s_80070760();
		// u8 one = (blah & 0xFF);
		// static const float incs[5] = {0.00390625f, 0.0078125f, 0.015625f, 0.0234375f, 0.03125f};
		// x_speed_inc = incs[one];
		max_speed.x = (direction == 1) ? -1.0f : 1.0f;
	} else {
		x_speed_inc = 0.0f;
	}

	// Bouncing checks
	if (_34A & 4) {
		Vec v = (Vec){0.0f, 1.0f, 0.0f};
		collMgr.pSpeed = &v;

		if (collMgr.calculateAboveCollision(collMgr.outputMaybe))
			speed.y = 0.0f;

		collMgr.pSpeed = &speed;

	} else {
		if (collMgr.calculateAboveCollision(collMgr.outputMaybe))
			speed.y = 0.0f;
	}

	collMgr.calculateAdjacentCollision(0);

	// Switch Direction
	if (collMgr.outputMaybe & (0x15 << direction)) {
		if (collMgr.isOnTopOfTile()) {
			isBouncing = true;
		}
		return true;
	}
	return false;
}

void daBunbun::bindAnimChr_and_setUpdateRate(const char* name, int unk, float unk2, float rate) {
	nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr(name);
	this->animationChr.bind(&this->bodyModel, anmChr, unk);
	this->bodyModel.bindAnim(&this->animationChr, unk2);
	this->animationChr.setUpdateRate(rate);
}

void daBunbun::bindAnimClr_and_setUpdateRate(const char* name, int unk, float unk2, float rate) {
	nw4r::g3d::ResAnmClr anmRes = this->resFile.GetResAnmClr(name);
	this->animationClr.bind(&this->bodyModel, anmRes, 0, 0);
	this->bodyModel.bindAnim(&this->animationClr, 0.0);
}

int daBunbun::onCreate() {

	// Model creation
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("bunbun", "g3d/bunbun.brres");
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("bunbun");
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_Map(&bodyModel, 0);


	// Animations start here
	nw4r::g3d::ResAnmChr anmChr = this->resFile.GetResAnmChr("wait");
	this->animationChr.setup(mdl, anmChr, &this->allocator, 0);

	nw4r::g3d::ResAnmClr anmRess = this->resFile.GetResAnmClr("normal");
	this->animationClr.setup(mdl, anmRess, &this->allocator, 0, 1);
	this->animationClr.bind(&this->bodyModel, anmRess, 0, 0);
	this->bodyModel.bindAnim(&this->animationClr, 0.0);

	allocator.unlink();

	// Stuff I do understand
	this->scale = (Vec){1.0, 1.0, 1.0};

	this->rot.x = 0; // X is vertical axis
	this->rot.y = 0xD800; // Y is horizontal axis
	this->rot.z = 0; // Z is ... an axis >.>
	this->direction = 1; // Heading left.

	this->speed.x = 0.0;
	this->speed.y = 0.0;
	this->max_speed.x = 1.1;
	this->x_speed_inc = 0.0;
	this->XSpeed = 1.1;

	this->isInSpace = this->settings & 0xF;
	this->fromBehind = 0;


	ActivePhysics::Info HitMeBaby;

	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 24.0;

	HitMeBaby.xDistToEdge = 28.0;
	HitMeBaby.yDistToEdge = 24.0;

	HitMeBaby.category1 = 0x3;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x4F;
	HitMeBaby.bitfield2 = 0xffbafffe;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;
	this->directiontomove = -1;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();


	// Tile collider

	// These fucking rects do something for the tile rect
	spriteSomeRectX = 28.0f;
	spriteSomeRectY = 32.0f;
	_320 = 0.0f;
	_324 = 16.0f;

	// These structs tell stupid collider what to collide with - these are from koopa troopa
	static const lineSensor_s below(12<<12, 4<<12, 0<<12);
	static const pointSensor_s above(0<<12, 12<<12);
	static const lineSensor_s adjacent(6<<12, 9<<12, 6<<12);

	collMgr.init(this, &below, &above, &adjacent);
	collMgr.calculateBelowCollisionWithSmokeEffect();

	cmgr_returnValue = collMgr.isOnTopOfTile();

	if (collMgr.isOnTopOfTile())
		isBouncing = false;
	else
		isBouncing = true;


	// State Changers
	bindAnimChr_and_setUpdateRate("wait", 1, 0.0, 1.0);
	bindAnimClr_and_setUpdateRate("normal", 1, 0.0, 1.0);
	doStateChange(&StateID_Intro);

	this->onExecute();
	return true;
}

int daBunbun::onDelete() {
	return true;
}

int daBunbun::onExecute() {
	acState.execute();
	updateModelMatrices();

	return true;
}

int daBunbun::onDraw() {

	bodyModel.scheduleForDrawing();

	bodyModel._vf1C();


	return true;
}

void daBunbun::updateModelMatrices() {
	matrix.translation(pos.x, pos.y - 2.0, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}



///////////////
// Intro State
///////////////
	void daBunbun::beginState_Intro() {
		bindAnimChr_and_setUpdateRate("wait", 1, 0.0, 0.75);

		this->timer = 0;

		SetupKameck(this, Kameck);
	}

	void daBunbun::executeState_Intro() {
		if(this->animationChr.isAnimationDone()) {
			this->animationChr.setCurrentFrame(0.0);
		}

		this->timer += 1;

		bool ret;
		ret = GrowBoss(this, Kameck, 1, 2, 0, this->timer);

		if (ret) {
			PlaySound(this, SE_EMY_MECHAKOOPA_BOUND);
			doStateChange(&StateID_Charge);
		}
	}
	void daBunbun::endState_Intro() {
		this->animationChr.setUpdateRate(1.0);
		CleanupKameck(this, Kameck);
	}




///////////////
// Turn State
///////////////
	void daBunbun::beginState_Turn() {
		this->direction ^= 1;
		this->speed.x = 0.0;
	}
	void daBunbun::executeState_Turn() {

		if(this->animationChr.isAnimationDone()) {
			this->animationChr.setCurrentFrame(0.0);
		}

		u16 amt = (this->direction == 0) ? 0x2800 : 0xD800;
		int done = SmoothRotation(&this->rot.y, amt, 0x800);

		if(done) {
			doStateChange(&StateID_Charge);
		}
	}
	void daBunbun::endState_Turn() { this->rot.y = (this->direction) ? 0xD800 : 0x2800; }




///////////////
// Charge State
///////////////
	void daBunbun::beginState_Charge() {
		bindAnimChr_and_setUpdateRate("run", 1, 0.0, 1.0);
		this->timer = 0;
		this->isTurningCountdown = 0;

		this->charging = 1;
	}
	void daBunbun::executeState_Charge() {
		if(this->animationChr.isAnimationDone()) {
			this->animationChr.setCurrentFrame(0.0);
		}

		bool ret = calculateTileCollisions();
		if (ret) {
			u16 amt;
			amt = (this->direction == 0) ? 0x2800 : 0xD800;
			int done = SmoothRotation(&this->rot.y, amt, 0x800);
			if(this->rot.y == 0xD800) {
				this->direction = 1;
			}
			if(this->rot.y == 0x2800) {
				this->direction = 0;
			}
		}
		else {
			if(this->direction == 1) {
				this->directiontomove = 2;
			}
			if(this->direction == 0) {
				this->directiontomove = -2;
			}
			this->pos.x += 1 * this->directiontomove;
		}
	}
	void daBunbun::endState_Charge() {
		this->charging = 0;
	}



///////////////
// Damage State
///////////////
	void daBunbun::beginState_Damage() {
		this->isInvulnerable = 1;
		bindAnimChr_and_setUpdateRate("damage", 1, 0.0, 0.75);
		bindAnimClr_and_setUpdateRate("damage", 1, 0.0, 0.75);
		this->timer = 0;
		this->damage++;
	}
	void daBunbun::executeState_Damage() {
		if(this->damage < 3) {
			if(this->animationChr.isAnimationDone()) {
				this->timer += 1;
				if (this->timer == 1) {
					u8 dir = dSprite_c__getXDirectionOfFurthestPlayerRelativeToVEC3(this, this->pos);
					if (dir != this->direction) {
						doStateChange(&StateID_Turn);
					}
					else {
						doStateChange(&StateID_Charge);
					}
				}
				this->animationChr.setCurrentFrame(0.0);
			}
		}
		else {
			doStateChange(&StateID_Outro);
		}
	}
	void daBunbun::endState_Damage() {
		bindAnimChr_and_setUpdateRate("run", 1, 0.0, 1.0);
		bindAnimClr_and_setUpdateRate("normal", 1, 0.0, 0.75);
		this->isInvulnerableCountdown = 90;
	}


///////////////
// Outro State
///////////////
	void daBunbun::beginState_Outro() {
		OutroSetup(this);
		bindAnimChr_and_setUpdateRate("dead", 1, 0.0, 1.0);
	}
	void daBunbun::executeState_Outro() {
		if(this->animationChr.isAnimationDone()) {
			animationChr.setCurrentFrame(0.0);
		}
		if (this->dying == 1) {
			if (this->timer > 180) { ExitStage(WORLD_MAP, 0, BEAT_LEVEL, MARIO_WIPE); }
			if (this->timer == 60) { PlayerVictoryCries(this); }

			this->timer += 1;
			return;
		}

		bool ret;
		ret = ShrinkBoss(this, &this->pos, 1, this->timer);

		if (ret == true) 	{
			BossExplode(this, &this->pos);
			this->dying = 1;
			this->timer = 0;
		}
		else 		{ PlaySound(this, SE_EMY_BUBBLE_EXTINCT); }

		this->timer += 1;
	}
	void daBunbun::endState_Outro() { }
