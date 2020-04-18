#ifndef __KAMEK_NUMPAD_H
#define __KAMEK_NUMPAD_H
#include <game.h>


class dNumpadSpawner_c : public dStageActor_c {
	public:
		static dNumpadSpawner_c *build();
		static dNumpadSpawner_c *instance;

		dNumpadSpawner_c();

		int onCreate();
		int onDelete();
		int onExecute();
		int onDraw();

		int beforeExecute() { return true; }
		int afterExecute(int) { return true; }
		int beforeDraw() { return true; }
		int afterDraw(int) { return true; }

		m2d::EmbedLayout_c layout;
		bool layoutLoaded;

		bool visible;
		float scaleEase;
		int timer;

		int selected, lastTopRowChoice;

		nw4r::lyt::TextBox
			*T_numberS_00, *T_number_00,
			*T_one_00, *T_one_01,
			*T_two_00, *T_two_01,
			*T_three_00, *T_three_01,
			*T_four_00, *T_four_01,
			*T_five_00, *T_five_01,
			*T_six_00, *T_six_01,
			*T_seven_00, *T_seven_01,
			*T_eight_00, *T_eight_01,
			*T_nine_00, *T_nine_01;

		nw4r::lyt::Picture
			*BtnLeft[9], *BtnMid[9], *BtnRight[9];

		nw4r::lyt::Pane
			*Buttons[9];



		void selectNumber(int num);
		void doSummon();

		dStateWrapper_c<dNumpadSpawner_c> state;

		USING_STATES(dNumpadSpawner_c);
		DECLARE_STATE(Hidden);
		DECLARE_STATE(ShowWait);
		DECLARE_STATE(ButtonActivateWait);
		DECLARE_STATE(Wait);
		DECLARE_STATE(HideWait);
};

#endif

