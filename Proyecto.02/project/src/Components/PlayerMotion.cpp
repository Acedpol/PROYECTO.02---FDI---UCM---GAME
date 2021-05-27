#include "PlayerMotion.h"
#include "../Utilities/InputHandler.h"
#include "../Managers/game/CombatManager.h"
#include "../Managers/game/CharacterManager.h"
#include "../Managers/TheElementalMaze.h"

PlayerMotion::PlayerMotion(SDL_KeyCode avanzar, SDL_KeyCode izq, SDL_KeyCode der, Laberinto* lab_) :Component(ecs::PlayerMotion), //
pos(nullptr), avance(avanzar), giraIzq(izq), giraDer(der), lab(lab_) //
{

}

PlayerMotion::PlayerMotion() :Component(ecs::PlayerMotion), //
pos(nullptr), avance(SDLK_UP), giraIzq(SDLK_LEFT), giraDer(SDLK_DOWN), lab(nullptr) //
{

}

void PlayerMotion::init()
{
	pos = GETCMP1_(MazePos);
	debugear();

}

void PlayerMotion::update()
{
	if (TheElementalMaze::instance()->gameState() != gameST::EXPLORING) return;
	InputHandler* ih = InputHandler::instance();
	x = int(pos->getPos().getX());
	y = int(pos->getPos().getY());
	if (ih->isKeyDown(avance)) { avanzar(); }
	else if (ih->isKeyDown(giraIzq)) { rotarIzquierda(); }
	else if (ih->isKeyDown(giraDer)) { rotarDerecha(); }
	else if (ih->isKeyDown(SDLK_e) && lab->getCasillaInfo(x, y)->isExit()) { TheElementalMaze::instance()->changeState(gameST::END_EXPLORING); }
	else if (ih->isKeyDown(SDLK_f) && lab->getCasillaInfo(x, y)->isExit()) { TheElementalMaze::instance()->changeState(gameST::LOBBY); }
}

void PlayerMotion::rotarDerecha()
{
	if (TheElementalMaze::instance()->gameState() != gameST::EXPLORING)
		return;
	
	Casilla* cas = lab->getCasillaInfo(x, y);
	casillaActual = cas->checkCell();

	sent = pos->getLook();
	if (sent == Oeste)
		sent = Norte;
	else
		sent++;

	pos->setLook(sent);
	cas->setLook(sent * 90);
	switch (pos->getLook())
	{
	case Norte:
		cout << "Estas mirando hacia el norte" << endl;
		break;
	case Este:
		cout << "Estas mirando hacia el este" << endl;
		break;
	case Sur:
		cout << "Estas mirando hacia el sur" << endl;
		break;
	case Oeste:
		cout << "Estas mirando hacia el oeste" << endl;
		break;
	}
}

void PlayerMotion::rotarIzquierda()
{
	if (TheElementalMaze::instance()->gameState() != gameST::EXPLORING)
		return;
	/*x = int(pos->getPos().getX());
	y = int(pos->getPos().getY());*/
	Casilla* cas = lab->getCasillaInfo(x, y);
	casillaActual = cas->checkCell();

	auto sent = pos->getLook();
	if (sent == Norte)
		sent = Oeste;
	else
		sent--;
	pos->setLook(sent);
	cas->setLook(sent * 90);
	switch (pos->getLook())
	{
	case Norte:
		cout << "Estas mirando hacia el norte" << endl;
		break;
	case Este:
		cout << "Estas mirando hacia el este" << endl;
		break;
	case Sur:
		cout << "Estas mirando hacia el sur" << endl;
		break;
	case Oeste:
		cout << "Estas mirando hacia el oeste" << endl;
		break;
	}
}

void PlayerMotion::avanzar()
{
	if (TheElementalMaze::instance()->gameState() != gameST::EXPLORING)
		return;
	/*x = int(pos->getPos().getX());
	y = int(pos->getPos().getY());*/
	Casilla* cas = lab->getCasillaInfo(x, y);
	casillaActual = cas->checkCell();

	if (casillaActual[pos->getLook()])
	{
		cas->setPosActual(false);
		switch (pos->getLook())
		{
		case Norte:
			//if (y - 1 >= 0)
			//{

			pos->setPos(Vector2D(x, y - 1));
			//}
			break;
		case Este:
			//if (x + 1 < lab->mazeWidth())
			//{
			pos->setPos(Vector2D(x + 1, y));
			//}
			break;
		case Sur:
			//if (y + 1 < lab->mazeHeigh())
			//{
			pos->setPos(Vector2D(x, y + 1));
			//}
			break;
		case Oeste:
			//if (x - 1 >= 0)
			//{
			pos->setPos(Vector2D(x - 1, y));
			//}
			break;
		}
		/*cout << "Estas en la casilla " << pos->getPos() << ".	\n";

		vector<Enemy*> enemigo = lab->getCasillaInfo(pos->getPos().getX(), pos->getPos().getY())->getEnemy();

		for (int i = 0; i < enemigo.size(); i++)
		{
			cout <<"Encuentras con el enemigo "<< enemigo[i]->name() << endl;
		}*/
		debugear();

	}
}

void PlayerMotion::debugear()
{
	cout << "Estas en la casilla " << pos->getPos() << ".	\n";


	Casilla* cas = lab->getCasillaInfo(int(pos->getPos().getX()), int(pos->getPos().getY()));
	cas->setVisibilidad(Visibilidad::visitado);
	cas->setPosActual(true);
	cas->setLook(pos->getLook() * 90);

	vector<bool> vecinos = cas->checkCell();
	for (int k = 0; k < vecinos.size(); k++)
	{
		if (vecinos[k])
		{
			switch (k)
			{
			case Norte:
				if (lab->getCasillaInfo(int(pos->getPos().getX()), int(pos->getPos().getY()) - 1)->getVisibilidad() == Visibilidad::noVisitado)
					lab->getCasillaInfo(int(pos->getPos().getX()), int(pos->getPos().getY()) - 1)->setVisibilidad(Visibilidad::noEntrado);
				break;
			case Este:
				if (lab->getCasillaInfo(int(pos->getPos().getX()) + 1, int(pos->getPos().getY()))->getVisibilidad() == Visibilidad::noVisitado)
					lab->getCasillaInfo(int(pos->getPos().getX()) + 1, int(pos->getPos().getY()))->setVisibilidad(Visibilidad::noEntrado);
				break;
			case Sur:
				if (lab->getCasillaInfo(int(pos->getPos().getX()), int(pos->getPos().getY()) + 1)->getVisibilidad() == Visibilidad::noVisitado)
					lab->getCasillaInfo(int(pos->getPos().getX()), int(pos->getPos().getY()) + 1)->setVisibilidad(Visibilidad::noEntrado);
				break;
			case Oeste:
				if (lab->getCasillaInfo(int(pos->getPos().getX()) - 1, int(pos->getPos().getY()))->getVisibilidad() == Visibilidad::noVisitado)
					lab->getCasillaInfo(int(pos->getPos().getX()) - 1, int(pos->getPos().getY()))->setVisibilidad(Visibilidad::noEntrado);
				break;
			}
		}
	}

	vector<enemyTemplate>* enemigo = cas->getEnemy();

	if (enemigo->size()) {
		CharacterManager* chaManager = TheElementalMaze::instance()->getCharacterManager();
		CombatManager* comManager = TheElementalMaze::instance()->getCombatManager();
		for (int i = 0; i < enemigo->size(); i++)
		{
			cout << "Encuentras con el enemigo " << toString((*enemigo)[i]) << endl;

			comManager->addCharacter(chaManager->addEnemyFromTemplate((*enemigo)[i]));
		}
		TheElementalMaze::instance()->changeState(gameST::START_COMBAT);
		
		return;
	}

	vector<Chest>* cofres = cas->getChest();

	if (cofres->size()) {
		for (int i = 0; i < cofres->size(); i++)
		{
			cout << "Encuentras con un cofre con " << to_string((*cofres)[i].getType()) << " de tipo " << to_string((*cofres)[i].getIdValue()) << endl;
		}
	}

}
