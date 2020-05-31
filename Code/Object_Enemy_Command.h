#pragma once

class Map_Dungeon;
class Player;
class Enemy;
class Move_Object;
class Hitting_Range_Polygon;
class Camera;
class File;

void Command_Enemy(Map_Dungeon& map_d, Player& player, const Camera& camera, const File& file, const RECT c_rect);

//Range범위 내에 플레이어가 있는지 확인
bool Camera_Range_Check(const Move_Object& enemy, const Camera& camera, const RECT c_rect);
bool Reaction_Range_Check(const Move_Object& enemy, const Player& player, const int& range);

/*Enemy Move*/
void Move_Enemy_Check(Move_Object& enemy, const Map_Dungeon& map_d, const Player& player, const int& index, const int& move_x, const int& move_y);
void Move_Enemy(Map_Dungeon& map_d, const Player& player, const int& index);

/*Enemy Attack*/
void Attack_Base_Enemy(Map_Dungeon& map_d, const Player& player, const File& file, const int& index);
void Attack_Select(Enemy& enemy, const Player& player);
void Create_Hitting_Point(Enemy& enemy, const Player& player, const File& file, const int& owner, const int& type, const int& attack_type);

void Attack_Enemy_End(Enemy& enemy, const int& attack_delay);
void Skill_Enemy_End(Enemy& enemy, const int& index, const int& attack_delay);
void CalCul_Enemy_Hitting_Point(Map_Dungeon& map_d, Move_Object& attack_obj, Player& player, const int& e_index);

/*Enemy Hit*/

void Hit_Enemy(Map_Dungeon& map_d, const int& index);
void Enemy_Kill_Check(Map_Dungeon& map_d, const int& index);