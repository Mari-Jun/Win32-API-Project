#include <Windows.h>
#include <math.h>
#include "Hitting_Range.h"


const int& Hitting_Range::Get_Owner() const {
	return owner;
}

void Hitting_Range::Set_Owner(const int& owner) {
	this->owner = owner;
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

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const POINT pos[4]) {
	hit_range_p.Set_Pos(pos);
	Reset_Hitting_Range(hit_range_p, onwer);
}