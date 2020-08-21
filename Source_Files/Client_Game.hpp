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
};