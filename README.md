# The libhttp reference manual

## Introducion

libhttp is fast and simple http library to build HTTP servers with REST fashion. the purpose of the library is to
provide the fastest possible access to the network, based on modern C++ approaches

## Requirements

- g++ >=10.3.0
- spdlog >= 1.5.0
- fmt >=6.1.2

## Building

libhttp uses standard system where the usual build process involves running

> mkdir build \
> cd build \
> cmake .. \
> cmake --build . \
> make install # (optionally to install on the system)

## Getting Started

The most basic example of creating a server and handling a requests for the path `/hello`

```c++
#include <httpserver.hpp>

using namespace libhttp;
class HelloHandler{
public:
	std::string path = "/hello";
	Response receive(const Headers& headers, const std::string& body){
		return {200, {/*No headers. default content-type: text/plain*/}, "Hello world!!"};
	}
};

int main(int argc, char** argv){
	Server<HelloHandler> server{8080};
	server.run();
	return 0;
}
```

To test the above example, you could run the following command from a terminal:

``` bash
curl -XGET -v http://localhost:8080/hello
```

## Create Custom header

To use your class with libhttp::Server, you need to add to the public domain:

```c++
public:
    std::string path = "<path on the server>";
    Response receive(const Headers& headers, const std::string& body);
```



