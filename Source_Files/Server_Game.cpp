#include "Server_Game.hpp"

server_game::server_game(const InitData& init) :IScene(init) {
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

	//ポイントアイテムを初期化
	for (auto i : step(array_point_items_size)) {
		array_point_items.push_back(item(random_point_item_position(array_point_items), e_item_type::point));
	}
}

void server_game::update() {
	if (!getData().tcp_server.hasSession()) {
		//通信エラー発生時、エラー画面に遷移
		getData().tcp_server.disconnect();
		changeScene(e_scene::error);
	}

	player0.update_direction(left_joystick_direction());
	player1.update_direction(right_joystick_direction());
	player0.update();
	player1.update();
	for (uint16 i = timer; i < getData().receive_data[e_communication::timer]; i++) {
		//ラグ補正
		player2.update();
		player3.update();
	}
	if (player0.intersects(player2.light())) {
		
	}
	for (auto &it : array_point_items) {
		if (player0.intersects(it)) {
			it.set_pos(random_point_item_position(array_point_items));
			player0.add_score(point_item_score);
		}
		if (player1.intersects(it)) {
			it.set_pos(random_point_item_position(array_point_items));
			player1.add_score(point_item_score);
		}
	}
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
	getData().send_data[e_communication::player0_score] = player0.get_score();
	getData().send_data[e_communication::player1_score] = player1.get_score();
	getData().send_data[e_communication::player2_score] = player2.get_score();
	getData().send_data[e_communication::player3_score] = player3.get_score();
	for (auto i : step(array_point_items_size)) {
		getData().send_data[e_communication::point_item_status + i * 2] = array_point_items[i].get_pos().x;
		getData().send_data[e_communication::point_item_status + i * 2 + 1] = array_point_items[i].get_pos().y;
	}
	getData().send_data[e_communication::ghost_special_item_x] = ghost_special_item.get_pos().x;
	getData().send_data[e_communication::ghost_special_item_y] = ghost_special_item.get_pos().y;
	getData().send_data[e_communication::ghost_special_item_status] = exist_ghost_special_item;
	getData().send_data[e_communication::ghost_special_item_x] = tagger_special_item.get_pos().x;
	getData().send_data[e_communication::ghost_special_item_y] = tagger_special_item.get_pos().y;
	getData().send_data[e_communication::ghost_special_item_status] = exist_tagger_special_item;
	getData().send_data[e_communication::player0_has_item] = player0.get_has_item();
	getData().send_data[e_communication::player1_has_item] = player1.get_has_item();
	getData().send_data[e_communication::player2_has_item] = player2.get_has_item();
	getData().send_data[e_communication::player3_has_item] = player3.get_has_item();
	getData().tcp_server.send(getData().send_data);
	while (getData().tcp_server.read(getData().receive_data));
	player2.set_pos(Point(getData().receive_data[e_communication::player2_x], getData().receive_data[e_communication::player2_y]));
	player3.set_pos(Point(getData().receive_data[e_communication::player3_x], getData().receive_data[e_communication::player3_y]));
	player2.set_direction(e_direction(getData().receive_data[e_communication::player2_direction]));
	player3.set_direction(e_direction(getData().receive_data[e_communication::player3_direction]));
}

void server_game::draw()const {
	draw_maze();
	draw_timer(timer);
	draw_big_point_box(player0.get_score()+player1.get_score());
	draw_small_point_box(player2.get_score() + player3.get_score());
	left_item_circle.draw();
	right_item_circle.draw();
	for (auto i : array_point_items) {
		i.draw();
	}
	player0.draw();
	player1.draw();
	player2.draw();
	player3.draw();
	player2.draw_light();
	player3.draw_light();
}