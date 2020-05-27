#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Map_Dungeon.h"
#include "Object_Main.h"
#include "Object_Player.h"
#include "Object_Enemy.h"
#include "Object_Info.h"

Map_Dungeon::~Map_Dungeon() {
	
}

const int& Map_Dungeon::Get_Dungeon_Type() const {
	return dungeon_type;
}

void Map_Dungeon::Set_Dungeon_Type(const int& dungeon_type) {
	this->dungeon_type = dungeon_type;
}

const Enemy& Map_Dungeon::Get_Enemy_Const(const int& index) const {
	return *enemy[index];
}

Enemy& Map_Dungeon::Get_Enemy(const int& index) const {
	return *enemy[index];
}

void Map_Dungeon::Set_NM_Object() {
	//임시 미구현
}

void Map_Dungeon::Set_Texture() {
	//임시 미구현
}

void Map_Dungeon::Set_Enemy() {
	switch (Get_Dungeon_Type())
	{
	case Map_Type::Dungeon1:
		//일단 1마리만 생성
		for (int index = 0; index < 5; index++) {
			enemy[index] = Create_Class<Enemy>();
			Reset_Enemy(*enemy[index], Enemy_Type::Bird);
			Reset_Move_Object(*enemy[index], 0 + index * 100, 400, enemy[index]->Get_Motion_Size().bmWidth, enemy[index]->Get_Motion_Size().bmHeight, 4);
		}
		break;
	default:
		break;
	}
}

void Map_Dungeon::Kill_Enemy(const int& index) {
	Delete_Class<Enemy>(&enemy[index]);
}

void Reset_Dungeon_Map(HDC hdc, Map_Dungeon& map_d, const int& dungeon_type) {
	map_d.Set_Dungeon_Type(dungeon_type);
	switch (map_d.Get_Dungeon_Type())
	{
	case Map_Type::Dungeon1:
		map_d.Set_Map_Rect(0, 0, 1760, 1600);
		break;
	case Map_Type::Dungeon2:
		map_d.Set_Map_Rect(0, 0, 1760, 1600);
		break;
	default:
		break;
	}
	map_d.Set_Map_Size_Bit(hdc);
	map_d.Set_NM_Object();
	map_d.Set_Enemy();
	map_d.Set_Texture();
}

void Paint_Dungeon_Map_Texture(HDC hdc, HDC bitdc, const Map_Dungeon& map_d) {
	//일단 미구현
}

void Paint_Dungeon_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Dungeon& map_d) {
	SelectObject(hdc, map_d.Get_Map_Size_Bitmap());
	FillRect(hdc, &map_d.Get_Map_Rect(), WHITE_BRUSH);

	Paint_Dungeon_Map_Texture(hdc, bitdc, map_d);

	int y_pos = 0;
	for (y_pos = 0; y_pos <= map_d.Get_Map_Rect().bottom; y_pos++) {

		//오브젝트 그리기
		for (int index = 0; index < 30; index++) {
			if (&map_d.Get_NM_Object(index) != NULL && y_pos == map_d.Get_NM_Object(index).Get_YPos() + map_d.Get_NM_Object(index).Get_Height()) {
				SelectObject(bitdc, map_d.Get_NM_Object(index).Get_Object_Bitmap());
				TransparentBlt(hdc, map_d.Get_NM_Object(index).Get_XPos(), map_d.Get_NM_Object(index).Get_YPos(), map_d.Get_NM_Object(index).Get_Width(), map_d.Get_NM_Object(index).Get_Height(), bitdc, 0, 0, map_d.Get_NM_Object(index).Get_Width(), map_d.Get_NM_Object(index).Get_Height(), RGB(150, 150, 150));
			}
		}

		//적 그리기
		for (int index = 0; index < 50; index++) {
			if (&map_d.Get_Enemy_Const(index) != NULL && y_pos == map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height())
				Paint_Enemy(hdc, bitdc, map_d.Get_Enemy_Const(index));
		}
	

		if (&player != NULL && y_pos == player.Get_YPos() + player.Get_Height())
			Paint_Player(hdc, bitdc, player);
	}
}