#include <Windows.h>
#include "Source.h"
#include "Game_Progress.h"
#include "Object_Enemy_Command.h"
#include "Object_Player_Command.h"
#include "Object_Info.h"
#include "Object_Enemy.h"
#include "Hitting_Range.h"
#include "Hitting_Range.h"
#include "Map_Dungeon.h"

void Command_Enemy(Map_Dungeon& map_d, Player& player) {
	for (int index = 0; index < 50; index++) {
		if (&map_d.Get_Enemy_Const(index) != NULL) {

			map_d.Get_Enemy(index).Set_Ani_Count(map_d.Get_Enemy_Const(index).Get_Ani_Count() + 1);
			if (map_d.Get_Enemy_Const(index).Get_Ani_Count() == 800)
				map_d.Get_Enemy(index).Set_Ani_Count(0);

			Move_Enemy(map_d, player, index);

			if (map_d.Get_Enemy_Const(index).Get_Attack_Delay() != 0)
				map_d.Get_Enemy(index).Set_Attack_Delay(map_d.Get_Enemy_Const(index).Get_Attack_Delay() - 1);

			for (int s_index = 0; s_index < 5; s_index++) {
				if (map_d.Get_Enemy_Const(index).Get_Skill_Delay(s_index) != 0)
					map_d.Get_Enemy(index).Set_Skill_Delay(s_index, map_d.Get_Enemy_Const(index).Get_Skill_Delay(s_index) - 1);
			}

			Attack_Enemy(map_d, player);

			Hit_Enemy(map_d, index);
		}
	}
}

bool Reaction_Range_Check(const Move_Object& enemy, const Player& player, const int& range) {
	//범위 내에 있는 경우 true반환
	if (enemy.Get_XPos() - range < player.Get_XPos() + player.Get_Crash_Width() &&
		enemy.Get_XPos() + enemy.Get_Crash_Width() + range > player.Get_XPos() &&
		enemy.Get_YPos() + enemy.Get_Crash_Height() - enemy.Get_Crash_Height() - range < player.Get_YPos() + player.Get_Crash_Height() &&
		enemy.Get_YPos() + enemy.Get_Crash_Height() + range > player.Get_YPos())
		return true;
	return false;
}

void Move_Enemy_Check(Move_Object& enemy, const Map_Dungeon& map_d, const Player& player, const int& index, const int& move_x, const int& move_y) {
	if (Crash_Check_Map(enemy, map_d, move_x, move_y))
		return;

	//맵 오브젝트와의 충돌
	for (int index = 0; index < 30; index++) {
		if (&map_d.Get_NM_Object_Const(index) != NULL && Crash_Check_Object(enemy, map_d.Get_NM_Object_Const(index), move_x, move_y))
			return;
	}

	//다른적과의 충돌
	for (int e_index = 0; e_index < 50; e_index++) {
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
	if (Reaction_Range_Check(map_d.Get_Enemy_Const(index), player, 300)) {

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

void Attack_Enemy(Map_Dungeon& map_d, Player& player) {

	for (int e_index = 0; e_index < 50; e_index++) {
		if (&map_d.Get_Enemy_Const(e_index) != NULL) {
			if (map_d.Get_Enemy_Const(e_index).Get_Attack_Delay() == 0) {
				switch (map_d.Get_Enemy_Const(e_index).Get_Enemy_Type())
				{
				case Enemy_Type::Bird:
					//이 밑부터 전체를 함수화를 하면 되지 않을까?
					//아직은 ㄴㄴ하다. 왜냐? Skill을 구현하고 함수화를 하자
					if (map_d.Get_Enemy_Const(e_index).Get_Status() != Enemy_Status::E_Attack) {
						if (Reaction_Range_Check(map_d.Get_Enemy_Const(e_index), player, 60)) {
							map_d.Get_Enemy(e_index).Set_Status(Enemy_Status::E_Attack);
							map_d.Get_Enemy(e_index).Set_Ani_Count(0);
						}
					}
					else {
						//공격의 Hitting_Point생성 지점
						if (map_d.Get_Enemy_Const(e_index).Get_Ani_Count() == 4) {
							for (int index = 0; index < 20; index++) {
								if (&map_d.Get_Enemy_Const(e_index).Get_Hit_Range_P_Const(index) == NULL) {
									//폴리곤 생성

									POINT pos[4];
									Create_Hitting_Polygon(map_d.Get_Enemy_Const(e_index), pos, 50, 50, Hitting_Shape::FRONT);

									map_d.Get_Enemy(e_index).Set_Hit_Range_Polygon(index, Hit_Owner::HO_Enemy, pos, 6);
									break;
								}
							}
						}
						//공격의 Hitting_Point실행 지점
						else if (map_d.Get_Enemy_Const(e_index).Get_Ani_Count() == 10) {

						}
						else if (map_d.Get_Enemy_Const(e_index).Get_Ani_Count() == 16) {
							map_d.Get_Enemy(e_index).Set_Status(Enemy_Status::E_Move);
							map_d.Get_Enemy(e_index).Set_Ani_Count(0);
							map_d.Get_Enemy(e_index).Set_Attack_Delay(16);
						}
					}
					break;
				default:
					break;
				}
			}
			//히팅 포인트 지점 계산
			for (int index = 0; index < 20; index++) {
				if (&map_d.Get_Enemy_Const(e_index).Get_Hit_Range_P_Const(index) != NULL) {
					if (map_d.Get_Enemy_Const(e_index).Get_Hit_Range_P_Const(index).Get_Delay() == 0) {
						Polygon_Damage_Player(map_d.Get_Enemy_Const(e_index), player, map_d.Get_Enemy_Const(e_index).Get_Hit_Range_P_Const(index), map_d.Get_Enemy_Const(e_index).Get_Object_Info_Const().Get_Attack());
						//마지막 인자부분이 우리가 설정해주어야 할 배수이다. 즉 이건 기본공격이므로 배수가 안들어갔다. 100%의 공격임.

						//폴리곤 제거
						map_d.Get_Enemy(e_index).Delete_Hit_Range_Polygon(index);
					}

					if (&map_d.Get_Enemy_Const(e_index).Get_Hit_Range_P_Const(index) != NULL)
						map_d.Get_Enemy(e_index).Get_Hit_Range_P(index).Set_Delay(map_d.Get_Enemy_Const(e_index).Get_Hit_Range_P_Const(index).Get_Delay() - 1);
				}
			}
		}
	}


}


void Polygon_Damage_Player(const Move_Object& attack_obj, Player& player, const Hitting_Range_Polygon& hit_range_p, const int& hit_dmg) {
	if (hit_range_p.Get_Owner() == Hit_Owner::HO_Enemy && &player != NULL && Crash_Attack_Polygon(attack_obj, player, hit_range_p))
		Calcul_Hitting_Damage(attack_obj, player, hit_dmg);
}

void Hit_Enemy(Map_Dungeon& map_d, const int& index) {
	Count_Up_Hitting_Damage_Count(map_d.Get_Enemy(index));
	Enemy_Kill_Check(map_d, index);
}

void Enemy_Kill_Check(Map_Dungeon& map_d, const int& index) {
	if (map_d.Get_Enemy_Const(index).Get_Object_Info_Const().Get_Hp() < 0)
		map_d.Kill_Enemy(index);
}