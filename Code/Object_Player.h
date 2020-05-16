#pragma once
#include <Windows.h>
#include "Object_Main.h"

class Player_Info;

class Player : public Move_Object {
public:
	~Player();

	const Player_Info& Get_Player_Info_Const() const;
	Player_Info& Get_Player_Info() const;

	void Create_Player_Info();

private:
	Player_Info* p_info;
};

void Reset_Player(Player& player, const int& width, const int& height);

//비트맵을 그냥 Player에 선언할지 고민좀 해보자.

class Warrior : public Player {
public:
	~Warrior();

	const BITMAP Get_Motion_Size() const;
	const HBITMAP Get_Stop_Motion(const int& direction) const;
	const HBITMAP Get_Move_Motion(const int& direction, const int& index);
	const HBITMAP Get_Attack_Motion(const int& direction, const int& index) const;

	void Set_Stop_Motion();
	void Set_Move_Motion();
	void Set_Attack_Motion();

private:
	BITMAP motion_size;
	HBITMAP stop_motion_bitmap[8];
	HBITMAP move_motion_bitmap[8][8];
	HBITMAP attack_motion_bitmap[8][10];
};

void Reset_Warrior(Warrior& warrior);
void Paint_Warrior(HDC hdc, HDC bitdc, Warrior& warrior);