#pragma once
#include "Object_Main.h"

enum Npc_Name {
	ELDER, WEAPON_SHOP, ITEM_SHOP, LEGEND, SOLDIER
};

class Npc : public Object {
public:
	~Npc();

	const int& Get_Npc_Type() const;
	const HBITMAP Get_Stop_Motion_Bitmap(const int& index) const;
	const BITMAP Get_Stop_Size() const;
	const bool& Is_Quest_Exist() const;
	const bool& Is_Interaction() const;
	const int& Get_Interaction_Count() const;
	const int& Get_Ani_Count() const;


	void Set_Npc_Type(const int& npc_type);
	void Set_Bitmap();
	void Set_Quest_Exist(const bool& quest_exist);
	void Set_Interaction(const bool& interaction);
	void Set_interaction_Count(const int& inter_count);
	void Set_Ani_Count(const int& ani_count);


private:
	int npc_type;
	HBITMAP stop_motion_bitmap[10];
	BITMAP stop_motion_size;
	bool quest_exist;
	bool interaction;
	int interaction_count;
	int ani_count;
};

void Reset_Npc(Npc& npc, const int& npc_type, const int& x_pos, const int& y_pos);
void Paint_Npc(HDC hdc, HDC bitdc, const Npc& npc);


