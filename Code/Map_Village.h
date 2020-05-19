#pragma once
#include <Windows.h>
#include "Map_Main.h"

class Warrior;
class Practice_Enemy;
class Hitting_Range_Polygon;

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
	const HBITMAP Get_Texture(const int& index) const;
	
	virtual void Set_NM_Object();
	virtual void Set_NM_Npc();
	void Set_P_Enemy();
	void Set_Texture();

	void Kill_P_Enemy();
	
private:
	Practice_Enemy* p_enemy;
	HBITMAP texture[4];
};

void Reset_Village_Map(HDC hdc, Map_Village& map_v);
void Paint_Village_Map_Texture(HDC hdc, HDC bitdc, const Map_Village& map_v);
void Paint_Village_Map(HDC hdc, HDC bitdc, const Warrior& warrior, const Map_Village& map_v);

void Enemy_Kill_Check(Map_Village& map_v);
