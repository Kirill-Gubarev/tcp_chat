#include <iostream>
#include "client.h"

int main(int argc, char* argv[]){
	net::Client client("127.0.0.1", "56744");
	try{
		client.start();
	}
	catch(std::exception& ex){
		std::cerr << ex.what() << std::endl;
	}
	return 0;
}
