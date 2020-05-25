#pragma once
#include <Windows.h>


class Hitting_Range {
public:
	const int& Get_Owner() const;
	void Set_Owner(const int& owner);
private:
	int owner;
};

void Reset_Hitting_Range(Hitting_Range& hit_range, const int& owner);

class Hitting_Range_Polygon : public Hitting_Range {
public:
	const POINT Get_Pos(const int& index) const;
	const int& Get_Delay() const;

	void Set_Pos(const POINT p[4]);
	void Set_Delay(const int& delay);
private:
	POINT pos[4];
	int delay;
};

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const POINT pos[4], const int& delay);

class Hitting_Range_Circle : public Hitting_Range {

};

