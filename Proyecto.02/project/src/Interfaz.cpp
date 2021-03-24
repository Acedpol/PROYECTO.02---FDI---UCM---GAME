#include "Interfaz.h"
#include "Button.h"
#include "callbacks.h"
#include "SDLGame.h"

void Interfaz::createMovement()
{
	SDLGame* game_ = g_->getSDLGame();
	Panel* p = new Panel(Movement);
	allPanels.push_back(p);
	p->addButton(new Button(game_, g_, mngr_, Vector2D(100, 100), 50, 50, Resources::Asteroid));
	p->addButton(new Button(game_, g_, mngr_, Vector2D(150, 100), 50, 50, Resources::Asteroid));
	p->addButton(new Button(game_, g_, mngr_, Vector2D(200, 100), 50, 50, Resources::Asteroid));
	Button* b = new Button(game_, g_, mngr_, Vector2D(250, 100), 50, 50, Resources::WhiteRect);
	p->addButton(b);
	b->setCB(callbacksOnClick::pruebaGame);
}

Interfaz::Interfaz(Game* juego, EntityManager* manager)
{
	g_ = juego;
	mngr_ = manager;
	createPanel(Movement);
	createPanel(Minimap);
	createPanel(Heroes);
	createPanel(Info);
}

Interfaz::~Interfaz()
{
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
		createHeroesStats();
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
	}
}

void Interfaz::destroyPanel(idPanel panelID)
{
	bool encontrado = false;
	int i = 0;
	while (!encontrado && i < contador) {
		//encontrado = allPanels->GetID() == panelID;
		++i;
	}

	//if (encontrado) delete allPanels[i];
}

