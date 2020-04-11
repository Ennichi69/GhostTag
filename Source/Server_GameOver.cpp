#include "Server_GameOver.hpp"

Server_GameOver::Server_GameOver(const InitData& init) : IScene(init) {
}

void Server_GameOver::update() {
	if (!getData().TCP_Server.hasSession()) {
		getData().TCP_Server.disconnect();
		changeScene(State::Server_Error);
	}
	getData().TCP_Server.send(getData().SendData);
	while (getData().TCP_Server.read(getData().RecieveData));
}

void Server_GameOver::draw() const {
	FontAsset(U"PixelM+200")(U"GameScene").drawAt(Scene::Center());
}