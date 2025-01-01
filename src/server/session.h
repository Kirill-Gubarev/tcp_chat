#ifndef SESSION_H
#define SESSION_H

#define ASIO_NO_DEPRECATED
#include <asio.hpp>

namespace net{
using asio::ip::tcp;

class Session{
private:
	tcp::socket socket;

public:
	explicit Session(tcp::socket&& socket);
	void start();
};
}

#endif//SESSION_H
