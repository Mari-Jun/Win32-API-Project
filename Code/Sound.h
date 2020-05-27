#pragma once
#include <fmod.h>

enum Sound_Type {
	Sound_Map_Type, Sound_Enemy_Type, Sound_Player_Type
};

enum Village_Sound {
	BackGround_Village_Sound, Elder_Sound, Equipment_Shop_Sound, Weapon_Shop_Sound, Item_Shop_Sound, Legend_Sound, Soilder_sound
};

enum Player_Sound {
	Attack_Sound, SkillQ_Sound, SkillW_Sound, SkillE_Sound, SkillR_Sound, Potion_Sound
};

class Sound {
public:
	const FMOD_SYSTEM& Get_Fmod_Syetem() const;
	const FMOD_SOUND& Get_Fmod_Sound(const int& index) const;
	const FMOD_CHANNEL& Get_Fmod_Channel(const int& index) const;

	void Create_Fmod_System();
	void Create_Map_Sound(const int& map_type);
	void Create_Enemy_Sound(const int& enemy_type);
	void Create_Player_Sound(const int& player_type);
	void Play_Sound(const int& sound_type);
	void AllSoundStop();

private:
	FMOD_SYSTEM* system;
	FMOD_SOUND* sound[20];
	FMOD_CHANNEL* channel[20];
};

void Reset_Sound(Sound& sound, const int& sound_type, const int& detail_type);
