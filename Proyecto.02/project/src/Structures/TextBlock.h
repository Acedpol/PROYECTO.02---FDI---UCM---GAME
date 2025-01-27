#pragma once
#include "../ecs/Manager.h"
#include "../Utilities/interfaz/TextBlockResources.h"
#include "../Managers/game/TextBlockManager.h"
#include "../Templates/interfaz/ObjectPanel.h"

class TextBlock : public TextBlockManager, public ObjectPanel, public TextBlockResources
{
private:
	Entity* fondo_ = nullptr;
	uint set_NumLetterInARow();

public:
	TextBlock(SDLGame* game) : TextBlockManager(game) {};
	virtual ~TextBlock() { 
		delete fondo_; 
		fondo_ = nullptr;
		entities.clear();
	};

	void Init(SDL_Panel pan);
	void update() override;
	void draw() override;

protected:
	// -----
	void setFondo(src::TextureId image);
	void initByFile(string const& file, location lo, src::FontId font = src::ConsoleBO);
	void initByFile(string const& file, src::FontId font = src::ConsoleBO);

};
