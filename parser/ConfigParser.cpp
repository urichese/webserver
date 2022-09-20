#include "ConfigParser.hpp"

ConfigParser::ConfigParser(const std::string& config_name) :
	_config_name(config_name),
	_servers_config() {}

ConfigParser::~ConfigParser() {}

void ConfigParser::parseServerPreporation(std::ifstream& file) {

	_servers_config.push_back(ServerConfig());
	try {
		_servers_config.back().parseServer(file);
	}
	catch (std::logic_error& e) {
		throw;
	}
}

void ConfigParser::ParsingProcess() {

	std::ifstream file(_config_name);
	if (!file)
		throw std::logic_error("Config open error");
	std::string str;
	while (std::getline(file, str)) {
		if (str.empty())
			continue ;
		std::vector<std::string> command = str_split(str);
		if (command[0] != "server")
			throw std::logic_error("Config syntax error");
		if (command[1] == "{") {
			try {
				parseServerPreporation(file);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command.size() != 1) {
			throw std::logic_error("Symbols after server");
		}
		else {
			while (std::getline(file, str)) {
				if (str.empty())
					continue ;
				if (str == "{") {
					try {
						parseServerPreporation(file);
						break ;
					}
					catch (std::logic_error& e) {
						throw;
					}
				}
				else
					throw std::logic_error("Symbols before opening brackets");
			}
		}
	}
}

const std::vector<ServerConfig>& ConfigParser::getVectorOfServers() const {
	return _servers_config;
}