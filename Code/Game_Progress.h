#pragma once
#include <Windows.h>

class Player;

class Progress {
public:
	const int& Get_Player_Class() const;
	const int& Get_Map_Type() const;
	const int& Get_Select_Map_Type() const;
	const bool& Is_Map_Select() const;
	const int& Get_Quest_Num() const;
	const int& Get_Quest_Clear() const;
	const HBITMAP& Get_Map_Select_Bitmap() const;
	const BITMAP& Get_Map_Select_Bitmap_Size() const;
	const HFONT& Get_Font() const;

	void Set_Player_Class(const int& player_class);
	void Set_Map_Type(const int& map_type);
	void Set_Select_Map_Type(const int& select_map_type);
	void Set_Map_Select(const bool& map_select);
	void Set_Quest_Num(const int& quest_num);
	void Set_Quest_Clear(const int& quest_clear);
	void Set_Bitmap_Font();

private:
	int player_class;
	int map_type;
	int select_map_type;
	bool map_select;
	int quest_num;
	int quest_clear;
	HBITMAP map_select_bitmap;
	BITMAP map_select_bitmap_size;
	HFONT map_font;
};

void Reset_Progress(Progress& progress, const int& player_class);
void Paint_Map_Select(HDC hdc, HDC bitdc, const Progress& progress, const RECT c_rect);
int Change_Map_Select(Progress& progress, Player& player, const WPARAM wParam);
void Change_Map_Dungeon_Clear(Progress& progress, Player& player);
void Clear_Quest(Progress& progress);

