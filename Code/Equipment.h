#pragma once
#include <Windows.h>

enum Equipment_Type {
	T_HELMET, T_ARMOR, T_PANT, T_GLOVE, T_SHOE, T_WEAPON,
};

enum Helmet_Type {
	DEFUALT_HELMET, SHOP_HELMET1, SHOP_HELMET2, SHOP_HELMET3, SHOP_HELMET4
};

enum Armor_Type {
	DEFUALT_ARMOR, SHOP_ARMOR1, SHOP_ARMOR2, SHOP_ARMOR3, SHOP_ARMOR4
};

enum Glove_Type {
	DEFUALT_GLOVE, SHOP_GLOVE1, SHOP_GLOVE2, SHOP_GLOVE3, SHOP_GLOVE4
};

enum Shoe_Type {
	DEFUALT_SHOE, SHOP_SHOE1, SHOP_SHOE2, SHOP_SHOE3, SHOP_SHOE4
};

enum Weapon_Type {
	DEFUALT_WEAPON, SHOP_WEAPON1, SHOP_WEAPON2, SHOP_WEAPON3, SHOP_WEAPON4
};

class E_Helmet {
public:

private:
	int helmet_type;
	int hp;
};

class E_Armor {
public:

private:
	int armor_type;
	int defence;
};

class E_Glove {
public:

private:
	int glove_type;
	int fatal;
};

class E_Shoe {
public:

private:
	int shoe_type;
	int attack;
	int hp;
	int defence;
};

class E_Weapon {
public:
	const int& Get_Attack() const;
	const int& Get_Fatal() const;

	void Select_Weapon(const int& class_type, const int& weapon_type);
private:
	int attack;
	int fatal;
};

class Player_Equipment {
public:
	~Player_Equipment();

	const POINT& Get_Pos() const;
	const E_Helmet& Get_Helmet_Const() const;
	E_Helmet& Get_Helmet() const;
	const E_Armor& Get_Armor_Const() const;
	E_Armor& Get_Armor() const;
	const E_Glove& Get_Glove_Const() const;
	E_Glove& Get_Glove() const;
	const E_Shoe& Get_Shoe_Const() const;
	E_Shoe& Get_Shoe() const;
	const E_Weapon& Get_Weapon_Const() const;
	E_Weapon& Get_Weapon() const;

	const int& Get_Type_Select() const;
	const int& Get_Equipment_Detail_Select(const int& e_type) const;
	const bool& Is_Chnage_Select() const;
	const bool& Is_Own(const int& e_type, const int& d_select) const;

	const HBITMAP Get_Equipment_Interface_Bitmap() const;
	const BITMAP Get_Equipment_Interface_Bitmap_Size() const;
	const HBITMAP Get_Equipment_Bitmap(const int& e_type, const int& d_select) const;
	const HBITMAP Get_Equipment_Select_Bitmap(const int& index) const;
	const BITMAP Get_Equipment_Bitmap_Size() const;

	void Create_Equipment();
	
	void Set_Pos(const POINT& pos);
	void Set_Type_Select(const int& e_type);
	void Set_Equipment_Detail_Select(const int& e_type, const int& d_select);
	void Set_Change_Select(const bool& change_select);
	void Set_Own(const int& e_type, const int& d_select);

	void Set_Bitmap();

private:
	POINT pos;
	E_Helmet* helmet;
	E_Armor* armor;
	E_Glove* glove;
	E_Shoe* shoe;
	E_Weapon* weapon;

	int equipment_type_select;
	int equipment_detail_select[10];
	bool equipment_change_select;
	bool own[10][10];

	HBITMAP equipment_interface_bitmap;
	BITMAP equipment_interface_bitmap_size;
	HBITMAP equipment_bitmap[10][10];
	HBITMAP equipment_select_bitmap[2];
	BITMAP equipment_bitmap_size;


	//스킬도 넣을건데..
};

void Reset_Player_Equipment(Player_Equipment& p_equip);
void Paint_Player_Equipment(HDC hdc, HDC bitdc, const Player_Equipment& p_equip);
void Change_Equipment_Type_Select(Player_Equipment& p_equip, WPARAM wParam);
void Change_Select_Equipment_Detail(Player_Equipment& p_equip, WPARAM wParam);