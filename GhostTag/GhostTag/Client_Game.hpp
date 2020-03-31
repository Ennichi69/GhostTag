#pragma once
#include "Common.hpp"

class Client_Game : public App::Scene {
public:
	Client_Game(const InitData& init);
	void update() override;
	void draw() const override;
private:
};