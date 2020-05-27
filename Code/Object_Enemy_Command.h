#pragma once

class Map_Dungeon;
class Player;
class Move_Object;
class Hitting_Range_Polygon;

void Command_Enemy(Map_Dungeon& map_d, Player& player);

//Range범위 내에 플레이어가 있는지 확인
bool Reaction_Range_Check(const Move_Object& enemy, const Player& player, const int& range);

/*Enemy Move*/
void Move_Enemy_Check(Move_Object& enemy, const Map_Dungeon& map_d, const Player& player, const int& index, const int& move_x, const int& move_y);
void Move_Enemy(Map_Dungeon& map_d, const Player& player, const int& index);

/*Enemy Attack*/
void Attack_Enemy(Map_Dungeon& map_d, Player& player, const int& index);
void CalCul_Enemy_Hitting_Point(Move_Object& attack_obj, Player& player, const int& e_index);

/*Enemy Hit*/

void Hit_Enemy(Map_Dungeon& map_d, const int& index);
void Enemy_Kill_Check(Map_Dungeon& map_d, const int& index);