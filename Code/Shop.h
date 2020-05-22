#pragma once
#include <Windows.h>

class Player_Equipment;

class Shop {
public:
	~Shop();

	const POINT& Get_Pos() const;
	const HBITMAP& Get_Shop_Bitmap() const;
	const BITMAP& Get_Shop_Bitmap_Size() const;
	const HBITMAP& Get_Select_Bitmap() const;
	const BITMAP& Get_Select_Bitmap_Size() const;
	const HBITMAP& Get_Shop_Item_Bitmap(const int& type, const int& index) const;
	const int& Get_Shop_Type() const;
	const int& Get_Item_Price(const int& type, const int& index) const;
	const int& Get_Select_Item() const;

	void Set_Pos(const RECT it_rect);
	void Set_Bitmap();
	void Set_Shop_Type(const int& shop_type);
	void Set_Item_Price();
	void Set_Select_Item(const int& select_item);

private:
	POINT pos;
	HBITMAP shop_bitmap;
	BITMAP shop_bitmap_size;
	HBITMAP select_bitmap;
	BITMAP select_bitmap_size;
	HBITMAP shop_item_bitmap[5][4];
	int shop_type;
	int item_price[5][4];
	int select_item;	
};

void Reset_Shop(Shop& shop, const RECT it_rect, const int& shop_type);
void Paint_Shop(HDC hdc, HDC bitdc, const Player_Equipment& p_equip, const Shop& shop);
const bool Change_Select_Item(Shop& shop, const WPARAM wParam);
const bool Buy_Equipment_Shop(Player_Equipment& p_equip, Shop& shop);