#pragma once
#include "Common.hpp"

enum class State {
	Server_Connecting,Server_Title,Server_Tutorial,Server_Game,Server_GameOver,Server_Error
};


struct GameData {
	TCPServer TCP_Server;
	uint16 SendData[100];
	uint16 RecieveData[100];
};

using App = SceneManager<State, GameData>;

void Server_Init();