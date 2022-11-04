//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_RESPONSEGENERATOR_HPP
#define LIBHTTP_RESPONSEGENERATOR_HPP

#include "string"
#include "libhttp/Response.hpp"
#include "fmt/format.h"

namespace libhttp::_detail {

	std::string	generateResponse(
			Response &response, const std::string &path, const std::string &version, const std::string &type);

} // _detail

#endif //LIBHTTP_RESPONSEGENERATOR_HPP
