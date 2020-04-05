#pragma once
#include "Server_Common.hpp"

class Server_GameOver :public App::Scene {
public:
	Server_GameOver(const InitData& init);
	void update()override;
	void draw()const override;
private:
};