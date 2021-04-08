#include "CharacterSheet.h"


bool CharacterSheet::recieveDamage(int damage, rpgLogic::damageType type)
{
	float res = weaknesses.getWeakness(type);

	damage -= damage * int(res);

	cout << name << " recieves " << damage << " damage" << endl;

	_hitPoints -= damage;

	if (_hitPoints < 0)
		_hitPoints = 0;

	return !_hitPoints;
}

void CharacterSheet::recieveHealing(int healing)
{
	_hitPoints += healing;

	cout << name << " heals for " << healing << " points" << endl;

	if (_hitPoints > _maxHitPoints)
		_hitPoints = _maxHitPoints;
}

/*void CharacterSheet::recieveBuff(int buff,mainStat st)
{
	//cambiar el _hitPoints por el stat que aumenta

	_stats[st].value += buff;

	//cout << name << " aumenta su "<< stat << buff << " puntos" << endl;

	
}*/