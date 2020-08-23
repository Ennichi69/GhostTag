#pragma once
#include "Client_Common.hpp"

class client_result :public app::Scene {
public:
	client_result(const InitData& init);
	void update() override;
	void draw()const override;
private:
};




const Rect player0_result_box = Rect(Arg::center(480, 270), 500, 200);
const Rect player1_result_box = Rect(Arg::center(480, 540), 500, 200);
const Rect player2_result_box = Rect(Arg::center(1440, 270), 500, 200);
const Rect player3_result_box = Rect(Arg::center(1440, 540), 500, 200);
const Rect ghost_result_box = Rect(Arg::center(480, 810), 500, 200);
const Rect tagger_result_box = Rect(Arg::center(480, 810), 500, 200);
