//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_HEADERPARSER_HPP
#define LIBHTTP_HEADERPARSER_HPP

#include "unordered_map"
#include "string"

namespace libhttp::_detail {

	using ParsedHeaders = std::unordered_map<std::string, std::string>;

	ParsedHeaders headerParser(std::string& not_parsed_headers);

} // _detail

#endif //LIBHTTP_HEADERPARSER_HPP
