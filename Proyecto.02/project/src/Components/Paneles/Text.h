#pragma once
#include "../../ecs/Component.h"
#include "../../Utilities/interfaz/MousePanelMecanics.h"
#include "../../Structures/TextBlock.h"

const string path = "project/resources/languages/";
enum class location {
	SPAIN,
	ENGLAND
};

class Text : public Component, public TextBlock, public MousePanelMecanics
{
private:
	string file_;

public:
	Text(SDLGame* game, string file, location lo) : Component(ecs::Text), TextBlock(game) {
		if (lo == location::SPAIN) { file_ = path + "es/" + file; }
		else if (lo == location::ENGLAND) { file_ = path + "en/" + file; }		
	};
	void init();

	void update() override;
	void draw() override;

	void re_writeText(string file);

	virtual ~Text() {};

};
