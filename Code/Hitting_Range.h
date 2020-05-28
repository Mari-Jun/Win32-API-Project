#pragma once
#include <Windows.h>

class Hitting_Range {
public:
	virtual ~Hitting_Range();

	const int& Get_Owner() const;
	const int& Get_Delay() const;
	const double& Get_Attack_Multiple() const;
	const bool& Is_Move() const;
	const POINT& Get_Speed() const;

	void Set_Owner(const int& owner);
	void Set_Delay(const int& delay);
	void Set_Attack_Multiple(const double& attack_multiple);
	void Set_Move(const bool& move);
	void Set_Speed(const POINT& speed);

private:
	int owner;
	int delay;
	double attack_multiple;
	bool move;
	POINT speed;
};

void Reset_Hitting_Range(Hitting_Range& hit_range, const int& owner, const bool& move, const POINT& speed);
const POINT Create_Speed(const int& direction, const int& speed);

class Hitting_Range_Polygon : public Hitting_Range {
public:
	virtual ~Hitting_Range_Polygon();

	const POINT Get_Pos(const int& index) const;

	void Set_Pos(const POINT p[4]);
	void Set_Pos_One(const POINT& pos, const int& index);

private:
	POINT pos[4];
};

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const bool& move, const POINT& speed, const POINT pos[4], const int& delay, const double& attack_multiple);
void Move_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p);
