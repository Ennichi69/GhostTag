#include "Client_GameOver.hpp"

Client_GameOver::Client_GameOver(const InitData& init) : IScene(init) {
}

void Client_GameOver::update() {
	if (getData().TCP_Client.hasError()) {
		getData().TCP_Client.disconnect();
		changeScene(State::Client_Error);
	}
	getData().TCP_Client.send(getData().SendData);
	while (getData().TCP_Client.read(getData().RecieveData));
}

void Client_GameOver::draw() const {
	FontAsset(U"PixelM+200")(U"GameScene").drawAt(Scene::Center());
}