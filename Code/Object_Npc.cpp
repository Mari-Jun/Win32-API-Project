#include <Windows.h>
#include <tchar.h>
#include "Object_Npc.h"

Npc::~Npc() {
	for (int index = 0; index < 10; index++)
		DeleteObject(stop_motion_bitmap[index]);
}

const int& Npc::Get_Npc_Type() const {
	return npc_type;
}

const HBITMAP Npc::Get_Stop_Motion_Bitmap(const int& index) const {
	return stop_motion_bitmap[index];
}

const BITMAP Npc::Get_Stop_Size() const {
	return stop_motion_size;
}

const bool& Npc::Is_Quest_Exist() const {
	return quest_exist;
}

const bool& Npc::Is_Interaction() const {
	return interaction;
}

const int& Npc::Get_Interaction_Count() const {
	return interaction_count;
}

const int& Npc::Get_Ani_Count() const {
	return ani_count;
}

void Npc::Set_Bitmap() {
	switch (Get_Npc_Type())
	{
	case Npc_Name::ELDER:
		for (int index = 0; index < 6; index++) {
			wchar_t str[50];
			wsprintf(str, _T(".\\BitMap\\Npc\\Non_Move\\Elder\\Elder%d.bmp"), index + 1);
			stop_motion_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		break;
	case Npc_Name::WEAPON_SHOP:
		for (int index = 0; index < 6; index++) {
			wchar_t str[50];
			wsprintf(str, _T(".\\BitMap\\Npc\\Non_Move\\Weapon\\Weapon%d.bmp"), index + 1);
			stop_motion_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		break;
	case Npc_Name::ITEM_SHOP:
		for (int index = 0; index < 8; index++) {
			wchar_t str[50];
			wsprintf(str, _T(".\\BitMap\\Npc\\Non_Move\\Item\\Item%d.bmp"), index + 1);
			stop_motion_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		break;
	case Npc_Name::LEGEND:
		for (int index = 0; index < 8; index++) {
			wchar_t str[50];
			wsprintf(str, _T(".\\BitMap\\Npc\\Non_Move\\Legend\\Legend%d.bmp"), index + 1);
			stop_motion_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		break;
	case Npc_Name::SOLDIER:
		for (int index = 0; index < 8; index++) {
			wchar_t str[50];
			wsprintf(str, _T(".\\BitMap\\Npc\\Non_Move\\Soldier\\Soldier%d.bmp"), index + 1);
			stop_motion_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		break;
	default:
		break;
	}
	GetObject(stop_motion_bitmap[0], sizeof(BITMAP), &stop_motion_size);
}

void Npc::Set_Quest_Exist(const bool& quest_exist) {
	this->quest_exist = quest_exist;
}

void Npc::Set_Interaction(const bool& interaction) {
	this->interaction = interaction;
}

void Npc::Set_Ani_Count(const int& ani_count) {
	this->ani_count = ani_count;
}

void Npc::Set_interaction_Count(const int& inter_count) {
	this->interaction_count = inter_count;
}

void Npc::Set_Npc_Type(const int& npc_type) {
	this->npc_type = npc_type;
}


void Reset_Npc(Npc& npc, const int& npc_type, const int& x_pos, const int& y_pos) {
	npc.Set_Npc_Type(npc_type);
	npc.Set_Quest_Exist(false);
	npc.Set_Interaction(false);
	npc.Set_interaction_Count(0);
	npc.Set_Ani_Count(0);
	npc.Set_Bitmap();
	Reset_Object(npc, x_pos, y_pos, npc.Get_Stop_Size().bmWidth, npc.Get_Stop_Size().bmHeight);

	switch (npc_type)
	{
	case Npc_Name::ELDER:
		npc.Set_Crash_Height(30);
		npc.Set_Crash_Width(30);
		break;
	case Npc_Name::WEAPON_SHOP:
	case Npc_Name::ITEM_SHOP:
	case Npc_Name::LEGEND:
	case Npc_Name::SOLDIER:
		npc.Set_Crash_Height(40);
		npc.Set_Crash_Width(40);
	default:
		break;
	}
}

void Paint_Npc(HDC hdc, HDC bitdc, const Npc& npc) {
	switch (npc.Get_Npc_Type())
	{
	case Npc_Name::ELDER:
		SelectObject(bitdc, npc.Get_Stop_Motion_Bitmap(npc.Get_Ani_Count() / 4));
		TransparentBlt(hdc, npc.Get_XPos() - 15, npc.Get_YPos() + 15, npc.Get_Width(), npc.Get_Height(), bitdc, 0, 0, npc.Get_Width(), npc.Get_Height(), RGB(150, 150, 150));
		break;
	case Npc_Name::WEAPON_SHOP:
	case Npc_Name::ITEM_SHOP:
	case Npc_Name::LEGEND:
	case Npc_Name::SOLDIER:
		SelectObject(bitdc, npc.Get_Stop_Motion_Bitmap(npc.Get_Ani_Count() / 4));
		TransparentBlt(hdc, npc.Get_XPos() - 10, npc.Get_YPos() + 15, npc.Get_Width(), npc.Get_Height(), bitdc, 0, 0, npc.Get_Width(), npc.Get_Height(), RGB(150, 150, 150));
	default:
		break;
	}
}