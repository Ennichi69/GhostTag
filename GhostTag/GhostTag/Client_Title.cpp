#include "Client_Title.hpp"

Client_Title::Client_Title(const InitData& init) : IScene(init) {
	for (int i = 0; i < DataSize; i++) {
		getData().SendData[i] = 0;
	}
}
void Client_Title::update() {
	if (getData().TCP_Client.hasError()) {
		getData().TCP_Client.disconnect();
		changeScene(State::Client_Error);
	}
	getData().TCP_Client.send(getData().SendData);
	while(getData().TCP_Client.read(getData().RecieveData));
	if (Player0_ButtonDown()) {
		Player0_IsReady = true;
	}
	if (Player1_ButtonDown()) {
		Player1_IsReady = true;
	}
	if (Player0_IsReady && Player1_IsReady) {
		//changeScene(State::Client_Tutorial);
		changeScene(State::Client_Game);
	}
}
void Client_Title::draw() const {
	FontAsset(U"PixelM+200")(U"Ghost Tag").drawAt(Scene::Center());
	if (Player0_IsReady) {
		FontAsset(U"PixelM+80")(U"Player0 Ready").drawAt(Scene::Center().movedBy(-300, 200));
	}
	if (Player1_IsReady) {
		FontAsset(U"PixelM+80")(U"Player1 Ready").drawAt(Scene::Center().movedBy(300, 200));
	}
}