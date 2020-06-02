#include <Windows.h>
#include <iostream>
#include <tchar.h>
#include <math.h>
#include "Source.h"
#include "Object_Command.h"
#include "Object_Enemy_Command.h"
#include "Object_Enemy_Attack_Info.h"
#include "Object_Info.h"
#include "Object_Player.h"
#include "Object_Enemy.h"
#include "Object_Skill.h"
#include "Hitting_Range.h"
#include "Map_Dungeon.h"
#include "Game_Progress.h"
#include "Camera.h"
#include "File.h"

using namespace std;

void Command_Enemy(Map_Dungeon& map_d, Player& player, const Camera& camera, const File& file, const RECT c_rect) {
	for (int index = 0; index < 53; index++) {
		if (&map_d.Get_Enemy_Const(index) != NULL && Camera_Range_Check(map_d.Get_Enemy_Const(index), camera, c_rect)) {

			map_d.Get_Enemy(index).Set_Ani_Count(map_d.Get_Enemy_Const(index).Get_Ani_Count() + 1);
			if (map_d.Get_Enemy_Const(index).Get_Ani_Count() == 800)
				map_d.Get_Enemy(index).Set_Ani_Count(0);

			Move_Enemy(map_d, player, index);

			if (map_d.Get_Enemy_Const(index).Get_Attack_Delay() != 0)
				map_d.Get_Enemy(index).Set_Attack_Delay(map_d.Get_Enemy_Const(index).Get_Attack_Delay() - 1);

			for (int s_index = 0; s_index < 4; s_index++) {
				if (map_d.Get_Enemy_Const(index).Get_Enemy_Skill_Const().Get_Current_Delay(s_index) != 0)
					map_d.Get_Enemy(index).Get_Enemy_Skill().Set_Current_Delay(s_index, map_d.Get_Enemy_Const(index).Get_Enemy_Skill_Const().Get_Current_Delay(s_index) - 1);
			}

			Attack_Base_Enemy(map_d, player, file, index);

			//특정 시간때 Hitting을 합니다.
			CalCul_Enemy_Hitting_Point(map_d, map_d.Get_Enemy(index), player, index);

			Hit_Enemy(map_d, index);
		}
	}
}

bool Camera_Range_Check(const Move_Object& enemy, const Camera& camera, const RECT c_rect) {
	if (enemy.Get_XPos() + enemy.Get_Width() >= camera.Get_Cam_Left() && enemy.Get_XPos() <= camera.Get_Cam_Left() + c_rect.right &&
		enemy.Get_YPos() + enemy.Get_Height() >= camera.Get_Cam_Top() && enemy.Get_YPos() <= camera.Get_Cam_Top() + c_rect.bottom)
		return true;
	return false;
}

bool Reaction_Range_Check(const Move_Object& enemy, const Player& player, const int& range) {
	//범위 내에 있는 경우 true반환
	if (enemy.Get_XPos() + enemy.Get_Crash_Width() / 2 - range < player.Get_XPos() + player.Get_Crash_Width() &&
		enemy.Get_XPos() + enemy.Get_Crash_Width() / 2 + range > player.Get_XPos() &&
		enemy.Get_YPos() + enemy.Get_Height() - enemy.Get_Crash_Height() / 2 - range < player.Get_YPos() + player.Get_Height() &&
		enemy.Get_YPos() + enemy.Get_Height() - enemy.Get_Crash_Height() / 2 + range > player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height())
		return true;
	return false;
}

void Move_Enemy_Check(Move_Object& enemy, const Map_Dungeon& map_d, const Player& player, const int& index, const int& move_x, const int& move_y) {
	if (Crash_Check_Map(enemy, map_d, move_x, move_y))
		return;

	//맵 오브젝트와의 충돌
	for (int index = 0; index < 60; index++) {
		if (&map_d.Get_NM_Object_Const(index) != NULL && Crash_Check_Object(enemy, map_d.Get_NM_Object_Const(index), move_x, move_y))
			return;
	}

	//다른적과의 충돌
	for (int e_index = 0; e_index < 53; e_index++) {
		if (index == e_index)
			continue;
		if (&map_d.Get_Enemy_Const(e_index) != NULL && Crash_Check_Object(enemy, map_d.Get_Enemy_Const(e_index), move_x, move_y))
			return;
	}

	//플레이어와의 충돌
	if (Crash_Check_Object(enemy, player, move_x, move_y))
		return;

	enemy.Set_XPos(enemy.Get_XPos() + move_x);
	enemy.Set_YPos(enemy.Get_YPos() + move_y);
}

void Move_Enemy(Map_Dungeon& map_d, const Player& player, const int& index) {

	//플레이어 근처에 있을 경우의 움직임
	if (Reaction_Range_Check(map_d.Get_Enemy_Const(index), player, 400)) {

		//가만히 있는 경우 움직여준다.
		if (map_d.Get_Enemy(index).Get_Status() == Enemy_Status::E_Stop) {
			map_d.Get_Enemy(index).Set_Ani_Count(0);
			map_d.Get_Enemy(index).Set_Status(Enemy_Status::E_Move);
		}

		//적이 왼쪽에 있을 경우
		if (map_d.Get_Enemy_Const(index).Get_XPos() + map_d.Get_Enemy_Const(index).Get_Crash_Width() <= player.Get_XPos()) {
			if (map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height() <= player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height())
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::DownRight);
			else if (map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height() - map_d.Get_Enemy_Const(index).Get_Crash_Height() >= player.Get_YPos() + player.Get_Height())
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::UpRight);
			else
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::Right);
		}
		//적이 오른쪽에 있을 경우
		else if (map_d.Get_Enemy_Const(index).Get_XPos() >= player.Get_XPos() + player.Get_Crash_Width()) {
			if (map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height() <= player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height())
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::DownLeft);
			else if (map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height() - map_d.Get_Enemy_Const(index).Get_Crash_Height() >= player.Get_YPos() + player.Get_Height())
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::UpLeft);
			else
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::Left);
		}
		else {
			if (map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height() <= player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height())
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::Down);
			else
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::Up);
		}
	}
	else {
		//플레이어 근처에 있지 않을 경우의 움직임
		if (map_d.Get_Enemy_Const(index).Get_Ani_Count() % 40 == 0) {
			int r = rand() % 9;
			if (r == 9)
				map_d.Get_Enemy(index).Set_Status(Enemy_Status::E_Stop);
			else {
				map_d.Get_Enemy(index).Set_Status(Enemy_Status::E_Move);
				map_d.Get_Enemy(index).Set_Direction(rand() % 8);
			}
		}

	}

	//움직이는 중일 경우
	if (map_d.Get_Enemy_Const(index).Get_Status() == Enemy_Status::E_Move) {
		switch (map_d.Get_Enemy_Const(index).Get_Direction())
		{
		case Object_Direction::Right:
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, map_d.Get_Enemy_Const(index).Get_Speed(), 0);
			break;
		case Object_Direction::UpRight:
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, 0, -1 * static_cast<int>(map_d.Get_Enemy_Const(index).Get_Speed() / sqrt(2) + 0.5));
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, static_cast<int>(map_d.Get_Enemy_Const(index).Get_Speed() / sqrt(2) + 0.5), 0);
			break;
		case Object_Direction::Up:
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, 0, -1 * map_d.Get_Enemy_Const(index).Get_Speed());
			break;
		case Object_Direction::UpLeft:
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, 0, -1 * static_cast<int>(map_d.Get_Enemy_Const(index).Get_Speed() / sqrt(2) + 0.5));
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, -1 * static_cast<int>(map_d.Get_Enemy_Const(index).Get_Speed() / sqrt(2) + 0.5), 0);;
			break;
		case Object_Direction::Left:
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, -1 * map_d.Get_Enemy_Const(index).Get_Speed(), 0);
			break;
		case Object_Direction::DownLeft:
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, 0, static_cast<int>(map_d.Get_Enemy_Const(index).Get_Speed() / sqrt(2) + 0.5));
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, -1 * static_cast<int>(map_d.Get_Enemy_Const(index).Get_Speed() / sqrt(2) + 0.5), 0);
			break;
		case Object_Direction::Down:
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, 0, map_d.Get_Enemy_Const(index).Get_Speed());
			break;
		case Object_Direction::DownRight:
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, 0, static_cast<int>(map_d.Get_Enemy_Const(index).Get_Speed() / sqrt(2) + 0.5));
			Move_Enemy_Check(map_d.Get_Enemy(index), map_d, player, index, static_cast<int>(map_d.Get_Enemy_Const(index).Get_Speed() / sqrt(2) + 0.5), 0);
			break;
		default:
			break;
		}
	}
}

void Attack_Base_Enemy(Map_Dungeon& map_d, const Player& player, const File& file, const int& index) {
	if (map_d.Get_Enemy_Const(index).Get_Attack_Delay() == 0) {
		if (map_d.Get_Enemy_Const(index).Get_Status() == Enemy_Status::E_Stop || map_d.Get_Enemy_Const(index).Get_Status() == Enemy_Status::E_Move)
			Attack_Select(map_d.Get_Enemy(index), player);
		else
			Attack_Enemy_Action(map_d.Get_Enemy(index), player, file);

	}
}

void Attack_Select(Enemy& enemy, const Player& player) {
	for (int select = 4; select > 0; select--) {
		if (enemy.Get_Enemy_Skill_Const().Get_Skill_Delay(select - 1) != 0 && enemy.Get_Enemy_Skill_Const().Get_Current_Delay(select - 1) == 0) {
			if (Reaction_Range_Check(enemy, player, enemy.Get_Attack_Reaction_Range(select))) {
				enemy.Set_Status(Enemy_Status::E_Attack + select);
				enemy.Set_Ani_Count(0);
				return;
			}
		}
	}
	if (Reaction_Range_Check(enemy, player, enemy.Get_Attack_Reaction_Range(0))) {
		enemy.Set_Status(Enemy_Status::E_Attack);
		enemy.Set_Ani_Count(0);
		return;
	}
}

void Create_Hitting_Point(Enemy& enemy, const Player& player, const File& file, const int& owner, const int& type, const int& attack_type) {
	for (int index = 0; index < 20; index++) {
		if (&enemy.Get_Hit_Range_P_Const(index) == NULL) {
			//폴리곤 생성

			POINT pos[4];
			if (file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Guide) == 1) {
				Create_Hitting_Polygon(enemy, pos, file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Range_X),
					file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Range_Y), Hitting_Shape::ROUND);
				enemy.Set_Hit_Range_Polygon(index, owner, false, enemy.Get_Direction(), true,
					Create_Guide_Speed(enemy, player, file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Hit_Delay)),
					type, attack_type, pos, file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Hit_Delay), file.Get_Enemy_Attack_Multiple_Info(enemy.Get_Enemy_Type(), attack_type));
			}
			else {
				Create_Hitting_Polygon(enemy, pos, file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Range_X),
					file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Range_Y),
					file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Shape));
				enemy.Set_Hit_Range_Polygon(index, owner, file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Move), enemy.Get_Direction(),
					false, Create_Speed(enemy.Get_Direction(), file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Speed)), type, attack_type,
					pos, file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), attack_type, Attack_Info::Attack_Hit_Delay), file.Get_Enemy_Attack_Multiple_Info(enemy.Get_Enemy_Type(), attack_type));
			}
			return;
		}
	}
}

void Attack_Enemy_End(Enemy& enemy, const int& attack_delay) {
	Attack_End(enemy);
	enemy.Set_Attack_Delay(attack_delay);
}

void Skill_Enemy_End(Enemy& enemy, const int& index, const int& attack_delay) {
	Attack_Enemy_End(enemy, attack_delay);
	enemy.Get_Enemy_Skill().Set_Current_Delay(index, enemy.Get_Enemy_Skill_Const().Get_Skill_Delay(index));
}

//히팅 범위를 적에게 적용하는 함수
void CalCul_Enemy_Hitting_Point(Map_Dungeon& map_d, Move_Object& attack_obj, Player& player, const int& e_index) {
	
	//히팅 포인트 지점 계산
	for (int index = 0; index < 20; index++) {
		if (&attack_obj.Get_Hit_Range_P_Const(index) != NULL) {
			if (!attack_obj.Get_Hit_Range_P_Const(index).Is_Move() && attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() == 0) {
				Polygon_Damage_Enemy(attack_obj, player, attack_obj.Get_Hit_Range_P_Const(index), attack_obj.Get_Object_Info_Const().Get_Attack() * attack_obj.Get_Hit_Range_P_Const(index).Get_Attack_Multiple());
				attack_obj.Delete_Hit_Range_Polygon(index);
			}
			else if (attack_obj.Get_Hit_Range_P_Const(index).Is_Move()) {
				if (Polygon_Damage_Enemy(attack_obj, player, attack_obj.Get_Hit_Range_P_Const(index), attack_obj.Get_Object_Info_Const().Get_Attack() * attack_obj.Get_Hit_Range_P_Const(index).Get_Attack_Multiple())
					|| Crash_Check_Attack(map_d, attack_obj.Get_Hit_Range_P_Const(index)) || attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() == 0)
					attack_obj.Delete_Hit_Range_Polygon(index);
				//플레이어와 부딪히지 않았고 삭제 딜레이도 시간이 있으니 움직여줍니다.
				else
					Move_Hitting_Range_Polygon(attack_obj.Get_Hit_Range_P(index));
			}
			else if (attack_obj.Get_Hit_Range_P_Const(index).Is_Guide()) {
				if (attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() == 0) {
					Polygon_Damage_Enemy(attack_obj, player, attack_obj.Get_Hit_Range_P_Const(index), attack_obj.Get_Object_Info_Const().Get_Attack() * attack_obj.Get_Hit_Range_P_Const(index).Get_Attack_Multiple());
					attack_obj.Delete_Hit_Range_Polygon(index);
				}
				else
					Move_Hitting_Range_Polygon(attack_obj.Get_Hit_Range_P(index));
			}

			if (&attack_obj.Get_Hit_Range_P_Const(index) != NULL)
				attack_obj.Get_Hit_Range_P(index).Set_Delay(attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() - 1);
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