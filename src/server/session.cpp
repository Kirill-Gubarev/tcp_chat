#include "session.h"

net::Session::Session(tcp::socket&& socket):
	socket(std::move(socket)){
		
}

void net::Session::start(){
		
}
