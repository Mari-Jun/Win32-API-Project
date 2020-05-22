#pragma once
#include <Windows.h>
#include "Map_Main.h"

class Player;
class Practice_Enemy;
class Hitting_Range_Polygon;
class Npc;
class Shop;
class Interaction_Box;

typedef enum Village_Texture {
	Load, Grow1, Grow2
}VT;

typedef enum Village_NM_Object {
	House1, House2, House3, House4, Lake, Wall1
}VNM_OB;

class Map_Village : public Map {
public:
	virtual ~Map_Village();

	const Practice_Enemy& Get_P_Enemy_Const() const;
	Practice_Enemy& Get_P_Enemy() const;
	const Npc& Get_Npc_Const(const int& npc_type) const;
	Npc& Get_Npc(const int& npc_type) const;
	const Shop& Get_Shop_Const() const;
	Shop& Get_Shop() const;
	const HBITMAP& Get_Texture(const int& index) const;
	
	virtual void Set_NM_Object();
	void Set_Npc();
	void Set_P_Enemy();
	void Set_Texture();

	void Create_Shop(const int& shop_type, const RECT& it_rect);
	void Destroy_Shop();

	void Kill_P_Enemy();
	
private:
	Practice_Enemy* p_enemy;
	Npc* npc[5];
	Shop* shop;
	HBITMAP texture[4];
};

void Reset_Village_Map(HDC hdc, Map_Village& map_v);
void Paint_Village_Map_Texture(HDC hdc, HDC bitdc, const Map_Village& map_v);
void Paint_Village_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Village& map_v);

void Animation_Play_Npc(Map_Village& map_v);

void Enemy_Kill_Check(Map_Village& map_v);

//상점에 있는 물건을 선택, 사는 기능이 구현되어있다.
bool Shop_Select_Item(Player& player, Map_Village& map_v, Interaction_Box& it_box, const WPARAM wParam);