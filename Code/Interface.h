#pragma once
#include <Windows.h>

class Player;
class Map_Dungeon;
class Camera;

class Player_Interface {
public:
	~Player_Interface();

	const HBITMAP& Get_Panel_Bitmap() const;
	const BITMAP& Get_Panel_Bitmap_Size() const;
	const HBITMAP& Get_Hp_Bitmap() const;
	const BITMAP& Get_Hp_Bitmap_Size() const;
	const HBITMAP& Get_Mp_Bitmap() const;
	const BITMAP& Get_Mp_Bitmap_Size() const;
	const HBITMAP& Get_Command_Bitmap(const int& inde) const;
	const BITMAP& Get_Command_Bitmap_Size() const;
	
	void Set_Bitmap();

private:
	HBITMAP panel_bitmap;
	BITMAP panel_bitmap_size;
	HBITMAP hp_bitmap;
	BITMAP hp_bitmap_size;
	HBITMAP mp_bitmap;
	BITMAP mp_bitmap_size;
	HBITMAP command_bitmap[7];
	BITMAP command_bitmap_size;
};

void Reset_Player_Interface(Player_Interface& p_inter);
void Paint_Player_Interface(HDC hdc, HDC bitdc, const RECT c_rect, const Player_Interface& p_inter, const Player& player);

class Enemy_Interface {
public:
	~Enemy_Interface();

	const HFONT& Get_Font() const;
	const HBITMAP& Get_Hp_BackGround_Bitmap() const;
	const BITMAP& Get_Hp_BackGround_Bitmap_Size() const;
	const HBITMAP& Get_Hp_Bitmap() const;
	const BITMAP& Get_Hp_Bitmap_Size() const;

	void Set_Font();
	void Set_Bitmap();

private:
	HFONT font;
	HBITMAP hp_background;
	BITMAP hp_background_size;
	HBITMAP hp_bitmap;
	BITMAP hp_bitmap_size;
};

void Reset_Enemy_Interface(Enemy_Interface& e_inter);
void Paint_Enemy_Interface(HDC hdc, HDC bitdc, const RECT c_rect, const Enemy_Interface& e_inter, const Map_Dungeon& map_d, const Camera& camera);

class Clear_Interface {
public:
	~Clear_Interface();

	const HFONT& Get_Font(const int& index) const;
	const HBITMAP& Get_Clear_Bitmap() const;
	const BITMAP& Get_Clear_Bitmap_Size() const;
	const int& Get_Item(const int& index) const;
	const int& Get_Gold() const;

	void Set_Font();
	void Set_Bitmap();
	void Set_Item();
	void Set_Gold(const Player& player, const Map_Dungeon& map_d);

private:
	HFONT font[2];
	HBITMAP clear_bitmap;
	BITMAP clear_bitmap_size;
	int item[3];
	int gold;
};

void Reset_Clear_Interface(Clear_Interface& c_inter, Player& player, const Map_Dungeon& map_d);
void Paint_Clear_Interface(HDC hdc, HDC bitdc, const Clear_Interface& c_inter, const Player& player, const Map_Dungeon& map_d, const RECT c_rect);

void Clear_Dungeon_Player_Reward(const Clear_Interface& c_inter, Player& player, const Map_Dungeon& map_d);