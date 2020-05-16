#include <Windows.h>
#include <math.h>
#include "Source.h"
#include "Object_Move.h"
#include "Object_Npc.h"
#include "Object_Enemy.h"
#include "Object_Command.h"
#include "Map_Village.h"

template <>
void Move_Object_Check(Player& player, const Map_Village& map_v, const int& move_x, const int& move_y) {
	if (!Crash_Check_Map(player, map_v, move_x, move_y))
		return;

	if (!Crash_Check_Village_Map(player, map_v, move_x, move_y))
		return;

	player.Set_XPos(player.Get_XPos() + move_x);
	player.Set_YPos(player.Get_YPos() + move_y);
}

bool Crash_Check_Map(const Move_Object& m_object, const Map& map, const int& move_x, const int& move_y) {
	if (m_object.Get_XPos() + move_x >= map.Get_Map_Rect().left && m_object.Get_XPos() + m_object.Get_Width() + move_x <= map.Get_Map_Rect().right &&
		m_object.Get_YPos() + move_y >= map.Get_Map_Rect().top && m_object.Get_YPos() + m_object.Get_Height() + move_y <= map.Get_Map_Rect().bottom)
		return true;
	return false;
}

bool Crash_Check_Object(const Move_Object& m_object, const Object& obj, const int& move_x, const int& move_y) {
	if (m_object.Get_XPos() + m_object.Get_Crash_Width() + move_x > obj.Get_XPos() && m_object.Get_XPos() + move_x < obj.Get_XPos() + obj.Get_Crash_Width() &&
		m_object.Get_YPos() + m_object.Get_Height() + move_y > obj.Get_YPos() + obj.Get_Height() - obj.Get_Crash_Height() &&
		m_object.Get_YPos() + m_object.Get_Height() - m_object.Get_Crash_Height() + move_y < obj.Get_YPos() + obj.Get_Height())
		return false;
	return true;
}

bool Crash_Check_Village_Map(const Move_Object& m_object, const Map_Village& map_v, const int& move_x, const int& move_y) {
	for (int index = 0; index < 10; index++) {
		if (&map_v.Get_NM_Object(index) != NULL && !Crash_Check_Object(m_object, map_v.Get_NM_Object(index), move_x, move_y))
			return false;
	}

	for (int index = 0; index < 4; index++) {
		if (&map_v.Get_NM_Npc_Const(index) != NULL && !Crash_Check_Object(m_object, map_v.Get_NM_Npc_Const(index), move_x, move_y))
			return false;
	}

	if (&map_v.Get_P_Enemy_Const() != NULL && !Crash_Check_Object(m_object, map_v.Get_P_Enemy_Const(), move_x, move_y))
		return false;

	return true;
}

