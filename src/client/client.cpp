#include "client.h"
#include <iostream>

net::Client::Client(const string& host, const string& port):
	io_context(), resolver(io_context),
	host(host), port(port)
{

}

net::Client::~Client(){}

void net::Client::start(){
	if(is_running) return;
	is_running = true;

	std::cout << "starting the client...\n";	

	start_connect();	
	io_context_thread = std::thread(&asio::io_context::run, &io_context);
	io_context_thread.detach();
}
void net::Client::stop(){
	if(!is_running) return;
	is_running = false;

	std::cout << "stopping the client...\n";

	io_context.stop();
}
void net::Client::start_connect(){
	auto socket = std::make_shared<tcp::socket>(resolver.get_executor());

    resolver.async_resolve(host, port, 
        [this, socket](const asio::error_code& ec, tcp::resolver::results_type results) {
            if(!ec){
				start_resolved_connect(socket, results);
            }
			else{
                std::cout << "resolving error: " + ec.message() + '\n';
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
				std::cout << "connected!\n";
			}
			else {
				std::cout << "connecting error: " + ec.message() + '\n';
			}
		}
	);
}
