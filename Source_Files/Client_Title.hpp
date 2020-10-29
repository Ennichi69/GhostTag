#pragma once
#include "Client_Common.hpp"

class client_title :public app::Scene {
public:
	client_title(const InitData& init);
	void update() override;
	void draw()const override;
private:
	Texture title_picture;
	bool player2_isready;
	bool player3_isready;
};