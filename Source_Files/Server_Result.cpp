#include "Server_Result.hpp"

server_result::server_result(const InitData& init) :IScene(init) {
	getData().send_data[e_communication::scene_status] = e_scene::result;
	player0_score = getData().receive_data[e_communication::player0_score];
	player1_score = getData().receive_data[e_communication::player1_score];
	player2_score = getData().receive_data[e_communication::player2_score];
	player3_score = getData().receive_data[e_communication::player3_score];
	result_picture = Texture(Resource(U"pictures/result.png"));
}

void server_result::update() {
	if (!getData().tcp_server.hasSession()) {
		//通信エラー発生時、エラー画面に遷移
		getData().tcp_server.disconnect();
		changeScene(e_scene::error);
	}
	getData().tcp_server.send(getData().send_data);
	while (getData().tcp_server.read(getData().receive_data));
	if (KeyEnter.down()) {
		changeScene(e_scene::title);
	}
}

void server_result::draw()const {
	result_picture.draw();
	FontAsset(U"font60")(U"{:0>4}pt"_fmt(player0_score)).drawAt(Point(670, 370));
	FontAsset(U"font60")(U"{:0>4}pt"_fmt(player1_score)).drawAt(Point(670, 490));
	FontAsset(U"font80")(U"{:0>4}pt"_fmt(player0_score + player1_score)).drawAt(Point(670, 720));
	FontAsset(U"font60")(U"{:0>4}pt"_fmt(player2_score)).drawAt(Point(1525, 370));
	FontAsset(U"font60")(U"{:0>4}pt"_fmt(player3_score)).drawAt(Point(1525, 490));
	FontAsset(U"font80")(U"{:0>4}pt"_fmt(player2_score + player3_score)).drawAt(Point(1525, 720));
	/*
	player0_result_box.drawFrame(5);
	player1_result_box.drawFrame(5);
	player2_result_box.drawFrame(5);
	player3_result_box.drawFrame(5);
	ghost_result_box.drawFrame(5);
	tagger_result_box.drawFrame(5);
	FontAsset(U"font40")(U"Player0:{:0>4}pt"_fmt(player0_score)).drawAt(player0_result_box.center());
	FontAsset(U"font40")(U"Player1:{:0>4}pt"_fmt(player1_score)).drawAt(player1_result_box.center());
	FontAsset(U"font40")(U"Player2:{:0>4}pt"_fmt(player2_score)).drawAt(player2_result_box.center());
	FontAsset(U"font40")(U"Player3:{:0>4}pt"_fmt(player3_score)).drawAt(player3_result_box.center());
	FontAsset(U"font40")(U"おばけ:{:0>4}pt"_fmt(player0_score + player1_score)).drawAt(ghost_result_box.center());
	FontAsset(U"font40")(U"ひと:{:0>4}pt"_fmt(player2_score + player3_score)).drawAt(tagger_result_box.center());
	*/
}