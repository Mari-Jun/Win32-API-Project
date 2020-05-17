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

Object_Info& Enemy::Get_Enemy_Info() const {
	return *o_info;
}

void Enemy::Create_Enemy_Info() {
	o_info = Create_Class<Object_Info>();
}

void Reset_Enemy(Enemy& enemy, const int& hp, const int& attack, const int& defence, const int& speed) {
	enemy.Create_Enemy_Info();
	Reset_Object_Info(enemy.Get_Enemy_Info(), hp, attack, defence, speed);
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

void Reset_Practice_Enemy(Practice_Enemy& p_enemy) {
	p_enemy.Set_Stop_Motion();
	Reset_Enemy(p_enemy, (0 << 31), 0, 0, 0);
	Reset_Move_Object(p_enemy, 1100, 400, p_enemy.Get_Bitmap_Size().bmWidth, p_enemy.Get_Bitmap_Size().bmHeight);
	p_enemy.Set_Crash_Width(60);
	p_enemy.Set_Crash_Height(60);
}

void Paint_Practice_Enemy(HDC hdc, HDC bitdc, const Practice_Enemy& p_enemy) {
	SelectObject(bitdc, p_enemy.Get_Stop_Motion_Bitmap(p_enemy.Get_Ani_Count()));
	TransparentBlt(hdc, p_enemy.Get_XPos() - 10, p_enemy.Get_YPos(), p_enemy.Get_Width(), p_enemy.Get_Height(), bitdc, 0, 0, p_enemy.Get_Width(), p_enemy.Get_Height(), RGB(255, 255, 255));
}