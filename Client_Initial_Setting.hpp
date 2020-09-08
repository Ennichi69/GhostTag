#pragma once
#include "Client_Common.hpp"

class client_initial_setting :public app::Scene {
public:
	client_initial_setting(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Rect rect_ok_button = Rect(Arg::center = Scene::Center().movedBy(0, 200), 500, 100);//OKボタン
	Rect rect_textbox[4];//入力用テキストボックス
	String text[4];//それぞれのテキストボックスに何が書かれているか
	Transition transition_ok_button = Transition(4.0s, 2.0s);//OKボタンアニメーション用
	uint16 input_textbox_number = 0;//現在入力中のテキストボックスの番号
};