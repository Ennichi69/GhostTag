#pragma once
#include "Server_Common.hpp"
#include "Common_Game.hpp"

class server_game :public app::Scene {
public:
	server_game(const InitData& init);
	void update() override;
	void draw()const override;
private:
	player player0;
	player player1;
	player player2;
	player player3;
	uint16 timer;
};