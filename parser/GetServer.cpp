#include "GetServer.hpp"

std::string GetServer::parseServerName(const std::string& host) {

	std::string res;
	size_t pos = host.find(':');
	if (pos == std::string::npos)
		return host;
	res = host.substr(0,pos);
	return res;
}

const ServerConfig* GetServer::chooseServer(Connect* conn,
											const std::vector <const ServerConfig*>& config) {

	std::string reqServerName = parseServerName(conn->head.get("host"));
	for (std::vector<const ServerConfig*>::const_iterator it = config.begin();
		 it != config.end(); ++it) {
		std::set<std::string> serverNames = (*it)->getServerNames();
		for (std::set<std::string>::iterator iter = serverNames.begin(); iter
		!= serverNames.end(); ++iter) {
			if (*iter == reqServerName)
				return &(**it);
		}
	}
	return &(*config[0]);
}

bool GetServer::checkHTTPMethodAllowed(const std::string& method,
									   const Route* route) {
	std::set<std::string> HTTPmethods = route->getHTTPmethods();
	for (std::set<std::string>::iterator
				 it = HTTPmethods.begin(); it != HTTPmethods.end(); ++it) {
		if (*it == method)
			return true;
	}
	return false;
}

void GetServer::getConfigInformation(Connect* conn,
									 const std::vector <const ServerConfig*>& config) {

	if (conn->head.get("http") != "HTTP/1.1")
		throw std::runtime_error("505");
	std::string method = conn->head.get("method");
	const ServerConfig* server = chooseServer(conn, config);
	std::string HTTPmethod = conn->head.get("method");
	if (HTTPmethod != "GET" && HTTPmethod != "HEAD" && HTTPmethod != "PUT" &&
	HTTPmethod != "POST" && HTTPmethod != "DELETE")
		throw std::runtime_error("501");
	const std::vector<Route>& vecRoute = server->getServerRoutes();
	const Route* res = &(vecRoute.front());
	std::string uri = conn->head.get("uri");
	if (uri.length() > 8192)
		throw std::runtime_error("414");
	if (uri.empty() || uri == "/") {
		if (!checkHTTPMethodAllowed(method, res))
			throw std::runtime_error("405");
		conn->location = res;
		return;
	}
	size_t maxLen = 0;
	for (std::vector<Route>::const_iterator it = vecRoute.begin(); it !=
													vecRoute.end(); ++it) {
		std::string route = it->getRoute();
		if (uri.length() != route.length() && route[route.length() - 1] != '/')
			route += '/';
		size_t len = route.length();
		if (len > uri.size())
			continue;
		std::string bufUri = uri.substr(0, len);
		if (bufUri == route && len > maxLen) {
			maxLen = len;
			res = &(*it);
		}
	}
	if (!checkHTTPMethodAllowed(method, res))
		throw std::runtime_error("405");
	if (conn->body.len() > static_cast<size_t>(res->getLimitBodySize()))
		throw std::runtime_error("413");
	conn->location = res;
}