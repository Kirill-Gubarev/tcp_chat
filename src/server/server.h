#ifndef SERVER_H
#define SERVER_H

#define ASIO_NO_DEPRECATED

#include <asio.hpp>
#include <cstdint>
#include <thread>

namespace net{
	using asio::ip::tcp;
	using std::runtime_error;
	using std::string;

class Server{
private:
	asio::io_context io_context;	
	tcp::acceptor acceptor;
	uint16_t port;
	std::thread io_context_thread;
	bool is_running = false;

public:
	Server(uint16_t port);
	Server(const Server& other) = delete;
	Server operator=(const Server& other) = delete;
	~Server();

	void start();
	void stop();
	void stop(const string& message);

private:
	void acceptor_init();
	void start_accept();
};
}

#endif//SERVER_H
