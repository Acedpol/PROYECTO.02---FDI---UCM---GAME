#pragma once
#include <string>
#include <list>
#include "../ecs/Component.h"
#include "../Structures/Panel.h"

class Font;

class InterfazManager;

using namespace std;

class Interfaz : public Component {

private:
	bool tutorial_active;
	InterfazManager* iManager;
	std::vector<Panel*> allPanels;
	uint pagHeroes = 0;
	uint pagItems = 0;
	void createFight();
	void createEnemies();
	void createMovement();
	void createHeroes();
	void createInfo();
	void createInventory();
	void createBigMap() {}; //
	void createTurns(); //
	void createSettings() {}; //
	void createChat();
	void createTargets(); //
	void createHabilities(); //
	void createWeaponAttacks();
	void createInventoryLobby();
	void createSendToStashPanel();
	void createMenuPrincipal();
	void createLobby();
	void createOptions();
	void createGuide();
	void createShop();
	void createStash();
	void createInfoTienda();
	void createUnequipPanel();
	void toggleMinimap();
	string nameItemTienda;
	string descrItemTienda;
	void checkAndDeletePanel(idPanel id);
	void createHeroToPartyPanel();
	void createSellButtonPanel();
	void createEquipPanel();
	int selectedHeroToParty;
	bool isWeapon;
	bool isItemToEquipAWeapon;
	int selectedInventoryHero;
	int selectedInventoryItem;
	int selectedItem;
public:
	Interfaz(InterfazManager* i) :
		Component(ecs::Interfaz),
		allPanels(std::vector<Panel*>(maxPanels, nullptr)),
		iManager(i),
		tutorial_active(true)
	{};
	virtual ~Interfaz();

	void createPanel(idPanel panelID);
	void removePanel(idPanel panelID);
	void removeChat();
	void destroyPanel(idPanel panelID);

	void togglePanel(Panel* pan);
	void togglePanel(idPanel panID) { togglePanel(allPanels[panID]); };
	bool getEnablePan(idPanel panID);
	void avPagHeroes();
	void rePagHeroes();
	void avPagItems();
	void rePagItems();
	void toggleCombat_Movement();

	virtual void init() override;
	virtual void update() override;
	virtual void draw() override {};

	Entity* getEntity();
	bool getActivePan(idPanel pan) { return allPanels[pan] != nullptr; };
	void checkActiveHeroButton(HeroNum nAct);
	void checkHerosParty();
	void createFichaDD(uint nCharacter);

	void setNameItem(string name_) { nameItemTienda = name_; }
	void setDescrItem(string descr_) { descrItemTienda = descr_; }
	void setSelectedHeroToParty(int selectedHero) { selectedHeroToParty = selectedHero; }
	void setSelectedItem(int selectedItem_) { selectedItem = selectedItem_; }
	void setIsWeapon(bool isWeapon_) { isWeapon = isWeapon_; }
	void setSelectedInventoryHero(int selectedHero_) { selectedInventoryHero = selectedHero_; }
	void setSelectedInventoryItem(int selectedItem_) { selectedInventoryItem = selectedItem_; }
	void setIsItemToEquipAWeapon(bool isItemToEquipAWeapon_) { isItemToEquipAWeapon = isItemToEquipAWeapon_; }
};