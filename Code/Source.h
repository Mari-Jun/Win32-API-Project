#pragma once
#include <windows.h>

template <typename T>
T* Create_Class() {
	T* t = new T();

	return t;
}

template<typename T>
void Delete_Class(T** t) {
	if (*t != NULL) {
		delete* t;
		*t = NULL;
	}
}

enum Object_Direction {
	Up, UpRight, Right, DownRight, Down, DownLeft, Left, UpLeft
};

enum Timer_Name {
	Player_Move_Timer = 40
};