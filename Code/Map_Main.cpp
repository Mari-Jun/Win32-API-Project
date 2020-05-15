#include <windows.h>
#include "Source.h"
#include "Map_Main.h"

const RECT& Map::Get_Map_Rect() const {
	return map_rect;
}

const HBITMAP& Map::Get_Map_Size_Bitmap() const {
	return map_size_bit;
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