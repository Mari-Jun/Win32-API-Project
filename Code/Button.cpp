#include <windows.h>
#include <tchar.h>
#include "Button.h"
#include "Source.h"

const int& Button::GetXPos() const {
	return x_pos;
}

const int& Button::GetYPos() const {
	return y_pos;
}

const SIZE Button::GetSize() const {
	return size;
}

const TCHAR* Button::GetText() const {
	return text;
}


void Button::SetXPos(const int& x) {
	x_pos = x;
}

void Button::SetYPos(const int& y) {
	y_pos = y;
}

void Button::SetSize(HDC hdc) {
	GetTextExtentPointW(hdc, GetText(), _tcslen(GetText()), &size);
}

void Button::SetText(const wchar_t* t) {
	memset(text, NULL, sizeof(text));
	_tcscpy_s(text, t);
}

const bool Button::Check_Click_Button(const int& mouse_x, const int& mouse_y) const {
	if (GetXPos() < mouse_x && GetXPos() + GetSize().cx > mouse_x && GetYPos() < mouse_y && GetYPos() + GetSize().cy > mouse_y)
		return true;
	return false;
}

Button* Create_Button() {
	Button* bt = new Button();
	if (bt == NULL)
		return bt;
	return bt;
}

void Delete_Button(Button** bt) {
	if (*bt != NULL) {
		delete* bt;
		*bt = NULL;
	}
}

void Setting_Button(HDC hdc, Button& bt, const wchar_t* t, const int& x_pos, const int& y_pos, int sort) {
	bt.SetText(t);
	bt.SetSize(hdc);
	switch (sort)
	{
	case Button_Sort::LEFT_SORT:
		bt.SetXPos(x_pos);
		break;
	case Button_Sort::MIDDLE_SORT:
		bt.SetXPos(x_pos - bt.GetSize().cx / 2);
		break;
	case Button_Sort::RIGHT_SORT:
		bt.SetXPos(x_pos - bt.GetSize().cx);
		break;
	default:
		break;
	}
	bt.SetYPos(y_pos);
}

void Paint_Button(HDC hdc, const Button& bt) {
	TextOut(hdc, bt.GetXPos(), bt.GetYPos(), bt.GetText(), _tcslen(bt.GetText()));
}