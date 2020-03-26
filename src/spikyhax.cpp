#include <common.h>
#include <game.h>
#include <g3dhax.h>
#include <sfx.h>
#include <timekeeper.h>

/*const char* SHarcNameList [] = {
	"hammerM",
	NULL	
};*/
int doWait = 0;


class daSpikyHax_c : public dEn_c {
	int onCreate();
	int onDelete();
	int onExecute();
	int onDraw();

	mHeapAllocator_c allocator;
	nw4r::g3d::ResFile resFile;

	m3d::mdl_c bodyModel;

	int alreadyOnTop = 0;

	float XSpeed;
	u32 cmgr_returnValue;
	bool isOnTopOfTile;

	static daSpikyHax_c *build();

	void updateModelMatrices();
	bool calculateTileCollisions();

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

	USING_STATES(daSpikyHax_c);
	DECLARE_STATE(Out);
	DECLARE_STATE(Walk);
	DECLARE_STATE(Turn);
	DECLARE_STATE(Die);
};

daSpikyHax_c *daSpikyHax_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daSpikyHax_c));
	return new(buffer) daSpikyHax_c;
}

///////////////////////
// States
///////////////////////


	CREATE_STATE(daSpikyHax_c, Out);
	CREATE_STATE(daSpikyHax_c, Walk);
	CREATE_STATE(daSpikyHax_c, Turn);
	CREATE_STATE(daSpikyHax_c, Die);


////////////////////////
// Collision Functions
////////////////////////


	void daSpikyHax_c::spriteCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
		u16 name = ((dEn_c*)apOther->owner)->name;

		if (name == EN_COIN || name == EN_EATCOIN || name == AC_BLOCK_COIN || name == EN_COIN_JUGEM || name == EN_COIN_ANGLE
			|| name == EN_COIN_JUMP || name == EN_COIN_FLOOR || name == EN_COIN_VOLT || name == EN_COIN_WIND
			|| name == EN_BLUE_COIN || name == EN_COIN_WATER || name == EN_REDCOIN || name == EN_GREENCOIN
			|| name == EN_JUMPDAI || name == EN_ITEM)
			{ return; }


		dEn_c::spriteCollision(apThis, apOther);
		((dEn_c*)apOther->owner)->collisionCat13_Hammer(apThis, apOther);
	}

	void daSpikyHax_c::playerCollision(ActivePhysics *apThis, ActivePhysics *apOther) {

	}

	void daSpikyHax_c::yoshiCollision(ActivePhysics *apThis, ActivePhysics *apOther) {

	}

	bool daSpikyHax_c::collisionCatD_Drill(ActivePhysics *apThis, ActivePhysics *apOther) {
		doStateChange(&StateID_Die);
		return true;
	}

	bool daSpikyHax_c::collisionCat7_GroundPound(ActivePhysics *apThis, ActivePhysics *apOther) {
		return true;
	}

	bool daSpikyHax_c::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
		return true;
	}

	bool daSpikyHax_c::collisionCat9_RollingObject(ActivePhysics *apThis, ActivePhysics *apOther) {
		doStateChange(&StateID_Die);
		return true;
	}

	bool daSpikyHax_c::collisionCat3_StarPower(ActivePhysics *apThis, ActivePhysics *apOther){
		return false;
	}

	bool daSpikyHax_c::collisionCat13_Hammer(ActivePhysics *apThis, ActivePhysics *apOther) {
		return false;
	}

	bool daSpikyHax_c::collisionCatA_PenguinMario(ActivePhysics *apThis, ActivePhysics *apOther){
		return true;
	}

	bool daSpikyHax_c::collisionCat14_YoshiFire(ActivePhysics *apThis, ActivePhysics *apOther){
		return false;
	}

	bool daSpikyHax_c::collisionCat1_Fireball_E_Explosion(ActivePhysics *apThis, ActivePhysics *apOther) {
		return false;
	}
	
	bool daSpikyHax_c::collisionCat2_IceBall_15_YoshiIce(ActivePhysics *apThis, ActivePhysics *apOther) { 
		return false;
	}


bool daSpikyHax_c::calculateTileCollisions() {
	// Returns true if sprite should turn, false if not.

	HandleXSpeed();
	HandleYSpeed();
	doSpriteMovement();

	cmgr_returnValue = collMgr.isOnTopOfTile();
	collMgr.calculateBelowCollisionWithSmokeEffect();

	stuffRelatingToCollisions(0.1875f, 1.0f, 0.5f);

	float xDelta = pos.x - last_pos.x;

	if (xDelta >= 0.0f) {
		direction = 0;
	}
	else {
		direction = 1;
	}

	if (collMgr.isOnTopOfTile()) {
		// Walking into a tile branch

		if(alreadyOnTop == 0) {
			PlaySound(this, SE_OBJ_ROCK_LAND);
			alreadyOnTop = 1;
		}

		if (cmgr_returnValue == 0)
			isOnTopOfTile = true;

		speed.y = 0.0f;
		max_speed.x = (direction == 1) ? -1.5f : 1.5f;
		this->x_speed_inc = 0.0f;
		this->speed.x = (direction == 1) ? -1.5f : 1.5f;
	}
	else {
		alreadyOnTop = 0;
	}

	collMgr.calculateAdjacentCollision(0);

	// Switch Direction
	if (collMgr.outputMaybe & (0x15 << direction)) {
		if (collMgr.isOnTopOfTile()) {
			isOnTopOfTile = true;
		}
		return true;
	}
	return false;
}

int daSpikyHax_c::onCreate() {

	this->deleteForever = true;

	// Model creation	
	allocator.link(-1, GameHeaps[0], 0, 0x20);

	this->resFile.data = getResource("hammerM", "g3d/iron_ball.brres");
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("iron_ball");
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);
	SetupTextures_MapObj(&bodyModel, 0);


	allocator.unlink();

	// Stuff I do understand
	this->scale = (Vec){0.7, 0.7, 0.7};

	this->rot.x = 0;
	this->rot.y = 0;
	this->rot.z = 0;
	this->direction = this->settings; // Heading where the player look.
	
	this->speed.x = 0.0;
	this->speed.y = 3.0;
	this->max_speed.x = 0.0;
	this->x_speed_inc = 0.0;
	this->XSpeed = 3.0;

	ActivePhysics::Info HitMeBaby;

	HitMeBaby.xDistToCenter = 0.0;
	HitMeBaby.yDistToCenter = 0.0;

	HitMeBaby.xDistToEdge = 7.5;
	HitMeBaby.yDistToEdge = 7.5;		

	HitMeBaby.category1 = 0x3;
	HitMeBaby.category2 = 0x0;
	HitMeBaby.bitfield1 = 0x6F;
	HitMeBaby.bitfield2 = 0xffbafffe;
	HitMeBaby.unkShort1C = 0;
	HitMeBaby.callback = &dEn_c::collisionCallback;

	this->aPhysics.initWithStruct(this, &HitMeBaby);
	this->aPhysics.addToList();


	// Tile collider

	// These fucking rects do something for the tile rect
	spriteSomeRectX = 28.0f;
	spriteSomeRectY = 32.0f;
	_320 = 0.0f;
	_324 = 16.0f;

	static const lineSensor_s below(-5<<12, 5<<12, -9<<12); // unk, unk, y pos 
	static const pointSensor_s above(0<<12, 12<<12);
	static const lineSensor_s adjacent(3<<12, 6<<12, 6<<12);

	collMgr.init(this, &below, &above, &adjacent);
	collMgr.calculateBelowCollisionWithSmokeEffect();

	cmgr_returnValue = collMgr.isOnTopOfTile();

	if (collMgr.isOnTopOfTile())
		isOnTopOfTile = false;
	else
		isOnTopOfTile = true;

	this->pos.y += 16;


	doStateChange(&StateID_Walk); 

	this->onExecute();
	return true;
}

int daSpikyHax_c::onDelete() {
	return true;
}

int daSpikyHax_c::onExecute() {
	acState.execute();
	updateModelMatrices();

	bodyModel._vf1C();

	this->rot.z += (this->settings == 1) ? 2000 : -2000;
	
	PlaySound(this, SE_PLY_WALK_METAL);

	return true;
}

int daSpikyHax_c::onDraw() {
	bodyModel.scheduleForDrawing();

	return true;
}

void daSpikyHax_c::updateModelMatrices() {
	matrix.translation(pos.x, pos.y - 2.0, pos.z);
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);

	bodyModel.setDrawMatrix(matrix);
	bodyModel.setScale(&scale);
	bodyModel.calcWorld(false);
}


///////////////
// Out State
///////////////
	void daSpikyHax_c::beginState_Out() {
	}
	void daSpikyHax_c::executeState_Out() {	
		this->speed.x = 0.0;
		this->speed.y = 0.0;
		this->max_speed.x = 0.0;
		this->max_speed.y = 0.0;
	}
	void daSpikyHax_c::endState_Out() { }


///////////////
// Walk State
///////////////
	void daSpikyHax_c::beginState_Walk() {
		this->max_speed.x = (this->direction) ? -this->XSpeed : this->XSpeed;
		this->speed.x = (this->direction) ? -3.0 : 3.0;
		this->x_speed_inc = (this->direction) ? 0.6 : -0.6;

		this->max_speed.y = -4;
		this->speed.y = 6.0;
		this->y_speed_inc = -0.5;
	}
	void daSpikyHax_c::executeState_Walk() {
		bool ret = calculateTileCollisions();
		if (ret) {
			doStateChange(&StateID_Die);
		}
	}
	void daSpikyHax_c::endState_Walk() { }


///////////////
// Turn State
///////////////
	void daSpikyHax_c::beginState_Turn() {
		this->direction ^= 1;
		this->speed.x *= -1;
	}
	void daSpikyHax_c::executeState_Turn() {
		this->doStateChange(&StateID_Walk);
	}
	void daSpikyHax_c::endState_Turn() { }


///////////////
// Die State
///////////////
	void daSpikyHax_c::beginState_Die() {
		this->removeMyActivePhysics();
	}
	void daSpikyHax_c::executeState_Die() { 
		PlaySound(this, SE_OBJ_WOOD_BOX_BREAK);
		Vec2 nyeh = {this->pos.x, this->pos.y};
		this->spawnHitEffectAtPosition(nyeh);
		this->Delete(this->deleteForever);
	}
	void daSpikyHax_c::endState_Die() { }




/*****************************************************/
/**************Gabon Rock replacing shit**************/
/*Don't ask me how does it work, because i don't know*/
/*****************************************************/

extern "C" float pow(float num, float power);

int getNybbleValuee(u32 settings, int fromNybble, int toNybble) {
	int numberOfNybble = (toNybble  - fromNybble) + 1;               //gets how many nybbles are used for the process (example: nybbles 4-6 -> there's nybbles 4, 5 and 6 used -> numberOfNybble = 3) 
	int valueToUse = 48 - (4 * toNybble);                            //gets the value to use with the bitshift at the end 
	int fShit = pow(16, numberOfNybble) - 1;                         //gets the value to use with the "&" operator at the end 
	OSReport("-> (settings >> %d) & 0x%x) => ", valueToUse, fShit);  //debugging
	return ((settings >> valueToUse) & fShit);                       //uses everything to make the nybble value 
}


class daGabonRock_c : dEn_c { //The daGabonRock_c class, very important.
	public:
		int onCreate_orig();
		int getsettings();
};

int daGabonRock_c::getsettings() {
	int orig_val = this->onCreate_orig();
	OSReport("--------\nSpawning daGabonRock_c:\n");
	OSReport("this->settings: nybble 5  -> %d\n", getNybbleValuee(this->settings, 5, 5));
	OSReport("this->settings: nybble 6  -> %d\n", getNybbleValuee(this->settings, 6, 6));
	OSReport("this->settings: nybble 7  -> %d\n", getNybbleValuee(this->settings, 7, 7));
	OSReport("this->settings: nybble 8  -> %d\n", getNybbleValuee(this->settings, 8, 8));
	OSReport("this->settings: nybble 9  -> %d\n", getNybbleValuee(this->settings, 9, 9));
	OSReport("this->settings: nybble 10 -> %d\n", getNybbleValuee(this->settings, 10, 10));
	OSReport("this->settings: nybble 11 -> %d\n", getNybbleValuee(this->settings, 11, 11));
	OSReport("this->settings: nybble 12 -> %d\n", getNybbleValuee(this->settings, 12, 12));
	OSReport("this->pos.x: %d\n", this->pos.x);
	OSReport("this->pos.y: %d\n", this->pos.y);
	OSReport("this->pos.z: %d\n", this->pos.z);
	OSReport("this->scale.x: %d\n", this->scale.x);
	OSReport("this->scale.y: %d\n", this->scale.y);
	OSReport("this->scale.z: %d\n", this->scale.z);
	OSReport("this->direction: %d\n", this->direction);
	if(this->settings > 1) {
		int playerID = this->settings - 2;
		dAcPy_c *player = dAcPy_c::findByID(playerID);
		int xofugnuzoqx = 0x22B;
		int *count = (int *)Actor_SearchByID(0x22B);
		OSReport("Count: %d\n", count);
		OSReport("player ID: %d\n", playerID);
		OSReport("player direction: %d\n", player->direction); //1 -> facing left | 0 -> facing right
		PlaySound(player, SE_EMY_GABON_ROCK_THROW);
		CreateActor(555, player->direction, player->pos, 0, 0);
		doWait = 120;
	}
	OSReport("--------\n");
	return orig_val;
}

int dGameDisplay_c::doWaitCheck() {
	int orig_val = this->onExecute_orig();
	if(doWait > 0) {
		doWait--;
	}
	return orig_val;
}