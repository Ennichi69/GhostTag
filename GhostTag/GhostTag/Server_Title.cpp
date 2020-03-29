#include "Server_Title.hpp"

Server_Title::Server_Title(const InitData& init) : IScene(init) {
}

void Server_Title::update() {
	if (!getData().TCP_Server.hasSession()) {
		getData().TCP_Server.disconnect();
		changeScene(State::Server_Error);
	}
	if (KeyEnter.down()) {
		IsReady = true;
	}
	if (IsReady) {
		int Data[100];
		for (int i = 0; i < 100; i++) {
			Data[i] = 0;
		}
		Data[0] = 1;
		getData().TCP_Server.send(Data);
	}
	else {
		int Data[100];
		for (int i = 0; i < 100; i++) {
			Data[i] = 0;
		}
		getData().TCP_Server.send(Data);
		//‚±‚Ì•Ó‚Í‚Ü‚½‚¢‚Â‚©l‚¦‚é
	}
}

void Server_Title::draw() const {

}