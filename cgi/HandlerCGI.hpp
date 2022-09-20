#ifndef WEBSERV_HANDLERCGI_HPP
#define WEBSERV_HANDLERCGI_HPP

#include <vector>
#include <map>
#include <iostream>
#include <cstdio>
#include <unistd.h>
# include <sys/fcntl.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <sys/types.h>
# include <sys/socket.h>
# include "ServerConfig.hpp"
# include "Content.hpp"
# include "Connect.hpp"
# include "RequestBody.hpp"

class HandlerCGI {

public:
	void handleCGI(Connect* conn, std::string const &path_interpritator,
				   std::string& head, AContent* body);
	std::string getInterpretator(Connect *conn);

private:
	std::string getServerNameFromHost(const std::string& host);
	std::string getPortFromHost(const std::string& host);
	std::string getScriptFromPath(const std::string& path);
	std::string myToString(int num);
	std::string	form_env_string(std::string name, std::string param);
	std::vector<std::string> init_env(Connect* conn);
	char**	form_env(std::vector<std::string>& arrEnv);

};


#endif
