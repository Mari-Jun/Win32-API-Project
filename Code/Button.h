#pragma once
#include <windows.h>

class Button {
public:
	const int& GetXPos() const;
	const int& GetYPos() const;
	const SIZE GetSize() const;
	const TCHAR* GetText() const;

	void SetXPos(const int& x);
	void SetYPos(const int& y);
	void SetSize(HDC hdc);
	void SetText(const wchar_t* t);

	const bool Check_Click_Button(const int& mouse_x, const int& mouse_y) const;

private:
	int x_pos;
	int y_pos;
	SIZE size;
	TCHAR text[10];
};

void Setting_Button(HDC hdc, Button& bt, const wchar_t* t, const int& x_pos, const int& y_pos, int sort);
void Paint_Button(HDC hdc, const Button& bt);