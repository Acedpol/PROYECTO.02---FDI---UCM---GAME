#pragma once

#include <vector>
#include "RPGLogic.h"
#include <string>

using namespace rpgLogic;

class Character;

#pragma region HABILITY

enum ObjectiveType
{
	SINGLEALLY,
	SINGLEENEMY,
	ALLYTEAM,
	ENEMYTEAM,
	CASTER
};

enum HabilityType {
	ATTACK,
	DEBUFF,
	HEAL,
	BUFF
};

class Hability {
protected:
	int level = 0;
	int _mana = 0;
	std::string _name = "DefaultName";
	std::string _description = "DefaultDescription";

	damageType _damageType = damageType(0);
	mainStat _mod = _LastStatId_;
	ObjectiveType _obj = CASTER;

	HabilityType _habilityType  = ATTACK;

	Character* _caster;

public:

	Hability() :_caster(nullptr) {}

	Hability(Character* caster) :_caster(caster) {}

	~Hability() {}

	int getMana() { return _mana; }

	Character* getCaster() { return _caster; }

	virtual void throwHability(Character* obj, bool critical)const = 0;

	std::string name() { return _name; }

	std::string description() { return _description; }

	mainStat getMod() { return _mod; }

	ObjectiveType getObjectiveType() { return _obj; }

	HabilityType getHabilityType() { return _habilityType; }
};

class LightAttack : public Hability {
public:
	LightAttack(Character* caster) :Hability(caster) {
		level = 0;
		_mana = 0;
		_name = "Light Attack";
		_description = "Golpe to guapo con el arma, a terminar";

		_habilityType = ATTACK;
		_mod = STR;
		_obj = SINGLEENEMY;
	}

	void throwHability(Character* obj, bool critical)const override;
};

class Fireball : public Hability {
public:
	Fireball(Character* caster) :Hability(caster) {	

		level = 4;
		_mana = 0;
		_name = "Fireball";
		_description = "Bola de fuego to guapa, a hace 8d6 a todos los enemigos frente a salvacion DEX";

		_damageType = FIRE;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = ENEMYTEAM;
	}

	void throwHability(Character* obj, bool critical)const override;
};


class SingleTargetAttackExample : public Hability {
public:
	SingleTargetAttackExample(Character* caster) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "SingleTargetAttackExample";
		_description = "Esto es un ejemplo, hace 1d5 de da�o";

		_damageType = ICE;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	void throwHability(Character* obj, bool critical)const override;
};



class SingleTargetHealxample : public Hability {
public:
	SingleTargetHealxample(Character* caster) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "SingleTargetHealxample";
		_description = "Esto es un ejemplo, cura 2d5 de vida a un aliado";

		_damageType = LIGHT;
		_habilityType = HEAL;
		_mod = INT;
		_obj = SINGLEALLY;
	}

	void throwHability(Character* obj, bool critical)const override;
};


class AllyTeamHealExample : public Hability {
public:
	AllyTeamHealExample(Character* caster) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "AllyTeamHealExample";
		_description = "Esto es un ejemplo, cura a todo tu equipo 1d5";

		_damageType = LIGHT;
		_habilityType = HEAL;
		_mod = INT;
		_obj = ALLYTEAM;
	}

	void throwHability(Character* obj, bool critical)const override;
};


class SelfHealExample : public Hability {
public:
	SelfHealExample(Character* caster) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "SelfHealExample";
		_description = "Esto es un ejemplo, te cura 1d8";

		_damageType = LIGHT;
		_habilityType = HEAL;
		_mod = INT;
		_obj = CASTER;
	}

	void throwHability(Character* obj, bool critical)const override;
};


class AllyTeamAttackExample : public Hability {
public:
	AllyTeamAttackExample(Character* caster) :Hability(caster) {

		level = 0;
		_mana = 0;
		_name = "AllyTeamAttackExample";
		_description = "Esto es un ejemplo, se te va la cabeza y haces 2d4 de da�o a tu equipo";

		_damageType = DARK;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = ALLYTEAM;
	}

	void throwHability(Character* obj, bool critical)const override;
};

//-----------------------------------------------------------------------------

class WindBurst : public Hability {
public:
	WindBurst(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "WindBurst";
		_description = "Sal a que te de el aire, hace 8d6 a todos los enemigos frente a salvacion DEX (reduce DEX)";

		_damageType = WIND;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = ENEMYTEAM;
	}

	void throwHability(Character* obj, bool critical)const override;
};

class WindSlash : public Hability {
public:
	WindSlash(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Wind Slash";
		_description = "Menuda brisa, a hace 1d8 a un enemigo frente a salvacion DEX";

		_damageType = WIND;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	void throwHability(Character* obj, bool critical)const override;
};

class RockPillar : public Hability {
public:
	RockPillar(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Rock Pillar";
		_description = "Mejorando la estructura, a hace 1d8 a un enemigo frente a salvacion DEX (reduce CON)";

		_damageType = WIND;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	void throwHability(Character* obj, bool critical)const override;
};

class ToxicShadow : public Hability {
public:
	ToxicShadow(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Toxic Shadow";
		_description = "Sientes cosquillas, a hace 1d8 a un enemigo frente a salvacion DEX (puede causar envenenamiento)";

		_damageType = WIND;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	void throwHability(Character* obj, bool critical)const override;
};

class Tsunami : public Hability {
public:
	Tsunami(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Tsunami";
		_description = "Avisaron de bandera roja, a hace 8d6 a todos los enemigos frente a salvacion DEX (y reduce STR)";

		_damageType = WATER;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = ENEMYTEAM;
	}

	void throwHability(Character* obj, bool critical)const override;
};

class DivineProtection : public Hability {
public:
	DivineProtection(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Divine protection";
		_description = "Reduce el da�o recibido en el proximo ataque";

		_damageType = LIGHT;
		_habilityType = BUFF;
		_mod = INT;
		_obj = CASTER;
	}

	void throwHability(Character* obj, bool critical)const override;
};

class Flash : public Hability {
public:
	Flash(Character* caster) :Hability(caster) {

		level = 4;
		_mana = 0;
		_name = "Flash";
		_description = "Sonrie, a hace 1d8 a un enemigo frente a salvacion DEX(reduce DEX)";

		_damageType = LIGHT;
		_habilityType = ATTACK;
		_mod = INT;
		_obj = SINGLEENEMY;
	}

	void throwHability(Character* obj, bool critical)const override;
};

#pragma endregion