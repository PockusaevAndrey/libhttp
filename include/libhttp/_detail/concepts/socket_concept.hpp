//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_SOCKET_CONCEPT_HPP
#define LIBHTTP_SOCKET_CONCEPT_HPP

#include "concepts"
#include "string"


namespace libhttp::_detail::concepts {
	template<typename T>
	concept io_socket = requires(T t, const std::string &buffer, size_t len) {
		{ t.read(len) }/* -> std::convertible_to<std::string>*/;
		{ t.write(buffer) };
	};
}

#endif //LIBHTTP_SOCKET_CONCEPT_HPP
