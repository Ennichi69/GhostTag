#pragma once
#include <Siv3D.hpp>

uint16 Player0_ButtonDown();
uint16 Player0_JoyStick_Direction();
uint16 Player1_ButtonDown();
uint16 Player1_JoyStick_Direction();
void Init();

enum class Communication_ID {
	Timer,
	Player0_PosX, Player0_PosY,
	Player0_Direction,
	Player0_Next_Direction,	//Neutral:0 Left:1 Up:2 Right:3 Down:4
	Player0_Status,			//Title:0 Tutorial:1 Game:2
	Player1_PosX, Player1_PosY,
	Player1_Direction,
	Player1_Next_Direction,
	Player1_Status,
	Item_Status
};

constexpr uint16 Port = 50000;
constexpr uint16 DataSize = 100;
