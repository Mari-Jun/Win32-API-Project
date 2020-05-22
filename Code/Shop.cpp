#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Equipment.h"
#include "Shop.h"

Shop::~Shop() {
	DeleteObject(shop_bitmap);
	DeleteObject(select_bitmap);
}

const POINT& Shop::Get_Pos() const {
	return pos;
}

const HBITMAP& Shop::Get_Shop_Bitmap() const {
	return shop_bitmap;
}

const BITMAP& Shop::Get_Shop_Bitmap_Size() const {
	return shop_bitmap_size;
}

const HBITMAP& Shop::Get_Select_Bitmap() const {
	return select_bitmap;
}

const BITMAP& Shop::Get_Select_Bitmap_Size() const {
	return select_bitmap_size;
}

const HBITMAP& Shop::Get_Shop_Item_Bitmap(const int& type, const int& index) const {
	return shop_item_bitmap[type][index];
}

const int& Shop::Get_Shop_Type() const {
	return shop_type;
}

const int& Shop::Get_Item_Price(const int& type, const int& index) const {
	return item_price[type][index];
}

const int& Shop::Get_Select_Item() const {
	return select_item;
}

void Shop::Set_Pos(const RECT it_rect) {
	pos = { (it_rect.left + it_rect.right) / 2 - Get_Shop_Bitmap_Size().bmWidth / 2, it_rect.top - Get_Shop_Bitmap_Size().bmHeight + 20 };
}

void Shop::Set_Bitmap() {
	shop_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Shop\\EquipShop.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(shop_bitmap, sizeof(BITMAP), &shop_bitmap_size);
	select_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Shop\\border1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(select_bitmap, sizeof(BITMAP), &select_bitmap_size);

	TCHAR str[50];
	switch (shop_type)
	{
	case Shop_Type::Equipment_Type:
		for (int type = Equipment_Type::T_HELMET; type <= Equipment_Type::T_SHOE; type++) {
			for (int index = 0; index < 4; index++) {
				wsprintf(str, _T(".\\BitMap\\Interface\\Shop\\Shop_Item%d.bmp"), type * 4 + index + 1);
				shop_item_bitmap[type][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
		}
		break;
	case Shop_Type::Accessory_Type:
		for (int type = Equipment_Type::T_WEAPON; type <= Equipment_Type::T_BOOK; type++) {
			for (int index = 0; index < 4; index++) {
				wsprintf(str, _T(".\\BitMap\\Interface\\Shop\\Shop_Item%d.bmp"), type * 4 + index + 1);
				shop_item_bitmap[type - Equipment_Type::T_WEAPON][index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
			}
		}
		break;
	default:
		break;
	}
	
}

void Shop::Set_Shop_Type(const int& shop_type) {
	this->shop_type = shop_type;
}

void Shop::Set_Item_Price() {
	switch (Get_Shop_Type())
	{
	case Shop_Type::Equipment_Type:

		item_price[Equipment_Type::T_HELMET][Helmet_Type::SHOP_HELMET1 - 1] = 115;
		item_price[Equipment_Type::T_HELMET][Helmet_Type::SHOP_HELMET2 - 1] = 474;
		item_price[Equipment_Type::T_HELMET][Helmet_Type::SHOP_HELMET3 - 1] = 1560;
		item_price[Equipment_Type::T_HELMET][Helmet_Type::SHOP_HELMET4 - 1] = 2045;
		
		item_price[Equipment_Type::T_ARMOR][Armor_Type::SHOP_ARMOR1 - 1] = 185;
		item_price[Equipment_Type::T_ARMOR][Armor_Type::SHOP_ARMOR2 - 1] = 550;
		item_price[Equipment_Type::T_ARMOR][Armor_Type::SHOP_ARMOR3 - 1] = 1744;
		item_price[Equipment_Type::T_ARMOR][Armor_Type::SHOP_ARMOR4 - 1] = 2150;

		item_price[Equipment_Type::T_PANT][Pant_Type::SHOP_PANT1 - 1] = 130;
		item_price[Equipment_Type::T_PANT][Pant_Type::SHOP_PANT2 - 1] = 493;
		item_price[Equipment_Type::T_PANT][Pant_Type::SHOP_PANT3 - 1] = 1600;
		item_price[Equipment_Type::T_PANT][Pant_Type::SHOP_PANT4 - 1] = 2088;

		item_price[Equipment_Type::T_GLOVE][Glove_Type::SHOP_GLOVE1 - 1] = 175;
		item_price[Equipment_Type::T_GLOVE][Glove_Type::SHOP_GLOVE2 - 1] = 532;
		item_price[Equipment_Type::T_GLOVE][Glove_Type::SHOP_GLOVE3 - 1] = 1715;
		item_price[Equipment_Type::T_GLOVE][Glove_Type::SHOP_GLOVE4 - 1] = 2139;

		item_price[Equipment_Type::T_SHOE][Shoe_Type::SHOP_SHOE1 - 1] = 100;
		item_price[Equipment_Type::T_SHOE][Shoe_Type::SHOP_SHOE2 - 1] = 450;
		item_price[Equipment_Type::T_SHOE][Shoe_Type::SHOP_SHOE3 - 1] = 1500;
		item_price[Equipment_Type::T_SHOE][Shoe_Type::SHOP_SHOE4 - 1] = 2000;

		break;
	case Shop_Type::Accessory_Type:
		break;
	default:
		break;
	}
}

void Shop::Set_Select_Item(const int& select_item) {
	this->select_item = select_item;
}

void Reset_Shop(Shop& shop, const RECT it_rect, const int& shop_type) {
	shop.Set_Shop_Type(shop_type);
	shop.Set_Select_Item(0);
	shop.Set_Bitmap();
	shop.Set_Pos(it_rect);
	shop.Set_Item_Price();
}

void Paint_Shop(HDC hdc, HDC bitdc, const Player_Equipment& p_equip, const Shop& shop) {
	SelectObject(bitdc, shop.Get_Shop_Bitmap());
	
	TransparentBlt(hdc, shop.Get_Pos().x, shop.Get_Pos().y, shop.Get_Shop_Bitmap_Size().bmWidth, shop.Get_Shop_Bitmap_Size().bmHeight,
		bitdc, 0, 0, shop.Get_Shop_Bitmap_Size().bmWidth, shop.Get_Shop_Bitmap_Size().bmHeight, RGB(255, 255, 255));

	//상점 장비들을 출력합니다.
	switch (shop.Get_Shop_Type())
	{
	case Shop_Type::Equipment_Type:
		for (int e_type = Equipment_Type::T_HELMET; e_type <= Equipment_Type::T_SHOE; e_type++) {
			for (int index = 0; index < 4; index++) {
				SelectObject(bitdc, shop.Get_Shop_Item_Bitmap(e_type, index));
				TransparentBlt(hdc, shop.Get_Pos().x + 18 + 43 * e_type, shop.Get_Pos().y + 246 + 43 * index, shop.Get_Select_Bitmap_Size().bmWidth, shop.Get_Select_Bitmap_Size().bmHeight,
					bitdc, 0, 0, shop.Get_Select_Bitmap_Size().bmWidth, shop.Get_Select_Bitmap_Size().bmHeight, RGB(0, 0, 0));
			}
		}
		break;
	case Shop_Type::Accessory_Type:
		break;
	default:
		break;
	}

	//선택한 장비를 나타내는 이미지를 출력합니다.
	SelectObject(bitdc, shop.Get_Select_Bitmap());

	TransparentBlt(hdc, shop.Get_Pos().x + 18 + 43 * (shop.Get_Select_Item() % 5), shop.Get_Pos().y + 246 + 43 * (shop.Get_Select_Item() / 5), shop.Get_Select_Bitmap_Size().bmWidth, shop.Get_Select_Bitmap_Size().bmHeight,
		bitdc, 0, 0, shop.Get_Select_Bitmap_Size().bmWidth, shop.Get_Select_Bitmap_Size().bmHeight, RGB(150, 150, 150));

	SetBkMode(hdc, TRANSPARENT);
	//선택한 장비의 정보를 출력합니다.
	SelectObject(hdc, p_equip.Get_Font(0));
	switch (shop.Get_Shop_Type())
	{
	case Shop_Type::Equipment_Type:
		switch (shop.Get_Select_Item() % 5)
		{
		case Equipment_Type::T_HELMET:
			Paint_Helmet_Info(hdc, p_equip.Get_Helmet_Const(), { shop.Get_Pos().x + 40, shop.Get_Pos().y + 40 }, shop.Get_Select_Item() / 5 + 1, p_equip.Get_Font(1));
			break;
		case Equipment_Type::T_ARMOR:
			Paint_Armor_Info(hdc, p_equip.Get_Armor_Const(), { shop.Get_Pos().x + 40, shop.Get_Pos().y + 40 }, shop.Get_Select_Item() / 5 + 1, p_equip.Get_Font(1));
			break;
		case Equipment_Type::T_PANT:
			Paint_Pant_Info(hdc, p_equip.Get_Pant_Const(), { shop.Get_Pos().x + 40, shop.Get_Pos().y + 40 }, shop.Get_Select_Item() / 5 + 1, p_equip.Get_Font(1));
			break;
		case Equipment_Type::T_GLOVE:
			Paint_Glove_Info(hdc, p_equip.Get_Glove_Const(), { shop.Get_Pos().x + 40, shop.Get_Pos().y + 40 }, shop.Get_Select_Item() / 5 + 1, p_equip.Get_Font(1));
			break;
		case Equipment_Type::T_SHOE:
			Paint_Shoe_Info(hdc, p_equip.Get_Shoe_Const(), { shop.Get_Pos().x + 40, shop.Get_Pos().y + 40 }, shop.Get_Select_Item() / 5 + 1, p_equip.Get_Font(1));
			break;
		default:
			break;
		}
		break;
	case Shop_Type::Accessory_Type:
		break;
	default:
		break;
	}

	//가격 출력
	SelectObject(hdc, p_equip.Get_Font(2));
	TextOut(hdc, shop.Get_Pos().x + 300, shop.Get_Pos().y + 40, _T("Price"), 5);
	TCHAR price[7];
	wsprintf(price, _T("%5dG"), shop.Get_Item_Price(shop.Get_Select_Item() % 5, shop.Get_Select_Item() / 5));
	TextOut(hdc, shop.Get_Pos().x + 290, shop.Get_Pos().y + 60, price, 7);
		
}

const bool Change_Select_Item(Shop& shop, const WPARAM wParam) {
	switch (wParam)
	{
	case VK_LEFT:
		if (shop.Get_Select_Item() % 5 > 0)
			shop.Set_Select_Item(shop.Get_Select_Item() - 1);
		break;
	case VK_RIGHT:
		if (shop.Get_Select_Item() % 5 < 4)
			shop.Set_Select_Item(shop.Get_Select_Item() + 1);
		break;
	case VK_UP:
		if (shop.Get_Select_Item() / 5 > 0)
			shop.Set_Select_Item(shop.Get_Select_Item() - 5);
		break;
	case VK_DOWN:
		if (shop.Get_Select_Item() / 5 < 3)
			shop.Set_Select_Item(shop.Get_Select_Item() + 5);
		break;
	case VK_RETURN:
		return true;
	default:
		break;
	}
	return false;
}

const bool Buy_Equipment_Shop(Player_Equipment& p_equip, Shop& shop) {
	if (p_equip.Get_Gold() >= shop.Get_Item_Price(shop.Get_Select_Item() % 5, shop.Get_Select_Item() / 5)) {
		p_equip.Set_Own(shop.Get_Select_Item() % 5, shop.Get_Select_Item() / 5 + 1);
		p_equip.Set_Gold(p_equip.Get_Gold() - shop.Get_Item_Price(shop.Get_Select_Item() % 5, shop.Get_Select_Item() / 5));
		return true;
	}
	return false;	
}