#include "Text.h"
#include "../../Managers/TheElementalMaze.h"
#include "../../ecs/Entity.h"

//--- INIT ----------------------------------------------------------------------

// Inicializa los valores para el panel del chat
void Text::init()
{
	// relative sizes
	MousePanelMecanics::Init(1, set_FE::UP);
	TextBlock::initByFile(file_);
}

//--- UPDATE ---------------------------------------------------------------

// Hace el efecto de scroll si detecta MouseScrollEvent dentro del chat
void Text::update()
{
	TextBlock::update();
	scroll(marco_, tuppleLimits_, entities, ObjectPanel::bottomElement_.h);
}

//--- DRAW ---------------------------------------------------------------

void Text::draw()
{
	TextBlock::draw();
}

void Text::re_writeText(string file)
{
	removeEntities();
	vector<string> text = TextBlock::readFile(file);
	TextBlock::addText(text);
}
