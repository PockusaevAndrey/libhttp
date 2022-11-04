//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_HEADERREADER_HPP
#define LIBHTTP_HEADERREADER_HPP


#include "libhttp/_detail/HeaderDataKnown.hpp"


namespace libhttp::_detail {
	template<concepts::io_socket Socket, concepts::handleable ...Handler>
	void headerReader(Socket& socket){
		// region read headers
		std::string data;
		while(data.find("\r\n\r\n") == std::string::npos){
			data += socket.read(64);
		}
		spdlog::debug(data);
		// endregion
		headerDataKnown<Socket, Handler...>(socket, data);
	};
}


#endif //LIBHTTP_HEADERREADER_HPP
