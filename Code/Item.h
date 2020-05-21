#pragma once
#include <Windows.h>

class Object_Info;
class Move_Object;

class Player_Item {
public:
	const HBITMAP Get_Potion_Bitmap(const int& index) const;
	const HFONT Get_Font() const;
	const BITMAP Get_Bitmap_Size() const;
	const int& Get_Hp_Potion() const;
	const int& Get_Hp_Potion_Max() const;
	const int& Get_Mp_Potion() const;
	const int& Get_Mp_Potion_Max() const;
	const int& Get_Panacea() const;

	void Set_Bitmap();
	void Set_Font();
	void Set_Hp_Potion(const int& hp_potion);
	void Set_Hp_Potion_Max(const int& hp_potion_max);
	void Set_Mp_Potion(const int& mp_potion);
	void Set_Mp_Potion_Max(const int& mp_potion_max);
	void Set_Panacea(const int& panacea);

private:
	HBITMAP potion_bitmap[3];
	HFONT font;
	BITMAP bitmap_size;
	int hp_potion;
	int hp_potion_max;
	int mp_potion;
	int mp_potion_max;
	int panacea;
};

void Reset_Player_Item(Player_Item& p_item);
void Paint_Player_Item(HDC hdc, HDC bitdc, const Player_Item& p_item, const RECT c_rect);

void Recharge_Item(Player_Item& p_item);
void Use_Hp_Potion(Player_Item& p_item, Object_Info& o_info);
void Use_Mp_Potion(Player_Item& p_item, Object_Info& o_info);
void Use_Panacea(Player_Item& p_item, Move_Object& m_object);