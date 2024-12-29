#include "client.h"
#include <iostream>

net::Client::Client(string host, string port):
	io_context(), resolver(io_context),
	host(host), port(port)
{

}

net::Client::~Client(){}

void net::Client::start(){
	std::cout << "starting the client..." << std::endl;	
	start_connect();	
	io_context.run();
}
void net::Client::start_connect(){
	auto socket = std::make_shared<tcp::socket>(resolver.get_executor());

    resolver.async_resolve(host, port, 
        [this, socket](const asio::error_code& ec, tcp::resolver::results_type results) {
            if(!ec){
				start_resolved_connect(socket, results);
            }
			else{
                std::cerr << "resolving error: " << ec.message() << "\n";
            }
        }
    );
}

void net::Client::start_resolved_connect(socket_ptr socket, 
			tcp::resolver::results_type results)
{
	asio::async_connect(*socket, results,
		[this, socket](const asio::error_code& ec, const tcp::endpoint& endpoint) {
			if (!ec) {
				std::cout << "connected to: " << endpoint << "\n";
			}
			else {
				std::cerr << "connecting error: " << ec.message() << "\n";
			}
		}
	);
}
