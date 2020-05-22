#pragma once
#include <windows.h>

static const double PIE = 3.141592;

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
	Co_Interaction = 'f', Co_Equipment = 'c'
};

enum Hit_Onwer {
	HO_Player, HO_Enemy
};

enum Object_Direction {
	Right, UpRight, Up, UpLeft, Left, DownLeft, Down, DownRight
};

enum Player_Status {
	Stop, Move, Run, Interaction, Attack, Inventory, Shopping
};

enum Class_Type {
	Warrior,
};

enum Enemy_Type {
	E_Pratice
};

enum Player_Item_Type {
	Hp_Potion = 1, Mp_Potion, Panacea
};

enum Shop_Type {
	Equipment_Type, Accessory_Type
};

enum Dialog_Type {
	Shop_Type, Quest_Type, No_Money_Type
};

enum Timer_Name {
	Default_Timer
};
