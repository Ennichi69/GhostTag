#pragma once
#include "Common.hpp"

<<<<<<< HEAD
=======
typedef enum {
	point1,
	point2,
	point3,
	special_thunder,
	special_wing,
	nothing,
	in_use
}e_item_type;


>>>>>>> develop
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
<<<<<<< HEAD
	void add_score(uint16 t);
	void set_has_item(bool b);
	Point get_pos();
	uint16 get_score()const;
	e_direction get_direction();
	e_direction get_next_direction();
	bool get_has_item();
	void set_color(Color c);//画像読み込ませたら消す
=======
	void set_special_item(e_item_type t);
	void add_score(uint16 t);
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
>>>>>>> develop
	//sinatori
	uint16 get_invincible_timer();
	void set_invincible_timer();
	void count_invincible_timer();
<<<<<<< HEAD
=======
	void set_texture(uint16 i, String file_name);
	void set_frame_per_move(uint16 fpm);
	uint16 get_frame_per_move()const;
>>>>>>> develop
private:
	Point pos;
	e_direction direction;//今向いている向き
	e_direction next_direction;//次に向く向き
	uint16 score;
<<<<<<< HEAD
	bool has_item;//スペシャルアイテムを所持しているか
	Color col;//イラストに置き換えるまでの仮に色を設定

	//sinatori
	uint16 walking_timer;//テクスチャ変更用変数
	uint16 invincible_timer;//無敵時間変数
};

typedef enum {
	point,
	special,
}e_item_type;
=======
	Color col;//イラストに置き換えるまでの仮に色を設定
	e_item_type special_item;
	uint16 special_item_thunder_timer;
	uint16 special_item_wing_timer;
	//sinatori
	uint16 walking_timer;//テクスチャ変更用変数
	uint16 invincible_timer;//無敵時間変数
	Texture player_picture[8];// left, down, up
	uint16 frame_per_move;//これがmaze_brock_sizeの約数でないと動かない←修正済
};

>>>>>>> develop

class item {
public:
	item();
	item(Point p, e_item_type t);
	void draw();
	void set_pos(Point p);
<<<<<<< HEAD
	Point get_pos();
	uint16 get_radius();
=======
	void set_type(e_item_type t);
	void set_texture(String file_name);
	Point get_pos();
	uint16 get_radius();
	e_item_type get_type();
>>>>>>> develop
private:
	Point pos;
	uint16 radius;
	e_item_type type;
<<<<<<< HEAD
=======
	Texture picture;
>>>>>>> develop
};

//アイテム取得時エフェクト
struct item_effect :IEffect {
	Point pos;
<<<<<<< HEAD
	item_effect(const Point& p);
=======
	Color col;
	item_effect(const Point& p, const Color& c);
>>>>>>> develop
	bool update(double t)override;
};


//捕獲時エフェクト
struct tag_effect :IEffect {
	Point pos;
	tag_effect(const Point& p);
	bool update(double t)override;
};

<<<<<<< HEAD
void draw_maze();
=======
>>>>>>> develop
bool intersect_maze(Rect r);
bool intersect_maze(Point p);
Point maze_brock_position(uint16 h, uint16 w);
Point random_maze_brock_position();//ランダムな迷路内で通行可能な場所の座標
<<<<<<< HEAD
Point random_point_item_position(Array<item>&ai);//ポイントアイテムをランダムに設置
Point random_player_respawn_position(player& player2, player& player3);//プレイヤーの復活地点
=======
Point random_player_respawn_position(player& player2, player& player3);//プレイヤーの復活地点
item random_next_item(Array<item>& ai);//アイテムをランダムに設置
>>>>>>> develop
void draw_timer(uint16 t);//タイマーを書く
void draw_big_point_box(uint16 t);
void draw_small_point_box(uint16 t);

<<<<<<< HEAD
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
=======
bool is_tagged(player ghost, player tagger);//捕獲判定

void left_special_item_timer_draw(uint16 t, uint16 a, Color col);//値、Maxの値、色
void right_special_item_timer_draw(uint16 t, uint16 a, Color col);//値、Maxの値、色

void thunder_effect_draw();

const Grid<uint16>maze_data = {
	{1,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,1,1,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,5,2,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,2,2,3,2,4,4,3,2,0,3,3,4,2,0,2,2,1,0,1,1,0,1,3,3,0,2,4,4,3,0,2,2,4,4,3,4,3,3,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,3,3,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,2,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,1,1,0,3,3,4,4,3,4,3,0,1,1,1,1,0,0,0,1,1,0,1,0,1,1,1,1,0,0,0,0,0,0,0,0,0,1,1,0,1},
	{1,0,1,1,0,0,0,0,0,0,0,0,0,1,1,1,1,0,1,0,2,3,0,0,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,1,1,0,1,1,1,1,1,1,1,0,1,1,1,1,0,1,0,0,0,0,1,0,1,1,1,1,0,1,1,1,1,1,1,1,0,1,1,0,1},
	{1,0,2,2,0,2,2,3,4,4,2,2,0,2,4,3,2,0,1,0,1,1,0,1,0,2,4,3,2,0,3,3,4,4,3,3,2,0,2,2,0,1},
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,0,1,1,0,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,1,1,1,1,1,1,1,1,0,1,1,1,1,0,1,1,1,0,1,1,0,1,1,1,0,1,1,1,1,0,1,1,1,1,1,1,1,1,0,1},
	{1,0,2,2,3,3,4,4,4,2,0,2,4,3,3,0,3,4,2,0,1,1,0,2,3,3,0,2,2,4,4,0,4,4,3,2,2,4,3,3,0,1},
>>>>>>> develop
	{1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1},
	{1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1},
};

const Rect timer_box = Rect(Arg::center(960, 1000), 300, 120);
const Rect big_point_box = Rect(Arg::center(850, 90), 300, 120);
const Rect small_point_box = Rect(Arg::center(1200, 120), 200, 60);
<<<<<<< HEAD
=======
const Rect left_special_item_timer_box = Rect(Arg::center(960 - 450, 1000), 500, 80);
const Rect right_special_item_timer_box = Rect(Arg::center(960 + 450, 1000), 500, 80);
>>>>>>> develop
const Circle left_item_circle = Circle(960 - 800, 1000, 70);
const Circle right_item_circle = Circle(960 + 800, 1000, 70);
const uint16 maze_height = 18;
const uint16 maze_width = 42;
const uint16 maze_brock_size = 40;
<<<<<<< HEAD
const uint16 frame_per_move = 4;//これがmaze_brock_sizeの約数でないと動かないクソ仕様だが多分この数字変えないので問題ない
=======
>>>>>>> develop
const uint16 init_time = 7500;
const uint16 light_range = 120;
const uint16 item_radius = 10;

const uint16 array_point_items_size = 14;//ポイントアイテムの個数

const uint16 point_item_score = 100;
<<<<<<< HEAD
=======
const uint16 additional_item_score = 50;
>>>>>>> develop
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
<<<<<<< HEAD
=======

//スペシャルアイテムの効果時間
const uint16 special_thunder_effect_time = 60;
const uint16 special_wing_ghost_effect_time = 300;
const uint16 special_wing_tagger_effect_time = 180;


const uint16 ghost_speed = 4;
const uint16 tagger_speed = 5;
const uint16 special_wing_ghost_speed = 6;
const uint16 special_wing_tagger_speed = 6;
>>>>>>> develop
