#include <iostream>
#include "server.h"

int main(int argc, char* argv[]){
	net::Server server(56744);
	server.start();	

	getchar(); //do something

	server.stop();
	return 0;
}
