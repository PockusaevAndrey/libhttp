//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_RESPONSE_HPP
#define LIBHTTP_RESPONSE_HPP

#include "libhttp/_detail/HeaderParser.hpp"

namespace libhttp {
	using Headers = _detail::ParsedHeaders;

	struct Response {
		int status_code;
		Headers headers;
		std::string body;
	};
}


#endif //LIBHTTP_RESPONSE_HPP
