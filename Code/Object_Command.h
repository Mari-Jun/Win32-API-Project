#pragma once
#include "Source.h"
#include <math.h>
#include "Game_Progress.h"
#include "Object_Info.h"
#include "Object_Npc.h"
#include "Object_Player.h"

enum Hitting_Shape {
	FRONT, ROUND
};
class Progress;
class Hitting_Range_Polygon;
class Move_Object;
class Player;
class Practice_Enemy;
class Map;
class Object;
class Map_Village;
class Map_D;



bool Crash_Check_Map(const Move_Object& m_object, const Map& map, const int& move_x, const int& move_y);
bool Crash_Check_Object(const Move_Object& m_object, const Object& obj, const int& move_x, const int& move_y);
//만약 다른 맵에 NPC가 없을 경우 템플릿 해서 원본에는 그냥 return true만 하고 따로 특수화 하면 된다.
bool Crash_Check_Npc(const Move_Object& m_objcet, const Map_Village& map_v, const int& move_x, const int& move_y);
bool Crash_Check_Enemy(const Move_Object& m_objcet, const Map_Village& map_v, const int& move_x, const int& move_y);
bool Crash_Attack_Polygon(const Move_Object& attack_obj, const Move_Object& hit_object, const Hitting_Range_Polygon& hit_range_p);
void Polygon_Damage_Enemy(Map_Village& map_v, const Move_Object& attack_obj, const Hitting_Range_Polygon& hit_range_p, const int& hit_dmg);


void Create_Hitting_Polygon(const Move_Object& m_object, POINT* pos, const int& width_size, const int& height_size, const int& shape);


template <typename T_Map>
void Command_Player(Player& player, T_Map& map, Progress& progress) {

	if (player.Get_Status() == Player_Status::Interaction || player.Get_Status() == Player_Status::Inventory || player.Get_Status() == Player_Status::Shopping ||
		player.Get_Status() == Player_Status::Map_Selecting)
		return;

	player.Set_Ani_Count(player.Get_Ani_Count() + 1);
	if (player.Get_Ani_Count() == 800)
		player.Set_Ani_Count(0);

	Attack_Player(player, map);

	Move_Player(player, map, progress);
}

template <typename T_Map>
void Move_Player(Move_Object& player, const T_Map& map, Progress& progress) {
	//나중에 충돌 체크 할일이 있을텐데, 그때는 모든 충돌이가능한 Object(맵, 적)에 대해서 검사를 한후 이동이 가능하게 해야합니다.

	bool KeyUp = (GetAsyncKeyState(VK_UP) & 0x8001);
	bool KeyDown = (GetAsyncKeyState(VK_DOWN) & 0x8001);
	bool KeyLeft = (GetAsyncKeyState(VK_LEFT) & 0x8001);
	bool KeyRight = (GetAsyncKeyState(VK_RIGHT) & 0x8001);


	//이러면 안되는데..
	if (player.Get_Status() != Player_Status::Attack) {
		if (KeyUp || KeyDown || KeyLeft || KeyRight) {
			player.Set_Status(Player_Status::Move);
		}
		else
			player.Set_Status(Player_Status::Stop);
	}

	if (KeyUp && KeyRight) {
		Move_Player_Check(player, map, progress, 0, -1 * static_cast<int>(player.Get_Speed() / sqrt(2) + 0.5));
		Move_Player_Check(player, map, progress, static_cast<int>(player.Get_Speed() / sqrt(2) + 0.5), 0);
		player.Set_Direction(Object_Direction::UpRight);
	}
	else if (KeyUp && KeyLeft) {
		Move_Player_Check(player, map, progress, 0, -1 * static_cast<int>(player.Get_Speed() / sqrt(2) + 0.5));
		Move_Player_Check(player, map, progress, -1 * static_cast<int>(player.Get_Speed() / sqrt(2) + 0.5), 0);
		player.Set_Direction(Object_Direction::UpLeft);
	}
	else if (KeyDown && KeyRight) {
		Move_Player_Check(player, map, progress, 0, static_cast<int>(player.Get_Speed() / sqrt(2) + 0.5));
		Move_Player_Check(player, map, progress, static_cast<int>(player.Get_Speed() / sqrt(2) + 0.5), 0);
		player.Set_Direction(Object_Direction::DownRight);
	}
	else if (KeyDown && KeyLeft) {
		Move_Player_Check(player, map, progress, 0, static_cast<int>(player.Get_Speed() / sqrt(2) + 0.5));
		Move_Player_Check(player, map, progress, -1 * static_cast<int>(player.Get_Speed() / sqrt(2) + 0.5), 0);
		player.Set_Direction(Object_Direction::DownLeft);
	}
	else if (KeyUp && !KeyDown) {
		Move_Player_Check(player, map, progress, 0, -1 * player.Get_Speed());
		player.Set_Direction(Object_Direction::Up);
	}
	else if (KeyDown && !KeyUp) {
		Move_Player_Check(player, map, progress, 0, player.Get_Speed());
		player.Set_Direction(Object_Direction::Down);
	}
	else if (KeyRight && !KeyLeft) {
		Move_Player_Check(player, map, progress, player.Get_Speed(), 0);
		player.Set_Direction(Object_Direction::Right);
	}
	else if (KeyLeft && !KeyRight) {
		Move_Player_Check(player, map, progress, -1 * player.Get_Speed(), 0);
		player.Set_Direction(Object_Direction::Left);
	}
}

//템플릿 특수화 해야한다.
template <typename T_Map>
void Move_Player_Check(Move_Object& player, const T_Map& map, Progress& progress, const int& move_x, const int& move_y) {
	if (!Crash_Check_Map(player, map, move_x, move_y))
		return;

	//맵 오브젝트와의 충돌
	for (int index = 0; index < 30; index++) {
		if (&map.Get_NM_Object_Const(index) != NULL && !Crash_Check_Object(player, map.Get_NM_Object_Const(index), move_x, move_y))
			return;
	}

	//맵 포탈과의 충돌
	if (&map.Get_Portal_Const() != NULL && !Crash_Check_Object(player, map.Get_Portal_Const(), move_x, move_y)) {
		//포탈과 충돌 했을 경우 던전 선택을 해야합니다.
		//퀘스트 안받았을 경우는 포탈 못탑니다. 일단 주석처리 해놓겠습니다. 나중에 주석 풀어주세요.
		//if (progress.Get_Quest_Num() != Quest_Name::No_Quest) {
			progress.Set_Map_Select(true);
			player.Set_Status(Player_Status::Map_Selecting);
		//}
		return;
	}
		

	//맵 Npc와의 충돌
	if (!Crash_Check_Npc(player, map, move_x, move_y))
		return;

	//적과의 충돌
	if (!Crash_Check_Enemy(player, map, move_x, move_y))
		return;

	player.Set_XPos(player.Get_XPos() + move_x);
	player.Set_YPos(player.Get_YPos() + move_y);
}

template <typename T_Map>
void Attack_Player(Player& player, T_Map& map) {
	bool attack = (GetAsyncKeyState(VK_LCONTROL) & 0x8000);

	if (player.Get_Status() != Player_Status::Attack) {
		if (attack) {
			player.Set_Status(Player_Status::Attack);
			player.Set_Ani_Count(0);
		}
	}
	else {
		//공격의 Hitting_Point지점
		if (player.Get_Ani_Count() == 9) {
			for (int index = 0; index < 20; index++) {
				if (&player.Get_Hit_Range_P_Const(index) == NULL) {
					//폴리곤 생성

					POINT pos[4];
					Create_Hitting_Polygon(player, pos, 70, 70, Hitting_Shape::FRONT);
	
					player.Set_Hit_Range_Polygon(index, HO_Player, pos);

					//히팅!

					Polygon_Damage_Enemy(map, player, player.Get_Hit_Range_P_Const(index), player.Get_Object_Info_Const().Get_Attack());
					//마지막 인자부분이 우리가 설정해주어야 할 배수이다. 즉 이건 기본공격이므로 배수가 안들어갔다. 100%의 공격임.

					//폴리곤 제거
					player.Delete_Hit_Range_Polygon(index);
					break;
				}
			}
		}

		if (player.Get_Ani_Count() == 20) {
			player.Set_Status(Player_Status::Stop);
			player.Set_Ani_Count(0);
		}
	}
}



