#pragma once
#include "../ecs/Entity.h"
#include "../Templates/interfaz/ObjectPanel.h"
#include "../Utilities/interfaz/MousePanelMecanics.h"
#include "../ecs/Manager.h"

class Item;

const int NUM_ITEMS_IN_CHEST = 20;

class ObjectChest : public EntityManager, public ObjectPanel, public MousePanelMecanics
{
private:
	SDL_Panel pan;
	Entity* fondo_ = nullptr;
	int numItems_ = NUM_ITEMS_IN_CHEST;
	void addTemplate();
	void example();
	void itemChest(vector<Item*> items);

public:
	ObjectChest(SDLGame* game) : EntityManager(game) {
		pan = game_->relativePanel(1470, 320, 420, 410, 1, 4, 30, 30, 10, 10, 0, 5);
	};

	virtual ~ObjectChest() { 

		delete fondo_;
		fondo_ = nullptr;
		//entities.clear();
	};

	void Init();
	void update();
	void draw();

};
