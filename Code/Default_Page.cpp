#include <windows.h>
#include <tchar.h>
#include "Sound.h"
#include "Source.h"
#include "Default_Page.h"

Default_Page::~Default_Page() {
	DeleteObject(back_ground_bitmap);
	DeleteObject(big_font);
	DeleteObject(main_page_font);
	DeleteObject(main_page_select_font);
}

const HBITMAP& Default_Page::Get_Bitmap() const {
	return back_ground_bitmap;
}

const HFONT& Default_Page::Get_Big_Font() const {
	return big_font;
}

const HFONT& Default_Page::Get_Main_Font() const {
	return main_page_font;
}

const HFONT& Default_Page::Get_Select_Font() const {
	return main_page_select_font;
}

const HFONT& Default_Page::Get_Info_Font() const {
	return info_font;
}

const HFONT& Default_Page::Get_Credit_Font() const {
	return credit_font;
}

Sound& Default_Page::Get_Sound() const {
	return *sound;
}

void Default_Page::Set_Bitmap() {
	back_ground_bitmap = (HBITMAP)LoadImage(NULL, _T(".\\BitMap\\Page\\main_image.bmp"), IMAGE_BITMAP, 0, 0, LR_LOADFROMFILE);
}

void Default_Page::Set_Font() {
	big_font = CreateFontW(200, 80, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
	main_page_font = CreateFontW(100, 40, 0, 0, FW_BOLD, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
	main_page_select_font = CreateFontW(100, 40, 0, 0, FW_BOLD, FALSE, TRUE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
	info_font = CreateFontW(80, 30, 0, 0, NULL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
	credit_font = CreateFontW(40, 15, 0, 0, NULL, FALSE, FALSE, 0, DEFAULT_CHARSET, OUT_DEFAULT_PRECIS, CLIP_DEFAULT_PRECIS, DEFAULT_QUALITY, DEFAULT_PITCH, _T("Curlz MT"));
}

void Default_Page::Set_Sound() {
	sound = Create_Class<Sound>();
	Reset_Sound(*sound, Sound_Type::Sound_Map_Type, Map_Type::Type_Main_Page);
}

void Reset_Default_Page(Default_Page& d_page) {
	d_page.Set_Bitmap();
	d_page.Set_Font();
	d_page.Set_Sound();

	//À½¾Ç Àç»ý
	d_page.Get_Sound().Play_Sound(7);
}

void Paint_Loading_Page(HDC hdc, const RECT c_rect, const Default_Page& d_page) {
	TextOut(hdc, 50, 50, _T("Loading"), 7);
}

void Change_Page_To(Default_Page& d_page) {
	d_page.Get_Sound().AllSoundStop();
}

void Change_To_Page(Default_Page& d_page) {
	d_page.Get_Sound().Play_Sound(7);
}
