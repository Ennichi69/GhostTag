#include "Server_Game.hpp"

server_game::server_game(const InitData& init) :IScene(init) {
	getData().send_data[e_communication::scene_status] = e_scene::game;

	timer = init_time;

	//���ꂼ��̏ꏊ��������
	player0.set_pos(init_player0_x, init_player0_y);
	player1.set_pos(init_player1_x, init_player1_y);
	player2.set_pos(init_player2_x, init_player2_y);
	player3.set_pos(init_player3_x, init_player3_y);

	//���ꂼ��̐F��������
	player0.set_color(init_player0_color);
	player1.set_color(init_player1_color);
	player2.set_color(init_player2_color);
	player3.set_color(init_player3_color);

	//�|�C���g�A�C�e����������
	for (auto i : step(array_point_items_size)) {
		array_point_items.push_back(item(random_point_item_position(array_point_items), e_item_type::point));
	}

	//�e�N�X�`����������
	player0.set_texture(0, U"pictures/pump_left1.png");
	player0.set_texture(1, U"pictures/pump_left2.png");
	player0.set_texture(2, U"pictures/pump_up1.png");
	player0.set_texture(3, U"pictures/pump_up2.png");
	player0.set_texture(4, U"pictures/pump_right1.png");
	player0.set_texture(5, U"pictures/pump_right2.png");
	player0.set_texture(6, U"pictures/pump_down1.png");
	player0.set_texture(7, U"pictures/pump_down2.png");
	player0.set_frame_per_move(4);

	player1.set_texture(0, U"pictures/ghost_left1.png");
	player1.set_texture(1, U"pictures/ghost_left2.png");
	player1.set_texture(2, U"pictures/ghost_up1.png");
	player1.set_texture(3, U"pictures/ghost_up2.png");
	player1.set_texture(4, U"pictures/ghost_right1.png");
	player1.set_texture(5, U"pictures/ghost_right2.png");
	player1.set_texture(6, U"pictures/ghost_down1.png");
	player1.set_texture(7, U"pictures/ghost_down2.png");
	player1.set_frame_per_move(4);

	player2.set_texture(0, U"pictures/girl_left1.png");
	player2.set_texture(1, U"pictures/girl_left2.png");
	player2.set_texture(2, U"pictures/girl_up1.png");
	player2.set_texture(3, U"pictures/girl_up2.png");
	player2.set_texture(4, U"pictures/girl_right1.png");
	player2.set_texture(5, U"pictures/girl_right2.png");
	player2.set_texture(6, U"pictures/girl_down1.png");
	player2.set_texture(7, U"pictures/girl_down2.png");
	player2.set_frame_per_move(5);

	player3.set_texture(0, U"pictures/boy_left1.png");
	player3.set_texture(1, U"pictures/boy_left2.png");
	player3.set_texture(2, U"pictures/boy_up1.png");
	player3.set_texture(3, U"pictures/boy_up2.png");
	player3.set_texture(4, U"pictures/boy_right1.png");
	player3.set_texture(5, U"pictures/boy_right2.png");
	player3.set_texture(6, U"pictures/boy_down1.png");
	player3.set_texture(7, U"pictures/boy_down2.png");
	player3.set_frame_per_move(5);
	
	//���̃e�N�X�`����������
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

	maze_walls[2] = Texture(Resource(U"pictures/wall1.png"));
	maze_walls[3] = Texture(Resource(U"pictures/wall2.png"));
	maze_walls[4] = Texture(Resource(U"pictures/bookshelf.png"));
	maze_walls[5] = Texture(Resource(U"pictures/window.png"));
	maze_walls[6] = Texture(Resource(U"pictures/door.png"));

}

void server_game::update() {
	if (!getData().tcp_server.hasSession()) {
		//�ʐM�G���[�������A�G���[��ʂɑJ��
		getData().tcp_server.disconnect();
		changeScene(e_scene::error);
	}

	for (uint16 i = timer; i < getData().receive_data[e_communication::timer]; i++) {
		//���O�␳
		player2.update();
		player3.update();
	}
	getData().send_data[e_communication::player2_status] = 0;
	getData().send_data[e_communication::player3_status] = 0;

	uint16 inv_timer_0 = player0.get_invincible_timer();
	uint16 inv_timer_1 = player1.get_invincible_timer();
	if (inv_timer_0 > 60) {
		player0.update();
		player0.count_invincible_timer();
	}
	else {
		player0.update_direction(left_joystick_direction());
		player0.update();

		if (player0.get_invincible_timer() == 0) {
			if (tag(player0, player2)) {
				effect.add<tag_effect>(player0.get_pos());
				player2.add_score(tag_score);
				player0.set_pos(random_player_respawn_position(player2, player3));
				player0.set_invincible_timer();
				player0.set_direction(neutral);
				player0.set_next_direction(neutral);
				getData().send_data[e_communication::player2_status] = 1;
			}
			else if (tag(player0, player3)) {
				effect.add<tag_effect>(player0.get_pos());
				player3.add_score(tag_score);
				player0.set_pos(random_player_respawn_position(player2, player3));
				player0.set_invincible_timer();
				player0.set_direction(neutral);
				player0.set_next_direction(neutral);
				getData().send_data[e_communication::player3_status] = 1;
			}
		}
		else {
			player0.count_invincible_timer();
		}
	}

	if (inv_timer_1 > 60) {
		player1.update();
		player1.count_invincible_timer();
	}
	else {
		player1.update_direction(right_joystick_direction());
		player1.update();

		if (player1.get_invincible_timer() == 0) {
			if (tag(player1, player2)) {
				effect.add<tag_effect>(player1.get_pos());
				player2.add_score(tag_score);
				player1.set_pos(random_player_respawn_position(player2, player3));
				player1.set_invincible_timer();
				player1.set_direction(neutral);
				player1.set_next_direction(neutral);
				getData().send_data[e_communication::player2_status] = 1;
			}
			else if (tag(player1, player3)) {
				effect.add<tag_effect>(player1.get_pos());
				player3.add_score(tag_score);
				player1.set_pos(random_player_respawn_position(player2, player3));
				player1.set_invincible_timer();
				player1.set_direction(neutral);
				player1.set_next_direction(neutral);
				getData().send_data[e_communication::player3_status] = 1;
			}
			for (auto& it : array_point_items) {
				if (player0.intersects(it)) {
					effect.add<item_effect>(it.get_pos());
					it.set_pos(random_point_item_position(array_point_items));
					player0.add_score(point_item_score);
				}
				if (player1.intersects(it)) {
					effect.add<item_effect>(it.get_pos());
					it.set_pos(random_point_item_position(array_point_items));
					player1.add_score(point_item_score);
				}
			}
		}
		else {
			player1.count_invincible_timer();
		}
	}

	timer--;
	//�S�Ẵf�[�^�𑗂�Ԃ��Ă���(�Ӗ����������̂��܂܂��)

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
	player2.set_next_direction(e_direction(getData().receive_data[e_communication::player2_next_direction]));
	player3.set_next_direction(e_direction(getData().receive_data[e_communication::player3_next_direction]));
	if (timer == 0) {
		changeScene(e_scene::result);
	}
}

void server_game::draw_maze() const {
	for (auto i : step(maze_height)) {
		for (auto j : step(maze_width)) {
			if (maze_data[i][j]) {
				if (maze_data[i][j] == 1) {
					Rect(Arg::center(maze_brock_position(i, j)), maze_brock_size).draw(Palette::Black);
				}
				else {
					maze_walls[maze_data[i][j]].draw(Arg::center(maze_brock_position(i, j)));
				}
			}
			else {
				if (i == 0 || i == maze_height - 1 || j == 0 || j == maze_width - 1)continue;//�}�b�v�ɂ͑��݂��Ȃ�
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

void server_game::draw()const {
	draw_maze();
	draw_timer(timer);
	draw_big_point_box(player0.get_score() + player1.get_score());
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
	effect.update();
}