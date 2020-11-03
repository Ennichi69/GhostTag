#pragma once
#include <Siv3D.hpp>

typedef enum {
	timer,
	player0_x, player0_y,//逃げる側
	player1_x, player1_y,//逃げる側
	player2_x, player2_y,//追う側
	player3_x, player3_y,//追う側
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
	player2_status,//未捕獲 0 捕獲時 1
	player3_status,//未捕獲 0 捕獲時 1
	scene_status,
	player0_score,
	player1_score,
	player2_score,
	player3_score,
	player0_special_item,//e_item_type
	player1_special_item,//e_item_type
	player2_special_item,//e_item_type
	player3_special_item,//e_item_type
	player0_special_item_thunder_timer,
	player1_special_item_thunder_timer,
	player2_special_item_thunder_timer,
	player3_special_item_thunder_timer,
	player0_special_item_wing_timer,
	player1_special_item_wing_timer,
	player2_special_item_wing_timer,
	player3_special_item_wing_timer,
	player0_speed,
	player1_speed,
	player2_speed,
	player3_speed,
	player0_button_down,//特殊ボタンが押されているか
	player1_button_down,
	player2_button_down,
	player3_button_down,
	player0_invincible_timer,
	player1_invincible_timer,
	player2_invincible_timer,
	player3_invincible_timer,
	player0_isready,
	player1_isready,
	player2_isready,
	player3_isready,
	point_item_status,//[0]x座標,[0]y座標,[0]type,[1]x座標,[1]y座標,[1]type,[2]x座標...の順


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

bool left_button_down(Array<uint8>& a, bool b);
bool right_button_down(Array<uint8>& a, bool b);
e_direction left_joystick_direction(Array<uint8>& a, bool b, e_direction now_direction);
e_direction right_joystick_direction(Array<uint8>& a, bool b, e_direction now_direction);
void init();

constexpr uint16 port = 50000;//ポート番号
constexpr uint16 communication_data_size = 100;//通信に使う配列サイズ

