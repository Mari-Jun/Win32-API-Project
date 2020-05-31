#include "Source.h"
#include "Object_Player.h"
#include "Object_Enemy.h"
#include "Object_Enemy_Attack_Info.h"
#include "Object_Command.h"
#include "Object_Enemy_Command.h"
#include "File.h"

void Attack_Enemy_Action(Enemy& enemy, const Player& player, const File& file) {
	switch (enemy.Get_Enemy_Type())
	{
	case Enemy_Type::Bird:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			//공격의 Hitting_Point지점을 생성해줍니다.
			if (enemy.Get_Ani_Count() == 4)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			else if (enemy.Get_Ani_Count() == 16)
				Attack_Enemy_End(enemy, 48);
			break;
		default:
			break;
		}
		break;
	case Enemy_Type::Zadrom:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			//공격의 Hitting_Point지점을 생성해줍니다.
			if (enemy.Get_Ani_Count() == 8)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			else if (enemy.Get_Ani_Count() == 16)
				Attack_Enemy_End(enemy, 64);
			break;
		default:
			break;
		}
		break;
	case Enemy_Type::Tolpi:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			if (enemy.Get_Ani_Count() == 2)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			else if (enemy.Get_Ani_Count() == 16)
				Attack_Enemy_End(enemy, 64);
			break;
		case Enemy_Status::E_SkillQ:
			if (enemy.Get_Ani_Count() == 2)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			else if (enemy.Get_Ani_Count() == 16)
				Skill_Enemy_End(enemy, Skill_Type::Skill_Q, 64);
			break;
		default:
			break;
		}
		break;
	case Enemy_Type::Dark_Flower:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			if (enemy.Get_Ani_Count() == 1) {
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			}
			else if (enemy.Get_Ani_Count() == 16)
				Attack_Enemy_End(enemy, 128);
			break;
		case Enemy_Status::E_SkillQ:
			if (enemy.Get_Ani_Count() == 8)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			else if (enemy.Get_Ani_Count() == 16)
				Skill_Enemy_End(enemy, Skill_Type::Skill_Q, 128);
			break;
		case Enemy_Status::E_SkillW:
			if (enemy.Get_Ani_Count() == 22 || enemy.Get_Ani_Count() == 28 || enemy.Get_Ani_Count() == 34)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			else if (enemy.Get_Ani_Count() == 42)
				Skill_Enemy_End(enemy, Skill_Type::Skill_W, 128);
			break;
		default:
			break;
		}
	default:
		break;
	}

	/*
	switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			break;
		case Enemy_Status::E_SkillQ:
			break;
		case Enemy_Status::E_SkillW:
			break;
		case Enemy_Status::E_SkillE:
			break;
		case Enemy_Status::E_SkillR:
			break;
		default:
			break;
		}
		*/

}