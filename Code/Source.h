#pragma once
#include <windows.h>

template <typename T>
T* Create_Class() {
	T* t = new T();

	return t;
}

template<typename T>
void Delete_Class(T** t) {
	if (*t != NULL) {
		delete* t;
		*t = NULL;
	}
}

enum Player_Select {
	Class_Warrior
};

enum Map_Select {
	Village1
};

enum Command_Key {
	Co_Interaction = 'f'
};

enum Hit_Onwer {
	HO_Player, HO_Enemy
};

enum Object_Direction {
	Right, UpRight, Up, UpLeft, Left, DownLeft, Down, DownRight
};

enum Player_Status {
	Stop, Move, Run, Interaction, Attack
};

enum Enemy_Type {
	E_Pratice
};

enum Timer_Name {
	Player_Move_Timer = 10, Player_Attack_Timer
};