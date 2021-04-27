#pragma once

#include <SDL.h>
#include <string>
#include <vector>

using namespace std;

class Resources {
public:

	enum TextureId : std::size_t {
		// images
		posMiniMap,
		camino_izq,
		camino_der,
		camino_fr,
		muro_izq,
		muro_der,
		muro_fr,
		no_visitado,
		no_entrado,
		visitado,
		pared_N,
		pared_E,
		pared_S,
		pared_O,
		cargando,

		// text
		HelloWorld,
		PressAnyKey,
		GameOverWon,
		GameOverLost,

		// heroes
		Bardo,
		Brujo,
		Clerigo,
		Guerrero,
		Paladin,
		Barbaro,
		Explorador,
		Picaro,
		Druida,
		Bestia,
		GranArchimago,

		// UI
		Mouse,
		Fondo,

		// movement
		Avanzar,
		RotarD,
		RotarI,
		Interactuar,

		//Info
		Inventario,
		PocionVida,
		PocionMana,
		PocionRess,
		Chat,
		Configuracion, 

		//Combate
		AtaqueNormal,
		AtaqueMagico, 
		Defensa,
		Huida,
		Marco,

		//Inventario
		Slot,
		EmptySword,
		EmptyArmor,
		WeaponSlot,
		ArmorSlot,

		//Objetos
		Desarmado,
		Baston,
		Daga,
		Clava,
		HachaPequena,
		Hoz,
		Lanza,
		MartilloPequeno,
		Maza,
		ArcoPequeno,
		BallestaLigera,

		// Comodin
		Joker,

		//Armas Marciales
		Alabarda,
		Atarraga,
		EspadaCorta,
		EspadaLarga,
		Espadon,
		EspadaRopera,
		HachaBatalla,
		Guja,
		Latigo,
		LuceroAlba,
		MartilloGuerra,
		Pica,
		Tridente,
		ArcoLargo,
		BallestaPesada,

		//Armaduras
		Acolchada,
		CueroTachonado,
		CotaEscamas,
		Coraza,
		SemiPlacas,
		CotaMalla,
		Bandas,
		Placas,

		//Ficha DD
		Pergamino
	};

	enum AudioId : std::size_t {
		// music
		ImperialMarch,

		// sound effects
		Explosion,
		GunShot
	};

	enum FontId : std::size_t {
		ARIAL16, ARIAL24, HERMAN, Fornite, Quake, KillerInst, Sega, Beaulieux, Triforce
	};

	enum JsonId : std::size_t {
		Heroes,
		Enemies,
		Weapons,
		Armors
	};

	struct FontInfo {
		FontId id;
		string fileName;
		int size;
	};

	struct ImageInfo {
		TextureId id;
		string fileName;
	};

	struct TextMsgInfo {
		TextureId id;
		string msg;
		SDL_Color color;
		FontId fontId;
	};

	struct MusicInfo {
		AudioId id;
		string fileName;
	};

	struct SoundInfo {
		AudioId id;
		string fileName;

	};

	struct JsonInfo {
		JsonId id;
		string filename;
	};

	static vector<FontInfo> fonts_; // initialized in .cpp
	static vector<ImageInfo> images_; // initialized in .cpp
	static vector<TextMsgInfo> messages_; // initialized in .cpp
	static vector<MusicInfo> musics_; // initialized in .cpp
	static vector<SoundInfo> sounds_; // initialized in .cpp
	static vector<JsonInfo> jsons_; // initialized in .cpp
	//static vector<ClassTemplates> classTemplates_;

};
