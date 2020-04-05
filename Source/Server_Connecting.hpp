#pragma once
#include "Server_Common.hpp"

class Server_Connecting : public App::Scene {
public:
	Server_Connecting(const InitData& init);
	void update() override;
	void draw() const override;
private:
};