#pragma once
#include "Server_Common.hpp"

class server_result :public app::Scene {
public:
	server_result(const InitData& init);
	void update() override;
	void draw()const override;
private:
};