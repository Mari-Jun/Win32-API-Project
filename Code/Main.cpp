#include <windows.h>
#include <tchar.h>
#include <fmod.h>
#include "resource.h"
#include "Source.h"
#include "Object_Command.h"
#include "Object_Player.h"
#include "Object_Player_Interaction.h"
#include "Camera.h"
#include "Map_Village.h"
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
	static HDC hdc, memdc, gamedc, bitdc, interfacedc, alphadc;
	PAINTSTRUCT ps;

	//비트맵
	static HBITMAP db_bitmap, db_alpha;

	//데미지 폰트
	static HFONT damage_font;

	//클라이언트 사각형
	static RECT c_rect;

	//플레이어 관련 객체
	static Player* player;

	//카메라 관련 객체
	static Camera* camera;

	//인터페이스 관련 객체
	static Interaction_Box* it_box;
	static Player_Interface* p_inter;

	//맵 관련 객체
	static Map_Village* map_v;	

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
		db_alpha = CreateCompatibleBitmap(hdc, c_rect.right, c_rect.bottom);

		damage_font = CreateFont(40, 20, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("휴먼매직체"));

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

		SetTimer(hwnd, Default_Timer, 30, NULL);

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
			Interaction_Command(*player, *map_v, *it_box);
			break;
		case Command_Key::Co_Equipment:
			Equipment_Command(*player);
		default:
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (wParam)
		{
		case VK_LEFT:
		case VK_RIGHT:
		case VK_UP:
		case VK_DOWN:
		case VK_RETURN:
			if(Chnage_Equipment(*player, wParam))
				InvalidateRgn(hwnd, NULL, FALSE);
			break;
		default:
			break;
		}
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case Default_Timer:
			//Player 관련
			Command_Player<Map_Village>(*player, *map_v);
			Move_Camera(*camera, *player, *map_v, c_rect);
			//Enemy관련
			Enemy_Kill_Check(*map_v);

			//Npc관련
			Animation_Play_Npc(*map_v);
			break;
		default:
			break;
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(memdc, db_bitmap);
		SelectObject(alphadc, db_alpha);

		FillRect(memdc, &c_rect, WHITE_BRUSH);

		SelectObject(gamedc, damage_font);

		Paint_Village_Map(gamedc, bitdc, *player, *map_v);

		BitBlt(memdc, 0, 0, c_rect.right, c_rect.bottom, gamedc, camera->Get_Cam_Left(), camera->Get_Cam_Top(), SRCCOPY);

		Paint_Player_Interface(memdc, bitdc, c_rect, *p_inter, *player);
		Paint_Player_Equipment(memdc, bitdc, *player);
		
		if (Paint_Interaction_Box(memdc, alphadc, bitdc, c_rect, *player, *it_box))
			Show_Npc_Interaction(memdc, *map_v, *it_box);

		BitBlt(hdc, 0, 0, c_rect.right, c_rect.bottom, memdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}