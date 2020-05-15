#pragma once
#include <Windows.h>
#include "Object_Main.h"

class Player_Info;

class Player : public Move_Object {
public:
	~Player();

	const int& Get_Status() const;
	const Player_Info& Get_Player_Info_Const() const;
	Player_Info& Get_Player_Info() const;

	void Set_Status(const int& status);
	void Create_Player_Info();

private:
	int status;
	Player_Info* p_info;
};

void Reset_Player(Player& player, const int& width, const int& height);

//비트맵을 그냥 Player에 선언할지 고민좀 해보자.

class Warrior : public Player {
public:
	~Warrior();

	const HBITMAP Get_Stop_Motion(const int& direction) const;
	const BITMAP Get_Stop_Motion_Size() const;
	const HBITMAP Get_Move_Motion(const int& direction, const int& index);
	const BITMAP Get_Move_Motion_Size() const;

	void Set_Stop_Motion();
	void Set_Move_Motion();

private:
	HBITMAP stop_motion_bitmap[8];
	BITMAP stop_motion_size;
	HBITMAP move_motion_bitmap[8][8];
	BITMAP move_motion_size;
};

void Reset_Warrior(Warrior& warrior);
void Paint_Warrior(HDC hdc, HDC bitdc, Warrior& warrior);