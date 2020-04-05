#include "Server_Common.hpp"
#include "Server_Connecting.hpp"
#include "Server_Title.hpp"
#include "Server_Tutorial.hpp"
#include "Server_Game.hpp"
#include "Server_Error.hpp"
#include "Server_GameOver.hpp"

void Main() {
	Init();
	Server_Init();
	App Manager;
	Manager
		.add<Server_Connecting>(State::Server_Connecting)
		.add<Server_Title>(State::Server_Title)
		.add<Server_Tutorial>(State::Server_Tutorial)
		.add<Server_Game>(State::Server_Game)
		.add<Server_Error>(State::Server_Error)
		.add<Server_GameOver>(State::Server_GameOver);
	while (System::Update()) {
		if (!Manager.update()) {
			break;
		}
	}
}