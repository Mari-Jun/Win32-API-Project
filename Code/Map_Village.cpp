#include <windows.h>
#include <tchar.h>
#include "Source.h"
#include "Map_Village.h"
#include "Object_Main.h"
#include "Object_Player.h"
#include "Object_Npc.h"
#include "Object_Enemy.h"

Map_Village::~Map_Village() {
	for (int index = 0; index < 4; index++)
		DeleteObject(texture[index]);
}

const Practice_Enemy& Map_Village::Get_P_Enemy_Const() const {
	return *p_enemy;
}

Practice_Enemy& Map_Village::Get_P_Enemy() const {
	return *p_enemy;
}


const HBITMAP Map_Village::Get_Texture(const int& index) const {
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

void Map_Village::Set_NM_Npc() {
	Create_NM_Npc(Npc_Name::Elder);
	Reset_Non_Move_Npc(Get_NM_Npc(Npc_Name::Elder), 240, 1140, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Npc\\Non_Move\\Elder.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Npc(Npc_Name::Elder).Set_Crash_Height(30);
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



void Reset_Village_Map(HDC hdc, Map_Village& map_v) {
	map_v.Set_Map_Rect(0, 0, 1760, 1600);
	map_v.Set_Map_Size_Bit(hdc);
	map_v.Set_NM_Object();
	map_v.Set_NM_Npc();
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

void Paint_Village_Map(HDC hdc, HDC bitdc, const Warrior& warrior, const Map_Village& map_v) {
	SelectObject(hdc, map_v.Get_Map_Size_Bitmap());
	FillRect(hdc, &map_v.Get_Map_Rect(), WHITE_BRUSH);

	Paint_Village_Map_Texture(hdc, bitdc, map_v);

	int y_pos = 0;
	for (y_pos = 0; y_pos <= map_v.Get_Map_Rect().bottom; y_pos++) {
		for (int index = 0; index < 10; index++) {
			if (&map_v.Get_NM_Object(index) != NULL && y_pos == map_v.Get_NM_Object(index).Get_YPos() + map_v.Get_NM_Object(index).Get_Height()) {
				SelectObject(bitdc, map_v.Get_NM_Object(index).Get_Object_Bitmap());
				TransparentBlt(hdc, map_v.Get_NM_Object(index).Get_XPos(), map_v.Get_NM_Object(index).Get_YPos(), map_v.Get_NM_Object(index).Get_Width(), map_v.Get_NM_Object(index).Get_Height(), bitdc, 0, 0, map_v.Get_NM_Object(index).Get_Width(), map_v.Get_NM_Object(index).Get_Height(), RGB(255, 255, 255));
			}
		}
		for (int index = 0; index < 4; index++) {
			if (&map_v.Get_NM_Npc_Const(index) != NULL && y_pos == map_v.Get_NM_Npc_Const(index).Get_YPos() + map_v.Get_NM_Npc_Const(index).Get_Height()) {
				SelectObject(bitdc, map_v.Get_NM_Npc_Const(index).Get_Object_Bitmap());
				TransparentBlt(hdc, map_v.Get_NM_Npc_Const(index).Get_XPos(), map_v.Get_NM_Npc_Const(index).Get_YPos(), map_v.Get_NM_Npc_Const(index).Get_Width(), map_v.Get_NM_Npc_Const(index).Get_Height(), bitdc, 0, 0, map_v.Get_NM_Npc_Const(index).Get_Width(), map_v.Get_NM_Npc_Const(index).Get_Height(), RGB(255, 255, 255));
			}
		}

		if (&map_v.Get_P_Enemy_Const() != NULL && y_pos == map_v.Get_P_Enemy_Const().Get_YPos() + map_v.Get_P_Enemy_Const().Get_Height()) 
			Paint_Practice_Enemy(hdc,bitdc, map_v.Get_P_Enemy_Const());

		if (&warrior != NULL && y_pos == warrior.Get_YPos() + warrior.Get_Height())
			Paint_Warrior(hdc, bitdc, warrior);
	}
}