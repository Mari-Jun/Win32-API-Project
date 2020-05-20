#pragma once

class Object_Info {
public:

	const int& Get_Level() const;
	const int& Get_Hp() const;
	const int& Get_Max_Hp() const;
	const int& Get_Mp() const;
	const int& Get_Max_Mp() const;
	const int& Get_Attack() const;
	const int& Get_Defence() const;
	const int& Get_Fatal() const;
	const bool& Is_No_Damage() const;
	
	void Set_Level(const int& level);
	void Set_Hp(const int& hp);
	void Set_Max_Hp(const int& max_hp);
	void Set_Mp(const int& mp);
	void Set_Max_Mp(const int& max_mp);
	void Set_Attack(const int& attack);
	void Set_Defence(const int& defence);
	void Set_Fatal(const int& fatal);
	void Set_No_Damage(const bool& damage);

private:
	int level;
	int hp;
	int max_hp;
	int mp;
	int max_mp;
	int attack;
	int defence;
	int fatal;
	bool no_damage;
};

void Reset_Object_Info(Object_Info& o_info, const int& level, const int& hp, const int& mp, const int& attack, const int& defence, const int& fatal);