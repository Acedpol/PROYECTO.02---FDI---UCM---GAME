#ifndef _CHARACTER_SHEET_
#define _CHARACTER_SHEET_
#include "Component.h"
#include "RPGLogic.h"
#include "checkML.h"

using namespace rpgLogic;

class CharacterSheet : public Component
{
private:

	//Caracteristicas 
	vector<Stat> _stats;

	//Salud
	int _hitPoints = 10;
	int _maxHitPoints = 10;
	//Mana
	int _manaPoints = 10;
	int _maxManaPoints = 10;

public:

	//Debilidades
	Weaknesses weaknesses;

	//Nombre del personaje ( o enemigo)
	string name = "DefaultClass";

	CharacterSheet() :Component(ecs::CharacterSheet),
		weaknesses(), _stats(vector<Stat>(4, { 10 }))
	{
	}

	~CharacterSheet(){}

	Stat getStat(mainStat st) {
		return _stats[st];
	}

	void setStat(mainStat st, int set) {
		_stats[st].value = set;
	}

	void setStat(int st, int set) {
		_stats[st].value = set;
	}

	int maxHitPoints() {
		return _maxHitPoints;
	}

	int maxManaPoints() {
		return _maxManaPoints;
	}

	int hitPoints() {
		return _hitPoints;
	}

	int manaPoints() {
		return _manaPoints;
	}

	void setMaxHitPoints(int set) {
		_maxHitPoints = set;
	}

	void setMaxManaPoints(int set) {
		_maxManaPoints = set;
	}

	void setHitPoints(int set) {
		_hitPoints = set;
	}

	void setManaPoints(int set) {
		_manaPoints = set;
	}

	void changeStat(mainStat st, int change) {
		_stats[st].value += change;
	}

	bool recieveDamage(int damage, rpgLogic::damageType type);

	void recieveHealing(int healing);

	//void recieveBuff(int buff,mainStat st);
};
#endif