#pragma once
#include "Client_Common.hpp"

class Client_Game : public App::Scene {
public:
	Client_Game(const InitData& init);
	void update() override;
	void draw() const override;
private:
};