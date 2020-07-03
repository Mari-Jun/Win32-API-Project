#pragma once
#include <Windows.h>

class Default_Page;
class Button;

class Help_Page {
public:
	Help_Page();
	~Help_Page();

	const Button& Get_Next_Button() const;
	const Button& Get_Back_Button() const;
	const int& Get_Menu_Select() const;
	const int& Get_Page_Select() const;

	void Set_Button(HDC hdc, const RECT c_rect);
	void Set_Menu_Select(const int& select_num);
	void Set_Page_Select(const int& page_select);

private:
	Button* next_button;
	Button* back_button;
	int menu_select;
	int page_select;
};

void Reset_Help_Page(HDC hdc, const RECT c_rect, Default_Page& d_page, Help_Page& h_page);
void Paint_Help_Page(HDC hdc, HDC bitdc, const RECT c_rect, const Default_Page& d_page, const Help_Page& h_page);
void Paint_Credit_Page(HDC hdc, HDC bitdc, const RECT c_rect, const Default_Page& d_page, const Help_Page& h_page);
int Key_Down_to_Help_Menu_Select(Help_Page& h_page, const WPARAM wParam, const int& page_type);