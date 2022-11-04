//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_CONTENTREADER_HPP
#define LIBHTTP_CONTENTREADER_HPP

#include "libhttp/_detail/ContentDataKnown.hpp"

namespace libhttp::_detail {
	template<concepts::io_socket Socket, concepts::handleable ...Handler>
	void contentReader(Socket& socket, ParsedHeaders &headers) {
		std::string body;
		if (headers.contains("Header-Parsed-Data")) {
			body += headers.at("Header-Parsed-Data");
		}

		body = headers.contains("Content-Length") ? body + socket.read(
				std::stoi(headers.at("Content-Length")) - body.length())
		                                          : std::string{};
		contentDataKnown<Socket, Handler...>(socket, headers, body);
	}
} // _detail

#endif //LIBHTTP_CONTENTREADER_HPP
