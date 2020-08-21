#include "Server_Connecting.hpp"

server_connecting::server_connecting(const InitData& init) :IScene(init) {
	getData().tcp_server.startAccept(port);//通信待機中画面に遷移した瞬間、通信開始
}

void server_connecting::update() {
	if (getData().tcp_server.hasSession()) {
		//もし接続したら
		changeScene(e_scene::title);//タイトル画面へ
	}
}

void server_connecting::draw() const {
	FontAsset(U"font200")(U"通信待機中...").drawAt(Scene::Center());
}