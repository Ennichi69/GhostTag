#include <Siv3D.hpp>
#include "Server_Common.hpp"
#include "Server_Connecting.hpp"
#include "Server_Title.hpp"
#include "Server_Game.hpp"
#include "Server_Error.hpp"
#include "Server_Result.hpp"
void Main() {
	init();
	app manager;
	manager
		.add<server_connecting>(e_scene::connecting)
		.add<server_title>(e_scene::title)
		.add<server_game>(e_scene::game)
		.add<server_error>(e_scene::error)
		.add<server_result>(e_scene::result);
	while (System::Update()) {
		if (!manager.update()) {
			break;
		}
	}
}