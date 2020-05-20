#pragma once
#include <Windows.h>
#include "Object_Main.h"

class Player_Equipment;

class Player : public Move_Object {
public:
	~Player();

	const int& Get_Class_Type() const;
	const Player_Equipment& Get_Player_Equipment_Const() const;
	Player_Equipment& Get_Player_Equipment() const;
	
	const BITMAP Get_Motion_Size() const;
	const HBITMAP Get_Stop_Motion(const int& direction) const;
	const HBITMAP Get_Move_Motion(const int& direction, const int& index) const;
	const HBITMAP Get_Attack_Motion(const int& direction, const int& index) const;

	void Set_Class_Type(const int& class_type);
	void Set_Motion_Bitmap();

	void Create_Player_Equipment();

private:
	int class_type;
	Player_Equipment* p_equip;
	BITMAP motion_size;
	HBITMAP stop_motion_bitmap[8];
	HBITMAP move_motion_bitmap[8][8];
	HBITMAP attack_motion_bitmap[8][10];
};

void Reset_Player(Player& player, const int& class_type);
void Paint_Player (HDC hdc, HDC bitdc, const Player& player);
void Paint_Player_Equipment(HDC hdc, HDC bitdc, const Player& player);

void Equipment_Command(Player& player);
bool Chnage_Equipment(Player& player, WPARAM wParam);