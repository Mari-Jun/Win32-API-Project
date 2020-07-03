#include <windows.h>
#include <tchar.h>
#include "resource.h"
#include "Source.h"
#include "Game_Progress.h"
#include "Object_Info.h"
#include "Object_Player_Command.h"
#include "Object_Player.h"
#include "Object_Player_Interaction.h"
#include "Object_Enemy_Command.h"
#include "Object_Skill.h"
#include "Camera.h"
#include "Map_Village.h"
#include "Map_Dungeon.h"
#include "Interface.h"
#include "File.h"
#include "Default_Page.h"
#include "Main_Page.h"
#include "Help_Page.h"

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
	WndClass.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
	WndClass.hCursor = LoadCursor(NULL, IDC_ARROW);
	WndClass.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	WndClass.lpszMenuName = NULL;
	WndClass.lpszClassName = _T("WndClass");
	RegisterClass(&WndClass);
	hwnd = CreateWindowW(
		_T("WndClass"),
		_T("NIKKO"),
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

	//��Ʈ��
	static HBITMAP db_bitmap, db_bitmap2;

	//������ ��Ʈ
	static HFONT damage_font;

	//Ŭ���̾�Ʈ �簢��
	static RECT c_rect;

	//������ ��ü
	static Default_Page* d_page;
	static Main_Page* m_page;
	static Help_Page* h_page;
	static int select_menu;

	//���� ����
	static File* file;

	//���� ���� ��ü
	static Progress* progress;

	//�÷��̾� ���� ��ü
	static Player* player;

	//ī�޶� ���� ��ü
	static Camera* camera;

	//�������̽� ���� ��ü
	static Interaction_Box* it_box;
	static Player_Interface* p_inter;
	static Enemy_Interface* e_inter;
	static Clear_Interface* c_inter;

	//�� ���� ��ü
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

		damage_font = CreateFont(40, 20, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("�޸ո���ü"));

		//���� ���� ����
		progress = Create_Class<Progress>();
		Reset_Progress(*progress, Class_Type::Warrior);

		//������ ����
		d_page = Create_Class<Default_Page>();
		Reset_Default_Page(*d_page);
		m_page = Create_Class<Main_Page>();
		Reset_Main_Page(hdc, c_rect, *d_page, *m_page);
		h_page = Create_Class<Help_Page>();
		Reset_Help_Page(hdc, c_rect, *d_page, *h_page);
		select_menu = 0;

		ReleaseDC(hwnd, hdc);

		break;
	case WM_GETMINMAXINFO:
		//ȭ�� ����
		((MINMAXINFO*)lParam)->ptMinTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMinTrackSize.y = WindowY;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.x = WindowX;
		((MINMAXINFO*)lParam)->ptMaxTrackSize.y = WindowY;
		break;
	case WM_CHAR:
		switch (progress->Get_Page_Type())
		{
		case Page_Type::T_Game_Page:
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
			case 'o':
				DialogBox(hInst, MAKEINTRESOURCE(IDD_DIALOG_OBJECT_INFO), hwnd, Object_Info_Dialog);
				break;
			default:
				break;
			}
			if (progress->Get_Map_Type() != Map_Type::Village1)
				Change_Player_Status_To_Skill(*player, wParam);
			break;
		}
		break;
	case WM_KEYDOWN:
		switch (progress->Get_Page_Type())
		{
		case Page_Type::T_Main_Page:
			select_menu = Key_Down_to_Main_Menu_Select(*m_page, wParam);
			switch (select_menu)
			{
			case Main_Page_Select::M_Start:
				hdc = GetDC(hwnd);

				Change_Page_To(*d_page);
				Change_Page_Type(*progress, Page_Type::T_Loading_Page);

				Delete_Class<Main_Page>(&m_page);
				Delete_Class<Default_Page>(&d_page);

				//���� ���� ����
				file = Create_Class<File>();
				Reset_File(*file);

				//�÷��̾� ����
				player = Create_Class<Player>();
				Reset_Player(*player, *file, Warrior);

				//ī�޶� ����
				camera = Create_Class<Camera>();
				Reset_Camera(*camera, c_rect);

				//�������̽� ����
				it_box = Create_Class<Interaction_Box>();
				Reset_Interaction_Box(*it_box, c_rect);
				p_inter = Create_Class<Player_Interface>();
				Reset_Player_Interface(*p_inter);

				//�� ����
				map_v = Create_Class<Map_Village>();
				Reset_Village_Map(hdc, *map_v);

				Change_Page_Type(*progress, Page_Type::T_Game_Page);

				SetTimer(hwnd, Timer_Name::Default_Timer, 30, NULL);

				ReleaseDC(hwnd, hdc);
				break;
			case Main_Page_Select::M_Help:
				Change_Page_Type(*progress, Page_Type::T_Help_Page);
				break;
			case Main_Page_Select::M_Credit:
				Change_Page_Type(*progress, Page_Type::T_Credit_Page);
				break;
			case Main_Page_Select::M_Quit:
				exit(0);
				break;
			}
			InvalidateRgn(hwnd, NULL, FALSE);
			break;
		case Page_Type::T_Help_Page:
		case Page_Type::T_Credit_Page:
			select_menu = Key_Down_to_Help_Menu_Select(*h_page, wParam, progress->Get_Page_Type());
			if(select_menu==0)
				Change_Page_Type(*progress, Page_Type::T_Main_Page);			
			InvalidateRgn(hwnd, NULL, FALSE);
			break;
		case Page_Type::T_Game_Page:
			if (progress->Get_Map_Type() == Map_Type::Village1) {
				Chnage_Equipment(*player, wParam);
				Shop_Select_Item(*player, *map_v, *it_box, wParam);
				Interaction_Dialog_Select(*player, *map_v, *it_box, wParam);
				switch (Change_Map_Select(*progress, *player, wParam))
				{
				case Map_Type::Dungeon1:
				case Map_Type::Dungeon2:
				case Map_Type::Dungeon3:
				case Map_Type::Dungeon4:
				case Map_Type::Dungeon5:
				case Map_Type::Dungeon6:
					hdc = GetDC(hwnd);
					map_d = Create_Class<Map_Dungeon>();
					Change_Map_Village_To(*map_v);
					Reset_Dungeon_Map(hdc, *map_d, *file, progress->Get_Map_Type());
					Change_Map_Reset_Player(*player, *progress);
					e_inter = Create_Class<Enemy_Interface>();
					Reset_Enemy_Interface(*e_inter);
					ReleaseDC(hwnd, hdc);
					break;
				default:
					break;
				}
			}
			break;
		}
		break;
	case WM_TIMER:
		switch (progress->Get_Page_Type())
		{
		case Page_Type::T_Loading_Page:
			switch (wParam)
			{
			case Timer_Name::Loading_Timer:
				exit(0);
				break;
			}
			break;
		case Page_Type::T_Game_Page:
			if (progress->Get_Map_Type() == Map_Type::Village1) {
				switch (wParam)
				{
				case Timer_Name::Default_Timer:
					//Player ����
					Command_Player<Map_Village>(*player, *map_v, *progress);
					Move_Camera(*camera, *player, *map_v, c_rect);
					//Npc����
					Animation_Play_Npc(*map_v);
					break;
				default:
					break;
				}
			}
			else {
				switch (wParam)
				{
				case Timer_Name::Default_Timer:
					//Player ����
					if (Command_Player<Map_Dungeon>(*player, *map_d, *progress)) {
						//�÷��̾ �����
						Change_Map_Dungeon_To(*map_d);
						Change_Map_To_Village(*map_v);

						Delete_Class<Map_Dungeon>(&map_d);
						Delete_Class<Enemy_Interface>(&e_inter);
						Change_Map_Player_Die(*progress, *player);
						Change_Map_Reset_Player(*player, *progress);
						break;
					}
					else {
						Move_Camera(*camera, *player, *map_d, c_rect);
						//Enemy����
						Command_Enemy(*map_d, *player, *camera, *file, c_rect);
						if (Check_Dungeon_Clear(*map_d) && c_inter == NULL) {
							SetTimer(hwnd, Timer_Name::Clear_Timer, 10000, NULL);
							c_inter = Create_Class<Clear_Interface>();
							Reset_Clear_Interface(*c_inter, *player, *map_d);
						}
					}
					break;
				case Timer_Name::Clear_Timer:
					//���� ���
					Change_Map_Dungeon_To(*map_d);
					Change_Map_To_Village(*map_v);

					Delete_Class<Map_Dungeon>(&map_d);
					Delete_Class<Clear_Interface>(&c_inter);
					Delete_Class<Enemy_Interface>(&e_inter);

					//progress����
					Clear_Quest(*progress);
					Change_Map_Dungeon_Clear(*progress, *player);
					Change_Map_Reset_Player(*player, *progress);
					KillTimer(hwnd, Timer_Name::Clear_Timer);

					break;
				default:
					break;
				}
			}
			break;
		}
		InvalidateRgn(hwnd, NULL, FALSE);		
		break;
	case WM_PAINT:
		hdc = BeginPaint(hwnd, &ps);
		SelectObject(memdc, db_bitmap);
		SelectObject(alphadc, db_bitmap2);

		FillRect(memdc, &c_rect, WHITE_BRUSH);

		switch (progress->Get_Page_Type())
		{
		case Page_Type::T_Main_Page:
			Paint_Main_Page(memdc, bitdc, c_rect, *d_page, *m_page);
			break;
		case Page_Type::T_Loading_Page:
			Paint_Loading_Page(memdc, c_rect, *d_page);
			break;
		case Page_Type::T_Help_Page:
			Paint_Help_Page(memdc, bitdc, c_rect, *d_page, *h_page);
			break;
		case Page_Type::T_Credit_Page:
			Paint_Credit_Page(memdc, bitdc, c_rect, *d_page, *h_page);
			break;
		case Page_Type::T_Game_Page:
			SelectObject(gamedc, damage_font);

			switch (progress->Get_Map_Type())
			{
			case Map_Type::Village1:
				Paint_Village_Map(gamedc, bitdc, *player, *map_v, *camera, c_rect);
				break;
			case Map_Type::Dungeon1:
			case Map_Type::Dungeon2:
			case Map_Type::Dungeon3:
			case Map_Type::Dungeon4:
			case Map_Type::Dungeon5:
			case Map_Type::Dungeon6:
				Paint_Dungeon_Map(gamedc, bitdc, *player, *map_d, *file, *camera, c_rect);
				break;
			default:
				break;
			}

			BitBlt(memdc, 0, 0, c_rect.right, c_rect.bottom, gamedc, camera->Get_Cam_Left(), camera->Get_Cam_Top(), SRCCOPY);

			Paint_Player_Interface(memdc, bitdc, c_rect, *p_inter, *player);
			if (progress->Get_Map_Type() != Map_Type::Village1) {
				Paint_Enemy_Interface(memdc, bitdc, c_rect, *e_inter, *map_d, *camera);
				if (c_inter != NULL)
					Paint_Clear_Interface(memdc, bitdc, *c_inter, *player, *map_d, c_rect);
			}
			Paint_Player_Equipment(memdc, bitdc, *player);

			if (Paint_Interaction_Box(memdc, alphadc, bitdc, c_rect, *player, *it_box))
				if (progress->Get_Map_Type() == Map_Type::Village1)
					Show_Npc_Interaction(memdc, bitdc, *player, *map_v, *it_box, *progress, *file);

			Paint_Map_Select(memdc, bitdc, *progress, c_rect);
			break;
		}		

		BitBlt(hdc, 0, 0, c_rect.right, c_rect.bottom, memdc, 0, 0, SRCCOPY);
		EndPaint(hwnd, &ps);
		break;
	case WM_DESTROY:
		PostQuitMessage(0);
		break;
	}
	return DefWindowProc(hwnd, iMsg, wParam, lParam);
}