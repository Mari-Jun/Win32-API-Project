#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Object_Enemy.h"


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
	Reset_Move_Object(p_enemy, 1100, 400, p_enemy.Get_Bitmap_Size().bmWidth, p_enemy.Get_Bitmap_Size().bmHeight, 0);
	Reset_Object_Info(p_enemy.Get_Object_Info(), 1, (1 << 30), 0, 0);
	p_enemy.Set_Crash_Width(60);
	p_enemy.Set_Crash_Height(60);
}

void Paint_Practice_Enemy(HDC hdc, HDC bitdc, const Practice_Enemy& p_enemy) {
	SelectObject(bitdc, p_enemy.Get_Stop_Motion_Bitmap(p_enemy.Get_Ani_Count()));
	TransparentBlt(hdc, p_enemy.Get_XPos() - 10, p_enemy.Get_YPos(), p_enemy.Get_Width(), p_enemy.Get_Height(), bitdc, 0, 0, p_enemy.Get_Width(), p_enemy.Get_Height(), RGB(255, 255, 255));
	Paint_Hitting_Damage(hdc, p_enemy);
	//Rectangle(hdc, p_enemy.Get_XPos(), p_enemy.Get_YPos() + p_enemy.Get_Height() - p_enemy.Get_Crash_Height(), p_enemy.Get_XPos() + p_enemy.Get_Crash_Width(), p_enemy.Get_YPos() + p_enemy.Get_Height());
}