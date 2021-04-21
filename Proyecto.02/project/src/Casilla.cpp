#include "Casilla.h"
Casilla::Casilla(SDLGame* game):esSalida(false)
{
	game_ = game;
	direcciones.resize(4);
	direcciones[Norte] = 0;
	direcciones[Este] = 0;
	direcciones[Sur] = 0;
	direcciones[Oeste] = 0;
	visib = noVisitado;
}

Casilla::Casilla(SDLGame* game, bool _N, bool _E, bool _S, bool _O ) :esSalida(false)
{
	game_= game;
	direcciones.resize(4);
	direcciones[Norte] = _N;
	direcciones[Este] = _E;
	direcciones[Sur] = _S;
	direcciones[Oeste] = _O;
	visib = noVisitado;
	
}

Casilla::~Casilla()
{

}

vector<bool> Casilla::checkCell()
{
	return direcciones;
}
void Casilla::casillaRender(int x, int y)
{
	SDL_Rect dest = { x, y, 28, 20 };
	Texture* texturaSuelo;
	Texture* texturaPosActual;
	Texture* texturaPared = nullptr;
	auto manager = game_->getTextureMngr();

	if (visib == noVisitado)
	{
		texturaSuelo = manager->getTexture(Resources::no_visitado);
		texturaSuelo->render(dest);
	}
	else if (visib == noEntrado)
	{
		texturaSuelo = manager->getTexture(Resources::no_entrado);
		texturaSuelo->render(dest);
	}
	else if (visib == visitado)
	{
		texturaSuelo = manager->getTexture(Resources::visitado);
		texturaSuelo->render(dest);

		for (int i = 0; i < direcciones.size(); ++i)
		{
			if (!direcciones[i])
			{
				switch (i)
				{
				case Norte:
					texturaPared = manager->getTexture(Resources::pared_N);
					break;
				case Este:
					texturaPared = manager->getTexture(Resources::pared_E);
					break;
				case Sur:
					texturaPared = manager->getTexture(Resources::pared_S);
					break;
				case Oeste:
					texturaPared = manager->getTexture(Resources::pared_O);
					break;
				}
				if (texturaPared != nullptr)
					texturaPared->render(dest);
					
			}

		}

	}

	if (esPosActual)
	{
		texturaPosActual = manager->getTexture(Resources::posMiniMap);
		texturaPosActual->render(dest,angulo);

	}
	

	

}