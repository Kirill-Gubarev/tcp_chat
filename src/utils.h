#ifndef UTILS_H
#define UTILS_H

#include <vector>
#include <string>

namespace utils{
	void handle_command(int(&command_callback)(const std::vector<std::string>& args));
}

#endif//UTILS_H
