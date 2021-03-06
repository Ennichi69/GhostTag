#pragma once
#include "Client_Common.hpp"
#include "Common_Game.hpp"

class client_game :public app::Scene {
public:
	client_game(const InitData& init);
	void update() override;
	void draw()const override;
	void draw_maze()const;
private:
	uint16 timer;
	player player0;
	player player1;
	player player2;
	player player3;
	Array<item>array_items;
	Effect effect;


	Texture junction_u;
	Texture junction_l;
	Texture junction_d;
	Texture junction_r;

	Texture corner_ld;
	Texture corner_rd;
	Texture corner_ru;
	Texture corner_lu;
	Texture street_ud;
	Texture street_lr;

	Texture cross;

	Texture maze_walls[7];

	
	//Texture maze_pictures[18];
	//3 * 6 
	//1~9ΝeL[Ξ(5ΝΤ)(ΆΊ1,Eγ9)
	//‘¦’
	//₯©§
	//€¨£
	//10Ν‘όA11Νcό
	//12 wall1
	//13 wall2
	//14 bookshelf
	//15 window
	//16 door
	//maze_wallsΎ―g€Θη-10΅Δ12~16gp

	Texture item_pictures[8];

	Texture background;

	Texture special_thunder_picture;
	Texture special_wing_picture;

	Texture pumpkin_picture;
	Texture ghost_picture;

	Texture tagger_characters;
};