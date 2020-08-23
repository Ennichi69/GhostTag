#pragma once
#include <Siv3D.hpp>

typedef enum {
	timer,
	player0_x, player0_y,//�����鑤
	player1_x, player1_y,//�����鑤
	player2_x, player2_y,//�ǂ���
	player3_x, player3_y,//�ǂ���
	player0_direction,
	player1_direction,
	player2_direction,
	player3_direction,
	player0_next_direction,
	player1_next_direction,
	player2_next_direction,
	player3_next_direction,
	player0_status,
	player1_status,
	player2_status,
	player3_status,
	scene_status,
	player0_score,
	player1_score,
	player2_score,
	player3_score,
	point_item_status = 40,//[0]x���W,[0]y���W,[1]x���W,[1]y���W,[2]x���W...�̏�
	ghost_special_item_x = 70,
	ghost_special_item_y,
	ghost_special_item_status,//0 �}�b�v��ɂȂ� 1�}�b�v��ɂ���
	tagger_special_item_x,
	tagger_special_item_y,
	tagger_special_item_status,//0 �}�b�v��ɂȂ� 1�}�b�v��ɂ���
	player0_has_item,//false:0 true:1
	player1_has_item,//false:0 true:1
	player2_has_item,//false:0 true:1
	player3_has_item//false:0 true:1

} e_communication;

typedef enum {
	neutral,
	left,
	up,
	right,
	down
} e_direction;

typedef enum {
	initial_setting,
	connecting,
	title,
	game,
	error,
	result,
}e_scene;

bool left_button_down();
bool right_button_down();
e_direction left_joystick_direction();
e_direction right_joystick_direction();
void init();

constexpr uint16 port = 50000;//�|�[�g�ԍ�
constexpr uint16 communication_data_size = 100;//�ʐM�Ɏg���z��T�C�Y

