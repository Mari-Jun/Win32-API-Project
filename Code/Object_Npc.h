#pragma once
#include "Object_Main.h"

class Player;

enum Npc_Name {
	Elder
};

class Non_Move_Npc : public Non_Move_Object {
public:
	const bool& Is_Quest_Exist() const;
	const bool& Is_Interaction() const;

	void Set_Quest_Exist(const bool& quest_exist);
	void Set_Interaction(const bool& interaction);

private:
	bool quest_exist;
	bool interaction;
};

void Reset_Non_Move_Npc(Non_Move_Npc& nm_npc, const int& x_pos, const int& y_pos, HBITMAP bitmap);


