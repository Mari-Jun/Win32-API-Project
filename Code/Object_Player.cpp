#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "Source.h"
#include "Map_Main.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Object_Player.h"
#include "Object_Npc.h"
#include "Hitting_Range.h"

/*Defualt Player*/

Player::~Player() {
	Delete_Class<Player_Info>(&p_info);
}

const Player_Info& Player::Get_Player_Info_Const() const {
	return *p_info;
}

Player_Info& Player::Get_Player_Info() const {
	return *p_info;
}

void Player::Create_Player_Info() {
	p_info = Create_Class<Player_Info>();
}

void Reset_Player(Player& player, const int& width, const int& height) {
	Reset_Move_Object(player, 400, 500, width, height);
	player.Create_Player_Info();
}

/*Warrior Player*/

Warrior::~Warrior() {
	for (int i = 0; i < 8; i++) {
		DeleteObject(stop_motion_bitmap[i]);
		for (int j = 0; j < 8; j++)
			DeleteObject(move_motion_bitmap[i][j]);
	}
}

const HBITMAP Warrior::Get_Stop_Motion(const int& direction) const {
	return stop_motion_bitmap[direction];
}

const BITMAP Warrior::Get_Motion_Size() const {
	return motion_size;
}

const HBITMAP Warrior::Get_Move_Motion(const int& direction, const int& index) const {
	return move_motion_bitmap[direction][index];
}

const HBITMAP Warrior::Get_Attack_Motion(const int& direction, const int& index) const {
	return attack_motion_bitmap[direction][index];
}


void Warrior::Set_Stop_Motion() {
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		wchar_t str[100];
		wsprintf(str, _T(".\\BitMap\\Warrior\\Stop\\Warrior_Stop_%d.bmp"), direction + 1);
		stop_motion_bitmap[direction] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	GetObject(stop_motion_bitmap[0], sizeof(BITMAP), &motion_size);
}

void Warrior::Set_Move_Motion() {
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		for (int index = 0; index < 8; index++) {
			wchar_t str[100];
			wsprintf(str, _T(".\\BitMap\\Warrior\\Move\\Warrior_Move%d.bmp"), direction * 8 + index + 1);
			move_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
	}
}

void Warrior::Set_Attack_Motion() {
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		for (int index = 0; index < 10; index++) {
			wchar_t str[100];
			wsprintf(str, _T(".\\BitMap\\Warrior\\Attack\\Warrior_Attack_%d.bmp"), direction * 10 + index + 1369);
			attack_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
	}
}

void Reset_Warrior(Warrior& warrior) {
	warrior.Set_Stop_Motion();
	warrior.Set_Move_Motion();
	warrior.Set_Attack_Motion();
	Reset_Player(warrior, warrior.Get_Motion_Size().bmWidth, warrior.Get_Motion_Size().bmHeight);
	Reset_Player_Info(warrior.Get_Player_Info(), 100, 100, 10, 0, 8);

	//지면 충돌 크기는 비트맵 객체마다 다 다르기때문에 일일히 객체가 생성때 설정을 해주어야한다.
	warrior.Set_Crash_Height(30);
	warrior.Set_Crash_Width(60);
}

void Paint_Warrior(HDC hdc, HDC bitdc, const Warrior& warrior) {

	switch (warrior.Get_Status())
	{
	case Player_Status::Stop:
	case Player_Status::Interaction:
		SelectObject(bitdc, warrior.Get_Stop_Motion(warrior.Get_Direction()));
		TransparentBlt(hdc, warrior.Get_XPos() - 45, warrior.Get_YPos(), warrior.Get_Motion_Size().bmWidth, warrior.Get_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Motion_Size().bmWidth, warrior.Get_Motion_Size().bmHeight, RGB(255, 255, 255));
		break;
	case Player_Status::Move:
		SelectObject(bitdc, warrior.Get_Move_Motion(warrior.Get_Direction(), warrior.Get_Ani_Count() / 2 % 8));
		TransparentBlt(hdc, warrior.Get_XPos() - 45, warrior.Get_YPos(), warrior.Get_Motion_Size().bmWidth, warrior.Get_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Motion_Size().bmWidth, warrior.Get_Motion_Size().bmHeight, RGB(255, 255, 255));
		break;
	case Player_Status::Attack:
		SelectObject(bitdc, warrior.Get_Attack_Motion(warrior.Get_Direction(), warrior.Get_Ani_Count() / 2 % 10));
		TransparentBlt(hdc, warrior.Get_XPos() - 45, warrior.Get_YPos(), warrior.Get_Motion_Size().bmWidth, warrior.Get_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Motion_Size().bmWidth, warrior.Get_Motion_Size().bmHeight, RGB(255, 255, 255));
		break;
	default:
		break;
	}

	for (int index = 0; index < 20; index++) {
		if (&warrior.Get_Hit_Range_P_Const(index) != NULL) {
			POINT pos[4];
			pos[0] = warrior.Get_Hit_Range_P_Const(index).Get_Pos(0);
			pos[1] = warrior.Get_Hit_Range_P_Const(index).Get_Pos(1);
			pos[2] = warrior.Get_Hit_Range_P_Const(index).Get_Pos(2);
			pos[3] = warrior.Get_Hit_Range_P_Const(index).Get_Pos(3);

			Polygon(hdc, pos, 4);
		}
		
	}
}