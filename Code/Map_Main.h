#pragma once
#include <Windows.h>

class Non_Move_Object;
class Non_Move_Npc;
class Enemy;

class Map {
public:
	virtual ~Map();

	const RECT& Get_Map_Rect() const;
	const HBITMAP& Get_Map_Size_Bitmap() const;
	const Non_Move_Object& Get_NM_Object_Const(const int& index) const;
	Non_Move_Object& Get_NM_Object(const int& index) const;
	const Non_Move_Npc& Get_NM_Npc_Const(const int& index) const;
	Non_Move_Npc& Get_NM_Npc(const int& index) const;

	virtual void Set_NM_Object() = 0;
	virtual void Set_NM_Npc() = 0;

	void Create_NM_Object(const int& index);
	void Create_NM_Npc(const int& index);

	void Set_Map_Rect(const int& left, const int& top, const int& right, const int& bottom);
	void Set_Map_Size_Bit(HDC hdc);

private:
	RECT map_rect;
	HBITMAP map_size_bit;
	Non_Move_Object* nm_object[10];
	Non_Move_Npc* nm_npc[4];
	Enemy* enemy[3];
};