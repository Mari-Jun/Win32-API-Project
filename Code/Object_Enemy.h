#pragma once
#include "Object_Main.h"

class Object_Info;

class Enemy : public Move_Object {
public:
	~Enemy();

	const Object_Info& Get_Player_Info_Const() const;
	Object_Info& Get_Enemy_Info() const;

	void Create_Enemy_Info();
private:
	Object_Info* o_info;
};

void Reset_Enemy(Enemy& enemy, const int& hp, const int& attack, const int& defence, const int& speed);

class Practice_Enemy : public Enemy {
public:
	~Practice_Enemy();

	const BITMAP Get_Bitmap_Size() const;
	const HBITMAP Get_Stop_Motion_Bitmap(const int& index) const;

	void Set_Stop_Motion();
		
private:
	BITMAP bitmap_size;
	HBITMAP stop_motion_bitmap[4];
};

void Reset_Practice_Enemy(Practice_Enemy& p_enemy);
void Paint_Practice_Enemy(HDC hdc, HDC bitdc, const Practice_Enemy& p_enemy);