#include "Source.h"
#include "Object_Enemy.h"
#include "Object_Enemy_Attack_Info.h"
#include "Object_Command.h"
#include "Object_Enemy_Command.h"

void Attack_Enemy_Action(Enemy& enemy) {
	switch (enemy.Get_Enemy_Type())
	{
	case Enemy_Type::Bird:
		switch (enemy.Get_Status())
		{
		case Enemy_Status::E_Attack:
			//������ Hitting_Point������ �������ݴϴ�.
			if (enemy.Get_Ani_Count() == 4)
				//�׳� ������ Delay�� �ߵ� �ð��Դϴ�. ex(8 : 8�ڿ� Hit)
				Create_Hitting_Point(enemy, 50, 25, Hitting_Shape::FRONT, Hit_Owner::HO_Enemy, false, 0, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, 8, 1.0);
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
			//������ Hitting_Point������ �������ݴϴ�.
			if (enemy.Get_Ani_Count() == 8)
				//����ü�� Delay�� ���ӽð��Դϴ�. ex(20 : 20���� ����)
				Create_Hitting_Point(enemy, 40, 20, Hitting_Shape::FRONT, Hit_Owner::HO_Enemy, true, 15, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, 20, 1.0);
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
				Create_Hitting_Point(enemy, 100, 50, Hitting_Shape::FRONT, Hit_Owner::HO_Enemy, false, 0, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, 6, 1.0);
			else if (enemy.Get_Ani_Count() == 16)
				Attack_Enemy_End(enemy, 64);
			break;
		case Enemy_Status::E_SkillQ:
			if (enemy.Get_Ani_Count() == 2)
				Create_Hitting_Point(enemy, 60, 30, Hitting_Shape::FRONT, Hit_Owner::HO_Enemy, true, 10, enemy.Get_Enemy_Type(), enemy.Get_Status() - Enemy_Status::E_Attack, 20, 1.0);
			else if (enemy.Get_Ani_Count() == 16)
				Skill_Enemy_End(enemy, 0, 64);
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