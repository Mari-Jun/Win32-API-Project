#pragma once
#include <Windows.h>
#include "Map_Main.h"

class Player;
class Practice_Enemy;
class Hitting_Range_Polygon;
class Npc;
class Shop;
class Interaction_Box;
class Sound;
class Camera;

typedef enum Village_Texture {
	Load, Grow1, Grow2
}VT;

typedef enum Village_NM_Object {
	House1, House2, House3, House4, House5, Wall1, Tree1, Tree2, Tree3
}VNM_OB;

class Map_Village : public Map {
public:
	virtual ~Map_Village();

	const Npc& Get_Npc_Const(const int& npc_type) const;
	Npc& Get_Npc(const int& npc_type) const;
	const Shop& Get_Shop_Const() const;
	Shop& Get_Shop() const;
	const Non_Move_Object& Get_Portal_Const() const;
	Non_Move_Object& Get_Portal() const;
	Sound& Get_Village_Sound() const;
	
	void Set_NM_Object();
	void Set_Texture();

;	void Set_Portal();
	void Set_Npc();
	void Set_Village_Sound();

	void Create_Portal();
	void Create_Shop(const int& shop_type, const RECT& it_rect);
	void Destroy_Shop();	


private:
	Non_Move_Object* portal;
	Npc* npc[6];
	Shop* shop;
	Sound* village_sound;
};

void Reset_Village_Map(HDC hdc, Map_Village& map_v);
void Paint_Village_Map_Texture(HDC hdc, HDC bitdc, const Map_Village& map_v, const Camera& camera, const RECT c_rect);
void Paint_Village_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Village& map_v, const Camera& camera, const RECT c_rect);
void Paint_Portal(HDC hdc, HDC bitdc, const Non_Move_Object& portal);

void Animation_Play_Npc(Map_Village& map_v);

//상점에 있는 물건을 선택, 사는 기능이 구현되어있다.
void Shop_Select_Item(Player& player, Map_Village& map_v, Interaction_Box& it_box, const WPARAM wParam);

void Change_Map_Village_To(Map_Village& map_v);
void Change_Map_To_Village(Map_Village& map_v);