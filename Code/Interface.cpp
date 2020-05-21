#include <Windows.h>
#include <tchar.h>
#include "Interface.h"
#include "Object_Player.h"
#include "Object_Info.h"
#include "Item.h"

/*Player_Interface*/

const HBITMAP Player_Interface::Get_Panel_Bitmap() const {
	return panel_bitmap;
}

const BITMAP Player_Interface::Get_Panel_Bitmap_Size() const {
	return panel_bitmap_size;
}

const HBITMAP Player_Interface::Get_Hp_Bitmap() const {
	return hp_bitmap;
}

const BITMAP Player_Interface::Get_Hp_Bitmap_Size() const {
	return hp_bitmap_size;
}

const HBITMAP Player_Interface::Get_Mp_Bitmap() const {
	return mp_bitmap;
}

const BITMAP Player_Interface::Get_Mp_Bitmap_Size() const {
	return mp_bitmap_size;
}

const HBITMAP Player_Interface::Get_Command_Bitmap(const int& index) const {
	return command_bitmap[index];
}

const BITMAP Player_Interface::Get_Command_Bitmap_Size() const {
	return command_bitmap_size;
}


void Player_Interface::Set_Bitmap() {
	panel_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\PlayerPanels.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(panel_bitmap, sizeof(BITMAP), &panel_bitmap_size);
	hp_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\Hp.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hp_bitmap, sizeof(BITMAP), &hp_bitmap_size);
	mp_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\Mp.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(mp_bitmap, sizeof(BITMAP), &mp_bitmap_size);

	for (int index = 0; index < 8; index++) {
		TCHAR str[40];
		wsprintf(str, _T(".\\BitMap\\Interface\\Player\\Command%d.bmp"), index + 1);
		command_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	GetObject(command_bitmap[0], sizeof(BITMAP), &command_bitmap_size);
}

void Reset_Player_Interface(Player_Interface& p_inter) {
	p_inter.Set_Bitmap();
}

void Paint_Player_Interface(HDC hdc, HDC bitdc, const RECT c_rect, const Player_Interface& p_inter, const Player& player) {
	SelectObject(bitdc, p_inter.Get_Hp_Bitmap());
	
	TransparentBlt(hdc, c_rect.right - p_inter.Get_Hp_Bitmap_Size().bmWidth - 115, c_rect.bottom - (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()) - 10,
		p_inter.Get_Hp_Bitmap_Size().bmWidth, (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()),
		bitdc, 0, p_inter.Get_Hp_Bitmap_Size().bmHeight - (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()),
		p_inter.Get_Hp_Bitmap_Size().bmWidth, (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()), RGB(150, 150, 150));

	SelectObject(bitdc, p_inter.Get_Mp_Bitmap());

	TransparentBlt(hdc, c_rect.right - p_inter.Get_Hp_Bitmap_Size().bmWidth - 10, c_rect.bottom - (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Mp() / player.Get_Object_Info_Const().Get_Max_Mp()) - 10,
		p_inter.Get_Hp_Bitmap_Size().bmWidth, (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Mp() / player.Get_Object_Info_Const().Get_Max_Mp()),
		bitdc, 0, p_inter.Get_Hp_Bitmap_Size().bmHeight - (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Mp() / player.Get_Object_Info_Const().Get_Max_Mp()),
		p_inter.Get_Hp_Bitmap_Size().bmWidth, (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Mp() / player.Get_Object_Info_Const().Get_Max_Mp()), RGB(150, 150, 150));

	SelectObject(bitdc, p_inter.Get_Panel_Bitmap());
	TransparentBlt(hdc, c_rect.right - p_inter.Get_Panel_Bitmap_Size().bmWidth, c_rect.bottom - p_inter.Get_Panel_Bitmap_Size().bmHeight, p_inter.Get_Panel_Bitmap_Size().bmWidth, p_inter.Get_Panel_Bitmap_Size().bmHeight,
		bitdc, 0, 0, p_inter.Get_Panel_Bitmap_Size().bmWidth, p_inter.Get_Panel_Bitmap_Size().bmHeight, RGB(145, 145, 145));

	//아이템을 출력합니다.
	Paint_Player_Item(hdc, bitdc, player.Get_Player_Item_Const(), c_rect);



	//단축키 그림을 출력합니다.
	for (int index = 0; index < 3; index++) {
		SelectObject(bitdc, p_inter.Get_Command_Bitmap(index));
		TransparentBlt(hdc, c_rect.right - 406 + index * 57, c_rect.bottom - 117, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, bitdc, 0, 0, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	}
	for (int index = 3; index < 8; index++) {
		SelectObject(bitdc, p_inter.Get_Command_Bitmap(index));
		TransparentBlt(hdc, c_rect.right - 517 + (index - 3) * 56, c_rect.bottom - 60, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, bitdc, 0, 0, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	}
}