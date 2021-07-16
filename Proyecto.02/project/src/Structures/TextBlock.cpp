#include "TextBlock.h"
#include <fstream>
#include "../Components/Transform.h"
#include "../Components/Rectangle.h"
#include "../Components/Image.h"

void TextBlock::Init(SDL_Panel pan)
{
	ObjectPanel::Init(pan);
	TextBlockResources::Init(bottomElement(), this, set_FE::DOWN);

	// fondo oscuro
	fondo_ = new Entity(game_, this);
	SDL_Rect dest = RECT(pan.x, pan.y, pan.w, pan.h);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Rectangle_cmpt>(hex2sdlcolor("#000000FF"));
}

void TextBlock::update()
{
	if (ElementsResources::checkBlockSize_reduce(entities, numLines_)) removeEntity(entities.begin()->get());
}

void TextBlock::draw()
{
	fondo_->draw();
	ElementsResources::draw(entities, tuppleLimits());
}

void TextBlock::setFondo(src::TextureId image)
{
	fondo_->removeComponent(ecs::Rectangle_cmpt);
	fondo_->addComponent<Image>(game_->getTextureMngr()->getTexture(image));
}

void TextBlock::initByFile(string const& file, location lo, src::FontId font)
{
	SDL_Panel pan = game_->relativePanel(70, 360, 950, 330, 1, 15, 30, 10);
	ObjectPanel::Init(pan);
	TextBlockResources::Init(bottomElement(), this, set_FE::DOWN);
	TextBlockResources::set_line_letters(set_NumLetterInARow());

	// fondo oscuro
	fondo_ = new Entity(game_, this);
	SDL_Rect dest = RECT(pan.x, pan.y, pan.w, pan.h);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Image>(game_->getTextureMngr()->getTexture(src::Cartelito));

	TextBlockResources::writeText(file, lo, font);
	TextBlockResources::resetToBottom(entities, bottomElement(), tuppleLimits());
	TextBlockResources::resetToTop(entities, topElement(), tuppleLimits());
}

void TextBlock::initByFile(string const& key, src::FontId font)
{
	SDL_Panel pan = game_->relativePanel(70, 360, 950, 330, 1, 15, 30, 10);
	ObjectPanel::Init(pan);
	TextBlockResources::Init(bottomElement(), this, set_FE::DOWN);
	TextBlockResources::set_line_letters(set_NumLetterInARow());

	// fondo oscuro
	fondo_ = new Entity(game_, this);
	SDL_Rect dest = RECT(pan.x, pan.y, pan.w, pan.h);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Image>(game_->getTextureMngr()->getTexture(src::Cartelito));
	
	TextBlockResources::writeText(game_->getLocale()->format(key), font);
	TextBlockResources::resetToBottom(entities, bottomElement(), tuppleLimits());
	TextBlockResources::resetToTop(entities, topElement(), tuppleLimits());
}

uint TextBlock::set_NumLetterInARow()
{	
	return uint(marco_.w * 35.0 / game_->setHorizontalScale(630));
}
