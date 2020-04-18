#include <game.h>
#include <stage.h>

extern u8 LastLevelPlayed[2];
extern "C" int CanExitThisLevel();

void restartLevel() {

	LastPowerupStoreType = LOSE_LEVEL;

	//OSReport("Got last level: %d-%d\n", LastLevelPlayed[0], LastLevelPlayed[1]);

	StartLevelInfo sl;
	sl.replayTypeMaybe = 0;
	sl.entrance = 0xFF;
	sl.areaMaybe = 0;
	sl.unk4 = 0;
	sl.purpose = 0;

	sl.world1 = LastLevelPlayed[0];
	sl.world2 = LastLevelPlayed[0];
	sl.level1 = LastLevelPlayed[1];
	sl.level2 = LastLevelPlayed[1];

	ActivateWipe(WIPE_BOWSER);

	DoStartLevel(GetGameMgr(), &sl);
}

void exitLevel() {
	int canI = CanExitThisLevel();
	if(canI) {
		ExitStage(WORLD_MAP, 0, EXIT_LEVEL, 5);
	}
	else {
		Player_Lives[0]--;
		if(Player_Active[1]) {
			Player_Lives[1]--;
		}
		if(Player_Active[2]) {
			Player_Lives[2]--;
		}
		if(Player_Active[3]) {
			Player_Lives[3]--;
		}
		ExitStage(WORLD_MAP, 0, LOSE_LEVEL, 5);
	}
}