#include "TextBlockResources.h"
#include "../../GameObjects/SDL_Objects.h"
#include "../../Components/Transform.h"

//--- PUBLIC -------------------------------------------------------------------------

void TextBlockResources::Init(SDL_Rect bottom_elem, tb_Mngr* mngr, set_FE way)
{
	bottomElement_ = bottom_elem; 
	mngr_ = mngr;
	LineTypes::Init();
	ElementsResources::Init(way);
}

// checks if they are in their standar position and then insert a new line
void TextBlockResources::add(std::string line, LineColor type, Resources::FontId font)
{
	reset(mngr_->entities, bottomElement_, limits_);
	addLine(line, type, font);
}

// cleans all the chat and insert a new line, it can be a title
void TextBlockResources::clean_n_addLine(std::string line, LineColor type, bool makeTitle, Resources::FontId font)
{
	cleanALL(mngr_->entities);
	isTitle_ = makeTitle;
	addLine(line, type, font);
}

//--- PRIVATE ------------------------------------------------------------------------

// inserts another line, checking the line size and the format
void TextBlockResources::addLine(std::string line, LineColor type, Resources::FontId font)
{
	if (!checkLineSize(line, type, font)) {
		for (auto it = mngr_->entities.begin(); it != mngr_->entities.end(); it++) {
			moveUp(it->get(), bottomElement_.h);
		}
		if (line.size() > 0) {
			line = formatLine(line);
			mngr_->addLine(bottomElement_, line, lineTypesMap_[type], isTitle_, font);
			if (isTitle_) isTitle_ = false;
		} 
		else {
			int a = 0;
		}
	}
}

// checks the size of the line, if it exceeds the limit the line will be cut
bool TextBlockResources::checkLineSize(std::string line, LineColor type, Resources::FontId font)
{
	bool cut = false;
	if (line.size() > lineLetters_) {
		string lin = cutLine(line);
		addLine(lin, type, font);
		string lin2 = line.substr(lin.size());
		addLine(lin2, type, font);
		cut = true;
	}
	return cut;
}

//--- FORMATS -------------------------------------------------------------------------

// cuts the line to the limit, avoiding to cut the last word
string TextBlockResources::cutLine(string line)
{
	string cut;
	if (line.size() > lineLetters_) {
		if (line.at(lineLetters_ - 2.0) != ' ' && line.at(lineLetters_ - 1.0) != ' ' || line.at(lineLetters_ - 1.0) != ' ' && line.at(lineLetters_) != ' ') {
			string aux = line.substr(0, lineLetters_);
			size_t n = aux.rfind(' ', lineLetters_);
			cut = aux.substr(0, n + 1);
		}
	}
	if (cut == "") {
		cut = line.substr(0, lineLetters_);
	}
	return cut;
}

// formats line to the size given
string TextBlockResources::formatLine(string line)
{
	if (line.front() == ' ') line.erase(line.begin());
	if (line.size() < lineLetters_) line.resize(lineLetters_, ' ');
	return line;
}

//--- FILES -----------------------------------------------------------------------------

vector<string> TextBlockResources::readFile(string const& file)
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

void TextBlockResources::addText(vector<string> const& text, src::FontId font)
{
	bool title_done = false;
	for (int i = 0; i < text.size(); i++)
	{
		if (!title_done) {
			clean_n_addLine(text[i], LineColor::White, true, src::ConsoleBO);
			title_done = true;
		}
		else add(text[i], LineColor::White, src::ConsoleBO);
	}
}

void TextBlockResources::writeText(string file, location lo, src::FontId font)
{
	if (lo == location::SPAIN) { 
		file = path + "es/" + file; }
	else if (lo == location::ENGLAND) { 
		file = path + "en/" + file; }

	//removeEntities();
	cleanALL(mngr_->entities);
	vector<string> text = readFile(file);
	addText(text, font);

	numLines_ = mngr_->entities.size();
}
