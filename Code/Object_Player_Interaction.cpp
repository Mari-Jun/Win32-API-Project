#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Npc.h"
#include "Object_Main.h"
#include "Object_Player.h"
#include "Object_Player_Interaction.h"
#include "Map_Village.h"

Interaction_Box::~Interaction_Box() {
	DeleteObject(message_box);
}

const RECT Interaction_Box::Get_Messsage_Box_Rect() const {
	return mb_rect;
}

const HBITMAP Interaction_Box::Get_Message_Box() const {
	return message_box;
}

const BITMAP Interaction_Box::Get_Message_Box_Size() const {
	return message_box_size;
}

const HFONT Interaction_Box::Get_Message_Box_Font(const int& index) const {
	return message_box_font[index];
}

const BLENDFUNCTION Interaction_Box::Get_Message_Box_Alpha() const {
	return message_box_alpha;
}

void Interaction_Box::Set_Message_Box(RECT c_rect) {
	message_box = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Interaction_Box.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(message_box, sizeof(BITMAP), &message_box_size);
	mb_rect = { c_rect.left + 320,c_rect.bottom - 240,c_rect.left + 960,c_rect.bottom };
	message_box_font[0] = CreateFont(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼 편지체"));
	message_box_font[1] = CreateFont(35, 12, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼 편지체"));
	message_box_alpha.BlendOp = AC_SRC_OVER;
	message_box_alpha.BlendFlags = 0;
	message_box_alpha.SourceConstantAlpha = 175;
	message_box_alpha.AlphaFormat = 0;
}

void Reset_Interaction_Box(Interaction_Box& it_box, RECT c_rect) {
	it_box.Set_Message_Box(c_rect);
}

bool Paint_Interaction_Box(HDC hdc, HDC alphadc, HDC bitdc, RECT c_rect, Move_Object& player, Interaction_Box& it_box) {
	if (player.Get_Status() == Player_Status::Interaction) {
		SelectObject(bitdc, it_box.Get_Message_Box());
		BitBlt(alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, hdc, c_rect.left + 320, c_rect.bottom - 240, SRCCOPY);
		TransparentBlt(alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, bitdc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, RGB(255, 255, 255));
		AlphaBlend(hdc, it_box.Get_Messsage_Box_Rect().left, it_box.Get_Messsage_Box_Rect().top, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, it_box.Get_Message_Box_Alpha());
		
		return true;
	}
	return false;
}


void Interaction_Command(Move_Object& player, Map_Village& map_v, Interaction_Box& it_box) {

	//NPC와의 상호작용
	if (player.Get_Status() != Player_Status::Interaction) {
		for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) {
			if (&map_v.Get_Npc_Const(npc_type) != NULL && Interaction_Range_Player_To_Npc(player, map_v.Get_Npc_Const(npc_type))) {
				player.Set_Status(Player_Status::Interaction);
				map_v.Get_Npc(npc_type).Set_Interaction(true);
				map_v.Get_Npc(npc_type).Set_interaction_Count(1);
			}
		}
	}
	else {
		for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) {
			if (&map_v.Get_Npc_Const(npc_type) != NULL && map_v.Get_Npc_Const(npc_type).Is_Interaction()) {
				//퀘스트 상태가 아닐 경우
				if (!map_v.Get_Npc_Const(npc_type).Is_Quest_Exist()) {
					switch (npc_type)
					{
					case Npc_Name::ELDER:
					case Npc_Name::ITEM_SHOP:
					case Npc_Name::LEGEND:
					case Npc_Name::SOLDIER:
						map_v.Get_Npc(npc_type).Set_interaction_Count(0);
						player.Set_Status(Player_Status::Stop);
						map_v.Get_Npc(npc_type).Set_Interaction(false);
						break;
					case Npc_Name::WEAPON_SHOP:
						map_v.Get_Npc(npc_type).Set_interaction_Count(map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() + 1);

						if (map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() == 3) {
							map_v.Get_Npc(npc_type).Set_interaction_Count(0);
							player.Set_Status(Player_Status::Stop);
							map_v.Get_Npc(npc_type).Set_Interaction(false);
						}
						break;
					default:
						break;
					}
				}
				//퀘스트 상태일 경우
				else {

				}
			}
		}		
	}
}

bool Interaction_Range_Player_To_Npc(Move_Object& player, const Npc& npc) {
	if (npc.Get_XPos() - 40 < player.Get_XPos() + player.Get_Crash_Width() && npc.Get_XPos() + npc.Get_Crash_Width() + 40 > player.Get_XPos() &&
		npc.Get_YPos() + npc.Get_Height() - npc.Get_Crash_Height() - 40 < player.Get_YPos() + player.Get_Height() &&
		npc.Get_YPos() + npc.Get_Height() + 40 > player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height()) {
		player.Set_Status(Player_Status::Interaction);
		return true;
	}
	
	return false;
}

void Show_Npc_Interaction(HDC hdc, const Map_Village& map_v, const Interaction_Box& it_box) {
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, it_box.Get_Message_Box_Font(0));

	for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) 
		if (&map_v.Get_Npc_Const(npc_type) != NULL && map_v.Get_Npc_Const(npc_type).Is_Interaction()) {
			switch (npc_type)
			{
			case Npc_Name::ELDER:
				Show_Npc_Elder_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box);
				break;
			case Npc_Name::WEAPON_SHOP:
				Show_Npc_Weapon_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box);
				break;
			case Npc_Name::ITEM_SHOP:
				Show_Npc_Item_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box);
				break;
			case Npc_Name::LEGEND:
				Show_Npc_Legend_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box);
				break;
			case Npc_Name::SOLDIER:
				Show_Npc_Soldier_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box);
			default:
				break;
			}
		}
}

void Show_Npc_Elder_Interaction(HDC hdc, const Npc& elder, const Interaction_Box& it_box) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 50, _T("촌장"), 2);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("마을을 지켜야하는데..."), 13);
}


void Show_Npc_Weapon_Interaction(HDC hdc, const Npc& weapon, const Interaction_Box& it_box) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 50, _T("장비 상인"), 5);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	switch (weapon.Get_Interaction_Count())
	{
	case 1:
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("마음에 드는게 있으면 골라봐!!!"), 18);
		break;
	case 2:
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("다음에 또 오라구!"), 10);
		break;
	default:
		break;
	}
	
}

void Show_Npc_Item_Interaction(HDC hdc, const Npc& item, const Interaction_Box& it_box) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 50, _T("치유 술사"), 5);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("치유가 필요하신가요?"), 11);
}

void Show_Npc_Legend_Interaction(HDC hdc, const Npc& Legend, const Interaction_Box& it_box) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 50, _T("퇴역한 수비대장"), 8);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("크윽.. 내가 10년만 젊었어도..."), 20);
}

void Show_Npc_Soldier_Interaction(HDC hdc, const Npc& Soldier, const Interaction_Box& it_box) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 50, _T("군인"), 2);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("이 앞은 몬스터가 많아서 위험해"), 17);
}