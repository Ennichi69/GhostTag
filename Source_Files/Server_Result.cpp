#include "Server_Result.hpp"

server_result::server_result(const InitData& init) :IScene(init) {
	getData().send_data[e_communication::scene_status] = e_scene::result;
}

void server_result::update() {
	if (!getData().tcp_server.hasSession()) {
		//通信エラー発生時、エラー画面に遷移
		getData().tcp_server.disconnect();
		changeScene(e_scene::error);
	}
	getData().tcp_server.send(getData().send_data);
	while (getData().tcp_server.read(getData().receive_data));

}

void server_result::draw()const {
}