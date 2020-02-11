#include "SocketHelper.h"

int main(void)
{
	// Start client to get data from socket
	auto client_ = std::make_unique<SocketHelper>(9605);

	while (1) {
		fmt::print("Received value: {}.\n", client_->Get_AoA());
		std::this_thread::sleep_for(std::chrono::milliseconds(1));
	}
	return 0;
}