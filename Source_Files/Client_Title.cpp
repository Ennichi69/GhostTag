#include "Client_Title.hpp"

client_title::client_title(const InitData& init) :IScene(init) {
	//�^�C�g����ʂɈړ������� �S�Ă̒ʐM�Ɋւ��f�[�^��������
	for (auto i : step(communication_data_size)) {
		getData().send_data[i] = 0;
	}
	for (auto i : step(communication_data_size)) {
		getData().receive_data[i] = 0;
	}
	getData().send_data[e_communication::scene_status] = e_scene::title;
}

void client_title::update() {
	if (getData().tcp_client.hasError()) {
		//�ʐM�G���[�������A�G���[��ʂɑJ��
		getData().tcp_client.disconnect();
		changeScene(e_scene::error);
	}
	getData().tcp_client.send(getData().send_data);
	while (getData().tcp_client.read(getData().receive_data));
	if (getData().receive_data[e_communication::scene_status] == e_scene::game) {
		//Server���̏�Ԃ��ς�����Ƃ��A�Q�[����ʂɑJ��
		changeScene(e_scene::game);
	}
}

void client_title::draw()const {
	FontAsset(U"font100")(U"�^�C�g�����\nServer����Enter�L�[�������Ă�������").drawAt(Scene::Center());
}