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

	Texture maze_walls[7];

	//Texture maze_pictures[18];
	//3 * 6 
	//1~9はテンキー対応(5は欠番)(左下1,右上9)
	//┌┬┐
	//├┼┤
	//└┴┘
	//10は横線、11は縦線
	//12 wall1
	//13 wall2
	//14 bookshelf
	//15 window
	//16 door
	//maze_wallsだけ使うなら-10して12~16使用

	Texture special_thunder_picture;
	Texture special_wing_picture;
};