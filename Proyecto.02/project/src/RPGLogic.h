#ifndef _RPG_LOGIC
#define _RPG_LOGIC

class RpgLogic {
public:
	enum damageType {
	// Da�os f�sicos
	BLUNT,
	PIERCE,
	SLASH,
	// Da�os Elementales
	FIRE,
	WATER,
	ICE,
	EARTH,
	WIND,
	LIGHT,
	DARK
	};

	enum modStat{
		STR,
		DEX,
		CON,
		INT,
		NULLMOD
	};
};


#endif // !