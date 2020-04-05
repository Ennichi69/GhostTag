#pragma once
#include "Client_Common.hpp"

class Client_GameOver : public App::Scene {
public:
	Client_GameOver(const InitData& init);
	void update() override;
	void draw() const override;
private:
};