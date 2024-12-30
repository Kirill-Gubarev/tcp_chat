#include <iostream>
#include "client.h"

int main(int argc, char* argv[]){
	net::Client client("127.0.0.1", "56744");
	client.start();
	getchar(); //do something
	client.stop();
	return 0;
}
