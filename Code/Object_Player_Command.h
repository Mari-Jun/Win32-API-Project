#pragma once
#include <math.h>
#include "Source.h"
#include "Object_Player.h"
#include "Game_Progress.h"

class Progress;
class Hitting_Range_Polygon;
class Move_Object;
class Player;
class Map_Village;
class Map_Dungeon;

/*Player Move*/
void Move_Player_Check(Move_Object& player, const Map_Village& map_v, Progress& progress, const int& move_x, const int& move_y);
void Move_Player_Check(Move_Object& player, const Map_Dungeon& map_d, Progress& progress, const int& move_x, const int& move_y);

/*Player Attack*/
void Attack_Player(Player& player, Map_Dungeon& map_d);

/*Player_Skill*/
void Skill_Player(Player& player, Map_Dungeon& map_d);

/*Player Hit*/
void Hit_Player(Player& player);
void Player_Kill_Check(Player& player);


template <typename T_Map>
void Command_Player(Player& player, T_Map& map, Progress& progress) {

	if (player.Get_Status() == Player_Status::Die || player.Get_Status() == Player_Status::Interaction || player.Get_Status() == Player_Status::Inventory || player.Get_Status() == Player_Status::Shopping ||
		player.Get_Status() == Player_Status::Map_Selecting)
		return;

	player.Set_Ani_Count(player.Get_Ani_Count() + 1);
	if (player.Get_Ani_Count() == 800)
		player.Set_Ani_Count(0);

	Move_Player(player, map, progress);
}

template <>
void Command_Player(Player& player, Map_Dungeon& map_d, Progress& progress);

template <typename T_Map>
void Move_Player(Move_Object& player, const T_Map& map, Progress& progress) {
	//나중에 충돌 체크 할일이 있을텐데, 그때는 모든 충돌이가능한 Object(맵, 적)에 대해서 검사를 한후 이동이 가능하게 해야합니다.

	bool KeyUp = (GetAsyncKeyState(VK_UP) & 0x8001);
	bool KeyDown = (GetAsyncKeyState(VK_DOWN) & 0x8001);
	bool KeyLeft = (GetAsyncKeyState(VK_LEFT) & 0x8001);
	bool KeyRight = (GetAsyncKeyState(VK_RIGHT) & 0x8001);


	if (player.Get_Status() != Player_Status::Attack && player.Get_Status() != Player_Status::SkillQ &&
		player.Get_Status() != Player_Status::SkillW && player.Get_Status() != Player_Status::SkillE &&
		player.Get_Status() != Player_Status::SkillR) {
		if (KeyUp || KeyDown || KeyLeft || KeyRight) {
			//마을이면 그냥 이동, 던전이면 달리기를 선택합니다.
			if (progress.Get_Map_Type() == Map_Type::Village1)
				player.Set_Status(Player_Status::Move);
			else
				player.Set_Status(Player_Status::Run);
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





