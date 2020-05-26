#include <windows.h>
#include <tchar.h>
#include <fmod.h>
#include "resource.h"
#include "Source.h"
#include "Game_Progress.h"
#include "Object_Player_Command.h"
#include "Object_Player.h"
#include "Object_Player_Interaction.h"
#include "Object_Enemy_Command.h"
#include "Object_Skill.h"
#include "Camera.h"
#include "Map_Village.h"
#include "Map_Dungeon.h"
#include "Interface.h"

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib,"fmodL_vc.lib")

static const int WindowX = 1280 + GetSystemMetrics(SM_CXFRAME << 2);
static const int WindowY = 720 + GetSystemMetrics(SM_CYFRAME << 2) + GetSystemMetrics(SM_CYCAPTION);

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam);

HINSTANCE hInst;
int WINAPI wWinMain(_In_ HINSTANCE hInstance, _In_opt_ HINSTANCE hPrevInstance, _In_ LPWSTR lpCmdLine, _In_ int nCmdShow) {
	HWND hwnd;
	MSG msg;
	WNDCLASS WndClass;
	hInst = hInstance;
	WndClass.style = CS_HREDRAW | CS_VREDRAW | CS_DBLCLKS;
	WndClass.lpfnWndProc = WndProc;
	WndClass.cbClsExtra = 0;
	WndClass.cbWndExtra = 0;
	WndClass.hInstance = hInstance;
	WndClass.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("WndClass");
	RegisterClass(&WndClass);
	hwnd = CreateWindowW(
		_T("WndClass"),
		_T("windows program"),
		WS_OVERLAPPEDWINDOW,
		(GetSystemMetrics(SM_CXSCREEN) - WindowX) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - WindowY) / 2,
		WindowX,
		WindowY,
		NULL,
		NULL,
		hInstance,
		NULL
	);
	ShowWindow(hwnd, nCmdShow);
	UpdateWindow(hwnd);
	while (GetMessage(&msg, NULL, 0, 0)) {
		TranslateMessage(&msg);
		DispatchMessage(&msg);
	}
	return (int)msg.wParam;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT iMsg, WPARAM wParam, LPARAM lParam) {
	static HDC hdc, memdc, gamedc, bitdc, alphadc, interfacedc;
	PAINTSTRUCT ps;

	//비트맵
	static HBITMAP db_bitmap, db_bitmap2;

	//데미지 폰트
	static HFONT damage_font;

	//클라이언트 사각형
	static RECT c_rect;

	//게임 진행 객체
	static Progress* progress;

	//플레이어 관련 객체
	static Player* player;

	//카메라 관련 객체
	static Camera* camera;

	//인터페이스 관련 객체
	static Interaction_Box* it_box;
	static Player_Interface* p_inter;

	//맵 관련 객체
	static Map_Village* map_v;	
	static Map_Dungeon* map_d;

	switch (iMsg)
	{
	case WM_CREATE:
		GetClientRect(hwnd, &c_rect);

		hdc = GetDC(hwnd);
		memdc = CreateCompatibleDC(hdc);
		gamedc = CreateCompatibleDC(hdc);
		bitdc = CreateCompatibleDC(hdc);
		alphadc = CreateCompatibleDC(hdc);
		db_bitmap = CreateCompatibleBitmap(hdc, c_rect.right, c_rect.bottom);
		db_bitmap2 = CreateCompatibleBitmap(hdc, c_rect.right, c_rect.bottom);

		damage_font = CreateFont(40, 20, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼매직체"));

		//게임 진행 관련
		progress = Create_Class<Progress>();
		Reset_Progress(*progress, Class_Type::Warrior);

		//플레이어 관련
		player = Create_Class<Player>();
		Reset_Player(*player, Warrior);

		//카메라 관련
		camera = Create_Class<Camera>();
		Reset_Camera(*camera, c_rect);

		//인터페이스 관련
		it_box = Create_Class<Interaction_Box>();
		Reset_Interaction_Box(*it_box, c_rect);
		p_inter = Create_Class<Player_Interface>();
		Reset_Player_Interface(*p_inter);

		//맵 관련
		map_v = Create_Class<Map_Village>();
		Reset_Village_Map(hdc, *map_v);

		SetTimer(hwnd, Default_Timer, 10, NULL);

		ReleaseDC(hwnd, hdc);

		break;
	case WM_GETMINMAXINFO:
		//화면 고정
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WindowY;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WindowY;
		break;
	case WM_CHAR:
		switch (wParam)
		{
		case Command_Key::Co_Interaction:
			if (progress->Get_Map_Type() == Map_Type::Village1)
				Interaction_Command(*player, *map_v, *it_box, *progress);
			break;
		case Command_Key::Co_Equipment:
			Equipment_Command(*player);
			break;
		case '1':
		case '2':
		case '3':
			Use_Item_Command(*player, wParam - '0');
			break;
		default:
			break;
		}
		if (progress->Get_Map_Type() != Map_Type::Village1)
			Change_Player_Status_To_Skill(*player, wParam);
		break;
	case WM_KEYDOWN:
		if (progress->Get_Map_Type() == Map_Type::Village1) {
			Chnage_Equipment(*player, wParam);
			Shop_Select_Item(*player, *map_v, *it_box, wParam);
			Interaction_Dialog_Select(*player, *map_v, *it_box, wParam);
			switch (Change_Map_Select(*progress, *player, wParam))
			{
			case Map_Type::Dungeon1:
				map_d = Create_Class<Map_Dungeon>();
				Reset_Dungeon_Map(hdc, *map_d, Map_Type::Dungeon1);
				//던전으로 들어왔으니 속도를 설정해준다.
				Change_Object_Speed(*player, 10);
				break;
			default:
				break;
			}
		}
		break;
	case WM_TIMER:
		if (progress->Get_Map_Type() == Map_Type::Village1) {
			switch (wParam)
			{
			case Default_Timer:
				//Player 관련
				Command_Player<Map_Village>(*player, *map_v, *progress);
				Move_Camera(*camera, *player, *map_v, c_rect);
				//Npc관련
				Animation_Play_Npc(*map_v);
				break;
			default:
				break;
			}
		}
		else {
			switch (wParam)
			{
			case Default_Timer:
				//Player 관련
				Command_Player<Map_Dungeon>(*player, *map_d, *progress);
				Move_Camera(*camera, *player, *map_d, c_rect);
				//Enemy관련
				Command_Enemy(*map_d, *player);
				break;
			default:
				break;
			}
		}
		InvalidateRgn(hwnd, NULL, FALSE);		
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(memdc, db_bitmap);
		SelectObject(alphadc, db_bitmap2);

		FillRect(memdc, &c_rect, WHITE_BRUSH);

		SelectObject(gamedc, damage_font);

		switch (progress->Get_Map_Type())
		{
		case Map_Type::Village1:
			Paint_Village_Map(gamedc, bitdc, *player, *map_v);
			break;
		case Map_Type::Dungeon1:
			Paint_Dungeon_Map(gamedc, bitdc, *player, *map_d);
			break;
		default:
			break;
		}

		BitBlt(memdc, 0, 0, c_rect.right, c_rect.bottom, gamedc, camera->Get_Cam_Left(), camera->Get_Cam_Top(), SRCCOPY);

		Paint_Player_Interface(memdc, bitdc, c_rect, *p_inter, *player);
		Paint_Player_Equipment(memdc, bitdc, *player);
		
		if (Paint_Interaction_Box(memdc, alphadc, bitdc, c_rect, *player, *it_box))
			if (progress->Get_Map_Type() == Map_Type::Village1)
				Show_Npc_Interaction(memdc, bitdc, *player, *map_v, *it_box);

		Paint_Map_Select(memdc, bitdc, *progress, c_rect);

		BitBlt(hdc, 0, 0, c_rect.right, c_rect.bottom, memdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}