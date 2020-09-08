#pragma once
#include "Server_Common.hpp"

class server_connecting : public app::Scene {
	//’ÊM‘Ò‹@’†‰æ–Ê
public:
	server_connecting(const InitData& init);
	void update() override;
	void draw()const override;
private:
};