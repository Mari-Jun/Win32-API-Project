#include <Windows.h>
#include <math.h>
#include "Source.h"
#include "Object_Move.h"

bool Crash_Check_Object(Move_Object& object, const Object& obj, const int& move_x, const int& move_y) {
	if (object.Get_XPos() + object.Get_Crash_Width() + move_x > obj.Get_XPos() && object.Get_XPos() + move_x < obj.Get_XPos() + obj.Get_Crash_Width() &&
		object.Get_YPos() + object.Get_Height() + move_y > obj.Get_YPos() + obj.Get_Height() - obj.Get_Crash_Height() &&
		object.Get_YPos() + object.Get_Height() - object.Get_Crash_Height() + move_y < obj.Get_YPos() + obj.Get_Height())
		return false;
	return true;
}

bool Crash_Check_Village_Map(Move_Object& object, const Map_Village& map_v, const int& move_x, const int& move_y) {
	for (int index = 0; index < 10; index++) {
		if (&map_v.Get_NM_Object(index) != NULL && !Crash_Check_Object(object, map_v.Get_NM_Object(index), move_x, move_y))
			return false;
	}

	return true;
}

