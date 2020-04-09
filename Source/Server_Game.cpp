#include "Server_Game.hpp"

Server_Game::Server_Game(const InitData& init) : IScene(init) {
}

void Server_Game::update() {
	if (!getData().TCP_Server.hasSession()) {
		getData().TCP_Server.disconnect();
		changeScene(State::Server_Error);
	}
	getData().TCP_Server.send(getData().SendData);
	while (getData().TCP_Server.read(getData().RecieveData)) {
	};
	Ghost0.Update_Direction(Player0_JoyStick_Direction());
	Ghost1.Update_Direction(Player1_JoyStick_Direction());
	Ghost0.Update();
	Ghost1.Update();
}

void Server_Game::draw() const {
	DrawMaze();
	Ghost0.Draw();
	Ghost1.Draw();
	Tagger0.Draw();
	Tagger1.Draw();
}