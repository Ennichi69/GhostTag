#include "Server_Title.hpp"

server_title::server_title(const InitData& init) :IScene(init) {
	//�^�C�g����ʂɈړ������� �S�Ă̒ʐM�Ɋւ��f�[�^��������
	for (auto i : step(communication_data_size)) {
		getData().send_data[i] = 0;
	}
	for (auto i : step(communication_data_size)) {
		getData().receive_data[i] = 0;
	}
	getData().send_data[e_communication::scene_status] = e_scene::title;

	//�^�C�g����ʂ̉摜��ݒ�
	title_picture = Texture(Resource(U"pictures/title.png"));
	timer = 180;
	player0_isready = false;
	player1_isready = false;
	Array<uint8>serial_array;
	if (getData().serial_available) {
		serial_array = getData().serial.readBytes();
	}
}

void server_title::update() {
	Array<uint8>serial_array;
	if (getData().serial_available) {
		serial_array = getData().serial.readBytes();
	}
	if (!getData().tcp_server.hasSession()) {
		//�ʐM�G���[�������A�G���[��ʂɑJ��
		getData().tcp_server.disconnect();
		changeScene(e_scene::error);
	}
	getData().tcp_server.send(getData().send_data);
	while (getData().tcp_server.read(getData().receive_data));
	if (timer != 0) {
		timer--;
	}
	else {
		if (left_button_down(serial_array, getData().serial_available)) {
			player0_isready = true;
		}
		if (right_button_down(serial_array, getData().serial_available)) {
			player1_isready = true;
		}
		getData().send_data[e_communication::player0_isready] = player0_isready;
		getData().send_data[e_communication::player1_isready] = player1_isready;
		if ((player0_isready&&player1_isready&&getData().receive_data[e_communication::player2_isready]&&getData().receive_data[e_communication::player3_isready])||KeyEnter.down()) {
			//Enter�L�[�������ꂽ�Ƃ��A�y�ёS�Ă̓���{�^���������ꂽ�Ƃ� �Q�[����ʂֈڍs
			changeScene(e_scene::game);
		}
	}
}

void server_title::draw()const {
	title_picture.draw();
	FontAsset(U"font40")(U"Ghost").draw(Point(0, 0));
	if (player0_isready) {
		FontAsset(U"font40")(U"Player3 Ready").drawAt(400, 1040);
	}
	if (player1_isready) {
		FontAsset(U"font40")(U"Player4 Ready").drawAt(1920 - 400, 1040);
	}
}