#pragma once
#include "Common.hpp"

struct server_game_data {
	TCPServer tcp_server;//�ʐM�p
	IPv4 ipv4;//�ʐM���IPv4�A�h���X
	uint16 send_data[communication_data_size];//�f�[�^���M�p
	uint16 receive_data[communication_data_size];//�f�[�^��M��
	Serial serial;//�V���A���ʐM�p
	bool serial_available;//�V���A���ʐM���s����
	server_game_data();
};

using app = SceneManager<e_scene, server_game_data>;


void server_init();