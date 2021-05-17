#include "Interfaz.h"
#include "../ecs/ecs.h"
#include "../Templates/callbacks.h"
#include "../GameObjects/Button.h"
#include "../GameObjects/Character.h"
#include "Image.h"
#include "Transform.h"
#include "StateBar.h"
#include "../Utilities/SDL_macros.h"
#include "../Utilities/textures_box.h"
#include "../Managers/SDLGame.h"
#include "../Managers/TheElementalMaze.h"
#include "../Managers/game/PartyManager.h"
#include "../Managers/game/InterfazManager.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/LobbyManager.h"


using cb = callbacks;
using src = Resources;
using namespace textures_box;

Interfaz::~Interfaz()
{
	for (auto it = allPanels.begin(); it != allPanels.end(); ++it)
	{
		delete (*it);
	}
	allPanels.clear();
}

void Interfaz::createFight()
{
	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	// espacios entre objetos
	double espace = game_->setHorizontalScale((w_ - n) / 4);

	// ancho y alto de cada objeto
	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Fight);
	allPanels[Fight] = p;

	// BOTONES: normal, magic, defend, escape
	p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + 0, y_), w_, h_, src::AtaqueNormal, CmbtType::attack));
	p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace, y_), w_, h_, src::AtaqueMagico, CmbtType::magic));
	p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace * 2, y_), w_, h_, src::Defensa, CmbtType::defend));
	p->addButton(iManager->addButton<ButtonCombate>(Vector2D(x_ + espace * 3, y_), w_, h_, src::Huida, CmbtType::escape));
}

void Interfaz::createEnemies()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	std::vector<Enemy*> enemies = c->getEnemiesTeam();
	uint nEnemies = c->getEnemysTam();

	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 70;
	// tamano en pixeles del 'fondo'
	double w_ = 1340;
	double h_ = 620;
	// tamano de los margenes
	double n = 50;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	// espacios entre objetos
	double espace = game_->setHorizontalScale((w_ - n) / 4);

	// ancho y alto de cada objeto
	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Enemies);
	allPanels[Enemies] = p;

	for (int i = 0; i < nEnemies; i++) {
		SDL_Object* b_ = iManager->addButton<SDL_Object>(Vector2D(x_ + i * espace, y_), w_, h_, getEnemyTxt(i));
		uint k = 6;
		b_->addComponent<StateBar>(enemies[i], health, SDL_Rect(RECT((x_ + i * espace), (y_ + h_ * 1 / k), w_ * 2, h_ / k)));
		//b_->addComponent<StateBar>(enemies[i], mana, SDL_Rect(RECT((x_ + i * espace), (y_ + h_ * 2.5 / k), w_ * 2, h_ / k)));
		p->addButton(b_);
	}
}

void Interfaz::createMovement()
{
	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	/* || 20px - button - 20px - button - 20px - button - 20px - button - 20px - button - 20px || */
	double espace = game_->setHorizontalScale((w_ - n) / 4);

	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Movement);
	allPanels[Movement] = p;

	// BOTONES: rotR, rotL, forward, touch
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + 0, y_), w_, h_, src::RotarI, MovType::rotL));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace, y_), w_, h_, src::Avanzar, MovType::forward));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace * 2, y_), w_, h_, src::RotarD, MovType::rotR));
	p->addButton(iManager->addButton<ButtonMovimiento>(Vector2D(x_ + espace * 3, y_), w_, h_, src::Interactuar, MovType::touch));
}

void Interfaz::createHeroes()
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();
	uint nHeros = heroes.size();

	// posicion en pixeles del 'fondo'
	double x_ = 1510;
	double y_ = 360;
	// tamano en pixeles del 'fondo'
	double w_ = 340;
	double h_ = 330;
	// tamano de los margenes
	double n = 5.0 + 5.0;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	double espace = game_->setVerticalScale((h_ - n) / nHeros);

	h_ = espace - game_->setVerticalScale(n);
	w_ = h_;

	// construccion del panel de heroes
	Panel* p = new Panel(Heroes);
	allPanels[Heroes] = p;

	// BOTONES: hero1, hero2, hero3, hero4
	for (int i = 0; i < nHeros; i++) {
		ButtonHero* b_ = iManager->addButton<ButtonHero>(Vector2D(x_, y_ + i * espace), w_, h_, getHeroTxt(i), (HeroNum)i, DDPan, false);
		uint k = 6;
		b_->addComponent<StateBar>(heroes[i], health, SDL_Rect(RECT((x_ + w_ + n), (y_ + i * espace + h_ * 1 / k), w_ * 2, h_ / k)));
		b_->addComponent<StateBar>(heroes[i], mana, SDL_Rect(RECT( (x_ + w_ + n), (y_ + i * espace + h_ * 2.5 / k), w_ * 2, h_ / k )));
		b_->addComponent<StateBar>(heroes[i], experience, SDL_Rect(RECT( (x_ + w_ + n), (y_ + i * espace + h_ * 4 / k), w_ * 2, h_ / k )));
		p->addButton(b_);
	}
}

void Interfaz::createInfo()
{
	uint nInfoButton_H = 4; // separaciones horizontales
	uint nInfoButton_V = 2; // separaciones verticales

	// posicion en pixeles del 'fondo'
	double x_ = 880;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 530;
	double h_ = 190;
	// tamano de los margenes
	double n = 5;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	double espace_H = game_->setHorizontalScale((w_ - n) / nInfoButton_H);
	double espace_V = game_->setVerticalScale((h_ - n) / nInfoButton_V);

	w_ = espace_H - game_->setHorizontalScale(n);
	h_ = espace_V - game_->setVerticalScale(n);

	// construccion del panel de informacion
	Panel* p = new Panel(Info);
	allPanels[Info] = p;

	// BOTONES: health, mana, resurrection
	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_, y_), w_ * 2, h_ * 2, src::Inventario, Inventory, false));
	p->addButton(iManager->addButton<ButtonPotion>(Vector2D(x_ + 2 * espace_H, y_ + 0 * espace_V), w_, h_, src::PocionVida, PtnType::health));
	p->addButton(iManager->addButton<ButtonPotion>(Vector2D(x_ + 2 * espace_H, y_ + 1 * espace_V), w_, h_, src::PocionMana, PtnType::mana));
	//p->addButton(iManager->addButton<ButtonPotion>(Vector2D(width * 5 / 7, height * 5 / 6 + space), tamBoton * 0.8, tamBoton * 0.8, src::PocionRess, PtnType::resurrection));

	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_ + 3 * espace_H, y_ + 0 * espace_V), w_, h_, src::Chat, Chat, false));
	p->addButton(iManager->addButton<ButtonPanel>(Vector2D(x_ + 3 * espace_H, y_ + 1 * espace_V), w_, h_, src::Configuracion, Settings, false));
} // 

void Interfaz::createInventory()
{
	SDLGame* game_ = entity_->getSDLGame();

	double slotTam = game_->getWindowWidth() / 16;
	double posX;
	double posY = slotTam * 1.8;

	Panel* p = new Panel(Inventory);
	//allPanels.emplace(allPanels.begin() + Inventory, p);
	allPanels[Inventory] = p;

	// Cuadro de inventario 5x5
	for (int i = 0; i < 5; ++i) {

		posX = slotTam * 1.5; //Se resetea la coordenada X

		for (int j = 0; j < 5; ++j) {
			p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX, posY), slotTam, slotTam, src::Slot));
			posX += slotTam;
		}

		posY += slotTam; // Se suma la coordenada Y
	}

	posX += slotTam; // Se suma la coordenada X dejando un espacio.
	posY = slotTam * 1.8;
	int margen = 6;

	// Inventario personajes: clase + arma + armadura
	for (int i = 0; i < 4; ++i) {
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX, posY), slotTam, slotTam, getHeroTxt(i)));
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX + slotTam, posY), slotTam, slotTam, src::WeaponSlot));
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(posX + slotTam * 2, posY), slotTam, slotTam, src::ArmorSlot));

		posY += slotTam * 1.33;
	}
}

void Interfaz::createFichaDD(uint nCharacter)
{
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();

	Character* hero = heroes[nCharacter];
	CharacterSheet* hero_sheet = hero->getCharacterSheet();

	uint nInfoButton_H = 3; // separaciones horizontales
	uint nInfoButton_V = 3; // separaciones verticales

	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 70;
	// tamano en pixeles del 'fondo'
	double w_ = 1340;
	double h_ = 620;
	// tamano de los margenes
	double _nw = 50;
	double _nh = 50;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + _nw);
	y_ = game_->setVerticalScale(y_ + _nh);

	// dmensiones delpanel
	w_ = game_->setHorizontalScale(w_ - _nw * 2);	// ancho panel
	h_ = game_->setVerticalScale(h_ - _nh * 2);	// alto panel
	
	// construccion y asignacion del panel:
	Panel* p = new Panel(DDPan);
	allPanels[DDPan] = p;

	// Fondo:
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(x_, y_), w_, h_, src::Pergamino));
	
	_nw = 10;
	_nh = 10;
	// posicion del primer button respecto al panel
	double k = 3.75;
	double xs_ = game_->setHorizontalScale(x_ + w_ * k / 10);
	double ys_ = game_->setVerticalScale(y_ + h_ * k / 10);
	k = 2;
	double espace_H = w_ * (k / 10);
	double espace_V = h_ * (k / 10);
	// dimensiones de cada cuadrante
	double ws_ = espace_H - game_->setHorizontalScale(_nw);	// ancho cuadrante
	double hs_ = espace_V - game_->setVerticalScale(_nh);	// alto cuadrante
	double lineTam_V = espace_V * 2 / 8;

	SDL_Color color = { 0,0,0,255 };
	// Titulo:
	p->addButton(iManager->addButton<Line>(Vector2D(xs_, ys_ - espace_V * 1 / 3), ws_ * 3, hs_, hero->name(), Resources::Beaulieux, color));

	// icono heroe:
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(xs_ + 1 * espace_H + (abs(ws_ - hs_) / 2), ys_ + 1 * espace_V), hs_, hs_, getHeroTxt((uint)nCharacter)));

	string info = ""; // auxiliar para recopilar todo en caso de poder sacarlo en una sola linea.

	// VIDA y MANA:
	string text = "Health = " + to_string(hero_sheet->maxHitPoints()); info += text + "\n";		// Health
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 0 * espace_H, ys_ + 1 * espace_V + lineTam_V * 0), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Mana = " + to_string(hero_sheet->maxManaPoints()); info += text + "\n";				// Mana
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 0 * espace_H, ys_ + 1 * espace_V + lineTam_V * 1), ws_, lineTam_V, text, Resources::Beaulieux, color));

	// MAIN STATS:
	text = "Strength = " + to_string(hero_sheet->getStat(STR).value); info += text + "\n";		// Fuerza
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 0 * espace_H, ys_ + 1 * espace_V + lineTam_V * 3), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Constitution = " + to_string(hero_sheet->getStat(CON).value); info += text + "\n";	// Constitution
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 0 * espace_H, ys_ + 1 * espace_V + lineTam_V * 4), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Dexterity = " + to_string(hero_sheet->getStat(DEX).value); info += text + "\n";		// Destreza
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 0 * espace_H, ys_ + 1 * espace_V + lineTam_V * 5), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Intelect = " + to_string(hero_sheet->getStat(INT).value); info += text + "\n";		// Intelecto
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 0 * espace_H, ys_ + 1 * espace_V + lineTam_V * 6), ws_, lineTam_V, text, Resources::Beaulieux, color));

	// RESISTENCIAS:
	text = "Fire = " + to_string(hero_sheet->getResistance(FIRE)); info += text + "\n";			// Fire
	color = { 255,0,0,255 };
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 2 * espace_H, ys_ + 1 * espace_V + lineTam_V * 0), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Water = " + to_string(hero_sheet->getResistance(WATER)); info += text + "\n";		// Water
	color = { 0,0,255,255 };
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 2 * espace_H, ys_ + 1 * espace_V + lineTam_V * 1), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Ice = " + to_string(hero_sheet->getResistance(ICE)); info += text + "\n";			// Ice
	color = { 155,155,255,255 };
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 2 * espace_H, ys_ + 1 * espace_V + lineTam_V * 2), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Earth = " + to_string(hero_sheet->getResistance(EARTH)); info += text + "\n";		// Earth
	color = { 155,80,20,255 };
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 2 * espace_H, ys_ + 1 * espace_V + lineTam_V * 3), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Wind = " + to_string(hero_sheet->getResistance(WIND)); info += text + "\n";			// Wind
	color = { 0, 150, 0,255 };
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 2 * espace_H, ys_ + 1 * espace_V + lineTam_V * 4), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Light = " + to_string(hero_sheet->getResistance(LIGHT)); info += text + "\n";		// Light
	color = { 255,255,150,255 };
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 2 * espace_H, ys_ + 1 * espace_V + lineTam_V * 5), ws_, lineTam_V, text, Resources::Beaulieux, color));
	text = "Dark = " + to_string(hero_sheet->getResistance(DARK)); info += text + "\n";			// Dark
	color = { 50,50,50,255 };
	p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 2 * espace_H, ys_ + 1 * espace_V + lineTam_V * 6), ws_, lineTam_V, text, Resources::Beaulieux, color));

	// ARMA & ARMADURA:
	Hero* hero_ = dynamic_cast<Hero*>(hero);
	if (hero_ != nullptr)
	{
		Armor* armor_ = hero_->getArmor();		// Armadura
		Weapon* weapon_ = hero_->getWeapon();	// Arma
	}

	// No funciona bien lo ponerlo en una sola linea: (prueba si quieres)
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(xs_ + 1 * espace_H + (abs(ws_ - hs_) / 2), ys_ + 2 * espace_V + (abs(ws_ - hs_) / 2)), hs_ / 2, hs_ / 2, Resources::WeaponSlot));
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(xs_ + 1.5 * espace_H, ys_ + 2 * espace_V + (abs(ws_ - hs_) / 2)), hs_ / 2, hs_ / 2, Resources::ArmorSlot));
	//p->addButton(iManager->addButton<Line>(Vector2D(xs_ + 2 * espace_H, ys_ + 1 * espace_V + lineTam_V * 0), ws_, lineTam_V * 4, info, Resources::Beaulieux,color));
}

void Interfaz::createTargets()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	uint nEnemys = c->getEnemysTam();

	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	double espace = game_->setHorizontalScale((w_ - n) / 4);

	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Targets);
	allPanels[Targets] = p;

	// BOTONES:
	for (int i = 0; i < 4/*nEnemys*/; i++) {
		p->addButton(iManager->addButton<ButtonTarget>(Vector2D(x_ + espace * i, y_), w_, h_, src::Target, (target)i));
	}
}

void Interfaz::createHabilities()
{
	CombatManager* c = GETCMP2(TheElementalMaze::instance(), CombatManager);
	uint nEnemys = c->getEnemysTam();

	// posicion en pixeles del 'fondo'
	double x_ = 70;
	double y_ = 790;
	// tamano en pixeles del 'fondo'
	double w_ = 710;
	double h_ = 190;
	// tamano de los margenes
	double n = 20;

	// posicion del panel respecto a la ventana
	x_ = game_->setHorizontalScale(x_ + n);
	y_ = game_->setVerticalScale(y_ + n);

	double espace = game_->setHorizontalScale((w_ - n) / 4);

	w_ = espace - game_->setHorizontalScale(n);
	h_ = game_->setVerticalScale(h_ - n * 2);

	// construccion y asignacion del panel:
	Panel* p = new Panel(Habilities);
	allPanels[Habilities] = p;

	// BOTONES:
	for (int i = 0; i < nEnemys; i++) {
		p->addButton(iManager->addButton<ButtonHability>(Vector2D(x_ + espace * i, y_), w_, h_, src::Hability, (HbltType)i));
	}
	togglePanel(Fight); // oculta el panel fight
}

void Interfaz::createMenuPrincipal()
{
	Panel* p = new Panel(MenuPrincipal);
	allPanels[MenuPrincipal] = p;
	int w,  h;
	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(0, 0), w, h, src::mFondo));

	int x, y;
	x = w / 2 - 150;	y = h / 2 - 50;
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(x,y ), 300, 100, src::start, accionMenu::start, this));
	y += 120;
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(x,y), 300, 100, src::options, accionMenu::options, this));
	y += 120;
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(x,y), 300, 100, src::howToPlay, accionMenu::how_to_play, this));
	y += 120;
	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(x,y), 300, 100, src::quit, accionMenu::quit, this));
}

void Interfaz::createLobby()
{
	Panel* p = new Panel(Lobby);
	allPanels[Lobby] = p;
	int w, h ,x,y;
	string text;
	SDL_Color color;

	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(0, 0), w, h, src::lobFondo));


	y = 50;
	color = { 205,105,0,255 };
	text = "Tu equipo de combate";
	p->addButton(iManager->addButton<Line>(Vector2D(w/2 - text.size()*15, y), text.size() * 30, 70, text, Resources::FontId::Fornite, color));
	
	int esp = (w - 6 * 100)/7;
	y += 120;
	LobbyManager* loManager = TheElementalMaze::instance()->getLobbyManager();

	int tam;
	
	/*tam = loManager->getPlayerStash()->heroes.size();
	for (int i = 0; i < 6 && i<tam ; i++)
	{
		Hero* her = loManager->getPlayerStash()->heroes[i];
		auto tex = src::_firstHeroRId_ + her->getTemplate()+1;
		x = esp + 100 * i +esp*i;
		p->addButton(iManager->addButton<ButtonSlott>(Vector2D(x, y), 70, 100, static_cast<Resources::TextureId>(tex)));
		p->addButton(iManager->addButton<ButtonHeroEquipar>(Vector2D(x, y + 100), 100, 60, src::howToPlay, i, this));
	}*/

	if (loManager->getLobbyStore() != nullptr)
	{

		y += 150;
		text = "Heroes que puedes comprar";
		p->addButton(iManager->addButton<Line>(Vector2D(w / 2 - text.size() * 15, y), text.size() * 30, 70, text, Resources::FontId::Fornite, color));


		y += 70;
		color = { 155,155,0,255 };
		tam = loManager->getLobbyStore()->heroes.size();
		for (int i = 0; i < 6 && i < tam; i++)
		{
			HeroContract* her = loManager->getLobbyStore()->heroes[i];
			int tex = src::_firstHeroRId_ + her->hero->getTemplate()+1;
			x = esp + 100 * i + esp * i;
			p->addButton(iManager->addButton<ButtonSlott>(Vector2D(x, y), 100, 100, static_cast<Resources::TextureId>(tex)));
			text = "x" + to_string(her->price);
			p->addButton(iManager->addButton<Line>(Vector2D(x-text.size()*8, y + 110), text.size()*15, 50, text, Resources::FontId::Fornite, color));
			p->addButton(iManager->addButton<ButtonCompra>(Vector2D(x + 45, y + 110), 70, 50, src::howToPlay, i, 0, this));
		}
		color = { 205,105,0,255 };


		y += 180;
		text = "Items que puedes comprar";
		p->addButton(iManager->addButton<Line>(Vector2D(w / 2 - text.size() * 15, y), text.size() * 30, 70, text, Resources::FontId::Fornite, color));

		y += 70;
		tam = loManager->getLobbyStore()->items.size();
		for (int i = 0; i < 6 && i < tam; i++)
		{
			ItemToBuy* it = loManager->getLobbyStore()->items[i];
			int tex = src::_firstWeaponId_ + it->item->getItemType()+1;
			x = esp + 100 * i + esp * i;
			p->addButton(iManager->addButton<ButtonSlott>(Vector2D(x, y), 100, 100, static_cast<Resources::TextureId>(tex)));
			text = "x" + to_string(it->sold);
			p->addButton(iManager->addButton<Line>(Vector2D(x-text.size()*8, y + 110), text.size()*15, 50, text, Resources::FontId::Fornite, color));
			p->addButton(iManager->addButton<ButtonCompra>(Vector2D(x + 45, y + 110), 70, 50, src::howToPlay, i, 1, this));
		}
	}
	



	

}

void Interfaz::createOptions()
{
	Panel* p = new Panel(Options);
	allPanels[Options] = p;
	int w, h;
	int x, y;
	int ancho;
	string text;
	SDL_Color color;

	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(0, 0), w, h, src::mFondo));

	
	x = w / 2 - 200; y = 100;
	color = { 0,0,0,255 };
	text = "Options";
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), 400, 200, text, Resources::FontId::HERMAN, color));

	x = w / 2 - 75;
	y += 75;
	text = "Volume"; //Volumen con 4 botones
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), 150, 40, text, Resources::FontId::HERMAN, color));
	//
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::volumen, 1, this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::volumen, 2,this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::volumen, 3,this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::volumen, 4,this));
	
	x = w / 2 - 100;
	y += 50;
	text = "Animation speed";
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), 200, 40, text, Resources::FontId::HERMAN, color));
	//x0.5 x1 x2 x4
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::velocidad,1 , this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::velocidad,2,this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::velocidad,3, this));
	//p->addButton(iManager->addButton<ButtonOption>(Vector2D(w - 100, 36), 64, 64, src::close, accionOption::velocidad,4,this));


	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 100, 36), 64, 64, src::close, accionMenu::options, this));

}

void Interfaz::createGuide()
{
	Panel* p = new Panel(HowToPlay);
	allPanels[HowToPlay] = p;
	int w, h;
	int x, y;
	int ancho;
	string text;
	SDL_Color color;

	w = game_->getWindowWidth();
	h = game_->getWindowHeight();
	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(0, 0), w, h, src::mFondo));

	p->addButton(iManager->addButton<ButtonSlott>(Vector2D(100, 100), w-200, h-200, src::Pergamino));

	x = w / 2 - 200; y = 250;
	color = {0,0,0,255};
	text = "How To Play";
	p->addButton(iManager->addButton<Line>(Vector2D(x,y),400,100, text, Resources::FontId::HERMAN, color));

	color = { 100,50,0,255 };
	x = 250; y = 370;
	text = "Click on the virtual buttons to play the game";
	ancho = text.size() * 15 - 100;
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite, color));

	color = { 150,150,0,255 };
	y += 50;
	text = "Special Keyboards";
	ancho = text.size() * 20;
	p->addButton(iManager->addButton<Line>(Vector2D(x+150, y), ancho, 40, text, Resources::Fornite, color));

	color = { 100,50,0,255 };
	y += 50;
	text = "Press left-right arrows or A-D keys to rotate the view";
	ancho = text.size() * 15 -100;
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite, color));

	y += 30;
	text = "Press up arrows or W keys to advance";
	ancho = text.size() * 15 -30;
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho , 30, text, Resources::Fornite, color));

	y += 30;
	text = "Press spacebar or E keys to interact";
	ancho = text.size() * 15 - 50;
	p->addButton(iManager->addButton<Line>(Vector2D(x, y), ancho, 30, text, Resources::Fornite, color));	

	p->addButton(iManager->addButton<ButtonMenu>(Vector2D(w - 100, 36), 64, 64, src::close, accionMenu::how_to_play, this));

}


void Interfaz::createPanel(idPanel panelID)
{
	switch (panelID) {
	case Fight:
		createFight();
		break;
	case Movement:
		createMovement();
		break;
	case Minimap:
		createMinimap();
		break;
	case Heroes:
		createHeroes();
		break;
	case Info:
		createInfo();
		break;
	case Inventory:
		createInventory();
		break;
	case HeroesStats:
		//createFichaDD();
		break;
	case BigMap:
		createBigMap();
		break;
	case Turns:
		createTurns();
		break;
	case Settings:
		createSettings();
		break;
	case Chat:
		createChat();
		break;
	case Targets:
		createTargets();
		break;
	case Habilities:
		createHabilities();
		break;
	case MenuPrincipal:
		createMenuPrincipal();
		break;
	case HowToPlay:
		createGuide();
		break;
	case Options:
		createOptions();
		break;
	case Enemies:
		createEnemies();
		break;
	case Lobby:
		createLobby();
		break;
	default:
		break;
	}
}

void Interfaz::removePanel(idPanel panID)
{
	allPanels[panID]->removeButtons();
	allPanels[panID] = nullptr;
}

void Interfaz::destroyPanel(idPanel panelID)
{
	/*delete allPanels[panelID];
	allPanels[panelID] = nullptr;*/
}

void Interfaz::togglePanel(Panel* pan)
{
	pan->toggleEnable();
}

bool Interfaz::getEnablePan(idPanel panID)
{
	if (getActivePan(panID)) return allPanels[panID]->getEnable();
	else return false;
}

void Interfaz::toggleCombat_Movement()
{
	togglePanel(Fight);
	togglePanel(Movement);
}

void Interfaz::init()
{
	//allPanels.reserve(maxPanels);
	initialize(); // convertir a tipo std::map<clave, valor> -> ahora est� hardcodeado
	// Fondo de todo la interfaz, para delimitar claramente los paneles: 
	// (mejor que ButtonSlott ser�a crear unaclase foto/image y que button herede de ella)
	//iManager->addButton<ButtonSlott>(Vector2D(), game_->getWindowWidth(), game_->getWindowHeight(), src::Fondo); 
	createPanel(MenuPrincipal);
	createPanel(HowToPlay);
	createPanel(Options);

	togglePanel(HowToPlay);
	togglePanel(Options);


	
}

void Interfaz::update()
{
	InputHandler* ih_ = InputHandler::instance();
	if (ih_->isKeyDown(SDLK_t)) {
		// mouse event
		toggleCombat_Movement();
	}
	GameState state_ = TheElementalMaze::instance()->gameState();
	switch (state_)
	{
	case gameST::MainMenu:
		break;
	case gameST::LOBBY:
		break;
	case gameST::START_EXPLORING:
		if (!getActivePan(Movement))
		{
			createPanel(Movement);
			createPanel(Heroes);
			createPanel(Info);
		}
		break;
	case gameST::EXPLORING:
		if (!getEnablePan(Movement))
		{
			togglePanel(Movement);
			if (getActivePan(Fight)) {
				removePanel(Fight);
			}
			// PARTY
			checkHerosParty(); // check de puertas de la muerte
		}
		break;
	case gameST::COMBAT:
		if (!getActivePan(Fight))
		{
			togglePanel(Movement);
			createPanel(Fight);
			createPanel(Enemies);
		}
		break;
	case gameST::END_COMBAT:
		if (getActivePan(Enemies))
		{
			removePanel(Enemies);
			TheElementalMaze::instance()->changeState(gameST::COMBAT);
		}
		break;
	case gameST::END_EXPLORING:
		removePanel(Movement);
		removePanel(Heroes);
		removePanel(Info);
		break;
	default:
		break;
	}
}

Entity* Interfaz::getEntity()
{
	return entity_;
}

void Interfaz::checkActiveHeroButton(HeroNum nAct)
{
	ButtonPanel* b = allPanels[Heroes]->getButtonActive();
	if (b != nullptr) {
		ButtonHero* b_hero = dynamic_cast<ButtonHero*>(b);
		if (b_hero != nullptr && b_hero->getNumHero() != nAct) {
			b->turnOFF();
			removePanel(DDPan);
		}
	}
}

void Interfaz::checkHerosParty()
{
	bool changed = false;
	vector<Entity*> savedHeroes;
	PartyManager* c = TheElementalMaze::instance()->getPartyManager();
	std::vector<Hero*> heroes = c->getHeroes();
	auto n = heroes.size(); // max number of heros
	for (auto i = 0u; i < n; i++)
		if (heroes[i]->getDeathGate()) {
			allPanels[Heroes]->removeButton(i);
			changed = true;
		}
		else {
			savedHeroes.push_back(allPanels[Heroes]->getButton(i));
		}
	if (changed) allPanels[Heroes]->swapButtonList(savedHeroes);
}

void Interfaz::initialize()
{
	for (uint i = 0; i < maxPanels; ++i)
	{
		allPanels.push_back(nullptr);
	}
}

