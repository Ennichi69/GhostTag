#include "Client_Error.hpp"

Client_Error::Client_Error(const InitData& init) : IScene(init) {
}

void Client_Error::update() {
	Transition_ReturnButton.update(Rect_ReturnButton.mouseOver());
	if (Rect_ReturnButton.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (Rect_ReturnButton.leftClicked()) {
		changeScene(State::Client_Connecting);
	}
}

void Client_Error::draw() const {
	Rect_ReturnButton.draw(ColorF(1.0, Transition_ReturnButton.value())).drawFrame(5); 
	FontAsset(U"PixelM+80")(U"���ǂ�").drawAt(Rect_ReturnButton.center());
	FontAsset(U"PixelM+200")(U"�ʐM�G���[���������܂���").drawAt(Scene::Center());
}