#pragma once
#include <Windows.h>

class Non_Move_Object;

class Map {
public:
	virtual ~Map();

	const RECT& Get_Map_Rect() const;
	const HBITMAP& Get_Map_Size_Bitmap() const;
	const Non_Move_Object& Get_NM_Object_Const(const int& index) const;
	Non_Move_Object& Get_NM_Object(const int& index) const;
	const HBITMAP& Get_Texture(const int& index) const;

	virtual void Set_NM_Object() = 0;
	virtual void Set_Texture() = 0;

	void Create_NM_Object(const int& index);
	void Create_Texture(const int& index, HBITMAP texture);

	void Set_Map_Rect(const int& left, const int& top, const int& right, const int& bottom);
	void Set_Map_Size_Bit(HDC hdc);


private:
	RECT map_rect;
	HBITMAP map_size_bit;
	Non_Move_Object* nm_object[30];
	HBITMAP texture[8];
};
