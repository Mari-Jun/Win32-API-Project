#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Skill.h"
#include "Object_Player.h"
#include "Object_Info.h"

Object_Skill::~Object_Skill() {
	for (int direction = 0; direction < 8; direction++) {
		for (int index = 0; index < 20; index++) {
			DeleteObject(skill1_motion_bitmap[direction][index]);
			DeleteObject(skill2_motion_bitmap[direction][index]);
			DeleteObject(skill3_motion_bitmap[direction][index]);
			DeleteObject(skill4_motion_bitmap[direction][index]);
		}
	}
}


const HBITMAP& Object_Skill::Get_Skill1_Motion_Bitmap(const int& direction, const int& index) const {
	return skill1_motion_bitmap[direction][index];
}

const HBITMAP& Object_Skill::Get_Skill2_Motion_Bitmap(const int& direction, const int& index) const {
	return skill2_motion_bitmap[direction][index];
}

const HBITMAP& Object_Skill::Get_Skill3_Motion_Bitmap(const int& direction, const int& index) const {
	return skill3_motion_bitmap[direction][index];
}

const HBITMAP& Object_Skill::Get_Skill4_Motion_Bitmap(const int& direction, const int& index) const {
	return skill4_motion_bitmap[direction][index];
}

const int& Object_Skill::Get_Current_Delay(const int& index) const {
	return current_delay[index];
}

const int& Object_Skill::Get_Skill_Delay(const int& index) const {
	return skill_delay[index];
}

void Object_Skill::Set_Bitmap(const int& skill, const int& direction, const int& index, const HBITMAP& bitmap) {
	switch (skill)
	{
	case 0:
		skill1_motion_bitmap[direction][index] = bitmap;
		break;
	case 1:
		skill2_motion_bitmap[direction][index] = bitmap;
		break;
	case 2:
		skill3_motion_bitmap[direction][index] = bitmap;
		break;
	case 3:
		skill4_motion_bitmap[direction][index] = bitmap;
		break;
	default:
		break;
	}
}

void  Object_Skill::Set_Current_Delay(const int& index, const int& current_delay) {
	this->current_delay[index] = current_delay;
}

void  Object_Skill::Set_Skill_Delay(const int& index, const int& skill_delay) {
	this->skill_delay[index] = skill_delay;
}

Player_Skill::~Player_Skill() {
	for (int index = 0; index < 4; index++)
		DeleteObject(skill_bitmap);
}

const BITMAP& Player_Skill::Get_Skill_Bitmap_Size() const {
	return skill_bitmap_size;
}

const HBITMAP& Player_Skill::Get_Skill_Bitmap(const int& index) const {
	return skill_bitmap[index];
}

const int& Player_Skill::Get_Use_Mp(const int& index) const {
	return use_mp[index];
}

void Player_Skill::Set_Skill_Bitmap(const int& class_type) {
	switch (class_type)
	{
	case Class_Type::Warrior:
		TCHAR str[50];
		for (int index = 0; index < 4; index++) {
			wsprintf(str, _T(".\\BitMap\\Warrior\\Icon\\Skill%d.bmp"), index + 1);
			skill_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
		break;
	default:
		break;
	}
	GetObject(skill_bitmap[0], sizeof(BITMAP), &skill_bitmap_size);
}

void Player_Skill::Set_Motion_Bitmap(const int& class_type) {
	
	switch (class_type)
	{
	case Class_Type::Warrior:
		TCHAR str[50];
		for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
			for (int index = 0; index < 18; index++) {
				wsprintf(str, _T(".\\BitMap\\Warrior\\Skill1\\Warrior_SkillQ%d.bmp"), direction * 18 + index + 1);
				Set_Bitmap(0, direction, index, (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			}
			for (int index = 0; index < 10; index++) {
				wsprintf(str, _T(".\\BitMap\\Warrior\\Skill2\\Warrior_SkillW%d.bmp"), direction * 10 + index + 1);
				Set_Bitmap(1, direction, index, (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			}
			for (int index = 0; index < 17; index++) {
				wsprintf(str, _T(".\\BitMap\\Warrior\\Skill3\\Warrior_SkillE%d.bmp"), direction * 17 + index + 1);
				Set_Bitmap(2, direction, index, (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			}
			for (int index = 0; index < 13; index++) {
				wsprintf(str, _T(".\\BitMap\\Warrior\\Skill4\\Warrior_SkillR%d.bmp"), direction * 13 + index + 1);
				Set_Bitmap(3, direction, index, (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
			}
		}
		break;
	default:
		break;
	}
}

void Player_Skill::Set_Use_Mp(const int& class_type) {
	switch (class_type)
	{
	case Class_Type::Warrior:
		use_mp[Skill_Type::Skill_Q] = 15;
		use_mp[Skill_Type::Skill_W] = 10;
		use_mp[Skill_Type::Skill_E] = 25;
		use_mp[Skill_Type::Skill_R] = 20;
		break;
	default:
		break;
	}
}

void Player_Skill::Set_Delay(const int& class_type) {
	switch (class_type)
	{
	case Class_Type::Warrior:
		Set_Skill_Delay(Skill_Type::Skill_Q, 500);
		Set_Skill_Delay(Skill_Type::Skill_W, 400);
		Set_Skill_Delay(Skill_Type::Skill_E, 1000);
		Set_Skill_Delay(Skill_Type::Skill_R, 750);
		break;
	default:
		break;
	}
}

void Reset_Player_Skill(Player_Skill& p_skill, const int& class_type) {
	p_skill.Set_Skill_Bitmap(class_type);
	p_skill.Set_Motion_Bitmap(class_type);
	p_skill.Set_Use_Mp(class_type);
	p_skill.Set_Delay(class_type);
	for (int index = Skill_Type::Skill_Q; index <= Skill_Type::Skill_R; index++)
		p_skill.Set_Current_Delay(index, 0);
}

void Paint_Player_Skill_Icon(HDC hdc, HDC bitdc, const Player_Skill& p_skill, const RECT c_rect) {
	TCHAR text[3];
	for (int index = Skill_Type::Skill_Q; index <= Skill_Type::Skill_R; index++) {
		SelectObject(bitdc, p_skill.Get_Skill_Bitmap(index));
		//스킬 쿨다운의 비율에 따라 가로 사이즈를 정합니다.
		TransparentBlt(hdc, c_rect.right - 461 + 57 * index, c_rect.bottom - 60, (p_skill.Get_Skill_Bitmap_Size().bmWidth * (p_skill.Get_Skill_Delay(index) - p_skill.Get_Current_Delay(index)) / p_skill.Get_Skill_Delay(index)), p_skill.Get_Skill_Bitmap_Size().bmHeight,
			bitdc, 0, 0, (p_skill.Get_Skill_Bitmap_Size().bmWidth * (p_skill.Get_Skill_Delay(index) - p_skill.Get_Current_Delay(index)) / p_skill.Get_Skill_Delay(index)), p_skill.Get_Skill_Bitmap_Size().bmHeight, RGB(17, 33, 42));
		//Mp cost값을 화면에 띄웁니다.
		wsprintf(text, _T("%2d"), p_skill.Get_Use_Mp(index));
		TextOut(hdc, c_rect.right - 432 + 57 * index, c_rect.bottom - 30, text, _tcslen(text));
	}
}

//스킬 단축키를 눌렀을 때 작동하는 함수
void Change_Player_Status_To_Skill(Player& player, const WPARAM wParam) {
	if (player.Get_Status() == Player_Status::Stop || player.Get_Status() == Player_Status::Move || player.Get_Status() == Player_Status::Run) {
		switch (wParam)
		{
		case 'q':
		case 'Q':
			if (player.Get_Object_Info_Const().Get_Mp() >= player.Get_Player_Skill_Const().Get_Use_Mp(Skill_Type::Skill_Q) && player.Get_Player_Skill_Const().Get_Current_Delay(Skill_Type::Skill_Q) == 0) 
				Change_Player_Info_Use_Skill(player, Player_Status::SkillQ, Skill_Type::Skill_Q);
			break;
		case 'w':
		case 'W':
			if (player.Get_Object_Info_Const().Get_Mp() >= player.Get_Player_Skill_Const().Get_Use_Mp(Skill_Type::Skill_W) && player.Get_Player_Skill_Const().Get_Current_Delay(Skill_Type::Skill_W) == 0) 
				Change_Player_Info_Use_Skill(player, Player_Status::SkillW, Skill_Type::Skill_W);
			break;
		case 'e':
		case 'E':
			if (player.Get_Object_Info_Const().Get_Mp() >= player.Get_Player_Skill_Const().Get_Use_Mp(Skill_Type::Skill_E) && player.Get_Player_Skill_Const().Get_Current_Delay(Skill_Type::Skill_E) == 0) 
				Change_Player_Info_Use_Skill(player, Player_Status::SkillE, Skill_Type::Skill_E);
			break;
		case 'r':
		case 'R':
			if (player.Get_Object_Info_Const().Get_Mp() >= player.Get_Player_Skill_Const().Get_Use_Mp(Skill_Type::Skill_R) && player.Get_Player_Skill_Const().Get_Current_Delay(Skill_Type::Skill_R) == 0) 
				Change_Player_Info_Use_Skill(player, Player_Status::SkillR, Skill_Type::Skill_R);
			break;
		default:
			break;
		}
	}
}

//스킬이 사용되었을때 플레이어 정보를 바꾸는 함수
void Change_Player_Info_Use_Skill(Player& player, const int& status_type, const int& skill_type) {
	player.Set_Status(status_type);
	player.Set_Ani_Count(0);
	player.Get_Object_Info().Set_Mp(player.Get_Object_Info_Const().Get_Mp() - player.Get_Player_Skill_Const().Get_Use_Mp(skill_type));
	player.Get_Player_Skill().Set_Current_Delay(skill_type, player.Get_Player_Skill_Const().Get_Skill_Delay(skill_type));
}