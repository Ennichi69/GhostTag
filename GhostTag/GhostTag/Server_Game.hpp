#pragma once
#include "Common.hpp"

class Server_Game : public App::Scene {
public:
	Server_Game(const InitData& init);
	void update() override;
	void draw() const override;
private:
};