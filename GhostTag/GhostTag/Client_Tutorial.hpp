#pragma once
#include "Common.hpp"

class Client_Tutorial: public App::Scene {
public:
	Client_Tutorial(const InitData& init);
	void update() override;
	void draw() const override;
private:
	bool Player0_IsReady = false;
	bool Player1_IsReady = false;
};