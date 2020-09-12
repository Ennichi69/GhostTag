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
	array_point_items.resize(array_point_items_size);
	
	player0.set_frame_per_move(4);
	player1.set_frame_per_move(4);

	player2.set_texture(0, U"pictures/girl_left1.png");
	player2.set_texture(1, U"pictures/girl_left2.png");
	player2.set_texture(2, U"pictures/girl_up1.png");
	player2.set_texture(3, U"pictures/girl_up2.png");
	player2.set_texture(4, U"pictures/girl_left1.png");
	player2.set_texture(5, U"pictures/girl_left2.png");
	player2.set_texture(6, U"pictures/girl_down1.png");
	player2.set_texture(7, U"pictures/girl_down2.png");
	player2.set_frame_per_move(5);

	player3.set_texture(0, U"pictures/boy_left1.png");
	player3.set_texture(1, U"pictures/boy_left2.png");
	player3.set_texture(2, U"pictures/boy_up1.png");
	player3.set_texture(3, U"pictures/boy_up2.png");
	player3.set_texture(4, U"pictures/boy_left1.png");
	player3.set_texture(5, U"pictures/boy_left2.png");
	player3.set_texture(6, U"pictures/boy_down1.png");
	player3.set_texture(7, U"pictures/boy_down2.png");
	player3.set_frame_per_move(5);

	//道のテクスチャを初期化
	junction_u = Texture(Resource(U"pictures/junction_a.png"));
	junction_l = Texture(Resource(U"pictures/junction_b.png"));
	junction_d = Texture(Resource(U"pictures/junction_c.png"));
	junction_r = Texture(Resource(U"pictures/junction_d.png"));

	corner_ld = Texture(Resource(U"pictures/corner_a.png"));
	corner_rd = Texture(Resource(U"pictures/corner_b.png"));
	corner_ru = Texture(Resource(U"pictures/corner_c.png"));
	corner_lu = Texture(Resource(U"pictures/corner_d.png"));
	street_ud = Texture(Resource(U"pictures/street_vert.png"));
	street_lr = Texture(Resource(U"pictures/street_hori.png"));
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
	getData().tcp_client.send(getData().send_data);
	while (getData().tcp_client.read(getData().receive_data)) {
		player0.set_pos(Point(getData().receive_data[e_communication::player0_x], getData().receive_data[e_communication::player0_y]));
		player1.set_pos(Point(getData().receive_data[e_communication::player1_x], getData().receive_data[e_communication::player1_y]));
		player0.set_direction(e_direction(getData().receive_data[e_communication::player0_direction]));
		player1.set_direction(e_direction(getData().receive_data[e_communication::player1_direction]));
		player0.set_next_direction(e_direction(getData().receive_data[e_communication::player0_next_direction]));
		player1.set_next_direction(e_direction(getData().receive_data[e_communication::player1_next_direction]));
		//得点管理は全てserver側なので
		player0.set_score(getData().receive_data[e_communication::player0_score]);
		player1.set_score(getData().receive_data[e_communication::player1_score]);
		player2.set_score(getData().receive_data[e_communication::player2_score]);
		player3.set_score(getData().receive_data[e_communication::player3_score]);
		for (auto i : step(array_point_items_size)) {
			if (array_point_items[i].get_pos() != Point(getData().receive_data[e_communication::point_item_status + i * 2], getData().receive_data[e_communication::point_item_status + i * 2 + 1])) {
				effect.add<item_effect>(array_point_items[i].get_pos());
			}
			array_point_items[i].set_pos(Point(getData().receive_data[e_communication::point_item_status + i * 2], getData().receive_data[e_communication::point_item_status + i * 2 + 1]));
		}
		timer = getData().receive_data[e_communication::timer];
		if (getData().receive_data[e_communication::player2_status]) {
			effect.add<tag_effect>(player2.get_pos());
		}
		if (getData().receive_data[e_communication::player3_status]) {
			effect.add<tag_effect>(player3.get_pos());
		}
	}
	if (timer == 0) {
		changeScene(e_scene::result);
	}
}

void client_game::draw_maze() const {
	for (auto i : step(maze_height)) {
		for (auto j : step(maze_width)) {
			if (maze_data[i][j]) {
				Rect(Arg::center(maze_brock_position(i, j)), maze_brock_size).draw(Palette::Orange);
			}
			else {
				if (i == 0 || i == maze_height - 1 || j == 0 || j == maze_width - 1)continue;//マップには存在しない
				if (maze_data[i - 1][j]) {
					if (maze_data[i][j - 1])
						corner_rd.draw(Arg::center(maze_brock_position(i, j)));
					else if (maze_data[i + 1][j])
						street_lr.draw(Arg::center(maze_brock_position(i, j)));
					else if (maze_data[i][j + 1])
						corner_ld.draw(Arg::center(maze_brock_position(i, j)));
					else
						junction_u.draw(Arg::center(maze_brock_position(i, j)));
				}
				else if (maze_data[i][j - 1]) {
					if (maze_data[i + 1][j])
						corner_ru.draw(Arg::center(maze_brock_position(i, j)));
					else if (maze_data[i][j + 1])
						street_ud.draw(Arg::center(maze_brock_position(i, j)));
					else
						junction_l.draw(Arg::center(maze_brock_position(i, j)));
				}
				else if (maze_data[i + 1][j]) {
					if (maze_data[i][j + 1])
						corner_lu.draw(Arg::center(maze_brock_position(i, j)));
					else
						junction_d.draw(Arg::center(maze_brock_position(i, j)));
				}
				else {
					junction_r.draw(Arg::center(maze_brock_position(i, j)));
				}
			}
		}
	}
}

void client_game::draw()const {
	draw_maze();
	draw_timer(timer);
	draw_big_point_box(player2.get_score() + player3.get_score());
	draw_small_point_box(player0.get_score() + player1.get_score());
	left_item_circle.draw();
	right_item_circle.draw();
	for (auto i : array_point_items) {
		i.draw();
	}
	player2.draw();
	player3.draw();
	player2.draw_light();
	player3.draw_light();
	effect.update();
}