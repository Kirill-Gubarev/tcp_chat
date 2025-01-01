#ifndef SERVER_H
#define SERVER_H

#define ASIO_NO_DEPRECATED
#include <asio.hpp>

#include <cstdint>
#include <thread>
#include "session.h"
#include <vector>

namespace net{
	using asio::ip::tcp;
	using std::runtime_error;
	using std::string;

class Server{
private:
	asio::io_context io_context;	
	tcp::acceptor acceptor;
	std::thread io_context_thread;
	bool is_running = false;
	std::vector<std::unique_ptr<Session>> sessions;

public:
	explicit Server() noexcept;
	Server(const Server& other) = delete;
	Server operator=(const Server& other) = delete;
	~Server();

	void start(uint16_t port);
	void stop();
	void stop(const string& message);

private:
	void acceptor_init(uint16_t port);
	void start_accept();
};
}

#endif//SERVER_H
