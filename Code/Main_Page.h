#pragma once
#include <Windows.h>

class Default_Page;
class Button;

class Main_Page {
public:
	Main_Page();
	~Main_Page();

	const Button& GetStartButton() const;
	const Button& GetHelpButton() const;
	const Button& GetCreditButton() const;
	const Button& GetQuitButton() const;
	const int& GetMenuSelect() const;

	void SetButton(HDC hdc, RECT c_rect);
	void SetMenuSelect(const int& select_num);

private:
	Button* start_button;
	Button* help_button;
	Button* credit_button;
	Button* quit_button;
	int menu_select;
};

void Reset_Main_Page(HDC hdc, const RECT c_rect, Default_Page& d_page, Main_Page& m_page);
void Paint_Main_Page(HDC hdc, HDC bitdc, const RECT c_rect, const  Default_Page& d_page, const Main_Page& m_page);
int Key_Down_to_Main_Menu_Select(Main_Page& m_page, WPARAM wParam);