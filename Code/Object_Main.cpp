#include <windows.h>
#include "Object_Main.h"
#include "Object_Info.h"

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

void Reset_Object(Object& object, const int& x_pos, const int& y_pos, const int& width, const int& height) {
	object.Set_XPos(x_pos);
	object.Set_YPos(y_pos);
	object.Set_Width(width);
	object.Set_Height(height);
}
