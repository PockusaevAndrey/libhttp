//
// Created by pokys on 03.11.2022.
//

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunknown-escape-sequence"
#ifndef LIBHTTP_RESOURCE_HPP
#define LIBHTTP_RESOURCE_HPP

#include "regex"
#include "libhttp/Response.hpp"
#include "libhttp/_detail/concepts/handler.hpp"

namespace libhttp::_detail {
	template<concepts::handleable ...Handler>
	struct Resource {
		Response resp;

		Resource(ParsedHeaders &headers, std::string &content) {
			([](const Handler &handler, Response &response, ParsedHeaders &headers, std::string &content) {
				try {
					std::regex handler_expr(handler.path + "([/]?)$");
					std::smatch queryParamMatch;
					if (std::regex_match(headers["Request-Path"], queryParamMatch, handler_expr)) {
						for(int i = 1; i < queryParamMatch.size()-1; i++){
							headers[fmt::format("PP-{0}", i-1)] = queryParamMatch[i].str();
						}
						response = handler.receive(headers, content);

					}
				} catch (std::exception &e){
					spdlog::error(e.what());
				}
			}(Handler(), resp, headers, content), ...);
		}

		Response operator()() {
			return resp;
		}
	};

} // _detail

#endif //LIBHTTP_RESOURCE_HPP

#pragma clang diagnostic pop