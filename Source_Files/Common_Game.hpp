#pragma once
#include "Common.hpp"

class player {
public:
	player();
	player(Point p);
	void draw() const;
	void draw_light()const;
	void update();
	void update_direction(e_direction e_dir);
	Line light()const;
	void set_pos(Point p);
	void set_pos(uint16 h, uint16 w);
	void set_direction(e_direction e_dir);
	void set_next_direction(e_direction e_n_dir);
	Point get_pos();
	e_direction get_direction();
	e_direction get_next_direction();
	void set_color(Color c);//画像読み込ませたら消す
private:
	Point pos;
	e_direction direction;//今向いている向き
	e_direction next_direction;//次に向く向き
	Color col;//イラストに置き換えるまでの仮に色を設定
};


class item {
public:
	item();
	item(Point p, uint16 t);
	void draw();
	Point get_pos();
private:
	Point pos;
	uint16 type;
};


void draw_maze();
bool intersect_maze(Rect r);
bool intersect_maze(Point p);
Point maze_brock_position(uint16 h, uint16 w);

const Grid<bool>maze_data = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,0,0,1,1},
	{1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
	{1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,0,1,1,1,1,1,1,1,0,1,1,1,1,1,1,1},
	{1,1,0,1,0,1,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,1,0,1,0,1,1,1,1,1,1,0,0,0,1,1,1,1,1,1},
	{1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,0,0,0,0,1,0,1,0,1,1,1,1,1,0,0,1,0,0,1,1,1,1,1},
	{1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,0,0,0,1,0,0,0,0,0,1,1,1,0,0,1,1,1,0,0,1,1,1,1},
	{1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,1,0,0,1,1,1,1,1,0,0,1,1,1},
	{1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,0,1,0,1,0,1,0,1,0,1,1,0,0,1,1,1,0,1,1,1,0,0,1,1},
	{1,1,0,1,0,1,0,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,0,1,1,1,1,0,1,1},
	{1,1,0,0,0,0,0,1,0,0,0,0,0,0,0,0,0,1,1,1,0,1,1,0,1,1,0,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

const Rect timer_box = Rect(Arg::center(960, 1020), 300, 100);
const Circle left_item_circle = Circle(960 - 800, 1020, 50);
const Circle right_item_circle = Circle(960 + 800, 1020, 50);
const uint16 maze_height = 18;
const uint16 maze_width = 42;
const uint16 maze_brock_size = 40;
const uint16 frame_per_move = 4;//これがmaze_brock_sizeの約数でないと動かないクソ仕様だが多分この数字変えないので問題ない
const uint16 init_time = 7500;
const uint16 light_range = 120;

const Point delta_point[5] = { Point(0,0),Point(-1,0),Point(0,-1),Point(1,0),Point(0,1) };//移動時の差分 neutral left up right down

//それぞれのプレイヤーの初期座標
const uint16 init_player0_x = 1;
const uint16 init_player0_y = 1;
const uint16 init_player1_x = 15;
const uint16 init_player1_y = 39;
const uint16 init_player2_x = 15;
const uint16 init_player2_y = 2;
const uint16 init_player3_x = 1;
const uint16 init_player3_y = 40;

//それぞれのプレイヤーの色(仮)
const Color init_player0_color = Palette::Red;
const Color init_player1_color = Palette::Pink;
const Color init_player2_color = Palette::Skyblue;
const Color init_player3_color = Palette::Limegreen;
