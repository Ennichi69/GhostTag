#include "Common.hpp"

bool left_button_down(Array<uint8>& a, bool b) {
	//PC環境だとスペースキー 本番環境では物理ボタン(左)
	if (b) {
		for (auto i : a) {
			if (i == 15)return true;
		}
	//	return false;
	}
	return KeySpace.pressed();
}
bool right_button_down(Array<uint8>& a, bool b) {
	//PC環境だとエンターキー 本番環境では物理ボタン(右)
	if (b) {
		for (auto i : a) {
			if (i == 25)return true;
		}
	//	return false;
	}
	return KeyEnter.pressed();
}
e_direction left_joystick_direction(Array<uint8>& a,bool b, e_direction now_direction) {
	//PC環境だとWASD 本番環境ではジョイスティック(左)
	if (b) {
		//斜め入力をした時に曲がれるように
		for (auto i : a) {
			if (i == 11 && now_direction != left)return e_direction::left;
			if (i == 12 && now_direction != up)return e_direction::up;
			if (i == 13 && now_direction != right)return e_direction::right;
			if (i == 14 && now_direction != down)return e_direction::down;
		}
		for (auto i : a) {
			if (i == 11)return e_direction::left;
			if (i == 12)return e_direction::up;
			if (i == 13)return e_direction::right;
			if (i == 14)return e_direction::down;
		}
	//	return e_direction::neutral;
	}
	if (KeyA.pressed())return e_direction::left;
	if (KeyW.pressed())return e_direction::up;
	if (KeyD.pressed())return e_direction::right;
	if (KeyS.pressed())return e_direction::down;
	return e_direction::neutral;
}
e_direction right_joystick_direction(Array<uint8>& a, bool b, e_direction now_direction) {
	//PC環境だと←↑→↓ 本番環境ではジョイスティック(右)
	if (b) {
		//斜め入力をした時に曲がれるように
		for (auto i : a) {
			if (i == 21 && now_direction != left)return e_direction::left;
			if (i == 22 && now_direction != up)return e_direction::up;
			if (i == 23 && now_direction != right)return e_direction::right;
			if (i == 24 && now_direction != down)return e_direction::down;
		}
		for (auto i : a) {
			if (i == 21)return e_direction::left;
			if (i == 22)return e_direction::up;
			if (i == 23)return e_direction::right;
			if (i == 24)return e_direction::down;
		}
	//	return e_direction::neutral;
	}
	if (KeyLeft.pressed())return e_direction::left;
	if (KeyUp.pressed())return e_direction::up;
	if (KeyRight.pressed())return e_direction::right;
	if (KeyDown.pressed())return e_direction::down;
	return e_direction::neutral;
}

void init() {
	Scene::SetBackground(Palette::Black);//背景色の設定
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
	FontAsset::Register(U"font50", 50, Resource(U"fonts/4x4kanafont.ttf"));
	FontAsset::Register(U"font60", 60, Resource(U"fonts/4x4kanafont.ttf"));
	FontAsset::Register(U"font80", 80, Resource(U"fonts/4x4kanafont.ttf"));
	FontAsset::Register(U"font100", 100, Resource(U"fonts/4x4kanafont.ttf"));
	FontAsset::Register(U"font200", 200, Resource(U"fonts/4x4kanafont.ttf"));
	
	AudioAsset::Register(U"game_set", Resource(U"musics/game_set.mp3"));
	AudioAsset::Register(U"item_get", Resource(U"musics/item_get.mp3"));
	AudioAsset::Register(U"main_theme", Resource(U"musics/main_theme.mp3"));
	AudioAsset::Register(U"respawn", Resource(U"musics/respawn.mp3"));
	AudioAsset::Register(U"tag", Resource(U"musics/tag.mp3"));
	AudioAsset::Register(U"thunder", Resource(U"musics/thunder.mp3"));
	AudioAsset::Register(U"wing", Resource(U"musics/wing.mp3"));

	TextureAsset::Register(U"pump_left1", Resource(U"pictures/pump_left1.png"));
	TextureAsset::Register(U"pump_left2", Resource(U"pictures/pump_left2.png"));
	TextureAsset::Register(U"pump_up1", Resource(U"pictures/pump_up1.png"));
	TextureAsset::Register(U"pump_up2", Resource(U"pictures/pump_up2.png"));
	TextureAsset::Register(U"pump_right1", Resource(U"pictures/pump_right1.png"));
	TextureAsset::Register(U"pump_right2", Resource(U"pictures/pump_right2.png"));
	TextureAsset::Register(U"pump_down1", Resource(U"pictures/pump_down1.png"));
	TextureAsset::Register(U"pump_down2", Resource(U"pictures/pump_down2.png"));
	TextureAsset::Register(U"ghost_left1", Resource(U"pictures/ghost_left1.png"));
	TextureAsset::Register(U"ghost_left2", Resource(U"pictures/ghost_left2.png"));
	TextureAsset::Register(U"ghost_up1", Resource(U"pictures/ghost_up1.png"));
	TextureAsset::Register(U"ghost_up2", Resource(U"pictures/ghost_up2.png"));
	TextureAsset::Register(U"ghost_right1", Resource(U"pictures/ghost_right1.png"));
	TextureAsset::Register(U"ghost_right2", Resource(U"pictures/ghost_right2.png"));
	TextureAsset::Register(U"ghost_down1", Resource(U"pictures/ghost_down1.png"));
	TextureAsset::Register(U"ghost_down2", Resource(U"pictures/ghost_down2.png"));
	TextureAsset::Register(U"boy_left1", Resource(U"pictures/boy_left1.png"));
	TextureAsset::Register(U"boy_left2", Resource(U"pictures/boy_left2.png"));
	TextureAsset::Register(U"boy_up1", Resource(U"pictures/boy_up1.png"));
	TextureAsset::Register(U"boy_up2", Resource(U"pictures/boy_up2.png"));
	TextureAsset::Register(U"boy_right1", Resource(U"pictures/boy_right1.png"));
	TextureAsset::Register(U"boy_right2", Resource(U"pictures/boy_right2.png"));
	TextureAsset::Register(U"boy_down1", Resource(U"pictures/boy_down1.png"));
	TextureAsset::Register(U"boy_down2", Resource(U"pictures/boy_down2.png"));
	TextureAsset::Register(U"girl_left1", Resource(U"pictures/girl_left1.png"));
	TextureAsset::Register(U"girl_left2", Resource(U"pictures/girl_left2.png"));
	TextureAsset::Register(U"girl_up1", Resource(U"pictures/girl_up1.png"));
	TextureAsset::Register(U"girl_up2", Resource(U"pictures/girl_up2.png"));
	TextureAsset::Register(U"girl_right1", Resource(U"pictures/girl_right1.png"));
	TextureAsset::Register(U"girl_right2", Resource(U"pictures/girl_right2.png"));
	TextureAsset::Register(U"girl_down1", Resource(U"pictures/girl_down1.png"));
	TextureAsset::Register(U"girl_down2", Resource(U"pictures/girl_down2.png"));

	TextureAsset::Register(U"pump_left1_thunder", Resource(U"pictures/pump_left1_thunder.png"));
	TextureAsset::Register(U"pump_left2_thunder", Resource(U"pictures/pump_left2_thunder.png"));
	TextureAsset::Register(U"pump_up1_thunder", Resource(U"pictures/pump_up1_thunder.png"));
	TextureAsset::Register(U"pump_up2_thunder", Resource(U"pictures/pump_up2_thunder.png"));
	TextureAsset::Register(U"pump_right1_thunder", Resource(U"pictures/pump_right1_thunder.png"));
	TextureAsset::Register(U"pump_right2_thunder", Resource(U"pictures/pump_right2_thunder.png"));
	TextureAsset::Register(U"pump_down1_thunder", Resource(U"pictures/pump_down1_thunder.png"));
	TextureAsset::Register(U"pump_down2_thunder", Resource(U"pictures/pump_down2_thunder.png"));
	TextureAsset::Register(U"ghost_left1_thunder", Resource(U"pictures/ghost_left1_thunder.png"));
	TextureAsset::Register(U"ghost_left2_thunder", Resource(U"pictures/ghost_left2_thunder.png"));
	TextureAsset::Register(U"ghost_up1_thunder", Resource(U"pictures/ghost_up1_thunder.png"));
	TextureAsset::Register(U"ghost_up2_thunder", Resource(U"pictures/ghost_up2_thunder.png"));
	TextureAsset::Register(U"ghost_right1_thunder", Resource(U"pictures/ghost_right1_thunder.png"));
	TextureAsset::Register(U"ghost_right2_thunder", Resource(U"pictures/ghost_right2_thunder.png"));
	TextureAsset::Register(U"ghost_down1_thunder", Resource(U"pictures/ghost_down1_thunder.png"));
	TextureAsset::Register(U"ghost_down2_thunder", Resource(U"pictures/ghost_down2_thunder.png"));
	TextureAsset::Register(U"boy_left1_thunder", Resource(U"pictures/boy_left1_thunder.png"));
	TextureAsset::Register(U"boy_left2_thunder", Resource(U"pictures/boy_left2_thunder.png"));
	TextureAsset::Register(U"boy_up1_thunder", Resource(U"pictures/boy_up1_thunder.png"));
	TextureAsset::Register(U"boy_up2_thunder", Resource(U"pictures/boy_up2_thunder.png"));
	TextureAsset::Register(U"boy_right1_thunder", Resource(U"pictures/boy_right1_thunder.png"));
	TextureAsset::Register(U"boy_right2_thunder", Resource(U"pictures/boy_right2_thunder.png"));
	TextureAsset::Register(U"boy_down1_thunder", Resource(U"pictures/boy_down1_thunder.png"));
	TextureAsset::Register(U"boy_down2_thunder", Resource(U"pictures/boy_down2_thunder.png"));
	TextureAsset::Register(U"girl_left1_thunder", Resource(U"pictures/girl_left1_thunder.png"));
	TextureAsset::Register(U"girl_left2_thunder", Resource(U"pictures/girl_left2_thunder.png"));
	TextureAsset::Register(U"girl_up1_thunder", Resource(U"pictures/girl_up1_thunder.png"));
	TextureAsset::Register(U"girl_up2_thunder", Resource(U"pictures/girl_up2_thunder.png"));
	TextureAsset::Register(U"girl_right1_thunder", Resource(U"pictures/girl_right1_thunder.png"));
	TextureAsset::Register(U"girl_right2_thunder", Resource(U"pictures/girl_right2_thunder.png"));
	TextureAsset::Register(U"girl_down1_thunder", Resource(U"pictures/girl_down1_thunder.png"));
	TextureAsset::Register(U"girl_down2_thunder", Resource(U"pictures/girl_down2_thunder.png"));

	TextureAsset::Register(U"pump_left1_wing", Resource(U"pictures/pump_left1_wing.png"));
	TextureAsset::Register(U"pump_left2_wing", Resource(U"pictures/pump_left2_wing.png"));
	TextureAsset::Register(U"pump_up1_wing", Resource(U"pictures/pump_up1_wing.png"));
	TextureAsset::Register(U"pump_up2_wing", Resource(U"pictures/pump_up2_wing.png"));
	TextureAsset::Register(U"pump_right1_wing", Resource(U"pictures/pump_right1_wing.png"));
	TextureAsset::Register(U"pump_right2_wing", Resource(U"pictures/pump_right2_wing.png"));
	TextureAsset::Register(U"pump_down1_wing", Resource(U"pictures/pump_down1_wing.png"));
	TextureAsset::Register(U"pump_down2_wing", Resource(U"pictures/pump_down2_wing.png"));
	TextureAsset::Register(U"ghost_left1_wing", Resource(U"pictures/ghost_left1_wing.png"));
	TextureAsset::Register(U"ghost_left2_wing", Resource(U"pictures/ghost_left2_wing.png"));
	TextureAsset::Register(U"ghost_up1_wing", Resource(U"pictures/ghost_up1_wing.png"));
	TextureAsset::Register(U"ghost_up2_wing", Resource(U"pictures/ghost_up2_wing.png"));
	TextureAsset::Register(U"ghost_right1_wing", Resource(U"pictures/ghost_right1_wing.png"));
	TextureAsset::Register(U"ghost_right2_wing", Resource(U"pictures/ghost_right2_wing.png"));
	TextureAsset::Register(U"ghost_down1_wing", Resource(U"pictures/ghost_down1_wing.png"));
	TextureAsset::Register(U"ghost_down2_wing", Resource(U"pictures/ghost_down2_wing.png"));
	TextureAsset::Register(U"boy_left1_wing", Resource(U"pictures/boy_left1_wing.png"));
	TextureAsset::Register(U"boy_left2_wing", Resource(U"pictures/boy_left2_wing.png"));
	TextureAsset::Register(U"boy_up1_wing", Resource(U"pictures/boy_up1_wing.png"));
	TextureAsset::Register(U"boy_up2_wing", Resource(U"pictures/boy_up2_wing.png"));
	TextureAsset::Register(U"boy_right1_wing", Resource(U"pictures/boy_right1_wing.png"));
	TextureAsset::Register(U"boy_right2_wing", Resource(U"pictures/boy_right2_wing.png"));
	TextureAsset::Register(U"boy_down1_wing", Resource(U"pictures/boy_down1_wing.png"));
	TextureAsset::Register(U"boy_down2_wing", Resource(U"pictures/boy_down2_wing.png"));
	TextureAsset::Register(U"girl_left1_wing", Resource(U"pictures/girl_left1_wing.png"));
	TextureAsset::Register(U"girl_left2_wing", Resource(U"pictures/girl_left2_wing.png"));
	TextureAsset::Register(U"girl_up1_wing", Resource(U"pictures/girl_up1_wing.png"));
	TextureAsset::Register(U"girl_up2_wing", Resource(U"pictures/girl_up2_wing.png"));
	TextureAsset::Register(U"girl_right1_wing", Resource(U"pictures/girl_right1_wing.png"));
	TextureAsset::Register(U"girl_right2_wing", Resource(U"pictures/girl_right2_wing.png"));
	TextureAsset::Register(U"girl_down1_wing", Resource(U"pictures/girl_down1_wing.png"));
	TextureAsset::Register(U"girl_down2_wing", Resource(U"pictures/girl_down2_wing.png"));
}