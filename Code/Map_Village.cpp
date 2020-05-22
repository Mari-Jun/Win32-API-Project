#include <windows.h>
#include <tchar.h>
#include "Source.h"
#include "Map_Village.h"
#include "Object_Main.h"
#include "Object_Player.h"
#include "Object_Npc.h"
#include "Object_Enemy.h"
#include "Object_Info.h"
#include "Object_Player_Interaction.h"
#include "Shop.h"

Map_Village::~Map_Village() {
	for (int index = 0; index < 4; index++)
		DeleteObject(texture[index]);
	Delete_Class<Practice_Enemy>(&p_enemy);
	for (int index = 0; index < 5; index++)
		Delete_Class<Npc>(&npc[index]);
	Delete_Class<Shop>(&shop);
}

const Npc& Map_Village::Get_Npc_Const(const int& npc_type) const {
	return *npc[npc_type];
}

Npc& Map_Village::Get_Npc(const int& npc_type) const {
	return *npc[npc_type];
}

const Shop& Map_Village::Get_Shop_Const() const {
	return *shop;
}

Shop& Map_Village::Get_Shop() const {
	return *shop;
}

const Practice_Enemy& Map_Village::Get_P_Enemy_Const() const {
	return *p_enemy;
}

Practice_Enemy& Map_Village::Get_P_Enemy() const {
	return *p_enemy;
}


const HBITMAP& Map_Village::Get_Texture(const int& index) const {
	return texture[index];
}

void Map_Village::Set_NM_Object() {

	for (int index = VNM_OB::House1; index <= VNM_OB::House4; index++)
		Create_NM_Object(index);
		
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House1), 560, 0, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House1).Set_Crash_Height(Get_NM_Object(VNM_OB::House1).Get_Object_Image_Size().bmHeight);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House2), Get_Map_Rect().right - 320, 720, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House2).Set_Crash_Height(Get_NM_Object(VNM_OB::House2).Get_Object_Image_Size().bmHeight - 160);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House3), 0, 720, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House3).Set_Crash_Height(Get_NM_Object(VNM_OB::House3).Get_Object_Image_Size().bmHeight - 160);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House4), 0, 0, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House4.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House4).Set_Crash_Height(Get_NM_Object(VNM_OB::House4).Get_Object_Image_Size().bmHeight - 160);

	Create_NM_Object(VNM_OB::Lake);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::Lake), 720, 800, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Lake.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::Lake).Set_Crash_Height(Get_NM_Object(VNM_OB::Lake).Get_Object_Image_Size().bmHeight);

	Create_NM_Object(VNM_OB::Wall1);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::Wall1), 0, Get_Map_Rect().bottom - 160, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Ground_Wall.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::Wall1).Set_Crash_Height(Get_NM_Object(VNM_OB::Wall1).Get_Object_Image_Size().bmHeight);
}

void Map_Village::Set_Npc() {
	npc[Npc_Name::ELDER] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::ELDER), Npc_Name::ELDER, Get_NM_Object_Const(Village_NM_Object::House3).Get_XPos() + 260, 1140);

	npc[Npc_Name::WEAPON_SHOP] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::WEAPON_SHOP), Npc_Name::WEAPON_SHOP, Get_NM_Object_Const(Village_NM_Object::House2).Get_XPos() + 60, 1140);

	npc[Npc_Name::ITEM_SHOP] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::ITEM_SHOP), Npc_Name::ITEM_SHOP, Get_NM_Object_Const(Village_NM_Object::House1).Get_XPos() + 200, 420);

	npc[Npc_Name::LEGEND] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::LEGEND), Npc_Name::LEGEND, Get_NM_Object_Const(Village_NM_Object::House4).Get_XPos() + 140, 420);

	npc[Npc_Name::SOLDIER] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::SOLDIER), Npc_Name::SOLDIER, Get_Map_Rect().right - 100, 440);
}

void Map_Village::Set_P_Enemy() {
	p_enemy = Create_Class<Practice_Enemy>();
	p_enemy->Set_Stop_Motion();
	Reset_Practice_Enemy(*p_enemy);
}

void Map_Village::Set_Texture() {
	texture[VT::Load] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Load.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	texture[VT::Grow1] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Grow1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	texture[VT::Grow2] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Grow2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void Map_Village::Create_Shop(const int& shop_type, const RECT& it_rect) {
	shop = Create_Class<Shop>();
	Reset_Shop(*shop, it_rect, shop_type);
}

void Map_Village::Destroy_Shop() {
	Delete_Class<Shop>(&shop);
}

void Map_Village::Kill_P_Enemy() {
	Delete_Class<Practice_Enemy>(&p_enemy);
}


void Reset_Village_Map(HDC hdc, Map_Village& map_v) {
	map_v.Set_Map_Rect(0, 0, 1760, 1600);
	map_v.Set_Map_Size_Bit(hdc);
	map_v.Set_NM_Object();
	map_v.Set_Npc();
	map_v.Set_P_Enemy();
	map_v.Set_Texture();
}

void Paint_Village_Map_Texture(HDC hdc, HDC bitdc, const Map_Village& map_v) {
	
	SelectObject(bitdc, map_v.Get_Texture(VT::Grow1));
	for (int y = 0; y < map_v.Get_Map_Rect().bottom - 320; y += 80) {
		for (int x = 0; x < map_v.Get_Map_Rect().right; x += 80) {
			BitBlt(hdc, x, y, 80, 80, bitdc, 0, 0, SRCCOPY);
		}
	}

	SelectObject(bitdc, map_v.Get_Texture(VT::Load));
	for (int x = 0; x < map_v.Get_Map_Rect().right; x += 80) {
		BitBlt(hdc, x, map_v.Get_Map_Rect().bottom - 320, 80, 80, bitdc, 0, 0, SRCCOPY);
		BitBlt(hdc, x, map_v.Get_Map_Rect().bottom - 240, 80, 80, bitdc, 0, 0, SRCCOPY);
		BitBlt(hdc, x, 560, 80, 80, bitdc, 0, 0, SRCCOPY);
		BitBlt(hdc, x, 640, 80, 80, bitdc, 0, 0, SRCCOPY);
		BitBlt(hdc, x, 720, 80, 80, bitdc, 0, 0, SRCCOPY);
	}

	for (int y = 800; y < map_v.Get_Map_Rect().bottom - 320; y += 80) {
		BitBlt(hdc, 480, y, 80, 80, bitdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 560, y, 80, 80, bitdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 640, y, 80, 80, bitdc, 0, 0, SRCCOPY);
	}

	for (int y = 800; y < map_v.Get_Map_Rect().bottom - 320; y += 80) {
		BitBlt(hdc, 1200, y, 80, 80, bitdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 1280, y, 80, 80, bitdc, 0, 0, SRCCOPY);
		BitBlt(hdc, 1360, y, 80, 80, bitdc, 0, 0, SRCCOPY);
	}

	BitBlt(hdc, 80, 400, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 80, 480, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 160, 480, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 160, 400, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 630, 400, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 630, 480, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 65, 1120, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 65, 1200, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 340, 1120, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, 340, 1200, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, map_v.Get_Map_Rect().right - 200, 1120, 80, 80, bitdc, 0, 0, SRCCOPY);
	BitBlt(hdc, map_v.Get_Map_Rect().right - 200, 1200, 80, 80, bitdc, 0, 0, SRCCOPY);
}

void Paint_Village_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Village& map_v) {
	SelectObject(hdc, map_v.Get_Map_Size_Bitmap());
	FillRect(hdc, &map_v.Get_Map_Rect(), WHITE_BRUSH);

	Paint_Village_Map_Texture(hdc, bitdc, map_v);

	int y_pos = 0;
	for (y_pos = 0; y_pos <= map_v.Get_Map_Rect().bottom; y_pos++) {
		for (int index = 0; index < 10; index++) {
			if (&map_v.Get_NM_Object(index) != NULL && y_pos == map_v.Get_NM_Object(index).Get_YPos() + map_v.Get_NM_Object(index).Get_Height()) {
				SelectObject(bitdc, map_v.Get_NM_Object(index).Get_Object_Bitmap());
				TransparentBlt(hdc, map_v.Get_NM_Object(index).Get_XPos(), map_v.Get_NM_Object(index).Get_YPos(), map_v.Get_NM_Object(index).Get_Width(), map_v.Get_NM_Object(index).Get_Height(), bitdc, 0, 0, map_v.Get_NM_Object(index).Get_Width(), map_v.Get_NM_Object(index).Get_Height(), RGB(150, 150, 150));
			}
		}

		//Npc그리기
		for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) 
			if (&map_v.Get_Npc_Const(npc_type) != NULL && y_pos == map_v.Get_Npc_Const(npc_type).Get_YPos() + map_v.Get_Npc_Const(npc_type).Get_Height())
				Paint_Npc(hdc, bitdc, map_v.Get_Npc_Const(npc_type));

		//적 그리기
		if (&map_v.Get_P_Enemy_Const() != NULL && y_pos == map_v.Get_P_Enemy_Const().Get_YPos() + map_v.Get_P_Enemy_Const().Get_Height()) 
			Paint_Practice_Enemy(hdc,bitdc, map_v.Get_P_Enemy_Const());

		if (&player != NULL && y_pos == player.Get_YPos() + player.Get_Height())
			Paint_Player(hdc, bitdc, player);
	}
}

//Paint부분도 Object자체로 돌려서 범위 체크하면 최대한 줄일 수 있다.

void Animation_Play_Npc(Map_Village& map_v) {
	for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) {
		map_v.Get_Npc(npc_type).Set_Ani_Count(map_v.Get_Npc_Const(npc_type).Get_Ani_Count() + 1);
		switch (npc_type)
		{
		case Npc_Name::ELDER:
		case Npc_Name::WEAPON_SHOP:
			if (map_v.Get_Npc_Const(npc_type).Get_Ani_Count() == 24)
				map_v.Get_Npc(npc_type).Set_Ani_Count(0);
			break;
		case Npc_Name::ITEM_SHOP:
		case Npc_Name::LEGEND:
		case Npc_Name::SOLDIER:
			if (map_v.Get_Npc_Const(npc_type).Get_Ani_Count() == 32)
				map_v.Get_Npc(npc_type).Set_Ani_Count(0);
			break;
		default:
			break;
		}
	}
}

void Enemy_Kill_Check(Map_Village& map_v) {
	if (&map_v.Get_P_Enemy_Const() != NULL && map_v.Get_P_Enemy_Const().Get_Object_Info_Const().Get_Hp() < 0)
		map_v.Kill_P_Enemy();
}

bool Shop_Select_Item(Player& player, Map_Village& map_v, Interaction_Box& it_box, const WPARAM wParam) {
	if (player.Get_Status() == Player_Status::Shopping && &map_v.Get_Shop_Const() != NULL) {
		if (it_box.Get_Dialog_Status() == 0) {
			if (Change_Select_Item(map_v.Get_Shop(), wParam))
				it_box.Set_Dialog_Status(it_box.Get_Dialog_Status() + 1);
		}
		else {
			switch (Select_Dialog_Ok(it_box,wParam))
			{
			case 0:
				//취소을 선택한 경우
				it_box.Set_Dialog_Status(0);
				break;
			case 1:
				//확인을 선택한 경우
				if (!Buy_Equipment_Shop(player.Get_Player_Equipment(), map_v.Get_Shop())) {
					if (it_box.Get_Dialog_Status() == 1)
						it_box.Set_Dialog_Status(it_box.Get_Dialog_Status() + 1);
					else {
						it_box.Set_Select_Ok(false);
						it_box.Set_Dialog_Status(0);
					}
				}
				else {
					it_box.Set_Select_Ok(false);
					it_box.Set_Dialog_Status(0);
				}
				break;
			default:
				break;
			}
		}
		return true;
	}
	return false;
}