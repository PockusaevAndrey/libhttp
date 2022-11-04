//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_HEADERDATKNOWN_HPP
#define LIBHTTP_HEADERDATKNOWN_HPP

#include "libhttp/_detail/HeaderParser.hpp"
#include "libhttp/_detail/ContentReader.hpp"

namespace libhttp::_detail {
	template<concepts::io_socket Socket, concepts::handleable ...Handler>
	void headerDataKnown(Socket& socket, std::string &raw_data) {
		// region process
		ParsedHeaders headers = headerParser(raw_data);
		// endregion
		contentReader<Socket, Handler...>(socket, headers);
	}


}


#endif //LIBHTTP_HEADERDATKNOWN_HPP
