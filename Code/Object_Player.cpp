#include <windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Object_Player.h"

/*Defualt Player*/

Player::~Player() {
	Delete_Class(&p_info);
}

const int& Player::Get_Direction() const {
	return direction;
}

const Player_Info& Player::Get_Player_Info_Const() const {
	return *p_info;
}

Player_Info& Player::Get_Player_Info() const {
	return *p_info;
}

void Player::Set_Direction(const int& direction) {
	this->direction = direction;
}

void Player::Create_Player_Info() {
	p_info = Create_Class<Player_Info>();
}

void Player::Move_Player_Up(RECT c_rect, bool diagonal) {
	if (Get_YPos() - (Get_Player_Info_Const().Get_Speed() / ((diagonal) ? 2 : 1)) >= c_rect.top)
		Set_YPos(Get_YPos() - (Get_Player_Info_Const().Get_Speed() / ((diagonal) ? 2 : 1)));
}

void Player::Move_Player_Down(RECT c_rect, bool diagonal) {
	if (Get_YPos() + Get_Height() + (Get_Player_Info_Const().Get_Speed() / ((diagonal) ? 2 : 1)) <= c_rect.bottom)
		Set_YPos(Get_YPos() + (Get_Player_Info_Const().Get_Speed() / ((diagonal) ? 2 : 1)));
}

void Player::Move_Player_Left(RECT c_rect, bool diagonal) {
	if (Get_XPos() - (Get_Player_Info_Const().Get_Speed() / ((diagonal) ? 2 : 1)) >= c_rect.left)
		Set_XPos(Get_XPos() - (Get_Player_Info_Const().Get_Speed() / ((diagonal) ? 2 : 1)));
}

void Player::Move_Player_Right(RECT c_rect, bool diagonal) {
	if (Get_XPos() + Get_Width() + (Get_Player_Info_Const().Get_Speed() / ((diagonal) ? 2 : 1)) <= c_rect.right)
		Set_XPos(Get_XPos() + (Get_Player_Info_Const().Get_Speed() / ((diagonal) ? 2 : 1)));
}

void Reset_Player(Player& player, RECT c_rect, const int& width, const int& height) {
	//юс╫ц..
	Reset_Object(player, c_rect.right / 2, c_rect.bottom / 2, width, height);
	player.Create_Player_Info();
}

void Move_Player(Player& player, RECT c_rect) {
	bool KeyUp = (GetAsyncKeyState(VK_UP) & 0x8000);
	bool KeyDown = (GetAsyncKeyState(VK_DOWN) & 0x8000);
	bool KeyLeft = (GetAsyncKeyState(VK_LEFT) & 0x8000);
	bool KeyRight = (GetAsyncKeyState(VK_RIGHT) & 0x8000);

	if (KeyUp && KeyRight) {
		player.Move_Player_Up(c_rect, true);
		player.Move_Player_Right(c_rect, true);
		player.Set_Direction(Object_Direction::UpRight);
	}
	else if (KeyUp && KeyLeft) {
		player.Move_Player_Up(c_rect, true);
		player.Move_Player_Left(c_rect, true);
		player.Set_Direction(Object_Direction::UpLeft);
	}
	else if (KeyDown && KeyRight) {
		player.Move_Player_Down(c_rect, true);
		player.Move_Player_Right(c_rect, true);
		player.Set_Direction(Object_Direction::DownRight);
	}
	else if (KeyDown && KeyLeft) {
		player.Move_Player_Down(c_rect, true);
		player.Move_Player_Left(c_rect, true);
		player.Set_Direction(Object_Direction::DownLeft);
	}
	else if (KeyUp && !KeyDown) {
		player.Move_Player_Up(c_rect, false);
		player.Set_Direction(Object_Direction::Up);
	}
	else if (KeyDown && !KeyUp) {
		player.Move_Player_Down(c_rect, false);
		player.Set_Direction(Object_Direction::Down);
	}
	else if (KeyRight && !KeyLeft) {
		player.Move_Player_Right(c_rect, false);
		player.Set_Direction(Object_Direction::Right);
	}
	else if (KeyLeft && !KeyRight) {
		player.Move_Player_Left(c_rect, false);
		player.Set_Direction(Object_Direction::Left);
	}


}

/*Warrior Player*/

Warrior::~Warrior() {
	for (int i = 0; i < 8; i++)
		DeleteObject(stop_motion_bitmap[i]);
}

const HBITMAP Warrior::Get_Stop_Motion(int direction) const {
	return stop_motion_bitmap[direction];
}

void Warrior::Set_Stop_Motion() {
	for (int direction = Object_Direction::Up; direction <= Object_Direction::UpLeft; direction++) {
		wchar_t str[100];
		wsprintf(str, _T(".\\BitMap\\Warrior\\Warrior_Stop_%d.bmp"), direction);
		stop_motion_bitmap[direction] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	GetObject(stop_motion_bitmap[0], sizeof(BITMAP), &stop_motion_size);
}

const BITMAP Warrior::Get_Stop_Motion_Size() const {
	return stop_motion_size;
}

void Reset_Warrior(Warrior& warrior, RECT c_rect) {
	warrior.Set_Stop_Motion();
	Reset_Player(warrior, c_rect, warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight);
	Reset_Player_Info(warrior.Get_Player_Info(), 100, 100, 0);
}

void Paint_Warrior(HDC hdc, HDC bitdc, Warrior& warrior) {
	SelectObject(bitdc, warrior.Get_Stop_Motion(warrior.Get_Direction()));
	
	TransparentBlt(hdc, warrior.Get_XPos(), warrior.Get_YPos(), warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight, bitdc, 0, 0, warrior.Get_Stop_Motion_Size().bmWidth, warrior.Get_Stop_Motion_Size().bmHeight, RGB(255, 255, 255));
}