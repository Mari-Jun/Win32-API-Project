#include <windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Main.h"
#include "Object_Enemy.h"
#include "Map_Main.h"
#include "Object_Npc.h"

Map::~Map() {
	DeleteObject(map_size_bit);
	for (int index = 0; index < 10; index++)
		Delete_Class<Non_Move_Object>(&nm_object[index]);
}

const RECT& Map::Get_Map_Rect() const {
	return map_rect;
}

const HBITMAP& Map::Get_Map_Size_Bitmap() const {
	return map_size_bit;
}

const Non_Move_Object& Map::Get_NM_Object_Const(const int& index) const {
	return *nm_object[index];
}

Non_Move_Object& Map::Get_NM_Object(const int& index) const {
	return *nm_object[index];
}

const Non_Move_Object& Map::Get_Portal_Const() const {
	return *portal;
}

Non_Move_Object& Map::Get_Portal() const {
	return *portal;
}

void Map::Create_NM_Object(const int& index) {
	nm_object[index] = Create_Class<Non_Move_Object>();
}

void Map::Create_Portal() {
	portal = Create_Class<Non_Move_Object>();
	portal->Set_Object_Bitmap((HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Portal.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
}

void Map::Set_Map_Rect(const int& left, const int& top, const int& right, const int& bottom) {
	map_rect.top = top;	
	map_rect.bottom = bottom;
	map_rect.left = left;
	map_rect.right = right;
}

void Map::Set_Map_Size_Bit(HDC hdc) {
	map_size_bit = CreateCompatibleBitmap(hdc, Get_Map_Rect().right, Get_Map_Rect().bottom);
}

void Paint_Portal(HDC hdc, HDC bitdc, const Non_Move_Object& portal) {
	SelectObject(bitdc, portal.Get_Object_Bitmap());
	TransparentBlt(hdc, portal.Get_XPos(), portal.Get_YPos(), portal.Get_Object_Image_Size().bmWidth, portal.Get_Object_Image_Size().bmHeight,
		bitdc, 0, 0, portal.Get_Object_Image_Size().bmWidth, portal.Get_Object_Image_Size().bmHeight, RGB(0, 0, 0));
}