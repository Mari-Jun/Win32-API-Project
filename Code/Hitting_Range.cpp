#include <Windows.h>
#include <math.h>
#include "Source.h"
#include "Hitting_Range.h"

Hitting_Range::~Hitting_Range() {}

const int& Hitting_Range::Get_Owner() const {
	return owner;
}

const int& Hitting_Range::Get_Delay() const {
	return delay;
}

const double& Hitting_Range::Get_Attack_Multiple() const {
	return attack_multiple;
}

const bool& Hitting_Range::Is_Move() const {
	return move;
}

const POINT& Hitting_Range::Get_Speed() const {
	return speed;
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

void Hitting_Range::Set_Move(const bool& move) {
	this->move = move;
}

void Hitting_Range::Set_Speed(const POINT& speed) {
	this->speed = speed;
}

void Reset_Hitting_Range(Hitting_Range& hit_range, const int& owner, const bool& move, const POINT& speed) {
	hit_range.Set_Owner(owner);
	hit_range.Set_Move(move);
	hit_range.Set_Speed(speed);
}

const POINT Create_Speed(const int& direction, const int& speed) {
	switch (direction)
	{
	case Object_Direction::Right:
		return { speed,0 };
	case Object_Direction::UpRight:
		return { static_cast<LONG>(speed / sqrt(2) + 0.5),-static_cast<LONG>(speed / sqrt(2) + 0.5) };
	case Object_Direction::Up:
		return { 0,-speed };
	case Object_Direction::UpLeft:
		return { -static_cast<LONG>(speed / sqrt(2) + 0.5),-static_cast<LONG>(speed / sqrt(2) + 0.5) };
	case Object_Direction::Left:
		return { -speed,0 };
	case Object_Direction::DownLeft:
		return { -static_cast<LONG>(speed / sqrt(2) + 0.5), static_cast<LONG>(speed / sqrt(2) + 0.5) };
	case Object_Direction::Down:
		return { 0,speed };
	case Object_Direction::DownRight:
		return { static_cast<LONG>(speed / sqrt(2) + 0.5), static_cast<LONG>(speed / sqrt(2) + 0.5) };
	default:
		break;
	}
}

Hitting_Range_Polygon::~Hitting_Range_Polygon() {}

const POINT Hitting_Range_Polygon::Get_Pos(const int& index) const {
	return pos[index];
}

void Hitting_Range_Polygon::Set_Pos(const POINT p[4]) {
	for (int index = 0; index < 4; index++)
		pos[index] = p[index];
}

void Hitting_Range_Polygon::Set_Pos_One(const POINT& pos, const int& index) {
	this->pos[index] = pos;
}

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const bool& move, const POINT& speed, const POINT pos[4], const int& delay, const double& attack_multiple) {
	hit_range_p.Set_Pos(pos);
	hit_range_p.Set_Delay(delay);
	hit_range_p.Set_Attack_Multiple(attack_multiple);
	Reset_Hitting_Range(hit_range_p, onwer, move, speed);
}

void Move_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p) {
	if (hit_range_p.Is_Move()) {
		for (int index = 0; index < 4; index++) {
			hit_range_p.Set_Pos_One({ hit_range_p.Get_Pos(index).x + hit_range_p.Get_Speed().x ,hit_range_p.Get_Pos(index).y + hit_range_p.Get_Speed().y }, index);
		}
	}
}