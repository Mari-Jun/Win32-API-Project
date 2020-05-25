#include <windows.h>
#include <tchar.h>
#include <math.h>
#include "Source.h"
#include "Map_Main.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Object_Player.h"
#include "Object_Npc.h"
#include "Equipment.h"
#include "Hitting_Range.h"
#include "Item.h"

/*Player Player*/

Player::~Player() {
	Delete_Class<Player_Equipment>(&p_equip);
	Delete_Class<Player_Item>(&p_item);
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			DeleteObject(stop_motion_bitmap[i][j]);
			DeleteObject(move_motion_bitmap[i][j]);
			DeleteObject(run_motion_bitmap[i][j]);
		}
		for (int j = 0; j < 10; j++) {
			DeleteObject(attack_motion_bitmap[i][j]);
		}
	}
}

const int& Player::Get_Class_Type() const {
	return class_type;
}

const Player_Equipment& Player::Get_Player_Equipment_Const() const {
	return *p_equip;
}

Player_Equipment& Player::Get_Player_Equipment() const {
	return *p_equip;
}

const Player_Item& Player::Get_Player_Item_Const() const {
	return *p_item;
}

Player_Item& Player::Get_Player_Item() const {
	return *p_item;
}

const BITMAP& Player::Get_Motion_Size() const {
	return motion_size;
}

const HBITMAP& Player::Get_Stop_Motion(const int& direction, const int& index) const {
	return stop_motion_bitmap[direction][index];
}

const HBITMAP& Player::Get_Move_Motion(const int& direction, const int& index) const {
	return move_motion_bitmap[direction][index];
}

const HBITMAP& Player::Get_Run_Motion(const int& direction, const int& index) const {
	return run_motion_bitmap[direction][index];
}

const HBITMAP& Player::Get_Attack_Motion(const int& direction, const int& index) const {
	return attack_motion_bitmap[direction][index];
}

void Player::Set_Class_Type(const int& class_type) {
	this->class_type = class_type;
}

void Player::Set_Motion_Bitmap() {
	switch (Get_Class_Type())
	{
	case Class_Type::Warrior:
		for (int direction = Object_Direction::Right; direction <= Object_Direction::DownRight; direction++) {
			for (int index = 0; index < 8; index++) {
				wchar_t str[50];
				wsprintf(str, _T(".\\BitMap\\Warrior\\Stop\\Warrior_Stop%d.bmp"), direction * 8 + index + 369);
				stop_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}	
			for (int index = 0; index < 8; index++) {
				wchar_t str[50];
				wsprintf(str, _T(".\\BitMap\\Warrior\\Move\\Warrior_Move%d.bmp"), direction * 8 + index + 1);
				move_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
			for (int index = 0; index < 8; index++) {
				wchar_t str[50];
				wsprintf(str, _T(".\\BitMap\\Warrior\\Run\\Warrior_Run%d.bmp"), direction * 8 + index + 1);
				run_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
			for (int index = 0; index < 10; index++) {
				wchar_t str[50];
				wsprintf(str, _T(".\\BitMap\\Warrior\\Attack\\Warrior_Attack_%d.bmp"), direction * 10 + index + 1369);
				attack_motion_bitmap[direction][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
		}
		break;
	default:
		break;
	}

	GetObject(stop_motion_bitmap[0][0], sizeof(BITMAP), &motion_size);
}

void Player::Create_Player_Equipment() {
	p_equip = Create_Class<Player_Equipment>();
	Reset_Player_Equipment(*p_equip, Get_Object_Info());
}

void Player::Create_Player_Item() {
	p_item = Create_Class<Player_Item>();
	Reset_Player_Item(*p_item);
}

void Reset_Player(Player& player, const int& class_type) {

	player.Set_Motion_Bitmap();
	Reset_Move_Object(player, 400, 500, player.Get_Motion_Size().bmWidth, player.Get_Motion_Size().bmHeight, 6);
	player.Create_Object_Info();
	Reset_Object_Info(player.Get_Object_Info(), 1, 100, 100, 10, 0, 0);
	player.Set_Class_Type(class_type);
	player.Create_Player_Equipment();
	player.Create_Player_Item();

	//지면 충돌 크기는 비트맵 객체마다 다 다르기때문에 일일히 객체가 생성때 설정을 해주어야한다.
	player.Set_Crash_Height(30);
	player.Set_Crash_Width(60);
}

void Paint_Player(HDC hdc, HDC bitdc, const Player& player) {

	switch (player.Get_Status())
	{
	case Player_Status::Stop:
	case Player_Status::Interaction:
	case Player_Status::Inventory:
	case Player_Status::Shopping:
	case Player_Status::Map_Selecting:
		SelectObject(bitdc, player.Get_Stop_Motion(player.Get_Direction(), player.Get_Ani_Count() / 2 % 8));
		break;
	case Player_Status::Move:
		SelectObject(bitdc, player.Get_Move_Motion(player.Get_Direction(), player.Get_Ani_Count() / 2 % 8));
		break;
	case Player_Status::Run:
		SelectObject(bitdc, player.Get_Run_Motion(player.Get_Direction(), player.Get_Ani_Count() / 2 % 8));
		break;
	case Player_Status::Attack:
		SelectObject(bitdc, player.Get_Attack_Motion(player.Get_Direction(), player.Get_Ani_Count() / 2 % 10));
		break;
	default:
		break;
	}

	TransparentBlt(hdc, player.Get_XPos() - 45, player.Get_YPos(), player.Get_Motion_Size().bmWidth, player.Get_Motion_Size().bmHeight, bitdc, 0, 0, player.Get_Motion_Size().bmWidth, player.Get_Motion_Size().bmHeight, RGB(255, 255, 255));

	Paint_Hitting_Damage(hdc, player);

	//나중에 스킬 설정할때나 다시 그려주장
	/*for (int index = 0; index < 20; index++) {
		if (&player.Get_Hit_Range_P_Const(index) != NULL) {
			POINT pos[4];
			pos[0] = player.Get_Hit_Range_P_Const(index).Get_Pos(0);
			pos[1] = player.Get_Hit_Range_P_Const(index).Get_Pos(1);
			pos[2] = player.Get_Hit_Range_P_Const(index).Get_Pos(2);
			pos[3] = player.Get_Hit_Range_P_Const(index).Get_Pos(3);

			Polygon(hdc, pos, 4);
		}
		
	}*/
}

void Paint_Player_Equipment(HDC hdc, HDC bitdc, const Player& player) {
	if (player.Get_Status() == Player_Status::Inventory)
		Paint_Player_Equipment(hdc, bitdc, player.Get_Player_Equipment_Const(), player.Get_Object_Info_Const());
}

void Equipment_Command(Player& player) {

	if (player.Get_Status() != Player_Status::Interaction && player.Get_Status() != Player_Status::Shopping && player.Get_Status() != Player_Status::Map_Selecting) {
		//장비창(인벤토리) 열기
		if (player.Get_Status() != Player_Status::Inventory) {
			player.Set_Status(Player_Status::Inventory);
		}
		//장비창(인벤토리) 닫기
		else {
			if (!player.Get_Player_Equipment_Const().Is_Chnage_Select())
				player.Set_Status(Player_Status::Stop);
		}
	}
}

void Chnage_Equipment(Player& player, WPARAM wParam) {
	if (player.Get_Status() == Player_Status::Inventory) {
		//장비 변경중이 아닐 경우
		if (!player.Get_Player_Equipment_Const().Is_Chnage_Select())
			Change_Equipment_Type_Select(player.Get_Player_Equipment(), wParam);
		else
			Change_Select_Equipment_Detail(player.Get_Player_Equipment(), player.Get_Object_Info(), wParam);
	}
}

void Use_Item_Command(Player& player, WPARAM wParam) {
	if (player.Get_Status() != Player_Status::Inventory && player.Get_Status() != Player_Status::Interaction) {
		//캐릭터 정보창, 상호작용중이 아닐경우만 작동합니다.
		switch (wParam)
		{
		case Player_Item_Type::Hp_Potion:
			Use_Hp_Potion(player.Get_Player_Item(), player.Get_Object_Info());
			break;
		case Player_Item_Type::Mp_Potion:
			Use_Mp_Potion(player.Get_Player_Item(), player.Get_Object_Info());
			break;
		case Player_Item_Type::Panacea:
			Use_Panacea(player.Get_Player_Item(), player);
			break;
		default:
			break;
		}
	}
}