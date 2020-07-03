#include <windows.h>
#include <tchar.h>
#include "Button.h"
#include "Source.h"
#include "Default_Page.h"
#include "Main_Page.h"

Main_Page::Main_Page() {
	start_button = Create_Class<Button>();
	help_button = Create_Class<Button>();
	credit_button = Create_Class<Button>();
	quit_button = Create_Class<Button>();
	menu_select = Main_Page_Select::M_Start;
}

Main_Page::~Main_Page() {
	Delete_Class<Button>(&start_button);
	Delete_Class<Button>(&help_button);
	Delete_Class<Button>(&credit_button);
	Delete_Class<Button>(&quit_button);
}

const Button& Main_Page::GetStartButton() const {
	return *start_button;
}

const Button& Main_Page::GetHelpButton() const {
	return *help_button;
}

const Button& Main_Page::GetCreditButton() const {
	return *credit_button;
}

const Button& Main_Page::GetQuitButton() const {
	return *quit_button;
}

const int& Main_Page::GetMenuSelect() const {
	return menu_select;
}

void Main_Page::SetButton(HDC hdc, RECT c_rect) {
	Setting_Button(hdc, *start_button, _T("Start"), c_rect.right / 2, 250, MIDDLE_SORT);
	Setting_Button(hdc, *help_button, _T("Help"), c_rect.right / 2, 350, MIDDLE_SORT);
	Setting_Button(hdc, *credit_button, _T("Credit"), c_rect.right / 2, 450, MIDDLE_SORT);
	Setting_Button(hdc, *quit_button, _T("Quit"), c_rect.right / 2, 550, MIDDLE_SORT);
}


void Main_Page::SetMenuSelect(const int& select_num) {
	menu_select = select_num;
}

void Reset_Main_Page(HDC hdc, const RECT c_rect, Default_Page& d_page, Main_Page& m_page) {
	SelectObject(hdc, d_page.Get_Main_Font());
	m_page.SetButton(hdc, c_rect);
}

void Paint_Main_Page(HDC hdc, HDC bitdc, const RECT c_rect, const  Default_Page& d_page, const Main_Page& m_page) {

	SelectObject(bitdc, d_page.Get_Bitmap());
	BitBlt(hdc, 0, 0, c_rect.right, c_rect.bottom, bitdc, 0, 0, SRCCOPY);

	SetBkMode(hdc, TRANSPARENT);

	SelectObject(hdc, d_page.Get_Big_Font());
	SetTextColor(hdc, RGB(255, 167, 167));
	TextOut(hdc, c_rect.left + 300, 50, _T("NIKKO"), 7);

	for (int menu = Main_Page_Select::M_Start; menu <= Main_Page_Select::M_Quit; menu++) {
		if (menu == m_page.GetMenuSelect()) {
			SelectObject(hdc, d_page.Get_Select_Font());
			SetTextColor(hdc, RGB(0, 51, 153));
		}
		else {
			SelectObject(hdc, d_page.Get_Main_Font());
			SetTextColor(hdc, RGB(103, 153, 255));
		}
		switch (menu)
		{
		case Main_Page_Select::M_Start:
			Paint_Button(hdc, m_page.GetStartButton());
			break;
		case Main_Page_Select::M_Help:
			Paint_Button(hdc, m_page.GetHelpButton());
			break;
		case Main_Page_Select::M_Credit:
			Paint_Button(hdc, m_page.GetCreditButton());
			break;
		case Main_Page_Select::M_Quit:
			Paint_Button(hdc, m_page.GetQuitButton());
			break;
		}
	}
}

int Key_Down_to_Main_Menu_Select(Main_Page& m_page, WPARAM wParam) {
	switch (wParam)
	{
	case VK_UP:
		if (m_page.GetMenuSelect() > Main_Page_Select::M_Start)
			m_page.SetMenuSelect(m_page.GetMenuSelect() - 1);
		break;
	case VK_DOWN:
		if (m_page.GetMenuSelect() < Main_Page_Select::M_Quit)
			m_page.SetMenuSelect(m_page.GetMenuSelect() + 1);
		break;
	case VK_RETURN:
		//해당 메뉴 선택값을 반환합니다.
		return m_page.GetMenuSelect();
	default:
		break;
	}

	return -1;
}