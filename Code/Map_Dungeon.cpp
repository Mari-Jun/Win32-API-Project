#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Map_Dungeon.h"
#include "Object_Main.h"
#include "Object_Player.h"
#include "Object_Enemy.h"
#include "Object_Info.h"
#include "Camera.h"

Map_Dungeon::~Map_Dungeon() {
	
}

const int& Map_Dungeon::Get_Dungeon_Type() const {
	return dungeon_type;
}

void Map_Dungeon::Set_Dungeon_Type(const int& dungeon_type) {
	this->dungeon_type = dungeon_type;
}

const Enemy& Map_Dungeon::Get_Enemy_Const(const int& index) const {
	return *enemy[index];
}

Enemy& Map_Dungeon::Get_Enemy(const int& index) const {
	return *enemy[index];
}

void Map_Dungeon::Set_Dungeon1(File& file) {

	/*Texture*/
	Create_Texture(Dungeon1_Texture::D1_Grass, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\grass1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon1_Texture::D2_Grass, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\grass2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon1_Texture::D1_Rock, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\rock1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	/*Object*/
	Create_NM_Object(Dungeon1_Object::D1_Left_Rock1);
	Reset_Object(Get_NM_Object(Dungeon1_Object::D1_Left_Rock1), 0, 1120, 80, 1520);
	Get_NM_Object(Dungeon1_Object::D1_Left_Rock1).Set_Crash_Width(80);
	Get_NM_Object(Dungeon1_Object::D1_Left_Rock1).Set_Crash_Height(1520);
	Create_NM_Object(Dungeon1_Object::D1_Left_Rock2);
	Reset_Object(Get_NM_Object(Dungeon1_Object::D1_Left_Rock2), 0, 2640, 320, 320);
	Get_NM_Object(Dungeon1_Object::D1_Left_Rock2).Set_Crash_Width(320);
	Get_NM_Object(Dungeon1_Object::D1_Left_Rock2).Set_Crash_Height(320);
	Create_NM_Object(Dungeon1_Object::D1_Right_Rock1);
	Reset_Object(Get_NM_Object(Dungeon1_Object::D1_Right_Rock1), 2800, 1120, 80, 1520);
	Get_NM_Object(Dungeon1_Object::D1_Right_Rock1).Set_Crash_Width(80);
	Get_NM_Object(Dungeon1_Object::D1_Right_Rock1).Set_Crash_Height(1520);
	Create_NM_Object(Dungeon1_Object::D1_Right_Rock2);
	Reset_Object(Get_NM_Object(Dungeon1_Object::D1_Right_Rock2), 800, 2640, 320, 320);
	Get_NM_Object(Dungeon1_Object::D1_Right_Rock2).Set_Crash_Width(2080);
	Get_NM_Object(Dungeon1_Object::D1_Right_Rock2).Set_Crash_Height(320);
	Create_NM_Object(Dungeon1_Object::D1_Bottom_Rock);
	Reset_Object(Get_NM_Object(Dungeon1_Object::D1_Bottom_Rock), 0, Get_Map_Rect().bottom - 320, Get_Map_Rect().right, 320);
	Get_NM_Object(Dungeon1_Object::D1_Bottom_Rock).Set_Crash_Width(Get_Map_Rect().right);
	Get_NM_Object(Dungeon1_Object::D1_Bottom_Rock).Set_Crash_Height(320);

	/*Create_NM_Object(Dungeon1_Object::D1_Tree1);
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1), 80, 1020, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(Dungeon1_Object::D1_Tree1).Set_Height(400);
	Get_NM_Object(Dungeon1_Object::D1_Tree1).Set_Crash_Width(2720);
	Get_NM_Object(Dungeon1_Object::D1_Tree1).Set_Crash_Height(300);*/


	for (int index = Dungeon1_Object::D1_Tree1 + 1; index < 60; index++)
		Create_NM_Object(index);

	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 1), 150, 350, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 2), 450, 770, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 3), 2860, 350, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 4), 3150, 850, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 5), 3630, 1230, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 6), 1050, 2120, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 7), 1920, 1860, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 8), 1390, 3350, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 9), 3500, 3150, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 10), 1050, 250, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 11), 2220, 150, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 12), 3550, 260, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 13), 3320, 1840, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 14), 2500, 3100, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 15), 450, 3150, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 16), 370, 1900, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 17), 2400, 2300, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 18), 450, 1650, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1 + 19), 1400, 2900, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	for (int index = Dungeon1_Object::D1_Tree1 + 1; index < Dungeon1_Object::D1_Tree2; index++)
		Get_NM_Object(index).Set_Crash_Height(80);

	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 1), 1300, 1620, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 2), 2500, 1760, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 3), 1000, 3150, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 4), 3020, 2850, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 5), 3530, 2470, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 6), 3180, 1480, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 7), 3230, 170, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 8), 1800, 600, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree2 + 9), 700, 100, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));


	for (int index = Dungeon1_Object::D1_Tree2 + 1; index < 35; index++)
		Get_NM_Object(index).Set_Crash_Height(100);

	/*Enemy*/

	POINT enemy_pos[50];

	enemy_pos[0] = { 250,650 };		enemy_pos[1] = { 1000,150 };		enemy_pos[2] = { 1000, 750 };		enemy_pos[3] = { 2450, 650 };		enemy_pos[4] = { 3300, 650 };
	enemy_pos[5] = { 3620, 1600 };	enemy_pos[6] = { 3100, 2700 };		enemy_pos[17] = { 2950, 3300 };		enemy_pos[8] = { 800, 3410 };		enemy_pos[9] = { 600, 2230 };
	enemy_pos[10] = { 2000, 850 };	enemy_pos[11] = { 2500, 200 };		enemy_pos[12] = { 3100, 600 };		enemy_pos[13] = { 3270, 1480 };		enemy_pos[14] = { 3630, 2470 };
	enemy_pos[15] = { 3100, 2860 };	enemy_pos[16] = { 1800, 3100 };		enemy_pos[17] = { 800, 3000 };		enemy_pos[18] = { 830, 1700 };		enemy_pos[19] = { 1500, 2300 };
	enemy_pos[20] = { 3750, 950 };	enemy_pos[21] = { 3750, 1850 };		enemy_pos[22] = { 3070, 3300 };		enemy_pos[23] = { 800, 2000 };		enemy_pos[24] = { 1800, 2300 };

	/*for (int index = 0; index < 10; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Bird);
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, enemy[index]->Get_Motion_Size().bmWidth, enemy[index]->Get_Motion_Size().bmHeight, 8);
	}

	for (int index = 10; index < 20; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Zadrom);
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, enemy[index]->Get_Motion_Size().bmWidth, enemy[index]->Get_Motion_Size().bmHeight, 6);
	}

	for (int index = 20; index < 25; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Tolpi);
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, enemy[index]->Get_Motion_Size().bmWidth, enemy[index]->Get_Motion_Size().bmHeight, 6);
	}*/

	enemy[50] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[50], file, Enemy_Type::Dark_Flower);
	Reset_Move_Object(*enemy[50], 1900, 1400, enemy[50]->Get_Motion_Size().bmWidth, enemy[50]->Get_Motion_Size().bmHeight, 0);
}

void Map_Dungeon::Kill_Enemy(const int& index) {
	Delete_Class<Enemy>(&enemy[index]);
}

void Reset_Dungeon_Map(HDC hdc, Map_Dungeon& map_d, File& file, const int& dungeon_type) {
	map_d.Set_Dungeon_Type(dungeon_type);
	switch (map_d.Get_Dungeon_Type())
	{
	case Map_Type::Dungeon1:
		map_d.Set_Map_Rect(0, 0, 4000, 4000);
		map_d.Set_Dungeon1(file);
		break;
	case Map_Type::Dungeon2:
		map_d.Set_Map_Rect(0, 0, 4000, 4000);
		break;
	default:
		break;
	}
	map_d.Set_Map_Size_Bit(hdc);

}

void Paint_Dungeon_Map_Texture(HDC hdc, HDC bitdc, const Map_Dungeon& map_d, const Camera& camera, const RECT c_rect) {
	switch (map_d.Get_Dungeon_Type())
	{
	case Map_Type::Dungeon1:
		SelectObject(bitdc, map_d.Get_Texture(Dungeon1_Texture::D1_Rock));
	
		//좌우 돌
		for (int y = 1120; y < map_d.Get_Map_Rect().bottom - 1360; y += 80) {
			Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 0, y, 80, 80);
			Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, map_d.Get_Map_Rect().right - 1200, y, 80, 80);
		}
		//입체돌
		for (int x = 0; x < map_d.Get_Map_Rect().right - 1120; x += 80) {
			for (int y = map_d.Get_Map_Rect().bottom - 1360; y < map_d.Get_Map_Rect().bottom - 1040; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}
		//제일 밑 돌
		for (int x = 0; x < map_d.Get_Map_Rect().right; x += 80) {
			for (int y = map_d.Get_Map_Rect().bottom - 320; y < map_d.Get_Map_Rect().bottom; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}


		SelectObject(bitdc, map_d.Get_Texture(Dungeon1_Texture::D1_Grass));

		for (int x = 0; x < map_d.Get_Map_Rect().right; x += 80) {
			for (int y = 0; y < 1120; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
			for (int y = map_d.Get_Map_Rect().bottom - 1040; y < map_d.Get_Map_Rect().bottom - 320; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}
		for (int y = 1120; y < map_d.Get_Map_Rect().bottom - 1040; y += 80) {
			for (int x = map_d.Get_Map_Rect().right - 1120; x < map_d.Get_Map_Rect().right; x += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}

		SelectObject(bitdc, map_d.Get_Texture(Dungeon1_Texture::D2_Grass));
		for (int x = 80; x < map_d.Get_Map_Rect().right - 1200; x += 80) {
			for (int y = 1120; y < map_d.Get_Map_Rect().bottom - 1360; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}
		for (int x = 320; x < 800; x += 80)
			for (int y = map_d.Get_Map_Rect().bottom - 1360; y < map_d.Get_Map_Rect().bottom - 1040; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		break;
	default:
		break;
	}
	
}

void Paint_Dungeon_Map(HDC hdc, HDC bitdc, const Player& player, const Map_Dungeon& map_d, const File& file, const Camera& camera, const RECT c_rect) {
	SelectObject(hdc, map_d.Get_Map_Size_Bitmap());
	FillRect(hdc, &map_d.Get_Map_Rect(), WHITE_BRUSH);

	Paint_Dungeon_Map_Texture(hdc, bitdc, map_d, camera, c_rect);

	int y_pos = 0;
	for (y_pos = camera.Get_Cam_Top(); y_pos < camera.Get_Cam_Top() + c_rect.bottom + c_rect.bottom / 2; y_pos++) {

		//오브젝트 그리기
		for (int index = 0; index < 60; index++) {
			if (&map_d.Get_NM_Object(index) != NULL && y_pos == map_d.Get_NM_Object(index).Get_YPos() + map_d.Get_NM_Object(index).Get_Height()) {
				SelectObject(bitdc, map_d.Get_NM_Object(index).Get_Object_Bitmap());

				Paint_TransparentBlt_Camera_In(hdc, bitdc, camera, c_rect, map_d.Get_NM_Object(index).Get_XPos(), map_d.Get_NM_Object(index).Get_YPos(),
					map_d.Get_NM_Object(index).Get_Object_Image_Size().bmWidth, map_d.Get_NM_Object(index).Get_Object_Image_Size().bmHeight, RGB(150, 150, 150));

				switch (map_d.Get_Dungeon_Type())
				{
				case Map_Type::Dungeon1:
					switch (index)
					{
					case Dungeon1_Object::D1_Tree1:
						for (int y = 0; y < 3; y++) {
							for (int x = map_d.Get_NM_Object(index).Get_XPos() + 80 * (y % 2); x < 2720; x += 160)
								Paint_TransparentBlt_Camera_In(hdc, bitdc, camera, c_rect, x, map_d.Get_NM_Object(index).Get_YPos() + 100 * y,
									map_d.Get_NM_Object(index).Get_Object_Image_Size().bmWidth, map_d.Get_NM_Object(index).Get_Object_Image_Size().bmHeight, RGB(150, 150, 150));
						}
						break;
					default:
						break;
					}
					break;
				default:
					break;
				}				
			}
		}

		//적 그리기
		for (int index = 0; index < 53; index++) {
			if (&map_d.Get_Enemy_Const(index) != NULL && y_pos == map_d.Get_Enemy_Const(index).Get_YPos() + map_d.Get_Enemy_Const(index).Get_Height())
				Paint_Enemy(hdc, bitdc, file, map_d.Get_Enemy_Const(index), camera, c_rect);
		}	

		if (&player != NULL && y_pos == player.Get_YPos() + player.Get_Height())
			Paint_Player(hdc, bitdc, player);
	}
}

bool Check_Dungeon_Clear(const Map_Dungeon& map_d) {
	for (int index = 50; index < 53; index++) {
		if (&map_d.Get_Enemy_Const(index) != NULL)
			return false;
	}
	return true;
}