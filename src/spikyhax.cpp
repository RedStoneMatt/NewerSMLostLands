#include <common.h>
#include <game.h>
#include <stage.h>
#include <g3dhax.h>
#include <sfx.h>
#include <timekeeper.h> //this doesn't contains only the TimeKeeper class, but also much shit. I should maybe have named it "junk.h"
#include "boss.h"

int doWait = 0; //global doWait variable to limit the spikeball throwing


class daSpikyHax_c : public dEn_c { //the class, to declare the things we'll use
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
	DECLARE_STATE(Walk);
	DECLARE_STATE(Die);
};

daSpikyHax_c *daSpikyHax_c::build() {
	void *buffer = AllocFromGameHeap1(sizeof(daSpikyHax_c));
	return new(buffer) daSpikyHax_c;
}

///////////////////////
// States
///////////////////////


	CREATE_STATE(daSpikyHax_c, Walk);
	CREATE_STATE(daSpikyHax_c, Die);


////////////////////////
// Collision Functions
////////////////////////


	void daSpikyHax_c::spriteCollision(ActivePhysics *apThis, ActivePhysics *apOther) {
		u16 name = ((dEn_c*)apOther->owner)->name;                                                                           //get the name of the actor the spikeball collided with

		if (name == EN_COIN || name == EN_EATCOIN || name == AC_BLOCK_COIN || name == EN_COIN_JUGEM || name == EN_COIN_ANGLE //list of actors ignored by the spikeball
			|| name == EN_COIN_JUMP || name == EN_COIN_FLOOR || name == EN_COIN_VOLT || name == EN_COIN_WIND
			|| name == EN_BLUE_COIN || name == EN_COIN_WATER || name == EN_REDCOIN || name == EN_GREENCOIN
			|| name == EN_JUMPDAI || name == EN_ITEM || name == EN_STAR_COIN)
			{ return; }


		dEn_c::spriteCollision(apThis, apOther);                                                                             //do as if it hit a sprite
		((dEn_c*)apOther->owner)->collisionCat13_Hammer(apThis, apOther);                                                    //do as if it was touched by a hammer
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
		return false;
	}

	bool daSpikyHax_c::collisionCat7_GroundPoundYoshi(ActivePhysics *apThis, ActivePhysics *apOther) {
		return false;
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
		return false;
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

	/****************************/
	/***Tile collision detector**/
	/*Returns true if hit a wall*/
	/****************************/


	HandleXSpeed();                                      //consider the X speed
	HandleYSpeed();                                      //consider the Y speed
	doSpriteMovement();                                  //execute the speed movements

	cmgr_returnValue = collMgr.isOnTopOfTile();          //check if the sprite is on top of a tile
	collMgr.calculateBelowCollisionWithSmokeEffect();    //duh

	stuffRelatingToCollisions(0.1875f, 1.0f, 0.5f);      //literally stuff related to collisions

	float xDelta = pos.x - last_pos.x;                   //just read dude

	if (xDelta >= 0.0f) {                                //change of direction if needed
		direction = 0;
	}
	else {
		direction = 1;
	}

	if (collMgr.isOnTopOfTile()) {                       //if the sprite is on top of a tile
		if(alreadyOnTop == 0) {                          //if it just landed
			PlaySound(this, SE_OBJ_ROCK_LAND);           //play SFX
			alreadyOnTop = 1;                            //now it's already on the to^p
		}

		if (cmgr_returnValue == 0)                       //just read ?
			isOnTopOfTile = true;

		speed.y = 0.0f;                                  //no Y speed anymore cuz it's on the ground
		max_speed.x = (direction == 1) ? -1.5f : 1.5f;   //maximum X speed re-setting
		this->x_speed_inc = 0.0f;                        //no X speed incrementation
		this->speed.x = (direction == 1) ? -1.5f : 1.5f; //X speed re-setting
	}
	else {                                               //if the sprite in in mid-air
		alreadyOnTop = 0;                                //it's no loner on the top of a tile
	}

	collMgr.calculateAdjacentCollision(0);               //literally calculate the adjacent collision

	if (collMgr.outputMaybe & (0x15 << direction)) {     //if hit a wall
		if (collMgr.isOnTopOfTile()) {                   //if on the top of a tile
			isOnTopOfTile = true;
		}
		return true;                                     //returns true duh
	}
	return false;                                        //if didn't hit a wall
}

int daSpikyHax_c::onCreate() {

	this->deleteForever = true;                                         //FOREVAAAAAAAAH

	/****************/
	/*Model Creation*/
	/****************/

	allocator.link(-1, GameHeaps[0], 0, 0x20);                          //allocator linking

	this->resFile.data = getResource("hammerM", "g3d/iron_ball.brres"); //get the brres in the arc file
	nw4r::g3d::ResMdl mdl = this->resFile.GetResMdl("iron_ball");       //get the mdl0
	bodyModel.setup(mdl, &allocator, 0x224, 1, 0);                      //setup it
	SetupTextures_MapObj(&bodyModel, 0);                                //setup shaders

	allocator.unlink();                                                 //allocator unlinking

	/****************/
	/*Values Setting*/
	/****************/

	this->scale = (Vec){0.7, 0.7, 0.7};                                 //scale setting

	this->rot.x = 0;                                                    //X rotation setting
	this->rot.y = 0;                                                    //Y rotation setting
	this->rot.z = 0;                                                    //Z rotation setting
	this->direction = this->settings;                                   //heading where the player look.
	
	this->speed.x = 0.0;                                                //X speed setting
	this->speed.y = 3.0;                                                //Y speed setting
	this->max_speed.x = 0.0;                                            //X maximum speed setting
	this->x_speed_inc = 0.0;                                            //X speed incrementation setting
	this->XSpeed = 3.0;                                                 //XSpeed value (used later) setting

	/********************/
	/*Collision Creating*/
	/********************/

	ActivePhysics::Info HitMeBaby;                                      //ActivePhysics::Info creating

	HitMeBaby.xDistToCenter = 0.0;                                      //no X distance to center duh
	HitMeBaby.yDistToCenter = 0.0;                                      //no Y distance to center duh

	HitMeBaby.xDistToEdge = 7.5;                                        //1 block wide
	HitMeBaby.yDistToEdge = 7.5;                                        //1 block high		

	HitMeBaby.category1 = 0x3;                                          //idk what is this, ask treeki
	HitMeBaby.category2 = 0x0;                                          //^
	HitMeBaby.bitfield1 = 0x6F;                                         //^
	HitMeBaby.bitfield2 = 0xffbafffe;                                   //^
	HitMeBaby.unkShort1C = 0;                                           //^
	HitMeBaby.callback = &dEn_c::collisionCallback;                     //collision callback

	this->aPhysics.initWithStruct(this, &HitMeBaby);                    //initating the collision
	this->aPhysics.addToList();                                         //add to the collision list

	/********************/
	/*Colliders Creating*/
	/********************/

	// These fucking rects do something for the tile rect
	spriteSomeRectX = 28.0f;
	spriteSomeRectY = 32.0f;
	_320 = 0.0f;
	_324 = 16.0f;

	static const lineSensor_s below(-5<<12, 5<<12, -9<<12);            //Below collider:    unk, unk, y pos 
	static const pointSensor_s above(0<<12, 12<<12);                   //Above collider:    unk, unk, unk
	static const lineSensor_s adjacent(3<<12, 6<<12, 6<<12);           //Adjacent collider: unk, unk, unk

	collMgr.init(this, &below, &above, &adjacent);                     //initating colliders
	collMgr.calculateBelowCollisionWithSmokeEffect();                  //dude, the description of this line IS in the line, so what are you reading ?

	cmgr_returnValue = collMgr.isOnTopOfTile();                        //get if the sprite is in top of a tile (GOD DAMMIT IT IS WROTE)

	if (collMgr.isOnTopOfTile())                                       //just... read !
		isOnTopOfTile = false;
	else
		isOnTopOfTile = true;

	this->pos.y += 16;                                                 //because the game


	doStateChange(&StateID_Walk);                                      //switch to the walk state (even if it's not really walking but shut up)

	this->onExecute();
	return true;
}

int daSpikyHax_c::onDelete() {
	return true;
}

int daSpikyHax_c::onExecute() {
	acState.execute();                                   //execute the states
	updateModelMatrices();                               //updates the model

	bodyModel._vf1C();                                   //Animations, iirc

	this->rot.z += (this->settings == 1) ? 2000 : -2000; //Rotating it depending of its spawning direction
	
	PlaySound(this, SE_PLY_WALK_METAL);                  //Play SFX

	return true;
}

int daSpikyHax_c::onDraw() {
	bodyModel.scheduleForDrawing();                      //shedule the model drawing

	return true;
}

void daSpikyHax_c::updateModelMatrices() {               //updates the model:
	matrix.translation(pos.x, pos.y - 2.0, pos.z);       //its position
	matrix.applyRotationYXZ(&rot.x, &rot.y, &rot.z);     //its rotation

	bodyModel.setDrawMatrix(matrix);                     //its draw matrix
	bodyModel.setScale(&scale);                          //its scale
	bodyModel.calcWorld(false);                          //what's that duh
}


///////////////
// Walk State
///////////////
	void daSpikyHax_c::beginState_Walk() {
		this->max_speed.x = (this->direction) ? -this->XSpeed : this->XSpeed; //set the maximum X speed depending of the spawning direction
		this->speed.x = (this->direction) ? -3.0 : 3.0;                       //set the current X speed depending of the spawning direction
		this->x_speed_inc = (this->direction) ? 0.6 : -0.6;                   //set the X speed increment depending of the spawning direction

		this->max_speed.y = -4;                                               //set the maximum Y speed
		this->speed.y = 6.0;                                                  //set the current Y speed
		this->y_speed_inc = -0.5;                                             //set the Y speed increment
	}
	void daSpikyHax_c::executeState_Walk() {
		bool ret = calculateTileCollisions();                                 //calculate the tiles collision
		if (ret) {
			doStateChange(&StateID_Die);                                      //if hit a wall, die
		}
	}
	void daSpikyHax_c::endState_Walk() { }


///////////////
// Die State
///////////////
	void daSpikyHax_c::beginState_Die() {
		this->removeMyActivePhysics();           //Remove the collision
	}
	void daSpikyHax_c::executeState_Die() { 
		PlaySound(this, SE_OBJ_WOOD_BOX_BREAK);  //Play SFX
		Vec2 nyeh = {this->pos.x, this->pos.y};  //Get the current position as a Vec2
		this->spawnHitEffectAtPosition(nyeh);    //Spawn Hit Effect at this position (duh)
		doWait = 0;                              //doWait is now 0
		this->Delete(this->deleteForever);       //DELETE FOREVAAAAAAAH
	}
	void daSpikyHax_c::endState_Die() { }



/***********************************************************************************/
/**ALL THE STUFF BELOW IS TESTS, DEBUG MODE AND MOSTLY UNRELATED TO THE SPIKE SUIT**/
/*************BUT I HAD TO PUT IT HERE CUZ LAZYNESS AND GLOBAL VARIABLES************/
/***********************************************************************************/


/***************************/
/**Nybble getting function**/
/***************************/

extern "C" float pow(float num, float power);

int getNybbleValuee(u32 settings, int fromNybble, int toNybble, bool doOSReport) {
	int numberOfNybble = (toNybble  - fromNybble) + 1;               //gets how many nybbles are used for the process (example: nybbles 4-6 -> there's nybbles 4, 5 and 6 used -> numberOfNybble = 3) 
	int valueToUse = 48 - (4 * toNybble);                            //gets the value to use with the bitshift at the end 
	int fShit = pow(16, numberOfNybble) - 1;                         //gets the value to use with the "&" operator at the end 
	if(doOSReport) {
		OSReport("-> (settings >> %d) & 0x%x) => ", valueToUse, fShit);  //debugging
	}
	return ((settings >> valueToUse) & fShit);                       //uses everything to make the nybble value 
}

/******************************************************/
/**The daGabonRock_c class so we can make edits to it**/
/******************************************************/

class daGabonRock_c : dEn_c {
	public:
		int onCreate_orig();
		int getsettings();
};

/******************************************************************/
/**OSReporting the gabon's rock settings for spike suit debugging**/
/******************************************************************/

int daGabonRock_c::getsettings() {
	int orig_val = this->onCreate_orig();
	OSReport("--------\nSpawning daGabonRock_c:\n");
	OSReport("this->settings: nybble 5  -> %d\n", getNybbleValuee(this->settings, 5, 5, true));
	OSReport("this->settings: nybble 6  -> %d\n", getNybbleValuee(this->settings, 6, 6, true));
	OSReport("this->settings: nybble 7  -> %d\n", getNybbleValuee(this->settings, 7, 7, true));
	OSReport("this->settings: nybble 8  -> %d\n", getNybbleValuee(this->settings, 8, 8, true));
	OSReport("this->settings: nybble 9  -> %d\n", getNybbleValuee(this->settings, 9, 9, true));
	OSReport("this->settings: nybble 10 -> %d\n", getNybbleValuee(this->settings, 10, 10, true));
	OSReport("this->settings: nybble 11 -> %d\n", getNybbleValuee(this->settings, 11, 11, true));
	OSReport("this->settings: nybble 12 -> %d\n", getNybbleValuee(this->settings, 12, 12, true));
	OSReport("this->pos.x: %d\n", this->pos.x);
	OSReport("this->pos.y: %d\n", this->pos.y);
	OSReport("this->pos.z: %d\n", this->pos.z);
	OSReport("this->scale.x: %d\n", this->scale.x);
	OSReport("this->scale.y: %d\n", this->scale.y);
	OSReport("this->scale.z: %d\n", this->scale.z);
	OSReport("this->direction: %d\n", this->direction);
	if(getNybbleValuee(this->settings, 12, 12, false) > 1) {
		int playerID = getNybbleValuee(this->settings, 6, 6, false);
		dAcPy_c *player = dAcPy_c::findByID(playerID);
		OSReport("player ID: %d\n", playerID);
		OSReport("player direction: %d\n", player->direction); //1 -> facing left | 0 -> facing right
		PlaySound(player, SE_EMY_GABON_ROCK_THROW);
		CreateActor(555, player->direction, player->pos, 0, 0);
		doWait = 60;
	}
	OSReport("--------\n");
	return orig_val;
}

/***************************************************************************/
/**Global variables declaring, which is why i put all of this in this file**/
/***************************************************************************/

extern bool enableDebugMode;
extern bool enableCollisionMode;
extern "C" void *dAcPy_c__ChangePowerupWithAnimation(void * Player, int powerup); 	// Powerups - 0 = small; 1 = big; 2 = fire; 3 = mini; 4 = prop; 5 = peng; 6 = ice; 7 = hammer
extern "C" int CheckExistingPowerup(void * Player);
int minuscounter;
bool stopCamera;
int doOneTimeCam;
VEC3 initialcamPos;
bool disableOrNot;
bool isLuigiActive;
bool isKinoBActive;
bool isKinoYActive;
int pActivityDoOneTime;

/********************************************************************/
/**gameScene's onExecute adds for the spike suit and the debug mode**/
/********************************************************************/

int dGameDisplay_c::doWaitCheck() {
	int orig_val = this->onExecute_orig();
	int nowPressed = Remocon_GetPressed(GetActiveRemocon());
	if(enableDebugMode) {
		dAcPy_c *player = dAcPy_c::findByID(0);
		if ((GetActiveRemocon()->heldButtons == 0x402) && (nowPressed & 0x402)) { // B + UP // Changes the player's powerup
			int playerPowerup = ((CheckExistingPowerup(player) == 7) ? 0 : (CheckExistingPowerup(player) + 1));          //increment the player's powerup id by 1. If 7 -> 0
			dAcPy_c__ChangePowerupWithAnimation(player, playerPowerup);                                                  //change it
		}
		if ((GetActiveRemocon()->heldButtons == 0x401) && (nowPressed & 0x401)) { // B + DOWN // Beats the current level
			ExitStage(WORLD_MAP, 0, BEAT_LEVEL, MARIO_WIPE);                                                             //exit the current stage and beat it
		}
		if ((GetActiveRemocon()->heldButtons == 0x408) && (nowPressed & 0x408)) { // B + LEFT // Turn On/Off the collision viewer
			enableCollisionMode = !enableCollisionMode;                                                                  //enable or disable to collision debugger
		}
		if ((GetActiveRemocon()->heldButtons == 0x404) && (nowPressed & 0x404)) { // B + RIGHT // Spawns a Star
			int enitemsettings = 0 | (1 << 0) | (2 << 18) | (4 << 9) | (2 << 10) | (8 << 16);                            //setting the settings
			dStageActor_c *Star = dStageActor_c::create(EN_ITEM, enitemsettings, &player->pos, 0, 0);                    //creates the Star
		}
		if ((GetActiveRemocon()->heldButtons == 0x500) && (nowPressed & 0x500)) { // B + TWO // Numpad to spawn an actor by ID // Points ID - 1 = 200; 2 = 400; 3 = 800; 4 = 1000; 5 = 2000; 6 = 4000; 7 = 8000; 8 = 1UP
			CreateActor(490, 0, player->pos, 0, 0);                                                                      //Numpad spawning
		}	
		if ((GetActiveRemocon()->heldButtons == 0x600) && (nowPressed & 0x600)) { // B + ONE // Makes the gameScene disappear/appear
			disableOrNot = !disableOrNot;                                                                                //disable or enable switching
			nw4r::lyt::Picture *_poisonusbar = dGameDisplay_c::instance->layout.findPictureByName("P_PoisonBar_00");     //getting the panes, too lazy to name them all
			nw4r::lyt::Picture *_poisonusjauge = dGameDisplay_c::instance->layout.findPictureByName("P_PoisonJauge_00");
			nw4r::lyt::Picture *_1 = dGameDisplay_c::instance->layout.findPictureByName("P_baseS_01");
			nw4r::lyt::Picture *_2 = dGameDisplay_c::instance->layout.findPictureByName("P_base_01");
			nw4r::lyt::Picture *_3 = dGameDisplay_c::instance->layout.findPictureByName("P_otasukeIcon_00");
			nw4r::lyt::Picture *_4 = dGameDisplay_c::instance->layout.findPictureByName("P_marioIcon_00");
			nw4r::lyt::Picture *_5 = dGameDisplay_c::instance->layout.findPictureByName("P_luijiIcon_00");
			nw4r::lyt::Picture *_6 = dGameDisplay_c::instance->layout.findPictureByName("P_kinoB_00");
			nw4r::lyt::Picture *_7 = dGameDisplay_c::instance->layout.findPictureByName("P_kinoY_00");
			nw4r::lyt::Picture *_31 = dGameDisplay_c::instance->layout.findPictureByName("P_baseS_00");
			nw4r::lyt::Picture *_8 = dGameDisplay_c::instance->layout.findPictureByName("P_base_00");
			nw4r::lyt::Picture *_9 = dGameDisplay_c::instance->layout.findPictureByName("P_coin_00");
			nw4r::lyt::Picture *_10 = dGameDisplay_c::instance->layout.findPictureByName("P_collectOff_00");
			nw4r::lyt::Picture *_11 = dGameDisplay_c::instance->layout.findPictureByName("P_collectOff_01");
			nw4r::lyt::Picture *_12 = dGameDisplay_c::instance->layout.findPictureByName("P_collectOff_02");
			nw4r::lyt::Picture *_13 = dGameDisplay_c::instance->layout.findPictureByName("P_collection_00");
			nw4r::lyt::Picture *_14 = dGameDisplay_c::instance->layout.findPictureByName("P_collection_01");
			nw4r::lyt::Picture *_15 = dGameDisplay_c::instance->layout.findPictureByName("P_collection_02");
			nw4r::lyt::Picture *_16 = dGameDisplay_c::instance->layout.findPictureByName("P_timer_00");
			nw4r::lyt::TextBox *_17 = dGameDisplay_c::instance->layout.findTextBoxByName("T_debug_00");
			nw4r::lyt::TextBox *_18 = dGameDisplay_c::instance->layout.findTextBoxByName("T_otaChuS_00");
			nw4r::lyt::TextBox *_19 = dGameDisplay_c::instance->layout.findTextBoxByName("T_otaChu_00");
			nw4r::lyt::TextBox *_20 = dGameDisplay_c::instance->layout.findTextBoxByName("T_x_01");
			nw4r::lyt::TextBox *_21 = dGameDisplay_c::instance->layout.findTextBoxByName("T_x_02");
			nw4r::lyt::TextBox *_22 = dGameDisplay_c::instance->layout.findTextBoxByName("T_x_03");
			nw4r::lyt::TextBox *_23 = dGameDisplay_c::instance->layout.findTextBoxByName("T_x_04");
			nw4r::lyt::TextBox *_24 = dGameDisplay_c::instance->layout.findTextBoxByName("T_left_00");
			nw4r::lyt::TextBox *_25 = dGameDisplay_c::instance->layout.findTextBoxByName("T_left_01");
			nw4r::lyt::TextBox *_26 = dGameDisplay_c::instance->layout.findTextBoxByName("T_left_02");
			nw4r::lyt::TextBox *_27 = dGameDisplay_c::instance->layout.findTextBoxByName("T_left_03");
			nw4r::lyt::TextBox *_28 = dGameDisplay_c::instance->layout.findTextBoxByName("T_coin_00");
			nw4r::lyt::TextBox *_29 = dGameDisplay_c::instance->layout.findTextBoxByName("T_score_00");
			nw4r::lyt::TextBox *_30 = dGameDisplay_c::instance->layout.findTextBoxByName("T_time_00");
			int visibility = !disableOrNot;                                                                              //store the visibility bool

			if(pActivityDoOneTime == 0) {                                                                                //get which players are active only a single time
				if(_5->flag == 1) {                                                                                      //if luigi's pane is visible, luigi is active
					isLuigiActive = true;
				}
				if(_6->flag == 1) {                                                                                      //if kinob's pane is visible, kinob is active
					isKinoBActive = true;
				}
				if(_7->flag == 1) {                                                                                      //if kinoy's pane is visible, kinoy is active
					isKinoYActive = true;
				}
				pActivityDoOneTime = 1;                                                                                  //don't redo that process next time, cuz useless
			}

			_poisonusbar->SetVisible(visibility);                                                                        //set the panes visibilities
			_poisonusjauge->SetVisible(visibility);
			_1->SetVisible(visibility);
			_2->SetVisible(visibility);
			_3->SetVisible(visibility);
			_4->SetVisible(visibility);

			if(isLuigiActive) {                                                                                          //if luigi is active, affect his panes
				_5->SetVisible(visibility);
				_21->SetVisible(visibility);
				_25->SetVisible(visibility);
			}
			
			if(isKinoBActive) {                                                                                          //if kinob is active, affect his panes
				_6->SetVisible(visibility);
				_22->SetVisible(visibility);
				_26->SetVisible(visibility);
			}
			
			if(isKinoYActive) {                                                                                          //if kinoy is active, affect his panes
				_7->SetVisible(visibility);
				_23->SetVisible(visibility);
				_27->SetVisible(visibility);
			}

			_8->SetVisible(visibility);
			_9->SetVisible(visibility);
			_10->SetVisible(visibility);
			_11->SetVisible(visibility);
			_12->SetVisible(visibility);
			_13->SetVisible(visibility);
			_14->SetVisible(visibility);
			_15->SetVisible(visibility);
			_16->SetVisible(visibility);
			_17->SetVisible(visibility);
			_18->SetVisible(visibility);
			_19->SetVisible(visibility);
			_20->SetVisible(visibility);
			_24->SetVisible(visibility);
			_28->SetVisible(visibility);
			_29->SetVisible(visibility);
			_30->SetVisible(visibility);
			_31->SetVisible(visibility);
		}		
	}
	if(nowPressed & WPAD_MINUS) {                                                                                        //minus pressing counter
		minuscounter++;                                                                                                  //increment it by one every press
		if(minuscounter >= 16) {                                                                                         //if pressed 16 times
			minuscounter = 0;                                                                                            //set it back to 0
			enableDebugMode = !enableDebugMode;                                                                          //enable/disable the debug mode
			nw4r::lyt::TextBox *debugText = dGameDisplay_c::instance->layout.findTextBoxByName("T_debug_00");            //get the debugging textbox
			debugText->SetString(((enableDebugMode) ? L"Debug Mode" : L" "));                                            //make it visible or not
			this->doHexCoin();                                                                                           //refresh the coin counter
		}
	}
	if(doWait > 0) {                                                                                                     //spikeball waiting variable: if >0
		doWait--;                                                                                                        //decrement it by one
	}
	return orig_val;
}

/****************************/
/**Hexadecimal coin counter**/
/****************************/

void dGameDisplay_c::doHexCoin() { //Make the coin counter display in hexadecimal if the debug mode is enabled
	nw4r::lyt::TextBox *stupidcoin = dGameDisplay_c::instance->layout.findTextBoxByName("T_coin_00");                    //get the coin textbox
	char str[3];                                                                                                         //make a char that will contain the text to display
	sprintf(str, ((enableDebugMode) ? "%03X" : "%03d"), dGameDisplay_c::instance->coins);                                //insert the number in the char win three characters
	wchar_t nyeh[3];                                                                                                     //make a wchar_t
	nyeh[0] = str[0];                                                                                                    //put the char's content in the wchar_t
	nyeh[1] = str[1];
	nyeh[2] = str[2];
	stupidcoin->SetString(nyeh, 0, 3);                                                                                   //write it to the textbox
}

/*************************/
/**Camera freezing tests**/
/*************************/

int dCamera_c::newOnExecute() { //freezing camera failed tests
	if(stopCamera) {
		return false;
	}
	int orig_val = this->onExecute_orig();
	return orig_val;
}

int dCamera_c::newOnDraw() { //freezing camera failed tests
	if(stopCamera) {                                                                                                  
		return false;
	}
	int orig_val = this->onDraw_orig();
	return orig_val;
}

/**************************************/
/**Sound switching, because i'm bored**/
/**************************************/

static nw4r::snd::StrmSoundHandle s_handle;                                                                                           //sound handling storing
extern "C" void PlaySoundWithFunctionB4(void *spc, nw4r::snd::SoundHandle *handle, int id, int unk);                                  //play sound function
u8 hijackMusicWithSongName(const char *songName, int themeID, bool hasFast, int channelCount, int trackCount, int *wantRealStreamID); //hijacking
bool isElevatorMusic;                                                                                                                 //obviously obvious boolean

int dScStage_c::newOnExecute() { //Why do I put that here ? because yes.
	int orig_val = this->onExecute_orig();
	if(enableDebugMode) {                                                                                                //if the debug mode is enabled
		int nowPressed = Remocon_GetPressed(GetActiveRemocon());                                                         //get pressed buttons
		if ((GetActiveRemocon()->heldButtons == 0xC00) && (nowPressed & 0xC00)) { // B + A // Do music change
			OSReport("isElevatorMusic = %d\n", isElevatorMusic);                                                         //OSReporting it cuz i'm a cute matt that needs to know his work works
			if(isElevatorMusic == false) {                                                                               //if need to switch to the elevator music
				StopBGMMusic();                                                                                          //stop current music
				OSReport("switching music\n");
				if (s_handle.Exists()) {                                                                                 //if the track is already playing cuz reasons, set its volume to 0
					s_handle.SetTrackVolume(1<<1, 30, 0.0f);
				}

				int realStreamID;                                                                                        //real steam id cuz reasons
				// int musicid = 0;
				char brstmName[8];
				sprintf(brstmName, "ELEVATOR");                                                                          //store the music filename in brstmName
				hijackMusicWithSongName(brstmName, -1, false, 2, 1, &realStreamID);                                      //hijack it

				PlaySoundWithFunctionB4(SoundRelatedClass, &s_handle, realStreamID, 1);                                  //play it
				isElevatorMusic = true;                                                                                  //yes we are playing it
			}
			else {                                                                                                       //if need to switch back to the original music
				s_handle.Stop(1);                                                                                        //stop the elevator music
				StartBGMMusic();                                                                                         //restart the original music
				isElevatorMusic = false;                                                                                 //no we aren't playing it
			}
		}
	}
	return orig_val;
}

/******************************************************************/
/**Okay so these are tests with bro's projectiles, for researches**/
/******************************************************************/

/*
class Projectile : dEn_c {
	public:
		int onCreate_orig();
		int getsettings();
};


int Projectile::getsettings() {
	int orig_val = this->onCreate_orig();
	OSReport("--------\nSpawning Projectile:\n");
	OSReport("this->settings: %d\n", this->settings);
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
	OSReport("--------\n");
	return orig_val;
}
*/