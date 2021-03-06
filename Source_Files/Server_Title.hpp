#pragma once
#include "Server_Common.hpp"

class server_title :public app::Scene {
public:
	server_title(const InitData& init);
	void update() override;
	void draw()const override;
private:
	Texture title_picture;
	uint16 timer;//timerが0でない限り遷移させない
	bool player0_isready;
	bool player1_isready;
};