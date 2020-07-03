#include <Windows.h>
#include "Source.h"
#include "Object_Command.h"
#include "Object_Player_Command.h"
#include "Hitting_Range.h"
#include "Object_Info.h"
#include "Object_Player.h"
#include "Object_Enemy.h"
#include "Object_Skill.h"
#include "Map_Village.h"
#include "Map_Dungeon.h"
#include "Game_Progress.h"
#include "Sound.h"

template <>
bool Command_Player(Player& player, Map_Dungeon& map_d, Progress& progress) {
	if (player.Get_Status() == Player_Status::Interaction || player.Get_Status() == Player_Status::Inventory || player.Get_Status() == Player_Status::Shopping ||
		player.Get_Status() == Player_Status::Map_Selecting)
		return false;

	player.Set_Ani_Count(player.Get_Ani_Count() + 1);
	if (player.Get_Ani_Count() == 800)
		player.Set_Ani_Count(0);

	if (player.Get_Object_Info_Const().Get_Hp() < 0 && player.Get_Status() != Player_Status::Die) {
		player.Set_Ani_Count(0);
		player.Set_Status(Player_Status::Die);
	}

	if (player.Get_Status() == Player_Status::Die) {
		if (player.Get_Ani_Count() == 16) {
			player.Get_Object_Info().Set_Hp(1);
			player.Set_Hitting_Damage_Count(-1);
			return true;
		}
		return false;
	}

	if (player.Get_Status() != Player_Status::SkillQ && player.Get_Status() != Player_Status::SkillW &&
		player.Get_Status() != Player_Status::SkillE && player.Get_Status() != Player_Status::SkillR)
		Attack_Player(player, map_d);

	Skill_Player(player, map_d);

	CalCul_Player_Hitting_Point(player, map_d);
	
	Move_Player(player, map_d, progress);

	Hit_Player(player);

	return false;
}

void Move_Player_Check(Move_Object& player, const Map_Village& map_v, Progress& progress, const int& move_x, const int& move_y) {
	if (Crash_Check_Map(player, map_v, move_x, move_y))
		return;

	//맵 오브젝트와의 충돌
	for (int index = 0; index < 60; index++) {
		if (&map_v.Get_NM_Object_Const(index) != NULL && Crash_Check_Object(player, map_v.Get_NM_Object_Const(index), move_x, move_y))
			return;
	}

	//맵 포탈과의 충돌
	if (&map_v.Get_Portal_Const() != NULL && Crash_Check_Object(player, map_v.Get_Portal_Const(), move_x, move_y)) {
		//포탈과 충돌 했을 경우 던전 선택을 해야합니다.
		//퀘스트 안받았을 경우는 포탈 못탑니다. 일단 주석처리 해놓겠습니다. 나중에 주석 풀어주세요.
		if (progress.Get_Quest_Num() != Quest_Name::No_Quest) {
			progress.Set_Map_Select(true);
			player.Set_Status(Player_Status::Map_Selecting);
		}
		return;
	}

	//맵 Npc와의 충돌
	if (Crash_Check_Npc(player, map_v, move_x, move_y))
		return;

	player.Set_XPos(player.Get_XPos() + move_x);
	player.Set_YPos(player.Get_YPos() + move_y);
}

void Move_Player_Check(Move_Object& player, const Map_Dungeon& map_d, Progress& progress, const int& move_x, const int& move_y) {
	if (Crash_Check_Map(player, map_d, move_x, move_y))
		return;

	//맵 오브젝트와의 충돌
	for (int index = 0; index < 60; index++) {
		if (&map_d.Get_NM_Object_Const(index) != NULL && Crash_Check_Object(player, map_d.Get_NM_Object_Const(index), move_x, move_y))
			return;
	}

	//적과의 충돌
	if (Crash_Check_Enemy(player, map_d, move_x, move_y))
		return;

	player.Set_XPos(player.Get_XPos() + move_x);
	player.Set_YPos(player.Get_YPos() + move_y);	
}


void Attack_Player(Player& player, Map_Dungeon& map_d) {
	bool attack = (GetAsyncKeyState(VK_LCONTROL) & 0x8000);

	if (player.Get_Status() != Player_Status::Attack) {
		if (attack) {
			player.Set_Status(Player_Status::Attack);
			player.Set_Ani_Count(0);
		}
	}
	else {
		//공격의 Hitting_Point지점을 생성해줍니다.
		if (player.Get_Ani_Count() == 6) {
			Create_Hitting_Point(player, 80, 50, Hitting_Shape::FRONT, Hit_Owner::HO_Player, false, 0, player.Get_Class_Type(), player.Get_Status() - Player_Status::Attack, 2, 1.0);
			player.Get_Player_Sound().Play_Sound(Player_Sound::Attack_Sound);
		}
		//공격 모션의 끝
		if (player.Get_Ani_Count() == 20)
			Attack_End(player);
	}
}

//히팅 범위를 적에게 적용하는 함수
void CalCul_Player_Hitting_Point(Move_Object& attack_obj, Map_Dungeon& map_d) {
	//히팅 포인트 지점 계산
	for (int index = 0; index < 20; index++) {
		if (&attack_obj.Get_Hit_Range_P_Const(index) != NULL) {
			if (!attack_obj.Get_Hit_Range_P_Const(index).Is_Move() && attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() == 0) {
				for (int e_index = 0; e_index < 53; e_index++)
					if (&map_d.Get_Enemy_Const(e_index) != NULL)
						Polygon_Damage_Enemy(attack_obj, map_d.Get_Enemy(e_index), attack_obj.Get_Hit_Range_P_Const(index), attack_obj.Get_Object_Info_Const().Get_Attack() * attack_obj.Get_Hit_Range_P_Const(index).Get_Attack_Multiple());
				//폴리곤 제거
				attack_obj.Delete_Hit_Range_Polygon(index);
			}
			else if (attack_obj.Get_Hit_Range_P_Const(index).Is_Move()) {
				bool destory = false;
				for (int e_index = 0; e_index < 53; e_index++) {
					if (&map_d.Get_Enemy_Const(e_index) != NULL) {
						if (Polygon_Damage_Enemy(attack_obj, map_d.Get_Enemy(e_index), attack_obj.Get_Hit_Range_P_Const(index), attack_obj.Get_Object_Info_Const().Get_Attack() * attack_obj.Get_Hit_Range_P_Const(index).Get_Attack_Multiple()))
							destory = true;
					}
				}
				if (destory || attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() == 0)
					attack_obj.Delete_Hit_Range_Polygon(index);
				else
					Move_Hitting_Range_Polygon(attack_obj.Get_Hit_Range_P(index));
			}
			if (&attack_obj.Get_Hit_Range_P_Const(index) != NULL)
				attack_obj.Get_Hit_Range_P(index).Set_Delay(attack_obj.Get_Hit_Range_P_Const(index).Get_Delay() - 1);

		}
	}
}

void Skill_Player(Player& player, Map_Dungeon& map_d) {
	//스킬 쿨다운 감소
	for (int index = Skill_Type::Skill_Q; index <= Skill_Type::Skill_R; index++)
		if (player.Get_Player_Skill_Const().Get_Current_Delay(index) > 0)
			player.Get_Player_Skill().Set_Current_Delay(index, player.Get_Player_Skill_Const().Get_Current_Delay(index) - 1);

	switch (player.Get_Class_Type())
	{
	case Class_Type::Warrior:
		switch (player.Get_Status())
		{
		case Player_Status::SkillQ:
			if (player.Get_Ani_Count() == 14 || player.Get_Ani_Count() == 20 || player.Get_Ani_Count() == 26) {
				Create_Hitting_Point(player, 70, 70, Hitting_Shape::ROUND, Hit_Owner::HO_Player, false, 0, player.Get_Class_Type(), player.Get_Status() - Player_Status::Attack, 0, 0.5);
				if(player.Get_Ani_Count()==14)
					player.Get_Player_Sound().Play_Sound(Player_Sound::SkillQ_Sound);
			}	
			if (player.Get_Ani_Count() == 36) 
				Attack_End(player);
			break;
		case Player_Status::SkillW:
			if (player.Get_Ani_Count() == 8) {
				Create_Hitting_Point(player, 130, 30, Hitting_Shape::FRONT, Hit_Owner::HO_Player, false, 0, player.Get_Class_Type(), player.Get_Status() - Player_Status::Attack, 4, 1.6);
				player.Get_Player_Sound().Play_Sound(Player_Sound::SkillW_Sound);
			}
			if (player.Get_Ani_Count() == 20)
				Attack_End(player);
			break;
		case Player_Status::SkillE:
			if (player.Get_Ani_Count() == 12 || player.Get_Ani_Count() == 22) {
				Create_Hitting_Point(player, 110, 50, Hitting_Shape::FRONT, Hit_Owner::HO_Player, false, 0, player.Get_Class_Type(), player.Get_Status() - Player_Status::Attack, 1, 1.2);
				if (player.Get_Ani_Count() == 12)
					player.Get_Player_Sound().Play_Sound(Player_Sound::SkillE_Sound);
			}
			if (player.Get_Ani_Count() == 34)
				Attack_End(player);
			break;
		case Player_Status::SkillR:
			if (player.Get_Ani_Count() == 8) {
				Create_Hitting_Point(player, 70, 35, Hitting_Shape::FRONT, Hit_Owner::HO_Player, false, 0, player.Get_Class_Type(), player.Get_Status() - Player_Status::Attack, 3, 2.0);
				player.Get_Player_Sound().Play_Sound(Player_Sound::SkillR_Sound);
			}
			if (player.Get_Ani_Count() == 26)
				Attack_End(player);
			break;
		default:
			break;
		}
		break;
	default:
		break;
	}
}

void Hit_Player(Player& player) {
	Count_Up_Hitting_Damage_Count(player);
}