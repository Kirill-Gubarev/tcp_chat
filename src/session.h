#ifndef SESSION_H
#define SESSION_H

#define ASIO_NO_DEPRECATED
#include <asio.hpp>

namespace net{
	using asio::ip::tcp;
	using std::string;

class Session{
private:
	tcp::socket socket;

#define BUFFER_SIZE 1024
	char read_buffer[BUFFER_SIZE];

public:
	explicit Session(asio::io_context& io_context)noexcept;
	explicit Session(tcp::socket&& socket)noexcept;
	explicit Session(Session&& other)noexcept;
	~Session()noexcept;
	
	tcp::socket& get_socket()noexcept;

	void start();


	void start_write(const string& message);
private: 
	void start_read();
};
}

#endif//SESSION_H
