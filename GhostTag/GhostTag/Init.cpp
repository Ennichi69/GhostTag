#include "Init.hpp"

Init_Screen::Init_Screen(const InitData& init) : IScene(init) {
}

void Init_Screen::update() {
	Transition_ClientButton.update(Rect_ClientButton.mouseOver());
	Transition_ServerButton.update(Rect_ServerButton.mouseOver());
	if (Rect_ClientButton.mouseOver() || Rect_ServerButton.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (Rect_ClientButton.leftClicked()) {
		changeScene(State::Client_Setting);
	}
	if (Rect_ServerButton.leftClicked()) {
		changeScene(State::Server_Connecting);
	}
}

void Init_Screen::draw()const{
	Rect_ClientButton.draw(ColorF(1.0, Transition_ClientButton.value())).drawFrame(5);
	Rect_ServerButton.draw(ColorF(1.0, Transition_ServerButton.value())).drawFrame(5);
	FontAsset(U"PixelM+100")(U"Client").drawAt(Rect_ClientButton.center());
	FontAsset(U"PixelM+100")(U"Server").drawAt(Rect_ServerButton.center());
}
