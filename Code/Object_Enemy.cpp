#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include "Source.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Object_Enemy.h"
#include "Object_Skill.h"
#include "Hitting_Range.h"
#include "File.h"
#include "Camera.h"

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

void Enemy::Create_Enemy_Skill(const File& file) {
	e_skill = Create_Class<Enemy_Skill>();
	Reset_Enemy_Skill(*e_skill, file, Get_Enemy_Type());
}


void Enemy::Set_Motion_Bitmap(const File& file) {

	wchar_t str[80];
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		for (int index = 0; index < file.Get_Enemy_Motion_Count(Get_Enemy_Type(), Enemy_Status::E_Stop); index++) {
			wsprintf(str, file.Get_Enemy_Motion_Text(Get_Enemy_Type(), Enemy_Status::E_Stop), direction * file.Get_Enemy_Motion_Count(Get_Enemy_Type(), Enemy_Status::E_Move) + index + 1);
			stop_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			//wcout << str << endl;
		}
		for (int index = 0; index < file.Get_Enemy_Motion_Count(Get_Enemy_Type(), Enemy_Status::E_Move); index++) {
			wsprintf(str, file.Get_Enemy_Motion_Text(Get_Enemy_Type(), Enemy_Status::E_Move), direction * file.Get_Enemy_Motion_Count(Get_Enemy_Type(), Enemy_Status::E_Move) + index + 1);
			move_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			//wcout << str << endl;
		}
		for (int index = 0; index < file.Get_Enemy_Motion_Count(Get_Enemy_Type(), Enemy_Status::E_Attack); index++) {
			wsprintf(str, file.Get_Enemy_Motion_Text(Get_Enemy_Type(), Enemy_Status::E_Attack), direction * file.Get_Enemy_Motion_Count(Get_Enemy_Type(), Enemy_Status::E_Attack) + index + 1);
			attack_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			//wcout << str << endl;
		}
	}

	GetObject(stop_motion_bitmap[0][0], sizeof(BITMAP), &motion_size);
	GetObject(attack_effect_bitmap[0][0], sizeof(BITMAP), &attack_effect_size);
};

void Reset_Enemy(Enemy& enemy, const File& file, const int& enemy_type) {
	enemy.Set_Enemy_Type(enemy_type);
	enemy.Set_Attack_Delay(0);
	enemy.Set_Motion_Bitmap(file);
	enemy.Create_Enemy_Skill(file);

	enemy.Create_Object_Info();
	Reset_Object_Info(enemy.Get_Object_Info(), file.Get_Enemy_Object_Info(enemy_type, 0), file.Get_Enemy_Object_Info(enemy_type, 1),
		file.Get_Enemy_Object_Info(enemy_type, 2), file.Get_Enemy_Object_Info(enemy_type, 3),
		file.Get_Enemy_Object_Info(enemy_type, 4), file.Get_Enemy_Object_Info(enemy_type, 5));
	enemy.Set_Crash_Width(file.Get_Enemy_Object_Info(enemy_type, 6));
	enemy.Set_Crash_Height(file.Get_Enemy_Object_Info(enemy_type, 7));

	enemy.Set_Attack_Reaction_Range(file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(),Attack_Type::A_Attack,Attack_Info::Attack_Reaction_Range),
		file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), Attack_Type::A_SkillQ, Attack_Info::Attack_Reaction_Range),
		file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), Attack_Type::A_SkillW, Attack_Info::Attack_Reaction_Range),
		file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), Attack_Type::A_SkillE, Attack_Info::Attack_Reaction_Range),
		file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), Attack_Type::A_SkillR, Attack_Info::Attack_Reaction_Range));
}

void Paint_Enemy(HDC hdc, HDC bitdc, const File& file, const Enemy& enemy, const Camera& camera, const RECT c_rect) {

	if (camera.Get_Cam_Left() <= enemy.Get_XPos() + enemy.Get_Width() &&
		camera.Get_Cam_Left() + c_rect.right >= enemy.Get_XPos() &&
		camera.Get_Cam_Top() <= enemy.Get_YPos() + enemy.Get_Height() &&
		camera.Get_Cam_Top() + c_rect.bottom >= enemy.Get_YPos()) {
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

		Paint_Enemy_Detail(hdc, bitdc, enemy, file);

		//Rectangle(hdc, enemy.Get_XPos(), enemy.Get_YPos() + enemy.Get_Height() - enemy.Get_Crash_Height(), enemy.Get_XPos() + enemy.Get_Crash_Width(), enemy.Get_YPos() + enemy.Get_Height());
	}
}

void Paint_Enemy_Detail(HDC hdc, HDC bitdc, const Enemy& enemy, const File& file) {

	for (int index = 0; index < 20; index++) {
		if (&enemy.Get_Hit_Range_P_Const(index) != NULL) {
			Paint_Hitting_Range(hdc, bitdc, enemy.Get_Hit_Range_P_Const(index));
		}
	}

	switch (enemy.Get_Status())
	{
	case Enemy_Status::E_Stop:
		SelectObject(bitdc, enemy.Get_Stop_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 3 % file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), Enemy_Status::E_Stop)));
		break;
	case Enemy_Status::E_Move:
		SelectObject(bitdc, enemy.Get_Move_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 3 % file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), Enemy_Status::E_Move)));
		break;
	case Enemy_Status::E_Attack:
		SelectObject(bitdc, enemy.Get_Attack_Motion(enemy.Get_Direction(), enemy.Get_Ani_Count() / 3 % file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), Enemy_Status::E_Attack)));
		break;
	case Enemy_Status::E_SkillQ:
		SelectObject(bitdc, enemy.Get_Enemy_Skill_Const().Get_Skill_Motion_Bitmap(Skill_Type::Skill_Q, enemy.Get_Direction(), enemy.Get_Ani_Count() / 3 % file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), Enemy_Status::E_SkillQ)));
		break;
	case Enemy_Status::E_SkillW:
		SelectObject(bitdc, enemy.Get_Enemy_Skill_Const().Get_Skill_Motion_Bitmap(Skill_Type::Skill_W, enemy.Get_Direction(), enemy.Get_Ani_Count() / 3 % file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), Enemy_Status::E_SkillW)));
		break;
	case Enemy_Status::E_SkillE:
		SelectObject(bitdc, enemy.Get_Enemy_Skill_Const().Get_Skill_Motion_Bitmap(Skill_Type::Skill_E, enemy.Get_Direction(), enemy.Get_Ani_Count() / 3 % file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), Enemy_Status::E_SkillE)));
		break;
	case Enemy_Status::E_SkillR:
		SelectObject(bitdc, enemy.Get_Enemy_Skill_Const().Get_Skill_Motion_Bitmap(Skill_Type::Skill_R, enemy.Get_Direction(), enemy.Get_Ani_Count() / 3 % file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), Enemy_Status::E_SkillR)));
		break;
	default:
		break;
	}
	TransparentBlt(hdc, enemy.Get_XPos() + file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), 7), enemy.Get_YPos() + file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), 8), enemy.Get_Width(), enemy.Get_Height(), bitdc, 0, 0, enemy.Get_Width(), enemy.Get_Height(), RGB(150, 150, 150));	

	Paint_Hitting_Damage(hdc, enemy, file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), 8));
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