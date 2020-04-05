#include "Common.hpp"

void Init() {
	Scene::SetBackground(ColorF(0.0, 0.0, 0.1));
	constexpr Size sceneSize = DisplayResolution::FHD_1920x1080;
	Scene::Resize(sceneSize);
	Window::Resize(sceneSize, WindowResizeOption::KeepSceneSize);
	Window::SetFullscreen(true, unspecified, WindowResizeOption::KeepSceneSize);
	FontAsset::Register(U"PixelM+80", 80, U"PixelMplus12-Regular.ttf");
	FontAsset::Register(U"PixelM+100", 100, U"PixelMplus12-Regular.ttf");
	FontAsset::Register(U"PixelM+200", 200, U"PixelMplus12-Regular.ttf");
}

int Player0_ButtonDown() {
	return KeySpace.down();
}
int Player0_JoyStick_Direction() {
	if (KeyA.pressed())return 1;
	if (KeyW.pressed())return 2;
	if (KeyD.pressed())return 3;
	if (KeyS.pressed())return 4;
	return 0;
}
int Player1_ButtonDown() {
	return KeyEnter.down();
}
int Player1_JoyStick_Direction() {
	if (KeyLeft.pressed())return 1;
	if (KeyUp.pressed())return 2;
	if (KeyRight.pressed())return 3;
	if (KeyDown.pressed())return 4;
	return 0;
}