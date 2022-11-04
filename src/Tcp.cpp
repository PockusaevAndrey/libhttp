//
// Created by GodPC on 03.11.2022.
//

#include <unistd.h>
#include "libhttp/_detail/Tcp.hpp"


namespace libhttp::_detail {
	TCP::TCP(int descriptor) : _s(descriptor) {}

	std::string TCP::read(size_t len) const {
		auto buffer = new char[len];
		auto wasRead = recv(_s, buffer, len, MSG_DONTWAIT);

//		if (wasRead != len) {
//			spdlog::error("error of reading data");
////			throw std::runtime_error("error of reading data");
//		}
		std::string result;
		for (int i = 0; i < wasRead; ++i) {
			if (buffer[i] == '\0')
				break;
			result += buffer[i];
		}
		delete[] buffer;
		return result;
	}

	void TCP::write(const std::string &buffer) const {
		auto wasSend = send(_s, buffer.c_str(), buffer.length() + 1, 0);

		if (wasSend >= 0) {
			if (wasSend != buffer.length() + 1) {
				spdlog::error("error of sending data");
//				throw std::runtime_error("error of sending data");
			}
		} else {
			spdlog::error("socket return -1 to send data");
//			throw std::runtime_error("socket return -1 to send data");
		}
	}

	TCP::~TCP() {
		close(_s);
	}
} // libhttp
