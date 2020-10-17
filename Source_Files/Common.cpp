#include "Common.hpp"

bool left_button_down(Array<uint8>& a, bool b) {
	//PC�����ƃX�y�[�X�L�[ �{�Ԋ��ł͕����{�^��(��)
	if (b) {
		for (auto i : a) {
			if (i == 15)return true;
		}
		return false;
	}
	else {
		return KeySpace.down();
	}
}
bool right_button_down(Array<uint8>& a, bool b) {
	//PC�����ƃG���^�[�L�[ �{�Ԋ��ł͕����{�^��(�E)
	if (b) {
		for (auto i : a) {
			if (i == 25)return true;
		}
		return false;
	}
	else {
		return KeyEnter.down();
	}
}
e_direction left_joystick_direction(Array<uint8>& a,bool b, e_direction now_direction) {
	//PC������WASD �{�Ԋ��ł̓W���C�X�e�B�b�N(��)
	if (b) {
		for (auto i : a) {
			if (i == 11 && now_direction != left)return e_direction::left;
			if (i == 12 && now_direction != up)return e_direction::up;
			if (i == 13 && now_direction != right)return e_direction::right;
			if (i == 14 && now_direction != down)return e_direction::down;
		}
		return e_direction::neutral;
	}
	else {
		if (KeyA.down())return e_direction::left;
		if (KeyW.down())return e_direction::up;
		if (KeyD.down())return e_direction::right;
		if (KeyS.down())return e_direction::down;
		return e_direction::neutral;
	}
}
e_direction right_joystick_direction(Array<uint8>& a, bool b, e_direction now_direction) {
	if (b) {
		//PC�����Ɓ������� �{�Ԋ��ł̓W���C�X�e�B�b�N(�E)
		for (auto i : a) {
			if (i == 21 && now_direction != left)return e_direction::left;
			if (i == 22 && now_direction != up)return e_direction::up;
			if (i == 23 && now_direction != right)return e_direction::right;
			if (i == 24 && now_direction != down)return e_direction::down;
		}
		return e_direction::neutral;
	}
	else {
		if (KeyLeft.down())return e_direction::left;
		if (KeyUp.down())return e_direction::up;
		if (KeyRight.down())return e_direction::right;
		if (KeyDown.down())return e_direction::down;
		return e_direction::neutral;
	}
}

void init() {
	Scene::SetBackground(Palette::Black);//�w�i�F�̐ݒ�
	constexpr Size sceneSize = DisplayResolution::FHD_1920x1080;
	Scene::Resize(sceneSize);
	Window::Resize(sceneSize, WindowResizeOption::KeepSceneSize);
	Window::SetFullscreen(true, unspecified, WindowResizeOption::KeepSceneSize);
	FontAsset::Register(U"Mplus_40", 40);
	FontAsset::Register(U"Mplus_60", 60);
	FontAsset::Register(U"Mplus_80", 80);
	FontAsset::Register(U"Mplus_100", 100);
	FontAsset::Register(U"Mplus_200", 200);
	FontAsset::Register(U"font40", 40, Resource(U"fonts/4x4kanafont.ttf"));
	FontAsset::Register(U"font60", 60, Resource(U"fonts/4x4kanafont.ttf"));
	FontAsset::Register(U"font80", 80, Resource(U"fonts/4x4kanafont.ttf"));
	FontAsset::Register(U"font100", 100, Resource(U"fonts/4x4kanafont.ttf"));
	FontAsset::Register(U"font200", 200, Resource(U"fonts/4x4kanafont.ttf"));

}