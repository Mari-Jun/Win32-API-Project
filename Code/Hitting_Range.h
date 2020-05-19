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

	void Set_Pos(const POINT p[4]);
private:
	POINT pos[4];
};

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const POINT pos[4]);

class Hitting_Range_Circle : public Hitting_Range {

};

