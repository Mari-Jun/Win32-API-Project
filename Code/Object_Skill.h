#pragma once
#include <Windows.h>

class Player;
class File;

class Object_Skill {
public:
	Object_Skill();
	virtual ~Object_Skill();

	const HBITMAP& Get_Skill_Motion_Bitmap(const int& skill_type, const int& direction, const int& index) const;
	const HBITMAP& Get_Skill_Effect_Bitmap(const int& skill_type, const int& direction, const int& index) const;
	const int& Get_Current_Delay(const int& index) const;
	const int& Get_Skill_Delay(const int& index) const;

	virtual void Set_Motion_Bitmap(const File& file, const int& type) = 0;
	void Set_Bitmap(const int& skill, const int& direction, const int& index, const HBITMAP& bitmap);
	void Set_Effect_Bitmap(const int& skill, const int& direction, const int& index, const HBITMAP& bitmap);
	void Set_Current_Delay(const int& index, const int& current_delay);
	void Set_Skill_Delay(const int& index, const int& skill_delay);
	

private:
	HBITMAP skill_motion_bitmap[4][8][30];
	HBITMAP skill_effect_bitmap[4][8][30];
	int current_delay[4];
	int skill_delay[4];
};

class Player_Skill : public Object_Skill {
public:
	virtual ~Player_Skill();

	const BITMAP& Get_Skill_Bitmap_Size() const;
	const HBITMAP& Get_Skill_Bitmap(const int& index) const;
	const int& Get_Use_Mp(const int& index) const;

	void Set_Skill_Bitmap(const int& class_type);
	virtual void Set_Motion_Bitmap(const File& file, const int& type);
	void Set_Use_Mp(const int& class_type);
	void Set_Delay(const int& class_type);

private:
	BITMAP skill_bitmap_size;
	HBITMAP skill_bitmap[4];
	int use_mp[4];
};

void Reset_Player_Skill(Player_Skill& p_skill, const File& file, const int& class_type);
void Paint_Player_Skill_Icon(HDC hdc, HDC bitdc, const Player_Skill& p_skill, const RECT c_rect);
void Change_Player_Status_To_Skill(Player& player, const WPARAM wParam);
void Change_Player_Info_Use_Skill(Player& player, const int& status_type, const int& skill_type);


class Enemy_Skill : public Object_Skill {
public:
	virtual void Set_Motion_Bitmap(const File& file, const int& type);
	void Set_Delay(const File& file, const int& enemy_type);
};

void Reset_Enemy_Skill(Enemy_Skill& e_skill, const File& file, const int& enemy_type);