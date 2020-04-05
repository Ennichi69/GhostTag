#include "Client_Tutorial.hpp"

Client_Tutorial::Client_Tutorial(const InitData& init) : IScene(init) {
	getData().SendData[(int)Communication_ID::Player0_Status] = 1;
	getData().SendData[(int)Communication_ID::Player1_Status] = 1;
}

void Client_Tutorial::update() {
	if (getData().TCP_Client.hasError()) {
		getData().TCP_Client.disconnect();
		changeScene(State::Client_Error);
	}
	getData().TCP_Client.send(getData().SendData);
	while(getData().TCP_Client.read(getData().RecieveData));
	if (Player0_ButtonDown()) {
		Player0_IsReady = true;
		getData().SendData[(int)Communication_ID::Player0_Status] = 2;
	}
	if (Player1_ButtonDown()) {
		Player1_IsReady = true;
		getData().SendData[(int)Communication_ID::Player1_Status] = 2;
	}
	if (Player0_IsReady && Player1_IsReady && getData().RecieveData[(int)Communication_ID::Player0_Status] == 2 && getData().RecieveData[(int)Communication_ID::Player1_Status] == 2) {
		changeScene(State::Client_Game);
	}
}

void Client_Tutorial::draw() const {
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