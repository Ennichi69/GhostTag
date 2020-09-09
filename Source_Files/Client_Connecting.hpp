#pragma once
#include "Client_Common.hpp"

class client_connecting : public app::Scene {
	//�ʐM�ҋ@�����
public:
	client_connecting(const InitData& init);
	void update() override;
	void draw()const override;
private:
	Rect rect_return_button = Rect(1500, 900, 400, 100);
	Transition transition_return_button = Transition(4.0s, 2.0s);
};