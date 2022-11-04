//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_HANDLER_HPP
#define LIBHTTP_HANDLER_HPP

#include "concepts"

namespace libhttp {
	class Response;
	namespace _detail::concepts {
		template<typename T>
		concept handleable = requires(T t, const std::string &body, const ParsedHeaders &headers){
			{ t.path } -> std::convertible_to<std::string>;
			{ t.receive(headers, body) } ->std::convertible_to<Response>;
		};
	}
}
#endif //LIBHTTP_HANDLER_HPP
