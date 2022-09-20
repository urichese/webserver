#include "Route.hpp"

Route:: Route(std::string& root, std::set<std::string>&
default_pages, std::map<int, std::string>& error_pages, std::map<std::string,
std::string>& cgi) :
		_route("/"),
		_default_pages(default_pages),
		_http_methods(),
		_redirection(),
		_root(root),
		_autoindex(false),
		_upload_dir("/downloads"),
		_error_pages(error_pages),
		_cgi(cgi),
		_limit_body_size(1000000) {

	_http_methods.insert("GET");
	_http_methods.insert("POST");
	_http_methods.insert("DELETE");
	_http_methods.insert("PUT");
	_http_methods.insert("HEAD");
}

Route:: Route(std::string& route, std::string& root, std::set<std::string>&
        default_pages, std::map<int, std::string>& error_pages,
		std::map<std::string, std::string>& cgi) :
			_route(route),
			_default_pages(default_pages),
			_http_methods(),
			_redirection(),
			_root(root),
			_autoindex(false),
			_upload_dir("/downloads"),
			_error_pages(error_pages),
			_cgi(cgi),
			_limit_body_size(1000000) {

		_http_methods.insert("GET");
		_http_methods.insert("POST");
		_http_methods.insert("DELETE");
		_http_methods.insert("PUT");
		_http_methods.insert("HEAD");
}

Route:: ~Route() {}

void Route::parseBrackets(std::ifstream& file,
						  std::vector<std::string>& command) {

	if (command[0] == "{")
		return ;
	command.clear();
	std::string str;
	while (std::getline(file, str)) {
		if (str.empty())
			continue ;
		if (str == "{")
			return ;
		else
			throw (std::logic_error("Commands outside brackets in location"));
	}
	throw (std::logic_error("No opening brackets in location"));
}

void Route::parseHTTPmethods(std::vector<std::string>& command) {

	if (command.size() < 2)
		throw (std::logic_error("Syntax error in HTTP_methods"));
	_http_methods.clear();
	for (size_t i = 1; i < command.size(); ++i) {
		if (command[i] != "GET" && command[i] != "POST" &&
			command[i] != "DELETE" && command[i] != "PUT" && command[i] !=
			"HEAD")
			throw std::logic_error("Invalid http method in config");
		_http_methods.insert(command[i]);
	}
}
void Route::parseRedirection(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in route redirection"));
	_redirection = command[1];
}

void Route::parseRoot(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in route root config"));
	if (command[1][0] != '/')
		throw (std::logic_error("Config syntax error in route root: root "
								"should begin with /"));
	if (command[1][command[1].length() - 1] == '/')
		throw std::logic_error("Config syntax error in route root: root should "
							   "not end with /");
	_root = command[1];
}

void Route::parseIndex(std::vector<std::string>& command) {

	if (command.size() < 2)
		throw (std::logic_error("Syntax error in route index config"));
	_default_pages.clear();
	for (size_t i = 1; i < command.size(); ++i)
		_default_pages.insert(command[i]);
}

void Route::parseAutoindex(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in autoindex config"));
	if (command[1] == "on")
		_autoindex = true;
	else if (command[1] != "off")
		throw (std::logic_error("Syntax error in autoindex config"));
}

void Route::parseUploadDir(std::vector<std::string>& command) {

	if (command.size() != 2)
		throw (std::logic_error("Syntax error in upload directory config"));
	if (command[1][0] != '/')
		throw (std::logic_error("Syntax error in upload directory config"));
	_upload_dir = command[1];
}

void Route::parseRouteInit(std::ifstream& file,
						   std::vector <std::string>& command,
						   std::string& root) {

	std::string route = command[1];
	if (route[route.length() - 1] == '/')
		_root = root + route.substr(0, route.length() - 1);
	else
		_root = root + route;
	try {
		parseBrackets(file, command);
	}
	catch (std::logic_error& e) {
		throw;
	}
	try {
		parsingProcess(file, command);
	}
	catch (std::logic_error& e) {
		throw;
	}
}

void Route::parseRouteInit(std::ifstream& file,
						   std::vector <std::string>& command,
						   std::string& root,
						   std::set <std::string>& default_pages,
						   std::map<int, std::string>& error_pages,
						   std::map<std::string, std::string>& cgi) {

	std::string route = command[1];
	if (route[route.length() - 1] == '/')
		_root = root + route.substr(0, route.length() - 1);
	else
		_root = root + route;
	try {
		parseBrackets(file, command);
	}
	catch (std::logic_error& e) {
		throw;
	}
	_default_pages = default_pages;
	_error_pages = error_pages;
	_cgi = cgi;
	try {
		parsingProcess(file, command);
	}
	catch (std::logic_error& e) {
		throw;
	}
}

void Route::setRoot(const std::string& root) {

	_root = root;
}

void Route::parseClientMaxBodySize(
		std::vector<std::string>& command) {

	if (command.size() != 2)
		throw std::logic_error("Config syntax error in client_max_body_size");
	int num = str_to_int(command[1]);
	if (num < 0)
		throw std::logic_error("Config syntax error in client_max_body_size");
	_limit_body_size = num;
}

void Route::parsingProcess(std::ifstream& file, std::vector<std::string>&
        command) {

	std::string str;
	bool in_brackets = true;
	while (getline(file, str)) {
		if (str.empty())
			continue;
		if (str == "}") {
			in_brackets = false;
			break;
		}
		command = str_split(str);
		if (command[0] == "http_methods") {
			try {
				parseHTTPmethods(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "redirection") {
			try {
				parseRedirection(command);
			}
			catch (std::logic_error& e) {
				throw;
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
		else if (command[0] == "client_max_body_size") {
			try {
				parseClientMaxBodySize(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "autoindex") {
			try {
				parseAutoindex(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else if (command[0] == "upload_directory") {
			try {
				parseUploadDir(command);
			}
			catch (std::logic_error& e) {
				throw;
			}
		}
		else
			throw std::logic_error("No such option in location config");
		command.clear();
	}
	if (in_brackets)
		throw (std::logic_error("Brackets unclosed in location config"));
}

const std::string& Route::getRoute() const {
	return _route;
}

const std::set<std::string>& Route::getDefaultPages() const {
	return _default_pages;
}

const std::set<std::string>& Route::getHTTPmethods() const {
	return _http_methods;
}

const std::string& Route::getRedirection() const {
	return _redirection;
}

bool Route::getAutoindex() const {
	return _autoindex;
}

const std::string& Route::getRoot() const {
	return _root;
}

const std::string& Route::getUploadDirectory() const {
	return _upload_dir;
}

const std::map<int, std::string>& Route::getErrorPages() const {
	return _error_pages;
}

const std::map<std::string, std::string>& Route::getCGI() const {
	return _cgi;
}

int Route::getLimitBodySize() const {
	return _limit_body_size;
}