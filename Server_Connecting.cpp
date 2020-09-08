#include "Server_Connecting.hpp"

server_connecting::server_connecting(const InitData& init) :IScene(init) {
	getData().tcp_server.startAccept(port);//�ʐM�ҋ@����ʂɑJ�ڂ����u�ԁA�ʐM�J�n
}

void server_connecting::update() {
	if (getData().tcp_server.hasSession()) {
		//�����ڑ�������
		changeScene(e_scene::title);//�^�C�g����ʂ�
	}
}

void server_connecting::draw() const {
	FontAsset(U"font200")(U"�ʐM�ҋ@��...").drawAt(Scene::Center());
}