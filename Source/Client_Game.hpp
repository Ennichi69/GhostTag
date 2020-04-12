#pragma once
#include "Client_Common.hpp"
#include "Game_Common.hpp"

class Client_Game : public App::Scene {
public:
	Client_Game(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Array<Item>Itemlist = Array<Item>(Item_Size);
	Player Tagger0 = Player(Tagger0_InitPos(), Palette::Blue);
	Player Tagger1 = Player(Tagger1_InitPos(), Palette::Aqua);
	uint16 Timer = Init_Time;
	uint16 Ghost_Score = 0;
	uint16 Tagger_Score = 0;
};