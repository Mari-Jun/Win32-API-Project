#pragma once
#include <Windows.h>
#include "Map_Main.h"

class Player;
class Enemy;
class Camera;
class File;

enum Dungeon1_Texture {
	D1_Grass, D2_Grass, D1_Rock
};

enum Dungeon1_Object {
	D1_Left_Rock1, D1_Left_Rock2, D1_Right_Rock1, D1_Right_Rock2, D1_Bottom_Rock, D1_Tree1, D1_Tree2 = 25
};


class Map_Dungeon : public Map {
public:
	virtual ~Map_Dungeon();

	const int& Get_Dungeon_Type() const;
	const Enemy& Get_Enemy_Const(const int& index) const;
	Enemy& Get_Enemy(const int& index) const;

	void Set_Dungeon_Type(const int& dungeon_type);

	void Set_Dungeon1(File& file);
	void Set_Dungeon2(File& file);

	void Kill_Enemy(const int& index);

private:
	int dungeon_type;
	Enemy* enemy[53];
};

void Reset_Dungeon_Map(HDC hdc, Map_Dungeon& map_d, File& file, const int& dungeon_type);
void Paint_Dungeon_Map_Texture(HDC hdc, HDC bitdc, const Map_Dungeon& map_d, const Camera& camera, const RECT c_rect);
void Paint_Dungeon_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Dungeon& map_d, const File& file, const Camera& camera, const RECT c_rect);
bool Check_Dungeon_Clear(const Map_Dungeon& map_d);