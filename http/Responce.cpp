/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Responce.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: msimon <msimon@student.21-school.ru>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/03/24 15:04:37 by msimon            #+#    #+#             */
/*   Updated: 2022/04/27 15:42:47 by msimon           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Responce.hpp"

Responce::Responce(): _head(""), _body(NULL), _server_name("JUM webserv/0.0.1")
{
	_code_error_text["100"] = "Continue";
	_code_error_text["101"] = "Switching Protocol";
	_code_error_text["102"] = "Processing";
	_code_error_text["103"] = "Early Hints";
	_code_error_text["200"] = "OK";
	_code_error_text["201"] = "Created";
	_code_error_text["202"] = "Accepted";
	_code_error_text["203"] = "Non-Authoritative Information";
	_code_error_text["204"] = "No Content";
	_code_error_text["205"] = "Reset Content";
	_code_error_text["206"] = "Partial Content";
	_code_error_text["300"] = "Multiple Choice";
	_code_error_text["301"] = "Moved Permanently";
	_code_error_text["302"] = "Found";
	_code_error_text["303"] = "See Other";
	_code_error_text["304"] = "Not Modified";
	_code_error_text["305"] = "Use Proxy";
	_code_error_text["306"] = "Switch Proxy";
	_code_error_text["307"] = "Temporary Redirect";
	_code_error_text["308"] = "Permanent Redirect";
	_code_error_text["400"] = "Bad Request";
	_code_error_text["401"] = "Unauthorized";
	_code_error_text["402"] = "Payment Required";
	_code_error_text["403"] = "Forbidden";
	_code_error_text["404"] = " Not Found";
	_code_error_text["405"] = "Method Not Allowed";
	_code_error_text["406"] = "Not Acceptable";
	_code_error_text["407"] = "Proxy Authentication Required";
	_code_error_text["408"] = "Request Timeout";
	_code_error_text["409"] = "Conflict";
	_code_error_text["410"] = "Gone";
	_code_error_text["411"] = "Length Required";
	_code_error_text["412"] = "Precondition Failed";
	_code_error_text["413"] = "Request Entity Too Large";
	_code_error_text["414"] = "Request-URI Too Long";
	_code_error_text["415"] = "Unsupported Media Type";
	_code_error_text["416"] = "Requested Range Not Satisfiable";
	_code_error_text["417"] = "Expectation Failed";
	_code_error_text["500"] = "Internal Server Error";
	_code_error_text["501"] = "Not Implemented";
	_code_error_text["502"] = "Bad Gateway";
	_code_error_text["503"] = "Service Unavailable";
	_code_error_text["504"] = "Gateway Timeout";
	_code_error_text["505"] = "HTTP Version Not Supported";
	_code_error_text["508"] = "Loop Detected";
	_mime_list["aac"] = "audio/aac";
	_mime_list["abw"] = "application/x-abiword";
	_mime_list["arc"] = "application/x-freearc";
	_mime_list["avi"] = "video/x-msvideo";
	_mime_list["azw"] = "application/vnd.amazon.ebook";
	_mime_list["bin"] = "application/octet-stream";
	_mime_list["bmp"] = "image/bmp";
	_mime_list["bz"] = "application/x-bzip";
	_mime_list["bz2"] = "application/x-bzip2";
	_mime_list["csh"] = "application/x-csh";
	_mime_list["css"] = "text/css; charset=UTF-8";
	_mime_list["csv"] = "text/csv; charset=UTF-8";
	_mime_list["doc"] = "application/msword";
	_mime_list["docx"] = "application/vnd.openxmlformats-officedocument.wordprocessingml.document";
	_mime_list["eot"] = "application/vnd.ms-fontobject";
	_mime_list["epub"] = "application/epub+zip";
	_mime_list["gz"] = "application/gzip";
	_mime_list["gif"] = "image/gif";
	_mime_list["htm"] = "text/html; charset=UTF-8";
	_mime_list["html"] = "text/html; charset=UTF-8";
	_mime_list["ico"] = "image/vnd.microsoft.icon";
	_mime_list["ics"] = "text/calendar; charset=UTF-8";
	_mime_list["jar"] = "application/java-archive";
	_mime_list["jpeg"] = "image/jpeg";
	_mime_list["jpg"] = "image/jpeg";
	_mime_list["js"] = "text/javascript; charset=UTF-8";
	_mime_list["json"] = "application/json";
	_mime_list["jsonld"] = "application/ld+json";
	_mime_list["mid"] = "audio/midi";
	_mime_list["midi"] = "audio/x-midi";
	_mime_list["mjs"] = "text/javascript; charset=UTF-8";
	_mime_list["mp3"] = "audio/mpeg";
	_mime_list["mpeg"] = "video/mpeg";
	_mime_list["mpkg"] = "application/vnd.apple.installer+xml";
	_mime_list["odp"] = "application/vnd.oasis.opendocument.presentation";
	_mime_list["ods"] = "application/vnd.oasis.opendocument.spreadsheet";
	_mime_list["odt"] = "application/vnd.oasis.opendocument.text";
	_mime_list["oga"] = "audio/ogg";
	_mime_list["ogv"] = "video/ogg";
	_mime_list["ogx"] = "application/ogg";
	_mime_list["opus"] = "audio/opus";
	_mime_list["otf"] = "font/otf";
	_mime_list["png"] = "image/png";
	_mime_list["pdf"] = "application/pdf";
	_mime_list["php"] = "application/php";
	_mime_list["ppt"] = "application/vnd.ms-powerpoint";
	_mime_list["pptx"] = "application/vnd.openxmlformats-officedocument.presentationml.presentation";
	_mime_list["rar"] = "application/vnd.rar";
	_mime_list["rtf"] = "application/rtf";
	_mime_list["sh"] = "application/x-sh";
	_mime_list["svg"] = "image/svg+xml";
	_mime_list["swf"] = "application/x-shockwave-flash";
	_mime_list["tar"] = "application/x-tar";
	_mime_list["tif"] = "image/tiff";
	_mime_list["tiff"] = "image/tiff";
	_mime_list["ts"] = "video/mp2t";
	_mime_list["ttf"] = "font/ttf";
	_mime_list["txt"] = "text/plain; charset=UTF-8";
	_mime_list["vsd"] = "application/vnd.visio";
	_mime_list["wav"] = "audio/wav";
	_mime_list["weba"] = "audio/webm";
	_mime_list["webm"] = "video/webm";
	_mime_list["webp"] = "image/webp";
	_mime_list["woff"] = "font/woff";
	_mime_list["woff2"] = "font/woff2";
	_mime_list["xhtml"] = "application/xhtml+xml";
	_mime_list["xls"] = "application/vnd.ms-excel";
	_mime_list["xlsx"] = "application/vnd.openxmlformats-officedocument.spreadsheetml.sheet";
	_mime_list["xml"] = "application/xml";
	_mime_list["xul"] = "application/vnd.mozilla.xul+xml";
	_mime_list["zip"] = "application/zip";
	_mime_list["3gp"] = "video/3gpp";
	_mime_list["3g2"] = "video/3gpp2";
	_mime_list["7z"] = "application/x-7z-compressed";	
}

Responce::~Responce()
{
	if (_body)
		delete _body;
}

std::string	Responce::getExtension(std::string const& path)
{
	size_t		pos = path.find(".");
	size_t		i;

	if (pos == std::string::npos)
		return ("");
	while (1)
	{
		i = path.find(".", pos + 1);
		if (i != std::string::npos)
			pos = i;
		else
			break;
	}
	return path.substr(pos + 1);
}

std::string	Responce::getType(std::string const& path)
{
	std::string	ext = Connect::down_str(getExtension(path));
	std::map<std::string, std::string>::iterator	it;

	it = _mime_list.find(ext);
	if (it != _mime_list.end())
		return it->second;
	return "application/octet-stream";
}

void	Responce::sending(Connect* conn, std::string const& http_code)
{
	if (http_code == "200")
	{
		if (!conn->location)
			throw (std::runtime_error("503"));
		conn->full_file_path = "";
		if (_body)		
			delete _body;
		_body = NULL;

		if (conn->location->getRedirection() != "")
			set_redirection(conn);
		else
		{			
			if (conn->location->getRoute() == conn->head.get("uri"))
				set_index_page(conn);
			if (conn->full_file_path == "" && conn->location->getAutoindex()
				&& conn->head.get("uri").data()[conn->head.get("uri").length() - 1] == '/')
				set_directories(conn);
			else
			{
				if (conn->full_file_path == "")
				{
					conn->full_file_path = conn->head.get("uri").substr(conn->location->getRoute().length());
					if (conn->full_file_path.length() == 0 || conn->full_file_path[0] != '/')
						conn->full_file_path = "/" + conn->full_file_path;
					conn->full_file_path = conn->location->getRoot() + conn->full_file_path;
				}
				std::string path_prg = getInterpretator(conn);
				if (path_prg != "")
				{
					_head = "";
					if (_body)		
						delete _body;
					_body = new Content();
					handleCGI(conn, path_prg, _head, _body);
				}
				else if (conn->head.get("method") == "PUT")
					set_load_file(conn);
				else if (conn->head.get("method") == "DELETE")
					set_delete_file(conn);
				else
					set_content_file(conn);
			}
		}
	}
	else
		set_other_page(conn, http_code);
	if (_body && _body->len())
		_head += "Content-Length: " + std::to_string(_body->len()) + "\r\n\r\n";
	else
		_head += "Content-Length: 0\r\n\r\n";
	if (send(conn->fds, _head.data(), _head.length(), 0) != static_cast<ssize_t>(_head.length()))
		throw (std::runtime_error("900"));
	if (_body && _body->len())
		if (send(conn->fds, _body->get_content(), _body->len(), 0) != static_cast<ssize_t>(_body->len()))
			throw (std::runtime_error("900"));
}

void	Responce::set_other_page(Connect* conn, std::string const& code, bool f_body)
{
	try {
		std::map<std::string, std::string>::iterator	code_it = _code_error_text.find(code);
		if (code_it == _code_error_text.end())
			code_it = _code_error_text.find("500");

		if (conn->head.get("method") == "HEAD")
			f_body = 0;

		if (_body)
			delete _body;
		_body = new ContentFile();
		_head = "HTTP/1.1 " + code_it->first + " " + code_it->second + "\r\n";
		if (f_body)
			_head += "Content-Type: text/html; charset=UTF-8\r\n";
		_head += "Connection: keep-alive\r\n";
		_head += "Server: " + std::string(_server_name) + "\r\n";
		if (conn->location)
		{
			std::map<int, std::string>				tmp = conn->location->getErrorPages();
			std::map<int, std::string>::iterator	tmp_it = tmp.find(std::atol(code_it->first.data()));
			if (tmp_it != tmp.end())
			{
				try {_body->read(tmp_it->second);}
				catch (std::exception &e) {_body->clean();}
			}
		}
		if (f_body && _body->len() == 0)
		{
			_body->push_back("<html><head><meta charset=\"utf-8\"><meta http-equiv=\"X-UA-Compatible\" content=\"IE=edge\">");
			_body->push_back("<meta name=\"viewport\" content=\"width=device-width, initial-scale=1\"><title>");
			_body->push_back(code_it->first + " - " + code_it->second);
			_body->push_back("</title></head><body style='width: 100%;height: 100%;background-color: #21232a;margin: 0;");
			_body->push_back("line-height: 1.15;color: #fff;text-align: center;text-shadow: 0 2px 4px rgba(0,0,0,.5);padding: 0;");
			_body->push_back("min-height: 100%;-webkit-box-shadow: inset 0 0 100px rgba(0,0,0,.8);box-shadow: inset 0 0 100px rgba(0,0,0,.8);");
			_body->push_back("display: table;font-family: \"Open Sans\",Arial,sans-serif;text-align: center;text-shadow: 0 2px 4px rgba(0,0,0,.5);'>");
			_body->push_back("<div style='display: table-cell;vertical-align: middle;padding: 0 20px;'><h1 style='font-family: inherit;font-weight: 500;");
			_body->push_back("line-height: 1.1;color: inherit;font-size: 36px;'>");
			_body->push_back(code_it->second);
			_body->push_back("&nbsp;<small style='font-size: 150%;font-weight: 400;line-height: 1;color: #777;'>");
			_body->push_back(code_it->first);
			_body->push_back("</small></h1></div></body></html>");
		}
	}
	catch (std::exception &e) {
		std::cerr << "failed to send error to client\n";
	}
}

void	Responce::set_redirection(Connect* conn)
{
	if (conn->location->getRoute() == conn->location->getRedirection())
		throw (std::runtime_error("508"));
	_head = "HTTP/1.1 307 " + _code_error_text.find("307")->second + "\r\n";
	_head += "Connection: keep-alive\r\n";
	_head += "Location: " + conn->location->getRedirection() + conn->head.get("uri").substr(conn->location->getRoute().length());
	if (conn->get_str != "")
		_head += "?" + conn->get_str;
	_head += "\r\n";
}

void	Responce::set_index_page(Connect* conn)
{
	std::set<std::string>			tmp_set = conn->location->getDefaultPages();
	std::set<std::string>::iterator	tmp_set_it = tmp_set.begin();
	std::ifstream		file_index;
	while (tmp_set_it != tmp_set.end())
	{
		conn->full_file_path = conn->location->getRoot() + "/" + *tmp_set_it;
		file_index.open(conn->full_file_path);
		if (file_index.is_open())
		{
			file_index.close();
			break;
		}
		file_index.close();
		conn->full_file_path = "";
		tmp_set_it++;
	}
}

void	Responce::set_directories(Connect* conn)
{
	std::string		route = conn->location->getRoute();
	std::string		uri = conn->head.get("uri");
	std::string		path = conn->location->getRoot() + "/" + uri.substr(route.length());	
	std::string		file_path;
	std::string		files_content = "";
	std::string		dirs_content = "";
	DIR*			p_dir;
	struct dirent*	dir_el;
	struct stat		buf;
	char 			time_str[32];

	if (uri != route)
	{
		size_t	i = uri.length() - 2;
		while (i > 0 && uri[i] != '/')
			i--;
		dirs_content += "<div style=\"font-size: 18px;margin-bottom: 5px;\"><a href=\"";
		dirs_content += uri.substr(0, i + 1);
		dirs_content += "\" style=\"display: inline-block;width: 70%;\">..</a></div>";
	}

	p_dir = opendir(path.data());
	if (p_dir)
	{
		dir_el = readdir(p_dir);
		while (dir_el)
		{
			if (dir_el->d_name[0] != '.')
			{
				file_path = path + "/" + dir_el->d_name;
				if (!stat(file_path.data(), &buf))
				{
					std::strftime(time_str, 32, "%d.%m.%Y %H:%M:%S", std::localtime(&(buf.st_ctime)));
					if (S_ISDIR(buf.st_mode))
					{
						dirs_content += "<div style=\"font-size: 18px;margin-bottom: 5px;\"><a href=\"";
						dirs_content += uri + dir_el->d_name + "/";
						dirs_content += "\" style=\"display: inline-block;width: 70%;\">" + std::string(dir_el->d_name) + "/";
						dirs_content += "</a><span style=\"width: 20%;display: inline-block;\">" + std::string(time_str);
						dirs_content += "</span><span>-</span></div>";
					}
					else
					{
						files_content += "<div style=\"font-size: 18px;margin-bottom: 5px;\"><a href=\"";
						files_content += uri + dir_el->d_name;
						files_content += "\" style=\"display: inline-block;width: 70%;\">" + std::string(dir_el->d_name);
						files_content += "</a><span style=\"width: 20%;display: inline-block;\">" + std::string(time_str);
						files_content += "</span><span>" + std::to_string(buf.st_size) + "</span></div>";
					}
				}
			}
			dir_el = readdir(p_dir);
		}
		closedir(p_dir);
	}
	else
	{
		if (errno == EACCES || errno == ENOTDIR)
			throw (std::runtime_error("403"));
		if (errno == ENOENT)
			throw (std::runtime_error("404"));
		throw (std::runtime_error("500"));
	}

	_body = new Content();
	_head = "HTTP/1.1 200 " + _code_error_text.find("200")->second + "\r\n";
	_head += "Content-Type: text/html; charset=UTF-8\r\n";
	_head += "Connection: keep-alive\r\n";
	_head += "Server: " + std::string(_server_name) + "\r\n";

	_body->push_back("<div style=\"font-size: 40px;margin-top: 20px;\">Index of ");
	_body->push_back(conn->head.get("uri"));
	_body->push_back("<div style=\"width: 100%;height: 0px;border: solid 1px gray;margin-top: 20px;margin-bottom: 20px;\"></div>");
	_body->push_back(dirs_content);
	_body->push_back(files_content);
	_body->push_back("<div style=\"width: 100%;height: 0px;border: solid 1px gray;margin-top: 20px;margin-bottom: 20px;\"></div>");
}

void	Responce::set_load_file(Connect* conn)
{
	std::string		path = conn->location->getUploadDirectory()
		+ "/" + conn->head.get("uri").substr(conn->location->getRoute().length());
	std::ifstream	found_file;
	bool			f_file = 0;
	std::ofstream	put_file;

	found_file.open(path);
	f_file = found_file.is_open();
	found_file.close();
	put_file.open(path);
	if (put_file.is_open())
	{
		conn->body.write_data(put_file);
		put_file.close();
		if (f_file)
			set_other_page(conn, "204", 0);
		else
			set_other_page(conn, "201", 0);
	}
	else
	{
		put_file.close();
		throw (std::runtime_error("412"));
	}
}

void	Responce::set_delete_file(Connect* conn)
{
	std::string		path = conn->location->getUploadDirectory()
		+ "/" + conn->head.get("uri").substr(conn->location->getRoute().length());
	std::ifstream	found_file;

	found_file.open(path);
	if (found_file.is_open())
	{
		found_file.close();
		std::remove(path.data());
		set_other_page(conn, "204", 0);
	}
	else
	{
		found_file.close();
		throw (std::runtime_error("412"));
	}

}

void	Responce::set_content_file(Connect* conn)
{
	_body = new ContentFile();
	if (conn->head.get("method") != "HEAD")
		_body->read(conn->full_file_path);
	_head = "HTTP/1.1 200 " + _code_error_text.find("200")->second + "\r\n";
	_head += "Server: " + std::string(_server_name) + "\r\n";
	_head += "Connection: keep-alive\r\n";
	_head += "Content-Type: " + getType(conn->full_file_path) + "\r\n";
}

std::string const&	Responce::get_code(std::string const& code)
{
	std::map<std::string, std::string>::iterator	code_it = _code_error_text.find(code);
	if (code_it == _code_error_text.end())
		code_it = _code_error_text.find("500");
	return (code_it->first);
}