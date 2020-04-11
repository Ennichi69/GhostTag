#include "Server_Error.hpp"

Server_Error::Server_Error(const InitData& init) : IScene(init) {
}

void Server_Error::update() {
	Transition_ExitButton.update(Rect_ExitButton.mouseOver());
	if (Rect_ExitButton.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (Rect_ExitButton.leftClicked()) {
		System::Exit();
	}
}

void Server_Error::draw() const {
	Rect_ExitButton.draw(ColorF(1.0, Transition_ExitButton.value())).drawFrame(5);
	FontAsset(U"PixelM+80")(U"Ç®ÇÌÇÈ").drawAt(Rect_ExitButton.center());
	FontAsset(U"PixelM+100")(U"í êMÉGÉâÅ[Ç™î≠ê∂ÇµÇ‹ÇµÇΩ").drawAt(Scene::Center());
}