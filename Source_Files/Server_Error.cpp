#include "Server_Error.hpp"

server_error::server_error(const InitData& init) :IScene(init) {
}

void server_error::update() {
	transition_return_button.update(rect_return_button.mouseOver());
	if (rect_return_button.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (rect_return_button.leftClicked()) {
		//もし「もどる」ボタンが押されたら
		changeScene(e_scene::connecting);
	}
}

void server_error::draw()const {
	FontAsset(U"Mplus_100")(U"通信エラーが発生しました").drawAt(Scene::Center());
	rect_return_button.draw(ColorF(1.0, transition_return_button.value())).drawFrame(5);
	FontAsset(U"Mplus_80")(U"もどる").drawAt(rect_return_button.center());
}