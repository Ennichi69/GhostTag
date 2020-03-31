#pragma once
#include "Common.hpp"

class Client_Title : public App::Scene {
public:
	Client_Title(const InitData& init);
	void update() override;
	void draw() const override;
private:
	bool Player0_IsReady = false;
	bool Player1_IsReady = false;
};