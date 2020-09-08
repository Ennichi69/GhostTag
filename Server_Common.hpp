#pragma once
#include "Common.hpp"

struct server_game_data {
	TCPServer tcp_server;//通信用
	IPv4 ipv4;//通信先のIPv4アドレス
	uint16 send_data[communication_data_size];//データ送信用
	uint16 receive_data[communication_data_size];//データ受信先
};

using app = SceneManager<e_scene, server_game_data>;


void server_init();