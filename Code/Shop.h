#pragma once
#include <Windows.h>

enum Shop_Type {
	Equipment_Type, Accessory_Type
};

class Player_Equipment;

class Shop {
public:
	const int& Get_Shop_Type();

	void Set_Shop_Type(const int& shop_type);

private:
	int shop_type;
	Player_Equipment* shop_equip;
	HBITMAP shop_bitmap;
	BITMAP shop_bitmap_size;
};