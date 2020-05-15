#pragma once

class Player;
class Map;

class Camera {
public:
	const int& Get_Cam_Top() const;
	const int& Get_Cam_Left() const;

	void Set_Cam_Top(const int& top);
	void Set_Cam_Left(const int& left);

private:
	int cam_top;
	int cam_left;
	HBITMAP camera_bit;
};

void Reset_Camera(Camera& camera, RECT c_rect);
void Move_Camera(Camera& camera, Player& player, Map& map, RECT c_rect);