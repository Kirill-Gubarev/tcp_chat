#include "server.h"
#include <iostream>

net::Server::Server() noexcept:
	io_context(), acceptor(io_context)
{

}

net::Server::~Server(){
	stop();
}

void net::Server::start(uint16_t port){
	if(is_running) return;
	is_running = true;
	std::cout << "starting the server...\n";

	acceptor_init(port);
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

void net::Server::acceptor_init(uint16_t port){
	asio::error_code ec;
		
	acceptor.open(tcp::v4(), ec);
	if(ec) stop("opening connection error: " + ec.message());

    acceptor.bind(tcp::endpoint(tcp::v4(), port), ec);
	if(ec) stop("binding connection error: " + ec.message());

    acceptor.listen(asio::socket_base::max_listen_connections, ec);
	if(ec) stop("listening connection error: " + ec.message());
}
void net::Server::start_accept(){
	acceptor.async_accept(
		[this](const asio::error_code& ec, tcp::socket socket){
			if(!ec){
				std::cout << "accepted new connection!\n";
				Session(std::move(socket)).start();
			}
			else{
				std::cout << "error accepting: " + ec.message() + '\n';
			}
			start_accept();
		}
	);	
}
