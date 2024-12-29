#ifndef SERVER_H
#define SERVER_H

#include <asio.hpp>
#include <cstdint>

namespace net{
	using asio::ip::tcp;
	using std::runtime_error;

class Server{
private:
	asio::io_context io_context;	
	tcp::acceptor acceptor;
	uint16_t port;

public:
	Server(uint16_t port);
	Server(const Server& other) = delete;
	Server operator=(const Server& other) = delete;
	~Server();

	void start();

private:
	void acceptor_init();
	void start_accept();
};
}

#endif//SERVER_H
