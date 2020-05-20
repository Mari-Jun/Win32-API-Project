#include <Windows.h>
#include <math.h>
#include "Source.h"
#include "Object_Command.h"
#include "Hitting_Range.h"
#include "Object_Npc.h"
#include "Object_Player.h"
#include "Object_Enemy.h"
#include "Map_Main.h"
#include "Map_Village.h"


bool Crash_Check_Map(const Move_Object& m_object, const Map& map, const int& move_x, const int& move_y) {
	if (m_object.Get_XPos() + move_x >= map.Get_Map_Rect().left && m_object.Get_XPos() + m_object.Get_Crash_Width() + move_x <= map.Get_Map_Rect().right &&
		m_object.Get_YPos() + move_y >= map.Get_Map_Rect().top && m_object.Get_YPos() + m_object.Get_Height() - m_object.Get_Crash_Height() + move_y <= map.Get_Map_Rect().bottom)
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

bool Crash_Check_Npc(const Move_Object& m_objcet, const Map_Village& map_v, const int& move_x, const int& move_y) {
	for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) {
		if (&map_v.Get_Npc_Const(npc_type) != NULL && !Crash_Check_Object(m_objcet, map_v.Get_Npc_Const(npc_type), move_x, move_y))
			return false;
	}

	return true;
}

bool Crash_Check_Enemy(const Move_Object& m_objcet, const Map_Village& map_v, const int& move_x, const int& move_y) {
	if (&map_v.Get_P_Enemy_Const() != NULL && !Crash_Check_Object(m_objcet, map_v.Get_P_Enemy_Const(), move_x, move_y))
		return false;
	return true;
}

bool Crash_Attack_Polygon(const Move_Object& attack_obj, const Move_Object& hit_object, const Hitting_Range_Polygon& hit_range_p) {

	//두점 사이의 벡터를 구합니다.
	int vx = (hit_range_p.Get_Pos(2).x + hit_range_p.Get_Pos(0).x) / 2 - (hit_object.Get_XPos() + hit_object.Get_Crash_Width() / 2);
	int vy = (hit_range_p.Get_Pos(2).y + hit_range_p.Get_Pos(0).y) / 2 - (hit_object.Get_YPos() + hit_object.Get_Height() - hit_object.Get_Crash_Height() / 2);

	//4방향의 사영벡터 크기를 구합니다.
	int proj[3][4];
	proj[0][Object_Direction::Right] = vx;
	proj[0][Object_Direction::Up] = vy;
	proj[0][Object_Direction::UpRight] = vx * sqrt(0.5) - vy * sqrt(0.5);
	proj[0][Object_Direction::UpLeft] = vx * sqrt(0.5) + vy * sqrt(0.5);
	proj[0][Object_Direction::UpRight] = abs(proj[0][Object_Direction::UpRight]);
	proj[0][Object_Direction::UpLeft] = abs(proj[0][Object_Direction::UpLeft]);


	//오브젝터의 사영 크기를 구합니다.
	proj[1][Object_Direction::Right] = hit_object.Get_Crash_Width() / 2;
	proj[1][Object_Direction::Up] = hit_object.Get_Crash_Height() / 2;
	proj[1][Object_Direction::UpRight] = sqrt(0.5) * (hit_object.Get_Crash_Width() / 2) + sqrt(0.5) * (hit_object.Get_Crash_Height() / 2);
	proj[1][Object_Direction::UpLeft] = sqrt(0.5) * (hit_object.Get_Crash_Width() / 2) + sqrt(0.5) * (hit_object.Get_Crash_Height() / 2);

	//히팅범위의 사영크기를 구합니다.
	proj[2][Object_Direction::Right] = abs(abs(hit_range_p.Get_Pos(2).x + hit_range_p.Get_Pos(0).x) / 2 - abs(hit_range_p.Get_Pos(1).x + hit_range_p.Get_Pos(0).x) / 2) + abs(abs(hit_range_p.Get_Pos(2).x + hit_range_p.Get_Pos(0).x) / 2 - abs(hit_range_p.Get_Pos(2).x + hit_range_p.Get_Pos(1).x) / 2);
	proj[2][Object_Direction::Up] = abs(abs(hit_range_p.Get_Pos(2).y + hit_range_p.Get_Pos(0).y) / 2 - abs(hit_range_p.Get_Pos(1).y + hit_range_p.Get_Pos(0).y) / 2) + abs(abs(hit_range_p.Get_Pos(2).y + hit_range_p.Get_Pos(0).y) / 2 - abs(hit_range_p.Get_Pos(2).y + hit_range_p.Get_Pos(1).y) / 2);
	if (attack_obj.Get_Direction() % 4 == 3) {
		proj[2][Object_Direction::UpRight] = (sqrt(pow((static_cast<double>(hit_range_p.Get_Pos(2).x) - static_cast<double>(hit_range_p.Get_Pos(1).x)), 2) + pow((static_cast<double>(hit_range_p.Get_Pos(2).y) - static_cast<double>(hit_range_p.Get_Pos(1).y)), 2))) / 2;
		proj[2][Object_Direction::UpLeft] = (sqrt(pow((static_cast<double>(hit_range_p.Get_Pos(1).x) - static_cast<double>(hit_range_p.Get_Pos(0).x)), 2) + pow((static_cast<double>(hit_range_p.Get_Pos(1).y) - static_cast<double>(hit_range_p.Get_Pos(0).y)), 2))) / 2;
	}
	else if (attack_obj.Get_Direction() % 4 == 1) {
		proj[2][Object_Direction::UpRight] = (sqrt(pow((static_cast<double>(hit_range_p.Get_Pos(0).x) - static_cast<double>(hit_range_p.Get_Pos(1).x)), 2) + pow((static_cast<double>(hit_range_p.Get_Pos(0).y) - static_cast<double>(hit_range_p.Get_Pos(1).y)), 2))) / 2;
		proj[2][Object_Direction::UpLeft] = (sqrt(pow((static_cast<double>(hit_range_p.Get_Pos(2).x) - static_cast<double>(hit_range_p.Get_Pos(1).x)), 2) + pow((static_cast<double>(hit_range_p.Get_Pos(2).y) - static_cast<double>(hit_range_p.Get_Pos(1).y)), 2))) / 2;
	}
	
	if (abs(proj[0][Object_Direction::Right]) > proj[2][Object_Direction::Right] + proj[1][Object_Direction::Right])
		return false;
	if (abs(proj[0][Object_Direction::Up]) > proj[2][Object_Direction::Up] + proj[1][Object_Direction::Up])
		return false;

	if (attack_obj.Get_Direction() % 2 == 1) {
		if (abs(proj[0][Object_Direction::UpRight]) > proj[2][Object_Direction::UpRight] + proj[1][Object_Direction::UpRight])
			return false;
		if (abs(proj[0][Object_Direction::UpLeft]) > proj[2][Object_Direction::UpLeft] + proj[1][Object_Direction::UpLeft])
			return false;
	}
	
	return true;
}

void Polygon_Damage_Enemy(Map_Village& map_v, const Move_Object& attack_obj, const Hitting_Range_Polygon& hit_range_p) {
	if (hit_range_p.Get_Owner() == HO_Player && &map_v.Get_P_Enemy_Const() != NULL && Crash_Attack_Polygon(attack_obj, map_v.Get_P_Enemy_Const(), hit_range_p)) 
		Calcul_Hitting_Damage(attack_obj, map_v.Get_P_Enemy());	
}

void Create_Hitting_Polygon(const Move_Object& m_object, POINT* pos, const int& width_size, const int& height_size, const int& shape) {
	switch (shape)
	{
	case Hitting_Shape::FRONT:
		pos[0] = { m_object.Get_XPos() + m_object.Get_Crash_Width() / 2 - static_cast <int>(width_size * sin(m_object.Get_Direction() * 45 * PIE / 180)) ,m_object.Get_YPos() + m_object.Get_Height() - m_object.Get_Crash_Height() / 2 - static_cast <int>(height_size * cos(m_object.Get_Direction() * 45 * PIE / 180)) };
		pos[1] = { m_object.Get_XPos() + m_object.Get_Crash_Width() / 2 + static_cast <int>(sqrt(width_size * width_size + height_size * height_size) * cos((m_object.Get_Direction() + 1) * 45 * PIE / 180)), m_object.Get_YPos() + m_object.Get_Height() - m_object.Get_Crash_Height() / 2 - static_cast <int>(sqrt(width_size * width_size + height_size * height_size) * sin((m_object.Get_Direction() + 1) * 45 * PIE / 180)) };
		pos[2] = { m_object.Get_XPos() + m_object.Get_Crash_Width() / 2 + static_cast <int>(sqrt(width_size * width_size + height_size * height_size) * sin((m_object.Get_Direction() + 1) * 45 * PIE / 180)), m_object.Get_YPos() + m_object.Get_Height() - m_object.Get_Crash_Height() / 2 + static_cast <int>(sqrt(width_size * width_size + height_size * height_size) * cos((m_object.Get_Direction() + 1) * 45 * PIE / 180)) };
		pos[3] = { m_object.Get_XPos() + m_object.Get_Crash_Width() / 2 + static_cast <int>(width_size * sin(m_object.Get_Direction() * 45 * PIE / 180)),m_object.Get_YPos() + m_object.Get_Height() - m_object.Get_Crash_Height() / 2 + static_cast <int>(height_size * cos(m_object.Get_Direction() * 45 * PIE / 180)) };
		break;
	default:
		break;
	}
}