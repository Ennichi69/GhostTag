#include"Client_Common.hpp"

client_game_data::client_game_data() {
	const Array<SerialPortInfo>infos = System::EnumerateSerialPorts();
	serial_available = false;
	for (auto i : infos) {
		if (serial.open(i.port)) {
			serial_available = true;
			break;
		}
	}
}

void client_init() {
}