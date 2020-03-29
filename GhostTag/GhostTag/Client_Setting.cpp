#include "Client_Setting.hpp"

Client_Setting::Client_Setting(const InitData& init) : IScene(init) {
	for (int i = 0; i < 4; i++) {
		Rect_TextBox[i] = Rect(Arg::center = Scene::Center().movedBy(i * 400 - 600, 0), 350, 100);
		Text[i] = U"XXX";
	}
}

void Client_Setting::update() {
	Transition_ReturnButton.update(Rect_ReturnButton.mouseOver());
	Transition_OKButton.update(Rect_OKButton.mouseOver());
	if (Rect_ReturnButton.mouseOver() || Rect_OKButton.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (Rect_ReturnButton.leftClicked()) {
		changeScene(State::Init_Screen);
	}
	if (Rect_OKButton.leftClicked()||KeyEnter.down()) {
		getData().IP = IPv4(ParseOr<int>(Text[0],127),ParseOr<int>(Text[1],0),ParseOr<int>(Text[2],0),ParseOr<int>(Text[3],1));
		changeScene(State::Client_Connecting);
	}
	if (KeyBackspace.down()) {
		if (!Text[InputTextBoxNumber].empty()) {
			Text[InputTextBoxNumber].pop_back();
		}
	}
	if (KeyRight.down()||KeyTab.down()) {
		InputTextBoxNumber++;
		InputTextBoxNumber %= 4;
	}
	if (KeyLeft.down()) {
		InputTextBoxNumber += 3;
		InputTextBoxNumber %= 4;
	}
	if (Key0.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('0');
	}
	if (Key1.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('1');
	}
	if (Key2.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('2');
	}
	if (Key3.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('3');
	}
	if (Key4.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('4');
	}
	if (Key5.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('5');
	}
	if (Key6.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('6');
	}
	if (Key7.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('7');
	}
	if (Key8.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('8');
	}
	if (Key9.down()) {
		if (Text[InputTextBoxNumber] == U"XXX")Text[InputTextBoxNumber].clear();
		Text[InputTextBoxNumber].push_back('9');
	}
}

void Client_Setting::draw()const {
	Rect_ReturnButton.draw(ColorF(1.0, Transition_ReturnButton.value())).drawFrame(5);
	Rect_OKButton.draw(ColorF(1.0, Transition_OKButton.value())).drawFrame(5);
	FontAsset(U"PixelM+80")(U"‚à‚Ç‚é").drawAt(Rect_ReturnButton.center());
	FontAsset(U"PixelM+100")(U"OK").drawAt(Rect_OKButton.center());
	for (int i = 0; i < 4; i++) {
		if (InputTextBoxNumber == i) {
			Rect_TextBox[i].draw();
		}
		else {
			Rect_TextBox[i].draw(ColorF(1.0, 0.8));
		}
		FontAsset(U"PixelM+100")(Text[i]).drawAt(Rect_TextBox[i].center(),Palette::Black);
	}
}