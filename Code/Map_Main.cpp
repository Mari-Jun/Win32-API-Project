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
	for (int index = 0; index < 8; index++)
		DeleteObject(texture[index]);
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

const HBITMAP& Map::Get_Texture(const int& index) const {
	return texture[index];
}

void Map::Create_NM_Object(const int& index) {
	nm_object[index] = Create_Class<Non_Move_Object>();
}

void Map::Create_Texture(const int& index, HBITMAP texture) {
	this->texture[index] = texture;
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