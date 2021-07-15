#pragma once
#include "../../ecs/Component.h"
#include "../../GameObjects/Button.h"
#include "../../Utilities/interfaz/MousePanelMecanics.h"
#include "../../Structures/TextBlock.h"

class Text : public Component, public TextBlock, public MousePanelMecanics
{
private:
	ButtonCloseText* bt_exit = nullptr;
	location lo_;
	string file_;

public:
	Text(SDLGame* game, string file, location lo) : Component(ecs::Text), TextBlock(game) {
		file_ = file;
		lo_ = lo;
	};
	void init();

	void update() override;
	void draw() override;

	virtual ~Text() { delete bt_exit; bt_exit = nullptr; };

};
