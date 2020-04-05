#pragma once
#include "Common.hpp"

enum class State {
	Init_Screen,Client_Setting,Client_Connecting,Client_Title,Client_Tutorial,Client_Game,Client_GameOver,Client_Error
};

struct GameData {
	TCPClient TCP_Client;
	IPv4 IP;
	uint16 SendData[100];
	uint16 RecieveData[100];
};

using App = SceneManager<State, GameData>;

void Client_Init();