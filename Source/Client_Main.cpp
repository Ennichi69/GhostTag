#include "Client_Common.hpp"
#include "Client_Setting.hpp"
#include "Client_Connecting.hpp"
#include "Client_Title.hpp"
#include "Client_Tutorial.hpp"
#include "Client_Game.hpp"
#include "Client_Error.hpp"
#include "Client_GameOver.hpp"

void Main() {
	Init();
	Client_Init();
	App Manager;
	Manager
		.add<Client_Setting>(State::Client_Setting)
		.add<Client_Connecting>(State::Client_Connecting)
		.add<Client_Title>(State::Client_Title)
		.add<Client_Tutorial>(State::Client_Tutorial)
		.add<Client_Game>(State::Client_Game)
		.add<Client_Error>(State::Client_Error)
		.add<Client_GameOver>(State::Client_GameOver);
	while (System::Update()) {
		if (!Manager.update()) {
			break;
		}
	}
}