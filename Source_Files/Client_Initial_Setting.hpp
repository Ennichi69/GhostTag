#pragma once
#include "Client_Common.hpp"

class client_initial_setting :public app::Scene {
public:
	client_initial_setting(const InitData& init);
	void update() override;
	void draw() const override;
private:
	Rect rect_ok_button = Rect(Arg::center = Scene::Center().movedBy(0, 200), 500, 100);//OK�{�^��
	Rect rect_textbox[4];//���͗p�e�L�X�g�{�b�N�X
	String text[4];//���ꂼ��̃e�L�X�g�{�b�N�X�ɉ���������Ă��邩
	Transition transition_ok_button = Transition(4.0s, 2.0s);//OK�{�^���A�j���[�V�����p
	uint16 input_textbox_number = 0;//���ݓ��͒��̃e�L�X�g�{�b�N�X�̔ԍ�
};