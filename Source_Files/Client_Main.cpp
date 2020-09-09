#include <Siv3D.hpp>
#include "Client_Common.hpp"
#include "Client_Initial_Setting.hpp"
#include "Client_Connecting.hpp"
#include "Client_Title.hpp"
#include "Client_Game.hpp"
#include "Client_Error.hpp"
#include "Client_Result.hpp"
void Main() {
	init();
	app manager;
	manager
		.add<client_initial_setting>(e_scene::initial_setting)
		.add<client_connecting>(e_scene::connecting)
		.add<client_title>(e_scene::title)
		.add<client_game>(e_scene::game)
		.add<client_error>(e_scene::error)
		.add<client_result>(e_scene::result);
	while (System::Update()) {
		if (!manager.update()) {
			break;
		}
	}
}