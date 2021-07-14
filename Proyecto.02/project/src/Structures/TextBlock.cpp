#include "TextBlock.h"
#include <fstream>
#include "../Components/Transform.h"
#include "../Components/Rectangle.h"
#include "../Components/Image.h"

void TextBlock::Init(SDL_Panel pan)
{
	ObjectPanel::Init(pan);
	TextBlockResources::Init(bottomElement(), this);

	// fondo oscuro
	fondo_ = new Entity(game_, this);
	SDL_Rect dest = RECT(pan.x, pan.y, pan.w, pan.h);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Rectangle_cmpt>(hex2sdlcolor("#000000FF"));
}

void TextBlock::update()
{
	ElementsResources::checkBlockSize(entities, numLines_);
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

void TextBlock::initByFile(string const& file)
{
	vector<string> text = readFile(file);

	SDL_Panel pan = game_->relativePanel(70, 360, 630, 330, 1, 12, 10, 10);
	ObjectPanel::Init(pan);
	TextBlockResources::Init(bottomElement(), this);

	// fondo oscuro
	fondo_ = new Entity(game_, this);
	SDL_Rect dest = RECT(pan.x, pan.y, pan.w, pan.h);
	fondo_->addComponent<Transform>(dest);
	fondo_->addComponent<Image>(game_->getTextureMngr()->getTexture(src::Cartelito));

	addText(text);	
}

vector<string> TextBlock::readFile(string const& file)
{
	vector<string> text;

	//ifstream fe("C:/ruta/archivo.txt");
	ifstream input;
	input.open(file);

	string cadena = "";
	if (!input.is_open()) throw("No se encuentra el fichero");
	else {
		while (!input.eof()) {
			string line = "";
			getline(input, line);

			text.push_back(line);

			cout << line << endl;
		}
	}
	input.close();
	//system("pause");

	return text;
}

void TextBlock::addText(vector<string> const& text)
{
	bool title_done = false;
	for (size_t i = 0; i < text.size(); i++)
	{
		if (!title_done) {
			clean_n_addLine(text[i], LineColor::Black, true, src::Beaulieux);
			title_done = true;
		}
		else add(text[i], LineColor::Black, src::Beaulieux);
	}
}
