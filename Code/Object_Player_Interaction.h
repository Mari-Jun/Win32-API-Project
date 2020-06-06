#pragma once
#include <Windows.h>

class Player;
class Npc;
class Map_Village;
class Progress;
class Sound;
class File;

class Interaction_Box {
public:
	~Interaction_Box();
	const RECT& Get_Messsage_Box_Rect() const;
	RECT Get_Messsage_Box_Rect_Ori() const;
	const HBITMAP& Get_Message_Box() const;
	const BITMAP& Get_Message_Box_Size() const;
	const HFONT& Get_Message_Box_Font(const int& index) const;
	const BLENDFUNCTION& Get_Message_Box_Alpha() const;
	const RECT& Get_Dialog_Box_Rect() const;
	const HBITMAP& Get_Dialog_Box(const int& index) const;
	const BITMAP& Get_Dialog_Box_Size() const;
	const HBITMAP& Get_Dialog_Select() const;
	const BITMAP& Get_Dialog_Select_Size() const;
	const bool& Is_Select_Ok() const;
	const int& Get_Dialog_Status() const;

	void Set_Message_Box(RECT c_rect);
	void Set_Dialog_Box(RECT c_rect);
	void Set_Select_Ok(const bool& select_ok);
	void Set_Dialog_Status(const int& dialog_status);

private:
	RECT mb_rect;
	HBITMAP message_box;
	BITMAP message_box_size;
	HFONT message_box_font[2];
	BLENDFUNCTION message_box_alpha;
	RECT db_rect;
	HBITMAP dialog_box[2];
	BITMAP dialog_box_size;
	HBITMAP dialog_select;
	BITMAP dialog_select_size;
	bool select_ok;
	int dialog_status;
};

void Reset_Interaction_Box(Interaction_Box& it_box, RECT c_rect);
bool Paint_Interaction_Box(HDC hdc, HDC bit2dc, HDC bitdc, RECT c_rect, Player& player, Interaction_Box& it_box);


void Interaction_Command(Player& player, Map_Village& map_v, Interaction_Box& it_box, Progress& progress);
bool Interaction_Range_Player_To_Npc(Player& player, const Npc& npc);

void Show_Npc_Interaction(HDC hdc, HDC bitdc, const Player& player, const Map_Village& map_v, const Interaction_Box& it_box, Progress& progress, const File& file);
void Show_Npc_Elder_Interaction(HDC hdc, const Npc& elder, const Interaction_Box& it_box, Progress& progress, const File& file);
void Show_Npc_Equipment_Interaction(HDC hdc, const Npc& equip, const Interaction_Box& it_box, Progress& progress);
void Show_Npc_Weapon_Interaction(HDC hdc, const Npc& weapon, const Interaction_Box& it_box, Progress& progress);
void Show_Npc_Item_Interaction(HDC hdc, const Npc& item, const Interaction_Box& it_box, Progress& progress);
void Show_Npc_Legend_Interaction(HDC hdc, const Npc& Legend, const Interaction_Box& it_box, Progress& progress);
void Show_Npc_Soldier_Interaction(HDC hdc, const Npc& Soldier, const Interaction_Box& it_box, Progress& progress);

void Show_Dialog_Box(HDC hdc, HDC bitdc, const Interaction_Box& it_box, const int& dialog_type);
const int Select_Dialog_Ok(Interaction_Box& it_box, const WPARAM wParam);
void Interaction_Dialog_Select(Player& player, Map_Village& map_v, Interaction_Box& it_box, const WPARAM wParam);