#pragma once
#include <Windows.h>

class Object_Info;

enum Equipment_Type {
	T_HELMET, T_ARMOR, T_PANT, T_GLOVE, T_SHOE, T_WEAPON, T_AMULET, T_RING, T_CLOAK, T_BOOK
};

enum Helmet_Type {
	DEFUALT_HELMET, SHOP_HELMET1, SHOP_HELMET2, SHOP_HELMET3, SHOP_HELMET4
};

enum Armor_Type {
	DEFUALT_ARMOR, SHOP_ARMOR1, SHOP_ARMOR2, SHOP_ARMOR3, SHOP_ARMOR4
};

enum Pant_Type {
	DEFUALT_PANT, SHOP_PANT1, SHOP_PANT2, SHOP_PANT3, SHOP_PANT4
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
	const int& Get_Mp(const int& helmet_type) const;
	const int& Get_Defence(const int& helmet_type) const;

	void Set_Helmet();
private:
	int mp[10];
	int defence[10];
};

void Reset_Helmet(E_Helmet& e_helmet);
void Paint_Helmet_Info(HDC hdc, const E_Helmet& e_helmet, const POINT& pos, const int& helmet_type, const HFONT font);
void Readjust_Info_By_Helmet(const E_Helmet& e_helmet, Object_Info& o_info, const int& helmet_type, const bool& New);

class E_Armor {
public:
	const int& Get_Hp(const int& armor_type) const;
	const int& Get_Defence(const int& armor_type) const;

	void Set_Armor();
private:
	int hp[10];
	int defence[10];
};

void Reset_Armor(E_Armor& e_armor);
void Paint_Armor_Info(HDC hdc, const E_Armor& e_armor, const POINT& pos, const int& armor_type, const HFONT font);
void Readjust_Info_By_Armor(const E_Armor& e_armor, Object_Info& o_info, const int& armor_type, const bool& New);

class E_Pant {
public:
	const int& Get_Hp(const int& pant_type) const;
	const int& Get_Defence(const int& pant_type) const;

	void Set_Pant();
private:
	int hp[10];
	int defence[10];
};

void Reset_Pant(E_Pant& e_pant);
void Paint_Pant_Info(HDC hdc, const E_Pant& e_pant, const POINT& pos, const int& pant_type, const HFONT font);
void Readjust_Info_By_Pant(const E_Pant& e_pant, Object_Info& o_info, const int& pant_type, const bool& New);

class E_Glove {
public:
	const int& Get_Attack(const int& glove_type) const;
	const int& Get_Fatal(const int& glove_type) const;

	void Set_Glove();
private:
	int attack[10];
	int fatal[10];
};

void Reset_Glove(E_Glove& e_glove);
void Paint_Glove_Info(HDC hdc, const E_Glove& e_glove, const POINT& pos, const int& glove_type, const HFONT font);
void Readjust_Info_By_Glove(const E_Glove& e_glove, Object_Info& o_info, const int& glove_type, const bool& New);

class E_Shoe {
public:
	const int& Get_Hp(const int& shoe_type) const;
	const int& Get_Mp(const int& shoe_type) const;

	void Set_Shoe();
private:
	int hp[10];
	int mp[10];
};

void Reset_Shoe(E_Shoe& e_shoe);
void Paint_Shoe_Info(HDC hdc, const E_Shoe& e_shoe, const POINT& pos, const int& shoe_type, const HFONT font);
void Readjust_Info_By_Shoe(const E_Shoe& e_shoe, Object_Info& o_info, const int& shoe_type, const bool& New);

class E_Weapon {
public:
	const int& Get_Attack(const int& weapon_type) const;
	const int& Get_Fatal(const int& weapon_type) const;

	void Set_Weapon(const int& class_type);
private:
	int attack[10];
	int fatal[10];
};

void Reset_Weapon(E_Weapon& e_weapon, const int& class_type);
void Paint_Weapon_Info(HDC hdc, const E_Weapon& e_weapon, const POINT& pos, const int& weapon_type, const HFONT font);
void Readjust_Info_By_Weapon(const E_Weapon& e_weapon, Object_Info& o_info, const int& weapon_type, const bool& New);

class Player_Equipment {
public:
	~Player_Equipment();

	const POINT& Get_Pos() const;
	const E_Helmet& Get_Helmet_Const() const;
	E_Helmet& Get_Helmet() const;
	const E_Armor& Get_Armor_Const() const;
	E_Armor& Get_Armor() const;
	const E_Pant& Get_Pant_Const() const;
	E_Pant& Get_Pant() const;
	const E_Glove& Get_Glove_Const() const;
	E_Glove& Get_Glove() const;
	const E_Shoe& Get_Shoe_Const() const;
	E_Shoe& Get_Shoe() const;
	const E_Weapon& Get_Weapon_Const() const;
	E_Weapon& Get_Weapon() const;
	const int& Get_Gold() const;

	const int& Get_Type_Select() const;
	const int& Get_Equipment_Detail_Select(const int& e_type) const;
	const bool& Is_Chnage_Select() const;
	const bool& Is_Own(const int& e_type, const int& d_select) const;

	const HBITMAP& Get_Equipment_Interface_Bitmap() const;
	const BITMAP& Get_Equipment_Interface_Bitmap_Size() const;
	const HBITMAP& Get_Equipment_Bitmap(const int& e_type, const int& d_select) const;
	const HBITMAP& Get_Equipment_Select_Bitmap(const int& index) const;
	const BITMAP& Get_Equipment_Bitmap_Size() const;

	const HFONT Get_Font(const int& index) const;

	void Create_Equipment();

	void Set_Pos(const POINT& pos);
	void Set_Gold(const int& gold);
	
	void Set_Type_Select(const int& e_type);
	void Set_Equipment_Detail_Select(const int& e_type, const int& d_select);
	void Set_Change_Select(const bool& change_select);
	void Set_Own(const int& e_type, const int& d_select);

	void Set_Bitmap();
	void Set_Font();

private:
	POINT pos;
	E_Helmet* helmet;
	E_Armor* armor;
	E_Pant* pant;
	E_Glove* glove;
	E_Shoe* shoe;
	E_Weapon* weapon;
	int gold;

	int equipment_type_select;
	int equipment_detail_select[10];
	bool equipment_change_select;
	bool own[10][10];


	HBITMAP equipment_interface_bitmap;
	BITMAP equipment_interface_bitmap_size;
	HBITMAP equipment_bitmap[10][10];
	HBITMAP equipment_select_bitmap[2];
	BITMAP equipment_bitmap_size;
	
	HFONT equip_font[3];

	//스킬도 넣을건데..
};

void Reset_Player_Equipment(Player_Equipment& p_equip, Object_Info& o_info);
void Paint_Player_Equipment(HDC hdc, HDC bitdc, const Player_Equipment& p_equip, const Object_Info& o_info);
void Change_Equipment_Type_Select(Player_Equipment& p_equip, WPARAM wParam);
void Change_Select_Equipment_Detail(Player_Equipment& p_equip, Object_Info& o_info, WPARAM wParam);