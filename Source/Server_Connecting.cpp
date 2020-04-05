#include "Server_Connecting.hpp"

Server_Connecting::Server_Connecting(const InitData& init) : IScene(init){
	getData().TCP_Server.startAccept(Port);
}

void Server_Connecting::update() {
	if (getData().TCP_Server.hasSession()) {
		changeScene(State::Server_Title);
	}
}

void Server_Connecting::draw() const {
	FontAsset(U"PixelM+200")(U"í êMë“ã@íÜ...").drawAt(Scene::Center());
}