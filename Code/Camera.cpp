#include <windows.h>
#include "Source.h"
#include "Camera.h"
#include "Object_Main.h"
#include "Map_Main.h"

const int& Camera::Get_Cam_Top() const {
	return cam_top;
}

const int& Camera::Get_Cam_Left() const {
	return cam_left;
}

void Camera::Set_Cam_Top(const int& top) {
	cam_top = top;
}

void Camera::Set_Cam_Left(const int& left) {
	cam_left = left;
}

void Reset_Camera(Camera& camera, RECT c_rect) {
	camera.Set_Cam_Top(c_rect.top);
	camera.Set_Cam_Left(c_rect.left);
}

void Move_Camera(Camera& camera, Move_Object& player, Map& map, RECT c_rect) {
	if (player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height() / 2 - c_rect.bottom / 2 >= map.Get_Map_Rect().top &&
		player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height() / 2 + c_rect.bottom / 2 <= map.Get_Map_Rect().bottom)
		camera.Set_Cam_Top(player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height() / 2 - c_rect.bottom / 2);
	else if (player.Get_YPos() + player.Get_Height() - player.Get_Crash_Height() / 2 - c_rect.bottom / 2 < map.Get_Map_Rect().top)
		camera.Set_Cam_Top(c_rect.top);
	else
		camera.Set_Cam_Top(map.Get_Map_Rect().bottom - c_rect.bottom);

	if (player.Get_XPos() + player.Get_Crash_Width() / 2 - c_rect.right / 2 >= map.Get_Map_Rect().left
		&& player.Get_XPos() + player.Get_Crash_Width() / 2 + c_rect.right / 2 <= map.Get_Map_Rect().right)
		camera.Set_Cam_Left(player.Get_XPos() + player.Get_Crash_Width() / 2 - c_rect.right / 2);
	else if (player.Get_XPos() + player.Get_Crash_Width() / 2 - c_rect.right / 2 < map.Get_Map_Rect().left)
		camera.Set_Cam_Left(c_rect.left);
	else
		camera.Set_Cam_Left(map.Get_Map_Rect().right - c_rect.right);
}