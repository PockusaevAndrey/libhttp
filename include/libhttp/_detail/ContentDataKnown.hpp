//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_CONTENTDATAKNOWN_HPP
#define LIBHTTP_CONTENTDATAKNOWN_HPP

#include "libhttp/_detail/Resource.hpp"
#include "libhttp/_detail/Writer.hpp"
#include "ResponseGenerator.hpp"


namespace libhttp::_detail {
	template<concepts::io_socket Socket, concepts::handleable ...Handler>
	void contentDataKnown(Socket& socket, ParsedHeaders &headers, std::string &content) {
		Resource<Handler...> res(headers, content);
		auto response = res();

		writer(socket,
		       generateResponse(response, headers["Request-Path"], headers["Request-Version"], headers["Request-Type"]));
	};

}

#endif //LIBHTTP_CONTENTDATAKNOWN_HPP
