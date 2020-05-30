#pragma once
class Move_Object;
class Map;
class Object;
class Map_Village;
class Map_Dungeon;
class Hitting_Range_Polygon;

/*Move*/

bool Crash_Check_Map(const Move_Object& m_object, const Map& map, const int& move_x, const int& move_y);
bool Crash_Check_Object(const Move_Object& m_object, const Object& obj, const int& move_x, const int& move_y);
bool Crash_Check_Npc(const Move_Object& m_objcet, const Map_Village& map_v, const int& move_x, const int& move_y);
bool Crash_Check_Enemy(const Move_Object& m_objcet, const Map_Dungeon& map_d, const int& move_x, const int& move_y);

/*Attack*/

const bool Crash_Attack_Polygon(const Move_Object& attack_obj, const Move_Object& hit_object, const Hitting_Range_Polygon& hit_range_p);
const bool Polygon_Damage_Enemy(const Move_Object& attack_obj, Move_Object& hit_obj, const Hitting_Range_Polygon& hit_range_p, const int& hit_dmg);
void Create_Hitting_Point(Move_Object& m_object, const int& width_size, const int& height_size, const int& shape, const int& owner, const bool& move, const int& speed, const int& type, const int& attack_type, const int& delay, const double& attack_multiple);
void Create_Hitting_Polygon(const Move_Object& m_object, POINT* pos, const int& width_size, const int& height_size, const int& shape);
void Attack_End(Move_Object& m_objcet);
