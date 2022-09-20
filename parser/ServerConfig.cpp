#include "ServerConfig.hpp"

ServerConfig::ServerConfig() :
	_request_address(),
	_server_names(),
	_error_pages(),
	_default_pages(),
	_root("/www"),
	_routes(),
	_cgi() {

	_request_address.push_back(std::pair<in_addr_t, int>
	        (inet_addr("0.0.0.0"), 80));
	_default_pages.insert("index.html");
	_server_names.insert(std::string());
	_routes.push_back(Route(_root, _default_pages, _error_pages, _cgi));
}

ServerConfig::~ServerConfig() {}

void ServerConfig::parseRequestAddress(std::vector<std::string>& command) {

	if (command.size() == 1)
		throw std::logic_error("Config syntax error in listen");
	for (size_t i = 1; i < command.size(); ++i) {
		if (i > _request_address.size())
			_request_address.push_back(std::make_pair(inet_addr("0.0.0.0"),80));
		size_t colon_pos = command[i].find(':');
		if (colon_pos != std::string::npos) {
			std::string ip_addr = command[i].substr(0, colon_pos);
			if (!ifIPvalid(ip_addr))
				throw std::logic_error("Invalid IP address");
			_request_address.back().first = inet_addr(ip_addr.c_str());
			if (_request_address.back().first == INADDR_NONE)
				throw std::logic_error("Invalid IP address");
			_request_address.back().second = str_to_int(command[i].substr
					(colon_pos + 1, command[i].size() - colon_pos));
			if (_request_address.back().second > 65535 || _request_address
			.back().second < 0)
				throw std::logic_error("Invalid port");
		}
		else if (command[i].find('.') != std::string::npos) {
			if (!ifIPvalid(command[i]))
				throw std::logic_error("Invalid IP address");
			_request_address.back().first = inet_addr(command[i].c_str());
			if (_request_address.back().first == INADDR_NONE)
				throw (std::logic_error("Invalid IP address"));
		}
		else {
			_request_address.back().second = str_to_int(command[i].substr
					(0, command[i].size()));
			if (_request_address.back().second > 65535 ||
				_request_address.back().second < 0)
				throw std::logic_error("Invalid port");
		}
	}
}

void ServerConfig::parseServerNames(std::vector<std::string>& command) {

	if (command.size() == 1)
		throw std::logic_error("Config syntax error in server_name");
	_server_names.clear();
	for (size_t i = 1; i < command.size(); ++i) {
		_server_names.insert(command[i]);
	}
}

void ServerConfig::parseErrorPages(std::vector<std::string>& command) {

	if (command.size() < 3)
		throw std::logic_error("Config syntax error in server_name");
	for (size_t i = 1; i < command.size() - 1; ++i) {
		int num = str_to_int(command[i]);
		if (num < 100 || num > 505)
			throw std::logic_error("Config syntax error in error_pages: no "
								   "such code of error");
		_error_pages[num] = command[command.size() - 1];
	}
}

void ServerConfig::parseRoot(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw std::logic_error("Config syntax error in root");
	if (command[1][0] != '/')
		throw std::logic_error("Config syntax error in root: root should "
							   "begin with /");
	if (command[1][command[1].length() - 1] == '/')
		throw std::logic_error("Config syntax error in root: root should "
							   "not end with /");
	_root = command[1];
	_routes.front().setRoot(_root);
}

void ServerConfig::parseCGI(std::vector<std::string>& command) {

	if (command.size() != 3)
		throw std::logic_error("Config syntax error in cgi");
	if (command[1][0] != '.')
		throw std::logic_error("Error in config:m cgi extension should begin "
							   "with '.'");
	_cgi.insert(std::make_pair(command[1], command[2]));
}

void ServerConfig::parseIndex(std::vector<std::string>& command) {

	if (command.size() < 2)
		throw std::logic_error("Config syntax error in index");
	_default_pages.clear();
	for (size_t i = 1; i < command.size(); ++i)
		_default_pages.insert(command[i]);
}

void ServerConfig::parseRoutePreporation(std::ifstream& file,
											std::vector<std::string>& command) {

	if (command.size() < 2)
		throw std::logic_error("Syntax error in location block");
	if (command[1][0] != '/')
		throw std::logic_error("Syntax error in location route");
	if (command[1] != "/")
		_routes.push_back(Route(command[1], _root, _default_pages,
								_error_pages, _cgi));
	try {
		if (command[1] == "/")
			_routes.front().parseRouteInit(file, command, _root,
										   _default_pages, _error_pages, _cgi);
		else
			_routes.back().parseRouteInit(file, command, _root);
	}
	catch (std::logic_error& e) {
		throw;
	}
}

void ServerConfig::parseServer(std::ifstream& file) {

	std::string str;
	bool in_brackets = true;
	while (std::getline(file, str)) {
		if (str.empty())
			continue;
		if (str == "}") {
			in_brackets = false;
			break;
		}
		std::vector<std::string> command = str_split(str);
		if (command[0] == "listen") {
			try {
				parseRequestAddress(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "server_name") {
			try {
				parseServerNames(command);
			}
			catch (std::logic_error& e) {
				throw ;
			}
		}
		else if (command[0] == "error_page") {
			try {
				parseErrorPages(command);
			}
			catch (std::logic_error& e) {
				throw ;
			}
		}
		else if (command[0] == "root") {
			try {
				parseRoot(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "index") {
			try {
				parseIndex(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "cgi") {
			try {
				parseCGI(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "location") {
			try {
				parseRoutePreporation(file, command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else
			throw std::logic_error("Invalid option in config found");
		command.clear();
	}
	if (in_brackets)
		throw std::logic_error("Config error: brackets unclosed");
}

bool ServerConfig::ifIPvalid(std::string& ip_address) {

	int points = 0;
	for (size_t i = 0; i < ip_address.size(); ++i) {
		if (ip_address[i] == '.')
			++points;
	}
	if (points == 3)
		return true;
	return false;
}

const std::vector<std::pair<in_addr_t, int> >&
        ServerConfig::getVectorOfAddresses() const {
	return _request_address;
}

const std::set<std::string>& ServerConfig::getServerNames() const {
	return _server_names;
}

const std::vector<Route>& ServerConfig::getServerRoutes() const {
	return _routes;
}