#pragma once
#include <Siv3D.hpp>

enum class State {
	Init_Screen,Client_Setting,Client_Connecting,Client_Title,Client_Tutorial,Client_Game,Client_GameOver,Client_Error,Server_Connecting,Server_Title,Server_Tutorial,Server_Game,Server_GameOver,Server_Error
};

struct GameData {
	int Timer;
	TCPServer TCP_Server;
	TCPClient TCP_Client;
	IPv4 IP;
};

using App = SceneManager<State, GameData>;

constexpr uint16 Port = 50000;