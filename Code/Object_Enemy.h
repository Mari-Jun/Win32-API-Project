#pragma once
#include "Object_Main.h"

class Practice_Enemy : public Move_Object {
public:
	~Practice_Enemy();

	const BITMAP Get_Bitmap_Size() const;
	const HBITMAP Get_Stop_Motion_Bitmap(const int& index) const;

	void Set_Stop_Motion();
		
private:
	BITMAP bitmap_size;
	HBITMAP stop_motion_bitmap[4];
};

void Reset_Practice_Enemy(Practice_Enemy& p_enemy);
void Paint_Practice_Enemy(HDC hdc, HDC bitdc, const Practice_Enemy& p_enemy);