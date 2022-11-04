//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_SERVER_HPP
#define LIBHTTP_SERVER_HPP

#include "libhttp/_detail/Listener.hpp"

namespace libhttp {
	template<_detail::concepts::handleable ...Handlers>
	class Server {
		libhttp::_detail::Listener<Handlers...> listener;
	public:
		Server(int port) : listener(port, 5) {

		}

		[[noreturn]] void run() {
			listener.run();
		}
	};

} // libhttp

#endif //LIBHTTP_SERVER_HPP
