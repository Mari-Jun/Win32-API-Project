#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include "Source.h"
#include "File.h"
#include "Game_Progress.h"
#include "Enemy_Bitmap.h"

Enemy_Bitmap::~Enemy_Bitmap() {
	for (int type = 0; type < 30; type++) 
		for (int direction = 0; direction < 8; direction++) 
			for (int index = 0; index < 20; index++) {
				DeleteObject(stop_motion_bitmap[type][direction][index]);
				DeleteObject(move_motion_bitmap[type][direction][index]);
				DeleteObject(attack_motion_bitmap[type][direction][index]);
			}
}

const BITMAP& Enemy_Bitmap::Get_Motion_Size(const int& type) const {
	return motion_size[type];
}

const HBITMAP& Enemy_Bitmap::Get_Stop_Motion(const int& type, const int& direction, const int& index) const {
	return stop_motion_bitmap[type][direction][index];
}

const HBITMAP& Enemy_Bitmap::Get_Move_Motion(const int& type, const int& direction, const int& index) const {
	return move_motion_bitmap[type][direction][index];
}

const HBITMAP& Enemy_Bitmap::Get_Attack_Motion(const int& type, const int& direction, const int& index) const {
	return attack_motion_bitmap[type][direction][index];
}

void Enemy_Bitmap::Set_Motion_Bitmap(const File& file, const int& enemy_type) {

	wchar_t str[80];
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		for (int index = 0; index < file.Get_Enemy_Motion_Count(enemy_type, Enemy_Status::E_Stop); index++) {
			wsprintf(str, file.Get_Enemy_Motion_Text(enemy_type, Enemy_Status::E_Stop), direction * file.Get_Enemy_Motion_Count(enemy_type, Enemy_Status::E_Move) + index + 1);
			stop_motion_bitmap[enemy_type][direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		for (int index = 0; index < file.Get_Enemy_Motion_Count(enemy_type, Enemy_Status::E_Move); index++) {
			wsprintf(str, file.Get_Enemy_Motion_Text(enemy_type, Enemy_Status::E_Move), direction * file.Get_Enemy_Motion_Count(enemy_type, Enemy_Status::E_Move) + index + 1);
			move_motion_bitmap[enemy_type][direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		for (int index = 0; index < file.Get_Enemy_Motion_Count(enemy_type, Enemy_Status::E_Attack); index++) {
			wsprintf(str, file.Get_Enemy_Motion_Text(enemy_type, Enemy_Status::E_Attack), direction * file.Get_Enemy_Motion_Count(enemy_type, Enemy_Status::E_Attack) + index + 1);
			attack_motion_bitmap[enemy_type][direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
	}

	GetObject(stop_motion_bitmap[enemy_type][0][0], sizeof(BITMAP), &motion_size[enemy_type]);
};

void Reset_Enemy_Bitmap(Enemy_Bitmap& e_bitmap, const File& file, const int& dungeon_type) {
	switch (dungeon_type)
	{
	case Map_Type::Dungeon1:
		for (int type = Enemy_Type::Bird; type <= Enemy_Type::Dark_Flower; type++)
			e_bitmap.Set_Motion_Bitmap(file, type);
		break;
	case Map_Type::Dungeon2:
		for (int type = Enemy_Type::Heke; type <= Enemy_Type::Grave; type++)
			e_bitmap.Set_Motion_Bitmap(file, type);
		break;
	case Map_Type::Dungeon3:
		for (int type = Enemy_Type::Riff; type <= Enemy_Type::Zeffel; type++)
			e_bitmap.Set_Motion_Bitmap(file, type);
		break;
	case Map_Type::Dungeon4:
		for (int type = Enemy_Type::Zarue; type <= Enemy_Type::Vagullion; type++)
			e_bitmap.Set_Motion_Bitmap(file, type);
		break;
	case Map_Type::Dungeon5:
		for (int type = Enemy_Type::Alnada; type <= Enemy_Type::Liagty3; type++)
			e_bitmap.Set_Motion_Bitmap(file, type);
		break;
	case Map_Type::Dungeon6:
		for (int type = Enemy_Type::Dularn; type <= Enemy_Type::Dularn; type++)
			e_bitmap.Set_Motion_Bitmap(file, type);
		break;
	default:
		break;
	}
}