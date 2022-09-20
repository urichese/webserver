#ifndef WEBSERV_GETSERVER_HPP
#define WEBSERV_GETSERVER_HPP

#include "ServerConfig.hpp"
#include "Route.hpp"
#include "../http/Connect.hpp"
#include "utils.hpp"

class GetServer {

public:
	void getConfigInformation(Connect* conn, const std::vector<const ServerConfig*>&
		config);
	const ServerConfig* chooseServer(Connect* conn,
												const std::vector
												        <const ServerConfig*>& config);

private:
	int checkServerIPs(in_addr_t reqIP, int reqPort,
					   std::vector<std::pair<in_addr_t, int> >& confReqAddr);
	bool checkHTTPMethodAllowed(const std::string& method, const Route* route);
	std::string parseServerName(const std::string& host);
};


#endif
