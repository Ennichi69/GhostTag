#include"Server_Common.hpp"

server_game_data::server_game_data() {
	const Array<SerialPortInfo>infos = System::EnumerateSerialPorts();
	serial_available = false;
	for (auto i : infos) {
		if (serial.open(i.port)) {
			serial_available = true;
			break;
		}
	}
}

void server_init() {
}