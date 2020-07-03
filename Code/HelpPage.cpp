#include <windows.h>
#include <tchar.h>
#include "Button.h"
#include "Source.h"
#include "Default_Page.h"
#include "Help_Page.h"


Help_Page::Help_Page() {
	next_button = Create_Class<Button>();
	back_button = Create_Class<Button>();
	menu_select = 0;
	page_select = 0;
}

Help_Page::~Help_Page() {
	Delete_Class<Button>(&next_button);
	Delete_Class<Button>(&back_button);
}

const Button& Help_Page::Get_Next_Button() const {
	return *next_button;
}

const Button& Help_Page::Get_Back_Button() const {
	return *back_button;
}

const int& Help_Page::Get_Menu_Select() const {
	return menu_select;
}

const int& Help_Page::Get_Page_Select() const {
	return page_select;
}

void Help_Page::Set_Button(HDC hdc, const RECT c_rect) {
	Setting_Button(hdc, *next_button, _T("Next"), c_rect.right - 50, 550, RIGHT_SORT);
	Setting_Button(hdc, *back_button, _T("Back"), c_rect.left + 50, 550, LEFT_SORT);
}

void Help_Page::Set_Menu_Select(const int& select_num) {
	menu_select = select_num;
}

void Help_Page::Set_Page_Select(const int& page_select) {
	this->page_select = page_select;
}

void Reset_Help_Page(HDC hdc, const RECT c_rect, Default_Page& d_page, Help_Page& h_page) {
	SelectObject(hdc, d_page.Get_Main_Font());
	h_page.Set_Button(hdc, c_rect);
	h_page.Set_Page_Select(0);
}

void Paint_Help_Page(HDC hdc, HDC bitdc, const RECT c_rect, const Default_Page& d_page, const Help_Page& h_page) {

	SelectObject(bitdc, d_page.Get_Bitmap());
	BitBlt(hdc, 0, 0, c_rect.right, c_rect.bottom, bitdc, 0, 0, SRCCOPY);

	SetBkMode(hdc, TRANSPARENT);

	SelectObject(hdc, d_page.Get_Info_Font());
	SetTextColor(hdc, RGB(103, 153, 255));

	TextOut(hdc, 300, 50, _T("이동 : ↑ ↓ ← →"), 12);
	TextOut(hdc, 300, 130, _T("공격 : Left Ctrl"), 14);
	TextOut(hdc, 300, 210, _T("스킬 : Q, W, E, R"), 15);
	TextOut(hdc, 300, 290, _T("아이템 : 1, 2, 3"), 13);
	TextOut(hdc, 300, 370, _T("플레이어 정보 확인 : C"), 14);
	TextOut(hdc, 300, 450, _T("장비 변경 : ENTER"), 13);
	TextOut(hdc, 300, 520, _T("상호작용 : F"), 8);

	for (int menu = 0; menu <= 1; menu++) {
		if (menu == h_page.Get_Menu_Select()) {
			SelectObject(hdc, d_page.Get_Select_Font());
			SetTextColor(hdc, RGB(0, 51, 153));
		}
		else {
			SelectObject(hdc, d_page.Get_Main_Font());
			SetTextColor(hdc, RGB(103, 153, 255));
		}
		switch (menu)
		{
		case 0:
			Paint_Button(hdc, h_page.Get_Back_Button());
			break;
		case 1:
			Paint_Button(hdc, h_page.Get_Next_Button());
			break;
		}
	}

}

void Paint_Credit_Page(HDC hdc, HDC bitdc, const RECT c_rect, const Default_Page& d_page, const Help_Page& h_page) {
	SelectObject(bitdc, d_page.Get_Bitmap());
	BitBlt(hdc, 0, 0, c_rect.right, c_rect.bottom, bitdc, 0, 0, SRCCOPY);

	SetBkMode(hdc, TRANSPARENT);

	SelectObject(hdc, d_page.Get_Credit_Font());
	SetTextColor(hdc, RGB(103, 153, 255));

	TextOut(hdc, 50, 50, _T("Message Box : Made By 588ku - pngtree.com"), 41);
	TextOut(hdc, 50, 110, _T("Game_Icon : HorrorPen, ..etc"), 28);
	TextOut(hdc, 50, 170, _T("Village Map Sound : Made By Alex McCulloch"), 42);
	TextOut(hdc, 50, 230, _T("Dungeon4 Map Sound : Made By isaiah658"), 38);
	TextOut(hdc, 50, 290, _T("Dungeon3,4,6 Map Sound : https://www.bensound.com"), 49);
	TextOut(hdc, 50, 350, _T("Character, Npc, Enemy : YS origin, YS VI, YS : The Oath in Felghana"), 67);
	TextOut(hdc, 450, 410, _T(" - https://www.spriters-resource.com/"), 37);

	for (int menu = 0; menu <= 1; menu++) {
		if (menu == h_page.Get_Menu_Select()) {
			SelectObject(hdc, d_page.Get_Select_Font());
			SetTextColor(hdc, RGB(0, 51, 153));
		}
		else {
			SelectObject(hdc, d_page.Get_Main_Font());
			SetTextColor(hdc, RGB(103, 153, 255));
		}
		switch (menu)
		{
		case 0:
			Paint_Button(hdc, h_page.Get_Back_Button());
			break;
		case 1:
			Paint_Button(hdc, h_page.Get_Next_Button());
			break;
		}
	}
}

int Key_Down_to_Help_Menu_Select(Help_Page& h_page, const WPARAM wParam, const int& page_type) {
	switch (wParam)
	{
	case VK_LEFT:
		if (h_page.Get_Menu_Select() > 0)
			h_page.Set_Menu_Select(h_page.Get_Menu_Select() - 1);
		break;
	case VK_RIGHT:
		if (h_page.Get_Menu_Select() < 1)
			h_page.Set_Menu_Select(h_page.Get_Menu_Select() + 1);
		break;
	case VK_RETURN:
		if (page_type == Page_Type::T_Help_Page)
			return 0;
		else if(page_type==Page_Type::T_Credit_Page) {
			return 0;
		}
	default:
		break;
	}

	return -1;
}