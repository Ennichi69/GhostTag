#include "Server_Game.hpp"

Server_Game::Server_Game(const InitData& init) : IScene(init) {
	for (uint16 i = 0; i < Item_Size; i++) {
		Itemlist.push_back(NewItem());
	}
}

void Server_Game::update() {
	if (!getData().TCP_Server.hasSession()) {
		getData().TCP_Server.disconnect();
		changeScene(State::Server_Error);
	}
	Timer--;
	Ghost0.Update_Direction(Player0_JoyStick_Direction());
	Ghost1.Update_Direction(Player1_JoyStick_Direction());
	Ghost0.Update();
	Ghost1.Update();
	getData().SendData[(int)Communication_ID::Timer] = Timer;
	getData().SendData[(int)Communication_ID::Player0_PosX] = Ghost0.Pos.x;
	getData().SendData[(int)Communication_ID::Player0_PosY] = Ghost0.Pos.y;
	getData().SendData[(int)Communication_ID::Player0_Direction] = Ghost0.Direction;
	getData().SendData[(int)Communication_ID::Player0_Next_Direction] = Ghost0.Next_Direction;
	getData().SendData[(int)Communication_ID::Player1_PosX] = Ghost1.Pos.x;
	getData().SendData[(int)Communication_ID::Player1_PosY] = Ghost1.Pos.y;
	getData().SendData[(int)Communication_ID::Player1_Direction] = Ghost1.Direction;
	getData().SendData[(int)Communication_ID::Player1_Next_Direction] = Ghost1.Next_Direction;
	getData().SendData[(int)Communication_ID::Ghost_Score] = Ghost_Score;
	getData().SendData[(int)Communication_ID::Tagger_Score] = Tagger_Score;	
	for (uint16 i:step(Item_Size)) {
		getData().SendData[(int)Communication_ID::Item + i * 3] = Itemlist[i].Pos.x;
		getData().SendData[(int)Communication_ID::Item + i * 3 + 1] = Itemlist[i].Pos.y;
		getData().SendData[(int)Communication_ID::Item + i * 3 + 2] = Itemlist[i].Type;
	}
	getData().TCP_Server.send(getData().SendData);
	while (getData().TCP_Server.read(getData().RecieveData)) {
		Tagger0.Pos.x = getData().RecieveData[(int)Communication_ID::Player0_PosX];
		Tagger0.Pos.y = getData().RecieveData[(int)Communication_ID::Player0_PosY];
		Tagger0.Direction = getData().RecieveData[(int)Communication_ID::Player0_Direction];
		Tagger0.Next_Direction = getData().RecieveData[(int)Communication_ID::Player0_Next_Direction];
		Tagger1.Pos.x = getData().RecieveData[(int)Communication_ID::Player1_PosX];
		Tagger1.Pos.y = getData().RecieveData[(int)Communication_ID::Player1_PosY];
		Tagger1.Direction = getData().RecieveData[(int)Communication_ID::Player1_Direction];
		Tagger1.Next_Direction = getData().RecieveData[(int)Communication_ID::Player1_Next_Direction];
	};
	Tagger0.Update();
	Tagger1.Update();
	for (Item &it:Itemlist) {
		if (Circle(it.Pos,Item_Size).intersects(Rect(Arg::center(Ghost0.Pos), Maze_BrockSize))|| Circle(it.Pos, Item_Size).intersects(Rect(Arg::center(Ghost1.Pos), Maze_BrockSize))) {
			Ghost_Score += Item_Score;
			it = NewItem();
		}
	}
}

void Server_Game::draw() const {
	Draw_Maze();
	Ghost0.Draw();
	Ghost1.Draw();
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

}

Item Server_Game::NewItem() {
	while (true) {
		Point p = Maze_BrockPos(Random(0, Maze_Height - 1), Random(0, Maze_Width - 1));
		if (!Intersect_Maze(p)) {
			return Item(p, 0);
		}
	}
}

bool Server_Game::Intersect(Player p, Item it) {
	return Circle(p.Pos, Maze_BrockSize).intersects(Circle(it.Pos, Item_Size));
}