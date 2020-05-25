#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Object_Enemy.h"
//임시로
#include "Hitting_Range.h"

Enemy::~Enemy() {
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		for (int index = 0; index < 10; index++) {
			DeleteObject(stop_motion_bitmap[direction][index]);
			DeleteObject(move_motion_bitmap[direction][index]);
		}
		for (int index = 0; index < 20; index++) {
			DeleteObject(attack_motion_bitmap[direction][index]);
			DeleteObject(skill_motion1_bitmap[direction][index]);
		}
	}
}


const int& Enemy::Get_Enemy_Type() const {
	return enemy_type;
}

const int& Enemy::Get_Attack_Delay() const {
	return attack_delay;
}

const int& Enemy::Get_Skill_Delay(const int& index) const {
	return skill_delay[index];
}

const BITMAP& Enemy::Get_Motion_Size() const {
	return motion_size;
}

const HBITMAP& Enemy::Get_Stop_Motion(const int& direction, const int& index) const {
	return stop_motion_bitmap[direction][index];
}

const HBITMAP& Enemy::Get_Move_Motion(const int& direction, const int& index) const {
	return move_motion_bitmap[direction][index];
}

const HBITMAP& Enemy::Get_Attack_Motion(const int& direction, const int& index) const {
	return attack_motion_bitmap[direction][index];
}

const HBITMAP& Enemy::Get_Skill_Motion1(const int& direction, const int& index) const {
	return skill_motion1_bitmap[direction][index];
}


void Enemy::Set_Enemy_Type(const int& enemy_type) {
	this->enemy_type = enemy_type;
}

void Enemy::Set_Attack_Delay(const int& delay) {
	attack_delay = delay;
}

void Enemy::Set_Skill_Delay(const int& index, const int& delay) {
	skill_delay[index] = delay;
}

void Enemy::Set_Motion_Bitmap() {
	switch (Get_Enemy_Type())
	{
	case Enemy_Type::Bird:
		for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
			for (int index = 0; index < 8; index++) {
				wchar_t str[50];
				wsprintf(str, _T(".\\BitMap\\Monster\\M1\\Move\\Bird_Move%d.bmp"), direction * 8 + index + 1);
				//가만히 있을 경우, 움직이는 경우의 모션이 같다.
				stop_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				move_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				wsprintf(str, _T(".\\BitMap\\Monster\\M1\\Attack\\Bird_Attack%d.bmp"), direction * 8 + index + 1);
				attack_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
		}
		GetObject(stop_motion_bitmap[0][0], sizeof(BITMAP), &motion_size);
		break;
	default:
		break;
	}
}

void Reset_Enemy(Enemy& enemy, const int& enemy_type) {
	enemy.Set_Enemy_Type(enemy_type);
	enemy.Set_Attack_Delay(0);
	for (int index = 0; index < 5; index++)
		enemy.Set_Skill_Delay(index, 0);
	enemy.Set_Motion_Bitmap();

	switch (enemy_type)
	{
	case Enemy_Type::Bird:
		enemy.Create_Object_Info();
		Reset_Object_Info(enemy.Get_Object_Info(), 1, 200, 0, 30, 5, 0);
		enemy.Set_Crash_Width(80);
		enemy.Set_Crash_Height(80);
		break;
	default:
		break;
	}
}

void Paint_Enemy(HDC hdc, HDC bitdc, const Enemy& enemy) {

	/*for (int index = 0; index < 20; index++) {
		if (&enemy.Get_Hit_Range_P_Const(index) != NULL) {
			POINT pos[4];
			pos[0] = enemy.Get_Hit_Range_P_Const(index).Get_Pos(0);
			pos[1] = enemy.Get_Hit_Range_P_Const(index).Get_Pos(1);
			pos[2] = enemy.Get_Hit_Range_P_Const(index).Get_Pos(2);
			pos[3] = enemy.Get_Hit_Range_P_Const(index).Get_Pos(3);

			Polygon(hdc, pos, 4);
		}
	}*/

	switch (enemy.Get_Enemy_Type())
	{
	case Enemy_Type::Bird:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Stop:
			SelectObject(bitdc, enemy.Get_Stop_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % 8));
			break;
		case Enemy_Status::E_Move:
			SelectObject(bitdc, enemy.Get_Move_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % 8));
			break;
		case Enemy_Status::E_Attack:
			SelectObject(bitdc, enemy.Get_Attack_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % 8));
			break;
		default:
			break;
		}
		TransparentBlt(hdc, enemy.Get_XPos() - 10, enemy.Get_YPos(), enemy.Get_Width(), enemy.Get_Height(), bitdc, 0, 0, enemy.Get_Width(), enemy.Get_Height(), RGB(255, 255, 255));
		break;
	default:
		break;
	}

	Paint_Hitting_Damage(hdc, enemy);
	//Rectangle(hdc, enemy.Get_XPos(), enemy.Get_YPos() + enemy.Get_Height() - enemy.Get_Crash_Height(), enemy.Get_XPos() + enemy.Get_Crash_Width(), enemy.Get_YPos() + enemy.Get_Height());

	
}