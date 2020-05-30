#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include "Source.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Object_Enemy.h"
#include "Object_Skill.h"
#include "Hitting_Range.h"

using namespace std;

Enemy::~Enemy() {
	Delete_Class<Enemy_Skill>(&e_skill);
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		for (int index = 0; index < 10; index++) {
			DeleteObject(stop_motion_bitmap[direction][index]);
			DeleteObject(move_motion_bitmap[direction][index]);
		}
		for (int index = 0; index < 20; index++) {
			DeleteObject(attack_motion_bitmap[direction][index]);
			DeleteObject(attack_effect_bitmap[direction][index]);
		}
	}
}


const int& Enemy::Get_Enemy_Type() const {
	return enemy_type;
}

const int& Enemy::Get_Attack_Delay() const {
	return attack_delay;
}

const int& Enemy::Get_Attack_Reaction_Range(const int& index) const {
	return attack_reaction_range[index];
}

const Enemy_Skill& Enemy::Get_Enemy_Skill_Const() const {
	return *e_skill;
}

Enemy_Skill& Enemy::Get_Enemy_Skill() const {
	return *e_skill;
}

const BITMAP& Enemy::Get_Motion_Size() const {
	return motion_size;
}

const BITMAP& Enemy::Get_Attack_Effect_Size() const {
	return attack_effect_size;
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

const HBITMAP& Enemy::Get_Attack_Effect_Motion(const int& direction, const int& index) const {
	return attack_effect_bitmap[direction][index];
}

void Enemy::Set_Enemy_Type(const int& enemy_type) {
	this->enemy_type = enemy_type;
}

void Enemy::Set_Attack_Delay(const int& delay) {
	attack_delay = delay;
}

void Enemy::Set_Attack_Reaction_Range(const int& r1, const int& r2, const int& r3, const int& r4, const int& r5) {
	attack_reaction_range[0] = r1;
	attack_reaction_range[1] = r2;
	attack_reaction_range[2] = r3;
	attack_reaction_range[3] = r4;
	attack_reaction_range[4] = r5;
}

void Enemy::Create_Enemy_Skill() {
	e_skill = Create_Class<Enemy_Skill>();
	Reset_Enemy_Skill(*e_skill, Get_Enemy_Type());
}


void Enemy::Set_Motion_Bitmap() {
	TCHAR str[50];
	switch (Get_Enemy_Type())
	{
	case Enemy_Type::Bird:
		for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
			for (int index = 0; index < 8; index++) {
				wsprintf(str, _T(".\\BitMap\\Monster\\M1\\Move\\Bird_Move%d.bmp"), direction * 8 + index + 1);
				//가만히 있을 경우, 움직이는 경우의 모션이 같다.
				stop_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				move_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				wsprintf(str, _T(".\\BitMap\\Monster\\M1\\Attack\\Bird_Attack%d.bmp"), direction * 8 + index + 1);
				attack_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
		}
		break;
	case Enemy_Type::Zadrom:
		for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
			for (int index = 0; index < 8; index++) {
				wsprintf(str, _T(".\\BitMap\\Monster\\M2\\Stop\\Zadrom_Stop%d.bmp"), direction * 8 + index + 1);
				stop_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				wsprintf(str, _T(".\\BitMap\\Monster\\M2\\Move\\Zadrom_Move%d.bmp"), direction * 8 + index + 1);
				move_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				wsprintf(str, _T(".\\BitMap\\Monster\\M2\\Attack\\Zadrom_Attack%d.bmp"), direction * 8 + index + 1);
				attack_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}

		}
		break;
	case Enemy_Type::Tolpi:
		for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
			for (int index = 0; index < 8; index++) {
				wsprintf(str, _T(".\\BitMap\\Monster\\M3\\Stop\\Tolpi_Stop%d.bmp"), direction * 8 + index + 1);
				stop_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				move_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				wsprintf(str, _T(".\\BitMap\\Monster\\M3\\Attack\\Tolpi_Attack%d.bmp"), direction * 8 + index + 1);
				attack_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
				/*wsprintf(str, _T(".\\BitMap\\Monster\\M2\\Attack\\Zadrom_Attack%d.bmp"), direction * 8 + index + 1);
				attack_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);*/
			}	
		}
		break;
	default:
		break;
	}
	GetObject(stop_motion_bitmap[0][0], sizeof(BITMAP), &motion_size);
	GetObject(attack_effect_bitmap[0][0], sizeof(BITMAP), &attack_effect_size);
};

void Reset_Enemy(Enemy& enemy, const int& enemy_type) {
	enemy.Set_Enemy_Type(enemy_type);
	enemy.Set_Attack_Delay(0);
	enemy.Set_Motion_Bitmap();
	enemy.Create_Enemy_Skill();

	switch (enemy_type)
	{
	case Enemy_Type::Bird:
		enemy.Create_Object_Info();
		Reset_Object_Info(enemy.Get_Object_Info(), 1, 200, 0, 20, 0, 0);
		enemy.Set_Crash_Width(80);
		enemy.Set_Crash_Height(80);
		enemy.Set_Attack_Reaction_Range(50, 0, 0, 0, 0);
		break;
	case Enemy_Type::Zadrom:
		enemy.Create_Object_Info();
		Reset_Object_Info(enemy.Get_Object_Info(), 1, 150, 0, 30, 0, 0);
		enemy.Set_Crash_Width(50);
		enemy.Set_Crash_Height(50);
		enemy.Set_Attack_Reaction_Range(300, 0, 0, 0, 0);
		break;
	case Enemy_Type::Tolpi:
		enemy.Create_Object_Info();
		Reset_Object_Info(enemy.Get_Object_Info(), 1, 350, 0, 35, 5, 0);
		enemy.Set_Crash_Width(90);
		enemy.Set_Crash_Height(60);
		enemy.Set_Attack_Reaction_Range(100, 250, 0, 0, 0);
		break;
	default:
		break;
	}
}

void Paint_Enemy(HDC hdc, HDC bitdc, const Enemy& enemy) {

	for (int index = 0; index < 20; index++) {
		if (&enemy.Get_Hit_Range_P_Const(index) != NULL) {
			POINT pos[4];
			pos[0] = enemy.Get_Hit_Range_P_Const(index).Get_Pos(0);
			pos[1] = enemy.Get_Hit_Range_P_Const(index).Get_Pos(1);
			pos[2] = enemy.Get_Hit_Range_P_Const(index).Get_Pos(2);
			pos[3] = enemy.Get_Hit_Range_P_Const(index).Get_Pos(3);

			Polygon(hdc, pos, 4);
		}
	}
	
	switch (enemy.Get_Enemy_Type())
	{
	case Enemy_Type::Bird:
		Paint_Enemy_Detail(hdc, bitdc, enemy, 8, 8, 8, 0, 0, 0, 0, - 10, 0);
		break;
	case Enemy_Type::Zadrom:
		Paint_Enemy_Detail(hdc, bitdc, enemy, 8, 8, 8, 0, 0, 0, 0, - 35, 35);
		break;
	case Enemy_Type::Tolpi:
		Paint_Enemy_Detail(hdc, bitdc, enemy, 8, 8, 8, 8, 0, 0, 0, - 50, 20);
		break;
	default:
		break;
	}

	Paint_Hitting_Damage(hdc, enemy);

	//Rectangle(hdc, enemy.Get_XPos(), enemy.Get_YPos() + enemy.Get_Height() - enemy.Get_Crash_Height(), enemy.Get_XPos() + enemy.Get_Crash_Width(), enemy.Get_YPos() + enemy.Get_Height());

}

void Paint_Enemy_Detail(HDC hdc, HDC bitdc, const Enemy& enemy, const int& stop, const int& move, const int& attack, const int& skillq, const int& skillw, const int& skille, const int& skillr, const int& x_move, const int& y_move) {
	switch (enemy.Get_Status())
	{
	case Enemy_Status::E_Stop:
		SelectObject(bitdc, enemy.Get_Stop_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % stop));
		break;
	case Enemy_Status::E_Move:
		SelectObject(bitdc, enemy.Get_Move_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % move));
		break;
	case Enemy_Status::E_Attack:
		SelectObject(bitdc, enemy.Get_Attack_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % attack));
		break;
	case Enemy_Status::E_SkillQ:
		SelectObject(bitdc, enemy.Get_Enemy_Skill_Const().Get_Skill_Motion_Bitmap(0, enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % skillq));
		break;
	case Enemy_Status::E_SkillW:
		SelectObject(bitdc, enemy.Get_Enemy_Skill_Const().Get_Skill_Motion_Bitmap(1, enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % skillw));
		break;
	case Enemy_Status::E_SkillE:
		SelectObject(bitdc, enemy.Get_Enemy_Skill_Const().Get_Skill_Motion_Bitmap(2, enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % skille));
		break;
	case Enemy_Status::E_SkillR:
		SelectObject(bitdc, enemy.Get_Enemy_Skill_Const().Get_Skill_Motion_Bitmap(3, enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % skillr));
		break;
	default:
		break;
	}
	TransparentBlt(hdc, enemy.Get_XPos() + x_move, enemy.Get_YPos() + y_move, enemy.Get_Width(), enemy.Get_Height(), bitdc, 0, 0, enemy.Get_Width(), enemy.Get_Height(), RGB(255, 255, 255));

	//Paint_Enemy_Attack_Effect(hdc, bitdc, enemy, attack);
	for (int index = 0; index < 20; index++) {
		if (&enemy.Get_Hit_Range_P_Const(index) != NULL) {
			Paint_Hitting_Range(hdc, bitdc, enemy.Get_Hit_Range_P_Const(index));
		}
	}
}

/*void Paint_Enemy_Attack_Effect(HDC hdc, HDC bitdc, const Enemy& enemy, const int& effect) {
	SelectObject(bitdc, enemy.Get_Attack_Effect_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 2 % effect));
	for (int index = 0; index < 20; index++) {
		if (&enemy.Get_Hit_Range_P_Const(index) != NULL) {
			POINT pos;
			pos = { (enemy.Get_Hit_Range_P_Const(index).Get_Pos(0).x + enemy.Get_Hit_Range_P_Const(index).Get_Pos(2).x) / 2, (enemy.Get_Hit_Range_P_Const(index).Get_Pos(0).y + enemy.Get_Hit_Range_P_Const(index).Get_Pos(2).y) / 2 };
			TransparentBlt(hdc, pos.x - enemy.Get_Attack_Effect_Size().bmWidth / 2, pos.y - enemy.Get_Attack_Effect_Size().bmHeight / 2, enemy.Get_Attack_Effect_Size().bmWidth, enemy.Get_Attack_Effect_Size().bmHeight,
				bitdc, 0, 0, enemy.Get_Attack_Effect_Size().bmWidth, enemy.Get_Attack_Effect_Size().bmHeight, RGB(255, 255, 255));
		}
	}
}*/