#pragma once
#include "Client_Common.hpp"
#include "Common_Game.hpp"

class client_game :public app::Scene {
public:
	client_game(const InitData& init);
	void update() override;
	void draw()const override;
private:
	uint16 timer;
	player player0;
	player player1;
	player player2;
	player player3;
	Array<item>array_point_items;
	item ghost_special_item;
	item tagger_special_item;
	bool exist_ghost_special_item;
	bool exist_tagger_special_item;
	Effect effect;
};