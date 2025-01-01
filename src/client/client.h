#ifndef CLIENT_H
#define CLIENT_H

#define ASIO_NO_DEPRECATED

#include <asio.hpp>
#include <thread>

namespace net{
	using std::string;
	using asio::ip::tcp;
	using std::runtime_error;
	using socket_ptr = std::shared_ptr<tcp::socket>;

class Client{
private:
	asio::io_context io_context;	
	tcp::resolver resolver;
	std::thread io_context_thread;
	bool is_running = false;

public:
	explicit Client()noexcept;
	Client(const Client& other) = delete;
	Client operator=(const Client& other) = delete;
	~Client();

	void start(const string& host, const string& port);
	void stop();

private:
	void start_connect(const string& host, const string& port);
	void inline start_resolved_connect(socket_ptr socket, 
			tcp::resolver::results_type results);
};
}

#endif//CLIENT_H
