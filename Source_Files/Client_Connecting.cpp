#include "Client_Connecting.hpp"

client_connecting::client_connecting(const InitData& init) :IScene(init) {
	getData().tcp_client.connect(getData().ipv4, port);//通信待機中画面に遷移した瞬間、通信開始
}

void client_connecting::update() {
	transition_return_button.update(rect_return_button.mouseOver());
	if (rect_return_button.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (rect_return_button.leftClicked()) {
		//もし「もどる」ボタンが押されたら
		getData().tcp_client.disconnect();//通信を切断
		changeScene(e_scene::initial_setting);
	}
	if (getData().tcp_client.isConnected()) {
		//もし接続したら
		changeScene(e_scene::title);//タイトル画面へ
	}
}

void client_connecting::draw() const {
	rect_return_button.draw(ColorF(1.0, transition_return_button.value())).drawFrame(5);
	FontAsset(U"Mplus_80")(U"もどる").drawAt(rect_return_button.center());
	FontAsset(U"Mplus_200")(U"通信待機中...").drawAt(Scene::Center());
}