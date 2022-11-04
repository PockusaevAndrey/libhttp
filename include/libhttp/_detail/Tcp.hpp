//
// Created by GodPC on 03.11.2022.
//

#ifndef LIBHTTP_TCP_HPP
#define LIBHTTP_TCP_HPP

#include <string>
#include <sys/socket.h>
#include <spdlog/spdlog.h>
#include "libhttp/_detail/HeaderReader.hpp"


namespace libhttp::_detail {

	class TCP {
		int _s;

		explicit TCP(int descriptor);

	public:
		[[nodiscard]] std::string read(size_t len) const;

		void write(const std::string &buffer) const;

		~TCP();

		template<concepts::handleable ...Handlers>
		friend class Listener;

	};

} // libhttp _detail

#endif //LIBHTTP_TCP_HPP