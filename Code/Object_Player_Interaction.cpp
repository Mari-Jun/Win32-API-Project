#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Game_Progress.h"
#include "Object_Npc.h"
#include "Object_Info.h"
#include "Object_Player.h"
#include "Object_Player_Interaction.h"
#include "Map_Village.h"
#include "Shop.h"
#include "Item.h"
#include "Sound.h"

Interaction_Box::~Interaction_Box() {
	DeleteObject(message_box);
}

const RECT& Interaction_Box::Get_Messsage_Box_Rect() const {
	return mb_rect;
}

const HBITMAP& Interaction_Box::Get_Message_Box() const {
	return message_box;
}

const BITMAP& Interaction_Box::Get_Message_Box_Size() const {
	return message_box_size;
}

const HFONT& Interaction_Box::Get_Message_Box_Font(const int& index) const {
	return message_box_font[index];
}

const BLENDFUNCTION& Interaction_Box::Get_Message_Box_Alpha() const {
	return message_box_alpha;
}

const RECT& Interaction_Box::Get_Dialog_Box_Rect() const {
	return db_rect;
}

const HBITMAP& Interaction_Box::Get_Dialog_Box(const int& index) const {
	return dialog_box[index];
}

const BITMAP& Interaction_Box::Get_Dialog_Box_Size() const {
	return dialog_box_size;
}

const HBITMAP& Interaction_Box::Get_Dialog_Select() const {
	return dialog_select;
}

const BITMAP& Interaction_Box::Get_Dialog_Select_Size() const {
	return dialog_select_size;
}

const bool& Interaction_Box::Is_Select_Ok() const {
	return select_ok;
}

const int& Interaction_Box::Get_Dialog_Status() const {
	return dialog_status;
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

void Interaction_Box::Set_Dialog_Box(RECT c_rect) {
	dialog_box[0] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Dialog_Box1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	dialog_box[1] = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Dialog_Box2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(dialog_box[0], sizeof(BITMAP), &dialog_box_size);
	db_rect = { c_rect.right / 2 - dialog_box_size.bmWidth / 2, c_rect.bottom / 2 - dialog_box_size.bmHeight / 2, c_rect.right / 2 + dialog_box_size.bmWidth / 2, c_rect.bottom / 2 + dialog_box_size.bmHeight / 2 };
	
	dialog_select = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Border1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(dialog_select, sizeof(BITMAP), &dialog_select_size);
}
void Interaction_Box::Set_Select_Ok(const bool& select_ok) {
	this->select_ok = select_ok;
}

void Interaction_Box::Set_Dialog_Status(const int& dialog_status) {
	this->dialog_status = dialog_status;
}

void Reset_Interaction_Box(Interaction_Box& it_box, RECT c_rect) {
	it_box.Set_Message_Box(c_rect);
	it_box.Set_Dialog_Box(c_rect);
	it_box.Set_Select_Ok(false);
}

bool Paint_Interaction_Box(HDC hdc, HDC alphadc, HDC bitdc, RECT c_rect, Player& player, Interaction_Box& it_box) {
	if (player.Get_Status() == Player_Status::Interaction || player.Get_Status() == Player_Status::Shopping) {
		SelectObject(bitdc, it_box.Get_Message_Box());
		BitBlt(alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, hdc, c_rect.left + 320, c_rect.bottom - 240, SRCCOPY);
		TransparentBlt(alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, bitdc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, RGB(255, 255, 255));
		AlphaBlend(hdc, it_box.Get_Messsage_Box_Rect().left, it_box.Get_Messsage_Box_Rect().top, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, alphadc, 0, 0, it_box.Get_Message_Box_Size().bmWidth, it_box.Get_Message_Box_Size().bmHeight, it_box.Get_Message_Box_Alpha());
		
		return true;
	}
	return false;
}


void Interaction_Command(Player& player, Map_Village& map_v, Interaction_Box& it_box, Progress& progress) {
	if (player.Get_Status() == Player_Status::Inventory || it_box.Get_Dialog_Status() != 0)
		return;

	//NPC와의 상호작용
	if (player.Get_Status() != Player_Status::Interaction && player.Get_Status() != Player_Status::Shopping) {
		for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) {
			if (&map_v.Get_Npc_Const(npc_type) != NULL && Interaction_Range_Player_To_Npc(player, map_v.Get_Npc_Const(npc_type))) {
				player.Set_Status(Player_Status::Interaction);
				map_v.Get_Npc(npc_type).Set_Interaction(true);
				map_v.Get_Npc(npc_type).Set_interaction_Count(1);
				if (npc_type == Npc_Name::EQUIPMENT_SHOP) {
					map_v.Create_Shop(Shop_Type::Equipment_Type, it_box.Get_Messsage_Box_Rect());
					player.Set_Status(Player_Status::Shopping);
				}
				else if (npc_type == Npc_Name::WEAPON_SHOP) {
					map_v.Create_Shop(Shop_Type::Accessory_Type, it_box.Get_Messsage_Box_Rect());
					player.Set_Status(Player_Status::Shopping);
				}

				//상호작용 사운드 재생
				map_v.Get_Village_Sound().Play_Sound(npc_type + 1);
			}
		}
	}
	else {
		for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) {
			if (&map_v.Get_Npc_Const(npc_type) != NULL && map_v.Get_Npc_Const(npc_type).Is_Interaction()) {
				//퀘스트 상태가 아닐 경우
				if (map_v.Get_Npc_Const(npc_type).Get_Quest_Num() == Quest_Name::No_Quest) {
					switch (npc_type)
					{
					case Npc_Name::ELDER:
					case Npc_Name::LEGEND:
					case Npc_Name::SOLDIER:
						map_v.Get_Npc(npc_type).Set_interaction_Count(0);
						player.Set_Status(Player_Status::Stop);
						map_v.Get_Npc(npc_type).Set_Interaction(false);
						break;
					case Npc_Name::ITEM_SHOP:
						//Hp포션과 Mp포션과 만병통치약을 가득 채웁니다.
						if (map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() == 1) {
							player.Get_Object_Info().Set_Hp(player.Get_Object_Info_Const().Get_Max_Hp());
							player.Get_Object_Info().Set_Mp(player.Get_Object_Info_Const().Get_Max_Mp());
							player.Get_Player_Item().Set_Hp_Potion(player.Get_Player_Item_Const().Get_Hp_Potion_Max());
							player.Get_Player_Item().Set_Mp_Potion(player.Get_Player_Item_Const().Get_Mp_Potion_Max());
							player.Get_Player_Item().Set_Panacea(1);

							//다이얼로그를 띄웁니다.
							it_box.Set_Dialog_Status(it_box.Get_Dialog_Status() + 1);

						}
						else if (map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() > 1) {
							map_v.Get_Npc(npc_type).Set_interaction_Count(0);
							player.Set_Status(Player_Status::Stop);
							map_v.Get_Npc(npc_type).Set_Interaction(false);
						}
						break;
					case Npc_Name::EQUIPMENT_SHOP:
					case Npc_Name::WEAPON_SHOP:
						map_v.Get_Npc(npc_type).Set_interaction_Count(map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() + 1);

						if (map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() == 2) {
							player.Set_Status(Player_Status::Interaction);
							map_v.Destroy_Shop();
						}
						else if (map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() == 3) {
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
					switch (map_v.Get_Npc_Const(npc_type).Get_Quest_Num())
					{
					case Quest_Name::Main_Quest1:
						if (map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() == 4) {
							it_box.Set_Dialog_Status(it_box.Get_Dialog_Status() + 1);
						}
						else if (map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() == 5) {
							map_v.Get_Npc(npc_type).Set_interaction_Count(0);
							map_v.Get_Npc(npc_type).Set_Quest_Num(Quest_Name::No_Quest);
							player.Set_Status(Player_Status::Stop);
							map_v.Get_Npc(npc_type).Set_Interaction(false);
							//게임 진행의 퀘스트 값을 1 올려준다.
							progress.Set_Quest_Num(progress.Get_Quest_Num() + 1);
						}
						else if (map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() == 6) {
							map_v.Get_Npc(npc_type).Set_interaction_Count(0);
							player.Set_Status(Player_Status::Stop);
							map_v.Get_Npc(npc_type).Set_Interaction(false);
						}
						break;
					default:
						break;
					}
					if (it_box.Get_Dialog_Status() == 0)
						map_v.Get_Npc(npc_type).Set_interaction_Count(map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() + 1);
				}
			}
		}		
	}
}

bool Interaction_Range_Player_To_Npc(Player& player, const Npc& npc) {
	if (npc.Get_XPos() - 40 < player.Get_XPos() + player.Get_Crash_Width() && npc.Get_XPos() + npc.Get_Crash_Width() + 40 > player.Get_XPos() &&
		npc.Get_YPos() + npc.Get_Height() - npc.Get_Crash_Height() - 40 < player.Get_YPos() + player.Get_Height() &&
		npc.Get_YPos() + npc.Get_Height() + 40 > player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height()) {
		player.Set_Status(Player_Status::Interaction);
		return true;
	}
	
	return false;
}

void Show_Npc_Interaction(HDC hdc, HDC bitdc, const Player& player, const Map_Village& map_v, const Interaction_Box& it_box, Progress& progress) {
	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(255, 255, 255));
	SelectObject(hdc, it_box.Get_Message_Box_Font(0));

	for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++) 
		if (&map_v.Get_Npc_Const(npc_type) != NULL && map_v.Get_Npc_Const(npc_type).Is_Interaction()) {
			switch (npc_type)
			{
			case Npc_Name::ELDER:
				Show_Npc_Elder_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box, progress);
				if (it_box.Get_Dialog_Status() == 1)
					Show_Dialog_Box(hdc, bitdc, it_box, Dialog_Type::Quest_Type);
				break;
			case Npc_Name::EQUIPMENT_SHOP:
				Show_Npc_Equipment_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box, progress);
				if (&map_v.Get_Shop_Const() != NULL) {
					Paint_Shop(hdc, bitdc, player.Get_Player_Equipment_Const(), map_v.Get_Shop_Const());
					if (it_box.Get_Dialog_Status() == 1)
						Show_Dialog_Box(hdc, bitdc, it_box, Dialog_Type::Shop_Type);
					else if (it_box.Get_Dialog_Status() == 2)
						Show_Dialog_Box(hdc, bitdc, it_box, Dialog_Type::No_Money_Type);
				}	
				break;
			case Npc_Name::WEAPON_SHOP:
				Show_Npc_Weapon_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box, progress);
				if (&map_v.Get_Shop_Const() != NULL) {
					Paint_Shop(hdc, bitdc, player.Get_Player_Equipment_Const(), map_v.Get_Shop_Const());
					if (it_box.Get_Dialog_Status() == 1)
						Show_Dialog_Box(hdc, bitdc, it_box, Dialog_Type::Shop_Type);
					else if (it_box.Get_Dialog_Status() == 2)
						Show_Dialog_Box(hdc, bitdc, it_box, Dialog_Type::No_Money_Type);
				}
				break;
			case Npc_Name::ITEM_SHOP:
				Show_Npc_Item_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box, progress);
				if (it_box.Get_Dialog_Status() == 1)
					Show_Dialog_Box(hdc, bitdc, it_box, Dialog_Type::Heal_Type);
				break;
			case Npc_Name::LEGEND:
				Show_Npc_Legend_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box, progress);
				break;
			case Npc_Name::SOLDIER:
				Show_Npc_Soldier_Interaction(hdc, map_v.Get_Npc_Const(npc_type), it_box, progress);
			default:
				break;
			}
		}
}

void Show_Npc_Elder_Interaction(HDC hdc, const Npc& elder, const Interaction_Box& it_box, Progress& progress) {
	SelectObject(hdc, it_box.Get_Message_Box_Font(1));

	if (elder.Get_Quest_Num() == Quest_Name::No_Quest && (progress.Get_Quest_Num() != progress.Get_Quest_Clear())) {
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("마을을 지켜야하는데..."), 13);
	}
	else if (elder.Get_Quest_Num() != Quest_Name::No_Quest) {
		switch (elder.Get_Interaction_Count())
		{
		case 1:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("쿨럭.. 쿨럭.."), 9);
			break;
		case 2:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("응? 자네는 누군가?"), 11);
			break;
		case 3:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("임시이름"), 4);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("....."), 11);
			break;
		case 4:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("그렇군.. 마침 잘됬구만"), 13);
			break;
		case 5:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("고맙네, 청년"), 7);
			break;
		case 6:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("에휴,, 요즘것들은.."), 12);
			break;
		default:
			break;
		}
	}
	else {
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("끄아아아악"), 5);
	}

	/*if (progress.Get_Quest_Num() == Quest_Name::No_Quest && progress.Get_Quest_Clear() == Quest_Name::No_Quest && elder.Get_Quest_Num() == Quest_Name::Main_Quest1) {
		switch (elder.Get_Interaction_Count())
		{
		case 1:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("쿨럭.. 쿨럭.."), 9);
			break;
		case 2:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("응? 자네는 누군가?"), 11);
			break;
		case 3:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("임시이름"), 4);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("....."), 11);
			break;
		case 4:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("그렇군.. 마침 잘됬구만"), 13);
			break;
		case 5:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("고맙네, 청년"), 7);
			break;
		case 6:
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
			TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("에휴,, 요즘것들은.."), 12);
			break;
		default:
			break;
		}
	}
	else {
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("촌장"), 2);
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("마을을 지켜야하는데..."), 13);
	}*/
}


void Show_Npc_Equipment_Interaction(HDC hdc, const Npc& equip, const Interaction_Box& it_box, Progress& progress) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("장비 상인"), 5);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	switch (equip.Get_Interaction_Count())
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

void Show_Npc_Weapon_Interaction(HDC hdc, const Npc& weapon, const Interaction_Box& it_box, Progress& progress) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("무기/장신구 상인"), 9);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	switch (weapon.Get_Interaction_Count())
	{
	case 1:
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("내가 전국 각지에서 명물들을 모아왔지"), 20);
		break;
	case 2:
		TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("그것밖에 안 사는 거야?"), 13);
		break;
	default:
		break;
	}

}

void Show_Npc_Item_Interaction(HDC hdc, const Npc& item, const Interaction_Box& it_box, Progress& progress) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("치유 술사"), 5);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("당신에게 가호가 있기를.."), 14);
}

void Show_Npc_Legend_Interaction(HDC hdc, const Npc& Legend, const Interaction_Box& it_box, Progress& progress) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("퇴역한 수비대장"), 8);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("크윽.. 내가 10년만 젊었어도..."), 20);
}

void Show_Npc_Soldier_Interaction(HDC hdc, const Npc& Soldier, const Interaction_Box& it_box, Progress& progress) {
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 45, _T("군인"), 2);

	SelectObject(hdc, it_box.Get_Message_Box_Font(1));
	TextOut(hdc, it_box.Get_Messsage_Box_Rect().left + 100, it_box.Get_Messsage_Box_Rect().top + 90, _T("이 앞은 몬스터가 많아서 위험해"), 17);
}

void Show_Dialog_Box(HDC hdc, HDC bitdc, const Interaction_Box& it_box, const int& dialog_type) {
	
	switch (dialog_type)
	{
	case Dialog_Type::Shop_Type:
	case Dialog_Type::Quest_Type:
		SelectObject(bitdc, it_box.Get_Dialog_Box(0));
		break;
	case Dialog_Type::No_Money_Type:
	case Dialog_Type::Heal_Type:
		SelectObject(bitdc, it_box.Get_Dialog_Box(1));
		break;
	default:
		break;
	}
	TransparentBlt(hdc, it_box.Get_Dialog_Box_Rect().left, it_box.Get_Dialog_Box_Rect().top, it_box.Get_Dialog_Box_Size().bmWidth, it_box.Get_Dialog_Box_Size().bmHeight,
		bitdc, 0, 0, it_box.Get_Dialog_Box_Size().bmWidth, it_box.Get_Dialog_Box_Size().bmHeight, RGB(105, 105, 105));

	//선택 테두리 출력
	SelectObject(bitdc, it_box.Get_Dialog_Select());

	switch (dialog_type)
	{
	case Dialog_Type::Shop_Type:
	case Dialog_Type::Quest_Type:
		TransparentBlt(hdc, it_box.Get_Dialog_Box_Rect().left + 29 + (1 - it_box.Is_Select_Ok()) * 140, it_box.Get_Dialog_Box_Rect().top + 92, it_box.Get_Dialog_Select_Size().bmWidth, it_box.Get_Dialog_Select_Size().bmHeight,
			bitdc, 0, 0, it_box.Get_Dialog_Select_Size().bmWidth, it_box.Get_Dialog_Select_Size().bmHeight, RGB(150, 150, 150));
		break;
	case Dialog_Type::No_Money_Type:
	case Dialog_Type::Heal_Type:
		TransparentBlt(hdc, it_box.Get_Dialog_Box_Rect().left + 102, it_box.Get_Dialog_Box_Rect().top + 92, it_box.Get_Dialog_Select_Size().bmWidth, it_box.Get_Dialog_Select_Size().bmHeight,
			bitdc, 0, 0, it_box.Get_Dialog_Select_Size().bmWidth, it_box.Get_Dialog_Select_Size().bmHeight, RGB(150, 150, 150));
		break;
	default:
		break;
	}

	SelectObject(hdc, it_box.Get_Message_Box_Font(0));
	switch (dialog_type)
	{
	case Dialog_Type::Shop_Type:
		TextOut(hdc, it_box.Get_Dialog_Box_Rect().left + 17, it_box.Get_Dialog_Box_Rect().top + 30, _T("아이템을 구매하시겠습니까?"), 14);
		break;
	case Dialog_Type::Quest_Type:
		TextOut(hdc, it_box.Get_Dialog_Box_Rect().left + 17, it_box.Get_Dialog_Box_Rect().top + 30, _T("퀘스트를 수락하시겠습니까?"), 14);
		break;
	case Dialog_Type::No_Money_Type:
		TextOut(hdc, it_box.Get_Dialog_Box_Rect().left + 17, it_box.Get_Dialog_Box_Rect().top + 30, _T("골드가 충분하지 않습니다."), 13);
		break;
	case Dialog_Type::Heal_Type:
		TextOut(hdc, it_box.Get_Dialog_Box_Rect().left + 17, it_box.Get_Dialog_Box_Rect().top + 30, _T("플레이어가 회복되었습니다."), 13);
		break;
	default:
		break;
	}

}

const int Select_Dialog_Ok(Interaction_Box& it_box, const WPARAM wParam) {
	switch (wParam)
	{
	case VK_LEFT:
		if (!it_box.Is_Select_Ok())
			it_box.Set_Select_Ok(true);
		break;
	case VK_RIGHT:
		if (it_box.Is_Select_Ok())
			it_box.Set_Select_Ok(false);
		break;
	case VK_RETURN:
		return it_box.Is_Select_Ok();
		break;
	default:
		break;
	}
	//이외를 눌렀을 경우
	return 2;
}

void Interaction_Dialog_Select(Player& player, Map_Village& map_v, Interaction_Box& it_box, const WPARAM wParam) {
	if (player.Get_Status() != Player_Status::Interaction || it_box.Get_Dialog_Status() == 0)
		return;

	switch (Select_Dialog_Ok(it_box, wParam))
	{
	case 0:
		//취소을 선택한 경우
		it_box.Set_Dialog_Status(0);
		for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++)
			if (map_v.Get_Npc_Const(npc_type).Is_Interaction())
				map_v.Get_Npc(npc_type).Set_interaction_Count(map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() + 2);
		break;
	case 1:
		//확인을 선택한 경우
		it_box.Set_Dialog_Status(0);
		for (int npc_type = Npc_Name::ELDER; npc_type <= Npc_Name::SOLDIER; npc_type++)
			if (map_v.Get_Npc_Const(npc_type).Is_Interaction())
				map_v.Get_Npc(npc_type).Set_interaction_Count(map_v.Get_Npc_Const(npc_type).Get_Interaction_Count() + 1);
		break;
	default:
		break;
	}
}