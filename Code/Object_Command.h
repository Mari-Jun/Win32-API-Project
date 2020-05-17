#pragma once
#include "Object_Move.h"

class Hitting_Range_Polygon;

template <typename P_Class, typename T_Map>
void Command_Player(P_Class& player, const T_Map& map) {

	if (player.Get_Status() == Player_Status::Interaction)
		return;

	if (player.Get_Status() != Player_Status::Stop)
		player.Set_Ani_Count(player.Get_Ani_Count() + 1);

	Attack_Player(player);

	Move_Player(player, map);
}

void Attack_Player(Warrior& warrior);

bool Crash_Attack_Polygon(Move_Object& m_objcet, Hitting_Range_Polygon& hit_range_p);
