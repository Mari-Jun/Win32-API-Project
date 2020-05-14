#pragma once
#include <Windows.h>

class Object {
public:
	const int& Get_XPos() const;
	const int& Get_YPos() const;
	const int& Get_Width() const;
	const int& Get_Height() const;

	void Set_XPos(const int& x_pos);
	void Set_YPos(const int& y_pos);
	void Set_Width(const int& width);
	void Set_Height(const int& height);

private:
	int x_pos;
	int y_pos;
	int width;
	int height;
};

void Reset_Object(Object& object, const int& x_pos, const int& y_pos, const int& width, const int& height);