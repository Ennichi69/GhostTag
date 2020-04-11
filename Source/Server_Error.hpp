#pragma once
#include "Server_Common.hpp"

class Server_Error : public App::Scene {
public:
	Server_Error(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Rect Rect_ExitButton = Rect(1500, 900, 400, 100);
	Transition Transition_ExitButton = Transition(4.0s, 2.0s);
};