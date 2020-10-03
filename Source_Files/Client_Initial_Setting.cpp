#include "Client_Initial_Setting.hpp"

client_initial_setting::client_initial_setting(const InitData& init) :IScene(init) {
	for (auto i : step(4)) {
		rect_textbox[i]= Rect(Arg::center = Scene::Center().movedBy(i * 400 - 600, 0), 350, 100);//各テキストボックスの位置を決める
		text[i] = U"XXX";///テキストを"XXX"で初期化
	}
}

void client_initial_setting::update() {
	transition_ok_button.update(rect_ok_button.mouseOver());
	if (rect_ok_button.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (rect_ok_button.leftClicked() || KeyEnter.down()) {
		getData().ipv4= IPv4(ParseOr<int>(text[0], 127), ParseOr<int>(text[1], 0), ParseOr<int>(text[2], 0), ParseOr<int>(text[3], 1));//初期値"XXX"のままでOKボタンを押すとlocalhostになる
		changeScene(e_scene::connecting);
	}
	if (KeyBackspace.down()) {
		if (!text[input_textbox_number].empty()) {
			text[input_textbox_number].pop_back();
		}
	}
	if (KeyRight.down() || KeyTab.down()) {
		input_textbox_number++;
		input_textbox_number %= 4;
	}
	if (KeyLeft.down()) {
		input_textbox_number += 3;
		input_textbox_number %= 4;
	}
	if (Key0.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('0');
	}
	if (Key1.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('1');
	}
	if (Key2.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('2');
	}
	if (Key3.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('3');
	}
	if (Key4.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('4');
	}
	if (Key5.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('5');
	}
	if (Key6.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('6');
	}
	if (Key7.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('7');
	}
	if (Key8.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('8');
	}
	if (Key9.down()) {
		if (text[input_textbox_number] == U"XXX")text[input_textbox_number].clear();
		text[input_textbox_number].push_back('9');
	}
}

void client_initial_setting::draw()const {
	rect_ok_button.draw(ColorF(1.0, transition_ok_button.value())).drawFrame(5);
	FontAsset(U"Mplus_100")(U"OK").drawAt(rect_ok_button.center());
	for (auto i : step(4)) {
		if (input_textbox_number == i) {
			rect_textbox[i].draw();
		}
		else {
			rect_textbox[i].draw(ColorF(1.0, 0.8));
		}
		FontAsset(U"Mplus_100")(text[i]).drawAt(rect_textbox[i].center(), Palette::Black);
	}
}