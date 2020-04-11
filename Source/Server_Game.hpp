#pragma once
#include "Server_Common.hpp"
#include "Game_Common.hpp"

class Server_Game : public App::Scene {
public:
	Server_Game(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Player Ghost0 = Player(Ghost0_InitPos(), Palette::Red);
	Player Ghost1 = Player(Ghost1_InitPos(), Palette::Orange);
	Player Tagger0 = Player(Tagger0_InitPos(), Palette::Blue);
	Player Tagger1 = Player(Tagger1_InitPos(), Palette::Aqua);
	uint16 Timer = Init_Time;
	uint16 Ghost_Score = 0;
	uint16 Tagger_Score = 0;
};