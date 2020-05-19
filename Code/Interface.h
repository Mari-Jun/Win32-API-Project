#pragma once
#include <Windows.h>

class Move_Object;

class Player_Interface {
public:
	const HBITMAP Get_Panel_Bitmap() const;
	const BITMAP Get_Panel_Bitmap_Size() const;
	const HBITMAP Get_Health_Bitmap() const;
	const BITMAP Get_Health_Bitmap_Size() const;
	
	void Set_Bitmap();

private:
	HBITMAP panel_bitmap;
	BITMAP panel_bitmap_size;
	HBITMAP health_bitmap;
	BITMAP health_bitmap_size;
};

void Reset_Player_Interface(Player_Interface& p_inter);
void Paint_Player_Interface(HDC hdc, HDC bitdc, RECT c_rect, Player_Interface& p_inter, Move_Object& player);
