//
// Created by pokys on 03.11.2022.
//

#include "libhttp/_detail/HeaderParser.hpp"
#include <spdlog/spdlog.h>

namespace libhttp::_detail {
	std::vector<std::string> split(std::string &str, const std::string &token) {
		std::vector<std::string> result;
		while (!str.empty()) {
			unsigned long index = str.find(token);
			if (index != std::string::npos) {
				result.push_back(str.substr(0, index));
				str = str.substr(index + token.size());
				if (str.empty())result.push_back(str);
			} else {
				result.push_back(str);
				str = "";
			}
		}
		return result;
	}

	ParsedHeaders headerParser(std::string &not_parsed_headers) {
		ParsedHeaders result;
		for (auto &header: split(not_parsed_headers, "\r\n")) {
			auto key_value = split(header, ": ");
			if (key_value.size() == 2)
				result[key_value[0]] = key_value[1];
			else if (key_value.size() == 1) {
				auto type_path_version = split(key_value[0], " ");
				if (type_path_version.size() == 3) {
					result["Request-Type"] = type_path_version[0];
					result["Request-Path"] = type_path_version[1];
					result["Request-Version"] = type_path_version[2];
				}
				else{
					std::string body;
					for(int i = 0; i < type_path_version.size(); i++) {
						if (i == type_path_version.size()-1) {
							body+=type_path_version[i];
							break;
						}
						body += type_path_version[i] + " ";

					}
					result["Header-Parsed-Data"] = body;
				}
			}
		}
		return result;
	}
} // _detail