//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_BASEHANDLER_HPP
#define LIBHTTP_BASEHANDLER_HPP

#include <spdlog/spdlog.h>
#include "string"
#include "libhttp/Response.hpp"

namespace libhttp {
	struct BaseHandler {
		std::string path = "/api/([0-9]+)";

		[[nodiscard]] Response receive(const Headers &headers, const std::string &body) const {
			for (auto &[key, value]: headers) {
				spdlog::info("key: {0} value: {1}", key, value);
			}
			spdlog::info("\n\n{0}", body);
			return {200, {{"Content-Type", "text/plain"}}, "this is Base Handler"};
		}
	};

}


#endif //LIBHTTP_BASEHANDLER_HPP
