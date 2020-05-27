#pragma once
#include <Windows.h>

class Hitting_Range {
public:
	virtual ~Hitting_Range();

	const int& Get_Owner() const;
	const int& Get_Delay() const;
	const double& Get_Attack_Multiple() const;

	void Set_Owner(const int& owner);
	void Set_Delay(const int& delay);
	void Set_Attack_Multiple(const double& attack_multiple);
private:
	int owner;
	int delay;
	double attack_multiple;
};

void Reset_Hitting_Range(Hitting_Range& hit_range, const int& owner);

class Hitting_Range_Polygon : public Hitting_Range {
public:
	virtual ~Hitting_Range_Polygon();

	const POINT Get_Pos(const int& index) const;

	void Set_Pos(const POINT p[4]);

private:
	POINT pos[4];
};

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const POINT pos[4], const int& delay, const double& attack_multiple);

class Hitting_Range_Circle : public Hitting_Range {

};

