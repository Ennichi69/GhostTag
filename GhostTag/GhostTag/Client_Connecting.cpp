#include "Client_Connecting.hpp"

Client_Connecting::Client_Connecting(const InitData& init) : IScene(init){
	getData().TCP_Client.connect(getData().IP, Port);
}

void Client_Connecting::update() {
	Transition_ReturnButton.update(Rect_ReturnButton.mouseOver());
	if (Rect_ReturnButton.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (Rect_ReturnButton.leftClicked()) {
		getData().TCP_Client.disconnect();
		changeScene(State::Client_Setting);
	}
	if (getData().TCP_Client.isConnected()) {
		changeScene(State::Client_Title);
	}
}

void Client_Connecting::draw() const {
	Rect_ReturnButton.draw(ColorF(1.0, Transition_ReturnButton.value())).drawFrame(5);
	FontAsset(U"PixelM+80")(U"���ǂ�").drawAt(Rect_ReturnButton.center());
	FontAsset(U"PixelM+200")(U"�ʐM�ҋ@��...").drawAt(Scene::Center());
}