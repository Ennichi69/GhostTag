#pragma once
#include <Siv3D.hpp>

enum class State {
	Init_Screen,Client_Setting,Client_Connecting,Client_Title,Client_Tutorial,Client_Game,Client_GameOver,Client_Error,Server_Connecting,Server_Title,Server_Tutorial,Server_Game,Server_GameOver,Server_Error
};

enum class Communication_ID {
	Timer, 
	Player0_Pos_X, Player0_Pos_Y, 
	Player0_Next_Direction,//Neutral:0 Left:1 Up:2 Right:3 Down:4
	Player0_Status, //Title:0 Tutorial:1 Game:2
	Player1_Pos_X, Player1_Pos_Y, 
	Player1_Next_Direction, 
	Player1_Status, 
	Item_Status
};

struct GameData {
	int Timer;
	TCPServer TCP_Server;
	TCPClient TCP_Client;
	IPv4 IP;
	int SendData[100];
	int RecieveData[100];
};

int Player0_ButtonDown();
int Player0_JoyStick_Direction();
int Player1_ButtonDown();
int Player1_JoyStick_Direction();

using App = SceneManager<State, GameData>;
constexpr uint16 Port = 50000;
constexpr int DataSize = 100;
constexpr Point dxdy[5] = { Point(0,0),Point(-1,0),Point(0,-1),Point(1,0),Point(0,1) };