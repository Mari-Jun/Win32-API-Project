#pragma once
#include "Object_Main.h"

class Enemy :public Move_Object {
public:
	~Enemy();

	const int& Get_Enemy_Type() const;
	const int& Get_Attack_Delay() const;
	const int& Get_Skill_Delay(const int& index) const;
	const BITMAP& Get_Motion_Size() const;
	const HBITMAP& Get_Stop_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Move_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Attack_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Skill_Motion1(const int& direction, const int& index) const;

	void Set_Enemy_Type(const int& enemy_type);
	void Set_Attack_Delay(const int& delay);
	void Set_Skill_Delay(const int& index, const int& delay);
	void Set_Motion_Bitmap();

private:
	int enemy_type;
	int attack_delay;
	int skill_delay[4];
	BITMAP motion_size;
	HBITMAP stop_motion_bitmap[8][10];
	HBITMAP move_motion_bitmap[8][10];
	HBITMAP attack_motion_bitmap[8][20];
	HBITMAP skill_motion1_bitmap[8][20];
};

void Reset_Enemy(Enemy& enemy, const int& enemy_type);
void Paint_Enemy(HDC hdc, HDC bitdc, const Enemy& enemy);
//Boss라는 객체를 만들게되면 Command쪽에서 조금 꼬이지 않나.. (근데 어차피 맵에 넣을껀데??)

