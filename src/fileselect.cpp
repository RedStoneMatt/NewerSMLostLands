#include <game.h>

class StateMethodExecutor {
	public:
		u32 vtable;
		u32 owningObject;
		u32 stateToCall;
};

class SMWrapperCls4 {
	public:
		u32 vtable;
};

class StateExecutor {
	public:
		u32 vtable;
		StateMethodExecutor stateMethodExecutor;
};

class SMWrapperBase {
	public:
		u32 vtable;
		SMWrapperCls4 cls4;
		StateExecutor cls8;
		dStateMgr_c stateMgr;
};

class SMWrapper : SMWrapperBase {

};

class dDateFile_c : dBase_c {
	public:
		u8 _70;
		u8 _71;
		u8 _72;
		u8 _73;
		m2d::EmbedLayout_c layout;
		u8 efClass0_0[296];
		u8 efClass0_1[296];
		u8 efClass0_2[296];
		u8 efClass0_3[296];
		u8 efClass0_4[296];
		u8 efClass1_0[296];
		u8 efClass1_1[296];
		u8 efClass1_2[296];
		u8 efClass1_3[296];
		u8 efClass1_4[296];
		SMWrapper stateThing;
		u32 nextActionToExecute;
		nw4r::lyt::Pane *rootPane;
		nw4r::lyt::Pane *N_dateFile_00;
		nw4r::lyt::Pane *N_dateFile_01;
		nw4r::lyt::Pane *N_NewFile_00;
		nw4r::lyt::Pane *N_save;
		u32 W_select_00;
		u32 W_shadow_00;
		nw4r::lyt::TextBox *T_worldNumber_00;
		nw4r::lyt::TextBox *T_worldNumber_01;
		nw4r::lyt::TextBox *T_x_00;
		nw4r::lyt::TextBox *T_zanki_00;
		nw4r::lyt::TextBox *T_fileNumber_00;
		nw4r::lyt::TextBox *T_fileNumber_01;
		nw4r::lyt::TextBox *T_NewdateFile_00;
		nw4r::lyt::TextBox *T_NewdateFileS;
		nw4r::lyt::Picture *P_Star_00;
		nw4r::lyt::Picture *P_Star_01;
		nw4r::lyt::Picture *P_Star_02;
		nw4r::lyt::Picture *P_Star_03;
		nw4r::lyt::Picture *P_Star_04;
		nw4r::lyt::Picture *P_Star_05;
		nw4r::lyt::Picture *P_Star_06;
		nw4r::lyt::Picture *P_Star_07;
		nw4r::lyt::Picture *P_Star_08;
		nw4r::lyt::Picture *P_Star_09;
		float inexplicably_float;
		u32 fileNum_maybe;
		u8 hasLoaded;
		u8 doActuallyDrawMe;
		u8 isNew;
		u8 doesHaveBalloon_maybe;
		u8 mustLoadMyInfo;
		u8 isWaitingForAnim;
		u8 probablyActivatesHit;
		u8 doesDrawStarEffects;
		u8 inited_to_1_E50;
		u8 _E51;
		u8 _E52;
		u8 _E53;
		u32 field_E54;
		
		void fileNum();
};

extern "C" int GetGameLanguage(int nyeh); //nyeh is alway 4 for some reasons

void dDateFile_c::fileNum() {	
	// OSReport("fileNum_maybe: %d\n", this->fileNum_maybe);
	
	if(GetGameLanguage(4) == 1) { // English (by everyone actually)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L"   File 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L"   File 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L"   File 3"); }
	}
	if(GetGameLanguage(4) == 2) { // German (by ?)
		T_fileNumber_01->SetString(L"UT ");
	}
	if(GetGameLanguage(4) == 3) { // French (by RedStoneMatt)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L"Fichier 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L"Fichier 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L"Fichier 3"); }
	}
	if(GetGameLanguage(4) == 4) { // Spanish (by ?)
		T_fileNumber_01->SetString(L"UT ");
	}
	if(GetGameLanguage(4) == 5) { // Italian (by ?)
		T_fileNumber_01->SetString(L"UT ");
	}
	if(GetGameLanguage(4) == 6) { // Dutch (by ?)
		T_fileNumber_01->SetString(L"UT ");
	}
}