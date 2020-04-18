class TimeKeeper {
	public:
		u32 *vtable;
		u32 timePlusFFFTimes40000;
		u16 time;
		u8 ambushMaybe;
		u8 timeLessThan100;
		u8 paused;
		
		static TimeKeeper* instance;
		void setTime(int time);
};

class dGameDisplay_c : dBase_c { //The dGameDisplay_c class, very important.
    public:
        m2d::EmbedLayout_c layout;
        mEf::es2 effect;
        u32 _330;
        u32 _334;
        u32 _338;
        u32 _33C;
        u32 _340;
        u32 _344;
        u32 _348;
        u32 _34C;
        u32 _350;
        u32 _354;
        u32 _358;
        u32 _35C;
        u32 _360;
        u32 _364;
        u32 _368;
        u32 _36C;
        u32 _370;
        u32 _374;
        u32 _378;
        u32 _37C;
        u32 _380;
        u32 _384;
        u32 _388;
        u32 _38C;
        u32 _390;
        u32 _394;
        u32 _398;
        u32 _39C;
        u32 _3A0;
        u32 _3A4;
        dStateMgr_c state;
        u32 _3CC;
        u32 _3D0;
        u32 _3D4;
        u32 _3D8;
        u32 coins;
        u32 timer;
        u32 _3E4;
        u32 score;
        u32 _3EC;
        u32 _3F0;
        u32 _3F4;
        u32 _3F8;
        u32 _3FC;
        u32 _400;
        u32 _404;
        u32 _408;
        u32 _40C;
        u32 _410;
        u32 _414;
        u32 _418;
        u32 _41C;
        u32 _420;
        u32 _424;
        u32 _428;
        u32 _42C;
        u32 _430;
        u32 mustAtLeast2ForScoreToCount;
        u32 _438;
        u32 _43C;
        u32 _440;
        u32 _444;
        u8 _448;
        u8 _449;
        u8 _44A;
        u8 _44B;
        u32 _44C;
        u8 _450;
        u8 _451;
        u8 _452;
        u8 _453;
        u8 _454;
        u8 _455;
        u8 _456;
        u8 _457;
        u32 _458;
        u32 _45C;
        u32 _460;
        u32 _464;
        u32 _468;
        u32 _46C;
        u32 _470;
        u32 _474;
        u32 _478;
        u32 _47C;
        u32 _480;
        u32 _484;
        u32 _488;
        u32 _48C;
        u32 _490;
        nw4r::lyt::Picture* p_collectOff_00;
        nw4r::lyt::Picture* p_collection_00;
        nw4r::lyt::Picture* p_collectOff_01;
        nw4r::lyt::Picture* p_collection_01;
        nw4r::lyt::Picture* p_collectOff_02;
        nw4r::lyt::Picture* p_collection_02;
        nw4r::lyt::Picture* p_marioIcon_00;
        nw4r::lyt::Picture* p_luijiIcon_00;
        nw4r::lyt::Picture* p_kinoB_00;
        nw4r::lyt::Picture* p_kinoY_00;
        u32 _4BC;
        u32 _4C0;
        u32 _4C4;
        u32 _4C8;
        u32 _4CC;
        u32 _4D0;
        u32 _4D4;
        u32 _4D8;
        nw4r::lyt::TextBox* coinBox;
        nw4r::lyt::TextBox* timerBox;
        nw4r::lyt::TextBox* scoreBox;
        u32 _4E8;
        u32 _4EC;
        u32 _4F0;
        u32 _4F4;
        u8  _4F8;
        void* StarCoin1;
        void* StarCoin2;
        void* StarCoin3;
        u8  _505;
        u8  _506;
        u8  _507;
        u8 blob1[0x51C - 0x508];
        u32 _51C;
        u8 blob2[0x5A0 - 0x508];
        u32 _5A0;
       
        static dGameDisplay_c* instance;
        int onCreate_orig();
        int onExecute_orig();
        int patch_fix();
        int doWaitCheck();
        void doHexCoin();
};

class Zone {
    public:
        u16 x;
        u16 y;
        u16 w;
        u16 h;
        u16 objShad;
        u16 terShad;
        u8 id;
        u8 bnd_id;
        u8 scroll;
        u8 zoom;
        u8 field_10;
        u8 light;
        u8 fg_id;
        u8 bg_id;
        u8 mp_bias;
        u8 field_15;
        u8 music;
        u8 audio;
};

class dCourseFull_c; // forward declaration

class dCourse_c {
    public:
        u32 vtable;
        u32 areanum;
        u32 blkTilesets;
        u32 blkSettings;
        u32 blkBoundings;
        u32 blkUnk1;
        u32 blkBg1;
        u32 blkBg2;
        u32 blkEntrance;
        u32 blkSprites;
        u32 blkSpriteLoad;
        u32 blkZones;
        u32 blkLocations;
        u32 blkUnk2;
        u32 blkPaths;
        u32 blkPathNodes;
        u32 bsTilesets;
        u32 bsSettings;
        u32 bsBoundings;
        u32 bsUnk1;
        u32 bsBg1;
        u32 bsBg2;
        u32 bsEntrance;
        u32 bsSprites;
        u32 bsSpriteLoad;
        u32 bsZones;
        u32 bsLocations;
        u32 bsUnk2;
        u32 bsPaths;
        u32 bsPathNodes;
        u32 bcTilesets;
        u32 bcSettings;
        u32 bcBoundings;
        u32 bcUnk1;
        u32 bcBg1;
        u32 bcBg2;
        u32 bcEntrance;
        u32 bcSprites;
        u32 bcSpriteLoad;
        u32 bcZones;
        u32 bcLocations;
        u32 bcUnk2;
        u32 bcPaths;
        u32 bcPathNodes;
        u32 zoneFirstSprite[64];
        u32 zoneSpriteCount[64];
        u32 zoneFirstSpriteIdx[64];

        Zone getZoneByID(/*dCourseFull_c *instance*/ int yes, u8 dScStage_ccurZone, int unk); //8008E410
        int getMusicForZone(int zoneID); //8008E5C0
};

class dCourseFull_c {
    public:
        dCourse_c *areas[4];

        static dCourseFull_c* instance; //8042A178
};

class Stage32C {
    public:
        u32 bulletData1[32];
        u32 bulletData2[32];
        u32 enemyCombos[4];
        u32 somethingAboutHatenaBalloons;
        u32 redCoinCount[4];
        u32 field_124;
        u32 field_128;
        u32 field_12C;
        u32 field_130;
        u32 greenCoinsCollected;
        u32 hasKilledEnemyThisTick_maybe;
        u16 booID;
        u8 _13E;
        u8 _13F;
        u32 bigBooID;
        u32 homingBanzaiID;
        u16 bulletBillCount;
        u8 _14A;
        u8 _14B;
        u32 bombCount;
        u32 goombaCount;
        u32 enemyKillCounter_maybe;
        u32 a_counter;
        u32 setToOneByBossDemoOrSomething;
        u32 aboutMortonBigPile;
        u32 somethingAboutPunchingChainlinkFence;
        u32 currentBigHanaMgr;
        u8 _16C;
        u8 _16D;
        u8 _16E;
        u8 _16F;
        u8 penguinCount;
        u8 _171;
        u8 _172;
        u8 _173;
        u32 pokeyTimer;
};

class MicroGoombaManager {
    public:
        u32 storedActorIDs[100];
        u8 storedGroupIDs[100];
        u8 generatedNumberFlag[4];
        u16 generatedNumbers[4];
};

class dEffectExplosionMgr_c {
    public:
        u16 field_0;
};

class dTimerMgr_c {
    public:
        u16 field_0;
};

class dBlockMgr_c {
    public:
        u32 areDonutLiftsDisabled;
};

class StageF70 {
    public:
        u16 field_0;
};

class StageF74Sub {
    public:
        u16 field_0;
        u8 _2;
        u8 _3;
        float field_4;
        float field_8;
        float field_C;
        float field_10;
        float field_14;
        float field_18;
        float field_1C;
        float field_20;
};

class StageF74 {
    public:
        StageF74Sub field_0[16];
};

class dScStage_c : public dScene_c {
    public:
        u32 runningFrameCount_probably;
        FunctionChain chain;
        Stage80 field_80;
        StageC4 field_C4;
        StageE4 field_E4;
        Stage32C field_32C; //bleh
        MicroGoombaManager microGoombaManager; //bleh
        dWaterManager_c waterManager;
        dEffectExplosionMgr_c effectExplosionManager; //bleh
        dTimerMgr_c timerMgr; //bleh
        dBlockMgr_c blockMgr; //bleh
        StageF70 field_F70; //bleh
        StageF74 field_F74; //bleh
        u8 _11B4;
        u8 _11B5;
        u8 _11B6;
        u8 _11B7;
        u8 _11B8;
        u8 _11B9;
        u8 _11BA;
        u8 _11BB;
        u8 _11BC;
        u8 _11BD;
        u8 _11BE;
        u8 _11BF;
        u8 _11C0;
        u8 _11C1;
        u8 _11C2;
        u8 _11C3;
        u8 _11C4;
        u8 _11C5;
        u8 _11C6;
        u8 _11C7;
        u8 _11C8;
        u8 _11C9;
        u8 _11CA;
        u8 _11CB;
        u8 _11CC;
        u8 _11CD;
        u8 _11CE;
        u8 _11CF;
        u8 _11D0;
        u8 _11D1;
        u8 _11D2;
        u8 _11D3;
        u32 ptrToGameDisplay;
        u32 ptrToGoalManager;
        u32 ptrToSmallScoreManager;
        u32 ptrToFukidashiManager;
        u32 ptrToCourseTimeUp;
        u32 ptrToMiniGameCannon;
        u32 ptrToMiniGameWire;
        u32 ptrToModelPlayManager;
        u32 ptrToMessageWindow;
        u32 ptrToModelPlayGuide;
        u32 ptrToStaffCreditScore;
        u32 ptrToTheEnd;
        u32 ptrToYesNoWindow;
        u8 _1208;
        u8 _1209;
        u8 _120A;
        u8 _120B;
        u8 curWorld;
        u8 curLevel;
        u8 curArea;
        u8 curZone;
        u8 curLayer;
        u8 curEntrance;
        u8 field_1212;
        u8 field_1213;
        u32 uselessPTMFIndex;

        int onExecute_orig(); //80925A60
        int newOnExecute();
};