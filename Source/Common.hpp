#pragma once
#include <Siv3D.hpp>

int Player0_ButtonDown();
int Player0_JoyStick_Direction();
int Player1_ButtonDown();
int Player1_JoyStick_Direction();
void Init();

enum class Communication_ID {
	Timer,
	Player0_Pos_X, Player0_Pos_Y,
	Player0_Next_Direction,	//Neutral:0 Left:1 Up:2 Right:3 Down:4
	Player0_Status,			//Title:0 Tutorial:1 Game:2
	Player1_Pos_X, Player1_Pos_Y,
	Player1_Next_Direction,
	Player1_Status,
	Item_Status
};

constexpr uint16 Port = 50000;
constexpr uint16 DataSize = 100;
constexpr Point dxdy[5] = { Point(0,0),Point(-1,0),Point(0,-1),Point(1,0),Point(0,1) };