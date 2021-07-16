#include "Text.h"
#include "../../Managers/TheElementalMaze.h"
#include "../../ecs/Entity.h"

//--- INIT ----------------------------------------------------------------------

// Inicializa los valores para el panel del chat
void Text::init()
{
	// relative sizes
	MousePanelMecanics::Init(4, set_FE::DOWN);
	TextBlock::initByFile(file_);
	bt_exit = new ButtonCloseText(Component::game_, nullptr);
	SDL_Rect dest = RECT(
		marco_.x + marco_.w - Component::game_->setHorizontalScale(50),
		marco_.y + Component::game_->setVerticalScale(25),
		Component::game_->setHorizontalScale(25),
		Component::game_->setVerticalScale(25)
	);
	bt_exit->init(dest);
}

//--- UPDATE ---------------------------------------------------------------

// Hace el efecto de scroll si detecta MouseScrollEvent dentro del chat
void Text::update()
{
	TextBlock::update();
	scroll(marco_, tuppleLimits_, entities, ObjectPanel::bottomElement_.h);
	bt_exit->update();
}

//--- DRAW ---------------------------------------------------------------

void Text::draw()
{
	TextBlock::draw();
	bt_exit->draw();
}


