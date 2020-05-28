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

enum Map_Type {
	Village1, Dungeon1, Dungeon2, Dungeon3, Dungeon4
};

enum Command_Key {
	Co_Interaction = 'f', Co_Equipment = 'c'
};

enum Hit_Owner {
	HO_Player, HO_Enemy
};

enum Object_Direction {
	Right, UpRight, Up, UpLeft, Left, DownLeft, Down, DownRight
};

enum Player_Status {
	Stop, Move, Run, Die, Attack, SkillQ, SkillW, SkillE, SkillR, Interaction, Inventory, Shopping, Map_Selecting
};

enum Enemy_Status {
	E_Stop, E_Move, E_Attack, E_SkillQ, E_SkillW, E_SkillE, E_SkillR
};

enum Class_Type {
	Warrior,
};

enum Enemy_Type {
	Bird, Zadrom, Tolpi
};

enum Skill_Type {
	Skill_Q, Skill_W, Skill_E, Skill_R
};

enum Player_Item_Type {
	Hp_Potion = 1, Mp_Potion, Panacea
};

enum Shop_Type {
	Equipment_Type, Accessory_Type
};

enum Dialog_Type {
	Shop_Type, Quest_Type, No_Money_Type, Heal_Type
};

enum Quest_Name {
	No_Quest, Main_Quest1, Main_Quest2, Main_Quest3, Main_Quest4, Main_Quest5,
	Main_Quest6, Main_Quest7, Main_Quest8
};

enum Timer_Name {
	Default_Timer
};

enum Hitting_Shape {
	FRONT, ROUND
};