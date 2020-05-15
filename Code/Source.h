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
	Right, UpRight, Up, UpLeft, Left, DownLeft, Down, DownRight
};

enum Object_Status {
	Stop, Move, Run
};

enum Timer_Name {
	Player_Move_Timer = 40
};