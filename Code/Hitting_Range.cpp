#include <Windows.h>
#include <math.h>
#include "Hitting_Range.h"


const int& Hitting_Range::Get_Owner() const {
	return owner;
}

const int& Hitting_Range::Get_Delay() const {
	return delay;
}

const double& Hitting_Range::Get_Attack_Multiple() const {
	return attack_multiple;
}

void Hitting_Range::Set_Owner(const int& owner) {
	this->owner = owner;
}

void Hitting_Range::Set_Delay(const int& delay) {
	this->delay = delay;
}

void Hitting_Range::Set_Attack_Multiple(const double& attack_multiple) {
	this->attack_multiple = attack_multiple;
}

void Reset_Hitting_Range(Hitting_Range& hit_range, const int& owner) {
	hit_range.Set_Owner(owner);
}

const POINT Hitting_Range_Polygon::Get_Pos(const int& index) const {
	return pos[index];
}


void Hitting_Range_Polygon::Set_Pos(const POINT p[4]) {
	for (int index = 0; index < 4; index++)
		pos[index] = p[index];
}

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const POINT pos[4], const int& delay, const double& attack_multiple) {
	hit_range_p.Set_Pos(pos);
	hit_range_p.Set_Delay(delay);
	hit_range_p.Set_Attack_Multiple(attack_multiple);
	Reset_Hitting_Range(hit_range_p, onwer);
}