#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Equipment.h"

/*equipment weapon*/

const int& E_Weapon::Get_Attack() const {
	return attack;
}

const int& E_Weapon::Get_Fatal() const {
	return fatal;
}

void E_Weapon::Select_Weapon(const int& class_type, const int& weapon_type) {
	switch (class_type)
	{
	case Class_Type::Warrior:
		switch (weapon_type)
		{
		case Weapon_Type::DEFUALT_WEAPON:
			attack = 10;
			fatal = 5;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}


/*player equipment*/

Player_Equipment::~Player_Equipment() {
	Delete_Class<E_Helmet>(&helmet);
	Delete_Class<E_Armor>(&armor);
	Delete_Class<E_Glove>(&glove);
	Delete_Class<E_Shoe>(&shoe);
	Delete_Class<E_Weapon>(&weapon);
	DeleteObject(equipment_interface_bitmap);
	for (int e_type = Equipment_Type::T_HELMET; e_type <= Equipment_Type::T_WEAPON; e_type++)
		for (int i = 0; i < 10; i++)
			DeleteObject(equipment_bitmap[e_type][i]);
}

const POINT& Player_Equipment::Get_Pos() const {
	return pos;
}

const E_Helmet& Player_Equipment::Get_Helmet_Const() const {
	return *helmet;
}

E_Helmet& Player_Equipment::Get_Helmet() const {
	return *helmet;
}

const E_Armor& Player_Equipment::Get_Armor_Const() const {
	return *armor;
}

E_Armor& Player_Equipment::Get_Armor() const {
	return *armor;
}

const E_Glove& Player_Equipment::Get_Glove_Const() const {
	return *glove;
}

E_Glove& Player_Equipment::Get_Glove() const {
	return *glove;
}

const E_Shoe& Player_Equipment::Get_Shoe_Const() const {
	return *shoe;
}

E_Shoe& Player_Equipment::Get_Shoe() const {
	return *shoe;
}

const E_Weapon& Player_Equipment::Get_Weapon_Const() const {
	return *weapon;
}

E_Weapon& Player_Equipment::Get_Weapon() const {
	return *weapon;
}

const int& Player_Equipment::Get_Type_Select() const {
	return equipment_type_select;
}

const int& Player_Equipment::Get_Equipment_Detail_Select(const int& e_type) const {
	return equipment_detail_select[e_type];
}

const bool& Player_Equipment::Is_Chnage_Select() const {
	return equipment_change_select;
}

const bool& Player_Equipment::Is_Own(const int& e_type, const int& d_select) const {
	return own[e_type][d_select];
}

const HBITMAP Player_Equipment::Get_Equipment_Interface_Bitmap() const {
	return equipment_interface_bitmap;
}

const BITMAP Player_Equipment::Get_Equipment_Interface_Bitmap_Size() const {
	return equipment_interface_bitmap_size;
}

const HBITMAP Player_Equipment::Get_Equipment_Bitmap(const int& e_type, const int& d_select) const {
	return equipment_bitmap[e_type][d_select];
}

const HBITMAP Player_Equipment::Get_Equipment_Select_Bitmap(const int& index) const {
	return equipment_select_bitmap[index];
}

const BITMAP Player_Equipment::Get_Equipment_Bitmap_Size() const {
	return equipment_bitmap_size;
}

void Player_Equipment::Create_Equipment() {
	helmet = Create_Class<E_Helmet>();
	armor = Create_Class<E_Armor>();
	glove = Create_Class<E_Glove>();
	shoe = Create_Class<E_Shoe>();
	weapon = Create_Class<E_Weapon>();
}

void Player_Equipment::Set_Pos(const POINT& pos) {
	this->pos = pos;
}

void Player_Equipment::Set_Type_Select(const int& e_type) {
	equipment_type_select = e_type;
}

void Player_Equipment::Set_Equipment_Detail_Select(const int& e_type, const int& d_select) {
	equipment_detail_select[e_type] = d_select;
}

void Player_Equipment::Set_Change_Select(const bool& change_select) {
	equipment_change_select = change_select;
}

void Player_Equipment::Set_Own(const int& e_type, const int& d_select) {
	own[e_type][d_select] = true;
}

void Player_Equipment::Set_Bitmap() {
	equipment_interface_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Inventory\\Inventory.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(equipment_interface_bitmap, sizeof(BITMAP), &equipment_interface_bitmap_size);

	
	for (int h_type = Helmet_Type::DEFUALT_HELMET; h_type <= Helmet_Type::SHOP_HELMET4; h_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Helmet\\Helmet%d.bmp"), h_type + 1);
		equipment_bitmap[Equipment_Type::T_HELMET][h_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	for (int a_type = Armor_Type::DEFUALT_ARMOR; a_type <= Armor_Type::SHOP_ARMOR4; a_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Armor\\Armor%d.bmp"), a_type + 1);
		equipment_bitmap[Equipment_Type::T_ARMOR][a_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	for (int g_type = Glove_Type::DEFUALT_GLOVE; g_type <= Glove_Type::SHOP_GLOVE4; g_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Glove\\Glove%d.bmp"), g_type + 1);
		equipment_bitmap[Equipment_Type::T_GLOVE][g_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	for (int s_type = Shoe_Type::DEFUALT_SHOE; s_type <= Shoe_Type::SHOP_SHOE4; s_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Shoe\\Shoe%d.bmp"), s_type + 1);
		equipment_bitmap[Equipment_Type::T_SHOE][s_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	for (int w_type = Weapon_Type::DEFUALT_WEAPON; w_type <= Weapon_Type::SHOP_WEAPON4; w_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Sword\\Sword%d.bmp"), w_type + 1);
		equipment_bitmap[Equipment_Type::T_WEAPON][w_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	GetObject(equipment_bitmap[0][0], sizeof(BITMAP), &equipment_bitmap_size);

	equipment_select_bitmap[0] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Inventory\\border1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	equipment_select_bitmap[1] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Inventory\\border2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void Reset_Player_Equipment(Player_Equipment& p_equip) {
	p_equip.Create_Equipment();
	p_equip.Set_Pos({ 60,60 });
	p_equip.Set_Type_Select(Equipment_Type::T_HELMET);
	for (int e_type = Equipment_Type::T_HELMET; e_type <= Equipment_Type::T_WEAPON; e_type++) {
		p_equip.Set_Equipment_Detail_Select(e_type, 0);
		p_equip.Set_Own(e_type, 0);
	}
	p_equip.Set_Change_Select(false);
	p_equip.Set_Bitmap();
}

void Paint_Player_Equipment(HDC hdc, HDC bitdc, const Player_Equipment& p_equip) {
	SelectObject(bitdc, p_equip.Get_Equipment_Interface_Bitmap());
	TransparentBlt(hdc, p_equip.Get_Pos().x, p_equip.Get_Pos().y, p_equip.Get_Equipment_Interface_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Interface_Bitmap_Size().bmHeight,
		bitdc, 0, 0, p_equip.Get_Equipment_Interface_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Interface_Bitmap_Size().bmHeight, RGB(255, 255, 255));

	//장비를 출력한다.
	for (int e_type = Equipment_Type::T_HELMET; e_type <= Equipment_Type::T_WEAPON; e_type++) {
		SelectObject(bitdc, p_equip.Get_Equipment_Bitmap(e_type, p_equip.Get_Equipment_Detail_Select(e_type)));
		TransparentBlt(hdc, p_equip.Get_Pos().x + 30 + 377 * (e_type / 5), p_equip.Get_Pos().y + 30 + (e_type % 5) * 80, p_equip.Get_Equipment_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Bitmap_Size().bmHeight,
			bitdc, 0, 0, p_equip.Get_Equipment_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Bitmap_Size().bmHeight, RGB(0, 0, 0));
	}

	//장비 선택 테두리를 출력한다.
	SelectObject(bitdc, p_equip.Get_Equipment_Select_Bitmap(p_equip.Is_Chnage_Select()));
	TransparentBlt(hdc, p_equip.Get_Pos().x + 30 + 377 * (p_equip.Get_Type_Select() / 5), p_equip.Get_Pos().y + 30 + (p_equip.Get_Type_Select() % 5) * 80, p_equip.Get_Equipment_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Bitmap_Size().bmHeight,
		bitdc, 0, 0, p_equip.Get_Equipment_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Bitmap_Size().bmHeight, RGB(150, 150, 150));
}

void Change_Equipment_Type_Select(Player_Equipment& p_equip, WPARAM wParam) {
	switch (wParam)
	{
	case VK_LEFT:
		if (p_equip.Get_Type_Select() >= Equipment_Type::T_WEAPON)
			p_equip.Set_Type_Select(p_equip.Get_Type_Select() - 5);
		break;
	case VK_RIGHT:
		if (p_equip.Get_Type_Select() < Equipment_Type::T_WEAPON)
			p_equip.Set_Type_Select(p_equip.Get_Type_Select() + 5);
		break;
	case VK_UP:
		if (p_equip.Get_Type_Select() % 5 > 0)
			p_equip.Set_Type_Select(p_equip.Get_Type_Select() - 1);
		break;
	case VK_DOWN:
		if (p_equip.Get_Type_Select() % 5 < 4)
			p_equip.Set_Type_Select(p_equip.Get_Type_Select() + 1);
		break;
	case VK_RETURN:
		p_equip.Set_Change_Select(true);
		break;
	default:
		break;
	}
}

void Change_Select_Equipment_Detail(Player_Equipment& p_equip, WPARAM wParam) {
	switch (wParam)
	{
		//나중에 OWN도 추가 해서 구현
	case VK_LEFT:
		if (p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) > 0)
			p_equip.Set_Equipment_Detail_Select(p_equip.Get_Type_Select(), p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) - 1);
		break;
	case VK_RIGHT:
		//반지는 10까지 없다. 나중에 바꿔주자.
		if (p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) < 10)
			p_equip.Set_Equipment_Detail_Select(p_equip.Get_Type_Select(), p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) + 1);
		break;
	case VK_RETURN:
		p_equip.Set_Change_Select(false);
		break;
	default:
		break;
	}
}