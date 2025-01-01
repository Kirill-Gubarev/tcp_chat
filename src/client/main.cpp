#include <iostream>
#include "client.h"
#include "utils.h"

net::Client client;

int command_callback(const std::vector<std::string>& args){
	if(args[0] == "stop"){
		client.stop();
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
	client.start("127.0.0.1", "56744");
	
	utils::handle_command(command_callback);

	client.stop();
	return 0;
}
