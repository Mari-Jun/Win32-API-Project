#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Interface.h"
#include "Object_Main.h"
#include "Object_Enemy.h"
#include "Object_Player.h"
#include "Object_Info.h"
#include "Object_Skill.h"
#include "Map_Dungeon.h"
#include "Camera.h"
#include "Item.h"
#include "Equipment.h"

/*Player_Interface*/

Player_Interface::~Player_Interface() {
	DeleteObject(panel_bitmap);
	DeleteObject(hp_bitmap);
	DeleteObject(mp_bitmap);
	for (int index = 0; index < 7; index++)
		DeleteObject(command_bitmap[index]);
}

const HBITMAP& Player_Interface::Get_Panel_Bitmap() const {
	return panel_bitmap;
}

const BITMAP& Player_Interface::Get_Panel_Bitmap_Size() const {
	return panel_bitmap_size;
}

const HBITMAP& Player_Interface::Get_Hp_Bitmap() const {
	return hp_bitmap;
}

const BITMAP& Player_Interface::Get_Hp_Bitmap_Size() const {
	return hp_bitmap_size;
}

const HBITMAP& Player_Interface::Get_Mp_Bitmap() const {
	return mp_bitmap;
}

const BITMAP& Player_Interface::Get_Mp_Bitmap_Size() const {
	return mp_bitmap_size;
}

const HBITMAP& Player_Interface::Get_Command_Bitmap(const int& index) const {
	return command_bitmap[index];
}

const BITMAP& Player_Interface::Get_Command_Bitmap_Size() const {
	return command_bitmap_size;
}


void Player_Interface::Set_Bitmap() {
	panel_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\PlayerPanels.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(panel_bitmap, sizeof(BITMAP), &panel_bitmap_size);
	hp_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\Hp.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hp_bitmap, sizeof(BITMAP), &hp_bitmap_size);
	mp_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Interface\\Player\\Mp.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(mp_bitmap, sizeof(BITMAP), &mp_bitmap_size);

	for (int index = 0; index < 7; index++) {
		TCHAR str[40];
		wsprintf(str, _T(".\\BitMap\\Interface\\Player\\Command%d.bmp"), index + 1);
		command_bitmap[index] = (HBITMAP)LoadImage(NULL, str, IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	}
	GetObject(command_bitmap[0], sizeof(BITMAP), &command_bitmap_size);
}

void Reset_Player_Interface(Player_Interface& p_inter) {
	p_inter.Set_Bitmap();
}

void Paint_Player_Interface(HDC hdc, HDC bitdc, const RECT c_rect, const Player_Interface& p_inter, const Player& player) {
	SelectObject(bitdc, p_inter.Get_Hp_Bitmap());
	
	TransparentBlt(hdc, c_rect.right - p_inter.Get_Hp_Bitmap_Size().bmWidth - 115, c_rect.bottom - (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()) - 10,
		p_inter.Get_Hp_Bitmap_Size().bmWidth, (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()),
		bitdc, 0, p_inter.Get_Hp_Bitmap_Size().bmHeight - (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()),
		p_inter.Get_Hp_Bitmap_Size().bmWidth, (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Hp() / player.Get_Object_Info_Const().Get_Max_Hp()), RGB(150, 150, 150));

	SelectObject(bitdc, p_inter.Get_Mp_Bitmap());

	TransparentBlt(hdc, c_rect.right - p_inter.Get_Hp_Bitmap_Size().bmWidth - 10, c_rect.bottom - (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Mp() / player.Get_Object_Info_Const().Get_Max_Mp()) - 10,
		p_inter.Get_Hp_Bitmap_Size().bmWidth, (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Mp() / player.Get_Object_Info_Const().Get_Max_Mp()),
		bitdc, 0, p_inter.Get_Hp_Bitmap_Size().bmHeight - (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Mp() / player.Get_Object_Info_Const().Get_Max_Mp()),
		p_inter.Get_Hp_Bitmap_Size().bmWidth, (p_inter.Get_Hp_Bitmap_Size().bmHeight * player.Get_Object_Info_Const().Get_Mp() / player.Get_Object_Info_Const().Get_Max_Mp()), RGB(150, 150, 150));

	SelectObject(bitdc, p_inter.Get_Panel_Bitmap());
	TransparentBlt(hdc, c_rect.right - p_inter.Get_Panel_Bitmap_Size().bmWidth, c_rect.bottom - p_inter.Get_Panel_Bitmap_Size().bmHeight, p_inter.Get_Panel_Bitmap_Size().bmWidth, p_inter.Get_Panel_Bitmap_Size().bmHeight,
		bitdc, 0, 0, p_inter.Get_Panel_Bitmap_Size().bmWidth, p_inter.Get_Panel_Bitmap_Size().bmHeight, RGB(145, 145, 145));

	//아이템을 출력합니다.
	Paint_Player_Item(hdc, bitdc, player.Get_Player_Item_Const(), c_rect);

	//스킬을 출력합니다.
	Paint_Player_Skill_Icon(hdc, bitdc, player.Get_Player_Skill_Const(), c_rect);

	//단축키 그림을 출력합니다.
	for (int index = 0; index < 3; index++) {
		SelectObject(bitdc, p_inter.Get_Command_Bitmap(index));
		TransparentBlt(hdc, c_rect.right - 406 + index * 57, c_rect.bottom - 117, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, bitdc, 0, 0, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	}
	for (int index = 3; index < 7; index++) {
		SelectObject(bitdc, p_inter.Get_Command_Bitmap(index));
		TransparentBlt(hdc, c_rect.right - 460 + (index - 3) * 56, c_rect.bottom - 60, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, bitdc, 0, 0, p_inter.Get_Command_Bitmap_Size().bmWidth, p_inter.Get_Command_Bitmap_Size().bmHeight, RGB(17, 33, 42));
	}

}

/*Enemy Interface*/

Enemy_Interface::~Enemy_Interface() {
	DeleteObject(font);
	DeleteObject(hp_bitmap);
}

const HFONT& Enemy_Interface::Get_Font() const {
	return font;
}

const HBITMAP& Enemy_Interface::Get_Hp_BackGround_Bitmap() const {
	return hp_background;
}

const BITMAP& Enemy_Interface::Get_Hp_BackGround_Bitmap_Size() const {
	return hp_background_size;
}

const HBITMAP& Enemy_Interface::Get_Hp_Bitmap() const {
	return hp_bitmap;
}

const BITMAP& Enemy_Interface::Get_Hp_Bitmap_Size() const {
	return hp_bitmap_size;
}

void Enemy_Interface::Set_Font() {
	font = CreateFont(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼 편지체"));
}

void Enemy_Interface::Set_Bitmap() {
	hp_background = (HBITMAP)LoadImage(NULL, _T(".\\Bitmap\\Interface\\Monster\\Enemy_Hp_Bk.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hp_background, sizeof(BITMAP), &hp_background_size);
	hp_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\Bitmap\\Interface\\Monster\\Enemy_Hp.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(hp_bitmap, sizeof(BITMAP), &hp_bitmap_size);
}


void Reset_Enemy_Interface(Enemy_Interface& e_inter) {
	e_inter.Set_Font();
	e_inter.Set_Bitmap();
}

void Paint_Enemy_Interface(HDC hdc, HDC bitdc, const RECT c_rect, const Enemy_Interface& e_inter, const Map_Dungeon& map_d, const Camera& camera) {
	SelectObject(hdc, e_inter.Get_Font());
	TCHAR str[20];
	int count = 0;
	for (int index = 0; index < 53; index++) 
		if (&map_d.Get_Enemy_Const(index) != NULL)
			count++;
	wsprintf(str, _T("남은 몬스터 수 : %d"), count);
	TextOut(hdc, c_rect.right - 200, 20, str, _tcslen(str));

	for (int index = 50; index < 53; index++) {
		if (&map_d.Get_Enemy_Const(index) != NULL && 
			camera.Get_Cam_Left() <= map_d.Get_Enemy_Const(index).Get_XPos() + map_d.Get_Enemy_Const(index).Get_Width() &&
			camera.Get_Cam_Left() + c_rect.right >= map_d.Get_Enemy_Const(index).Get_XPos() && 
			camera.Get_Cam_Top() <= map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height() &&
			camera.Get_Cam_Top() + c_rect.bottom >= map_d.Get_Enemy_Const(index).Get_YPos()) {

			switch (map_d.Get_Enemy_Const(index).Get_Enemy_Type())
			{
			case Enemy_Type::Dark_Flower:
				wsprintf(str, _T("암흑속에 피어난 꽃"));
				break;
			case Enemy_Type::Grave:
				wsprintf(str, _T("문지기"));
				break;
			case Enemy_Type::Zeffel:
				wsprintf(str, _T("실패한 비밀 병기"));
				break;
			case Enemy_Type::Vagullion:
				wsprintf(str, _T("공허한 존재"));
				break;
			case Enemy_Type::Liagty1:
			case Enemy_Type::Liagty2:
			case Enemy_Type::Liagty3:
				wsprintf(str, _T("하피"));
				break;
			case Enemy_Type::Dularn:
				wsprintf(str, _T("?"));
				break;
			default:
				break;
			}

			SIZE text_size;
			GetTextExtentPoint(hdc, str, _tcslen(str), &text_size);

			TextOut(hdc, 400 - text_size.cx - 10, 15, str, _tcslen(str));

			SelectObject(bitdc, e_inter.Get_Hp_BackGround_Bitmap());

			TransparentBlt(hdc, 400, 0, e_inter.Get_Hp_BackGround_Bitmap_Size().bmWidth, e_inter.Get_Hp_BackGround_Bitmap_Size().bmHeight,
				bitdc, 0, 0, e_inter.Get_Hp_BackGround_Bitmap_Size().bmWidth, e_inter.Get_Hp_BackGround_Bitmap_Size().bmHeight, RGB(150, 150, 150));

			SelectObject(bitdc, e_inter.Get_Hp_Bitmap());

			TransparentBlt(hdc, 400, 0, e_inter.Get_Hp_Bitmap_Size().bmWidth * map_d.Get_Enemy_Const(index).Get_Object_Info_Const().Get_Hp() / map_d.Get_Enemy_Const(index).Get_Object_Info_Const().Get_Max_Hp(), e_inter.Get_Hp_Bitmap_Size().bmHeight,
				bitdc, 0, 0, e_inter.Get_Hp_Bitmap_Size().bmWidth * map_d.Get_Enemy_Const(index).Get_Object_Info_Const().Get_Hp() / map_d.Get_Enemy_Const(index).Get_Object_Info_Const().Get_Max_Hp(), e_inter.Get_Hp_Bitmap_Size().bmHeight, RGB(150, 150, 150));
		}
	}
}

/*Clear_Interface*/

Clear_Interface::~Clear_Interface() {
	DeleteObject(font[0]);
	DeleteObject(font[1]);
	DeleteObject(clear_bitmap);
}

const HFONT& Clear_Interface::Get_Font(const int& index) const {
	return font[index];
}

const HBITMAP& Clear_Interface::Get_Clear_Bitmap() const {
	return clear_bitmap;
}

const BITMAP& Clear_Interface::Get_Clear_Bitmap_Size() const {
	return clear_bitmap_size;
}

const int& Clear_Interface::Get_Item(const int& index) const {
	return item[index];
}

const int& Clear_Interface::Get_Gold() const {
	return gold;
}

void Clear_Interface::Set_Font() {
	font[0] = CreateFont(30, 10, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼 편지체"));
	font[0] = CreateFont(40, 15, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼 편지체"));
}

void Clear_Interface::Set_Bitmap() {
	clear_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\Bitmap\\Interface\\Dungeon_Clear.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
	GetObject(clear_bitmap, sizeof(BITMAP), &clear_bitmap_size);
}

void Clear_Interface::Set_Item() {
	for (int index = 0; index < 3; index++)
		item[index] = rand() % 10;
}

void Clear_Interface::Set_Gold(const Player& player, const Map_Dungeon& map_d) {

	if (player.Get_Object_Info_Const().Get_Level() > map_d.Get_Dungeon_Type())
		return;

	int nokori = 0;
	for (int index = 0; index < 50; index++) 
		if (&map_d.Get_Enemy_Const(index) == NULL)
			nokori++;

	gold += (nokori * map_d.Get_Dungeon_Type() * 10);

	switch (map_d.Get_Dungeon_Type())
	{
	case Map_Type::Dungeon1:
		gold += 500;
		break;
	case Map_Type::Dungeon2:
		gold += 2000;
		break;
	case Map_Type::Dungeon3:
		gold += 3500;
		break;
	case Map_Type::Dungeon4:
		gold += 5000;
		break;
	case Map_Type::Dungeon5:
		gold += 7500;
		break;
	default:
		break;
	}
}

void Reset_Clear_Interface(Clear_Interface& c_inter, Player& player, const Map_Dungeon& map_d) {
	c_inter.Set_Font();
	c_inter.Set_Bitmap();
	c_inter.Set_Item();
	c_inter.Set_Gold(player, map_d);
	Clear_Dungeon_Player_Reward(c_inter, player, map_d);
}

void Paint_Clear_Interface(HDC hdc, HDC bitdc, const Clear_Interface& c_inter, const Player& player, const Map_Dungeon& map_d, const RECT c_rect) {
	SelectObject(bitdc, c_inter.Get_Clear_Bitmap());

	int x_pos = c_rect.right / 2 - c_inter.Get_Clear_Bitmap_Size().bmWidth / 2;
	int y_pos = c_rect.bottom / 2 - c_inter.Get_Clear_Bitmap_Size().bmHeight / 2;

	BitBlt(hdc, x_pos, y_pos, c_inter.Get_Clear_Bitmap_Size().bmWidth, c_inter.Get_Clear_Bitmap_Size().bmHeight, bitdc, 0, 0, SRCCOPY);

	SelectObject(hdc, c_inter.Get_Font(0));
	SetBkMode(hdc, TRANSPARENT);

	TCHAR str[30];
	wsprintf(str, _T("획득한 골드 : %d"), c_inter.Get_Gold());
	TextOut(hdc, x_pos + 40, y_pos + 140, str, _tcslen(str));

	for (int index = 0; index < 3; index++) {
		SelectObject(bitdc, player.Get_Player_Equipment_Const().Get_Equipment_Bitmap(c_inter.Get_Item(index), map_d.Get_Dungeon_Type()));
		StretchBlt(hdc, x_pos + 18 + index * 44, y_pos + 246, 40, 40, bitdc, 0, 0, player.Get_Player_Equipment_Const().Get_Equipment_Bitmap_Size().bmWidth, player.Get_Player_Equipment_Const().Get_Equipment_Bitmap_Size().bmHeight, SRCCOPY);
	}
}

void Clear_Dungeon_Player_Reward(const Clear_Interface& c_inter, Player& player, const Map_Dungeon& map_d) {
	player.Get_Player_Equipment().Set_Gold(player.Get_Player_Equipment_Const().Get_Gold() + c_inter.Get_Gold());
	for (int index = 0; index < 3; index++) 
		player.Get_Player_Equipment().Set_Own(c_inter.Get_Item(index), map_d.Get_Dungeon_Type());
	if (player.Get_Object_Info_Const().Get_Level() == map_d.Get_Dungeon_Type())
		player.Get_Object_Info().Set_Level(map_d.Get_Dungeon_Type() + 1);
}