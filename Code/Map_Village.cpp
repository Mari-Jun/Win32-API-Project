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
#include "Sound.h"
#include "Camera.h"

Map_Village::~Map_Village() {
	Delete_Class<Non_Move_Object>(&portal);
	for (int index = 0; index < 6; index++)
		Delete_Class<Npc>(&npc[index]);
	Delete_Class<Shop>(&shop);
	Delete_Class<Sound>(&village_sound);
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

const Non_Move_Object& Map_Village::Get_Portal_Const() const {
	return *portal;
}

Non_Move_Object& Map_Village::Get_Portal() const {
	return *portal;
}

Sound& Map_Village::Get_Village_Sound() const {
	return *village_sound;
}

void Map_Village::Set_NM_Object() {

	for (int index = VNM_OB::House1; index <= VNM_OB::House5; index++)
		Create_NM_Object(index);
		
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House1), 560, 0, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House1).Set_Crash_Height(Get_NM_Object(VNM_OB::House1).Get_Object_Image_Size().bmHeight - 160);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House2), Get_Map_Rect().right - 320, 720, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House2).Set_Crash_Height(Get_NM_Object(VNM_OB::House2).Get_Object_Image_Size().bmHeight - 160);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House3), 0, 720, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House3).Set_Crash_Height(Get_NM_Object(VNM_OB::House3).Get_Object_Image_Size().bmHeight - 160);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House4), 0, 0, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House4.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House4).Set_Crash_Height(Get_NM_Object(VNM_OB::House4).Get_Object_Image_Size().bmHeight - 160);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::House5), 720, 720, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\House5.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::House5).Set_Crash_Height(Get_NM_Object(VNM_OB::House5).Get_Object_Image_Size().bmHeight - 160);

	Create_NM_Object(VNM_OB::Wall1);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::Wall1), 0, Get_Map_Rect().bottom - 160, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Ground_Wall.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::Wall1).Set_Crash_Height(Get_NM_Object(VNM_OB::Wall1).Get_Object_Image_Size().bmHeight);

	Create_NM_Object(VNM_OB::Tree1);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::Tree1), 880, 60, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::Tree1).Set_Height(500);
	Get_NM_Object(VNM_OB::Tree1).Set_Crash_Width(Get_NM_Object(VNM_OB::Tree1).Get_Object_Image_Size().bmWidth + 280);
	Get_NM_Object(VNM_OB::Tree1).Set_Crash_Height(400);

	Create_NM_Object(VNM_OB::Tree2);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::Tree2), 1440, 60, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::Tree2).Set_Height(500);
	Get_NM_Object(VNM_OB::Tree2).Set_Crash_Width(Get_NM_Object(VNM_OB::Tree2).Get_Object_Image_Size().bmWidth + 120);
	Get_NM_Object(VNM_OB::Tree2).Set_Crash_Height(400);

	Create_NM_Object(VNM_OB::Tree3);
	Reset_Non_Move_Object(Get_NM_Object(VNM_OB::Tree3), -80, -80, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(VNM_OB::Tree3).Set_Crash_Width(Get_NM_Object(VNM_OB::Tree3).Get_Object_Image_Size().bmWidth + 1640);
}

void Map_Village::Set_Texture() {
	Create_Texture(VT::Load, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Load.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(VT::Grow1, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Grow1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(VT::Grow2, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Village\\Grow2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

 void Map_Village::Set_Portal() {
	 //위치 잡기
	 Create_Portal();
	 Reset_Non_Move_Object(Get_Portal(), Get_Map_Rect().right - Get_Portal_Const().Get_Object_Image_Size().bmWidth, 560, NULL);
	 Get_Portal().Set_Crash_Height(Get_Portal_Const().Get_Object_Image_Size().bmHeight - 100);
}

void Map_Village::Set_Npc() {
	npc[Npc_Name::ELDER] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::ELDER), Npc_Name::ELDER, Get_NM_Object_Const(Village_NM_Object::House3).Get_XPos() + 260, 1140);

	npc[Npc_Name::EQUIPMENT_SHOP] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::EQUIPMENT_SHOP), Npc_Name::EQUIPMENT_SHOP, Get_NM_Object_Const(Village_NM_Object::House2).Get_XPos() + 60, 1140);

	npc[Npc_Name::WEAPON_SHOP] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::WEAPON_SHOP), Npc_Name::WEAPON_SHOP, Get_NM_Object_Const(Village_NM_Object::House5).Get_XPos() + 200, 1140);

	npc[Npc_Name::ITEM_SHOP] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::ITEM_SHOP), Npc_Name::ITEM_SHOP, Get_NM_Object_Const(Village_NM_Object::House1).Get_XPos() + 200, 420);

	npc[Npc_Name::LEGEND] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::LEGEND), Npc_Name::LEGEND, Get_NM_Object_Const(Village_NM_Object::House4).Get_XPos() + 140, 420);

	npc[Npc_Name::SOLDIER] = Create_Class<Npc>();
	Reset_Npc(Get_Npc(Npc_Name::SOLDIER), Npc_Name::SOLDIER, Get_Map_Rect().right - 200, 440);
}

void Map_Village::Set_Village_Sound() {
	village_sound = Create_Class<Sound>();
	Reset_Sound(*village_sound, Sound_Type::Sound_Map_Type, Map_Type::Village1);
}

void Map_Village::Create_Portal() {
	portal = Create_Class<Non_Move_Object>();
	portal->Set_Object_Bitmap((HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Portal.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

void Map_Village::Create_Shop(const int& shop_type, const RECT& it_rect) {
	shop = Create_Class<Shop>();
	Reset_Shop(*shop, it_rect, shop_type);
}

void Map_Village::Destroy_Shop() {
	Delete_Class<Shop>(&shop);
}

void Reset_Village_Map(HDC hdc, Map_Village& map_v) {
	map_v.Set_Map_Rect(0, 0, 1780, 1600);
	map_v.Set_Map_Size_Bit(hdc);
	map_v.Set_NM_Object();
	map_v.Set_Portal();
	map_v.Set_Npc();
	map_v.Set_Texture();
	map_v.Set_Village_Sound();

	//음악 재생
	map_v.Get_Village_Sound().Play_Sound(Village_Sound::BackGround_Village_Sound);
}


void Paint_Village_Map_Texture(HDC hdc, HDC bitdc, const Map_Village& map_v, const Camera& camera, const RECT c_rect) {
	
	SelectObject(bitdc, map_v.Get_Texture(VT::Grow1));
	for (int y = camera.Get_Cam_Top() - (camera.Get_Cam_Top() % 80); y < camera.Get_Cam_Top() + c_rect.bottom; y += 80) {
		for (int x= camera.Get_Cam_Left() - (camera.Get_Cam_Left() % 80); x < camera.Get_Cam_Left() + c_rect.right; x += 80) {
			Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}
	}

	SelectObject(bitdc, map_v.Get_Texture(VT::Load));
	for (int x = camera.Get_Cam_Left() - (camera.Get_Cam_Left() % 80); x < camera.Get_Cam_Left() + c_rect.right; x += 80) {
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, map_v.Get_Map_Rect().bottom - 320, 80, 80);
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, map_v.Get_Map_Rect().bottom - 240, 80, 80);
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, 560, 80, 80);
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, 640, 80, 80);
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, 720, 80, 80);
	}

	for (int y = 800; y < map_v.Get_Map_Rect().bottom - 320; y += 80) {
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 480, y, 80, 80);
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 560, y, 80, 80);
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 640, y, 80, 80);
	}

	for (int y = 800; y < map_v.Get_Map_Rect().bottom - 320; y += 80) {
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 1200, y, 80, 80);
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 1280, y, 80, 80);
		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 1360, y, 80, 80);
	}

	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 80, 400, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 80, 480, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 160, 480, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 160, 400, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 630, 400, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 630, 480, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 65, 1120, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 65, 1200, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 340, 1120, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 340, 1200, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, map_v.Get_Map_Rect().right - 200, 1120, 80, 80);
	Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, map_v.Get_Map_Rect().right - 200, 1200, 80, 80);
}

void Paint_Village_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Village& map_v, const Camera& camera, const RECT c_rect) {
	SelectObject(hdc, map_v.Get_Map_Size_Bitmap());
	Paint_Village_Map_Texture(hdc, bitdc, map_v, camera, c_rect);

	int y_pos;
	for (y_pos = camera.Get_Cam_Top(); y_pos < camera.Get_Cam_Top() + c_rect.bottom * 2; y_pos++) {
		for (int index = 0; index < 60; index++) {
			if (&map_v.Get_NM_Object(index) != NULL && y_pos == map_v.Get_NM_Object(index).Get_YPos() + map_v.Get_NM_Object(index).Get_Height()) {
				SelectObject(bitdc, map_v.Get_NM_Object(index).Get_Object_Bitmap());
				switch (index)
				{
				case VNM_OB::Tree1:
					for (int y = 0; y < 4; y++)
						for (int x = 0; x < 3; x++)
							Paint_TransparentBlt_Camera_In(hdc, bitdc, camera, c_rect, map_v.Get_NM_Object(index).Get_XPos() + x * 160, map_v.Get_NM_Object(index).Get_YPos() + y * 100, 
								map_v.Get_NM_Object(index).Get_Object_Image_Size().bmWidth, map_v.Get_NM_Object(index).Get_Object_Image_Size().bmHeight, RGB(150, 150, 150));
					break;
				case VNM_OB::Tree2:
					for (int y = 0; y < 4; y++)
						for (int x = 0; x < 2; x++)
							Paint_TransparentBlt_Camera_In(hdc, bitdc, camera, c_rect, map_v.Get_NM_Object(index).Get_XPos() + x * 160, map_v.Get_NM_Object(index).Get_YPos() + y * 100,
								map_v.Get_NM_Object(index).Get_Object_Image_Size().bmWidth, map_v.Get_NM_Object(index).Get_Object_Image_Size().bmHeight, RGB(150, 150, 150));
					break;
				case VNM_OB::Tree3:
					for (int x = 0; x < 12; x++)
						Paint_TransparentBlt_Camera_In(hdc, bitdc, camera, c_rect, map_v.Get_NM_Object(index).Get_XPos() + x * 160, map_v.Get_NM_Object(index).Get_YPos(),
							map_v.Get_NM_Object(index).Get_Object_Image_Size().bmWidth, map_v.Get_NM_Object(index).Get_Object_Image_Size().bmHeight, RGB(150, 150, 150));
					break;
				default:
					Paint_TransparentBlt_Camera_In(hdc, bitdc, camera, c_rect, map_v.Get_NM_Object(index).Get_XPos(), map_v.Get_NM_Object(index).Get_YPos(),
						map_v.Get_NM_Object(index).Get_Object_Image_Size().bmWidth, map_v.Get_NM_Object(index).Get_Object_Image_Size().bmHeight, RGB(150, 150, 150));
					break;
				}
			}
		}

		//Npc그리기
		for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) 
			if (&map_v.Get_Npc_Const(npc_type) != NULL && y_pos == map_v.Get_Npc_Const(npc_type).Get_YPos() + map_v.Get_Npc_Const(npc_type).Get_Height())
				Paint_Npc(hdc, bitdc, map_v.Get_Npc_Const(npc_type));

		//포탈 그리기
		if (&map_v.Get_Portal_Const() != NULL && y_pos == map_v.Get_Portal_Const().Get_YPos() + map_v.Get_Portal_Const().Get_Height())
			Paint_Portal(hdc, bitdc, map_v.Get_Portal_Const());

		if (&player != NULL && y_pos == player.Get_YPos() + player.Get_Height())
			Paint_Player(hdc, bitdc, player);	
	}

}

void Paint_Portal(HDC hdc, HDC bitdc, const Non_Move_Object& portal) {
	SelectObject(bitdc, portal.Get_Object_Bitmap());
	TransparentBlt(hdc, portal.Get_XPos(), portal.Get_YPos(), portal.Get_Object_Image_Size().bmWidth, portal.Get_Object_Image_Size().bmHeight,
		bitdc, 0, 0, portal.Get_Object_Image_Size().bmWidth, portal.Get_Object_Image_Size().bmHeight, RGB(0, 0, 0));
}

//Paint부분도 Object자체로 돌려서 범위 체크하면 최대한 줄일 수 있다.

void Animation_Play_Npc(Map_Village& map_v) {
	for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) {
		map_v.Get_Npc(npc_type).Set_Ani_Count(map_v.Get_Npc_Const(npc_type).Get_Ani_Count() + 1);
		switch (npc_type)
		{
		case Npc_Name::ELDER:
		case Npc_Name::EQUIPMENT_SHOP:
			if (map_v.Get_Npc_Const(npc_type).Get_Ani_Count() == 24)
				map_v.Get_Npc(npc_type).Set_Ani_Count(0);
			break;
		case Npc_Name::WEAPON_SHOP:
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

void Shop_Select_Item(Player& player, Map_Village& map_v, Interaction_Box& it_box, const WPARAM wParam) {
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
	}
}

void Change_Map_Village_To(Map_Village& map_v) {
	map_v.Get_Village_Sound().AllSoundStop();
}

void Change_Map_To_Village(Map_Village& map_v) {
	map_v.Get_Village_Sound().Play_Sound(Village_Sound::BackGround_Village_Sound);
}