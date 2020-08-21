#include "Client_Game.hpp"

client_game::client_game(const InitData& init) :IScene(init) {
	getData().send_data[e_communication::scene_status] = e_scene::game;
	timer = init_time;

	//それぞれの場所を初期化
	player0.set_pos(init_player0_x, init_player0_y);
	player1.set_pos(init_player1_x, init_player1_y);
	player2.set_pos(init_player2_x, init_player2_y);
	player3.set_pos(init_player3_x, init_player3_y);

	//それぞれの色を初期化
	player0.set_color(init_player0_color);
	player1.set_color(init_player1_color);
	player2.set_color(init_player2_color);
	player3.set_color(init_player3_color);

}

void client_game::update() {
	if (getData().tcp_client.hasError()) {
		//通信エラー発生時、エラー画面に遷移
		getData().tcp_client.disconnect();
		changeScene(e_scene::error);
	}
	player2.update_direction(left_joystick_direction());
	player3.update_direction(right_joystick_direction());
	player2.update();
	player3.update();
	for (uint16 i = timer; i < getData().receive_data[e_communication::timer]; i++) {
		//ラグ補正
		player0.update();
		player1.update();
	}
	timer = getData().receive_data[e_communication::timer];
	timer--;

	//全てのデータを送り返しておく(意味が無いものも含まれる)
	getData().send_data[e_communication::timer] = timer;
	getData().send_data[e_communication::player0_x] = player0.get_pos().x;
	getData().send_data[e_communication::player0_y] = player0.get_pos().y;
	getData().send_data[e_communication::player1_x] = player1.get_pos().x;
	getData().send_data[e_communication::player1_y] = player1.get_pos().y;
	getData().send_data[e_communication::player2_x] = player2.get_pos().x;
	getData().send_data[e_communication::player2_y] = player2.get_pos().y;
	getData().send_data[e_communication::player3_x] = player3.get_pos().x;
	getData().send_data[e_communication::player3_y] = player3.get_pos().y;
	getData().send_data[e_communication::player0_direction] = player0.get_direction();
	getData().send_data[e_communication::player1_direction] = player1.get_direction();
	getData().send_data[e_communication::player2_direction] = player2.get_direction();
	getData().send_data[e_communication::player3_direction] = player3.get_direction();
	getData().send_data[e_communication::player0_next_direction] = player0.get_next_direction();
	getData().send_data[e_communication::player1_next_direction] = player1.get_next_direction();
	getData().send_data[e_communication::player2_next_direction] = player2.get_next_direction();
	getData().send_data[e_communication::player3_next_direction] = player3.get_next_direction();

	getData().tcp_client.send(getData().send_data);
	while (getData().tcp_client.read(getData().receive_data));
	player0.set_pos(Point(getData().receive_data[e_communication::player0_x], getData().receive_data[e_communication::player0_y]));
	player1.set_pos(Point(getData().receive_data[e_communication::player1_x], getData().receive_data[e_communication::player1_y]));
	player0.set_direction(e_direction(getData().receive_data[e_communication::player0_direction]));
	player1.set_direction(e_direction(getData().receive_data[e_communication::player1_direction]));
}

void client_game::draw()const {
	draw_maze();
	timer_box.draw();
	left_item_circle.draw();
	right_item_circle.draw();
	player2.draw();
	player3.draw();
	player2.draw_light();
	player3.draw_light();
}