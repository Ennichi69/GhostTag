#pragma once
#include "Client_Common.hpp"

class Client_Error : public App::Scene {
public:
	Client_Error(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Rect Rect_ExitButton = Rect(1500, 900, 400, 100);
	Transition Transition_ExitButton = Transition(4.0s, 2.0s);
};