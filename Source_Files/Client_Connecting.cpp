#include "Client_Connecting.hpp"

client_connecting::client_connecting(const InitData& init) :IScene(init) {
	getData().tcp_client.connect(getData().ipv4, port);//�ʐM�ҋ@����ʂɑJ�ڂ����u�ԁA�ʐM�J�n
}

void client_connecting::update() {
	transition_return_button.update(rect_return_button.mouseOver());
	if (rect_return_button.mouseOver()) {
		Cursor::RequestStyle(CursorStyle::Hand);
	}
	if (rect_return_button.leftClicked()) {
		//�����u���ǂ�v�{�^���������ꂽ��
		getData().tcp_client.disconnect();//�ʐM��ؒf
		changeScene(e_scene::initial_setting);
	}
	if (getData().tcp_client.isConnected()) {
		//�����ڑ�������
		changeScene(e_scene::title);//�^�C�g����ʂ�
	}
}

void client_connecting::draw() const {
	rect_return_button.draw(ColorF(1.0, transition_return_button.value())).drawFrame(5);
	FontAsset(U"Mplus_80")(U"���ǂ�").drawAt(rect_return_button.center());
	FontAsset(U"Mplus_200")(U"�ʐM�ҋ@��...").drawAt(Scene::Center());
}