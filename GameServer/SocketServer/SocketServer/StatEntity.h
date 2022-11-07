#pragma once
class StatEntity
{
private:
	int hp;
	int mp;

public:
	StatEntity() : hp(0), mp(0) {}
	void SetHp(int p_hp) { hp = p_hp; }
	void SetMp(int p_mp) { mp = p_mp; }
	int GetHp() { return hp; }
	int GetMp() { return mp; }
};

