#include <windows.h>
#include <tchar.h>
#include <fmod.h>
#include "resource.h"
#include "Source.h"
#include "Object_Move.h"
#include "Object_Player.h"
#include "Camera.h"
#include "Map_Village.h"

#pragma comment(lib, "msimg32.lib")
#pragma comment(lib,"fmodL_vc.lib")

static const int WindowX = 1280 + GetSystemMetrics(SM_CXFRAME);
static const int WindowY = 720 + GetSystemMetrics(SM_CYFRAME) + GetSystemMetrics(SM_CYCAPTION) + GetSystemMetrics(SM_CYMENU);

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
		LoadMenu(hInstance,MAKEINTRESOURCE(IDR_MENU)),
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
	static HDC hdc, memdc, gamedc, bitdc, alphadc;
	PAINTSTRUCT ps;

	//더블 버퍼링 비트맵
	static HBITMAP db_bitmap, db_oldbitmap;

	//클라이언트 사각형
	static RECT c_rect;

	//플레이어 관련 객체
	static Warrior* warrior;

	//카메라 관련 객체
	static Camera* camera;

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

		//플레이어 관련
		warrior = Create_Class<Warrior>();		
		Reset_Warrior(*warrior);

		//카메라 관련
		camera = Create_Class<Camera>();
		Reset_Camera(*camera, c_rect);

		//맵 관련
		map_v = Create_Class<Map_Village>();
		Reset_Village_Map(hdc, *map_v);

		SetTimer(hwnd, Player_Move_Timer, 30, NULL);

		ReleaseDC(hwnd, hdc);

		break;
	case WM_GETMINMAXINFO:
		//화면 고정
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WindowY;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WindowY;
		break;
	case WM_TIMER:
		switch (wParam)
		{
		case Player_Move_Timer:
			Move_Player<Map_Village>(*warrior, *map_v);
			Move_Camera(*camera, *warrior, *map_v, c_rect);
			break;
		default:
			break;
		}
		InvalidateRgn(hwnd, NULL, FALSE);
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		db_oldbitmap = (HBITMAP)SelectObject(memdc, db_bitmap);

		FillRect(memdc, &c_rect, WHITE_BRUSH);

		Paint_Village_Map(gamedc, bitdc, *warrior, *map_v);

		BitBlt(memdc, 0, 0, c_rect.right, c_rect.bottom, gamedc, camera->Get_Cam_Left(), camera->Get_Cam_Top(), SRCCOPY);

		BitBlt(hdc, 0, 0, c_rect.right, c_rect.bottom, memdc, 0, 0, SRCCOPY);
		SelectObject(memdc, db_oldbitmap);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}