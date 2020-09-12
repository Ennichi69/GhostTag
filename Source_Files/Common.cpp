#include "Common.hpp"

bool left_button_down() {
	//PC環境だとスペースキー 本番環境では物理ボタン(左)
	return KeySpace.down();
}
bool right_button_down() {
	//PC環境だとエンターキー 本番環境では物理ボタン(右)
	return KeyEnter.down();
}
e_direction left_joystick_direction() {
	//PC環境だとWASD 本番環境ではジョイスティック(左)
	if (KeyA.down())return e_direction::left;
	if (KeyW.down())return e_direction::up;
	if (KeyD.down())return e_direction::right;
	if (KeyS.down())return e_direction::down;
	return e_direction::neutral;
}
e_direction right_joystick_direction() {
	//PC環境だと←↑→↓ 本番環境ではジョイスティック(右)
	if (KeyLeft.down())return e_direction::left;
	if (KeyUp.down())return e_direction::up;
	if (KeyRight.down())return e_direction::right;
	if (KeyDown.down())return e_direction::down;
	return e_direction::neutral;
}
void init() {
	Scene::SetBackground(Palette::Black);//背景色の設定
	constexpr Size sceneSize = DisplayResolution::FHD_1920x1080;
	Scene::Resize(sceneSize);
	Window::Resize(sceneSize, WindowResizeOption::KeepSceneSize);
	Window::SetFullscreen(true, unspecified, WindowResizeOption::KeepSceneSize);
	//仮フォント
	FontAsset::Register(U"font40", 40);
	FontAsset::Register(U"font80", 80);
	FontAsset::Register(U"font100", 100);
	FontAsset::Register(U"font200", 200);
}