#include"Server_Common.hpp"

server_game_data::server_game_data() {
	const Array<SerialPortInfo>infos = System::EnumerateSerialPorts();
	serial_available = true;
	if (infos.size() == 1) {
		if (!serial.open(infos[0].port)) {
			serial_available = false;
		}
	}
	else {
		serial_available = false;
	}
}

void server_init() {
}