#pragma once
#include <Windows.h>

class Map {
public:
	const RECT& Get_Map_Rect() const;
	const HBITMAP& Get_Map_Size_Bitmap() const;

	void Set_Map_Rect(const int& left, const int& top, const int& right, const int& bottom);
	void Set_Map_Size_Bit(HDC hdc);

private:
	RECT map_rect;
	HBITMAP map_size_bit;
};