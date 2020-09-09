#include "Client_Error.hpp"

client_error::client_error(const InitData& init) :IScene(init) {
}

void client_error::update() {
	transition_return_button.update(rect_return_button.mouseOver());
	if (rect_return_button.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (rect_return_button.leftClicked()) {
		//もし「もどる」ボタンが押されたら
		changeScene(e_scene::initial_setting);
	}
}

void client_error::draw()const {
	FontAsset(U"font100")(U"通信エラーが発生しました").drawAt(Scene::Center());
	rect_return_button.draw(ColorF(1.0, transition_return_button.value())).drawFrame(5);
	FontAsset(U"font80")(U"もどる").drawAt(rect_return_button.center());
}