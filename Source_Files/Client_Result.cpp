#include "Client_Result.hpp"

client_result::client_result(const InitData& init) :IScene(init) {
	getData().send_data[e_communication::scene_status] = e_scene::result;
}

void client_result::update() {
	if (getData().tcp_client.hasError()) {
		//通信エラー発生時、エラー画面に遷移
		getData().tcp_client.disconnect();
		changeScene(e_scene::error);
	}
	getData().tcp_client.send(getData().send_data);
	while (getData().tcp_client.read(getData().receive_data));

}

void client_result::draw()const {
}