#include"Client_Common.hpp"

client_game_data::client_game_data() {
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

void client_init() {
}