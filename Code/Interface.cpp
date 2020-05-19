#include <Windows.h>
#include <tchar.h>
#include "Interface.h"
#include "Object_Main.h"
#include "Object_Info.h"

/*Player_Interface*/

const HBITMAP Player_Interface::Get_Panel_Bitmap() const {
	return panel_bitmap;
}

const BITMAP Player_Interface::Get_Panel_Bitmap_Size() const {
	return panel_bitmap_size;
}

const HBITMAP Player_Interface::Get_Health_Bitmap() const {
	return health_bitmap;
}

const BITMAP Player_Interface::Get_Health_Bitmap_Size() const {
	return health_bitmap_size;
}

void Player_Interface::Set_Bitmap() {
	panel_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\PlayerPanels.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(panel_bitmap, sizeof(BITMAP), &panel_bitmap_size);
	health_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\Health.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(health_bitmap, sizeof(BITMAP), &health_bitmap_size);
}

void Reset_Player_Interface(Player_Interface& p_inter) {
	p_inter.Set_Bitmap();
}

void Paint_Player_Interface(HDC hdc, HDC bitdc, RECT c_rect, Player_Interface& p_inter, Move_Object& player) {
	SelectObject(bitdc, p_inter.Get_Health_Bitmap());

	//height�� ������.
	
	TransparentBlt(hdc, c_rect.right - p_inter.Get_Health_Bitmap_Size().bmWidth - 10, c_rect.bottom - (p_inter.Get_Health_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()) - 10,
		p_inter.Get_Health_Bitmap_Size().bmWidth, (p_inter.Get_Health_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()),
		bitdc, 0, p_inter.Get_Health_Bitmap_Size().bmHeight - (p_inter.Get_Health_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()),
		p_inter.Get_Health_Bitmap_Size().bmWidth, (p_inter.Get_Health_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()), RGB(145, 145, 145));

	SelectObject(bitdc, p_inter.Get_Panel_Bitmap());
	TransparentBlt(hdc, c_rect.right - p_inter.Get_Panel_Bitmap_Size().bmWidth, c_rect.bottom - p_inter.Get_Panel_Bitmap_Size().bmHeight, p_inter.Get_Panel_Bitmap_Size().bmWidth, p_inter.Get_Panel_Bitmap_Size().bmHeight,
		bitdc, 0, 0, p_inter.Get_Panel_Bitmap_Size().bmWidth, p_inter.Get_Panel_Bitmap_Size().bmHeight, RGB(145, 145, 145));
}