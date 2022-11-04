
// Created by pokys on 03.11.2022.
//

#include "libhttp/_detail/ResponseGenerator.hpp"

namespace libhttp::_detail {
	std::string generateResponse(Response &response, const std::string &path, const std::string &version,
	                             const std::string &type) {
		if (!response.headers.contains("Server"))
			response.headers["Server"] = "libhttp";

		if (!response.headers.contains("Content-Type"))
			response.headers["Content-Type"] = "text/plain";

		if (!response.headers.contains("Connection"))
			response.headers["Connection"] = "keep-alive";

		if (!response.headers.contains("Transfer-Encoding"))
			response.headers["Transfer-Encoding"] = "chunked";

		std::string response_status;
		switch (response.status_code) {
			case 100:
				response_status = "100 Continue";
				break;
			case 101:
				response_status = "101 Switching Protocols";
				break;
			case 102:
				response_status = "102 Processing";
				break;
			case 103:
				response_status = "103 Early Hints";
				break;
			case 200:
				response_status = "200 OK";
				break;
			case 201:
				response_status = "201 Created";
				break;
			case 202:
				response_status = "202 Accepted";
				break;
			case 203:
				response_status = "203 No";
				break;
			case 204:
				response_status = "204 No Content";
				break;
			case 205:
				response_status = "205 Reset Content";
				break;
			case 206:
				response_status = "206 Partial Content";
				break;
			case 207:
				response_status = "207 Mult";
				break;
			case 208:
				response_status = "208 Already Reported";
				break;
			case 226:
				response_status = "226 IM Used";
				break;
			case 300:
				response_status = "300 Multiple Choices";
				break;
			case 301:
				response_status = "301 Moved Permanently";
				break;
			case 302:
				response_status = "302 Found";
				break;
			case 303:
				response_status = "303 See Other";
				break;
			case 304:
				response_status = "304 Not Modified";
				break;
			case 305:
				response_status = "305 Use Proxy";
				break;
			case 307:
				response_status = "307 Temporary Redirect";
				break;
			case 308:
				response_status = "308 Permanent Redirect";
				break;
			case 400:
				response_status = "400 Bad Request";
				break;
			case 401:
				response_status = "401 Unauthorized";
				break;
			case 402:
				response_status = "402 Payment Required";
				break;
			case 403:
				response_status = "403 Forbidden";
				break;
			case 404:
				response_status = "404 Not Found";
				break;
			case 405:
				response_status = "405 Method Not Allowed";
				break;
			case 406:
				response_status = "406 Not Acceptable";
				break;
			case 407:
				response_status = "407 Proxy Authentication Required";
				break;
			case 408:
				response_status = "408 Request Timeout";
				break;
			case 409:
				response_status = "409 Conflict";
				break;
			case 410:
				response_status = "410 Gone";
				break;
			case 411:
				response_status = "411 Length Required";
				break;
			case 412:
				response_status = "412 Precondition Failed";
				break;
			case 413:
				response_status = "413 Payload Too Large";
				break;
			case 414:
				response_status = "414 URI Too Long";
				break;
			case 415:
				response_status = "415 Unsupported Media Type";
				break;
			case 416:
				response_status = "416 Range Not Satisfiable";
				break;
			case 417:
				response_status = "417 Expectation Failed";
				break;
			case 418:
				response_status = "418 I’m a teapot";
				break;
			case 419:
				response_status = "419 Authentication Timeout";
				break;
			case 421:
				response_status = "421 Misdirected Request";
				break;
			case 422:
				response_status = "422 Unprocessable Entity";
				break;
			case 423:
				response_status = "423 Locked";
				break;
			case 424:
				response_status = "424 Failed Dependency";
				break;
			case 425:
				response_status = "425 Too Early";
				break;
			case 426:
				response_status = "426 Upgrade Required";
				break;
			case 428:
				response_status = "428 Precondition Required";
				break;
			case 429:
				response_status = "429 Too Many Requests";
				break;
			case 431:
				response_status = "431 Request Header Fields Too Large";
				break;
			case 449:
				response_status = "449 Retry With";
				break;
			case 451:
				response_status = "451 Unavailable For Legal Reasons";
				break;
			case 499:
				response_status = "499 Client Closed Request";
				break;
			case 500:
				response_status = "500 Internal Server Error";
				break;
			case 501:
				response_status = "501 Not Implemented";
				break;
			case 502:
				response_status = "502 Bad Gateway";
				break;
			case 503:
				response_status = "503 Service Unavailable";
				break;
			case 504:
				response_status = "504 Gateway Timeout";
				break;
			case 505:
				response_status = "505 HTTP Version Not Supported";
				break;
			case 506:
				response_status = "506 Variant Also Negotiates";
				break;
			case 507:
				response_status = "507 Insufficient Storage";
				break;
			case 508:
				response_status = "508 Loop Detected";
				break;
			case 509:
				response_status = "509 Bandwidth Limit Exceeded";
				break;
			case 510:
				response_status = "510 Not Extended";
				break;
			case 511:
				response_status = "511 Network Authentication Required";
				break;
			case 520:
				response_status = "520 Unknown Error";
				break;
			case 521:
				response_status = "521 Web Server Is Down";
				break;
			case 522:
				response_status = "522 Connection Timed Out";
				break;
			case 523:
				response_status = "523 Origin Is Unreachable";
				break;
			case 524:
				response_status = "524 A Timeout Occurred";
				break;
			case 525:
				response_status = "525 SSL Handshake Failed";
				break;
			case 526:
				response_status = "526 Invalid SSL Certificate";
				break;
		}

		std::string response_headers;
		for (auto &[key, value]: response.headers)
			response_headers += fmt::format("{0}: {1}\r\n", key, value);


		return fmt::format("{0} {1}\r\n{2}\r\n{4:x}\r\n{3}\r\n0\r\n\r\n",
		                   version, response_status, response_headers, response.body, response.body.length());
	}
} // _detail