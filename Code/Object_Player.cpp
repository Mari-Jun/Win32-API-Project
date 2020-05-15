#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "Source.h"
#include "Map_Main.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Object_Player.h"

/*Defualt Player*/

Player::~Player() {
	Delete_Class<Player_Info>(&p_info);
}

const int& Player::Get_Status() const {
	return status;
}

const Player_Info& Player::Get_Player_Info_Const() const {
	return *p_info;
}

Player_Info& Player::Get_Player_Info() const {
	return *p_info;
}

void Player::Set_Status(const int& status) {
	this->status = status;
}

void Player::Create_Player_Info() {
	p_info = Create_Class<Player_Info>();
}

void Reset_Player(Player& player, const int& width, const int& height) {
	//임시..
	Reset_Move_Object(player, 400, 500, width, height);
	player.Set_Status(Object_Status::Stop);
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

const BITMAP Warrior::Get_Stop_Motion_Size() const {
	return stop_motion_size;
}

const HBITMAP Warrior::Get_Move_Motion(const int& direction, const int& index) {
	return move_motion_bitmap[direction][index];
}

const BITMAP Warrior::Get_Move_Motion_Size() const {
	return move_motion_size;
}

void Warrior::Set_Stop_Motion() {
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		wchar_t str[100];
		wsprintf(str, _T(".\\BitMap\\Warrior\\Stop\\Warrior_Stop_%d.bmp"), direction);
		stop_motion_bitmap[direction] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	GetObject(stop_motion_bitmap[0], sizeof(BITMAP), &stop_motion_size);
}

void Warrior::Set_Move_Motion() {
	for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
		for (int index = 0; index < 8; index++) {
			wchar_t str[100];
			wsprintf(str, _T(".\\BitMap\\Warrior\\Move\\Warrior_Move%d.bmp"), direction * 8 + index + 1);
			move_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
		}
	}
	GetObject(move_motion_bitmap[0][0], sizeof(BITMAP), &move_motion_size);
}



void Reset_Warrior(Warrior& warrior) {
	warrior.Set_Stop_Motion();
	warrior.Set_Move_Motion();
	Reset_Player(warrior, warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight);
	Reset_Player_Info(warrior.Get_Player_Info(), 100, 100, 0);

	//지면 충돌 크기는 비트맵 객체마다 다 다르기때문에 일일히 객체가 생성때 설정을 해주어야한다.
	warrior.Set_Crash_Height(30);
	warrior.Set_Crash_Width(60);
}

void Paint_Warrior(HDC hdc, HDC bitdc, Warrior& warrior) {

	switch (warrior.Get_Status())
	{
	case Object_Status::Stop:
		SelectObject(bitdc, warrior.Get_Stop_Motion(warrior.Get_Direction()));
		if (warrior.Get_Direction() == Object_Direction::DownRight)
			TransparentBlt(hdc, warrior.Get_XPos() + 10, warrior.Get_YPos(), warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight, RGB(255, 255, 255));
		else if(warrior.Get_Direction() == Object_Direction::UpLeft)
			TransparentBlt(hdc, warrior.Get_XPos() - 10, warrior.Get_YPos(), warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight, RGB(255, 255, 255));
		else
			TransparentBlt(hdc, warrior.Get_XPos(), warrior.Get_YPos(), warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight, RGB(255, 255, 255));
		break;
	case Object_Status::Move:
		SelectObject(bitdc, warrior.Get_Move_Motion(warrior.Get_Direction(), warrior.Get_Ani_Count() / 2 % 8));
		if (warrior.Get_Direction() == Object_Direction::Left || warrior.Get_Direction() == Object_Direction::DownLeft)
			TransparentBlt(hdc, warrior.Get_XPos()-20, warrior.Get_YPos(), warrior.Get_Move_Motion_Size().bmWidth, warrior.Get_Move_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Move_Motion_Size().bmWidth, warrior.Get_Move_Motion_Size().bmHeight, RGB(255, 255, 255));
		else if(warrior.Get_Direction() == Object_Direction::UpLeft)
			TransparentBlt(hdc, warrior.Get_XPos() - 10, warrior.Get_YPos(), warrior.Get_Move_Motion_Size().bmWidth, warrior.Get_Move_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Move_Motion_Size().bmWidth, warrior.Get_Move_Motion_Size().bmHeight, RGB(255, 255, 255));
		else if(warrior.Get_Direction() == Object_Direction::DownRight)
			TransparentBlt(hdc, warrior.Get_XPos() + 10, warrior.Get_YPos(), warrior.Get_Move_Motion_Size().bmWidth, warrior.Get_Move_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Move_Motion_Size().bmWidth, warrior.Get_Move_Motion_Size().bmHeight, RGB(255, 255, 255));
		else
			TransparentBlt(hdc, warrior.Get_XPos(), warrior.Get_YPos(), warrior.Get_Move_Motion_Size().bmWidth, warrior.Get_Move_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Move_Motion_Size().bmWidth, warrior.Get_Move_Motion_Size().bmHeight, RGB(255, 255, 255));
		break;
	default:
		break;
	}
}