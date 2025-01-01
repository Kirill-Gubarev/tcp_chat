#include "session.h"
#include <iostream>

using asio::ip::tcp;

net::Session::Session(asio::io_context& io_context)noexcept:
	socket(io_context) {}
net::Session::Session(tcp::socket&& socket)noexcept:
	socket(std::move(socket)) {}
net::Session::Session(Session&& other)noexcept:
	socket(std::move(other.get_socket())) {}

net::Session::~Session()noexcept{
	socket.close();
}

tcp::socket& net::Session::get_socket()noexcept{
	return socket;
}
void net::Session::start(){
	start_read();		
}

void net::Session::start_read(){
	socket.async_read_some(asio::buffer(read_buffer, BUFFER_SIZE),
		[this](asio::error_code ec, size_t lenght){
			if(!ec){
				std::cout.write(read_buffer, lenght);		
			}
			else{
				std::cout << "receving error: " + ec.message() + "\n";			
			}
			start_read();
		}
	);
}

void net::Session::start_write(const string& message){
	asio::async_write(socket, asio::buffer(message),
		[this](asio::error_code ec, size_t lenght){
			if(!ec) 
				std::cout << lenght << " bytes sended\n";
			else
				std::cout << "sending error: " + ec.message() + "\n";
		}
	);
}
