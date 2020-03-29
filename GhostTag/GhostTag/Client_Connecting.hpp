#pragma once
#include "Common.hpp"

class Client_Connecting : public App::Scene {
public:
	Client_Connecting(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Rect Rect_ReturnButton = Rect(1500, 900, 400, 100);
	Transition Transition_ReturnButton = Transition(4.0s, 2.0s);
};