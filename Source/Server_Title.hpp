#pragma once
#include "Server_Common.hpp"

class Server_Title : public App::Scene {
public:
	Server_Title(const InitData& init);
	void update() override;
	void draw() const override;
private:
	bool Player0_IsReady = false;
	bool Player1_IsReady = false;
};