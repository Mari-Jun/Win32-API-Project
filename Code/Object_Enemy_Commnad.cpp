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

using namespace std;

void Command_Enemy(Map_Dungeon& map_d, Player& player) {
	for (int index = 0; index < 50; index++) {
		if (&map_d.Get_Enemy_Const(index) != NULL) {

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

			Attack_Base_Enemy(map_d, player, index);

			//Ư�� �ð��� Hitting�� �մϴ�.
			CalCul_Enemy_Hitting_Point(map_d.Get_Enemy(index), player, index);

			Hit_Enemy(map_d, index);
		}
	}
}

bool Reaction_Range_Check(const Move_Object& enemy, const Player& player, const int& range) {
	//���� ���� �ִ� ��� true��ȯ
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

	//�� ������Ʈ���� �浹
	for (int index = 0; index < 30; index++) {
		if (&map_d.Get_NM_Object_Const(index) != NULL && Crash_Check_Object(enemy, map_d.Get_NM_Object_Const(index), move_x, move_y))
			return;
	}

	//�ٸ������� �浹
	for (int e_index = 0; e_index < 50; e_index++) {
		if (index == e_index)
			continue;
		if (&map_d.Get_Enemy_Const(e_index) != NULL && Crash_Check_Object(enemy, map_d.Get_Enemy_Const(e_index), move_x, move_y))
			return;
	}

	//�÷��̾���� �浹
	if (Crash_Check_Object(enemy, player, move_x, move_y))
		return;

	enemy.Set_XPos(enemy.Get_XPos() + move_x);
	enemy.Set_YPos(enemy.Get_YPos() + move_y);
}

void Move_Enemy(Map_Dungeon& map_d, const Player& player, const int& index) {

	//�÷��̾� ��ó�� ���� ����� ������
	if (Reaction_Range_Check(map_d.Get_Enemy_Const(index), player, 400)) {

		//������ �ִ� ��� �������ش�.
		if (map_d.Get_Enemy(index).Get_Status() == Enemy_Status::E_Stop) {
			map_d.Get_Enemy(index).Set_Ani_Count(0);
			map_d.Get_Enemy(index).Set_Status(Enemy_Status::E_Move);
		}

		//���� ���ʿ� ���� ���
		if (map_d.Get_Enemy_Const(index).Get_XPos() + map_d.Get_Enemy_Const(index).Get_Crash_Width() <= player.Get_XPos()) {
			if (map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height() <= player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height())
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::DownRight);
			else if (map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height() - map_d.Get_Enemy_Const(index).Get_Crash_Height() >= player.Get_YPos() + player.Get_Height())
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::UpRight);
			else
				map_d.Get_Enemy(index).Set_Direction(Object_Direction::Right);
		}
		//���� �����ʿ� ���� ���
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
		//�÷��̾� ��ó�� ���� ���� ����� ������
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

	//�����̴� ���� ���
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

void Attack_Base_Enemy(Map_Dungeon& map_d, Player& player, const int& index) {
	if (map_d.Get_Enemy_Const(index).Get_Attack_Delay() == 0) {
		if (map_d.Get_Enemy_Const(index).Get_Status() == Enemy_Status::E_Stop || map_d.Get_Enemy_Const(index).Get_Status() == Enemy_Status::E_Move)
			Attack_Select(map_d.Get_Enemy(index), player);
		else
			Attack_Enemy_Action(map_d.Get_Enemy(index));

	}
}

void Attack_Select(Enemy& enemy, Player& player) {
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

void Attack_Enemy_End(Enemy& enemy, const int& attack_delay) {
	Attack_End(enemy);
	enemy.Set_Attack_Delay(attack_delay);
}

void Skill_Enemy_End(Enemy& enemy, const int& index, const int& attack_delay) {
	Attack_Enemy_End(enemy, attack_delay);
	enemy.Get_Enemy_Skill().Set_Current_Delay(index, enemy.Get_Enemy_Skill_Const().Get_Skill_Delay(index));
}

//���� ������ ������ �����ϴ� �Լ�
void CalCul_Enemy_Hitting_Point(Move_Object& attack_obj, Player& player, const int& e_index) {
	
	//���� ����Ʈ ���� ���
	for (int index = 0; index < 20; index++) {
		if (&attack_obj.Get_Hit_Range_P_Const(index) != NULL) {
			if (!attack_obj.Get_Hit_Range_P_Const(index).Is_Move() && attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() == 0) {
				Polygon_Damage_Enemy(attack_obj, player, attack_obj.Get_Hit_Range_P_Const(index), attack_obj.Get_Object_Info_Const().Get_Attack() * attack_obj.Get_Hit_Range_P_Const(index).Get_Attack_Multiple());
				attack_obj.Delete_Hit_Range_Polygon(index);
			}
			else if (attack_obj.Get_Hit_Range_P_Const(index).Is_Move()) {
				if (Polygon_Damage_Enemy(attack_obj, player, attack_obj.Get_Hit_Range_P_Const(index), attack_obj.Get_Object_Info_Const().Get_Attack() * attack_obj.Get_Hit_Range_P_Const(index).Get_Attack_Multiple())
					|| attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() == 0)
					attack_obj.Delete_Hit_Range_Polygon(index);
				//�÷��̾�� �ε����� �ʾҰ� ���� �����̵� �ð��� ������ �������ݴϴ�.
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