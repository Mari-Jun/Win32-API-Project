#pragma once
#include <windows.h>

/*
*게임 페이지를 제외한 모든 페이지에서 사용하는 기본 비트맵 파일, 폰트등을 모아놓는 클래스
*/
class Sound;

class Default_Page {
public:
	~Default_Page();

	const HBITMAP& Get_Bitmap() const;
	const HFONT& Get_Big_Font() const;
	const HFONT& Get_Main_Font() const;
	const HFONT& Get_Select_Font() const;
	const HFONT& Get_Info_Font() const;
	const HFONT& Get_Credit_Font() const;
	Sound& Get_Sound() const;

	void Set_Bitmap();
	void Set_Font();
	void Set_Sound();

private:
	HBITMAP back_ground_bitmap;
	HFONT big_font;
	HFONT main_page_font;
	HFONT main_page_select_font;
	HFONT info_font;
	HFONT credit_font;
	Sound* sound;
};

void Reset_Default_Page(Default_Page& d_page);
void Paint_Loading_Page(HDC hdc, const RECT c_rect, const Default_Page& d_page);

void Change_Page_To(Default_Page& d_page);
void Change_To_Page(Default_Page& d_page);