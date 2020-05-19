#include <windows.h>
#include "Object_Info.h"

/*디폴트(오브젝트) 인포메이션*/

const int& Object_Info::Get_Level() const {
	return level;
}

const int& Object_Info::Get_Hp() const {
	return hp;
}

const int& Object_Info::Get_Max_Hp() const {
	return max_hp;
}

const int& Object_Info::Get_Attack() const {
	return attack;
}

const int& Object_Info::Get_Defence() const {
	return defence;
}

const bool& Object_Info::Is_No_Damage() const {
	return no_damage;
}

void Object_Info::Set_Level(const int& level) {
	this->level = level;
}

void Object_Info::Set_Hp(const int& hp) {
	this->hp = hp;
}

void Object_Info::Set_Max_Hp(const int& max_hp) {
	this->max_hp = max_hp;
}

void Object_Info::Set_Attack(const int& attack) {
	this->attack = attack;
}

void Object_Info::Set_Defence(const int& defence) {
	this->defence = defence;
}

void Object_Info::Set_No_Damage(const bool& damage) {
	no_damage = damage;
}

void Reset_Object_Info(Object_Info& o_info, const int& level, const int& hp, const int& attack, const int& defence) {
	o_info.Set_Level(level);
	o_info.Set_Hp(hp);
	o_info.Set_Max_Hp(hp);
	o_info.Set_Attack(attack);
	o_info.Set_Defence(defence);
	o_info.Set_No_Damage(false);
}

