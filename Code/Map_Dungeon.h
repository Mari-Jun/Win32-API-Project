#pragma once
#include <Windows.h>
#include "Map_Main.h"

class Player;
class Enemy;
class Enemy_Bitmap;
class Camera;
class File;
class Sound;

enum Dungeon_Texture {
	Texture1, Texture2, Texture3
};

enum Dungeon1_Object {
	D1_Left_Rock1, D1_Left_Rock2, D1_Right_Rock1, D1_Right_Rock2, D1_Bottom_Rock, D1_Tree1, D1_Tree2 = 25
};

enum Dungeon2_Object {
	D2_Wall,
};

enum Dungeon3_Object {
	D3_Wall,
};

enum Dungeon4_Object {
	D4_Wall,
};

enum Dungeon5_Object {
	D5_Tree1, D5_Tree2 = 12
};


class Map_Dungeon : public Map {
public:
	~Map_Dungeon();

	const int& Get_Dungeon_Type() const;
	const Enemy& Get_Enemy_Const(const int& index) const;
	Enemy& Get_Enemy(const int& index) const;
	const Enemy_Bitmap& Get_Enemy_Bitmap_Const() const;
	Enemy_Bitmap& Get_Enemy_Bitmap() const;
	Sound& Get_Dungeon_Sound() const;

	void Set_Dungeon_Type(const int& dungeon_type);

	void Set_Dungeon1(const File& file);
	void Set_Dungeon2(const File& file);
	void Set_Dungeon3(const File& file);
	void Set_Dungeon4(const File& file);
	void Set_Dungeon5(const File& file);
	void Set_Dungeon6(const File& file);

	void Set_Enemy_Bitmap(const File& file);
	void Set_Dungeon_Sound();

	void Kill_Enemy(const int& index);

private:
	int dungeon_type;
	Enemy* enemy[53];
	Enemy_Bitmap* e_bitmap;
	Sound* dungeon_sound;
};

void Reset_Dungeon_Map(HDC hdc, Map_Dungeon& map_d, File& file, const int& dungeon_type);
void Paint_Dungeon_Map_Texture(HDC hdc, HDC bitdc, const Map_Dungeon& map_d, const Camera& camera, const RECT c_rect);
void Paint_Dungeon_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Dungeon& map_d, const File& file, const Camera& camera, const RECT c_rect);
bool Check_Dungeon_Clear(const Map_Dungeon& map_d);

void Change_Map_Dungeon_To(Map_Dungeon& map_d);