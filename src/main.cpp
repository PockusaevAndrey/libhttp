#include <iostream>
#include "libhttp.hpp"
#include "BaseHandler.hpp"

int main() {
	libhttp::Server<libhttp::BaseHandler> server = 8080;
	std::cout << "Hello, World!" << std::endl;
	server.run();
	return 0;
}
