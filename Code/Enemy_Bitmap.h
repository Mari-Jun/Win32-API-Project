#pragma once
#include <Windows.h>

class File;
class Progress;

class Enemy_Bitmap {
public:
	~Enemy_Bitmap();

	const BITMAP& Get_Motion_Size(const int& type) const;
	const HBITMAP& Get_Stop_Motion(const int& type, const int& direction, const int& index) const;
	const HBITMAP& Get_Move_Motion(const int& type, const int& direction, const int& index) const;
	const HBITMAP& Get_Attack_Motion(const int& type, const int& direction, const int& index) const;

	void Set_Motion_Bitmap(const File& file, const int& enemy_type);

private:
	BITMAP motion_size[30];
	HBITMAP stop_motion_bitmap[30][8][20];
	HBITMAP move_motion_bitmap[30][8][20];
	HBITMAP attack_motion_bitmap[30][8][20];
};

void Reset_Enemy_Bitmap(Enemy_Bitmap& e_bitmap, const File& file, const int& dungeon_type);