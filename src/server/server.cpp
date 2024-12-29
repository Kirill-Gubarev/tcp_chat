#include "server.h"
#include <iostream>

net::Server::Server(uint16_t port):
	io_context(), acceptor(io_context),
	port(port)
{

}

net::Server::~Server(){}

void net::Server::start(){
	std::cout << "starting the server..." << std::endl;
	acceptor_init();
	start_accept();
	io_context.run();
}

void net::Server::acceptor_init(){
	asio::error_code ec;
		
	acceptor.open(tcp::v4(), ec);
	if(ec) throw runtime_error("opening connection error: " + ec.message());

    acceptor.bind(tcp::endpoint(tcp::v4(), port));
	if(ec) throw runtime_error("binding connection error: " + ec.message());

    acceptor.listen(asio::socket_base::max_listen_connections, ec);
	if(ec) throw runtime_error("listening connection error: " + ec.message());
}
void net::Server::start_accept(){
	auto socket = std::make_shared<tcp::socket>(io_context);

	acceptor.async_accept(*socket, 
		[this, socket](const asio::error_code& ec){
			if(!ec){
				std::cout << "accepted new connection!" << std::endl;
			}
			else{
				std::cerr << "error accepting: "<< ec.message() << std::endl;
			}
			start_accept();
		}
	);	
}
