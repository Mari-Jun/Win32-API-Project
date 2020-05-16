#include <windows.h>
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

const HBITMAP Non_Move_Object::Get_Object_Bitmap() const {
	return object_image_bitmap;
}

const BITMAP Non_Move_Object::Get_Object_Image_Size() const {
	return object_image_size;
}

void Non_Move_Object::Set_Object_Bitmap(HBITMAP bitmap) {
	object_image_bitmap = bitmap;
	GetObject(object_image_bitmap, sizeof(BITMAP), &object_image_size);
}

void Reset_Non_Move_Object(Non_Move_Object& nm_object, const int& x_pos, const int& y_pos, HBITMAP bitmap) {
	nm_object.Set_Object_Bitmap(bitmap);
	nm_object.Set_Crash_Width(nm_object.Get_Object_Image_Size().bmWidth);
	Reset_Object(nm_object, x_pos, y_pos, nm_object.Get_Object_Image_Size().bmWidth, nm_object.Get_Object_Image_Size().bmHeight);
}

Move_Object::~Move_Object() {
	for (int index = 0; index < 20; index++)
		Delete_Class<Hitting_Range>(&hit_range[index]);
}

const int& Move_Object::Get_Status() const {
	return status;
}

const int& Move_Object::Get_Direction() const {
	return direction;
}

const int& Move_Object::Get_Ani_Count() const {
	return animaition_count;
}

const Hitting_Range& Move_Object::Get_Hit_Range_Const(const int& index) const {
	return *hit_range[index];
}

Hitting_Range& Move_Object::Get_Hit_Range(const int& index) const {
	return *hit_range[index];
}

void Move_Object::Set_Status(const int& status) {
	this->status = status;
}

void Move_Object::Set_Direction(const int& direction) {
	this->direction = direction;
}

void Move_Object::Set_Ani_Count(const int& ani_count) {
	animaition_count = ani_count;
}

void Move_Object::Set_Hit_Range(const int& index, const RECT hit_rect, const int& owner) {
	hit_range[index] = Create_Class<Hitting_Range>();
	Reset_Hitting_Range(*hit_range[index], hit_rect, owner);
}

void Reset_Move_Object(Move_Object& m_object, const int& x_pos, const int& y_pos, const int& width, const int& height) {
	Reset_Object(m_object, x_pos, y_pos, width, height);
	m_object.Set_Status(Player_Status::Stop);
	m_object.Set_Direction(Object_Direction::Down);
	m_object.Set_Ani_Count(0);
}

