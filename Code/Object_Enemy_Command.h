#pragma once

class Map_Dungeon;

void Command_Enemy(Map_Dungeon& map_d);

/*Enemy Move*/
void Move_Enemy();

/*Enemy Attack*/

/*Enemy Hit*/

void Hit_Enemy(Map_Dungeon& map_d, const int& index);
void Enemy_Kill_Check(Map_Dungeon& map_d, const int& index);