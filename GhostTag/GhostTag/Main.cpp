#include "Common.hpp"
#include "Init.hpp"
#include "Client_Setting.hpp"
#include "Client_Connecting.hpp"
#include "Client_Title.hpp"
#include "Client_Tutorial.hpp"
#include "Client_Game.hpp"
#include "Server_Connecting.hpp"
#include "Server_Title.hpp"
#include "Server_Tutorial.hpp"
#include "Server_Game.hpp"

void Main() {
	Scene::SetBackground(ColorF(0.0, 0.0, 0.1));
	constexpr Size sceneSize = DisplayResolution::FHD_1920x1080;
	Scene::Resize(sceneSize);
	Window::Resize(sceneSize, WindowResizeOption::KeepSceneSize);
	Window::SetFullscreen(true, unspecified, WindowResizeOption::KeepSceneSize);

	FontAsset::Register(U"PixelM+80", 80, U"example/font/PixelMplus12-Regular.ttf");
	FontAsset::Register(U"PixelM+100", 100, U"example/font/PixelMplus12-Regular.ttf");
	FontAsset::Register(U"PixelM+200", 200, U"example/font/PixelMplus12-Regular.ttf");

	App Manager;
	Manager
		.add<Init_Screen>(State::Init_Screen)
		.add<Client_Setting>(State::Client_Setting)
		.add<Client_Connecting>(State::Client_Connecting)
		.add<Client_Title>(State::Client_Title)
		.add<Client_Tutorial>(State::Client_Tutorial)
		.add<Server_Connecting>(State::Server_Connecting)
		.add<Server_Title>(State::Server_Title)
		.add<Server_Tutorial>(State::Server_Tutorial);
	while (System::Update()) {
		if (!Manager.update()) {
			break;
		}
	}
}