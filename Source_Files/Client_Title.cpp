#include "Client_Title.hpp"

client_title::client_title(const InitData& init) :IScene(init) {
	//タイトル画面に移動したら 全ての通信に関わるデータを初期化
	for (auto i : step(communication_data_size)) {
		getData().send_data[i] = 0;
	}
	for (auto i : step(communication_data_size)) {
		getData().receive_data[i] = 0;
	}
	getData().send_data[e_communication::scene_status] = e_scene::title;

	//タイトル画面の画像を設定
	title_picture = Texture(Resource(U"pictures/title.png"));
	Array<uint8>serial_array;
	if (getData().serial_available) {
		serial_array = getData().serial.readBytes();
	}
}

void client_title::update() {
	Array<uint8>serial_array;
	if (getData().serial_available) {
		serial_array = getData().serial.readBytes();
	}
	if (getData().tcp_client.hasError()) {
		//通信エラー発生時、エラー画面に遷移
		getData().tcp_client.disconnect();
		changeScene(e_scene::error);
	}
	getData().tcp_client.send(getData().send_data);
	while (getData().tcp_client.read(getData().receive_data));
	if (left_button_down(serial_array, getData().serial_available)) {
		player2_isready = true;
	}
	if (right_button_down(serial_array, getData().serial_available)) {
		player3_isready = true;
	}
	getData().send_data[e_communication::player2_isready] = player2_isready;
	getData().send_data[e_communication::player3_isready] = player3_isready;
	if (getData().receive_data[e_communication::scene_status] == e_scene::game) {
		//Server側の状態が変わったとき、ゲーム画面に遷移
		changeScene(e_scene::game);
	}
}

void client_title::draw()const {
	title_picture.draw();
	FontAsset(U"font40")(U"Human").draw(Point(0, 0));
	if (player2_isready) {
		FontAsset(U"font40")(U"Player1 Ready").drawAt(400, 1040);
	}
	if (player3_isready) {
		FontAsset(U"font40")(U"Player2 Ready").drawAt(1920 - 400, 1040);
	}
}