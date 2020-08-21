#pragma once
#include "Common.hpp"

struct client_game_data {
	TCPClient tcp_client;//�ʐM�p
	IPv4 ipv4;//�ʐM���IPv4�A�h���X
	uint16 send_data[communication_data_size];//�f�[�^���M�p
	uint16 receive_data[communication_data_size];//�f�[�^��M��
};

using app = SceneManager<e_scene, client_game_data>;


void client_init();