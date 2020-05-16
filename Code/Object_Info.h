#pragma once

class Object_Info {
public:

	const int& Get_Hp() const;
	const int& Get_Attack() const;
	const int& Get_Defence() const;
	const int& Get_Speed() const;
	
	void Set_Hp(const int& hp);
	void Set_Attack(const int& attack);
	void Set_Defence(const int& defence);
	void Set_Speed(const int& speed);


private:
	int hp;
	int attack;
	int defence;
	int speed;
};

void Reset_Object_Info(Object_Info& o_info, const int& hp, const int& attack, const int& defence, const int& speed);

class Player_Info : public Object_Info {
public:

	const int& Get_Level() const;
	const int& Get_Mp() const;
	const bool& Is_No_Damage() const;

	void Set_Level(const int& level);
	void Set_Mp(const int& mp);
	void Set_No_Damage(const bool& damage);

private:
	int level;
	int mp;
	bool no_damage;
};

void Reset_Player_Info(Player_Info& p_info, const int& hp, const int& mp, const int& attack, const int& defence, const int& speed);



class Enemy_Info : public Object_Info {

};
