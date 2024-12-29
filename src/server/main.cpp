#include <iostream>
#include "server.h"

int main(int argc, char* argv[]){
	net::Server server(56744);
	try{
		server.start();	
	}
	catch(std::exception& ex){
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}
