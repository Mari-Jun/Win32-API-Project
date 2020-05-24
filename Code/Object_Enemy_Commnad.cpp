#include <Windows.h>
#include "Source.h"
#include "Game_Progress.h"
#include "Object_Enemy_Command.h"
#include "Object_Info.h"
#include "Object_Enemy.h"
#include "Map_Dungeon.h"

void Command_Enemy(Map_Dungeon& map_d) {
	for (int index = 0; index < 50; index++) {
		if (&map_d.Get_Enemy_Const(index) != NULL) {

			map_d.Get_Enemy(index).Set_Ani_Count(map_d.Get_Enemy_Const(index).Get_Ani_Count() + 1);
			if (map_d.Get_Enemy_Const(index).Get_Ani_Count() == 800)
				map_d.Get_Enemy(index).Set_Ani_Count(0);



			Hit_Enemy(map_d, index);
		}
	}
}

void Hit_Enemy(Map_Dungeon& map_d, const int& index) {
	Count_Up_Hitting_Damage_Count(map_d.Get_Enemy(index));
	Enemy_Kill_Check(map_d, index);
}

void Enemy_Kill_Check(Map_Dungeon& map_d, const int& index) {
	if (map_d.Get_Enemy_Const(index).Get_Object_Info_Const().Get_Hp() < 0)
		map_d.Kill_Enemy(index);
}