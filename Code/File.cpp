#include <windows.h>
#include <tchar.h>
#include <iostream>
#include <fstream>
#include <string>
#include "Source.h"
#include "File.h"

using namespace std;

const int& File::Get_Enemy_Object_Info(const int& enemy_type, const int& index) const {
	return Enemy_Object_Info[enemy_type][index];
}

const int& File::Get_Enemy_Motion_Count(const int& enemy_type, const int& status) const {
	return Enemy_Motion_Count[enemy_type][status];
}

const wchar_t* File::Get_Enemy_Motion_Text(const int& enemy_type, const int& status) const {
	return Enemy_Motion_Text[enemy_type][status];
}

const int& File::Get_Enemy_Attack_Info(const int& enemy_type, const int& attack_type, const int& attack_info) const {
	return Enemy_Attack_Info[enemy_type][attack_type][attack_info];
}

const double& File::Get_Enemy_Attack_Multiple_Info(const int& enemy_type, const int& attack_type) const {
	return Enemy_Attack_Multiple_Info[enemy_type][attack_type];
}

const wchar_t& File::Get_Quest_Talk(const int& quest_type, const int& before, const int& index) const {
	return *Quest_Talk[quest_type][before][index];
}

void File::Set_Enemy_Object_Info() {
	string str;
	string result;
	fstream fs;

	fs.open(_T(".\\File\\Object_Info.csv"), ios::in);
	
	int type = -1;
	int index = 0;
	while (getline(fs, str, ',')) {

		result.clear();

		for (int i = 0; i < str.length(); i++) {
			if (str[i] >= '0' && str[i] <= '9')
				result += str[i];
		}

		if (result[0] == NULL)
			break;

		if (type == -1) 
			type = stoi(result);
		else {
			Enemy_Object_Info[type][index++] = stoi(result);
			if (index == 8) {
				type = -1;
				index = 0;
				getline(fs, str, '\n');
			}
		}
	}

	for (int i = 0; i < 11; i++) {
		for (int j = 0; j < 8; j++)
			cout << Enemy_Object_Info[i][j] << ' ';
		cout << endl;
	}

	
	fs.close();
}

void File::Set_Enemy_Motion() {
	string str;
	wstring wstr;
	fstream fs;

	fs.open(_T(".\\File\\Enemy_Motion_Info.csv"), ios::in);

	int type = 0;
	int status = 0;
	while (!fs.eof()) {

		getline(fs, str, ',');

		if (str[0] != '\n') {
			if (str[0] >= '0' && str[0] <= '9') {
				Enemy_Motion_Count[type][status] = stoi(str);
			}
			else {
				wstr = wstring(str.begin(), str.end());
				Enemy_Motion_Text[type][status++] = _wcsdup(wstr.c_str());
				if (status == 7) {
					getline(fs, str, ',');
					Enemy_Motion_Count[type][status] = stoi(str);
					getline(fs, str, ',');
					Enemy_Motion_Count[type][status + 1] = stoi(str);
					getline(fs, str, '\n');
					type++;
					status = 0;
				}
			}
		}		
	}

	fs.close();
}

void File::Set_Enemy_Attack_Info() {
	string str;
	string result;
	fstream fs;

	fs.open(_T(".\\File\\Enemy_Attack_Info.csv"), ios::in);

	int enemy_type = 0;
	int attack_type = Attack_Type::A_Attack;
	int attack_info = Attack_Info::Attack_Delay;
	
	while (!fs.eof()) {
		for (attack_type = Attack_Type::A_Attack; attack_type <= Attack_Type::A_SkillR; attack_type++) {
			for (attack_info = Attack_Info::Attack_Delay; attack_info <= Attack_Info::Attack_Multiple; attack_info++) {
				getline(fs, str, ',');

				if (str[0] == NULL)
					break;
			
				if (attack_info != Attack_Info::Attack_Multiple)
					Enemy_Attack_Info[enemy_type][attack_type][attack_info] = stoi(str);
				else
					Enemy_Attack_Multiple_Info[enemy_type][attack_type] = stod(str);

			}
			if (str[0] == NULL)
				break;
			getline(fs, str, '\n');
		}
		if (str[0] == NULL)
			break;
		enemy_type++;
	}

	for (int enemy_type = 0; enemy_type < 6; enemy_type++) {
		for (attack_type = Attack_Type::A_Attack; attack_type <= Attack_Type::A_SkillR; attack_type++) {
			for (attack_info = Attack_Info::Attack_Delay; attack_info <= Attack_Info::Attack_Multiple; attack_info++) {
				if (attack_info != Attack_Info::Attack_Multiple)
					cout << Enemy_Attack_Info[enemy_type][attack_type][attack_info] << ' ';
				else
					cout << Enemy_Attack_Multiple_Info[enemy_type][attack_type] << endl;
			}
		}
		cout << endl;
	}
	fs.close();
}

void File::Set_Quest_Talk() {
	wstring wstr;
	wifstream fs;

	fs.open(_T(".\\File\\Quest.txt"), ios::in);

	int quest_num = Quest_Name::Main_Quest1;
	int quest_after = 0;
	while (!fs.eof()) {

		getline(fs, wstr);

		int max_talk = stoi(wstr);
		
		for (int index = 0; index < max_talk; index++) {
			getline(fs, wstr);
			wcout << wstr << endl;
			Quest_Talk[quest_num - 1][quest_after][index] = _wcsdup(wstr.c_str());
			wcout << Quest_Talk[quest_num - 1][quest_after][index] << endl;
		}
	}

	fs.close();

	for (int i = 0; i < 10; i++)
		wcout << Quest_Talk[0][0][i] << endl;
}


void Reset_File(File& file) {
	file.Set_Enemy_Object_Info();
	file.Set_Enemy_Motion();
	file.Set_Enemy_Attack_Info();
	//file.Set_Quest_Talk();
}