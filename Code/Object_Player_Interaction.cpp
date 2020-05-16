#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Npc.h"
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

bool Paint_Interaction_Box(HDC hdc, HDC alphadc, HDC bitdc, RECT c_rect, Player& player, Interaction_Box& it_box) {
	if (player.Get_Status() == Player_Status::Interaction) {
		SelectObject(bitdc, it_box.Get_Message_Box());
		BitBlt(alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, hdc, c_rect.left + 320, c_rect.bottom - 240, SRCCOPY);
		TransparentBlt(alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, bitdc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, RGB(255, 255, 255));
		AlphaBlend(hdc, it_box.Get_Messsage_Box_Rect().left, it_box.Get_Messsage_Box_Rect().top, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, it_box.Get_Message_Box_Alpha());
		
		return true;
	}
	return false;
}

template<>
void Interaction_Command(Player& player, Map_Village& map_v, Interaction_Box& it_box) {

	//NPC와의 상호작용
	if (player.Get_Status() != Player_Status::Interaction) {
		for (int index = 0; index < 4; index++) {
			if (&map_v.Get_NM_Npc_Const(index) != NULL) {

				//상호작용 범위 내에 있으면
				map_v.Get_NM_Npc(index).Set_Interaction(Interaction_Range_Player_To_Npc(player, map_v.Get_NM_Npc_Const(index)));

				if (map_v.Get_NM_Npc_Const(index).Is_Interaction()) {
					player.Set_Status(Player_Status::Interaction);
				}
			}
		}
	}
	else {
		for (int index = 0; index < 4; index++) {
			if (&map_v.Get_NM_Npc_Const(index) != NULL) {
				//퀘스트 상태가 아닐 경우
				if (!map_v.Get_NM_Npc_Const(index).Is_Quest_Exist()) {
					player.Set_Status(Player_Status::Stop);
					map_v.Get_NM_Npc(index).Set_Interaction(false);
				}	
				//퀘스트 상태일 경우
				else {

				}			
			}
		}
	}
}

bool Interaction_Range_Player_To_Npc(Player& player, const Non_Move_Npc& nm_npc) {
	if (nm_npc.Get_XPos() - 40 < player.Get_XPos() + player.Get_Crash_Width() && nm_npc.Get_XPos() + nm_npc.Get_Crash_Width() + 40 > player.Get_XPos() &&
		nm_npc.Get_YPos() + nm_npc.Get_Height() - nm_npc.Get_Crash_Height() - 40 < player.Get_YPos() + player.Get_Height() &&
		nm_npc.Get_YPos() + nm_npc.Get_Height() + 40 > player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height())
		return true;
	return false;
}

template<>
void Show_Npc_Interaction(HDC hdc, Map_Village& map_v, Interaction_Box& it_box) {
	for (int index = Npc_Name::Elder; index < 4; index++) {
		if (&map_v.Get_NM_Npc_Const(index)!=NULL && map_v.Get_NM_Npc_Const(index).Is_Interaction()) {
			SetBkMode(hdc, TRANSPARENT);
			SetTextColor(hdc, RGB(255, 255, 255));
			switch (index)
			{
			case Npc_Name::Elder:
				SelectObject(hdc, it_box.Get_Message_Box_Font(0));
				Show_Npc_Elder_Interaction(hdc, it_box);
				break;
			default:
				break;
			}
		}
	}
}


void Show_Npc_Elder_Interaction(HDC hdc, Interaction_Box& it_box) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 50, _T("촌장"), 2);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("마을을 지켜야하는데..."), 13);
}
