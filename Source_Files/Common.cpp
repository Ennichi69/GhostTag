#include "Common.hpp"

bool left_button_down() {
	//PC�����ƃX�y�[�X�L�[ �{�Ԋ��ł͕����{�^��(��)
	return KeySpace.down();
}
bool right_button_down() {
	//PC�����ƃG���^�[�L�[ �{�Ԋ��ł͕����{�^��(�E)
	return KeyEnter.down();
}
e_direction left_joystick_direction() {
	//PC������WASD �{�Ԋ��ł̓W���C�X�e�B�b�N(��)
	if (KeyA.down())return e_direction::left;
	if (KeyW.down())return e_direction::up;
	if (KeyD.down())return e_direction::right;
	if (KeyS.down())return e_direction::down;
	return e_direction::neutral;
}
e_direction right_joystick_direction() {
	//PC�����Ɓ������� �{�Ԋ��ł̓W���C�X�e�B�b�N(�E)
	if (KeyLeft.down())return e_direction::left;
	if (KeyUp.down())return e_direction::up;
	if (KeyRight.down())return e_direction::right;
	if (KeyDown.down())return e_direction::down;
	return e_direction::neutral;
}
void init() {
	Scene::SetBackground(Palette::Black);//�w�i�F�̐ݒ�
	constexpr Size sceneSize = DisplayResolution::FHD_1920x1080;
	Scene::Resize(sceneSize);
	Window::Resize(sceneSize, WindowResizeOption::KeepSceneSize);
	Window::SetFullscreen(true, unspecified, WindowResizeOption::KeepSceneSize);
	//���t�H���g
	FontAsset::Register(U"font40", 40);
	FontAsset::Register(U"font80", 80);
	FontAsset::Register(U"font100", 100);
	FontAsset::Register(U"font200", 200);
}
