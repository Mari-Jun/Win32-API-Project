#include <windows.h>
#include "Object_Info.h"


/*디폴트(오브젝트) 인포메이션*/

const int& Object_Info::Get_Hp() const {
	return hp;
}

const int& Object_Info::Get_Attack() const {
	return attack;
}

const int& Object_Info::Get_Defence() const {
	return defence;
}

const int& Object_Info::Get_Speed() const {
	return speed;
}

void Object_Info::Set_Hp(const int& hp) {
	this->hp = hp;
}

void Object_Info::Set_Attack(const int& attack) {
	this->attack = attack;
}

void Object_Info::Set_Defence(const int& defence) {
	this->defence = defence;
}

void Object_Info::Set_Speed(const int& speed) {
	this->speed = speed;
}

void Reset_Object_Info(Object_Info& o_info, const int& hp, const int& attack, const int& defence, const int& speed) {
	o_info.Set_Hp(hp);
	o_info.Set_Attack(attack);
	o_info.Set_Defence(defence);
	o_info.Set_Speed(speed);
}


/*플레이어 인포메이션*/

const int& Player_Info::Get_Level() const {
	return level;
}

const int& Player_Info::Get_Mp() const {
	return mp;
}

const bool& Player_Info::Is_No_Damage() const {
	return no_damage;
}

void Player_Info::Set_Level(const int& level) {
	this->level = level;
}

void Player_Info::Set_Mp(const int& mp) {
	this->mp = mp;
}

void Player_Info::Set_No_Damage(const bool& damage) {
	no_damage = damage;
}

void Reset_Player_Info(Player_Info& p_info, const int& hp, const int& mp, const int& attack, const int& defence, const int& speed) {
	Reset_Object_Info(p_info, hp, attack, defence, speed);
	p_info.Set_Level(1);
	p_info.Set_Mp(mp);
	p_info.Set_No_Damage(false);
}
