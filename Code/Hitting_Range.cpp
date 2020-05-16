#include <Windows.h>
#include "Hitting_Range.h"

const RECT Hitting_Range::Get_Hit_Rect() const {
	return hit_rect;
}

const int& Hitting_Range::Get_Owner() const {
	return owner;
}

void Hitting_Range::Set_Hit_Rect(const RECT hit_rect) {
	this->hit_rect = hit_rect;
}

void Hitting_Range::Set_Owner(const int& owner) {
	this->owner = owner;
}

void Reset_Hitting_Range(Hitting_Range& hit_range, const RECT hit_rect, const int& owner) {
	hit_range.Set_Hit_Rect(hit_rect);
	hit_range.Set_Owner(owner);
}