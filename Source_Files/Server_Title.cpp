#include "Server_Title.hpp"

server_title::server_title(const InitData& init) :IScene(init) {
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
}

void server_title::update() {
	if (!getData().tcp_server.hasSession()) {
		//通信エラー発生時、エラー画面に遷移
		getData().tcp_server.disconnect();
		changeScene(e_scene::error);
	}
	getData().tcp_server.send(getData().send_data);
	while (getData().tcp_server.read(getData().receive_data));
	if (KeyEnter.down()) {
		//Enterキーが押されたとき、ゲーム画面に移行 タイトルからの遷移方法は要検討
		changeScene(e_scene::game);
	}
}

void server_title::draw()const {
	title_picture.draw();
	FontAsset(U"font40")(U"Server").draw(Point(0, 0));
}