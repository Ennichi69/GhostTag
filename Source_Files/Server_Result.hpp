#pragma once
#include "Server_Common.hpp"

class server_result :public app::Scene {
public:
	server_result(const InitData& init);
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
