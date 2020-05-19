#pragma once
#include <Windows.h>

class Move_Object;
class Non_Move_Npc;
class Map_Village;

class Interaction_Box {
public:
	~Interaction_Box();
	const RECT Get_Messsage_Box_Rect() const;
	const HBITMAP Get_Message_Box() const;
	const BITMAP Get_Message_Box_Size() const;
	const HFONT Get_Message_Box_Font(const int& index) const;
	const BLENDFUNCTION Get_Message_Box_Alpha() const;

	void Set_Message_Box(RECT c_rect);

private:
	RECT mb_rect;
	HBITMAP message_box;
	BITMAP message_box_size;
	HFONT message_box_font[2];
	BLENDFUNCTION message_box_alpha;
};

void Reset_Interaction_Box(Interaction_Box& it_box, RECT c_rect);
bool Paint_Interaction_Box(HDC hdc, HDC alphadc, HDC bitdc, RECT c_rect, Move_Object& player, Interaction_Box& it_box);

template <typename T_Map>
void Interaction_Command(Move_Object& player, T_Map& map, Interaction_Box& it_box) {

}

template<>
void Interaction_Command(Move_Object& player, Map_Village& map_v, Interaction_Box& it_box);

bool Interaction_Range_Player_To_Npc(Move_Object& player, const Non_Move_Npc& nm_npc);

template <typename T_Map>
void Show_Npc_Interaction(HDC hdc, T_Map& map, Interaction_Box& it_box) {

}

template<>
void Show_Npc_Interaction(HDC hdc, Map_Village& map_v, Interaction_Box& it_box);

void Show_Npc_Elder_Interaction(HDC hdc, Interaction_Box& it_box);