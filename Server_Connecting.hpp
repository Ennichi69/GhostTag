#pragma once
#include "Server_Common.hpp"

class server_connecting : public app::Scene {
	//通信待機中画面
public:
	server_connecting(const InitData& init);
	void update() override;
	void draw()const override;
private:
};