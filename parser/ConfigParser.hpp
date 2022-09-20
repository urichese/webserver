#ifndef WEBSERV_CONFIGPARSER_HPP
#define WEBSERV_CONFIGPARSER_HPP

#include <iostream>
#include <vector>
#include <cctype>
#include <stdexcept>
#include "ServerConfig.hpp"
#include "utils.hpp"

class ConfigParser {

private:
	std::string					_config_name;
	std::vector<ServerConfig>	_servers_config;

public:
	explicit ConfigParser(const std::string& config_name);
	~ConfigParser();

	void ParsingProcess();
	const std::vector<ServerConfig>& getVectorOfServers() const;

private:
	ConfigParser();
	void	parseServerPreporation(std::ifstream& file);
};

#endif