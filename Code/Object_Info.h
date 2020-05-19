#pragma once

class Object_Info {
public:

	const int& Get_Level() const;
	const int& Get_Hp() const;
	const int& Get_Max_Hp() const;
	const int& Get_Attack() const;
	const int& Get_Defence() const;
	const bool& Is_No_Damage() const;
	
	void Set_Level(const int& level);
	void Set_Hp(const int& hp);
	void Set_Max_Hp(const int& max_hp);
	void Set_Attack(const int& attack);
	void Set_Defence(const int& defence);
	void Set_No_Damage(const bool& damage);

private:
	int level;
	int hp;
	int max_hp;
	int attack;
	int defence;
	bool no_damage;
};

void Reset_Object_Info(Object_Info& o_info, const int& level, const int& hp, const int& attack, const int& defence);