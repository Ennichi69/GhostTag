#include "Client_Error.hpp"

client_error::client_error(const InitData& init) :IScene(init) {
}

void client_error::update() {
	transition_return_button.update(rect_return_button.mouseOver());
	if (rect_return_button.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (rect_return_button.leftClicked()) {
		//�����u���ǂ�v�{�^���������ꂽ��
		changeScene(e_scene::initial_setting);
	}
}

void client_error::draw()const {
	FontAsset(U"Mplus_100")(U"�ʐM�G���[���������܂���").drawAt(Scene::Center());
	rect_return_button.draw(ColorF(1.0, transition_return_button.value())).drawFrame(5);
	FontAsset(U"Mplus_80")(U"���ǂ�").drawAt(rect_return_button.center());
}