#pragma once
#include <Windows.h>
#include "Object_Main.h"

class Player_Equipment;
class Player_Item;
class Player_Skill;
class Progress;
class Sound;
class File;

class Player : public Move_Object {
public:
	~Player();

	const int& Get_Class_Type() const;
	const Player_Equipment& Get_Player_Equipment_Const() const;
	Player_Equipment& Get_Player_Equipment() const;
	const Player_Skill& Get_Player_Skill_Const() const;
	Player_Skill& Get_Player_Skill() const;
	const Player_Item& Get_Player_Item_Const() const;
	Player_Item& Get_Player_Item() const;
	Sound& Get_Player_Sound() const;
	
	const BITMAP& Get_Motion_Size() const;
	const HBITMAP& Get_Stop_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Move_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Run_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Die_Motion(const int& direction, const int& index) const;
	const HBITMAP& Get_Attack_Motion(const int& direction, const int& index) const;

	void Set_Class_Type(const int& class_type);
	void Set_Motion_Bitmap();

	void Create_Player_Equipment();
	void Create_Player_Skill(File& file);
	void Create_Player_Item();
	void Create_Player_Sound();

private:
	int class_type;
	Player_Equipment* p_equip;
	Player_Skill* p_skill;
	Player_Item* p_item;
	Sound* p_sound;
	BITMAP motion_size;
	HBITMAP stop_motion_bitmap[8][8];
	HBITMAP move_motion_bitmap[8][8];
	HBITMAP run_motion_bitmap[8][8];
	HBITMAP die_motion_bitmap[8][8];
	HBITMAP attack_motion_bitmap[8][10];
};

void Reset_Player(Player& player, File& file, const int& class_type);
void Paint_Player (HDC hdc, HDC bitdc, const Player& player);
void Paint_Player_Equipment(HDC hdc, HDC bitdc, const Player& player);

void Equipment_Command(Player& player);
void Chnage_Equipment(Player& player, WPARAM wParam);
void Use_Item_Command(Player& player, WPARAM wParam);

void Change_Map_Reset_Player(Player& player, const Progress& progress);