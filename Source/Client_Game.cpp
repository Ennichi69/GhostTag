#include "Client_Game.hpp"

Client_Game::Client_Game(const InitData& init) : IScene(init) {
}

void Client_Game::update() {
	if (getData().TCP_Client.hasError()) {
		getData().TCP_Client.disconnect();
		changeScene(State::Client_Error);
	}
	Timer--;
	Tagger0.Update_Direction(Player0_JoyStick_Direction());
	Tagger1.Update_Direction(Player1_JoyStick_Direction());
	Tagger0.Update();
	Tagger1.Update(); getData().SendData[(int)Communication_ID::Timer] = Timer;
	getData().SendData[(int)Communication_ID::Player0_PosX] = Tagger0.Pos.x;
	getData().SendData[(int)Communication_ID::Player0_PosY] = Tagger0.Pos.y;
	getData().SendData[(int)Communication_ID::Player0_Direction] = Tagger0.Direction;
	getData().SendData[(int)Communication_ID::Player0_Next_Direction] = Tagger0.Next_Direction;
	getData().SendData[(int)Communication_ID::Player1_PosX] = Tagger1.Pos.x;
	getData().SendData[(int)Communication_ID::Player1_PosY] = Tagger1.Pos.y;
	getData().SendData[(int)Communication_ID::Player1_Direction] = Tagger1.Direction;
	getData().SendData[(int)Communication_ID::Player1_Next_Direction] = Tagger1.Next_Direction;
	getData().TCP_Client.send(getData().SendData);
	while (getData().TCP_Client.read(getData().RecieveData));
}

void Client_Game::draw() const {
	DrawMaze();
	Tagger0.Draw();
	Tagger1.Draw();
}