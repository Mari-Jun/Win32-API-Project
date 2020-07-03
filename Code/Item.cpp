#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Info.h"
#include "Object_Main.h"
#include "Item.h"

const HBITMAP Player_Item::Get_Potion_Bitmap(const int& index) const {
	return potion_bitmap[index];
}

const HFONT Player_Item::Get_Font() const {
	return font;
}

const BITMAP Player_Item::Get_Bitmap_Size() const {
	return bitmap_size;
}

const int& Player_Item::Get_Hp_Potion() const {
	return hp_potion;
}

const int& Player_Item::Get_Hp_Potion_Max() const {
	return hp_potion_max;
}

const int& Player_Item::Get_Mp_Potion() const {
	return mp_potion;
}

const int& Player_Item::Get_Mp_Potion_Max() const {
	return mp_potion_max;
}

const int& Player_Item::Get_Panacea() const {
	return panacea;
}

void Player_Item::Set_Bitmap() {
	potion_bitmap[Player_Item_Type::Hp_Potion - 1] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item\\Hp_Potion.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	potion_bitmap[Player_Item_Type::Mp_Potion - 1] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item\\Mp_Potion.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	potion_bitmap[Player_Item_Type::Panacea - 1] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Item\\Panacea.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(potion_bitmap[0], sizeof(BITMAP), &bitmap_size);
}

void Player_Item::Set_Font() {
	font = CreateFont(18, 8, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Comic Sans MS 굵게"));
}

void Player_Item::Set_Hp_Potion(const int& hp_potion) {
	this->hp_potion = hp_potion;
}

void Player_Item::Set_Hp_Potion_Max(const int& hp_potion_max) {
	this->hp_potion_max = hp_potion_max;
}

void Player_Item::Set_Mp_Potion(const int& mp_potion) {
	this->mp_potion = mp_potion;
}

void Player_Item::Set_Mp_Potion_Max(const int& mp_potion_max) {
	this->mp_potion_max = mp_potion_max;
}

void Player_Item::Set_Panacea(const int& panacea) {
	this->panacea = panacea;
}


void Reset_Player_Item(Player_Item& p_item) {
	p_item.Set_Bitmap();
	p_item.Set_Font();
	p_item.Set_Hp_Potion(3);
	p_item.Set_Hp_Potion_Max(3);
	p_item.Set_Mp_Potion(3);
	p_item.Set_Mp_Potion_Max(3);
	p_item.Set_Panacea(1);
}

void Paint_Player_Item(HDC hdc, HDC bitdc, const Player_Item& p_item, const RECT c_rect) {	
	SelectObject(bitdc, p_item.Get_Potion_Bitmap(Player_Item_Type::Hp_Potion - 1));
	TransparentBlt(hdc, c_rect.right - 404, c_rect.bottom - 117, p_item.Get_Bitmap_Size().bmWidth, p_item.Get_Bitmap_Size().bmHeight, bitdc, 0, 0, p_item.Get_Bitmap_Size().bmWidth, p_item.Get_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	SelectObject(bitdc, p_item.Get_Potion_Bitmap(Player_Item_Type::Mp_Potion - 1));
	TransparentBlt(hdc, c_rect.right - 347, c_rect.bottom - 117, p_item.Get_Bitmap_Size().bmWidth, p_item.Get_Bitmap_Size().bmHeight, bitdc, 0, 0, p_item.Get_Bitmap_Size().bmWidth, p_item.Get_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	SelectObject(bitdc, p_item.Get_Potion_Bitmap(Player_Item_Type::Panacea - 1));
	TransparentBlt(hdc, c_rect.right - 290, c_rect.bottom - 117, p_item.Get_Bitmap_Size().bmWidth, p_item.Get_Bitmap_Size().bmHeight, bitdc, 0, 0, p_item.Get_Bitmap_Size().bmWidth, p_item.Get_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	
	
	SelectObject(hdc, p_item.Get_Font());
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	TCHAR text[3];
	wsprintf(text, _T("%2d"), p_item.Get_Hp_Potion());
	TextOut(hdc, c_rect.right - 372, c_rect.bottom - 87, text, _tcslen(text));
	wsprintf(text, _T("%2d"), p_item.Get_Mp_Potion());
	TextOut(hdc, c_rect.right - 315, c_rect.bottom - 87, text, _tcslen(text));
	wsprintf(text, _T("%2d"), p_item.Get_Panacea());
	TextOut(hdc, c_rect.right - 258, c_rect.bottom - 87, text, _tcslen(text));
}

void Recharge_Item(Player_Item& p_item) {
	p_item.Set_Hp_Potion(p_item.Get_Hp_Potion_Max());
	p_item.Set_Mp_Potion(p_item.Get_Mp_Potion_Max());
	p_item.Set_Panacea(2);
}

void Use_Hp_Potion(Player_Item& p_item, Object_Info& o_info) {
	//체력의 50%를 회복합니다.
	if (p_item.Get_Hp_Potion() > 0) {
		p_item.Set_Hp_Potion(p_item.Get_Hp_Potion() - 1);
		o_info.Set_Hp(((o_info.Get_Hp() < o_info.Get_Max_Hp() / 2) ? o_info.Get_Hp() + o_info.Get_Max_Hp() / 2 : o_info.Get_Max_Hp()));
	}
}
void Use_Mp_Potion(Player_Item& p_item, Object_Info& o_info) {
	//마나의 50%를 회복합니다.
	if (p_item.Get_Mp_Potion() > 0) {
		p_item.Set_Mp_Potion(p_item.Get_Mp_Potion() - 1);
		o_info.Set_Mp(((o_info.Get_Mp() < o_info.Get_Max_Mp() / 2) ? o_info.Get_Mp() + o_info.Get_Max_Mp() / 2 : o_info.Get_Max_Mp()));
	}
}
void Use_Panacea(Player_Item& p_item, Object_Info& o_info) {
	//체력과 마나의 50%를 회복합니다.
	if (p_item.Get_Panacea() > 0) {
		p_item.Set_Panacea(p_item.Get_Panacea() - 1);
		o_info.Set_Hp(((o_info.Get_Hp() < o_info.Get_Max_Hp() / 4) ? o_info.Get_Hp() + o_info.Get_Max_Hp() * 3 / 4 : o_info.Get_Max_Hp()));
		o_info.Set_Mp(((o_info.Get_Mp() < o_info.Get_Max_Mp() / 4) ? o_info.Get_Mp() + o_info.Get_Max_Mp() * 3 / 4 : o_info.Get_Max_Mp()));
	}
}