#ifndef CLIENT_H
#define CLIENT_H

#define ASIO_NO_DEPRECATED

#include <asio.hpp>
#include <thread>
#include "session.h"

namespace net{
	using std::string;
	using asio::ip::tcp;
	using std::runtime_error;

class Client{
private:
	asio::io_context io_context;	
	tcp::resolver resolver;
	Session session;
	std::thread io_context_thread;
	bool is_running = false;

public:
	explicit Client()noexcept;
	Client(const Client& other) = delete;
	Client operator=(const Client& other) = delete;
	~Client();

	void start(const string& host, const string& port);
	void stop();
	void send(const string& message);

private:
	void start_connect(const string& host, const string& port);
	void inline start_resolved_connect(tcp::resolver::results_type results);
};
}

#endif//CLIENT_H
