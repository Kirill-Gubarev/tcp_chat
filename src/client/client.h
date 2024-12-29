#ifndef CLIENT_H
#define CLIENT_H

#include <asio.hpp>

namespace net{
	using std::string;
	using asio::ip::tcp;
	using std::runtime_error;
	using socket_ptr = std::shared_ptr<tcp::socket>;

class Client{
private:
	asio::io_context io_context;	
	tcp::resolver resolver;
	string host, port;

public:
	Client(string host, string port);
	Client(const Client& other) = delete;
	Client operator=(const Client& other) = delete;
	~Client();

	void start();

private:
	void start_connect();
	void inline start_resolved_connect(socket_ptr socket, 
			tcp::resolver::results_type results);
};
}

#endif//CLIENT_H
