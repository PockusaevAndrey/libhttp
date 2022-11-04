//
// Created by GodPC on 03.11.2022.
//

#ifndef LIBHTTP_LISTENER_HPP
#define LIBHTTP_LISTENER_HPP

#include <netinet/in.h>
#include <spdlog/spdlog.h>
#include <arpa/inet.h>
#include "Tcp.hpp"
#include "future"


namespace libhttp::_detail {
	template<concepts::handleable ...Handlers>
	class Listener {

		int _s;

		int _port;
		struct sockaddr_in _address{};

		bool _isListen;

		TCP accept_client() {
			if (!_isListen) {
				spdlog::error("listener must be init");
				throw std::runtime_error("listener must be init");
			}
			auto addrlen = sizeof (_address);
			auto descr = accept(_s, (struct sockaddr *) &_address, (socklen_t *) &addrlen);
			return TCP(descr);
		}
	public:
		Listener(int port, int count) : _port(port) {
			_s = socket(AF_INET, SOCK_STREAM, 0);
			int opt = 1;
			if (_s < 0) {
				spdlog::error("error of creating listen socket");
//				throw std::runtime_error("error of creating listen socket");
			}

			_address.sin_family = AF_INET;
			_address.sin_port = htons(_port);
			_address.sin_addr.s_addr = INADDR_ANY;

			if (setsockopt(_s, SOL_SOCKET,
			               SO_REUSEADDR | SO_REUSEPORT, &opt,
			               sizeof(opt))) {
				spdlog::error("error of setting opt");
				throw std::runtime_error("error of setting opt");
			}

			if (bind(_s, (struct sockaddr *) &_address, sizeof(_address)) < 0) {
				spdlog::error("error of binding listener socket");
				throw std::runtime_error("error of binding listener socket");
			}

			if (listen(_s, count) < 0) {
				spdlog::error("error of setting listen socket");
				throw std::runtime_error("error of setting listen socket");
			}

			_isListen = true;
		}

		[[noreturn]] void run(){
			while(true){
				auto cli = accept_client();
				auto result = std::async(std::launch::async, [&cliref=cli](){
					headerReader<TCP, Handlers...>(cliref);
					});
			}
		}
	};

} // libhttp _detail

#endif //LIBHTTP_LISTENER_HPP
