#include "Server_Tutorial.hpp"

Server_Tutorial::Server_Tutorial(const InitData& init) :IScene(init) {
	getData().SendData[(int)Communication_ID::Player0_Status] = 1;
	getData().SendData[(int)Communication_ID::Player1_Status] = 1;
}

void Server_Tutorial::update() {
	if (!getData().TCP_Server.hasSession()) {
		getData().TCP_Server.disconnect();
		changeScene(State::Server_Error);
	}
	getData().TCP_Server.send(getData().SendData);
	while(getData().TCP_Server.read(getData().RecieveData));
	if (Player0_ButtonDown()) {
		Player0_IsReady = true;
		getData().SendData[(int)Communication_ID::Player0_Status] = 2;
	}
	if (Player1_ButtonDown()) {
		Player1_IsReady = true;
		getData().SendData[(int)Communication_ID::Player1_Status] = 2;
	}
	if (Player0_IsReady && Player1_IsReady && getData().RecieveData[(int)Communication_ID::Player0_Status] == 2 && getData().RecieveData[(int)Communication_ID::Player1_Status]) {
		changeScene(State::Server_Game);
	}
}

void Server_Tutorial::draw() const {
	FontAsset(U"PixelM+200")(U"Tutorial").drawAt(Scene::Center());
	if (Player0_IsReady) {
		FontAsset(U"PixelM+80")(U"Player0 Ready").drawAt(Scene::Center().movedBy(-300, 200));
	}
	if (Player1_IsReady) {
		FontAsset(U"PixelM+80")(U"Player1 Ready").drawAt(Scene::Center().movedBy(300, 200));
	}
	if (getData().RecieveData[(int)Communication_ID::Player0_Status] == 2) {
		FontAsset(U"PixelM+80")(U"Player2 Ready").drawAt(Scene::Center().movedBy(-300, -200));
	}
	if (getData().RecieveData[(int)Communication_ID::Player1_Status] == 2) {
		FontAsset(U"PixelM+80")(U"Player3 Ready").drawAt(Scene::Center().movedBy(300, -200));
	}
}