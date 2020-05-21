#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Equipment.h"
#include "Object_Info.h"

/*equipment helmet*/

const int& E_Helmet::Get_Mp() const {
	return mp;
}

const int& E_Helmet::Get_Defence() const {
	return defence;
}

void E_Helmet::Select_Helmet(const int& helmet_type) {
	switch (helmet_type)
	{
	case Helmet_Type::DEFUALT_HELMET:
		mp = 25;
		defence = 2;
		break;
	case Helmet_Type::SHOP_HELMET1:
		mp = 50;
		defence = 4;
		break;
	case Helmet_Type::SHOP_HELMET2:
		mp = 75;
		defence = 7;
		break;
	case Helmet_Type::SHOP_HELMET3:
		mp = 100;
		defence = 11;
		break;
	case Helmet_Type::SHOP_HELMET4:
		mp = 125;
		defence = 16;
		break;
	default:
		break;
	}
}

void Reset_Helmet(E_Helmet& e_helmet, const int& helmet_type) {
	e_helmet.Select_Helmet(helmet_type);
}

void Paint_Helmet_Info(HDC hdc, const E_Helmet& helmet, const POINT& pos, const int& helmet_type, const HFONT font) {
	switch (helmet_type)
	{
	case Helmet_Type::DEFUALT_HELMET:
		TextOut(hdc, pos.x, pos.y, _T("허름한 투구"), 6);
		break;
	case Helmet_Type::SHOP_HELMET1:
		TextOut(hdc, pos.x, pos.y, _T("레더 투구"), 5);
		break;
	case Helmet_Type::SHOP_HELMET2:
		TextOut(hdc, pos.x, pos.y, _T("가죽 투구"), 5);
		break;
	case Helmet_Type::SHOP_HELMET3:
		TextOut(hdc, pos.x, pos.y, _T("철제 투구"), 5);
		break;
	case Helmet_Type::SHOP_HELMET4:
		TextOut(hdc, pos.x, pos.y, _T("강철 투구"), 5);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("마나 + %d"), helmet.Get_Mp());
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("방어력 + %d"), helmet.Get_Defence());
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Helmet(const E_Helmet& e_helmet, Object_Info& o_info, const bool& New) {
	o_info.Set_Max_Mp(o_info.Get_Max_Mp() + (New ? e_helmet.Get_Mp() : -e_helmet.Get_Mp()));
	o_info.Set_Mp(o_info.Get_Mp() + (New ? e_helmet.Get_Mp() : -e_helmet.Get_Mp()));
	o_info.Set_Defence(o_info.Get_Defence() + (New ? e_helmet.Get_Defence() : -e_helmet.Get_Defence()));
}

/*equipment armor*/

const int& E_Armor::Get_Hp() const {
	return hp;
}

const int& E_Armor::Get_Defence() const {
	return defence;
}

void E_Armor::Select_Armor(const int& armor_type) {
	switch (armor_type)
	{
	case Armor_Type::DEFUALT_ARMOR:
		hp = 15;
		defence = 10;
		break;
	case Armor_Type::SHOP_ARMOR1:
		hp = 33;
		defence = 20;
		break;
	case Armor_Type::SHOP_ARMOR2:
		hp = 66;
		defence = 30;
		break;
	case Armor_Type::SHOP_ARMOR3:
		hp = 102;
		defence = 40;
		break;
	case Armor_Type::SHOP_ARMOR4:
		hp = 158;
		defence = 50;
		break;
	default:
		break;
	}
}

void Reset_Armor(E_Armor& e_armor, const int& armor_type) {
	e_armor.Select_Armor(armor_type);
}

void Paint_Armor_Info(HDC hdc, const E_Armor& e_armor, const POINT& pos, const int& armor_type, const HFONT font) {
	switch (armor_type)
	{
	case Armor_Type::DEFUALT_ARMOR:
		TextOut(hdc, pos.x, pos.y, _T("허름한 티셔츠"), 7);
		break;
	case Armor_Type::SHOP_ARMOR1:
		TextOut(hdc, pos.x, pos.y, _T("레더 아머"), 5);
		break;
	case Armor_Type::SHOP_ARMOR2:
		TextOut(hdc, pos.x, pos.y, _T("가죽 아머"), 5);
		break;
	case Armor_Type::SHOP_ARMOR3:
		TextOut(hdc, pos.x, pos.y, _T("철제 아머"), 5);
		break;
	case Armor_Type::SHOP_ARMOR4:
		TextOut(hdc, pos.x, pos.y, _T("강철 아머"), 5);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("채력 + %d"), e_armor.Get_Hp());
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("방어력 + %d"), e_armor.Get_Defence());
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Armor(const E_Armor& e_armor, Object_Info& o_info, const bool& New) {
	o_info.Set_Max_Hp(o_info.Get_Max_Hp() + (New ? e_armor.Get_Hp() : -e_armor.Get_Hp()));
	o_info.Set_Hp(o_info.Get_Hp() + (New ? e_armor.Get_Hp() : -e_armor.Get_Hp()));
	o_info.Set_Defence(o_info.Get_Defence() + (New ? e_armor.Get_Defence() : -e_armor.Get_Defence()));
}

/*equipment pant*/

const int& E_Pant::Get_Hp() const {
	return hp;
}

const int& E_Pant::Get_Defence() const {
	return defence;
}

void E_Pant::Select_Pant(const int& pant_type) {
	switch (pant_type)
	{
	case Pant_Type::DEFUALT_PANT:
		hp = 30;
		defence = 5;
		break;
	case Pant_Type::SHOP_PANT1:
		hp = 58;
		defence = 10;
		break;
	case Pant_Type::SHOP_PANT2:
		hp = 96;
		defence = 17;
		break;
	case Pant_Type::SHOP_PANT3:
		hp = 144;
		defence = 24;
		break;
	case Pant_Type::SHOP_PANT4:
		hp = 208;
		defence = 30;
		break;
	default:
		break;
	}
}

void Reset_Pant(E_Pant& e_pant, const int& pant_type) {
	e_pant.Select_Pant(pant_type);
}

void Paint_Pant_Info(HDC hdc, const E_Pant& e_pant, const POINT& pos, const int& pant_type, const HFONT font) {
	switch (pant_type)
	{
	case Pant_Type::DEFUALT_PANT:
		TextOut(hdc, pos.x, pos.y, _T("허름한 바지"), 6);
		break;
	case Pant_Type::SHOP_PANT1:
		TextOut(hdc, pos.x, pos.y, _T("레더 팬츠"), 5);
		break;
	case Pant_Type::SHOP_PANT2:
		TextOut(hdc, pos.x, pos.y, _T("가죽 팬츠"), 5);
		break;
	case Pant_Type::SHOP_PANT3:
		TextOut(hdc, pos.x, pos.y, _T("철제 팬츠"), 5);
		break;
	case Pant_Type::SHOP_PANT4:
		TextOut(hdc, pos.x, pos.y, _T("강철 팬츠"), 5);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("채력 + %d"), e_pant.Get_Hp());
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("방어력 + %d"), e_pant.Get_Defence());
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Pant(const E_Pant& e_pant, Object_Info& o_info, const bool& New) {
	o_info.Set_Max_Hp(o_info.Get_Max_Hp() + (New ? e_pant.Get_Hp() : -e_pant.Get_Hp()));
	o_info.Set_Hp(o_info.Get_Hp() + (New ? e_pant.Get_Hp() : -e_pant.Get_Hp()));
	o_info.Set_Defence(o_info.Get_Defence() + (New ? e_pant.Get_Defence() : -e_pant.Get_Defence()));
}

/*equipment glove*/

const int& E_Glove::Get_Attack() const {
	return attack;
}

const int& E_Glove::Get_Fatal() const {
	return fatal;
}

void E_Glove::Select_Glove(const int& glove_type) {
	switch (glove_type)
	{
	case Glove_Type::DEFUALT_GLOVE:
		attack = 5;
		fatal = 1;
		break;
	case Glove_Type::SHOP_GLOVE1:
		attack = 8;
		fatal = 2;
		break;
	case Glove_Type::SHOP_GLOVE2:
		attack = 12;
		fatal = 3;
		break;
	case Glove_Type::SHOP_GLOVE3:
		attack = 16;
		fatal = 4;
		break;
	case Glove_Type::SHOP_GLOVE4:
		attack = 20;
		fatal = 5;
		break;
	default:
		break;
	}
}

void Reset_Glove(E_Glove& e_glove, const int& glove_type) {
	e_glove.Select_Glove(glove_type);
}

void Paint_Glove_Info(HDC hdc, const E_Glove& e_glove, const POINT& pos, const int& glove_type, const HFONT font) {
	switch (glove_type)
	{
	case Glove_Type::DEFUALT_GLOVE:
		TextOut(hdc, pos.x, pos.y, _T("허름한 장갑"), 6);
		break;
	case Glove_Type::SHOP_GLOVE1:
		TextOut(hdc, pos.x, pos.y, _T("레더 장갑"), 5);
		break;
	case Glove_Type::SHOP_GLOVE2:
		TextOut(hdc, pos.x, pos.y, _T("가죽 장갑"), 5);
		break;
	case Glove_Type::SHOP_GLOVE3:
		TextOut(hdc, pos.x, pos.y, _T("철제 장갑"), 5);
		break;
	case Glove_Type::SHOP_GLOVE4:
		TextOut(hdc, pos.x, pos.y, _T("강철 장갑"), 5);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("공격력 + %d"), e_glove.Get_Attack());
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("치명타 확률 + %d"), e_glove.Get_Fatal());
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Glove(const E_Glove& e_glove, Object_Info& o_info, const bool& New) {
	o_info.Set_Attack(o_info.Get_Attack() + (New ? e_glove.Get_Attack() : -e_glove.Get_Attack()));
	o_info.Set_Fatal(o_info.Get_Fatal() + (New ? e_glove.Get_Fatal() : -e_glove.Get_Fatal()));
}

/*equipment shoe*/
const int& E_Shoe::Get_Hp() const {
	return hp;
}

const int& E_Shoe::Get_Mp() const {
	return mp;
}

void E_Shoe::Select_Shoe(const int& shoe_type) {
	switch (shoe_type)
	{
	case Shoe_Type::DEFUALT_SHOE:
		hp = 5;
		mp = 5;
		break;
	case Shoe_Type::SHOP_SHOE1:
		hp = 15;
		mp = 12;
		break;
	case Shoe_Type::SHOP_SHOE2:
		hp = 30;
		mp = 20;
		break;
	case Shoe_Type::SHOP_SHOE3:
		hp = 44;
		mp = 28;
		break;
	case Shoe_Type::SHOP_SHOE4:
		hp = 60;
		mp = 40;
		break;
	default:
		break;
	}
}

void Reset_Shoe(E_Shoe& e_shoe, const int& shoe_type) {
	e_shoe.Select_Shoe(shoe_type);
}

void Paint_Shoe_Info(HDC hdc, const E_Shoe& e_shoe, const POINT& pos, const int& shoe_type, const HFONT font) {
	switch (shoe_type)
	{
	case Shoe_Type::DEFUALT_SHOE:
		TextOut(hdc, pos.x, pos.y, _T("허름한 신발"), 6);
		break;
	case Shoe_Type::SHOP_SHOE1:
		TextOut(hdc, pos.x, pos.y, _T("레더 신발"), 5);
		break;
	case Shoe_Type::SHOP_SHOE2:
		TextOut(hdc, pos.x, pos.y, _T("가죽 신발"), 5);
		break;
	case Shoe_Type::SHOP_SHOE3:
		TextOut(hdc, pos.x, pos.y, _T("철제 신발"), 5);
		break;
	case Shoe_Type::SHOP_SHOE4:
		TextOut(hdc, pos.x, pos.y, _T("강철 신발"), 5);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("체력 + %d"), e_shoe.Get_Hp());
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("마나 + %d"), e_shoe.Get_Mp());
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Shoe(const E_Shoe& e_shoe, Object_Info& o_info, const bool& New) {
	o_info.Set_Max_Hp(o_info.Get_Max_Hp() + (New ? e_shoe.Get_Hp() : -e_shoe.Get_Hp()));
	o_info.Set_Hp(o_info.Get_Hp() + (New ? e_shoe.Get_Hp() : -e_shoe.Get_Hp()));
	o_info.Set_Max_Mp(o_info.Get_Max_Mp() + (New ? e_shoe.Get_Mp() : -e_shoe.Get_Mp()));
	o_info.Set_Mp(o_info.Get_Mp() + (New ? e_shoe.Get_Mp() : -e_shoe.Get_Mp()));
}

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
			fatal = 3;
			break;
		case Weapon_Type::SHOP_WEAPON1:
			attack = 20;
			fatal = 5;
			break;
		case Weapon_Type::SHOP_WEAPON2:
			attack = 33;
			fatal = 8;
			break;
		case Weapon_Type::SHOP_WEAPON3:
			attack = 47;
			fatal = 10;
			break;
		case Weapon_Type::SHOP_WEAPON4:
			attack = 60;
			fatal = 12;
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Reset_Weapon(E_Weapon& e_weapon, const int& class_type, const int& weapon_type) {
	e_weapon.Select_Weapon(class_type, weapon_type);
}

void Paint_Weapon_Info(HDC hdc, const E_Weapon& e_weapon, const POINT& pos, const int& weapon_type, const HFONT font) {
	switch (weapon_type)
	{
	case Weapon_Type::DEFUALT_WEAPON:
		TextOut(hdc, pos.x, pos.y, _T("허름한 검"), 5);
		break;
	case Weapon_Type::SHOP_WEAPON1:
		TextOut(hdc, pos.x, pos.y, _T("훈련용 검"), 5);
		break;
	case Weapon_Type::SHOP_WEAPON2:
		TextOut(hdc, pos.x, pos.y, _T("황금 검"), 4);
		break;
	case Weapon_Type::SHOP_WEAPON3:
		TextOut(hdc, pos.x, pos.y, _T("붉은 눈의 검"), 7);
		break;
	case Weapon_Type::SHOP_WEAPON4:
		TextOut(hdc, pos.x, pos.y, _T("전설의 검"), 5);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("공격력 + %d"), e_weapon.Get_Attack());
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("치명타 확률 + %d"), e_weapon.Get_Fatal());
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Weapon(const E_Weapon& e_weapon, Object_Info& o_info, const bool& New) {
	o_info.Set_Attack(o_info.Get_Attack() + (New ? e_weapon.Get_Attack() : -e_weapon.Get_Attack()));
	o_info.Set_Fatal(o_info.Get_Fatal() + (New ? e_weapon.Get_Fatal() : -e_weapon.Get_Fatal()));
}

/*player equipment*/

Player_Equipment::~Player_Equipment() {
	Delete_Class<E_Helmet>(&helmet);
	Delete_Class<E_Armor>(&armor);
	Delete_Class<E_Pant>(&pant);
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

const E_Pant& Player_Equipment::Get_Pant_Const() const {
	return *pant;
}

E_Pant& Player_Equipment::Get_Pant() const {
	return *pant;
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

const HFONT Player_Equipment::Get_Font(const int& index) const {
	return equip_font[index];
}

void Player_Equipment::Create_Equipment() {
	helmet = Create_Class<E_Helmet>();
	armor = Create_Class<E_Armor>();
	pant = Create_Class<E_Pant>();
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
	for (int p_type = Pant_Type::DEFUALT_PANT; p_type <= Pant_Type::SHOP_PANT4; p_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Pant\\Pant%d.bmp"), p_type + 1);
		equipment_bitmap[Equipment_Type::T_PANT][p_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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

void Player_Equipment::Set_Font() {
	equip_font[0] = CreateFont(50, 20, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼편지체"));
	equip_font[1] = CreateFont(35, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼편지체"));
	equip_font[2] = CreateFont(17, 7, 0, 0, NULL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼매직체"));
}

void Reset_Player_Equipment(Player_Equipment& p_equip, Object_Info& o_info) {
	p_equip.Create_Equipment();
	p_equip.Set_Pos({ 60,60 });
	p_equip.Set_Type_Select(Equipment_Type::T_HELMET);
	for (int e_type = Equipment_Type::T_HELMET; e_type <= Equipment_Type::T_WEAPON; e_type++) {
		p_equip.Set_Equipment_Detail_Select(e_type, 0);
		p_equip.Set_Own(e_type, 0);
	}
	p_equip.Set_Change_Select(false);
	p_equip.Set_Bitmap();
	p_equip.Set_Font();

	//기본 장비의 능력치를 Object_Info에 갱신시킨다.
	Reset_Helmet(p_equip.Get_Helmet(), p_equip.Get_Equipment_Detail_Select(Equipment_Type::T_HELMET));
	Readjust_Info_By_Helmet(p_equip.Get_Helmet_Const(), o_info, true);
	Reset_Armor(p_equip.Get_Armor(), p_equip.Get_Equipment_Detail_Select(Equipment_Type::T_ARMOR));
	Readjust_Info_By_Armor(p_equip.Get_Armor_Const(), o_info, true);
	Reset_Pant(p_equip.Get_Pant(), p_equip.Get_Equipment_Detail_Select(Equipment_Type::T_PANT));
	Readjust_Info_By_Pant(p_equip.Get_Pant_Const(), o_info, true);
	Reset_Glove(p_equip.Get_Glove(), p_equip.Get_Equipment_Detail_Select(Equipment_Type::T_GLOVE));
	Readjust_Info_By_Glove(p_equip.Get_Glove_Const(), o_info, true);
	Reset_Shoe(p_equip.Get_Shoe(), p_equip.Get_Equipment_Detail_Select(Equipment_Type::T_SHOE));
	Readjust_Info_By_Shoe(p_equip.Get_Shoe_Const(), o_info, true);
	Reset_Weapon(p_equip.Get_Weapon(), Class_Type::Warrior, p_equip.Get_Equipment_Detail_Select(Equipment_Type::T_WEAPON));
	Readjust_Info_By_Weapon(p_equip.Get_Weapon_Const(), o_info, true);
	
}

void Paint_Player_Equipment(HDC hdc, HDC bitdc, const Player_Equipment& p_equip, const Object_Info& o_info, const int& gold) {
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

	SetBkMode(hdc, TRANSPARENT);
	//선택한 장비의 정보를 출력합니다.
	//상점에서도 구현될 내용이니 따로 함수를 만들어야한다.
	SelectObject(hdc, p_equip.Get_Font(0));
	switch (p_equip.Get_Type_Select())
	{
	case Equipment_Type::T_HELMET:
		Paint_Helmet_Info(hdc, p_equip.Get_Helmet_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	case Equipment_Type::T_ARMOR:
		Paint_Armor_Info(hdc, p_equip.Get_Armor_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	case Equipment_Type::T_PANT:
		Paint_Pant_Info(hdc, p_equip.Get_Pant_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	case Equipment_Type::T_GLOVE:
		Paint_Glove_Info(hdc, p_equip.Get_Glove_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	case Equipment_Type::T_SHOE:
		Paint_Shoe_Info(hdc, p_equip.Get_Shoe_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	case Equipment_Type::T_WEAPON:
		Paint_Weapon_Info(hdc, p_equip.Get_Weapon_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	default:
		break;
	}


	//플레이어의 정보를 출력합니다.
	SelectObject(hdc, p_equip.Get_Font(2));
	SetTextColor(hdc, RGB(255, 255, 255));
	wchar_t text[20];

	wsprintf(text, _T("Warrior"), o_info.Get_Hp(), o_info.Get_Max_Hp());
	TextOut(hdc, p_equip.Get_Pos().x + 25, p_equip.Get_Pos().y + 450, text, _tcslen(text));
	wsprintf(text, _T("LEVEL : %d"), o_info.Get_Level());
	TextOut(hdc, p_equip.Get_Pos().x + 143, p_equip.Get_Pos().y + 450, text, _tcslen(text));
	wsprintf(text, _T("HP : %4d/%d"), o_info.Get_Hp(), o_info.Get_Max_Hp());
	TextOut(hdc, p_equip.Get_Pos().x + 262, p_equip.Get_Pos().y + 450, text, _tcslen(text));
	wsprintf(text, _T("MP : %4d/%d"), o_info.Get_Mp(), o_info.Get_Max_Mp());
	TextOut(hdc, p_equip.Get_Pos().x + 381, p_equip.Get_Pos().y + 450, text, _tcslen(text));
	wsprintf(text, _T("Gold : %d"), gold);
	TextOut(hdc, p_equip.Get_Pos().x + 25, p_equip.Get_Pos().y + 490, text, _tcslen(text));
	wsprintf(text, _T("ATK : %d"), o_info.Get_Attack());
	TextOut(hdc, p_equip.Get_Pos().x + 143, p_equip.Get_Pos().y + 490, text, _tcslen(text));
	wsprintf(text, _T("DEF : %d"), o_info.Get_Defence());
	TextOut(hdc, p_equip.Get_Pos().x + 262, p_equip.Get_Pos().y + 490, text, _tcslen(text));
	wsprintf(text, _T("FATAL : %d%%"), o_info.Get_Fatal());
	TextOut(hdc, p_equip.Get_Pos().x + 381, p_equip.Get_Pos().y + 490, text, _tcslen(text));
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

void Change_Select_Equipment_Detail(Player_Equipment& p_equip, Object_Info& o_info, WPARAM wParam) {
	switch (wParam)
	{
		//나중에 OWN도 추가 해서 구현
	case VK_LEFT:
	case VK_RIGHT:
		if (wParam == VK_LEFT) {
			if (p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) > 0) {
				for (int index = p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) - 1; index >= 0; index--) {
					if (p_equip.Is_Own(p_equip.Get_Type_Select(), index)) {
						p_equip.Set_Equipment_Detail_Select(p_equip.Get_Type_Select(), index);
						break;
					}
				}
			}
		}
		else {
			if (p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) < 10) {
				for (int index = p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) + 1; index < 10; index++) {
					if (p_equip.Is_Own(p_equip.Get_Type_Select(), index)) {
						p_equip.Set_Equipment_Detail_Select(p_equip.Get_Type_Select(), index);
						break;
					}
				}				
			}
		}
		//반지는 10까지 없다. 나중에 바꿔주자.

		//플레이어 정보 재조정
		switch (p_equip.Get_Type_Select())
		{
		case Equipment_Type::T_HELMET:
			Readjust_Info_By_Helmet(p_equip.Get_Helmet_Const(), o_info, false);
			Reset_Helmet(p_equip.Get_Helmet(), p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()));
			Readjust_Info_By_Helmet(p_equip.Get_Helmet_Const(), o_info, true);
			break;
		case Equipment_Type::T_ARMOR:
			Readjust_Info_By_Armor(p_equip.Get_Armor_Const(), o_info, false);
			Reset_Armor(p_equip.Get_Armor(), p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()));
			Readjust_Info_By_Armor(p_equip.Get_Armor_Const(), o_info, true);
			break;
		case Equipment_Type::T_PANT:
			Readjust_Info_By_Pant(p_equip.Get_Pant_Const(), o_info, false);
			Reset_Pant(p_equip.Get_Pant(), p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()));
			Readjust_Info_By_Pant(p_equip.Get_Pant_Const(), o_info, true);
			break;
		case Equipment_Type::T_GLOVE:
			Readjust_Info_By_Glove(p_equip.Get_Glove_Const(), o_info, false);
			Reset_Glove(p_equip.Get_Glove(), p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()));
			Readjust_Info_By_Glove(p_equip.Get_Glove_Const(), o_info, true);
			break;
		case Equipment_Type::T_SHOE:
			Readjust_Info_By_Shoe(p_equip.Get_Shoe_Const(), o_info, false);
			Reset_Shoe(p_equip.Get_Shoe(), p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()));
			Readjust_Info_By_Shoe(p_equip.Get_Shoe_Const(), o_info, true);
			break;
		case Equipment_Type::T_WEAPON:
			Readjust_Info_By_Weapon(p_equip.Get_Weapon_Const(), o_info, false);
			Reset_Weapon(p_equip.Get_Weapon(), Class_Type::Warrior, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()));
			Readjust_Info_By_Weapon(p_equip.Get_Weapon_Const(), o_info, true);
			break;
		default:
			break;
		}
	
	
	
		break;
	case VK_RETURN:
		p_equip.Set_Change_Select(false);
		break;
	default:
		break;
	}
}