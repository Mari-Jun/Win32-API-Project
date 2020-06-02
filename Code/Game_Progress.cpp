#include <Windows.h>
#include <tchar.h>
#include "Game_Progress.h"
#include "Source.h"
#include "Object_Player.h"

const int& Progress::Get_Player_Class() const {
	return player_class;
}

const int& Progress::Get_Map_Type() const {
	return map_type;
}

const int& Progress::Get_Select_Map_Type() const {
	return select_map_type;
}

const bool& Progress::Is_Map_Select() const {
	return map_select;
}

const int& Progress::Get_Quest_Num() const {
	return quest_num;
}

const int& Progress::Get_Quest_Clear() const {
	return quest_clear;
}

const HBITMAP& Progress::Get_Map_Select_Bitmap() const {
	return map_select_bitmap;
}

const BITMAP& Progress::Get_Map_Select_Bitmap_Size() const {
	return map_select_bitmap_size;
}

const HFONT& Progress::Get_Font() const {
	return map_font;
}

void Progress::Set_Player_Class(const int& player_class) {
	this->player_class = player_class;
}

void Progress::Set_Map_Type(const int& map_type) {
	this->map_type = map_type;
}

void Progress::Set_Select_Map_Type(const int& select_map_type) {
	this->select_map_type = select_map_type;
}

void Progress::Set_Map_Select(const bool& map_select) {
	this->map_select = map_select;
}

void Progress::Set_Quest_Num(const int& quest_num) {
	this->quest_num = quest_num;
}

void Progress::Set_Quest_Clear(const int& quest_clear) {
	this->quest_clear = quest_clear;
}

void Progress::Set_Bitmap_Font() {
	map_select_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Map_Select.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(map_select_bitmap, sizeof(BITMAP), &map_select_bitmap_size);
	map_font = CreateFont(35, 12, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("ÈÞ¸Õ ÆíÁöÃ¼"));
}

void Reset_Progress(Progress& progress, const int& player_class) {
	progress.Set_Player_Class(player_class);
	progress.Set_Map_Type(Map_Type::Village1);
	progress.Set_Select_Map_Type(Map_Type::Dungeon1);
	progress.Set_Map_Select(false);
	progress.Set_Quest_Num(Quest_Name::No_Quest);
	progress.Set_Quest_Clear(Quest_Name::No_Quest);
	progress.Set_Bitmap_Font();
}

void Paint_Map_Select(HDC hdc, HDC bitdc, const Progress& progress, const RECT c_rect) {
	if (!progress.Is_Map_Select())
		return;

	SelectObject(bitdc, progress.Get_Map_Select_Bitmap());
	TransparentBlt(hdc, c_rect.right / 2 - progress.Get_Map_Select_Bitmap_Size().bmWidth / 2, c_rect.bottom / 2 - progress.Get_Map_Select_Bitmap_Size().bmHeight / 2, progress.Get_Map_Select_Bitmap_Size().bmWidth, progress.Get_Map_Select_Bitmap_Size().bmHeight,
		bitdc, 0, 0, progress.Get_Map_Select_Bitmap_Size().bmWidth, progress.Get_Map_Select_Bitmap_Size().bmHeight, RGB(150, 150, 150));

	SelectObject(hdc, progress.Get_Font());
	switch (progress.Get_Select_Map_Type())
	{
	case Map_Type::Dungeon1:
		TextOut(hdc, c_rect.right / 2 - progress.Get_Map_Select_Bitmap_Size().bmWidth / 2 + 80, c_rect.bottom / 2 - progress.Get_Map_Select_Bitmap_Size().bmHeight / 2 + 35, _T("¿Ü°û Áö¿ª"), 5);
		break;
	case Map_Type::Dungeon2:
		TextOut(hdc, c_rect.right / 2 - progress.Get_Map_Select_Bitmap_Size().bmWidth / 2 + 80, c_rect.bottom / 2 - progress.Get_Map_Select_Bitmap_Size().bmHeight / 2 + 35, _T("¼öÇ® Áö¿ª"), 5);
		break;
	case Map_Type::Dungeon3:
		TextOut(hdc, c_rect.right / 2 - progress.Get_Map_Select_Bitmap_Size().bmWidth / 2 + 80, c_rect.bottom / 2 - progress.Get_Map_Select_Bitmap_Size().bmHeight / 2 + 35, _T("´ÏÆR Áö¿ª"), 5);
		break;
	default:
		break;
	}

}

int Change_Map_Select(Progress& progress, Player& player, const WPARAM wParam) {

	if (!progress.Is_Map_Select())
		return -1;

	switch (wParam)
	{
	case VK_LEFT:
		if (progress.Get_Select_Map_Type() > Map_Type::Dungeon1)
			progress.Set_Select_Map_Type(progress.Get_Select_Map_Type() - 1);
		break;
	case VK_RIGHT:
		if (progress.Get_Quest_Num() > progress.Get_Select_Map_Type())
			progress.Set_Select_Map_Type(progress.Get_Select_Map_Type() + 1);
		break;
	case VK_RETURN:
		progress.Set_Map_Select(false);
		player.Set_Status(Player_Status::Stop);
		progress.Set_Map_Type(progress.Get_Select_Map_Type());
		return progress.Get_Map_Type();
	case VK_ESCAPE:
		progress.Set_Map_Select(false);
		player.Set_Status(Player_Status::Stop);
		break;
	default:
		break;
	}
	return 0;
}

void Change_Map_Dungeon_Clear(Progress& progress, Player& player) {
	player.Set_Status(Player_Status::Stop);
	progress.Set_Map_Type(Map_Type::Village1);
}

void Clear_Quest(Progress& progress) {
	if (progress.Get_Quest_Clear() < progress.Get_Map_Type())
		progress.Set_Quest_Clear(progress.Get_Quest_Clear() + 1);
}