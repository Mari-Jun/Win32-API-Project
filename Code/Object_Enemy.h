#pragma once
#include "Object_Main.h"

class Enemy_Skill;
class File;
class Camera;

class Enemy :public Move_Object {
public:
	~Enemy();

	const int& Get_Enemy_Type() const;
	const int& Get_Attack_Delay() const;
	const int& Get_Attack_Reaction_Range(const int& index) const;
	const Enemy_Skill& Get_Enemy_Skill_Const() const;
	Enemy_Skill& Get_Enemy_Skill() const;
	const BITMAP& Get_Motion_Size() const;
	const BITMAP& Get_Attack_Effect_Size() const;
	const HBITMAP& Get_Stop_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Move_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Attack_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Attack_Effect_Motion(const int& direction, const int& index) const;

	void Set_Enemy_Type(const int& enemy_type);
	void Set_Attack_Delay(const int& delay);
	void Set_Attack_Reaction_Range(const int& r1, const int& r2, const int& r3, const int& r4, const int& r5);
	void Set_Motion_Bitmap(const File& file);

	void Create_Enemy_Skill(const File& file);

private:
	int enemy_type;
	int attack_delay;
	int attack_reaction_range[5];
	Enemy_Skill* e_skill;
	BITMAP motion_size;
	BITMAP attack_effect_size;
	HBITMAP stop_motion_bitmap[8][20];
	HBITMAP move_motion_bitmap[8][20];
	HBITMAP attack_motion_bitmap[8][20];
	HBITMAP attack_effect_bitmap[8][20];
};

void Reset_Enemy(Enemy& enemy, const File& file, const int& enemy_type);
void Paint_Enemy(HDC hdc, HDC bitdc, const File& file, const Enemy& enemy, const Camera& camera, const RECT c_rect);
void Paint_Enemy_Detail(HDC hdc, HDC bitdc, const Enemy& enemy, const File& file);
//void Paint_Enemy_Attack_Effect(HDC hdc, HDC bitdc, const Enemy& enemy, const int& effect);

