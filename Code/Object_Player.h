#pragma once
#include <Windows.h>
#include "Object_Main.h"

class Player_Info;

class Player : public Object {
public:
	~Player();

	const int& Get_Direction() const;
	const Player_Info& Get_Player_Info_Const() const;
	Player_Info& Get_Player_Info() const;

	void Set_Direction(const int& direction);
	void Create_Player_Info();

	void Move_Player_Up(RECT c_rect, bool diagonal);
	void Move_Player_Down(RECT c_rect, bool diagonal);
	void Move_Player_Left(RECT c_rect, bool diagonal);
	void Move_Player_Right(RECT c_rect, bool diagonal);


private:
	int direction;
	Player_Info* p_info;
};

void Reset_Player(Player& player, RECT c_rect, const int& width, const int& height);
void Move_Player(Player& player, RECT c_rect);

class Warrior : public Player {
public:
	~Warrior();

	const HBITMAP Get_Stop_Motion(int direction) const;
	const BITMAP Get_Stop_Motion_Size() const;

	void Set_Stop_Motion();

private:
	HBITMAP stop_motion_bitmap[8];
	BITMAP stop_motion_size;
};

void Reset_Warrior(Warrior& warrior, RECT c_rect);
void Paint_Warrior(HDC hdc, HDC bitdc, Warrior& warrior);