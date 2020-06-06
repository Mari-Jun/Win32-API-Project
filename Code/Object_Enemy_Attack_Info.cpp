#include "Source.h"
#include "Object_Player.h"
#include "Object_Info.h"
#include "Object_Enemy.h"
#include "Object_Enemy_Attack_Info.h"
#include "Object_Command.h"
#include "Object_Enemy_Command.h"
#include "File.h"
#include <iostream>

void Attack_Enemy_Action(Enemy& enemy, const Player& player, const File& file) {
	switch (enemy.Get_Enemy_Type())
	{
	case Enemy_Type::Bird:
	case Enemy_Type::Tolpi:
	case Enemy_Type::Heke:
	case Enemy_Type::Baocar:
	case Enemy_Type::Riff:
	case Enemy_Type::Selnarg:
	case Enemy_Type::Zarue:
	case Enemy_Type::Normous:
	case Enemy_Type::Venueba:
		if (enemy.Get_Ani_Count() == file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, Attack_Info::Attack_Hit_Delay))
			Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
		break;
	case Enemy_Type::Zadrom:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			//공격의 Hitting_Point지점을 생성해줍니다.
			if (enemy.Get_Ani_Count() == 8)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			break;
		}
		break;
	case Enemy_Type::Dark_Flower:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			if (enemy.Get_Ani_Count() == file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, Attack_Info::Attack_Hit_Delay))
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			break;
		case Enemy_Status::E_SkillQ:
			if (enemy.Get_Ani_Count() == 8)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			break;
		case Enemy_Status::E_SkillW:
			if (enemy.Get_Ani_Count() == 22 || enemy.Get_Ani_Count() == 28 || enemy.Get_Ani_Count() == 34) 
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			break;
		}
	case Enemy_Type::Huba:
	case Enemy_Type::Huba2:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			if (enemy.Get_Ani_Count() == 1 || enemy.Get_Ani_Count() == 6 || enemy.Get_Ani_Count() == 11 || enemy.Get_Ani_Count() == 16)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			break;
		}
	case Enemy_Type::Grave:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			if (enemy.Get_Ani_Count() == file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, Attack_Info::Attack_Hit_Delay))
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			break;
		case Enemy_Status::E_SkillQ:
			if (enemy.Get_Ani_Count() == 1)
				enemy.Get_Object_Info().Set_Defence(enemy.Get_Object_Info().Get_Defence() + 100);
			else if (enemy.Get_Ani_Count() == 15)
				enemy.Get_Object_Info().Set_Defence(enemy.Get_Object_Info().Get_Defence() - 100);
			break;
		}
		break;
	case Enemy_Type::Sama:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			if (enemy.Get_Ani_Count() == file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, Attack_Info::Attack_Hit_Delay))
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			break;
		case Enemy_Status::E_SkillQ:
			if (enemy.Get_Ani_Count() == 5) {
				enemy.Set_Speed(enemy.Get_Speed() * 2);
			}		
			else if (enemy.Get_Ani_Count() == file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, Attack_Info::Attack_Hit_Delay)) {
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
				enemy.Set_Speed(enemy.Get_Speed() / 2);
			}
			break;
		}
		break;
	case Enemy_Type::Mobre:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			if (enemy.Get_Ani_Count() == 8 || enemy.Get_Ani_Count() == 20)
				Create_Hitting_Point(enemy, player, file, Hit_Owner::HO_Enemy, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack);
			break;
		}
		break;
	}

	switch (enemy.Get_Status())
	{
	case Enemy_Status::E_Attack:
		if (enemy.Get_Ani_Count() == file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), enemy.Get_Status()) * 2)
			Attack_Enemy_End(enemy, file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), 0, Attack_Info::Attack_Delay));
		break;
	case Enemy_Status::E_SkillQ:
	case Enemy_Status::E_SkillW:
	case Enemy_Status::E_SkillE:
	case Enemy_Status::E_SkillR:
		if (enemy.Get_Ani_Count() == file.Get_Enemy_Motion_Count(enemy.Get_Enemy_Type(), enemy.Get_Status()) * 2) 
			Skill_Enemy_End(enemy, enemy.Get_Status() - Enemy_Status::E_SkillQ, file.Get_Enemy_Attack_Info(enemy.Get_Enemy_Type(), 0, Attack_Info::Attack_Delay));
		break;
	default:
		break;
	}
}