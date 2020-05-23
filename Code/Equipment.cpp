#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Equipment.h"
#include "Object_Info.h"

/*equipment helmet*/

const int& E_Helmet::Get_Mp(const int& helmet_type) const {
	return mp[helmet_type];
}

const int& E_Helmet::Get_Defence(const int& helmet_type) const {
	return defence[helmet_type];
}

void E_Helmet::Set_Helmet() {
	
	mp[Helmet_Type::DEFUALT_HELMET] = 25;
	defence[Helmet_Type::DEFUALT_HELMET] = 2;

	mp[Helmet_Type::SHOP_HELMET1] = 50;
	defence[Helmet_Type::SHOP_HELMET1] = 4;

	mp[Helmet_Type::SHOP_HELMET2] = 100;
	defence[Helmet_Type::SHOP_HELMET2] = 11;

	mp[Helmet_Type::SHOP_HELMET3] = 150;
	defence[Helmet_Type::SHOP_HELMET3] = 20;

	mp[Helmet_Type::SHOP_HELMET4] = 200;
	defence[Helmet_Type::SHOP_HELMET4] = 25;
}

void Reset_Helmet(E_Helmet& e_helmet) {
	e_helmet.Set_Helmet();
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
	wsprintf(text, _T("마나 + %d"), helmet.Get_Mp(helmet_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("방어력 + %d"), helmet.Get_Defence(helmet_type));
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Helmet(const E_Helmet& e_helmet, Object_Info& o_info, const int& helmet_type, const bool& New) {
	o_info.Set_Max_Mp(o_info.Get_Max_Mp() + (New ? e_helmet.Get_Mp(helmet_type) : -e_helmet.Get_Mp(helmet_type)));
	o_info.Set_Mp(o_info.Get_Mp() + (New ? e_helmet.Get_Mp(helmet_type) : -e_helmet.Get_Mp(helmet_type)));
	o_info.Set_Defence(o_info.Get_Defence() + (New ? e_helmet.Get_Defence(helmet_type) : -e_helmet.Get_Defence(helmet_type)));
}

/*equipment armor*/

const int& E_Armor::Get_Hp(const int& armor_type) const {
	return hp[armor_type];
}

const int& E_Armor::Get_Defence(const int& armor_type) const {
	return defence[armor_type];
}

void E_Armor::Set_Armor() {
	hp[Armor_Type::DEFUALT_ARMOR] = 15;
	defence[Armor_Type::DEFUALT_ARMOR] = 10;

	hp[Armor_Type::SHOP_ARMOR1] = 33;
	defence[Armor_Type::SHOP_ARMOR1] = 20;

	hp[Armor_Type::SHOP_ARMOR2] = 102;
	defence[Armor_Type::SHOP_ARMOR2] = 40;

	hp[Armor_Type::SHOP_ARMOR3] = 196;
	defence[Armor_Type::SHOP_ARMOR3] = 60;

	hp[Armor_Type::SHOP_ARMOR4] = 300;
	defence[Armor_Type::SHOP_ARMOR4] = 70;
}

void Reset_Armor(E_Armor& e_armor) {
	e_armor.Set_Armor();
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
	wsprintf(text, _T("채력 + %d"), e_armor.Get_Hp(armor_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("방어력 + %d"), e_armor.Get_Defence(armor_type));
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Armor(const E_Armor& e_armor, Object_Info& o_info, const int& armor_type, const bool& New) {
	o_info.Set_Max_Hp(o_info.Get_Max_Hp() + (New ? e_armor.Get_Hp(armor_type) : -e_armor.Get_Hp(armor_type)));
	o_info.Set_Hp(o_info.Get_Hp() + (New ? e_armor.Get_Hp(armor_type) : -e_armor.Get_Hp(armor_type)));
	o_info.Set_Defence(o_info.Get_Defence() + (New ? e_armor.Get_Defence(armor_type) : -e_armor.Get_Defence(armor_type)));
}

/*equipment pant*/

const int& E_Pant::Get_Hp(const int& pant_type) const {
	return hp[pant_type];
}

const int& E_Pant::Get_Defence(const int& pant_type) const {
	return defence[pant_type];
}

void E_Pant::Set_Pant() {
	hp[Pant_Type::DEFUALT_PANT] = 30;
	defence[Pant_Type::DEFUALT_PANT] = 5;

	hp[Pant_Type::SHOP_PANT1] = 58;
	defence[Pant_Type::SHOP_PANT1] = 10;

	hp[Pant_Type::SHOP_PANT2] = 144;
	defence[Pant_Type::SHOP_PANT2] = 24;

	hp[Pant_Type::SHOP_PANT3] = 250;
	defence[Pant_Type::SHOP_PANT3] = 40;

	hp[Pant_Type::SHOP_PANT4] = 350;
	defence[Pant_Type::SHOP_PANT4] = 50;
}

void Reset_Pant(E_Pant& e_pant) {
	e_pant.Set_Pant();
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
	wsprintf(text, _T("채력 + %d"), e_pant.Get_Hp(pant_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("방어력 + %d"), e_pant.Get_Defence(pant_type));
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Pant(const E_Pant& e_pant, Object_Info& o_info, const int& pant_type, const bool& New) {
	o_info.Set_Max_Hp(o_info.Get_Max_Hp() + (New ? e_pant.Get_Hp(pant_type) : -e_pant.Get_Hp(pant_type)));
	o_info.Set_Hp(o_info.Get_Hp() + (New ? e_pant.Get_Hp(pant_type) : -e_pant.Get_Hp(pant_type)));
	o_info.Set_Defence(o_info.Get_Defence() + (New ? e_pant.Get_Defence(pant_type) : -e_pant.Get_Defence(pant_type)));
}

/*equipment glove*/

const int& E_Glove::Get_Attack(const int& glove_type) const {
	return attack[glove_type];
}

const int& E_Glove::Get_Fatal(const int& glove_type) const {
	return fatal[glove_type];
}

void E_Glove::Set_Glove() {
	attack[Glove_Type::DEFUALT_GLOVE] = 5;
	fatal[Glove_Type::DEFUALT_GLOVE] = 1;

	attack[Glove_Type::SHOP_GLOVE1] = 8;
	fatal[Glove_Type::SHOP_GLOVE1] = 2;

	attack[Glove_Type::SHOP_GLOVE2] = 16;
	fatal[Glove_Type::SHOP_GLOVE2] = 4;

	attack[Glove_Type::SHOP_GLOVE3] = 24;
	fatal[Glove_Type::SHOP_GLOVE3] = 6;

	attack[Glove_Type::SHOP_GLOVE4] = 28;
	fatal[Glove_Type::SHOP_GLOVE4] = 7;
}

void Reset_Glove(E_Glove& e_glove) {
	e_glove.Set_Glove();
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
	wsprintf(text, _T("공격력 + %d"), e_glove.Get_Attack(glove_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("치명타 확률 + %d"), e_glove.Get_Fatal(glove_type));
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Glove(const E_Glove& e_glove, Object_Info& o_info, const int& glove_type, const bool& New) {
	o_info.Set_Attack(o_info.Get_Attack() + (New ? e_glove.Get_Attack(glove_type) : -e_glove.Get_Attack(glove_type)));
	o_info.Set_Fatal(o_info.Get_Fatal() + (New ? e_glove.Get_Fatal(glove_type) : -e_glove.Get_Fatal(glove_type)));
}

/*equipment shoe*/
const int& E_Shoe::Get_Hp(const int& shoe_type) const {
	return hp[shoe_type];
}

const int& E_Shoe::Get_Mp(const int& shoe_type) const {
	return mp[shoe_type];
}

void E_Shoe::Set_Shoe() {
	hp[Shoe_Type::DEFUALT_SHOE] = 10;
	mp[Shoe_Type::DEFUALT_SHOE] = 10;

	hp[Shoe_Type::SHOP_SHOE1] = 20;
	mp[Shoe_Type::SHOP_SHOE1] = 20;

	hp[Shoe_Type::SHOP_SHOE2] = 40;
	mp[Shoe_Type::SHOP_SHOE2] = 40;

	hp[Shoe_Type::SHOP_SHOE3] = 60;
	mp[Shoe_Type::SHOP_SHOE3] = 60;

	hp[Shoe_Type::SHOP_SHOE4] = 70;
	mp[Shoe_Type::SHOP_SHOE4] = 70;
}

void Reset_Shoe(E_Shoe& e_shoe) {
	e_shoe.Set_Shoe();
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
	wsprintf(text, _T("체력 + %d"), e_shoe.Get_Hp(shoe_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("마나 + %d"), e_shoe.Get_Mp(shoe_type));
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Shoe(const E_Shoe& e_shoe, Object_Info& o_info, const int& shoe_type, const bool& New) {
	o_info.Set_Max_Hp(o_info.Get_Max_Hp() + (New ? e_shoe.Get_Hp(shoe_type) : -e_shoe.Get_Hp(shoe_type)));
	o_info.Set_Hp(o_info.Get_Hp() + (New ? e_shoe.Get_Hp(shoe_type) : -e_shoe.Get_Hp(shoe_type)));
	o_info.Set_Max_Mp(o_info.Get_Max_Mp() + (New ? e_shoe.Get_Mp(shoe_type) : -e_shoe.Get_Mp(shoe_type)));
	o_info.Set_Mp(o_info.Get_Mp() + (New ? e_shoe.Get_Mp(shoe_type) : -e_shoe.Get_Mp(shoe_type)));
}

/*equipment weapon*/

const int& E_Weapon::Get_Attack(const int& weapon_type) const {
	return attack[weapon_type];
}

const int& E_Weapon::Get_Fatal(const int& weapon_type) const {
	return fatal[weapon_type];
}

void E_Weapon::Set_Weapon(const int& class_type) {
	switch (class_type)
	{
	case Class_Type::Warrior:
		attack[Weapon_Type::DEFUALT_WEAPON] = 20;
		fatal[Weapon_Type::DEFUALT_WEAPON] = 3;

		attack[Weapon_Type::SHOP_WEAPON1] = 35;
		fatal[Weapon_Type::SHOP_WEAPON1] = 5;

		attack[Weapon_Type::SHOP_WEAPON2] = 64;
		fatal[Weapon_Type::SHOP_WEAPON2] = 10;

		attack[Weapon_Type::SHOP_WEAPON3] = 100;
		fatal[Weapon_Type::SHOP_WEAPON3] = 15;

		attack[Weapon_Type::SHOP_WEAPON4] = 125;
		fatal[Weapon_Type::SHOP_WEAPON4] = 20;
		break;
	default:
		break;
	}
}

void Reset_Weapon(E_Weapon& e_weapon, const int& class_type) {
	e_weapon.Set_Weapon(class_type);
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
	wsprintf(text, _T("공격력 + %d"), e_weapon.Get_Attack(weapon_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
	wsprintf(text, _T("치명타 확률 + %d"), e_weapon.Get_Fatal(weapon_type));
	TextOut(hdc, pos.x, pos.y + 130, text, _tcslen(text));
}

void Readjust_Info_By_Weapon(const E_Weapon& e_weapon, Object_Info& o_info, const int& weapon_type, const bool& New) {
	o_info.Set_Attack(o_info.Get_Attack() + (New ? e_weapon.Get_Attack(weapon_type) : -e_weapon.Get_Attack(weapon_type)));
	o_info.Set_Fatal(o_info.Get_Fatal() + (New ? e_weapon.Get_Fatal(weapon_type) : -e_weapon.Get_Fatal(weapon_type)));
}

/*equipment Amulet*/

const int& E_Amulet::Get_Hp(const int& amulet_type) const {
	return hp[amulet_type];
}

void E_Amulet::Set_Amulet() {
	hp[Amulet_Type::DEFUALT_AMULET] = 20;

	hp[Amulet_Type::SHOP_AMULET1] = 40;

	hp[Amulet_Type::SHOP_AMULET2] = 80;

	hp[Amulet_Type::SHOP_AMULET3] = 120;

	hp[Amulet_Type::SHOP_AMULET4] = 140;
}

void Reset_Amulet(E_Amulet& e_amulet) {
	e_amulet.Set_Amulet();
}
void Paint_Amulet_Info(HDC hdc, const E_Amulet& e_amulet, const POINT& pos, const int& amulet_type, const HFONT font) {
	switch (amulet_type)
	{
	case Amulet_Type::DEFUALT_AMULET:
		TextOut(hdc, pos.x, pos.y, _T("돌 목걸이"), 5);
		break;
	case Amulet_Type::SHOP_AMULET1:
		TextOut(hdc, pos.x, pos.y, _T("푸른 빛 목걸이"), 8);
		break;
	case Amulet_Type::SHOP_AMULET2:
		TextOut(hdc, pos.x, pos.y, _T("붉은 빛 목걸이"), 8);
		break;
	case Amulet_Type::SHOP_AMULET3:
		TextOut(hdc, pos.x, pos.y, _T("푸른 진주 목걸이"), 9);
		break;
	case Amulet_Type::SHOP_AMULET4:
		TextOut(hdc, pos.x, pos.y, _T("붉은 진주 목걸이"), 9);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("체력 + %d"), e_amulet.Get_Hp(amulet_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
}
void Readjust_Info_By_Amulet(const E_Amulet& e_amulet, Object_Info& o_info, const int& amulet_type, const bool& New) {
	o_info.Set_Max_Hp(o_info.Get_Max_Hp() + (New ? e_amulet.Get_Hp(amulet_type) : -e_amulet.Get_Hp(amulet_type)));
	o_info.Set_Hp(o_info.Get_Hp() + (New ? e_amulet.Get_Hp(amulet_type) : -e_amulet.Get_Hp(amulet_type)));
}

/*equipment Ring*/
const int& E_Ring::Get_Fatal(const int& ring_type) const {
	return fatal[ring_type];
}

void E_Ring::Set_Ring() {
	fatal[Ring_Type::DEFUALT_RING] = 1;
	fatal[Ring_Type::SHOP_RING1] = 2;
	fatal[Ring_Type::SHOP_RING2] = 4;
	fatal[Ring_Type::SHOP_RING3] = 6;
	fatal[Ring_Type::SHOP_RING4] = 7;
}

void Reset_Ring(E_Ring& e_ring) {
	e_ring.Set_Ring();
}

void Paint_Ring_Info(HDC hdc, const E_Ring& e_ring, const POINT& pos, const int& ring_type, const HFONT font) {
	switch (ring_type)
	{
	case Ring_Type::DEFUALT_RING:
		TextOut(hdc, pos.x, pos.y, _T("녹슨 반지"), 5);
		break;
	case Ring_Type::SHOP_RING1:
		TextOut(hdc, pos.x, pos.y, _T("견습생의 반지"), 7);
		break;
	case Ring_Type::SHOP_RING2:
		TextOut(hdc, pos.x, pos.y, _T("붉은 빛 반지"), 7);
		break;
	case Ring_Type::SHOP_RING3:
		TextOut(hdc, pos.x, pos.y, _T("사냥꾼의 반지"), 7);
		break;
	case Ring_Type::SHOP_RING4:
		TextOut(hdc, pos.x, pos.y, _T("에메랄드 반지"), 7);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("치명타 확률 + %d"), e_ring.Get_Fatal(ring_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
}

void Readjust_Info_By_Ring(const E_Ring& e_ring, Object_Info& o_info, const int& ring_type, const bool& New) {
	o_info.Set_Fatal(o_info.Get_Fatal() + (New ? e_ring.Get_Fatal(ring_type) : -e_ring.Get_Fatal(ring_type)));
}

/*equipment Book*/

const int& E_Book::Get_Mp(const int& book_type) const {
	return mp[book_type];
}

void E_Book::Set_Book() {
	mp[Book_Type::DEFUALT_BOOK] = 10;
	mp[Book_Type::SHOP_BOOK1] = 20;
	mp[Book_Type::SHOP_BOOK2] = 40;
	mp[Book_Type::SHOP_BOOK3] = 60;
	mp[Book_Type::SHOP_BOOK4] = 70;
}

void Reset_Book(E_Book& e_book) {
	e_book.Set_Book();
}

void Paint_Book_Info(HDC hdc, const E_Book& e_book, const POINT& pos, const int& book_type, const HFONT font) {
	switch (book_type)
	{
	case Book_Type::DEFUALT_BOOK:
		TextOut(hdc, pos.x, pos.y, _T("헌 마법서"), 5);
		break;
	case Book_Type::SHOP_BOOK1:
		TextOut(hdc, pos.x, pos.y, _T("견습 마법서"), 6);
		break;
	case Book_Type::SHOP_BOOK2:
		TextOut(hdc, pos.x, pos.y, _T("중급 마법서"), 6);
		break;
	case Book_Type::SHOP_BOOK3:
		TextOut(hdc, pos.x, pos.y, _T("고급 마법서"), 6);
		break;
	case Book_Type::SHOP_BOOK4:
		TextOut(hdc, pos.x, pos.y, _T("전문가 마법서"), 7);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("마나 + %d"), e_book.Get_Mp(book_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
}

void Readjust_Info_By_Book(const E_Book& e_book, Object_Info& o_info, const int& book_type, const bool& New) {
	o_info.Set_Max_Mp(o_info.Get_Max_Mp() + (New ? e_book.Get_Mp(book_type) : -e_book.Get_Mp(book_type)));
	o_info.Set_Mp(o_info.Get_Mp() + (New ? e_book.Get_Mp(book_type) : -e_book.Get_Mp(book_type)));
}

/*equipment Cloak*/

const int& E_Cloak::Get_Attack(const int& cloak_type) const {
	return attack[cloak_type];
}

void E_Cloak::Set_Cloak() {
	attack[Cloak_Type::DEFUALT_CLOAK] = 5;
	attack[Cloak_Type::GRAY_CLOAK] = 20;
	attack[Cloak_Type::BLUE_CLOAK] = 50;
	attack[Cloak_Type::RED_CLOAK] = 100;
}

void Reset_Cloak(E_Cloak& e_cloak) {
	e_cloak.Set_Cloak();
}

void Paint_Cloak_Info(HDC hdc, const E_Cloak& e_cloak, const POINT& pos, const int& cloak_type, const HFONT font) {
	switch (cloak_type)
	{
	case Book_Type::DEFUALT_BOOK:
		TextOut(hdc, pos.x, pos.y, _T("허름한 망토"), 6);
		break;
	case Book_Type::SHOP_BOOK1:
		TextOut(hdc, pos.x, pos.y, _T("견습생의 망토"), 7);
		break;
	case Book_Type::SHOP_BOOK2:
		TextOut(hdc, pos.x, pos.y, _T("수비대장의 망토"), 8);
		break;
	case Book_Type::SHOP_BOOK3:
		TextOut(hdc, pos.x, pos.y, _T("전설의 망토"), 6);
		break;
	default:
		break;
	}
	TCHAR text[20];
	SelectObject(hdc, font);
	wsprintf(text, _T("공격력 + %d"), e_cloak.Get_Attack(cloak_type));
	TextOut(hdc, pos.x, pos.y + 80, text, _tcslen(text));
}

void Readjust_Info_By_Cloak(const E_Cloak& e_cloak, Object_Info& o_info, const int& cloak_type, const bool& New) {
	o_info.Set_Attack(o_info.Get_Attack() + (New ? e_cloak.Get_Attack(cloak_type) : -e_cloak.Get_Attack(cloak_type)));
}


/*player equipment*/

Player_Equipment::~Player_Equipment() {
	Delete_Class<E_Helmet>(&helmet);
	Delete_Class<E_Armor>(&armor);
	Delete_Class<E_Pant>(&pant);
	Delete_Class<E_Glove>(&glove);
	Delete_Class<E_Shoe>(&shoe);
	Delete_Class<E_Weapon>(&weapon);
	Delete_Class<E_Amulet>(&amulet);
	Delete_Class<E_Ring>(&ring);
	Delete_Class<E_Book>(&book);
	Delete_Class<E_Cloak>(&cloak);
	DeleteObject(equipment_interface_bitmap);
	for (int e_type = Equipment_Type::T_HELMET; e_type <= Equipment_Type::T_CLOAK; e_type++)
		for (int i = 0; i < 10; i++)
			DeleteObject(equipment_bitmap[e_type][i]);
	DeleteObject(equipment_select_bitmap[0]);
	DeleteObject(equipment_select_bitmap[1]);
	for (int index = 0; index < 3; index++)
		DeleteObject(equip_font[index]);
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

const E_Amulet& Player_Equipment::Get_Amulet_Const() const {
	return *amulet;
}

E_Amulet& Player_Equipment::Get_Amulet() const {
	return *amulet;
}

const E_Ring& Player_Equipment::Get_Ring_Const() const {
	return *ring;
}

E_Ring& Player_Equipment::Get_Ring() const {
	return *ring;
}

const E_Book& Player_Equipment::Get_Book_Const() const {
	return *book;
}

E_Book& Player_Equipment::Get_Book() const {
	return *book;
}

const E_Cloak& Player_Equipment::Get_Cloak_Const() const {
	return *cloak;
}

E_Cloak& Player_Equipment::Get_Cloak() const {
	return *cloak;
}

const int& Player_Equipment::Get_Gold() const {
	return gold;
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

const HBITMAP& Player_Equipment::Get_Equipment_Interface_Bitmap() const {
	return equipment_interface_bitmap;
}

const BITMAP& Player_Equipment::Get_Equipment_Interface_Bitmap_Size() const {
	return equipment_interface_bitmap_size;
}

const HBITMAP& Player_Equipment::Get_Equipment_Bitmap(const int& e_type, const int& d_select) const {
	return equipment_bitmap[e_type][d_select];
}

const HBITMAP& Player_Equipment::Get_Equipment_Select_Bitmap(const int& index) const {
	return equipment_select_bitmap[index];
}

const BITMAP& Player_Equipment::Get_Equipment_Bitmap_Size() const {
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
	amulet = Create_Class<E_Amulet>();
	ring = Create_Class<E_Ring>();
	book = Create_Class<E_Book>();
	cloak = Create_Class<E_Cloak>();
}

void Player_Equipment::Set_Pos(const POINT& pos) {
	this->pos = pos;
}

void Player_Equipment::Set_Gold(const int& gold) {
	this->gold = gold;
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
	for (int a_type = Amulet_Type::DEFUALT_AMULET; a_type <= Amulet_Type::SHOP_AMULET4; a_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Amulet\\Amulet%d.bmp"), a_type + 1);
		equipment_bitmap[Equipment_Type::T_AMULET][a_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	for (int r_type = Ring_Type::DEFUALT_RING; r_type <= Ring_Type::SHOP_RING4; r_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Ring\\Ring%d.bmp"), r_type + 1);
		equipment_bitmap[Equipment_Type::T_RING][r_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	for (int b_type = Book_Type::DEFUALT_BOOK; b_type <= Book_Type::SHOP_BOOK4; b_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Book\\Book%d.bmp"), b_type + 1);
		equipment_bitmap[Equipment_Type::T_BOOK][b_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	for (int c_type = Cloak_Type::DEFUALT_CLOAK; c_type <= Cloak_Type::RED_CLOAK; c_type++) {
		wchar_t str[50];
		wsprintf(str, _T(".\\BitMap\\Equipment\\Cloak\\Cloak%d.bmp"), c_type + 1);
		equipment_bitmap[Equipment_Type::T_CLOAK][c_type] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
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
	p_equip.Set_Gold(10000);
	p_equip.Set_Type_Select(Equipment_Type::T_HELMET);
	for (int e_type = Equipment_Type::T_HELMET; e_type <= Equipment_Type::T_CLOAK; e_type++) {
		p_equip.Set_Equipment_Detail_Select(e_type, 0);
		p_equip.Set_Own(e_type, 0);
	}
	p_equip.Set_Change_Select(false);
	p_equip.Set_Bitmap();
	p_equip.Set_Font();

	//기본 장비의 능력치를 Object_Info에 갱신시킨다.
	Reset_Helmet(p_equip.Get_Helmet());
	Readjust_Info_By_Helmet(p_equip.Get_Helmet_Const(), o_info, Helmet_Type::DEFUALT_HELMET, true);
	Reset_Armor(p_equip.Get_Armor());
	Readjust_Info_By_Armor(p_equip.Get_Armor_Const(), o_info, Armor_Type::DEFUALT_ARMOR, true);
	Reset_Pant(p_equip.Get_Pant());
	Readjust_Info_By_Pant(p_equip.Get_Pant_Const(), o_info, Pant_Type::DEFUALT_PANT, true);
	Reset_Glove(p_equip.Get_Glove());
	Readjust_Info_By_Glove(p_equip.Get_Glove_Const(), o_info, Glove_Type::DEFUALT_GLOVE, true);
	Reset_Shoe(p_equip.Get_Shoe());
	Readjust_Info_By_Shoe(p_equip.Get_Shoe_Const(), o_info, Shoe_Type::DEFUALT_SHOE, true);
	Reset_Weapon(p_equip.Get_Weapon(), Class_Type::Warrior);
	Readjust_Info_By_Weapon(p_equip.Get_Weapon_Const(), o_info, Weapon_Type::DEFUALT_WEAPON, true);
	Reset_Amulet(p_equip.Get_Amulet());
	Readjust_Info_By_Amulet(p_equip.Get_Amulet_Const(), o_info, Amulet_Type::DEFUALT_AMULET, true);
	Reset_Ring(p_equip.Get_Ring());
	Readjust_Info_By_Ring(p_equip.Get_Ring_Const(), o_info, Ring_Type::DEFUALT_RING, true);
	Reset_Book(p_equip.Get_Book());
	Readjust_Info_By_Book(p_equip.Get_Book_Const(), o_info, Book_Type::DEFUALT_BOOK, true);
	Reset_Cloak(p_equip.Get_Cloak());
	Readjust_Info_By_Cloak(p_equip.Get_Cloak_Const(), o_info, Cloak_Type::DEFUALT_CLOAK, true);
	
}

void Paint_Player_Equipment(HDC hdc, HDC bitdc, const Player_Equipment& p_equip, const Object_Info& o_info) {
	SelectObject(bitdc, p_equip.Get_Equipment_Interface_Bitmap());
	TransparentBlt(hdc, p_equip.Get_Pos().x, p_equip.Get_Pos().y, p_equip.Get_Equipment_Interface_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Interface_Bitmap_Size().bmHeight,
		bitdc, 0, 0, p_equip.Get_Equipment_Interface_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Interface_Bitmap_Size().bmHeight, RGB(255, 255, 255));

	//장비를 출력한다.
	for (int e_type = Equipment_Type::T_HELMET; e_type <= Equipment_Type::T_CLOAK; e_type++) {
		SelectObject(bitdc, p_equip.Get_Equipment_Bitmap(e_type, p_equip.Get_Equipment_Detail_Select(e_type)));
		TransparentBlt(hdc, p_equip.Get_Pos().x + 30 + 377 * (e_type / 5), p_equip.Get_Pos().y + 30 + (e_type % 5) * 80, p_equip.Get_Equipment_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Bitmap_Size().bmHeight,
			bitdc, 0, 0, p_equip.Get_Equipment_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Bitmap_Size().bmHeight, ((e_type <= Equipment_Type::T_WEAPON) ? RGB(0, 0, 0) : RGB(150, 150, 150)));
	}

	//장비 선택 테두리를 출력한다.
	SelectObject(bitdc, p_equip.Get_Equipment_Select_Bitmap(p_equip.Is_Chnage_Select()));
	TransparentBlt(hdc, p_equip.Get_Pos().x + 30 + 377 * (p_equip.Get_Type_Select() / 5), p_equip.Get_Pos().y + 30 + (p_equip.Get_Type_Select() % 5) * 80, p_equip.Get_Equipment_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Bitmap_Size().bmHeight,
		bitdc, 0, 0, p_equip.Get_Equipment_Bitmap_Size().bmWidth, p_equip.Get_Equipment_Bitmap_Size().bmHeight, RGB(150, 150, 150));

	SetBkMode(hdc, TRANSPARENT);
	//선택한 장비의 정보를 출력합니다.
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
	case Equipment_Type::T_AMULET:
		Paint_Amulet_Info(hdc, p_equip.Get_Amulet_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	case Equipment_Type::T_RING:
		Paint_Ring_Info(hdc, p_equip.Get_Ring_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	case Equipment_Type::T_BOOK:
		Paint_Book_Info(hdc, p_equip.Get_Book_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
		break;
	case Equipment_Type::T_CLOAK:
		Paint_Cloak_Info(hdc, p_equip.Get_Cloak_Const(), { p_equip.Get_Pos().x + 130, p_equip.Get_Pos().y + 70 }, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), p_equip.Get_Font(1));
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
	wsprintf(text, _T("Gold : %d"), p_equip.Get_Gold());
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
	
	int before_select;

	switch (wParam)
	{
	case VK_LEFT:
	case VK_RIGHT:
		before_select = p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select());

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
			if (p_equip.Get_Type_Select() != Equipment_Type::T_CLOAK) {
				if (p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) < 10) {
					for (int index = p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) + 1; index < 10; index++) {
						if (p_equip.Is_Own(p_equip.Get_Type_Select(), index)) {
							p_equip.Set_Equipment_Detail_Select(p_equip.Get_Type_Select(), index);
							break;
						}
					}
				}
			}
			//망토는 10까지 없다.
			else {
				if (p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) < 4) {
					for (int index = p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()) + 1; index < 4; index++) {
						if (p_equip.Is_Own(p_equip.Get_Type_Select(), index)) {
							p_equip.Set_Equipment_Detail_Select(p_equip.Get_Type_Select(), index);
							break;
						}
					}
				}
			}
		}
	

		//플레이어 정보 재조정
		switch (p_equip.Get_Type_Select())
		{
		case Equipment_Type::T_HELMET:
			Readjust_Info_By_Helmet(p_equip.Get_Helmet_Const(), o_info, before_select, false);
			Readjust_Info_By_Helmet(p_equip.Get_Helmet_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_ARMOR:
			Readjust_Info_By_Armor(p_equip.Get_Armor_Const(), o_info, before_select, false);
			Readjust_Info_By_Armor(p_equip.Get_Armor_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_PANT:
			Readjust_Info_By_Pant(p_equip.Get_Pant_Const(), o_info, before_select, false);
			Readjust_Info_By_Pant(p_equip.Get_Pant_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_GLOVE:
			Readjust_Info_By_Glove(p_equip.Get_Glove_Const(), o_info, before_select, false);
			Readjust_Info_By_Glove(p_equip.Get_Glove_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_SHOE:
			Readjust_Info_By_Shoe(p_equip.Get_Shoe_Const(), o_info, before_select, false);
			Readjust_Info_By_Shoe(p_equip.Get_Shoe_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_WEAPON:
			Readjust_Info_By_Weapon(p_equip.Get_Weapon_Const(), o_info, before_select, false);
			Readjust_Info_By_Weapon(p_equip.Get_Weapon_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_AMULET:
			Readjust_Info_By_Amulet(p_equip.Get_Amulet_Const(), o_info, before_select, false);
			Readjust_Info_By_Amulet(p_equip.Get_Amulet_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_RING:
			Readjust_Info_By_Ring(p_equip.Get_Ring_Const(), o_info, before_select, false);
			Readjust_Info_By_Ring(p_equip.Get_Ring_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_BOOK:
			Readjust_Info_By_Book(p_equip.Get_Book_Const(), o_info, before_select, false);
			Readjust_Info_By_Book(p_equip.Get_Book_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
			break;
		case Equipment_Type::T_CLOAK:
			Readjust_Info_By_Cloak(p_equip.Get_Cloak_Const(), o_info, before_select, false);
			Readjust_Info_By_Cloak(p_equip.Get_Cloak_Const(), o_info, p_equip.Get_Equipment_Detail_Select(p_equip.Get_Type_Select()), true);
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