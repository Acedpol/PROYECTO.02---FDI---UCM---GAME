#pragma once
#include <string>
#include "ElementsResources.h"
#include "../../Managers/game/TextBlockManager.h"
#include "../../Templates/interfaz/LineTypes.h"

class Tupple;
using namespace std;

// valores por defecto
const int NUM_LETTERS_IN_LINE = 30;

class TextBlockResources : public ElementsResources, public LineTypes
{
public:
	TextBlockResources() : ElementsResources(), bottomElement_(), limits_() {};
	virtual ~TextBlockResources() {};
	void Init(SDL_Rect bottom_elem, tb_Mngr* mngr, set_FE way);

	void set_line_letters(int n) { lineLetters_ = n; };

	// methods to access and interact by inserting lines
	void add(std::string line, LineColor type, Resources::FontId font = src::ConsoleBO);
	void clean_n_addLine(std::string line, LineColor type, bool makeTitle = false, Resources::FontId font = src::ConsoleBO);
	
private:
	// main way to insert a line
	void addLine(std::string line, LineColor type, Resources::FontId font = src::ConsoleBO);

	// checkers of the differents sizes
	bool checkLineSize(std::string line, LineColor type, Resources::FontId font = src::ConsoleBO);

	// cuts the line avoiding to cut the last word
	string cutLine(string line);

	// resizes the line to lineLetters and deletes the posible front white space
	string formatLine(string line);

	// sets the number of letter in a line and the number of lines in a block
	// void set_lineLetters(int width);
	// void set_numLines(int height);		// with the account of the bottomLine
	// void set_backGround();				// sets the background size to catch all the lines in a block

private:
	tb_Mngr* mngr_ = nullptr;
	bool isTitle_ = false;

	// valor por defecto
	int lineLetters_ = NUM_LETTERS_IN_LINE;

	SDL_Rect bottomElement_;
	Tupple limits_;

};
