#pragma once
#include "Server_Common.hpp"

class server_title :public app::Scene {
public:
	server_title(const InitData& init);
	void update() override;
	void draw()const override;
private:
};