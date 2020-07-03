#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Map_Dungeon.h"
#include "Object_Main.h"
#include "Object_Player.h"
#include "Object_Enemy.h"
#include "Enemy_Bitmap.h"
#include "Object_Info.h"
#include "Camera.h"
#include "Sound.h"


Map_Dungeon::~Map_Dungeon() {
	for (int index = 0; index < 53; index++)
		Delete_Class<Enemy>(&enemy[index]);
	Delete_Class<Enemy_Bitmap>(&e_bitmap);
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

const Enemy_Bitmap& Map_Dungeon::Get_Enemy_Bitmap_Const() const {
	return *e_bitmap;
}

Enemy_Bitmap& Map_Dungeon::Get_Enemy_Bitmap() const {
	return *e_bitmap;
}

Sound& Map_Dungeon::Get_Dungeon_Sound() const {
	return *dungeon_sound;
}

void Map_Dungeon::Set_Dungeon1(const File& file) {

	/*Texture*/
	Create_Texture(Dungeon_Texture::Texture1, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\grass1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture2, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\grass2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture3, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\rock1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

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

	Create_NM_Object(Dungeon1_Object::D1_Tree1);
	Reset_Non_Move_Object(Get_NM_Object(Dungeon1_Object::D1_Tree1), 80, 1020, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon1\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Get_NM_Object(Dungeon1_Object::D1_Tree1).Set_Height(400);
	Get_NM_Object(Dungeon1_Object::D1_Tree1).Set_Crash_Width(2720);
	Get_NM_Object(Dungeon1_Object::D1_Tree1).Set_Crash_Height(300);


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

	for (int index = 0; index < 10; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Bird);
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 8);
	}

	for (int index = 10; index < 20; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Zadrom);
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 6);
	}

	for (int index = 20; index < 25; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Tolpi);
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 6);
	}

	enemy[50] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[50], file, Enemy_Type::Dark_Flower);
	Reset_Move_Object(*enemy[50], 1900, 1400, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmHeight, 0);
}

void Map_Dungeon::Set_Dungeon2(const File& file) {

	/*Texture*/
	Create_Texture(Dungeon_Texture::Texture1, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon2\\texture1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture2, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon2\\texture2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture3, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon2\\texture3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	/*Object*/
	for (int i = 0; i < 8; i++) {
		Create_NM_Object(Dungeon2_Object::D2_Wall + i);
		Reset_Object(Get_NM_Object(Dungeon2_Object::D2_Wall + i), 880 + 1000 * i, 0 + 200 * (i % 2), 240, 800);
		Get_NM_Object(Dungeon2_Object::D2_Wall + i).Set_Crash_Width(240);
		Get_NM_Object(Dungeon2_Object::D2_Wall + i).Set_Crash_Height(800);
	}

	for (int i = 0; i < 2; i++) {
		Create_NM_Object(Dungeon2_Object::D2_Wall + 8 + i);
		Reset_Object(Get_NM_Object(Dungeon2_Object::D2_Wall + 8 + i), 8760, 0 + 520 * i, 240, 480);
		Get_NM_Object(Dungeon2_Object::D2_Wall + 8 + i).Set_Crash_Width(240);
		Get_NM_Object(Dungeon2_Object::D2_Wall + 8 + i).Set_Crash_Height(480);
	}

	POINT enemy_pos[50];	

	for (int index = 0; index < 9; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Heke);
		enemy_pos[index] = { 300 + index * 1000 , 500 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 8);
	}
	
	for (int index = 10; index < 19; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Baocar);
		enemy_pos[index] = { 650 + (index - 10) * 1000 , 600 - (index % 2) * 100 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 6);
	}
	
	for (int index = 20; index < 28; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Huba);
		enemy_pos[index] = { 950 + (index - 20) * 1000 , ((index + 1) % 2) * 850 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 4);
	}
	
	for (int index = 30; index < 38; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Huba2);
		enemy_pos[index] = { 1050 + (index - 30) * 1000 , -100 + ((index + 1) % 2) * 800 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 4);
	}

	enemy[50] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[50], file, Enemy_Type::Grave);
	Reset_Move_Object(*enemy[50], 9500, 500, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmHeight, 8);
	
}

void Map_Dungeon::Set_Dungeon3(const File& file) {

	/*Texture*/
	Create_Texture(Dungeon_Texture::Texture1, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon3\\texture1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture2, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon3\\texture2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture3, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon3\\texture3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	/*Object*/

	for (int i = 0; i < 2; i++) {
		Create_NM_Object(Dungeon3_Object::D3_Wall + i);
		Reset_Object(Get_NM_Object(Dungeon3_Object::D3_Wall + i), 400, 400 + 3760 * i, 640, 640);
		Get_NM_Object(Dungeon3_Object::D3_Wall + i).Set_Crash_Width(640);
		Get_NM_Object(Dungeon3_Object::D3_Wall + i).Set_Crash_Height(640);
	}

	for (int i = 0; i < 4; i++) {
		Create_NM_Object(Dungeon3_Object::D3_Wall + 2 + i);
		Reset_Object(Get_NM_Object(Dungeon3_Object::D3_Wall + 2 + i), 400 + 480 * (i % 2), 1440 + 1680 * (i / 2), 160, 640);
		Get_NM_Object(Dungeon3_Object::D3_Wall + 2 + i).Set_Crash_Width(160);
		Get_NM_Object(Dungeon3_Object::D3_Wall + 2 + i).Set_Crash_Height(640);
	}

	Create_NM_Object(Dungeon3_Object::D3_Wall + 7);
	Reset_Object(Get_NM_Object(Dungeon3_Object::D3_Wall + 7), 240, 2480, 960, 240);
	Get_NM_Object(Dungeon3_Object::D3_Wall + 7).Set_Crash_Width(960);
	Get_NM_Object(Dungeon3_Object::D3_Wall + 7).Set_Crash_Height(240);

	for (int i = 0; i < 2; i++) {
		Create_NM_Object(Dungeon3_Object::D3_Wall + 8 + i);
		Reset_Object(Get_NM_Object(Dungeon3_Object::D3_Wall + 8 + i), 0 + i * 240, 5200 + 320 * i, 1280, 160);
		Get_NM_Object(Dungeon3_Object::D3_Wall + 8 + i).Set_Crash_Width(1280);
		Get_NM_Object(Dungeon3_Object::D3_Wall + 8 + i).Set_Crash_Height(160);
	}

	/*Enemy*/

	POINT enemy_pos[50];

	for (int index = 0; index < 12; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Riff);

		if (index < 2)
			enemy_pos[index] = { 200 + (index % 2) * 1000 , 200 };
		else if (index >= 2 && index < 4)
			enemy_pos[index] = { 200 + ((index - 2) % 2) * 1000 , 700 };
		else if (index >= 4 && index < 6)
			enemy_pos[index] = { 200 + ((index - 4) % 2) * 1000 , 1700 };
		else if (index >= 6 && index < 8)
			enemy_pos[index] = { 200 + ((index - 6) % 2) * 1000 , 3400 };
		else if (index >= 8 && index < 10)
			enemy_pos[index] = { 200 + ((index - 8) % 2) * 1000 , 4400 };
		else
			enemy_pos[index] = { 200 + ((index - 10) % 2) * 1000 , 4900 };

		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 10);
	}

	for (int index = 15; index < 25; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Sama);
		if (index < 19)
			enemy_pos[index] = { 500 + ((index - 15) % 2) * 440, 1100 + ((index - 15) / 2) * 1000 };
		else if (index >= 19 && index < 23)
			enemy_pos[index] = { 500 + ((index - 19) % 2) * 440, 2800 + ((index - 19) / 2) * 1000 };
		else
			enemy_pos[index] = { 720, 1600 + (index - 23) * 1350 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 10);
	}

	for (int index = 25; index < 29; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Mobre);
		enemy_pos[index] = { 720, 1200 + (index - 25) * 900 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 5);
	}

	for (int index = 30; index < 38; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Selnarg);
		if (index < 34)
			enemy_pos[index] = { 200 + ((index - 30) % 2) * 1000 , 1200 + ((index - 30) / 2) * 900 };
		else
			enemy_pos[index] = { 200 + ((index - 30) % 2) * 1000 , 3000 + ((index - 34) / 2) * 900 };
		
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 7);
	}

	enemy[50] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[50], file, Enemy_Type::Zeffel);
	Reset_Move_Object(*enemy[50], 700, 6400, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmHeight, 12);
}


void Map_Dungeon::Set_Dungeon4(const File& file) {

	/*Texture*/
	Create_Texture(Dungeon_Texture::Texture1, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon4\\texture1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture2, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon4\\texture2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture3, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon4\\texture3.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	/*Object*/
	for (int i = 0; i < 10; i++) 
		Create_NM_Object(Dungeon4_Object::D4_Wall + i);

	for (int i = 0; i < 5; i++) {
		Reset_Object(Get_NM_Object(Dungeon4_Object::D4_Wall + i), 400 + i * 640, 400 - (i % 2) * 400, 240, 3360 - 1280 * (i / 2) - 240 * (i % 2));
		Get_NM_Object(Dungeon4_Object::D4_Wall + i).Set_Crash_Width(240);
		Get_NM_Object(Dungeon4_Object::D4_Wall + i).Set_Crash_Height(3360 - 1280 * (i / 2));
	}

	for (int i = 5; i < 10; i++) {
		Reset_Object(Get_NM_Object(Dungeon4_Object::D4_Wall + i), 640 + (i - 5) * 640, 3520 - (i - 5) * 640, 3520 - 1280 * ((i - 4) / 2) + 240 * ((i - 1) % 2), 240);
		Get_NM_Object(Dungeon4_Object::D4_Wall + i).Set_Crash_Width(3520 - 1280 * ((i - 4) / 2) + 240 * ((i - 1) % 2));
		Get_NM_Object(Dungeon4_Object::D4_Wall + i).Set_Crash_Height(240);
	}

	/*Enemy*/

	POINT enemy_pos[50];

	enemy_pos[0] = { 250,1250 };	enemy_pos[1] = { 250,2250 };		enemy_pos[2] = { 900, 1250 };		enemy_pos[3] = { 900, 2550 };		enemy_pos[4] = { 1540, 1750 };
	enemy_pos[5] = { 2180, 1250 };	enemy_pos[6] = { 3820, 300 };		enemy_pos[7] = { 1250, 3900 };		enemy_pos[8] = { 2250, 3900 };		enemy_pos[9] = { 1600, 3240 };
	enemy_pos[10] = { 2250, 3240 };	enemy_pos[11] = { 2250, 2580 };		enemy_pos[12] = { 2500, 1940 };		enemy_pos[13] = { 3900, 1350 };	

	for (int index = 0; index < 14; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Zarue);
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 9);
	}

	for (int index = 15; index < 27; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Normous);
		if (index >= 15 && index < 19)
			enemy_pos[index] = { 180 + (index - 15) * 640 , 2080 - ((index - 15) / 2) * 640 };
		else if (index >= 19 && index < 21)
			enemy_pos[index] = { 480 + (index - 19) * 1280 , 150 };
		else if (index >= 21 && index < 23)
			enemy_pos[index] = { 3950 , 1650 + (index - 21) * 1280 };
		else
			enemy_pos[index] = { 2080 + ((index - 23) / 2) * 640, 3850 - (index - 23) * 640 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 0);
	}

	for (int index = 30; index < 40; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Venueba);
		if (index < 35)
			enemy_pos[index] = { 150 + (index - 30) * 640 , 800 };
		else
			enemy_pos[index] = { 3160 , 1400 + (index - 35) * 640 };


		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 6);
	}

	for (int index = 40; index < 45; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Diphtheloyd);
		enemy_pos[index] = { 150 + (index - 40) * 640 , Get_Map_Rect().bottom - 250 - (index - 40) * 640 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 10);
	}
	

	enemy[50] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[50], file, Enemy_Type::Vagullion);
	Reset_Move_Object(*enemy[50], 3500, 500, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmHeight, 6);
}


void Map_Dungeon::Set_Dungeon5(const File& file) {

	/*Texture*/
	Create_Texture(Dungeon_Texture::Texture1, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\texture1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Create_Texture(Dungeon_Texture::Texture2, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\texture2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	/*Object*/


	for (int index = Dungeon5_Object::D5_Tree1; index < Dungeon5_Object::D5_Tree2 + 8; index++)
		Create_NM_Object(index);

	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 1), 150, 400, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 2), 450, 700, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 3), 750, 800, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 4), 1000, 100, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 5), 1250, 450, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 6), 1500, 350, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 7), 1750, 850, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 8), 2000, 700, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 9), 2250, 400, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 10), 2500, 200, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree1 + 11), 2750, 800, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree1.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree2), 300, 100, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree2 + 1), 850, 200, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree2 + 2), 1300, 800, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree2 + 3), 3000, 350, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree2 + 4), 3200, 750, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree2 + 5), 3400, 480, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree2 + 6), 3600, 180, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	Reset_Non_Move_Object(Get_NM_Object(Dungeon5_Object::D5_Tree2 + 7), 3800, 600, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon5\\Tree2.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));

	for (int index = Dungeon5_Object::D5_Tree1; index < Dungeon5_Object::D5_Tree2 + 8; index++)
		Get_NM_Object(index).Set_Crash_Height(40);

	/*Enemy*/

	POINT enemy_pos[50];

	for (int index = 0; index < 5; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Alnada);
		enemy_pos[index] = { 950 + index * 500, 300 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 8);
	}

	for (int index = 5; index < 10; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Magiste);
		enemy_pos[index] = { 1000 + (index - 5) * 500, 600 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 8);
	}

	for (int index = 10; index < 15; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Selnade);
		enemy_pos[index] = { 500 + (index - 10) * 350, 700 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 8);
	}

	for (int index = 15; index < 20; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Seean);
		enemy_pos[index] = { 800 + (index - 15) * 300, 100 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 8);
	}

	for (int index = 20; index < 25; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Sizarian);
		enemy_pos[index] = { 800 + (index - 20) * 300, 700 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 8);
	}

	for (int index = 25; index < 30; index++) {
		enemy[index] = Create_Class<Enemy>();
		Reset_Enemy(*enemy[index], file, Enemy_Type::Jestona);
		enemy_pos[index] = { 1000 + (index - 25) * 400, 400 };
		Reset_Move_Object(*enemy[index], enemy_pos[index].x, enemy_pos[index].y, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[index]->Get_Enemy_Type()).bmHeight, 8);
	}

	enemy[50] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[50], file, Enemy_Type::Liagty1);
	Reset_Move_Object(*enemy[50], 3700, 500, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmHeight, 10);
	enemy[51] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[51], file, Enemy_Type::Liagty2);
	Reset_Move_Object(*enemy[51], 3700, 300, e_bitmap->Get_Motion_Size(enemy[51]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[51]->Get_Enemy_Type()).bmHeight, 10);
	enemy[52] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[52], file, Enemy_Type::Liagty3);
	Reset_Move_Object(*enemy[52], 3700, 700, e_bitmap->Get_Motion_Size(enemy[52]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[52]->Get_Enemy_Type()).bmHeight, 10);
}

void Map_Dungeon::Set_Dungeon6(const File& file) {

	/*Texture*/
	Create_Texture(Dungeon_Texture::Texture1, (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Map\\Dungeon6\\texture.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE));
	/*Enemy*/

	enemy[50] = Create_Class<Enemy>();
	Reset_Enemy(*enemy[50], file, Enemy_Type::Dularn);
	Reset_Move_Object(*enemy[50], 500, 500,e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmWidth, e_bitmap->Get_Motion_Size(enemy[50]->Get_Enemy_Type()).bmHeight,10);
}

void Map_Dungeon::Set_Enemy_Bitmap(const File& file) {
	e_bitmap = Create_Class<Enemy_Bitmap>();
	Reset_Enemy_Bitmap(*e_bitmap, file, Get_Dungeon_Type());
}

void Map_Dungeon::Set_Dungeon_Sound() {
	dungeon_sound = Create_Class<Sound>();
	Reset_Sound(*dungeon_sound, Sound_Type::Sound_Map_Type, dungeon_type);
}

void Map_Dungeon::Kill_Enemy(const int& index) {
	Delete_Class<Enemy>(&enemy[index]);
}

void Reset_Dungeon_Map(HDC hdc, Map_Dungeon& map_d, File& file, const int& dungeon_type) {
	map_d.Set_Dungeon_Type(dungeon_type);
	map_d.Set_Enemy_Bitmap(file);
	map_d.Set_Dungeon_Sound();
	switch (map_d.Get_Dungeon_Type())
	{
	case Map_Type::Dungeon1:
		map_d.Set_Map_Rect(0, 0, 4000, 4000);
		map_d.Set_Dungeon1(file);
		break;
	case Map_Type::Dungeon2:
		map_d.Set_Map_Rect(0, 0, 10000, 1000);
		map_d.Set_Dungeon2(file);
		break;
	case Map_Type::Dungeon3:
		map_d.Set_Map_Rect(0, 0, 1440, 7040);
		map_d.Set_Dungeon3(file);
		break;
	case Map_Type::Dungeon4:
		map_d.Set_Map_Rect(0, 0, 4160, 4160);
		map_d.Set_Dungeon4(file);
		break;
	case Map_Type::Dungeon5:
		map_d.Set_Map_Rect(0, 0, 4000, 1000);
		map_d.Set_Dungeon5(file);
		break;
	case Map_Type::Dungeon6:
		map_d.Set_Map_Rect(0, 0, 1280, 1000);
		map_d.Set_Dungeon6(file);
		break;
	default:
		break;
	}
	map_d.Set_Map_Size_Bit(hdc);

	//음악 재생
	map_d.Get_Dungeon_Sound().AllSoundStop();
	map_d.Get_Dungeon_Sound().Play_Sound(7 + dungeon_type);
}

void Paint_Dungeon_Map_Texture(HDC hdc, HDC bitdc, const Map_Dungeon& map_d, const Camera& camera, const RECT c_rect) {
	switch (map_d.Get_Dungeon_Type())
	{
		//임시 꼭 바꿔라
	case Map_Type::Dungeon1:
		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture3));
	
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

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture1));

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

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture2));
		for (int x = 80; x < map_d.Get_Map_Rect().right - 1200; x += 80) {
			for (int y = 1120; y < map_d.Get_Map_Rect().bottom - 1360; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}
		for (int x = 320; x < 800; x += 80)
			for (int y = map_d.Get_Map_Rect().bottom - 1360; y < map_d.Get_Map_Rect().bottom - 1040; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		break;
	case Map_Type::Dungeon2:

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture2));
		for (int x = 0; x < 9000; x += 80) {
			for (int y = 0; y < 1000; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture1));
		for (int width = 0; width < 3; width++) {
			for (int x = 880; x < 8000; x += 1000) {
				if ((x / 1000) % 2 == 0) {
					for (int y = 0; y < 800; y += 80)
						Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x + width * 80, y, 80, 80);
				}
				else {
					for (int y = 200; y < 1000; y += 80)
						Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x + width * 80, y, 80, 80);
				}
			}
		}
		for (int x = 8760; x < 9000; x += 80) {
			for (int y = 0; y < 480; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
			for (int y = 520; y < 1000; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture3));
		
		for (int x = 9000; x < 10000; x += 80) {
			for (int y = 0; y < 1000; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		}
		break;
	case Map_Type::Dungeon3:

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture1));

		for (int x = 0; x < 1440; x += 80)
			for (int y = 0; y < 5520; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture3));

		for (int x = 0; x < 1440; x += 80)
			for (int y = 5520; y < 7040; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture2));

		for (int x = 400; x < 1040; x+=80) 
			for (int y = 400; y < 1040; y+=80) {
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y + 3760, 80, 80);
			}

		for (int x = 400; x < 560; x += 80) 
			for (int y = 1440; y < 2080; y += 80) {
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x + 480, y, 80, 80);
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y + 1680, 80, 80);
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x + 480, y + 1680, 80, 80);
			}

		for (int x = 240; x < 1200; x += 80) 
			for (int y = 2480; y < 2720; y += 80) 
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);

		for (int x = 0; x < 1280; x += 80) 
			for (int y = 5200; y < 5360; y += 80) {
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x + 160, y + 320, 80, 80);
			}
		break;
	case Map_Type::Dungeon4:

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture1));
		for (int x = 0; x < map_d.Get_Map_Rect().right - 960; x += 80)
			for (int y = 0; y < map_d.Get_Map_Rect().bottom; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);

		for (int x = map_d.Get_Map_Rect().right - 960; x < map_d.Get_Map_Rect().right; x += 80)
			for (int y = 960; y < map_d.Get_Map_Rect().bottom; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);


		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture2));

		for (int x = map_d.Get_Map_Rect().right - 960; x < map_d.Get_Map_Rect().right; x += 80)
			for (int y = 0; y < 960; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);


		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture3));

		for (int i = 0; i < 5; i++) {
			for (int x = 400 + i * 640; x < 640 + i * 640; x += 80) {
				for (int y = 400 - (i % 2) * 400; y < 3760 - 1280 * (i / 2) - (i % 2) * 400 - 240 * (i % 2); y += 80) {
					Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
				}
			}
		}

		for (int i = 5; i < 10; i++) {
			for (int x = 640 + (i - 5) * 640; x < 4160 - ((i - 5) % 2) * 400; x += 80) {
				for (int y = 3520 - (i - 5) * 640; y < 3520 - (i - 5) * 640 + 240; y += 80)
					Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
			}
		}
		break;
	case Map_Type::Dungeon5:
		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture1));

		for (int x = 2960; x < 4000; x += 80) 
			for(int y=0; y<1000; y+=80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		
		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture2));

		for (int x = 0; x < 2960; x += 80)
			for (int y = 0; y < 1000; y += 80)
				Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, x, y, 80, 80);
		break;
	case Map_Type::Dungeon6:

		SelectObject(bitdc, map_d.Get_Texture(Dungeon_Texture::Texture1));

		Paint_BitBlt_Camera_In(hdc, bitdc, camera, c_rect, 0, 0, 1280, 1000);
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
				Paint_Enemy(hdc, bitdc, file, map_d.Get_Enemy_Bitmap_Const(), map_d.Get_Enemy_Const(index), camera, c_rect);
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

void Change_Map_Dungeon_To(Map_Dungeon& map_d) {
	map_d.Get_Dungeon_Sound().AllSoundStop();
}