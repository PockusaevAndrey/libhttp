//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_SOCKET_HPP
#define LIBHTTP_SOCKET_HPP

#include <string>

namespace libhttp::_detail {
	class socket {
	public:
		int id{1};
		std::string read(){return {};}
		void write(){}
	};

}

#endif //LIBHTTP_SOCKET_HPP
