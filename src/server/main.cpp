#include <iostream>
#include "utils.h"
#include "server.h"

net::Server server;
int command_callback(const std::vector<std::string>& args){
	if(args[0] == "stop"){
		server.stop();
		return 1;
	}
	else if(args[0] == "echo"){
		for(size_t i = 1; i < args.size(); ++i)
			std::cout << args[i] << ' ';
		std::cout << '\n';
	}
	else{
		std::cout << "command not found: " << args[0] << '\n';
	}
	return 0;
}

int main(int argc, char* argv[]){
	server.start(56744);	
	utils::handle_command(command_callback);
	server.stop();
	return 0;
}
