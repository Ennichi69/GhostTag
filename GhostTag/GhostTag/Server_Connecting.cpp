#include "Server_Connecting.hpp"

Server_Connecting::Server_Connecting(const InitData& init) : IScene(init){
	getData().TCP_Server.startAccept(Port);
}

void Server_Connecting::update() {
	Transition_ReturnButton.update(Rect_ReturnButton.mouseOver());
	if (Rect_ReturnButton.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (Rect_ReturnButton.leftClicked()) {
		getData().TCP_Server.disconnect();
		changeScene(State::Init_Screen);
	}
	if (getData().TCP_Server.hasSession()) {
		changeScene(State::Server_Title);
	}
}

void Server_Connecting::draw() const {
	Rect_ReturnButton.draw(ColorF(1.0, Transition_ReturnButton.value())).drawFrame(5);
	FontAsset(U"PixelM+80")(U"Ç‡Ç«ÇÈ").drawAt(Rect_ReturnButton.center());
	FontAsset(U"PixelM+200")(U"í êMë“ã@íÜ...").drawAt(Scene::Center());
}