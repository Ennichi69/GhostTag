#pragma once
#include "Common.hpp"

class Client_Setting : public App::Scene {
public:
	Client_Setting(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Rect Rect_ReturnButton = Rect(1500, 900, 400, 100);
	Rect Rect_OKButton = Rect(Arg::center = Scene::Center().movedBy(0, 200), 500, 100);
	Rect Rect_TextBox[4];
	String Text[4];
	Transition Transition_ReturnButton = Transition(4.0s, 2.0s);
	Transition Transition_OKButton = Transition(4.0s, 2.0s);
	int InputTextBoxNumber = 0;
};