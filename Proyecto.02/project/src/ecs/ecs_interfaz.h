#pragma once

#include <ctime>

namespace interfaz {

	using idPanelType = std::size_t;

	enum idPanel : idPanelType {
		Movement, 
		Heroes, 
		Inventory, 
		Info, 
		Minimap, 
		Targets,
		Habilities,
		Fight, 
		Turns, 
		HeroesStats, 
		DDPan,
		BigMap, 
		Settings, 
		Chat,
		MenuPrincipal,
		Lobby,
		Options,
		HowToPlay,
		Enemies,
		Shop,
		StashPanel,
		infoTiendaPanel,
		ButtonHeroToPartyPanel,
		SellButtonPanel,
		InventoryLobby,
		//
		// don't touch the rest of this enum, it is to identify the max
		// number of components
		_LastPanId_
	};

	constexpr std::size_t maxPanels = _LastPanId_;
}

