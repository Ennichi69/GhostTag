#pragma once
#include "Common.hpp"

typedef enum {
	point1,
	point2,
	point3,
	golden_point1,
	golden_point2,
	golden_point3, 
	special_thunder,
	special_wing,
	nothing,
	in_use
}e_item_type;

typedef enum {
	none,
	pumpkin,
	ghost,
}e_ghost_type;

class player;
class item;

class player {
public:
	player();
	player(Point p);
	void draw(uint16 timer)const;
	void draw_before_start(uint16 t)const;
	void draw_range(Rect r, uint16 timer)const;
	void draw_light()const;
	void update();
	void update_direction(e_direction e_dir);
	Rect light_rect()const;
	Triangle light_triangle()const;
	Rect rect_ghost_visible()const;
	bool intersects(item& it);
	void set_pos(Point p);
	void set_pos(uint16 h, uint16 w);
	void set_direction(e_direction e_dir);
	void set_next_direction(e_direction e_n_dir);
	void set_score(uint16 t);
	void set_special_item(e_item_type t);
	void add_score(uint16 t);
	void remove_score(uint16 t);
	Point get_pos()const;
	uint16 get_score()const;
	e_direction get_direction()const;
	e_direction get_next_direction()const;
	e_item_type get_special_item()const;
	uint16 get_special_item_thunder_timer()const;
	uint16 get_special_item_wing_timer()const;
	void set_color(Color c);//画像読み込ませたら消す
	void set_special_item_thunder_timer(uint16 t);
	void set_special_item_wing_timer(uint16 t);
	void count_special_item_thunder_timer();
	void count_special_item_wing_timer();
	//sinatori
	uint16 get_invincible_timer()const;
	void set_invincible_timer(uint16 t);
	void init_invincible_timer();
	void count_invincible_timer();
	void set_texture(uint16 i, String file_name);
	void set_frame_per_move(uint16 fpm);
	uint16 get_frame_per_move()const;
private:
	Point pos;
	e_direction direction;//今向いている向き
	e_direction next_direction;//次に向く向き
	uint16 score;
	Color col;//イラストに置き換えるまでの仮に色を設定
	e_item_type special_item;
	uint16 special_item_thunder_timer;
	uint16 special_item_wing_timer;
	//sinatori
//	uint16 walking_timer;//テクスチャ変更用変数 timer依存にします なぜかバグるので
	uint16 invincible_timer;//無敵時間変数
	String player_picture[8];// left, down, up
	uint16 frame_per_move;//これがmaze_brock_sizeの約数でないと動かない←修正済
};


class item {
public:
	item();
	item(Point p, e_item_type t, Texture& te);
	void draw(bool b);//true:通常サイズ　false:半分のサイズ
	void set_pos(Point p);
	void set_type(e_item_type t, Texture* te);
	void set_texture(Texture &te);
	Point get_pos();
	uint16 get_radius();
	e_item_type get_type();
private:
	Point pos;
	uint16 radius;
	e_item_type type;
	Texture* picture;
};

//アイテム取得時エフェクト
struct item_effect :IEffect {
	Point pos;
	Color col;
	item_effect(const Point& p, const Color& c);
	bool update(double t)override;
};


//捕獲時エフェクト
struct tag_effect :IEffect {
	Point pos;
	Texture* texture;
	tag_effect(const Point& p, Texture& t);
	bool update(double t)override;
};

bool intersect_maze(Rect r);
bool intersect_maze(Point p);
Point maze_brock_position(uint16 h, uint16 w);
Point random_maze_brock_position();//ランダムな迷路内で通行可能な場所の座標
Point random_player_respawn_position(player& player2, player& player3);//プレイヤーの復活地点
item random_next_item(Array<item>& ai, Texture* tex, uint16 &counter);//アイテムをランダムに設置
void draw_timer(uint16 t);//タイマーを書く
void draw_big_point_box(uint16 t);
void draw_small_point_box(uint16 t);

bool is_tagged(player ghost, player tagger);//捕獲判定

void left_special_item_timer_draw(uint16 t, uint16 a, Color col);//値、Maxの値、色
void right_special_item_timer_draw(uint16 t, uint16 a, Color col);//値、Maxの値、色

void thunder_effect_draw();

void countdown_clock_draw(uint16 t);

const Grid<uint16>maze_data={ 
	{1,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,0,2,3,2,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,0,0,0,0,0,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,1,0,2,4,4,0,2,3,2,2,4,3,2,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,2,2,4,4,3,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,2,4,3,0,2,4,4,2,2,3,2,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,2,4,3,2,0,1,1,1,1,1,1,1,0,1,1,1,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,1,1,0,3,4,2,2,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,1,1,1,0,1,1,1,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,0,4,4,2,3,2,4,2,0,2,4,2,0,1},
	{1,0,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,3,2,4,4,0,1,1,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,4,3,2,0,2,3,2,2,3,2,4,0,1,1,1,1,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,1,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,4,4,2,2,0,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,0,0,0,0,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,1,0,1,1,1,0,1,1,1,0,1,1,1,0,1},
	{1,0,3,2,4,2,2,4,4,0,2,4,3,0,2,4,2,3,0,4,4,2,3,2,2,4,2,3,0,2,4,2,0,3,2,4,0,4,2,3,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1}
};

const Rect timer_box = Rect(Point(822, 923), Point(1097, 1063) - Point(822, 923));
const Rect big_point_box = Rect(Point(804, 26), Point(1116, 162) - Point(804, 26));
const Rect small_point_box = Rect(Point(1178, 49), Point(1410, 162) - Point(1178, 49));
const Rect left_special_item_timer_box = Rect(Arg::center(960 - 450, 1000), 500, 80);
const Rect right_special_item_timer_box = Rect(Arg::center(960 + 450, 1000), 500, 80);
const Circle left_item_circle = Circle(161, 972, 70);
const Circle right_item_circle = Circle(1764, 971, 70);
const uint16 maze_height = 18;
const uint16 maze_width = 42;
const uint16 maze_brock_size = 40;
const uint16 init_time = 7560;
const uint16 start_time = 7200;
const uint16 light_range = 120;
const uint16 item_radius = 10;

const uint16 array_point_items_size = 15;//ポイントアイテムの個数

const uint16 point_item_score = 100;
const uint16 golden_point_item_score = 200;
const uint16 additional_item_score = 50;
const uint16 additional_golden_item_score = 100;
const uint16 tag_score = 500;//捕まえた時の加点
const uint16 tagged_score = 200;//捕まったときの減点

const Point delta_point[5] = { Point(0,0),Point(-1,0),Point(0,-1),Point(1,0),Point(0,1) };//移動時の差分 neutral left up right down

//sinatori
const uint16 default_invincible = 150;

//それぞれのプレイヤーの初期座標
const uint16 init_player0_x = 16;
const uint16 init_player0_y = 1;
const uint16 init_player1_x = 16;
const uint16 init_player1_y = 40;
const uint16 init_player2_x = 1;
const uint16 init_player2_y = 1;
const uint16 init_player3_x = 1;
const uint16 init_player3_y = 40;

//それぞれのプレイヤーの色(仮)
const Color init_player0_color = Palette::Orange;
const Color init_player1_color = Palette::Skyblue;
const Color init_player2_color = Palette::Red;
const Color init_player3_color = Palette::Limegreen;

//スペシャルアイテムの効果時間
const uint16 special_thunder_ghost_effect_time = 120; 
const uint16 special_thunder_tagger_effect_time = 60;
const uint16 special_wing_ghost_effect_time = 270;
const uint16 special_wing_tagger_effect_time = 120;


const uint16 ghost_speed = 3;
const uint16 tagger_speed = 4;
const uint16 special_wing_ghost_speed = 5;
const uint16 special_wing_tagger_speed = 6;