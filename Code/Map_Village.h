#pragma once
#include <Windows.h>
#include "Map_Main.h"

class Warrior;
class Practice_Enemy;

typedef enum Village_Texture {
	Load, Grow1, Grow2
}VT;

typedef enum Village_NM_Object {
	House1, House2, House3, House4, Lake, Wall1
}VNM_OB;

class Non_Move_Object;
class Non_Move_Npc;

class Map_Village : public Map {
public:
	~Map_Village();

	const Non_Move_Object& Get_NM_Object(const int& index) const;
	const Non_Move_Npc& Get_NM_Npc_Const(const int& index) const;
	Non_Move_Npc& Get_NM_Npc(const int& index) const;
	const Practice_Enemy& Get_P_Enemy_Const() const;
	Practice_Enemy& Get_P_Enemy() const;
	const HBITMAP Get_Texture(const int& index) const;

	void Set_NM_Object();
	void Set_NM_Npc();
	void Set_P_Enemy();
	void Set_Texture();
	
private:
	Non_Move_Object* nm_object[10];
	Non_Move_Npc* nm_npc[4];
	Practice_Enemy* p_enemy;
	HBITMAP texture[4];
};

void Reset_Village_Map(HDC hdc, Map_Village& map_v);
void Paint_Village_Map_Texture(HDC hdc, HDC bitdc, Map_Village& map_v);
void Paint_Village_Map(HDC hdc, HDC bitdc, Warrior& warrior, Map_Village& map_v);
