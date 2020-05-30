#pragma once
#include <Windows.h>

class Map;
class Object_Info;

class Object {
public:
	const int& Get_XPos() const;
	const int& Get_YPos() const;
	const int& Get_Width() const;
	const int& Get_Height() const;
	const int& Get_Crash_Width() const;
	const int& Get_Crash_Height() const;

	void Set_XPos(const int& x_pos);
	void Set_YPos(const int& y_pos);
	void Set_Width(const int& width);
	void Set_Height(const int& height);
	void Set_Crash_Width(const int& c_width);
	void Set_Crash_Height(const int& c_height);


	void Move_Object_Up(const int& speed);
	void Move_Object_Down(const int& speed);
	void Move_Object_Left(const int& speed);
	void Move_Object_Right(const int& speed);

private:
	int x_pos;
	int y_pos;
	int width;
	int height;
	int crash_width;
	int crash_height;
};

void Reset_Object(Object& object, const int& x_pos, const int& y_pos, const int& width, const int& height);

class Non_Move_Object : public Object {
public:
	~Non_Move_Object();

	const HBITMAP& Get_Object_Bitmap() const;
	const BITMAP& Get_Object_Image_Size() const;

	void Set_Object_Bitmap(HBITMAP bitmap);
private:
	HBITMAP object_image_bitmap;
	BITMAP object_image_size;
};

void Reset_Non_Move_Object(Non_Move_Object& nm_object, const int& x_pos, const int& y_pos, HBITMAP bitmap);

class Hitting_Range_Polygon;

class Move_Object : public Object {
public:
	~Move_Object();

	const int& Get_Status() const;
	const int& Get_Direction() const;
	const int& Get_Speed() const;
	const int& Get_Ani_Count() const;
	const int& Get_Hitting_Damage() const;
	const int& Get_Hitting_Damage_Count() const;
	const Hitting_Range_Polygon& Get_Hit_Range_P_Const(const int& index) const;
	Hitting_Range_Polygon& Get_Hit_Range_P(const int& index) const;
	const Object_Info& Get_Object_Info_Const() const;
	Object_Info& Get_Object_Info() const;

	void Set_Status(const int& status);
	void Set_Direction(const int& direction);
	void Set_Speed(const int& speed);
	void Set_Ani_Count(const int& ani_count);
	void Set_Hitting_Damage(const int& hit_dmg);
	void Set_Hitting_Damage_Count(const int& hit_dmg_count);
	void Set_Hit_Range_Polygon(const int& index, const int& owner, const bool& move, const int& direcction, const POINT& speed, const int& type, const int& attack_type, const POINT pos[4], const int& delay, const double& attack_multiple);
	void Set_Hit_Range_Circle(const int& index, const int& owner);

	void Create_Object_Info();
	void Delete_Hit_Range_Polygon(const int& index);

private:
	int status;
	int direction;
	int speed;
	int animaition_count;
	int hitting_damage;
	int hitting_damage_count;
	Hitting_Range_Polygon* hit_range[20];
	Object_Info* o_info;
};

void Reset_Move_Object(Move_Object& m_object, const int& x_pos, const int& y_pos, const int& width, const int& height, const int& speed);
void Paint_Hitting_Damage(HDC hdc, const Move_Object& m_object);
void Calcul_Hitting_Damage(const Move_Object& attack_obj, Move_Object& hit_obj, const int& hit_dmg, const int& owner);
void Count_Up_Hitting_Damage_Count(Move_Object& m_object);