#include "utils.h"
#include <sstream>
#include <iostream>

namespace utils{
	void read_command(std::vector<std::string>& args);
}
void utils::handle_command(int(&command_callback)(const std::vector<std::string>& args)){
	std::vector<std::string> args(0);
	while(true){
		std::cout << ">> ";
		utils::read_command(args);
		if(args.empty()) continue;

		if(command_callback(args) == 1) return;
	}
}
void utils::read_command(std::vector<std::string>& args){
	args.clear();
	std::string str;
	bool repeat = true;
	while(repeat){
		repeat = false;

		std::getline(std::cin, str);
		if(str.back() == '\\') {
			str.pop_back();
			repeat = true;
		}
		std::istringstream iss(str);

		while(iss >> str){
			args.push_back(str);
		}
	}
}
