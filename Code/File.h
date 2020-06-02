#pragma once
#include <windows.h>


class File {
public:
	const int& Get_Enemy_Object_Info(const int& enemy_type, const int& index) const;
	const int& Get_Enemy_Motion_Count(const int& enemy_type, const int& status) const;
	const wchar_t* Get_Enemy_Motion_Text(const int& enemy_type, const int& status) const;
	const int& Get_Enemy_Attack_Info(const int& enemy_type, const int& attack_type, const int& attack_info) const;
	const double& Get_Enemy_Attack_Multiple_Info(const int& enemy_type, const int& attack_type) const;

	void Set_Enemy_Object_Info();
	void Set_Enemy_Motion();
	void Set_Enemy_Attack_Info();

private:
	int Enemy_Object_Info[50][8];
	int Enemy_Motion_Count[50][10];
	wchar_t* Enemy_Motion_Text[50][8];
	int Enemy_Attack_Info[50][5][9];
	double Enemy_Attack_Multiple_Info[50][5];
};

void Reset_File(File& file);