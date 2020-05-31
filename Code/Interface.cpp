#include <Windows.h>
#include <tchar.h>
#include "Interface.h"
#include "Object_Player.h"
#include "Object_Info.h"
#include "Object_Skill.h"
#include "Map_Dungeon.h"
#include "Item.h"

/*Player_Interface*/

Player_Interface::~Player_Interface() {
	DeleteObject(panel_bitmap);
	DeleteObject(hp_bitmap);
	DeleteObject(mp_bitmap);
	for (int index = 0; index < 7; index++)
		DeleteObject(command_bitmap[index]);
}

const HBITMAP& Player_Interface::Get_Panel_Bitmap() const {
	return panel_bitmap;
}

const BITMAP& Player_Interface::Get_Panel_Bitmap_Size() const {
	return panel_bitmap_size;
}

const HBITMAP& Player_Interface::Get_Hp_Bitmap() const {
	return hp_bitmap;
}

const BITMAP& Player_Interface::Get_Hp_Bitmap_Size() const {
	return hp_bitmap_size;
}

const HBITMAP& Player_Interface::Get_Mp_Bitmap() const {
	return mp_bitmap;
}

const BITMAP& Player_Interface::Get_Mp_Bitmap_Size() const {
	return mp_bitmap_size;
}

const HBITMAP& Player_Interface::Get_Command_Bitmap(const int& index) const {
	return command_bitmap[index];
}

const BITMAP& Player_Interface::Get_Command_Bitmap_Size() const {
	return command_bitmap_size;
}


void Player_Interface::Set_Bitmap() {
	panel_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\PlayerPanels.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(panel_bitmap, sizeof(BITMAP), &panel_bitmap_size);
	hp_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\Hp.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hp_bitmap, sizeof(BITMAP), &hp_bitmap_size);
	mp_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\Mp.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(mp_bitmap, sizeof(BITMAP), &mp_bitmap_size);

	for (int index = 0; index < 7; index++) {
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

	//스킬을 출력합니다.
	Paint_Player_Skill_Icon(hdc, bitdc, player.Get_Player_Skill_Const(), c_rect);

	//단축키 그림을 출력합니다.
	for (int index = 0; index < 3; index++) {
		SelectObject(bitdc, p_inter.Get_Command_Bitmap(index));
		TransparentBlt(hdc, c_rect.right - 406 + index * 57, c_rect.bottom - 117, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, bitdc, 0, 0, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	}
	for (int index = 3; index < 7; index++) {
		SelectObject(bitdc, p_inter.Get_Command_Bitmap(index));
		TransparentBlt(hdc, c_rect.right - 460 + (index - 3) * 56, c_rect.bottom - 60, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, bitdc, 0, 0, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	}

}

/*Enemy Interface*/

Enemy_Interface::~Enemy_Interface() {
	DeleteObject(font[0]);
	DeleteObject(font[1]);
	DeleteObject(hp_bitmap);
}

const HFONT& Enemy_Interface::Get_Font(const int& index) const {
	return font[index];
}

const HBITMAP& Enemy_Interface::Get_Hp_Bitmap() const {
	return hp_bitmap;
}

const BITMAP& Enemy_Interface::Get_Hp_Bitmap_Size() const {
	return hp_bitmap_size;
}

void Enemy_Interface::Set_Font() {
	font[0] = CreateFont(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼 편지체"));
	font[1] = CreateFont(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼 편지체"));
}

void Enemy_Interface::Set_Bitmap() {

}


void Reset_Enemy_Interface(Enemy_Interface& e_inter) {
	e_inter.Set_Font();
	e_inter.Set_Bitmap();
}

void Paint_Enemy_Interface(HDC hdc, HDC bitdc, const RECT c_rect, const Enemy_Interface& e_inter, const Map_Dungeon& map_d) {
	SelectObject(hdc, e_inter.Get_Font(0));
	TCHAR str[20];
	int count = 0;
	for (int index = 0; index < 53; index++) 
		if (&map_d.Get_Enemy_Const(index) != NULL)
			count++;
	wsprintf(str, _T("남은 몬스터 수 : %d"), count);
	TextOut(hdc, c_rect.right - 200, 20, str, _tcslen(str));
}