#include "Server_Title.hpp"

Server_Title::Server_Title(const InitData& init) : IScene(init) {
	for (int i = 0; i < DataSize; i++) {
		getData().SendData[i] = 0;
	}
}

void Server_Title::update() {
	if (!getData().TCP_Server.hasSession()) {
		getData().TCP_Server.disconnect();
		changeScene(State::Server_Error);
	}
	getData().TCP_Server.send(getData().SendData);
	while (getData().TCP_Server.read(getData().RecieveData));
	if (Player0_ButtonDown()) {
		Player0_IsReady = true;
	}
	if (Player1_ButtonDown()) {
		Player1_IsReady = true;
	}
	if (Player0_IsReady && Player1_IsReady) {
		//changeScene(State::Server_Tutorial);
		changeScene(State::Server_Game);
	}
}

void Server_Title::draw() const {
	FontAsset(U"PixelM+200")(U"Ghost Tag").drawAt(Scene::Center());
	if (Player0_IsReady) {
		FontAsset(U"PixelM+80")(U"Player0 Ready").drawAt(Scene::Center().movedBy(-300, 200));
	}
	if (Player1_IsReady) {
		FontAsset(U"PixelM+80")(U"Player1 Ready").drawAt(Scene::Center().movedBy(300, 200));
	}
}