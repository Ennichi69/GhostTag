#pragma once
#include "Server_Common.hpp"
#include "Common_Game.hpp"

class server_game :public app::Scene {
public:
	server_game(const InitData& init);
	void update() override;
	void draw()const override;
	void draw_maze()const;
private:
	player player0;
	player player1;
	player player2;
	player player3;
	uint16 timer;
	Array<item>array_point_items;
	item ghost_special_item;
	item tagger_special_item;
	bool exist_ghost_special_item;
	bool exist_tagger_special_item;
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

	Texture maze_walls[7];

	//Texture maze_pictures[18];
	//3 * 6 
	//1~9�̓e���L�[�Ή�(5�͌���)(����1,�E��9)
	//������
	//������
	//������
	//10�͉����A11�͏c��
	//12 wall1
	//13 wall2
	//14 bookshelf
	//15 window
	//16 door
	//maze_walls�����g���Ȃ�-10����12~16�g�p
};