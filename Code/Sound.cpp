#include <Windows.h>
#include <tchar.h>
#include "Source.h"
#include "Sound.h"

const FMOD_SYSTEM& Sound::Get_Fmod_Syetem() const {
	return *system;
}

const FMOD_SOUND& Sound::Get_Fmod_Sound(const int& index) const {
	return *sound[index];
}
const FMOD_CHANNEL& Sound::Get_Fmod_Channel(const int& index) const {
	return *channel[index];
}

void Sound::Create_Fmod_System() {
	FMOD_System_Create(&system);
	FMOD_System_Init(system, 20, FMOD_INIT_NORMAL, 0);
}

void Sound::Create_Map_Sound(const int& map_type) {
	TCHAR str[50];
	//char str[100];
	//sprintf_s(str, ".\\Sound\\BKMusic%d.mp3", i + 1);
	switch (map_type)
	{
	case Map_Type::Village1:
		FMOD_System_CreateStream(system, ".\\Sound\\Background\\Village1.mp3", FMOD_LOOP_NORMAL, 0, &sound[Village_Sound::BackGround_Village_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Npc\\Elder.mp3", FMOD_LOOP_OFF, 0, &sound[Village_Sound::Elder_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Npc\\Equipment.mp3", FMOD_LOOP_OFF, 0, &sound[Village_Sound::Equipment_Shop_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Npc\\Weapon.mp3", FMOD_LOOP_OFF, 0, &sound[Village_Sound::Weapon_Shop_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Npc\\Item.mp3", FMOD_LOOP_OFF, 0, &sound[Village_Sound::Item_Shop_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Npc\\Legend.mp3", FMOD_LOOP_OFF, 0, &sound[Village_Sound::Legend_Sound]);
		break;
	default:
		break;
	}
}

void Sound::Create_Enemy_Sound(const int& enemy_type) {

}

void Sound::Create_Player_Sound(const int& player_type) {
	switch (player_type)
	{
	case Class_Type::Warrior:
		FMOD_System_CreateStream(system, ".\\Sound\\Player\\Warrior\\Attack.mp3", FMOD_LOOP_OFF, 0, &sound[Player_Sound::Attack_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Player\\Warrior\\Skill_Q.mp3", FMOD_LOOP_OFF, 0, &sound[Player_Sound::SkillQ_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Player\\Warrior\\Skill_W.mp3", FMOD_LOOP_OFF, 0, &sound[Player_Sound::SkillW_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Player\\Warrior\\Skill_E.mp3", FMOD_LOOP_OFF, 0, &sound[Player_Sound::SkillE_Sound]);
		FMOD_System_CreateStream(system, ".\\Sound\\Player\\Warrior\\Skill_R.mp3", FMOD_LOOP_OFF, 0, &sound[Player_Sound::SkillR_Sound]);
		break;
	default:
		break;
	}
}

void Sound::Play_Sound(const int& sound_type) {
	FMOD_System_PlaySound(system, sound[sound_type], NULL, FALSE, &channel[sound_type]);
}

void Sound::AllSoundStop() {
	for (int index = 0; index < 20; index++)
		FMOD_Channel_Stop(channel[index]);
}

void Create_Enemy_Sound(const int& enemy_type) {

}

void Create_Player_Sound(const int& player_type) {

}

void Reset_Sound(Sound& sound, const int& sound_type, const int& detail_type) {
	sound.Create_Fmod_System();
	switch (sound_type)
	{
	case Sound_Type::Sound_Map_Type:
		sound.Create_Map_Sound(detail_type);
		break;
	case Sound_Type::Sound_Enemy_Type:
		sound.Create_Enemy_Sound(detail_type);
		break;
	case Sound_Type::Sound_Player_Type:
		sound.Create_Player_Sound(detail_type);
		break;
	default:
		break;
	}

}

/*void PlayMainBKSound() {
	//현재 Cahnnel0에 재생되는 음악을 정지한다.
	FMOD_Channel_Stop(M_Channel[0]);
	//배경 음악 Sound0를 재생한다.
	FMOD_System_PlaySound(M_System, M_Sound[0], NULL, FALSE, &M_Channel[0]);
}*/
