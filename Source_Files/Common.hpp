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
	ghost_score,
	tagger_score,
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

