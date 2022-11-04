//
// Created by pokys on 03.11.2022.
//

#ifndef LIBHTTP_WRITER_HPP
#define LIBHTTP_WRITER_HPP


#include "libhttp/_detail/concepts/socket_concept.hpp"

namespace libhttp::_detail {
		template<concepts::io_socket Socket>
		void writer(Socket& socket, const std::string& data){
			socket.write(data);
			spdlog::debug(data);
		};
} // _detail

#endif //LIBHTTP_WRITER_HPP
