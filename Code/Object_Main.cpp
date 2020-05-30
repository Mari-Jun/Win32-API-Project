#include <windows.h>
#include <tchar.h>
#include "Source.h"
#include "Object_Main.h"
#include "Object_Info.h"
#include "Map_Main.h"
#include "Map_Village.h"
#include "Hitting_Range.h"

const int& Object::Get_XPos() const {
	return x_pos;
}

const int& Object::Get_YPos() const {
	return y_pos;
}

const int& Object::Get_Width() const {
	return width;
}

const int& Object::Get_Height() const {
	return height;
}

const int& Object::Get_Crash_Width() const {
	return crash_width;
}

const int& Object::Get_Crash_Height() const {
	return crash_height;
}

void Object::Set_XPos(const int& x_pos) {
	this->x_pos = x_pos;
}

void Object::Set_YPos(const int& y_pos) {
	this->y_pos = y_pos;
}

void Object::Set_Width(const int& width) {
	this->width = width;
}

void Object::Set_Height(const int& height) {
	this->height = height;
}

void Object::Set_Crash_Width(const int& c_width) {
	crash_width = c_width;
}

void Object::Set_Crash_Height(const int& c_height) {
	crash_height = c_height;
}

void Object::Move_Object_Up(const int& speed) {
	Set_YPos(Get_YPos() - speed);
}

void Object::Move_Object_Down(const int& speed) {
	Set_YPos(Get_YPos() + speed);
}

void Object::Move_Object_Left(const int& speed) {
	Set_XPos(Get_XPos() - speed);
}

void Object::Move_Object_Right(const int& speed) {
	Set_XPos(Get_XPos() + speed);
}

void Reset_Object(Object& object, const int& x_pos, const int& y_pos, const int& width, const int& height) {
	object.Set_XPos(x_pos);
	object.Set_YPos(y_pos);
	object.Set_Width(width);
	object.Set_Height(height);
}

Non_Move_Object::~Non_Move_Object() {
	DeleteObject(object_image_bitmap);
}

const HBITMAP& Non_Move_Object::Get_Object_Bitmap() const {
	return object_image_bitmap;
}

const BITMAP& Non_Move_Object::Get_Object_Image_Size() const {
	return object_image_size;
}

void Non_Move_Object::Set_Object_Bitmap(HBITMAP bitmap) {
	object_image_bitmap = bitmap;
	GetObject(object_image_bitmap, sizeof(BITMAP), &object_image_size);
}

void Reset_Non_Move_Object(Non_Move_Object& nm_object, const int& x_pos, const int& y_pos, HBITMAP bitmap) {
	if (nm_object.Get_Object_Bitmap() == NULL)
		nm_object.Set_Object_Bitmap(bitmap);
	nm_object.Set_Crash_Width(nm_object.Get_Object_Image_Size().bmWidth);
	Reset_Object(nm_object, x_pos, y_pos, nm_object.Get_Object_Image_Size().bmWidth, nm_object.Get_Object_Image_Size().bmHeight);
}

Move_Object::~Move_Object() {
	for (int index = 0; index < 20; index++)
		Delete_Class<Hitting_Range_Polygon>(&hit_range[index]);
}

const int& Move_Object::Get_Status() const {
	return status;
}

const int& Move_Object::Get_Direction() const {
	return direction;
}

const int& Move_Object::Get_Speed() const {
	return speed;
}

const int& Move_Object::Get_Ani_Count() const {
	return animaition_count;
}

const int& Move_Object::Get_Hitting_Damage() const {
	return hitting_damage;
}

const int& Move_Object::Get_Hitting_Damage_Count() const {
	return hitting_damage_count;
}

const Hitting_Range_Polygon& Move_Object::Get_Hit_Range_P_Const(const int& index) const {
	return *hit_range[index];
}

Hitting_Range_Polygon& Move_Object::Get_Hit_Range_P(const int& index) const {
	return *hit_range[index];
}

const Object_Info& Move_Object::Get_Object_Info_Const() const {
	return *o_info;
}

Object_Info& Move_Object::Get_Object_Info() const {
	return *o_info;
}

void Move_Object::Set_Status(const int& status) {
	this->status = status;
}

void Move_Object::Set_Direction(const int& direction) {
	this->direction = direction;
}

void Move_Object::Set_Speed(const int& speed) {
	this->speed = speed;
}

void Move_Object::Set_Ani_Count(const int& ani_count) {
	animaition_count = ani_count;
}

void Move_Object::Set_Hitting_Damage(const int& hit_dmg) {
	hitting_damage = hit_dmg;
}

void Move_Object::Set_Hitting_Damage_Count(const int& hit_dmg_count) {
	hitting_damage_count = hit_dmg_count;
}

void Move_Object::Set_Hit_Range_Polygon(const int& index, const int& owner, const bool& move, const int& direcction, const POINT& speed, const int& type, const int& attack_type, const POINT pos[4], const int& delay, const double& attack_multiple) {
	hit_range[index] = Create_Class<Hitting_Range_Polygon>();
	Reset_Hitting_Range_Polygon(*hit_range[index], owner, move, direcction, speed, type, attack_type, pos, delay, attack_multiple);
}

void Move_Object::Set_Hit_Range_Circle(const int& index, const int& owner) {

}

void Move_Object::Create_Object_Info() {
	o_info = Create_Class<Object_Info>();
}

void Move_Object::Delete_Hit_Range_Polygon(const int& index) {
	Delete_Class<Hitting_Range_Polygon>(&hit_range[index]);
}

void Reset_Move_Object(Move_Object& m_object, const int& x_pos, const int& y_pos, const int& width, const int& height, const int& speed) {
	Reset_Object(m_object, x_pos, y_pos, width, height);
	m_object.Set_Status(Player_Status::Stop);
	m_object.Set_Direction(Object_Direction::Down);
	m_object.Set_Ani_Count(0);
	m_object.Set_Hitting_Damage(-1);
	m_object.Set_Hitting_Damage_Count(-1);
	m_object.Set_Speed(speed);
}

void Paint_Hitting_Damage(HDC hdc, const Move_Object& m_object) {
	if (m_object.Get_Hitting_Damage() == -1 || m_object.Get_Hitting_Damage_Count() == -1)
		return;

	SIZE damage_size;
	TCHAR str[6];
	wsprintf(str, _T("%d"), m_object.Get_Hitting_Damage());

	GetTextExtentPoint(hdc, str, _tcslen(str), &damage_size);

	SetBkMode(hdc, TRANSPARENT);
	SetTextColor(hdc, RGB(204, 61, 61));

	TextOut(hdc, m_object.Get_XPos() + m_object.Get_Crash_Width() / 2 - damage_size.cx / 2, m_object.Get_YPos() - damage_size.cy + 5, str, _tcslen(str));
}

void Calcul_Hitting_Damage(const Move_Object& attack_obj, Move_Object& hit_obj, const int& hit_dmg, const int& owner) {
	int critical = rand() % 100;
	int dmg_range;

	if (owner == Hit_Owner::HO_Player)
		dmg_range = 10;
	else
		dmg_range = 5;

	if (critical <= attack_obj.Get_Object_Info_Const().Get_Fatal())
		hit_obj.Set_Hitting_Damage((hit_dmg - hit_obj.Get_Object_Info_Const().Get_Defence() + ((rand() % 2 == 0) ? rand() % dmg_range : -rand() % dmg_range)) * 2);
	else
		hit_obj.Set_Hitting_Damage(hit_dmg - hit_obj.Get_Object_Info_Const().Get_Defence() + ((rand() % 2 == 0) ? rand() % dmg_range : -rand() % dmg_range));


	//치명타 넣어야함
	hit_obj.Get_Object_Info().Set_Hp(hit_obj.Get_Object_Info_Const().Get_Hp() - hit_obj.Get_Hitting_Damage());

	//데미지 표시 시간 초기화
	hit_obj.Set_Hitting_Damage_Count(0);
}

void Count_Up_Hitting_Damage_Count(Move_Object& m_object) {
	if (m_object.Get_Hitting_Damage_Count() != -1) {
		m_object.Set_Hitting_Damage_Count(m_object.Get_Hitting_Damage_Count() + 1);
		if (m_object.Get_Hitting_Damage_Count() == 20)
			m_object.Set_Hitting_Damage_Count(-1);
	}
}
