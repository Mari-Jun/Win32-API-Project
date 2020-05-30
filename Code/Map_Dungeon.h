#pragma once
#include <Windows.h>
#include "Map_Main.h"

class Player;
class Enemy;

enum Dungeon1_Texture {
	D1_Grass, D1_Rock
};

class Map_Dungeon : public Map {
public:
	virtual ~Map_Dungeon();

	const int& Get_Dungeon_Type() const;
	const Enemy& Get_Enemy_Const(const int& index) const;
	Enemy& Get_Enemy(const int& index) const;

	void Set_Dungeon_Type(const int& dungeon_type);

	virtual void Set_NM_Object();
	virtual void Set_Texture();

	void Set_Enemy();

	void Kill_Enemy(const int& index);

private:
	int dungeon_type;
	//그냥 Enemy와 Boss Enemy로 나중에 변환
	Enemy* enemy[50];

};

void Reset_Dungeon_Map(HDC hdc, Map_Dungeon& map_d, const int& dungeon_type);
void Paint_Dungeon_Map_Texture(HDC hdc, HDC bitdc, const Map_Dungeon& map_d);
void Paint_Dungeon_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Dungeon& map_d);