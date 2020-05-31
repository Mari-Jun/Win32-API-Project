#pragma once
#include <Windows.h>

class Non_Move_Object;
class Camera;

class Map {
public:
	virtual ~Map();

	const RECT& Get_Map_Rect() const;
	const HBITMAP& Get_Map_Size_Bitmap() const;
	const Non_Move_Object& Get_NM_Object_Const(const int& index) const;
	Non_Move_Object& Get_NM_Object(const int& index) const;
	const HBITMAP& Get_Texture(const int& index) const;

	void Create_NM_Object(const int& index);
	void Create_Texture(const int& index, HBITMAP texture);

	void Set_Map_Rect(const int& left, const int& top, const int& right, const int& bottom);
	void Set_Map_Size_Bit(const HDC hdc);


private:
	RECT map_rect;
	HDC map_size_dc;
	HBITMAP map_size_bit;
	Non_Move_Object* nm_object[60];
	HBITMAP texture[8];
};

void Paint_BitBlt_Camera_In(HDC hdc, HDC bitdc, const Camera& camera, const RECT c_rect, const int& x_pos, const int& y_pos, const int& x_size, const int& y_size);
void Paint_TransparentBlt_Camera_In(HDC hdc, HDC bitdc, const Camera& camera, const RECT c_rect, const int& x_pos, const int& y_pos, const int& x_size, const int& y_size, const COLORREF& color);