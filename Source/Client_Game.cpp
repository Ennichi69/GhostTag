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
	while (getData().TCP_Client.read(getData().RecieveData)) {
		Timer = getData().RecieveData[(int)Communication_ID::Timer];
		Ghost_Score = getData().RecieveData[(int)Communication_ID::Ghost_Score];
		Tagger_Score = getData().RecieveData[(int)Communication_ID::Tagger_Score];
		for (uint16 i : step(Item_Size)) {
			Itemlist[i].Pos.x = getData().RecieveData[(int)Communication_ID::Item + i * 3];
			Itemlist[i].Pos.y = getData().RecieveData[(int)Communication_ID::Item + i * 3 + 1];
			Itemlist[i].Type = getData().RecieveData[(int)Communication_ID::Item + i * 3 + 2];
		}
		if (getData().RecieveData[(int)Communication_ID::Tagger0_Catching]) {
			Client_Effect.add([pos = Tagger0.Pos](double t){
				FontAsset(U"PixelM+40")(U"Tag!").drawAt(pos.movedBy(0, t * -80), Palette::Limegreen);
				return t < 1.0;
			});
		}
		if (getData().RecieveData[(int)Communication_ID::Tagger1_Catching]) {
			Client_Effect.add([pos = Tagger1.Pos](double t){
				FontAsset(U"PixelM+40")(U"Tag!").drawAt(pos.movedBy(0, t * -80), Palette::Limegreen);
				return t < 1.0;
			});
		}
	}
}

void Client_Game::draw() const {
	Draw_Maze();
	Tagger0.Draw();
	Tagger1.Draw();
	for (Item it : Itemlist) {
		it.Draw();
	}
	TimerBox.drawFrame(5, 0);
	Player0_SpecialMeterBox.drawFrame(0, 5);
	Player1_SpecialMeterBox.drawFrame(0, 5);
	Ghost_ScoreBox.drawFrame(5, 0);
	Tagger_ScoreBox.drawFrame(5, 0);
	FontAsset(U"PixelM+80")(U"{}:{:0>2}"_fmt(Timer / 60, Timer % 60)).drawAt(TimerBox.center());
	FontAsset(U"PixelM+80")(U"{:0>5}"_fmt(Ghost_Score)).drawAt(Ghost_ScoreBox.center());
	FontAsset(U"PixelM+80")(U"{:0>5}"_fmt(Tagger_Score)).drawAt(Tagger_ScoreBox.center());
	Client_Effect.update();
}