#pragma once
#include "Common.hpp"

class Init_Screen : public App::Scene {
public:
	Init_Screen(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Rect Rect_ClientButton = Rect(Arg::center = Scene::Center().movedBy(0, 200), 700, 150);
	Transition Transition_ClientButton = Transition(4.0s, 2.0s);
	Rect Rect_ServerButton = Rect(Arg::center = Scene::Center().movedBy(0, -200), 700, 150);
	Transition Transition_ServerButton = Transition(4.0s, 2.0s);
};