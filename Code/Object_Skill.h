#pragma once
#include <Windows.h>

class Player;

class Object_Skill {
public:
	~Object_Skill();

	const HBITMAP& Get_Skill1_Motion_Bitmap(const int& direction, const int& index) const;
	const HBITMAP& Get_Skill2_Motion_Bitmap(const int& direction, const int& index) const;
	const HBITMAP& Get_Skill3_Motion_Bitmap(const int& direction, const int& index) const;
	const HBITMAP& Get_Skill4_Motion_Bitmap(const int& direction, const int& index) const;
	const int& Get_Current_Delay(const int& index) const;
	const int& Get_Skill_Delay(const int& index) const;

	virtual void Set_Motion_Bitmap(const int& type) = 0;
	void Set_Bitmap(const int& skill, const int& direction, const int& index, const HBITMAP& bitmap);
	void Set_Current_Delay(const int& index, const int& current_delay);
	void Set_Skill_Delay(const int& index, const int& skill_delay);
	

private:
	HBITMAP skill1_motion_bitmap[8][20];
	HBITMAP skill2_motion_bitmap[8][20];
	HBITMAP skill3_motion_bitmap[8][20];
	HBITMAP skill4_motion_bitmap[8][20];
	int current_delay[4];
	int skill_delay[4];
};

class Player_Skill : public Object_Skill {
public:
	~Player_Skill();

	const BITMAP& Get_Skill_Bitmap_Size() const;
	const HBITMAP& Get_Skill_Bitmap(const int& index) const;
	const int& Get_Use_Mp(const int& index) const;

	void Set_Skill_Bitmap(const int& class_type);
	virtual void Set_Motion_Bitmap(const int& type);
	void Set_Use_Mp(const int& class_type);
	void Set_Delay(const int& class_type);

private:
	BITMAP skill_bitmap_size;
	HBITMAP skill_bitmap[4];
	int use_mp[4];
};

void Reset_Player_Skill(Player_Skill& p_skill, const int& class_type);
void Paint_Player_Skill_Icon(HDC hdc, HDC bitdc, const Player_Skill& p_skill, const RECT c_rect);
void Change_Player_Status_To_Skill(Player& player, const WPARAM wParam);
void Change_Player_Info_Use_Skill(Player& player, const int& status_type, const int& skill_type);


class Enemy_Skill : public Object_Skill {
public:
	virtual void Set_Motion_Bitmap(const int& type);
private:
};