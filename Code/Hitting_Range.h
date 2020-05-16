#pragma once
#include <Windows.h>

enum Hit_Onwer {
	HO_Player, HO_Enemy
};

class Hitting_Range {
public:
	const RECT Get_Hit_Rect() const;
	const int& Get_Owner() const;

	void Set_Hit_Rect(const RECT hit_rect);
	void Set_Owner(const int& owner);
private:
	RECT hit_rect;
	int owner;
};

void Reset_Hitting_Range(Hitting_Range& hit_range, const RECT hit_rect, const int& owner);