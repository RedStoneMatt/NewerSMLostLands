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
		nw4r::lyt::Pane *W_select_00;
		nw4r::lyt::Pane *W_shadow_00;
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
		int onExecute_orig();
		int newFile();
};

extern "C" int GetGameLanguage(int nyeh); //nyeh is always 4 for some reasons

void dDateFile_c::fileNum() {
	nw4r::lyt::Picture *bgMid1Active = layout.findPictureByName("bgMid1Active");
	nw4r::lyt::Picture *bgLeftActive = layout.findPictureByName("bgLeftActive");
	nw4r::lyt::Picture *bgLeft = layout.findPictureByName("bgLeft");
	nw4r::lyt::Picture *bgMiddle = layout.findPictureByName("bgMiddle");
	nw4r::lyt::Picture *P_Shine_00 = layout.findPictureByName("P_Shine_00");
	nw4r::lyt::Picture *P_mario_00 = layout.findPictureByName("P_mario_00");
	if(GetGameLanguage(4) == 0) { // Japanese (by ?)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L"ファイル 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L"ファイル 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L"ファイル 3"); }
	}
	if(GetGameLanguage(4) == 1) { // English (by everyone actually)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L"File 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L"File 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L"File 3"); }
	}
	if(GetGameLanguage(4) == 2) { // German (by ?)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L" Datei 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L" Datei 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L" Datei 3"); }
		T_fileNumber_01->size.x = 140.11f;
		T_fileNumber_01->trans.x = -234.0f;
		N_dateFile_00->trans.x = 13.0f;
		bgLeftActive->trans.x = -314.0f;
		bgMid1Active->size.x = 122.0f;
		bgMid1Active->trans.x = -249.0f;
		W_select_00->size.x = 602.0f;
		W_select_00->trans.x = -16.0f;
		W_shadow_00->size.x = 600.0f;
		W_shadow_00->trans.x = -16.0f;
		bgLeft->trans.x = -314.0f;
		bgMiddle->size.x = 576.0f;
		bgMiddle->trans.x = -18.0f;
		P_Shine_00->size.x = 598.0f;
		P_Shine_00->trans.x = -15.0f;
		P_mario_00->trans.x = -286.0f;
		N_NewFile_00->trans.x = -30.0f;
	}
	if(GetGameLanguage(4) == 3) { // French (by RedStoneMatt)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L"Fichier 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L"Fichier 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L"Fichier 3"); }
		T_fileNumber_01->size.x = 140.11f;
		T_fileNumber_01->trans.x = -238.0f;
		N_dateFile_00->trans.x = 13.0f;
		bgLeftActive->trans.x = -314.0f;
		bgMid1Active->size.x = 122.0f;
		bgMid1Active->trans.x = -249.0f;
		W_select_00->size.x = 602.0f;
		W_select_00->trans.x = -16.0f;
		W_shadow_00->size.x = 600.0f;
		W_shadow_00->trans.x = -16.0f;
		bgLeft->trans.x = -314.0f;
		bgMiddle->size.x = 576.0f;
		bgMiddle->trans.x = -18.0f;
		P_Shine_00->size.x = 598.0f;
		P_Shine_00->trans.x = -15.0f;
		P_mario_00->trans.x = -290.0f;
		N_NewFile_00->trans.x = -30.0f;
	}
	if(GetGameLanguage(4) == 4) { // Spanish (by Sandre)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L"Archivo 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L"Archivo 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L"Archivo 3"); }
		T_fileNumber_01->size.x = 144.11f;
		T_fileNumber_01->trans.x = -242.0f;
		N_dateFile_00->trans.x = 16.0f;
		bgLeftActive->trans.x = -320.0f;
		bgMid1Active->size.x = 128.0f;
		bgMid1Active->trans.x = -252.0f;
		W_select_00->size.x = 608.0f;
		W_select_00->trans.x = -19.0f;
		W_shadow_00->size.x = 606.0f;
		W_shadow_00->trans.x = -19.0f;
		bgLeft->trans.x = -320.0f;
		bgMiddle->size.x = 582.0f;
		bgMiddle->trans.x = -21.0f;
		P_Shine_00->size.x = 598.0f;
		P_Shine_00->trans.x = -15.0f;
		P_mario_00->trans.x = -294.0f;
		N_NewFile_00->trans.x = -30.0f;
	}
	if(GetGameLanguage(4) == 5) { // Italian (by ?)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L"Salvataggio 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L"Salvataggio 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L"Salvataggio 3"); }
		T_fileNumber_01->size.x = 196.11f;
		T_fileNumber_01->trans.x = -271.0f;
		N_dateFile_00->trans.x = 41.0f;
		bgLeftActive->trans.x = -370.0f;
		bgMid1Active->size.x = 178.0f;
		bgMid1Active->trans.x = -277.0f;
		W_select_00->size.x = 658.0f;
		W_select_00->trans.x = -44.0f;
		W_shadow_00->size.x = 656.0f;
		W_shadow_00->trans.x = -44.0f;
		bgLeft->trans.x = -364.0f;
		bgMiddle->size.x = 626.0f;
		bgMiddle->trans.x = -43.0f;
		P_Shine_00->size.x = 648.0f;
		P_Shine_00->trans.x = -40.0f;
		P_mario_00->trans.x = -348.0f;
		N_NewFile_00->trans.x = -30.0f;
	}
	if(GetGameLanguage(4) == 6) { // Dutch (by ?)
		if(this->fileNum_maybe == 0) { T_fileNumber_01->SetString(L"Bestand 1"); }
		if(this->fileNum_maybe == 1) { T_fileNumber_01->SetString(L"Bestand 2"); }
		if(this->fileNum_maybe == 2) { T_fileNumber_01->SetString(L"Bestand 3"); }
		T_fileNumber_01->size.x = 144.11f;
		T_fileNumber_01->trans.x = -244.0f;
		N_dateFile_00->trans.x = 16.0f;
		bgLeftActive->trans.x = -320.0f;
		bgMid1Active->size.x = 128.0f;
		bgMid1Active->trans.x = -252.0f;
		W_select_00->size.x = 608.0f;
		W_select_00->trans.x = -19.0f;
		W_shadow_00->size.x = 606.0f;
		W_shadow_00->trans.x = -19.0f;
		bgLeft->trans.x = -320.0f;
		bgMiddle->size.x = 582.0f;
		bgMiddle->trans.x = -21.0f;
		P_Shine_00->size.x = 598.0f;
		P_Shine_00->trans.x = -15.0f;
		P_mario_00->trans.x = -296.0f;
		N_NewFile_00->trans.x = -30.0f;
	}
}

int dDateFile_c::newFile() {
	int orig_val = this->onExecute_orig(); //to preserve the original dDateFile_c::onExecute_orig function
	if(this->_70 > 34 && this->_70 < 36) { //this->_70 being unused, use it as a checker to see if isNew is ready to be used
		if(this->isNew) { //file is new, remove that nyeh pane
			T_fileNumber_01->SetVisible(false);
		}
		this->_70++;
	}
	else if(this->_70 < 36) {
		this->_70++;
	}
	return orig_val;
}