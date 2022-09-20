#ifndef WEBSERV_UTILS_HPP
#define WEBSERV_UTILS_HPP

#include <iostream>
#include <vector>

std::vector<std::string>	str_split(const std::string& str);
int 						str_to_int(const std::string& str);
std::vector<std::string>	strSplitBySlash(const std::string& str);

#endif //WEBSERV_UTILS_HPP
