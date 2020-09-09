#include "Server_Title.hpp"

server_title::server_title(const InitData& init) :IScene(init) {
	//�^�C�g����ʂɈړ������� �S�Ă̒ʐM�Ɋւ��f�[�^��������
	for (auto i : step(communication_data_size)) {
		getData().send_data[i] = 0;
	}
	for (auto i : step(communication_data_size)) {
		getData().receive_data[i] = 0;
	}
	getData().send_data[e_communication::scene_status] = e_scene::title;
}

void server_title::update() {
	if (!getData().tcp_server.hasSession()) {
		//�ʐM�G���[�������A�G���[��ʂɑJ��
		getData().tcp_server.disconnect();
		changeScene(e_scene::error);
	}
	getData().tcp_server.send(getData().send_data);
	while (getData().tcp_server.read(getData().receive_data));
	if (KeyEnter.down()) {
		//Enter�L�[�������ꂽ�Ƃ��A�Q�[����ʂɈڍs �^�C�g������̑J�ڕ��@�͗v����
		changeScene(e_scene::game);
	}
}

void server_title::draw()const {
	FontAsset(U"font100")(U"�^�C�g�����\nEnter�L�[�������Ă�������").drawAt(Scene::Center());
}