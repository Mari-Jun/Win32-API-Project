#pragma once
#include <Windows.h>
#include <math.h>
#include "Source.h"
#include "Object_Player.h"
#include "Object_Info.h"

class Map_Village;

template <typename T_Map> 
void Move_Player(Player& player, const T_Map& map) {

	//나중에 충돌 체크 할일이 있을텐데, 그때는 모든 충돌이가능한 Object(맵, 적)에 대해서 검사를 한후 이동이 가능하게 해야합니다.

	bool KeyUp = (GetAsyncKeyState(VK_UP) & 0x8000);
	bool KeyDown = (GetAsyncKeyState(VK_DOWN) & 0x8000);
	bool KeyLeft = (GetAsyncKeyState(VK_LEFT) & 0x8000);
	bool KeyRight = (GetAsyncKeyState(VK_RIGHT) & 0x8000);


	//이러면 안되는데..
	if (player.Get_Status() != Player_Status::Attack) {
		if (KeyUp || KeyDown || KeyLeft || KeyRight) {
			player.Set_Status(Player_Status::Move);
		}
		else {
			player.Set_Ani_Count(0);
			player.Set_Status(Player_Status::Stop);
		}
	}

	if (KeyUp && KeyRight) {
		Move_Object_Check(player, map, 0, -1 * static_cast<int>(player.Get_Player_Info_Const().Get_Speed() / sqrt(2) + 0.5));
		Move_Object_Check(player, map, static_cast<int>(player.Get_Player_Info_Const().Get_Speed() / sqrt(2) + 0.5), 0);
		player.Set_Direction(Object_Direction::UpRight);
	}
	else if (KeyUp && KeyLeft) {
		Move_Object_Check(player, map, 0, -1 * static_cast<int>(player.Get_Player_Info_Const().Get_Speed() / sqrt(2) + 0.5));
		Move_Object_Check(player, map, -1 * static_cast<int>(player.Get_Player_Info_Const().Get_Speed() / sqrt(2) + 0.5), 0);
		player.Set_Direction(Object_Direction::UpLeft);
	}
	else if (KeyDown && KeyRight) {
		Move_Object_Check(player, map, 0, static_cast<int>(player.Get_Player_Info_Const().Get_Speed() / sqrt(2) + 0.5));
		Move_Object_Check(player, map, static_cast<int>(player.Get_Player_Info_Const().Get_Speed() / sqrt(2) + 0.5), 0);
		player.Set_Direction(Object_Direction::DownRight);
	}
	else if (KeyDown && KeyLeft) {
		Move_Object_Check(player, map, 0, static_cast<int>(player.Get_Player_Info_Const().Get_Speed() / sqrt(2) + 0.5));
		Move_Object_Check(player, map, -1 * static_cast<int>(player.Get_Player_Info_Const().Get_Speed() / sqrt(2) + 0.5), 0);
		player.Set_Direction(Object_Direction::DownLeft);
	}
	else if (KeyUp && !KeyDown) {
		Move_Object_Check(player, map, 0, -1 * player.Get_Player_Info_Const().Get_Speed());
		player.Set_Direction(Object_Direction::Up);
	}
	else if (KeyDown && !KeyUp) {
		Move_Object_Check(player, map, 0, player.Get_Player_Info_Const().Get_Speed());
		player.Set_Direction(Object_Direction::Down);
	}
	else if (KeyRight && !KeyLeft) {
		Move_Object_Check(player, map, player.Get_Player_Info_Const().Get_Speed(), 0);
		player.Set_Direction(Object_Direction::Right);
	}
	else if (KeyLeft && !KeyRight) {
		Move_Object_Check(player, map, -1 * player.Get_Player_Info_Const().Get_Speed(), 0);
		player.Set_Direction(Object_Direction::Left);
	}
}

template <typename M_Ob, typename T_Map>
void Move_Object_Check(M_Ob& object, const T_Map& map, const int& move_x, const int& move_y) {
	if (!Crash_Check_Map(object, map, move_x, move_y))
		return;

	object.Set_XPos(object.Get_XPos() + move_x);
	object.Set_YPos(object.Get_YPos() + move_y);
}

template <>
void Move_Object_Check(Player& m_object, const Map_Village& map_v, const int& move_x, const int& move_y);

bool Crash_Check_Map(const Move_Object& m_object, const Map& map, const int& move_x, const int& move_y);
bool Crash_Check_Object(const Move_Object& m_object, const Object& obj, const int& move_x, const int& move_y);
bool Crash_Check_Village_Map(const Move_Object& object, const Map_Village& map_v, const int& move_x, const int& move_y);
