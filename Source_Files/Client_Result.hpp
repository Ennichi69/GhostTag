#pragma once
#include "Client_Common.hpp"

class client_result :public app::Scene {
public:
	client_result(const InitData& init);
	void update() override;
	void draw()const override;
private:
};