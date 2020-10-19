#include "Client_Game.hpp"

client_game::client_game(const InitData& init) :IScene(init) {
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

	//���ꂼ���special_item��������
	player0.set_special_item(nothing);
	player1.set_special_item(nothing);
	player2.set_special_item(nothing);
	player3.set_special_item(nothing);

	array_items.resize(array_point_items_size);

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

void client_game::update() {
	Array<uint8>serial_array;
	if (getData().serial_available) {
		serial_array = getData().serial.readBytes();
	}
	if (getData().tcp_client.hasError()) {
		//�ʐM�G���[�������A�G���[��ʂɑJ��
		getData().tcp_client.disconnect();
		changeScene(e_scene::error);
	}
	if (timer < start_time) {
		if (player0.get_special_item_thunder_timer() == 0 && player1.get_special_item_thunder_timer() == 0) {
			player2.update_direction(left_joystick_direction(serial_array, getData().serial_available, player2.get_direction()));
			player3.update_direction(right_joystick_direction(serial_array, getData().serial_available, player3.get_direction()));
			player2.update();
			player3.update();
		}
		//���O�␳
		if (player2.get_special_item_thunder_timer() == 0 && player3.get_special_item_thunder_timer() == 0) {
			player0.update();
			player1.update();
		}
	}
	if (timer == start_time)AudioAsset(U"main_theme").play();
	timer = getData().receive_data[e_communication::timer];
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
	getData().send_data[e_communication::player2_button_down] = left_button_down(serial_array,  getData().serial_available);
	getData().send_data[e_communication::player3_button_down] = right_button_down(serial_array,  getData().serial_available);

	for (auto i : step(array_point_items_size)) {
		getData().send_data[e_communication::point_item_status + i * 3] = array_items[i].get_pos().x;
		getData().send_data[e_communication::point_item_status + i * 3 + 1] = array_items[i].get_pos().y;
		getData().send_data[e_communication::point_item_status + i * 3 + 2] = array_items[i].get_type();
	}
	getData().tcp_client.send(getData().send_data);
	while (getData().tcp_client.read(getData().receive_data)) {
		player0.set_pos(Point(getData().receive_data[e_communication::player0_x], getData().receive_data[e_communication::player0_y]));
		player1.set_pos(Point(getData().receive_data[e_communication::player1_x], getData().receive_data[e_communication::player1_y]));
		player0.set_direction(e_direction(getData().receive_data[e_communication::player0_direction]));
		player1.set_direction(e_direction(getData().receive_data[e_communication::player1_direction]));
		player0.set_next_direction(e_direction(getData().receive_data[e_communication::player0_next_direction]));
		player1.set_next_direction(e_direction(getData().receive_data[e_communication::player1_next_direction]));
		//���_�Ǘ��͑S��server���Ȃ̂�
		player0.set_score(getData().receive_data[e_communication::player0_score]);
		player1.set_score(getData().receive_data[e_communication::player1_score]);
		player2.set_score(getData().receive_data[e_communication::player2_score]);
		player3.set_score(getData().receive_data[e_communication::player3_score]);
		for (auto i : step(array_point_items_size)) {
			if (array_items[i].get_pos() != Point(getData().receive_data[e_communication::point_item_status + i * 3], getData().receive_data[e_communication::point_item_status + i * 3 + 1])) {
				if (timer <= start_time) {
					if (array_items[i].get_type() == point1 || array_items[i].get_type() == point2 || array_items[i].get_type() == point3) {
						effect.add<item_effect>(array_items[i].get_pos(), Palette::Lime);
					}
					else {
						effect.add<item_effect>(array_items[i].get_pos(), Palette::Orange);
					}
				}
				array_items[i].set_pos(Point(getData().receive_data[e_communication::point_item_status + i * 3], getData().receive_data[e_communication::point_item_status + i * 3 + 1]));
				array_items[i].set_type((e_item_type)getData().receive_data[e_communication::point_item_status + i * 3 + 2], item_pictures);
			}
		}
		timer = getData().receive_data[e_communication::timer];
		if (getData().receive_data[e_communication::player2_status]==e_ghost_type::pumpkin) {
			effect.add<tag_effect>(player2.get_pos(), pumpkin_picture);
		}
		if (getData().receive_data[e_communication::player2_status] == e_ghost_type::ghost) {
			effect.add<tag_effect>(player2.get_pos(), ghost_picture);
		}
		if (getData().receive_data[e_communication::player3_status] == e_ghost_type::pumpkin) {
			effect.add<tag_effect>(player3.get_pos(), pumpkin_picture);
		}
		if (getData().receive_data[e_communication::player3_status]==e_ghost_type::ghost) {
			effect.add<tag_effect>(player3.get_pos(), ghost_picture);
		}
		player0.set_special_item((e_item_type)getData().receive_data[e_communication::player0_special_item]);
		player1.set_special_item((e_item_type)getData().receive_data[e_communication::player1_special_item]);
		player2.set_special_item((e_item_type)getData().receive_data[e_communication::player2_special_item]);
		player3.set_special_item((e_item_type)getData().receive_data[e_communication::player3_special_item]);
		if (player0.get_special_item_thunder_timer() == 0 && getData().receive_data[e_communication::player0_special_item_thunder_timer] != 0) {
			AudioAsset(U"thunder").stop();
			AudioAsset(U"thunder").play();
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
		if (player0.get_special_item_thunder_timer() != 0 && getData().receive_data[e_communication::player0_special_item_thunder_timer] == 0) {
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
		player0.set_special_item_thunder_timer(getData().receive_data[e_communication::player0_special_item_thunder_timer]);
		if (player1.get_special_item_thunder_timer() == 0 && getData().receive_data[e_communication::player1_special_item_thunder_timer] != 0) {
			AudioAsset(U"thunder").stop();
			AudioAsset(U"thunder").play();
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
		if (player1.get_special_item_thunder_timer() != 0 && getData().receive_data[e_communication::player1_special_item_thunder_timer] == 0) {
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
		player1.set_special_item_thunder_timer(getData().receive_data[e_communication::player1_special_item_thunder_timer]);
		if (player0.get_special_item_wing_timer() == 0 && getData().send_data[e_communication::player0_special_item_wing_timer] != 0) {
			player0.set_texture(0, U"pictures/pump_left1_wing.png");
			player0.set_texture(1, U"pictures/pump_left2_wing.png");
			player0.set_texture(2, U"pictures/pump_up1_wing.png");
			player0.set_texture(3, U"pictures/pump_up2_wing.png");
			player0.set_texture(4, U"pictures/pump_right1_wing.png");
			player0.set_texture(5, U"pictures/pump_right2_wing.png");
			player0.set_texture(6, U"pictures/pump_down1_wing.png");
			player0.set_texture(7, U"pictures/pump_down2_wing.png");
		}
		if (player0.get_special_item_wing_timer() != 0 && getData().send_data[e_communication::player0_special_item_wing_timer] == 0) {
			player0.set_texture(0, U"pictures/pump_left1.png");
			player0.set_texture(1, U"pictures/pump_left2.png");
			player0.set_texture(2, U"pictures/pump_up1.png");
			player0.set_texture(3, U"pictures/pump_up2.png");
			player0.set_texture(4, U"pictures/pump_right1.png");
			player0.set_texture(5, U"pictures/pump_right2.png");
			player0.set_texture(6, U"pictures/pump_down1.png");
			player0.set_texture(7, U"pictures/pump_down2.png");
		}
		player0.set_special_item_wing_timer(getData().receive_data[e_communication::player0_special_item_wing_timer]);
		if (player1.get_special_item_wing_timer() == 0 && getData().send_data[e_communication::player1_special_item_wing_timer] != 0) {
			player1.set_texture(0, U"pictures/ghost_left1_wing.png");
			player1.set_texture(1, U"pictures/ghost_left2_wing.png");
			player1.set_texture(2, U"pictures/ghost_up1_wing.png");
			player1.set_texture(3, U"pictures/ghost_up2_wing.png");
			player1.set_texture(4, U"pictures/ghost_right1_wing.png");
			player1.set_texture(5, U"pictures/ghost_right2_wing.png");
			player1.set_texture(6, U"pictures/ghost_down1_wing.png");
			player1.set_texture(7, U"pictures/ghost_down2_wing.png");
		}
		if (player1.get_special_item_wing_timer() != 0 && getData().send_data[e_communication::player1_special_item_wing_timer] == 0) {
			player1.set_texture(0, U"pictures/ghost_left1.png");
			player1.set_texture(1, U"pictures/ghost_left2.png");
			player1.set_texture(2, U"pictures/ghost_up1.png");
			player1.set_texture(3, U"pictures/ghost_up2.png");
			player1.set_texture(4, U"pictures/ghost_right1.png");
			player1.set_texture(5, U"pictures/ghost_right2.png");
			player1.set_texture(6, U"pictures/ghost_down1.png");
			player1.set_texture(7, U"pictures/ghost_down2.png");
		}
		player1.set_special_item_wing_timer(getData().receive_data[e_communication::player1_special_item_wing_timer]);
		player0.set_frame_per_move(getData().receive_data[e_communication::player0_speed]);
		player1.set_frame_per_move(getData().receive_data[e_communication::player1_speed]);
		if (player2.get_special_item_thunder_timer() == 0 && getData().receive_data[e_communication::player2_special_item_thunder_timer] != 0) {
			AudioAsset(U"thunder").stop();
			AudioAsset(U"thunder").play();
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
		if (player2.get_special_item_thunder_timer() != 0 && getData().receive_data[e_communication::player2_special_item_thunder_timer] == 0) {
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
		player2.set_special_item_thunder_timer(getData().receive_data[e_communication::player2_special_item_thunder_timer]);
		if (player3.get_special_item_thunder_timer() == 0 && getData().receive_data[e_communication::player3_special_item_thunder_timer] != 0) {
			AudioAsset(U"thunder").stop();
			AudioAsset(U"thunder").play();
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
		if (player3.get_special_item_thunder_timer() != 0 && getData().receive_data[e_communication::player3_special_item_thunder_timer] == 0) {
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
		player3.set_special_item_thunder_timer(getData().receive_data[e_communication::player3_special_item_thunder_timer]);
		if (player2.get_special_item_wing_timer() == 0 && getData().receive_data[e_communication::player2_special_item_wing_timer] != 0) {
			AudioAsset(U"wing").stop();
			AudioAsset(U"wing").play();
			player2.set_texture(0, U"pictures/boy_left1_wing.png");
			player2.set_texture(1, U"pictures/boy_left2_wing.png");
			player2.set_texture(2, U"pictures/boy_up1_wing.png");
			player2.set_texture(3, U"pictures/boy_up2_wing.png");
			player2.set_texture(4, U"pictures/boy_right1_wing.png");
			player2.set_texture(5, U"pictures/boy_right2_wing.png");
			player2.set_texture(6, U"pictures/boy_down1_wing.png");
			player2.set_texture(7, U"pictures/boy_down2_wing.png");
		}
		if (player2.get_special_item_wing_timer() != 0 && getData().receive_data[e_communication::player2_special_item_wing_timer] == 0) {
			player2.set_texture(0, U"pictures/boy_left1.png");
			player2.set_texture(1, U"pictures/boy_left2.png");
			player2.set_texture(2, U"pictures/boy_up1.png");
			player2.set_texture(3, U"pictures/boy_up2.png");
			player2.set_texture(4, U"pictures/boy_right1.png");
			player2.set_texture(5, U"pictures/boy_right2.png");
			player2.set_texture(6, U"pictures/boy_down1.png");
			player2.set_texture(7, U"pictures/boy_down2.png");
		}
		player2.set_special_item_wing_timer(getData().receive_data[e_communication::player2_special_item_wing_timer]);
		if (player3.get_special_item_wing_timer() == 0 && getData().receive_data[e_communication::player3_special_item_wing_timer] != 0) {
			AudioAsset(U"wing").stop();
			AudioAsset(U"wing").play();
			player3.set_texture(0, U"pictures/girl_left1_wing.png");
			player3.set_texture(1, U"pictures/girl_left2_wing.png");
			player3.set_texture(2, U"pictures/girl_up1_wing.png");
			player3.set_texture(3, U"pictures/girl_up2_wing.png");
			player3.set_texture(4, U"pictures/girl_right1_wing.png");
			player3.set_texture(5, U"pictures/girl_right2_wing.png");
			player3.set_texture(6, U"pictures/girl_down1_wing.png");
			player3.set_texture(7, U"pictures/girl_down2_wing.png");
		}
		if (player3.get_special_item_wing_timer() != 0 && getData().receive_data[e_communication::player3_special_item_wing_timer] == 0) {
			player3.set_texture(0, U"pictures/girl_left1.png");
			player3.set_texture(1, U"pictures/girl_left2.png");
			player3.set_texture(2, U"pictures/girl_up1.png");
			player3.set_texture(3, U"pictures/girl_up2.png");
			player3.set_texture(4, U"pictures/girl_right1.png");
			player3.set_texture(5, U"pictures/girl_right2.png");
			player3.set_texture(6, U"pictures/girl_down1.png");
			player3.set_texture(7, U"pictures/girl_down2.png");
		}
		player3.set_special_item_wing_timer(getData().receive_data[e_communication::player3_special_item_wing_timer]);
		player2.set_frame_per_move(getData().receive_data[e_communication::player2_speed]);
		player3.set_frame_per_move(getData().receive_data[e_communication::player3_speed]);
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

void client_game::draw_maze() const {
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

void client_game::draw()const {
	background.draw(Point(0, 0));
	draw_maze();
	draw_big_point_box(player2.get_score() + player3.get_score());
	draw_small_point_box(player0.get_score() + player1.get_score());
	//	left_item_circle.draw();
	//	right_item_circle.draw();
	if (timer > start_time) {
		countdown_clock_draw(timer - start_time);
		if (timer < start_time + 180) {
			player2.draw(timer);
			player3.draw(timer);
		}
	}
	else {
		draw_timer(timer);
		if (player2.get_special_item() == special_thunder || player2.get_special_item_thunder_timer() != 0) {
			special_thunder_picture.scaled(2.0).drawAt(left_item_circle.center);
		}
		else if (player2.get_special_item() == special_wing || player2.get_special_item_wing_timer() != 0) {
			special_wing_picture.scaled(2.0).drawAt(left_item_circle.center);
		}
		if (player3.get_special_item() == special_thunder || player3.get_special_item_thunder_timer() != 0) {
			special_thunder_picture.scaled(2.0).drawAt(right_item_circle.center);
		}
		else if (player3.get_special_item() == special_wing || player3.get_special_item_wing_timer() != 0) {
			special_wing_picture.scaled(2.0).drawAt(right_item_circle.center);
		}
		left_special_item_timer_draw(player2.get_special_item_thunder_timer(), special_thunder_effect_time, Palette::Yellow);
		left_special_item_timer_draw(player2.get_special_item_wing_timer(), special_wing_tagger_effect_time, Palette::Aqua);
		right_special_item_timer_draw(player3.get_special_item_thunder_timer(), special_thunder_effect_time, Palette::Yellow);
		right_special_item_timer_draw(player3.get_special_item_wing_timer(), special_wing_tagger_effect_time, Palette::Aqua);
		if (player0.get_special_item_thunder_timer() != 0 || player1.get_special_item_thunder_timer() != 0) {
			//����Ɉꎞ��~���g��ꂽ�Ƃ�
			thunder_effect_draw();
		}
		for (auto i : array_items) {
			i.draw();
		}
		player2.draw(timer);
		player3.draw(timer);
		if (player2.get_special_item_thunder_timer() != 0 || player3.get_special_item_thunder_timer() != 0) {
			player0.draw(timer);
			player1.draw(timer);
		}
		else {
			player0.draw_range(player2.rect_ghost_visible(), timer);
			player0.draw_range(player3.rect_ghost_visible(), timer);
			player1.draw_range(player2.rect_ghost_visible(), timer);
			player1.draw_range(player3.rect_ghost_visible(), timer);
		}
		player2.draw_light();
		player3.draw_light();
		effect.update();
	}
}