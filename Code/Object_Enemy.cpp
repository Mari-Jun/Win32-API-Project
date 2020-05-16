#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Info.h"
#include "Object_Enemy.h"


Enemy::~Enemy() {
	Delete_Class<Object_Info>(&o_info);
}

const Object_Info& Enemy::Get_Player_Info_Const() const {
	return *o_info;
}

Object_Info& Enemy::Get_Player_Info() const {
	return *o_info;
}

void Enemy::Create_Player_Info() {
	o_info = Create_Class<Object_Info>();
}

Practice_Enemy::~Practice_Enemy() {
	for (int index = 0; index < 4; index++)
		DeleteObject(stop_motion_bitmap[index]);
}

const BITMAP Practice_Enemy::Get_Bitmap_Size() const {
	return bitmap_size;
}

const HBITMAP Practice_Enemy::Get_Stop_Motion_Bitmap(const int& index) const {
	return stop_motion_bitmap[index];
}

void Practice_Enemy::Set_Stop_Motion() {
	for (int index = 0; index < 4; index++) {
		wchar_t str[100];
		wsprintf(str, _T(".\\BitMap\\Monster\\Practice\\Practice_Move%d.bmp"), index + 1);
		stop_motion_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	GetObject(stop_motion_bitmap[0], sizeof(BITMAP), &bitmap_size);
}