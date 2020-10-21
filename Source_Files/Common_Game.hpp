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
	void set_color(Color c);//�摜�ǂݍ��܂��������
	void set_special_item_thunder_timer(uint16 t);
	void set_special_item_wing_timer(uint16 t);
	void count_special_item_thunder_timer();
	void count_special_item_wing_timer();
	//sinatori
	uint16 get_invincible_timer();
	void set_invincible_timer();
	void count_invincible_timer();
	void set_texture(uint16 i, String file_name);
	void set_frame_per_move(uint16 fpm);
	uint16 get_frame_per_move()const;
private:
	Point pos;
	e_direction direction;//�������Ă������
	e_direction next_direction;//���Ɍ�������
	uint16 score;
	Color col;//�C���X�g�ɒu��������܂ł̉��ɐF��ݒ�
	e_item_type special_item;
	uint16 special_item_thunder_timer;
	uint16 special_item_wing_timer;
	//sinatori
//	uint16 walking_timer;//�e�N�X�`���ύX�p�ϐ� timer�ˑ��ɂ��܂� �Ȃ����o�O��̂�
	uint16 invincible_timer;//���G���ԕϐ�
	String player_picture[8];// left, down, up
	uint16 frame_per_move;//���ꂪmaze_brock_size�̖񐔂łȂ��Ɠ����Ȃ����C����
};


class item {
public:
	item();
	item(Point p, e_item_type t, Texture& te);
	void draw(bool b);//true:�ʏ�T�C�Y�@false:�����̃T�C�Y
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

//�A�C�e���擾���G�t�F�N�g
struct item_effect :IEffect {
	Point pos;
	Color col;
	item_effect(const Point& p, const Color& c);
	bool update(double t)override;
};


//�ߊl���G�t�F�N�g
struct tag_effect :IEffect {
	Point pos;
	Texture* texture;
	tag_effect(const Point& p, Texture& t);
	bool update(double t)override;
};

bool intersect_maze(Rect r);
bool intersect_maze(Point p);
Point maze_brock_position(uint16 h, uint16 w);
Point random_maze_brock_position();//�����_���Ȗ��H���Œʍs�\�ȏꏊ�̍��W
Point random_player_respawn_position(player& player2, player& player3);//�v���C���[�̕����n�_
item random_next_item(Array<item>& ai, Texture* tex, uint16 &counter);//�A�C�e���������_���ɐݒu
void draw_timer(uint16 t);//�^�C�}�[������
void draw_big_point_box(uint16 t);
void draw_small_point_box(uint16 t);

bool is_tagged(player ghost, player tagger);//�ߊl����

void left_special_item_timer_draw(uint16 t, uint16 a, Color col);//�l�AMax�̒l�A�F
void right_special_item_timer_draw(uint16 t, uint16 a, Color col);//�l�AMax�̒l�A�F

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

const uint16 array_point_items_size = 15;//�|�C���g�A�C�e���̌�

const uint16 point_item_score = 100;
const uint16 golden_point_item_score = 200;
const uint16 additional_item_score = 50;
const uint16 additional_golden_item_score = 100;
const uint16 tag_score = 500;//�߂܂������̉��_
const uint16 tagged_score = 200;//�߂܂����Ƃ��̌��_

const Point delta_point[5] = { Point(0,0),Point(-1,0),Point(0,-1),Point(1,0),Point(0,1) };//�ړ����̍��� neutral left up right down

//sinatori
const uint16 default_invincible = 90;

//���ꂼ��̃v���C���[�̏������W
const uint16 init_player0_x = 16;
const uint16 init_player0_y = 1;
const uint16 init_player1_x = 16;
const uint16 init_player1_y = 40;
const uint16 init_player2_x = 1;
const uint16 init_player2_y = 1;
const uint16 init_player3_x = 1;
const uint16 init_player3_y = 40;

//���ꂼ��̃v���C���[�̐F(��)
const Color init_player0_color = Palette::Red;
const Color init_player1_color = Palette::Pink;
const Color init_player2_color = Palette::Skyblue;
const Color init_player3_color = Palette::Limegreen;

//�X�y�V�����A�C�e���̌��ʎ���
const uint16 special_thunder_effect_time = 60;
const uint16 special_wing_ghost_effect_time = 300;
const uint16 special_wing_tagger_effect_time = 180;


const uint16 ghost_speed = 3;
const uint16 tagger_speed = 4;
const uint16 special_wing_ghost_speed = 5;
const uint16 special_wing_tagger_speed = 6;