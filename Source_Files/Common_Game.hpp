#pragma once
#include "Common.hpp"

class player;
class item;

class player {
public:
	player();
	player(Point p);
	void draw() const;
	void draw_light()const;
	void update();
	void update_direction(e_direction e_dir);
	Line light()const;
	bool intersects(item& it);
	void set_pos(Point p);
	void set_pos(uint16 h, uint16 w);
	void set_direction(e_direction e_dir);
	void set_next_direction(e_direction e_n_dir);
	void set_score(uint16 t);
	void add_score(uint16 t);
	void set_has_item(bool b);
	Point get_pos();
	uint16 get_score()const;
	e_direction get_direction();
	e_direction get_next_direction();
	bool get_has_item();
	void set_color(Color c);//画像読み込ませたら消す
	//sinatori
	uint16 get_invincible_timer();
	void set_invincible_timer();
	void count_invincible_timer();
	void set_texture(uint16 i, String file_name);
	void set_frame_per_move(uint16 fpm);
private:
	Point pos;
	e_direction direction;//今向いている向き
	e_direction next_direction;//次に向く向き
	uint16 score;
	bool has_item;//スペシャルアイテムを所持しているか
	Color col;//イラストに置き換えるまでの仮に色を設定

	//sinatori
	uint16 walking_timer;//テクスチャ変更用変数
	uint16 invincible_timer;//無敵時間変数
	Texture player_picture[8];// left, down, up
	uint16 frame_per_move;//これがmaze_brock_sizeの約数でないと動かない
};

typedef enum {
	point,
	special,
}e_item_type;

class item {
public:
	item();
	item(Point p, e_item_type t);
	void draw();
	void set_pos(Point p);
	Point get_pos();
	uint16 get_radius();
private:
	Point pos;
	uint16 radius;
	e_item_type type;
};

//アイテム取得時エフェクト
struct item_effect :IEffect {
	Point pos;
	item_effect(const Point& p);
	bool update(double t)override;
};


//捕獲時エフェクト
struct tag_effect :IEffect {
	Point pos;
	tag_effect(const Point& p);
	bool update(double t)override;
};

bool intersect_maze(Rect r);
bool intersect_maze(Point p);
Point maze_brock_position(uint16 h, uint16 w);
Point random_maze_brock_position();//ランダムな迷路内で通行可能な場所の座標
Point random_point_item_position(Array<item>& ai);//ポイントアイテムをランダムに設置
Point random_player_respawn_position(player& player2, player& player3);//プレイヤーの復活地点
void draw_timer(uint16 t);//タイマーを書く
void draw_big_point_box(uint16 t);
void draw_small_point_box(uint16 t);

bool tag(player ghost, player tagger);//捕獲判定

const Grid<bool>maze_data = {
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1},
	{1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,1,1,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,1,1,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

const Rect timer_box = Rect(Arg::center(960, 1000), 300, 120);
const Rect big_point_box = Rect(Arg::center(850, 90), 300, 120);
const Rect small_point_box = Rect(Arg::center(1200, 120), 200, 60);
const Circle left_item_circle = Circle(960 - 800, 1000, 70);
const Circle right_item_circle = Circle(960 + 800, 1000, 70);
const uint16 maze_height = 18;
const uint16 maze_width = 42;
const uint16 maze_brock_size = 40;
const uint16 init_time = 7500;
const uint16 light_range = 120;
const uint16 item_radius = 10;

const uint16 array_point_items_size = 14;//ポイントアイテムの個数

const uint16 point_item_score = 100;
const uint16 tag_score = 800;

const Point delta_point[5] = { Point(0,0),Point(-1,0),Point(0,-1),Point(1,0),Point(0,1) };//移動時の差分 neutral left up right down

//sinatori
const uint16 default_invincible = 90;

//それぞれのプレイヤーの初期座標
const uint16 init_player0_x = 1;
const uint16 init_player0_y = 1;
const uint16 init_player1_x = 15;
const uint16 init_player1_y = 40;
const uint16 init_player2_x = 15;
const uint16 init_player2_y = 1;
const uint16 init_player3_x = 1;
const uint16 init_player3_y = 40;

//それぞれのプレイヤーの色(仮)
const Color init_player0_color = Palette::Red;
const Color init_player1_color = Palette::Pink;
const Color init_player2_color = Palette::Skyblue;
const Color init_player3_color = Palette::Limegreen;