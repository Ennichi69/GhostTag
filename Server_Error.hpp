#pragma once
#include "Server_Common.hpp"

class server_error :public app::Scene {
public:
	server_error(const InitData& init);
	void update() override;
	void draw()const override;
private:
	Rect rect_return_button = Rect(1500, 900, 400, 100);
	Transition transition_return_button = Transition(4.0s, 2.0s);
};