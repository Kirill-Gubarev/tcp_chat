#include "server.h"
#include <iostream>

net::Server::Server(uint16_t port):
	io_context(), acceptor(io_context),
	port(port)
{

}

net::Server::~Server(){}

void net::Server::start(){
	if(is_running) return;
	is_running = true;
	std::cout << "starting the server...\n";

	acceptor_init();
	start_accept();
	io_context_thread = std::thread(&asio::io_context::run, &io_context);
	io_context_thread.detach();
}
void net::Server::stop(){
	if(!is_running) return;
	is_running = false;
	std::cout << "stopping the server...\n";

	io_context.stop();
}
void net::Server::stop(const string& message){
	std::cout << message + '\n';
	stop();
}

void net::Server::acceptor_init(){
	asio::error_code ec;
		
	acceptor.open(tcp::v4(), ec);
	if(ec) stop("opening connection error: " + ec.message());

    acceptor.bind(tcp::endpoint(tcp::v4(), port), ec);
	if(ec) stop("binding connection error: " + ec.message());

    acceptor.listen(asio::socket_base::max_listen_connections, ec);
	if(ec) stop("listening connection error: " + ec.message());
}
void net::Server::start_accept(){
	auto socket = std::make_shared<tcp::socket>(io_context);

	acceptor.async_accept(*socket, 
		[this, socket](const asio::error_code& ec){
			if(!ec){
				std::cout << "accepted new connection!\n";
			}
			else{
				std::cout << "error accepting: " + ec.message() + '\n';
			}
			start_accept();
		}
	);	
}
