#pragma once
#include "Common.hpp"

struct client_game_data {
	TCPClient tcp_client;//通信用
	IPv4 ipv4;//通信先のIPv4アドレス
	uint16 send_data[communication_data_size];//データ送信用
	uint16 receive_data[communication_data_size];//データ受信先
	Serial serial;//シリアル通信用
	bool serial_available;//シリアル通信を行うか
	client_game_data();
};

using app = SceneManager<e_scene, client_game_data>;


void client_init();