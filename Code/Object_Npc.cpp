#include <Windows.h>
#include "Object_Npc.h"

const bool& Non_Move_Npc::Is_Quest_Exist() const {
	return quest_exist;
}

const bool& Non_Move_Npc::Is_Interaction() const {
	return interaction;
}

void Non_Move_Npc::Set_Quest_Exist(const bool& quest_exist) {
	this->quest_exist = quest_exist;
}

void Non_Move_Npc::Set_Interaction(const bool& interaction) {
	this->interaction = interaction;
}

void Reset_Non_Move_Npc(Non_Move_Npc& nm_npc, const int& x_pos, const int& y_pos, HBITMAP bitmap) {
	Reset_Non_Move_Object(nm_npc, x_pos, y_pos, bitmap);
	nm_npc.Set_Quest_Exist(false);
	nm_npc.Set_Interaction(false);
}