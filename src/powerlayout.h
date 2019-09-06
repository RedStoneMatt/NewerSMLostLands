#ifndef MSGBOX_H
#define MSGBOX_H 
#include <common.h>
#include <game.h>

class dPowerLayout_c : public dStageActor_c {
	public:
		void showMessage(int id, bool canCancel=true, int delay=-1);

		dPowerLayout_c() : state(this, &StateID_LoadRes) { }

		int onCreate();
		int onDelete();
		int onExecute();
		int onDraw();

		int beforeExecute() { return true; }
		int afterExecute(int) { return true; }
		int beforeDraw() { return true; }
		int afterDraw(int) { return true; }

		m2d::EmbedLayout_c layout;
		dDvdLoader_c msgDataLoader;

		bool layoutLoaded;
		bool visible;

		bool canCancel;
		int delay;

		dStateWrapper_c<dPowerLayout_c> state;

		USING_STATES(dPowerLayout_c);
		DECLARE_STATE(LoadRes);
		DECLARE_STATE(Wait);
		DECLARE_STATE(BoxAppearWait);
		DECLARE_STATE(ShownWait);
		DECLARE_STATE(BoxDisappearWait);

		static dPowerLayout_c *instance;
		static dPowerLayout_c *build();

	private:
		struct entry_s {
			u32 id;
			u32 titleOffset;
			u32 msgOffset;
		};

		struct header_s {
			u32 count;
			entry_s entry[1];
		};
};
#endif /* MSGBOX_H */
