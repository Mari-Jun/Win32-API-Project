#pragma once
#include "Object_Main.h"

class Enemy_Skill;
class Enemy_Bitmap;
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

	void Set_Enemy_Type(const int& enemy_type);
	void Set_Attack_Delay(const int& delay);
	void Set_Attack_Reaction_Range(const int& r1, const int& r2, const int& r3, const int& r4, const int& r5);

	void Create_Enemy_Skill(const File& file);

private:
	int enemy_type;
	int attack_delay;
	int attack_reaction_range[5];
	Enemy_Skill* e_skill;
};

void Reset_Enemy(Enemy& enemy, const File& file, const int& enemy_type);
void Paint_Enemy(HDC hdc, HDC bitdc, const File& file, const Enemy_Bitmap& e_bitmap, const Enemy& enemy, const Camera& camera, const RECT c_rect);
void Paint_Enemy_Detail(HDC hdc, HDC bitdc, const Enemy& enemy, const File& file, const Enemy_Bitmap& e_bitmap);
//void Paint_Enemy_Attack_Effect(HDC hdc, HDC bitdc, const Enemy& enemy, const int& effect);

