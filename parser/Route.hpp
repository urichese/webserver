#ifndef WEBSERV_ROUTES_HPP
#define WEBSERV_ROUTES_HPP

#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <string>
#include <fstream>
#include "utils.hpp"

class Route {

private:
	std::string							_route;
	std::set<std::string>				_default_pages;
	std::set<std::string>				_http_methods;
	std::string							_redirection;
	std::string							_root;
	bool 								_autoindex;
	std::string							_upload_dir;
	std::map<int, std::string>			_error_pages;
	std::map<std::string, std::string>	_cgi;
	int 								_limit_body_size;

private:
	Route();

public:
	Route(std::string& route, std::string& root, std::set<std::string>&
	        default_pages, std::map<int, std::string>& error_pages,
			std::map<std::string, std::string>& cgi);
	Route(std::string& root, std::set<std::string>&
	default_pages, std::map<int, std::string>&
	        error_pages, std::map<std::string, std::string>& cgi);
	~Route();
	void	parseRouteInit(std::ifstream& file, std::vector<std::string>&
	command, std::string& root);
	void	parseRouteInit(std::ifstream& file, std::vector<std::string>&
	command, std::string& root, std::set<std::string>&
	default_pages, std::map<int, std::string>& error_pages,
	std::map<std::string, std::string>& cgi);
	void setRoot(const std::string& root);
	const std::string& getRoute() const;
	const std::set<std::string>& getDefaultPages() const;
	const std::set<std::string>& getHTTPmethods() const;
	const std::string& getRedirection() const;
	bool getAutoindex() const;
	const std::string& getRoot() const;
	const std::string& getUploadDirectory() const;
	const std::map<int, std::string>& getErrorPages() const;
	const std::map<std::string, std::string>& getCGI() const;
	int getLimitBodySize() const;


private:
	void	parsingProcess(std::ifstream& file, std::vector<std::string>&
	command);
	void parseBrackets(std::ifstream& file,
						 std::vector<std::string>& command);
	void parseHTTPmethods(std::vector<std::string>& command);
	void parseRedirection(std::vector<std::string>& command);
	void parseRoot(std::vector<std::string>& command);
	void parseIndex(std::vector<std::string>& command);
	void parseAutoindex(std::vector<std::string>& command);
	void parseUploadDir(std::vector<std::string>& command);
	void parseClientMaxBodySize(std::vector<std::string>& command);
};




#endif