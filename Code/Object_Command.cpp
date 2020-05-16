#include <Windows.h>
#include "Object_Command.h"
#include "Hitting_Range.h"

void Attack_Player(Warrior& warrior) {
	
	bool attack = (GetAsyncKeyState(VK_LCONTROL) & 0x8000);

	if (warrior.Get_Status() != Player_Status::Attack) {
		if (attack) {
			warrior.Set_Status(Player_Status::Attack);
			warrior.Set_Ani_Count(0);
		}
	}
	else {
		//공격의 Hitting_Point지점
		if (warrior.Get_Ani_Count() == 9) {
			for (int index = 0; index < 20; index++) {
				if (&warrior.Get_Hit_Range_Const(index) == NULL) {
					break;
				}
			}
		}

		if (warrior.Get_Ani_Count() == 20) {
			warrior.Set_Status(Player_Status::Stop);
			warrior.Set_Ani_Count(0);
		}
	}
	
}