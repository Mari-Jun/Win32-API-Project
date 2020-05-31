#pragma once
#include <Windows.h>

class Hitting_Range {
public:
	virtual ~Hitting_Range();

	const int& Get_Owner() const;
	const int& Get_Delay() const;
	const double& Get_Attack_Multiple() const;
	const bool& Is_Move() const;
	const int& Get_Direction() const;
	const bool& Is_Guide() const;
	const POINT& Get_Speed() const;
	const BITMAP& Get_Range_Bitmap_Size() const;
	const HBITMAP& Get_Range_Bitmap(const int& direction) const;

	void Set_Owner(const int& owner);
	void Set_Delay(const int& delay);
	void Set_Attack_Multiple(const double& attack_multiple);
	void Set_Move(const bool& move);
	void Set_Direction(const int& direction);
	void Set_Guide(const bool& guide);
	void Set_Speed(const POINT& speed);
	void Set_Range_Bitmap(const int& owner, const int& type, const int& attack_type);

private:
	int owner;
	int delay;
	double attack_multiple;
	bool move;
	int direction;
	bool guide;
	POINT speed;
	BITMAP range_bitmap_size;
	HBITMAP range_bitmap[8];
};

void Reset_Hitting_Range(Hitting_Range& hit_range, const int& owner, const bool& move, const int& direction, const bool& guide, const POINT& speed, const int& type, const int& attack_type);
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

void Reset_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p, const int& onwer, const bool& move, const int& direction, const bool& guide, const POINT& speed, const int& type, const int& attack_type, const POINT pos[4], const int& delay, const double& attack_multiple);
void Move_Hitting_Range_Polygon(Hitting_Range_Polygon& hit_range_p);
void Paint_Hitting_Range(HDC hdc, HDC bitdc, const Hitting_Range_Polygon& hit_range_p);
