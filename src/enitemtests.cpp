#include <game.h>
#include <newer.h>
#include <sfx.h>

class daEnItem_c : dEn_c { //The daEnItem_c class, very important.
	public:
		int onCreate_orig();
		int getsettings();
};

int daEnItem_c::getsettings() {
	int orig_val = this->onCreate_orig();
	OSReport("--------\nSpawning EN_ITEM:\n");
	OSReport("Powerup Type: %d\n", (this->settings >> 0 & 0xF)); //depends
	OSReport("0xDCE: %d\n", (this->settings >> 5 & 0xF));
	OSReport("StateID_DropMove: %d\n", (this->settings >> 7 & 0xF));
	OSReport("0xD9C: %d\n", (this->settings >> 9 & 0xF)); //4
	OSReport("StateID_MeterDropMove: %d\n", (this->settings >> 10 & 0xF)); //2
	OSReport("Z-Order Switch: %d\n", (this->settings >> 11 & 0xF)); //1
	OSReport("0xD68: %d\n", (this->settings >> 12 & 0xF));
	OSReport("0xDB0: %d\n", (this->settings >> 13 & 0xF));
	OSReport("0xDA0: %d\n", (this->settings >> 14 & 0xF));
	OSReport("Player ID: %d\n", (this->settings >> 16 & 0xF)); //8 or 12
	OSReport("0xD98: %d\n", (this->settings >> 18 & 0xF)); //2 or 3
	OSReport("0xDA4: %d\n", (this->settings >> 20 & 0xF));
	OSReport("0xDA8: %d\n", (this->settings >> 22 & 0xF));
	OSReport("Spawn Type: %d\n", (this->settings >> 24 & 0xF));
	OSReport("Direction: %d\n--------\n", (this->settings >> 31 & 0xF));
	return orig_val;
}