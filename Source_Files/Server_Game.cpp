#include "Server_Game.hpp"

server_game::server_game(const InitData& init) :IScene(init) {
	getData().send_data[e_communication::scene_status] = e_scene::game;

	item_counter = 0;
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

	//���ꂼ���special_item��������
	player0.set_special_item(e_item_type::nothing);
	player1.set_special_item(e_item_type::nothing);
	player2.set_special_item(e_item_type::nothing);
	player3.set_special_item(e_item_type::nothing);

	//�|�C���g�A�C�e����������
	for (auto i : step(array_point_items_size)) {
		array_items.push_back(random_next_item(array_items, item_pictures,item_counter));
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
	player0.set_frame_per_move(ghost_speed);

	player1.set_texture(0, U"pictures/ghost_left1.png");
	player1.set_texture(1, U"pictures/ghost_left2.png");
	player1.set_texture(2, U"pictures/ghost_up1.png");
	player1.set_texture(3, U"pictures/ghost_up2.png");
	player1.set_texture(4, U"pictures/ghost_right1.png");
	player1.set_texture(5, U"pictures/ghost_right2.png");
	player1.set_texture(6, U"pictures/ghost_down1.png");
	player1.set_texture(7, U"pictures/ghost_down2.png");
	player1.set_frame_per_move(ghost_speed);

	player2.set_texture(0, U"pictures/boy_left1.png");
	player2.set_texture(1, U"pictures/boy_left2.png");
	player2.set_texture(2, U"pictures/boy_up1.png");
	player2.set_texture(3, U"pictures/boy_up2.png");
	player2.set_texture(4, U"pictures/boy_right1.png");
	player2.set_texture(5, U"pictures/boy_right2.png");
	player2.set_texture(6, U"pictures/boy_down1.png");
	player2.set_texture(7, U"pictures/boy_down2.png");
	player2.set_frame_per_move(tagger_speed);

	player3.set_texture(0, U"pictures/girl_left1.png");
	player3.set_texture(1, U"pictures/girl_left2.png");
	player3.set_texture(2, U"pictures/girl_up1.png");
	player3.set_texture(3, U"pictures/girl_up2.png");
	player3.set_texture(4, U"pictures/girl_right1.png");
	player3.set_texture(5, U"pictures/girl_right2.png");
	player3.set_texture(6, U"pictures/girl_down1.png");
	player3.set_texture(7, U"pictures/girl_down2.png");
	player3.set_frame_per_move(tagger_speed);
	
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

	cross = Texture(Resource(U"pictures/cross.png"));

	maze_walls[2] = Texture(Resource(U"pictures/wall1.png"));
	maze_walls[3] = Texture(Resource(U"pictures/wall2.png"));
	maze_walls[4] = Texture(Resource(U"pictures/bookshelf.png"));
	maze_walls[5] = Texture(Resource(U"pictures/window.png"));
	maze_walls[6] = Texture(Resource(U"pictures/door.png"));

	item_pictures[0] = Texture(Resource(U"pictures/point_candy1.png"));
	item_pictures[1] = Texture(Resource(U"pictures/point_candy2.png"));
	item_pictures[2] = Texture(Resource(U"pictures/point_chocolate.png"));
	item_pictures[3] = Texture(Resource(U"pictures/special_thunder.png"));
	item_pictures[4] = Texture(Resource(U"pictures/special_wing.png"));

	background = Texture(Resource(U"pictures/background.png"));

	special_thunder_picture = Texture(Resource(U"pictures/special_thunder.png"));
	special_wing_picture = Texture(Resource(U"pictures/special_wing.png"));

	pumpkin_picture = Texture(Resource(U"pictures/pump_left1.png"));
	ghost_picture = Texture(Resource(U"pictures/ghost_left1.png"));
}

void server_game::update() {
	Array<uint8>serial_array;
	if (getData().serial_available) {
		serial_array = getData().serial.readBytes();
	}
	if (!getData().tcp_server.hasSession()) {
		//�ʐM�G���[�������A�G���[��ʂɑJ��
		getData().tcp_server.disconnect();
		changeScene(e_scene::error);
	}
	if (timer > start_time) {

	}
	else {
		if (timer == start_time)AudioAsset(U"main_theme").play();
		//���O�␳
		if (player0.get_special_item_thunder_timer() != 0 && player1.get_special_item_thunder_timer() != 0) {
			player2.update();
			player3.update();
		}
		getData().send_data[e_communication::player2_status] = e_ghost_type::none;
		getData().send_data[e_communication::player3_status] = e_ghost_type::none;

		uint16 inv_timer_0 = player0.get_invincible_timer();
		uint16 inv_timer_1 = player1.get_invincible_timer();
		if (inv_timer_0 > 60) {
			if (player2.get_special_item_thunder_timer() == 0 && player3.get_special_item_thunder_timer() == 0) {
				player0.update();
			}
			player0.count_invincible_timer();
		}
		else {
			if (player2.get_special_item_thunder_timer() == 0 && player3.get_special_item_thunder_timer() == 0) {
				player0.update_direction(left_joystick_direction(serial_array, getData().serial_available, player0.get_direction()));
				player0.update();
			}
			if (player0.get_invincible_timer() == 0) {
				if (is_tagged(player0, player2)) {
					effect.add<tag_effect>(player0.get_pos(), pumpkin_picture);
					player2.add_score(tag_score);
					player0.remove_score(tagged_score);
					player0.set_pos(random_player_respawn_position(player2, player3));
					player0.set_invincible_timer();
					player0.set_direction(neutral);
					player0.set_next_direction(neutral);
					getData().send_data[e_communication::player2_status] = e_ghost_type::pumpkin;
				}
				else if (is_tagged(player0, player3)) {
					effect.add<tag_effect>(player0.get_pos(), pumpkin_picture);
					player3.add_score(tag_score);
					player0.remove_score(tagged_score);
					player0.set_pos(random_player_respawn_position(player2, player3));
					player0.set_invincible_timer();
					player0.set_direction(neutral);
					player0.set_next_direction(neutral);
					getData().send_data[e_communication::player3_status] = e_ghost_type::pumpkin;
				}
			}
			else {
				player0.count_invincible_timer();
			}
		}

		if (inv_timer_1 > 60) {
			if (player2.get_special_item_thunder_timer() == 0 && player3.get_special_item_thunder_timer() == 0) {
				player1.update();
			}
			player1.count_invincible_timer();
		}
		else {
			if (player2.get_special_item_thunder_timer() == 0 && player3.get_special_item_thunder_timer() == 0) {
				player1.update_direction(right_joystick_direction(serial_array, getData().serial_available, player1.get_direction()));
				player1.update();
			}
			if (player1.get_invincible_timer() == 0) {
				if (is_tagged(player1, player2)) {
					effect.add<tag_effect>(player1.get_pos(), ghost_picture);
					player2.add_score(tag_score);
					player1.remove_score(tagged_score);
					player1.set_pos(random_player_respawn_position(player2, player3));
					player1.set_invincible_timer();
					player1.set_direction(neutral);
					player1.set_next_direction(neutral);
					getData().send_data[e_communication::player2_status] = e_ghost_type::ghost;
				}
				else if (is_tagged(player1, player3)) {
					effect.add<tag_effect>(player1.get_pos(), ghost_picture);
					player3.add_score(tag_score);
					player1.remove_score(tagged_score);
					player1.set_pos(random_player_respawn_position(player2, player3));
					player1.set_invincible_timer();
					player1.set_direction(neutral);
					player1.set_next_direction(neutral);
					getData().send_data[e_communication::player3_status] = e_ghost_type::ghost;
				}
			}
			else {
				player1.count_invincible_timer();
			}
		}

		//�A�C�e���Ƃ̓����蔻��
		if (timer <= start_time) {
			for (auto& it : array_items) {
				if (player0.intersects(it)) {
					if (it.get_type() == special_thunder || it.get_type() == special_wing) {
						if (player0.get_special_item() == nothing) {
							player0.set_special_item(it.get_type());
							effect.add<item_effect>(it.get_pos(), Palette::Orange);
							it = random_next_item(array_items, item_pictures, item_counter);
						}
					}
					else {
						effect.add<item_effect>(it.get_pos(), Palette::Lime);
						it = random_next_item(array_items, item_pictures, item_counter);
						player0.add_score(point_item_score);
						if (player0.get_special_item_wing_timer() != 0) {
							player0.add_score(additional_item_score);
						}
					}
				}
				if (player1.intersects(it)) {
					if (it.get_type() == special_thunder || it.get_type() == special_wing) {
						if (player1.get_special_item() == nothing) {
							player1.set_special_item(it.get_type());
							effect.add<item_effect>(it.get_pos(), Palette::Orange);
							it = random_next_item(array_items, item_pictures, item_counter);
						}
					}
					else {
						effect.add<item_effect>(it.get_pos(), Palette::Lime);
						it = random_next_item(array_items, item_pictures, item_counter);
						player1.add_score(point_item_score);
						if (player1.get_special_item_wing_timer() != 0) {
							player1.add_score(additional_item_score);
						}
					}
				}
				if (player2.intersects(it)) {
					if (it.get_type() == special_thunder || it.get_type() == special_wing) {
						if (player2.get_special_item() == nothing) {
							player2.set_special_item(it.get_type());
							effect.add<item_effect>(it.get_pos(), Palette::Orange);
							it = random_next_item(array_items, item_pictures, item_counter);
						}
					}
				}
				if (player3.intersects(it)) {
					if (it.get_type() == special_thunder || it.get_type() == special_wing) {
						if (player3.get_special_item() == nothing) {
							player3.set_special_item(it.get_type());
							effect.add<item_effect>(it.get_pos(), Palette::Orange);
							it = random_next_item(array_items, item_pictures, item_counter);
						}
					}
				}
			}
		}
		//�X�y�V�����A�C�e���̎g�p
		if (left_button_down(serial_array, getData().serial_available) && player0.get_special_item() == special_thunder) {
			AudioAsset(U"thunder").stop();
			AudioAsset(U"thunder").play();
			player0.set_special_item(in_use);
			player0.set_special_item_thunder_timer(special_thunder_effect_time);
			player2.set_texture(0, U"pictures/boy_left1_thunder.png");
			player2.set_texture(1, U"pictures/boy_left2_thunder.png");
			player2.set_texture(2, U"pictures/boy_up1_thunder.png");
			player2.set_texture(3, U"pictures/boy_up2_thunder.png");
			player2.set_texture(4, U"pictures/boy_right1_thunder.png");
			player2.set_texture(5, U"pictures/boy_right2_thunder.png");
			player2.set_texture(6, U"pictures/boy_down1_thunder.png");
			player2.set_texture(7, U"pictures/boy_down2_thunder.png");
			player3.set_texture(0, U"pictures/girl_left1_thunder.png");
			player3.set_texture(1, U"pictures/girl_left2_thunder.png");
			player3.set_texture(2, U"pictures/girl_up1_thunder.png");
			player3.set_texture(3, U"pictures/girl_up2_thunder.png");
			player3.set_texture(4, U"pictures/girl_right1_thunder.png");
			player3.set_texture(5, U"pictures/girl_right2_thunder.png");
			player3.set_texture(6, U"pictures/girl_down1_thunder.png");
			player3.set_texture(7, U"pictures/girl_down2_thunder.png");
		}
		if (left_button_down(serial_array, getData().serial_available) && player0.get_special_item() == special_wing) {
			AudioAsset(U"wing").stop();
			AudioAsset(U"wing").play();
			player0.set_special_item(in_use);
			player0.set_special_item_wing_timer(special_wing_ghost_effect_time);
			player0.set_frame_per_move(special_wing_ghost_speed);
			player0.set_texture(0, U"pictures/pump_left1_wing.png");
			player0.set_texture(1, U"pictures/pump_left2_wing.png");
			player0.set_texture(2, U"pictures/pump_up1_wing.png");
			player0.set_texture(3, U"pictures/pump_up2_wing.png");
			player0.set_texture(4, U"pictures/pump_right1_wing.png");
			player0.set_texture(5, U"pictures/pump_right2_wing.png");
			player0.set_texture(6, U"pictures/pump_down1_wing.png");
			player0.set_texture(7, U"pictures/pump_down2_wing.png");
		}
		if (right_button_down(serial_array, getData().serial_available) && player1.get_special_item() == special_thunder) {
			AudioAsset(U"thunder").stop();
			AudioAsset(U"thunder").play();
			player1.set_special_item(in_use);
			player1.set_special_item_thunder_timer(special_thunder_effect_time);
			player2.set_texture(0, U"pictures/boy_left1_thunder.png");
			player2.set_texture(1, U"pictures/boy_left2_thunder.png");
			player2.set_texture(2, U"pictures/boy_up1_thunder.png");
			player2.set_texture(3, U"pictures/boy_up2_thunder.png");
			player2.set_texture(4, U"pictures/boy_right1_thunder.png");
			player2.set_texture(5, U"pictures/boy_right2_thunder.png");
			player2.set_texture(6, U"pictures/boy_down1_thunder.png");
			player2.set_texture(7, U"pictures/boy_down2_thunder.png");
			player3.set_texture(0, U"pictures/girl_left1_thunder.png");
			player3.set_texture(1, U"pictures/girl_left2_thunder.png");
			player3.set_texture(2, U"pictures/girl_up1_thunder.png");
			player3.set_texture(3, U"pictures/girl_up2_thunder.png");
			player3.set_texture(4, U"pictures/girl_right1_thunder.png");
			player3.set_texture(5, U"pictures/girl_right2_thunder.png");
			player3.set_texture(6, U"pictures/girl_down1_thunder.png");
			player3.set_texture(7, U"pictures/girl_down2_thunder.png");
		}
		if (right_button_down(serial_array, getData().serial_available) && player1.get_special_item() == special_wing) {
			AudioAsset(U"wing").stop();
			AudioAsset(U"wing").play();
			player1.set_special_item(in_use);
			player1.set_special_item_wing_timer(special_wing_ghost_effect_time);
			player1.set_frame_per_move(special_wing_ghost_speed);
			player1.set_texture(0, U"pictures/ghost_left1_wing.png");
			player1.set_texture(1, U"pictures/ghost_left2_wing.png");
			player1.set_texture(2, U"pictures/ghost_up1_wing.png");
			player1.set_texture(3, U"pictures/ghost_up2_wing.png");
			player1.set_texture(4, U"pictures/ghost_right1_wing.png");
			player1.set_texture(5, U"pictures/ghost_right2_wing.png");
			player1.set_texture(6, U"pictures/ghost_down1_wing.png");
			player1.set_texture(7, U"pictures/ghost_down2_wing.png");
		}
		//�X�y�V�����A�C�e���̌���
		if (player0.get_special_item_thunder_timer() != 0) {
			player0.count_special_item_thunder_timer();
			if (player0.get_special_item_thunder_timer() == 0) {
				player0.set_special_item(e_item_type::nothing);
				if (player1.get_special_item_thunder_timer() == 0) {
					player2.set_texture(0, U"pictures/boy_left1.png");
					player2.set_texture(1, U"pictures/boy_left2.png");
					player2.set_texture(2, U"pictures/boy_up1.png");
					player2.set_texture(3, U"pictures/boy_up2.png");
					player2.set_texture(4, U"pictures/boy_right1.png");
					player2.set_texture(5, U"pictures/boy_right2.png");
					player2.set_texture(6, U"pictures/boy_down1.png");
					player2.set_texture(7, U"pictures/boy_down2.png");
					player3.set_texture(0, U"pictures/girl_left1.png");
					player3.set_texture(1, U"pictures/girl_left2.png");
					player3.set_texture(2, U"pictures/girl_up1.png");
					player3.set_texture(3, U"pictures/girl_up2.png");
					player3.set_texture(4, U"pictures/girl_right1.png");
					player3.set_texture(5, U"pictures/girl_right2.png");
					player3.set_texture(6, U"pictures/girl_down1.png");
					player3.set_texture(7, U"pictures/girl_down2.png");
				}
			}
		}
		if (player1.get_special_item_thunder_timer() != 0) {
			player1.count_special_item_thunder_timer();
			if (player1.get_special_item_thunder_timer() == 0) {
				player1.set_special_item(e_item_type::nothing);
				if (player0.get_special_item_thunder_timer() == 0) {
					player2.set_texture(0, U"pictures/boy_left1.png");
					player2.set_texture(1, U"pictures/boy_left2.png");
					player2.set_texture(2, U"pictures/boy_up1.png");
					player2.set_texture(3, U"pictures/boy_up2.png");
					player2.set_texture(4, U"pictures/boy_right1.png");
					player2.set_texture(5, U"pictures/boy_right2.png");
					player2.set_texture(6, U"pictures/boy_down1.png");
					player2.set_texture(7, U"pictures/boy_down2.png");
					player3.set_texture(0, U"pictures/girl_left1.png");
					player3.set_texture(1, U"pictures/girl_left2.png");
					player3.set_texture(2, U"pictures/girl_up1.png");
					player3.set_texture(3, U"pictures/girl_up2.png");
					player3.set_texture(4, U"pictures/girl_right1.png");
					player3.set_texture(5, U"pictures/girl_right2.png");
					player3.set_texture(6, U"pictures/girl_down1.png");
					player3.set_texture(7, U"pictures/girl_down2.png");
				}
			}
		}
		if (player0.get_special_item_wing_timer() != 0) {
			player0.count_special_item_wing_timer();
			if (player0.get_special_item_wing_timer() == 0) {
				player0.set_frame_per_move(ghost_speed);
				player0.set_special_item(e_item_type::nothing);
				player0.set_texture(0, U"pictures/pump_left1.png");
				player0.set_texture(1, U"pictures/pump_left2.png");
				player0.set_texture(2, U"pictures/pump_up1.png");
				player0.set_texture(3, U"pictures/pump_up2.png");
				player0.set_texture(4, U"pictures/pump_right1.png");
				player0.set_texture(5, U"pictures/pump_right2.png");
				player0.set_texture(6, U"pictures/pump_down1.png");
				player0.set_texture(7, U"pictures/pump_down2.png");
			}
		}
		if (player1.get_special_item_wing_timer() != 0) {
			player1.count_special_item_wing_timer();
			if (player1.get_special_item_wing_timer() == 0) {
				player1.set_frame_per_move(ghost_speed);
				player1.set_special_item(e_item_type::nothing);
				player1.set_texture(0, U"pictures/ghost_left1.png");
				player1.set_texture(1, U"pictures/ghost_left2.png");
				player1.set_texture(2, U"pictures/ghost_up1.png");
				player1.set_texture(3, U"pictures/ghost_up2.png");
				player1.set_texture(4, U"pictures/ghost_right1.png");
				player1.set_texture(5, U"pictures/ghost_right2.png");
				player1.set_texture(6, U"pictures/ghost_down1.png");
				player1.set_texture(7, U"pictures/ghost_down2.png");
			}
		}
		if (player2.get_special_item_thunder_timer() != 0) {
			player2.count_special_item_thunder_timer();
			if (player2.get_special_item_thunder_timer() == 0) {
				player2.set_special_item(e_item_type::nothing);
				if (player3.get_special_item_thunder_timer() == 0) {
					player0.set_texture(0, U"pictures/pump_left1.png");
					player0.set_texture(1, U"pictures/pump_left2.png");
					player0.set_texture(2, U"pictures/pump_up1.png");
					player0.set_texture(3, U"pictures/pump_up2.png");
					player0.set_texture(4, U"pictures/pump_right1.png");
					player0.set_texture(5, U"pictures/pump_right2.png");
					player0.set_texture(6, U"pictures/pump_down1.png");
					player0.set_texture(7, U"pictures/pump_down2.png");
					player1.set_texture(0, U"pictures/ghost_left1.png");
					player1.set_texture(1, U"pictures/ghost_left2.png");
					player1.set_texture(2, U"pictures/ghost_up1.png");
					player1.set_texture(3, U"pictures/ghost_up2.png");
					player1.set_texture(4, U"pictures/ghost_right1.png");
					player1.set_texture(5, U"pictures/ghost_right2.png");
					player1.set_texture(6, U"pictures/ghost_down1.png");
					player1.set_texture(7, U"pictures/ghost_down2.png");
				}
			}
		}
		if (player3.get_special_item_thunder_timer() != 0) {
			player3.count_special_item_thunder_timer();
			if (player3.get_special_item_thunder_timer() == 0) {
				player3.set_special_item(e_item_type::nothing);
				if (player2.get_special_item_thunder_timer() == 0) {
					player0.set_texture(0, U"pictures/pump_left1.png");
					player0.set_texture(1, U"pictures/pump_left2.png");
					player0.set_texture(2, U"pictures/pump_up1.png");
					player0.set_texture(3, U"pictures/pump_up2.png");
					player0.set_texture(4, U"pictures/pump_right1.png");
					player0.set_texture(5, U"pictures/pump_right2.png");
					player0.set_texture(6, U"pictures/pump_down1.png");
					player0.set_texture(7, U"pictures/pump_down2.png");
					player1.set_texture(0, U"pictures/ghost_left1.png");
					player1.set_texture(1, U"pictures/ghost_left2.png");
					player1.set_texture(2, U"pictures/ghost_up1.png");
					player1.set_texture(3, U"pictures/ghost_up2.png");
					player1.set_texture(4, U"pictures/ghost_right1.png");
					player1.set_texture(5, U"pictures/ghost_right2.png");
					player1.set_texture(6, U"pictures/ghost_down1.png");
					player1.set_texture(7, U"pictures/ghost_down2.png");
				}
			}
		}
		if (player2.get_special_item_wing_timer() != 0) {
			player2.count_special_item_wing_timer();
			if (player2.get_special_item_wing_timer() == 0) {
				player2.set_frame_per_move(tagger_speed);
				player2.set_special_item(e_item_type::nothing);
				player2.set_texture(0, U"pictures/boy_left1.png");
				player2.set_texture(1, U"pictures/boy_left2.png");
				player2.set_texture(2, U"pictures/boy_up1.png");
				player2.set_texture(3, U"pictures/boy_up2.png");
				player2.set_texture(4, U"pictures/boy_right1.png");
				player2.set_texture(5, U"pictures/boy_right2.png");
				player2.set_texture(6, U"pictures/boy_down1.png");
				player2.set_texture(7, U"pictures/boy_down2.png");
			}
		}
		if (player3.get_special_item_wing_timer() != 0) {
			player3.count_special_item_wing_timer();
			if (player3.get_special_item_wing_timer() == 0) {
				player3.set_frame_per_move(tagger_speed);
				player3.set_special_item(e_item_type::nothing);
				player3.set_texture(0, U"pictures/girl_left1.png");
				player3.set_texture(1, U"pictures/girl_left2.png");
				player3.set_texture(2, U"pictures/girl_up1.png");
				player3.set_texture(3, U"pictures/girl_up2.png");
				player3.set_texture(4, U"pictures/girl_right1.png");
				player3.set_texture(5, U"pictures/girl_right2.png");
				player3.set_texture(6, U"pictures/girl_down1.png");
				player3.set_texture(7, U"pictures/girl_down2.png");
			}
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
	getData().send_data[e_communication::player0_special_item] = player0.get_special_item();
	getData().send_data[e_communication::player1_special_item] = player1.get_special_item();
	getData().send_data[e_communication::player2_special_item] = player2.get_special_item();
	getData().send_data[e_communication::player3_special_item] = player3.get_special_item();
	getData().send_data[e_communication::player0_special_item_thunder_timer] = player0.get_special_item_thunder_timer();
	getData().send_data[e_communication::player1_special_item_thunder_timer] = player1.get_special_item_thunder_timer();
	getData().send_data[e_communication::player2_special_item_thunder_timer] = player2.get_special_item_thunder_timer();
	getData().send_data[e_communication::player3_special_item_thunder_timer] = player3.get_special_item_thunder_timer();
	getData().send_data[e_communication::player0_special_item_wing_timer] = player0.get_special_item_wing_timer();
	getData().send_data[e_communication::player1_special_item_wing_timer] = player1.get_special_item_wing_timer();
	getData().send_data[e_communication::player2_special_item_wing_timer] = player2.get_special_item_wing_timer();
	getData().send_data[e_communication::player3_special_item_wing_timer] = player3.get_special_item_wing_timer();
	getData().send_data[e_communication::player0_speed] = player0.get_frame_per_move();
	getData().send_data[e_communication::player1_speed] = player1.get_frame_per_move();
	getData().send_data[e_communication::player2_speed] = player2.get_frame_per_move();
	getData().send_data[e_communication::player3_speed] = player3.get_frame_per_move();
	getData().send_data[e_communication::player0_button_down] = left_button_down(serial_array,  getData().serial_available);
	getData().send_data[e_communication::player1_button_down] = right_button_down(serial_array,  getData().serial_available);

	for (auto i : step(array_point_items_size)) {
		getData().send_data[e_communication::point_item_status + i * 3] = array_items[i].get_pos().x;
		getData().send_data[e_communication::point_item_status + i * 3 + 1] = array_items[i].get_pos().y;
		getData().send_data[e_communication::point_item_status + i * 3 + 2] = array_items[i].get_type();
	}
	getData().tcp_server.send(getData().send_data);
	while (getData().tcp_server.read(getData().receive_data)) {
		player2.set_pos(Point(getData().receive_data[e_communication::player2_x], getData().receive_data[e_communication::player2_y]));
		player3.set_pos(Point(getData().receive_data[e_communication::player3_x], getData().receive_data[e_communication::player3_y]));
		player2.set_direction(e_direction(getData().receive_data[e_communication::player2_direction]));
		player3.set_direction(e_direction(getData().receive_data[e_communication::player3_direction]));
		player2.set_next_direction(e_direction(getData().receive_data[e_communication::player2_next_direction]));
		player3.set_next_direction(e_direction(getData().receive_data[e_communication::player3_next_direction]));
		//���葤�̃X�y�V�����A�C�e���̎g�p
		if (getData().receive_data[e_communication::player2_button_down] && player2.get_special_item() == special_thunder) {
			AudioAsset(U"thunder").stop();
			AudioAsset(U"thunder").play();
			player2.set_special_item(in_use);
			player2.set_special_item_thunder_timer(special_thunder_effect_time);
			player0.set_texture(0, U"pictures/pump_left1_thunder.png");
			player0.set_texture(1, U"pictures/pump_left2_thunder.png");
			player0.set_texture(2, U"pictures/pump_up1_thunder.png");
			player0.set_texture(3, U"pictures/pump_up2_thunder.png");
			player0.set_texture(4, U"pictures/pump_right1_thunder.png");
			player0.set_texture(5, U"pictures/pump_right2_thunder.png");
			player0.set_texture(6, U"pictures/pump_down1_thunder.png");
			player0.set_texture(7, U"pictures/pump_down2_thunder.png");
			player1.set_texture(0, U"pictures/ghost_left1_thunder.png");
			player1.set_texture(1, U"pictures/ghost_left2_thunder.png");
			player1.set_texture(2, U"pictures/ghost_up1_thunder.png");
			player1.set_texture(3, U"pictures/ghost_up2_thunder.png");
			player1.set_texture(4, U"pictures/ghost_right1_thunder.png");
			player1.set_texture(5, U"pictures/ghost_right2_thunder.png");
			player1.set_texture(6, U"pictures/ghost_down1_thunder.png");
			player1.set_texture(7, U"pictures/ghost_down2_thunder.png");
		}
		if (getData().receive_data[e_communication::player2_button_down] && player2.get_special_item() == special_wing) {
			player2.set_special_item(in_use);
			player2.set_special_item_wing_timer(special_wing_tagger_effect_time);
			player2.set_frame_per_move(special_wing_tagger_speed);
			player2.set_texture(0, U"pictures/boy_left1_wing.png");
			player2.set_texture(1, U"pictures/boy_left2_wing.png");
			player2.set_texture(2, U"pictures/boy_up1_wing.png");
			player2.set_texture(3, U"pictures/boy_up2_wing.png");
			player2.set_texture(4, U"pictures/boy_right1_wing.png");
			player2.set_texture(5, U"pictures/boy_right2_wing.png");
			player2.set_texture(6, U"pictures/boy_down1_wing.png");
			player2.set_texture(7, U"pictures/boy_down2_wing.png");
		}
		if (getData().receive_data[e_communication::player3_button_down] && player3.get_special_item() == special_thunder) {
			AudioAsset(U"thunder").stop();
			AudioAsset(U"thunder").play();
			player3.set_special_item(in_use);
			player3.set_special_item_thunder_timer(special_thunder_effect_time);
			player0.set_texture(0, U"pictures/pump_left1_thunder.png");
			player0.set_texture(1, U"pictures/pump_left2_thunder.png");
			player0.set_texture(2, U"pictures/pump_up1_thunder.png");
			player0.set_texture(3, U"pictures/pump_up2_thunder.png");
			player0.set_texture(4, U"pictures/pump_right1_thunder.png");
			player0.set_texture(5, U"pictures/pump_right2_thunder.png");
			player0.set_texture(6, U"pictures/pump_down1_thunder.png");
			player0.set_texture(7, U"pictures/pump_down2_thunder.png");
			player1.set_texture(0, U"pictures/ghost_left1_thunder.png");
			player1.set_texture(1, U"pictures/ghost_left2_thunder.png");
			player1.set_texture(2, U"pictures/ghost_up1_thunder.png");
			player1.set_texture(3, U"pictures/ghost_up2_thunder.png");
			player1.set_texture(4, U"pictures/ghost_right1_thunder.png");
			player1.set_texture(5, U"pictures/ghost_right2_thunder.png");
			player1.set_texture(6, U"pictures/ghost_down1_thunder.png");
			player1.set_texture(7, U"pictures/ghost_down2_thunder.png");
		}
		if (getData().receive_data[e_communication::player3_button_down] && player3.get_special_item() == special_wing) {
			player3.set_special_item(in_use);
			player3.set_special_item_wing_timer(special_wing_tagger_effect_time);
			player3.set_frame_per_move(special_wing_tagger_speed);
			player3.set_texture(0, U"pictures/girl_left1_wing.png");
			player3.set_texture(1, U"pictures/girl_left2_wing.png");
			player3.set_texture(2, U"pictures/girl_up1_wing.png");
			player3.set_texture(3, U"pictures/girl_up2_wing.png");
			player3.set_texture(4, U"pictures/girl_right1_wing.png");
			player3.set_texture(5, U"pictures/girl_right2_wing.png");
			player3.set_texture(6, U"pictures/girl_down1_wing.png");
			player3.set_texture(7, U"pictures/girl_down2_wing.png");
		}
	}
	if (timer > start_time) {
		effect.clear();
	}
	if (timer == 0) {
		AudioAsset(U"main_theme").stop();
		AudioAsset(U"game_set").play();
		changeScene(e_scene::result);
	}
}

void server_game::draw_maze() const {
	for (auto i : step(maze_height)) {
		for (auto j : step(maze_width)) {
			if (maze_data[i][j]) {
				if (maze_data[i][j] == 1) {
//					Rect(Arg::center(maze_brock_position(i, j)), maze_brock_size).draw(Palette::Black);
				}
				else {
					maze_walls[maze_data[i][j]].draw(Arg::center(maze_brock_position(i, j)));
				}
			}
			else {
				if (i == 0 || i == maze_height - 1 || j == 0 || j == maze_width - 1)
					continue;//�}�b�v�ɂ͑��݂��Ȃ�
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
				else if (maze_data[i][j + 1]) {
					junction_r.draw(Arg::center(maze_brock_position(i, j)));
				}
				else {
					cross.draw(Arg::center(maze_brock_position(i, j)));
				}
			}
		}
	}
}

void server_game::draw()const {
	background.draw(Point(0, 0));
	draw_maze();
	draw_big_point_box(player0.get_score() + player1.get_score());
	draw_small_point_box(player2.get_score() + player3.get_score());
	//	left_item_circle.draw();
	//	right_item_circle.draw();
	if (timer > start_time) {
		countdown_clock_draw(timer-start_time);
		if (timer < start_time + 80) {
			player0.draw(timer);
			player1.draw(timer);
			player2.draw(timer);
			player3.draw(timer);
		}
		else {
			player0.draw_before_start(timer - start_time);
			player1.draw_before_start(timer - start_time);
		}
	}
	else {
		//�X�y�V�����A�C�e���֘A
		draw_timer(timer);
		if (player0.get_special_item() == special_thunder || player0.get_special_item_thunder_timer() != 0) {
			special_thunder_picture.scaled(4.0).drawAt(left_item_circle.center);
		}
		else if (player0.get_special_item() == special_wing || player0.get_special_item_wing_timer() != 0) {
			special_wing_picture.scaled(4.0).drawAt(left_item_circle.center);
		}
		if (player1.get_special_item() == special_thunder || player1.get_special_item_thunder_timer() != 0) {
			special_thunder_picture.scaled(4.0).drawAt(right_item_circle.center);
		}
		else if (player1.get_special_item() == special_wing || player1.get_special_item_wing_timer() != 0) {
			special_wing_picture.scaled(4.0).drawAt(right_item_circle.center);
		}
		left_special_item_timer_draw(player0.get_special_item_thunder_timer(), special_thunder_effect_time, Palette::Yellow);
		left_special_item_timer_draw(player0.get_special_item_wing_timer(), special_wing_ghost_effect_time, Palette::Aqua);
		right_special_item_timer_draw(player1.get_special_item_thunder_timer(), special_thunder_effect_time, Palette::Yellow);
		right_special_item_timer_draw(player1.get_special_item_wing_timer(), special_wing_ghost_effect_time, Palette::Aqua);
		if (player2.get_special_item_thunder_timer() != 0 || player3.get_special_item_thunder_timer() != 0) {
			//����Ɉꎞ��~���g��ꂽ�Ƃ�
			thunder_effect_draw();
		}
		for (auto i : array_items) {
			i.draw(true);
		}
		player0.draw(timer);
		player1.draw(timer);
		player2.draw(timer);
		player3.draw(timer);
		player2.draw_light();
		player3.draw_light();
		effect.update();
	}
}